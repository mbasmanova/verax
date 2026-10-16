# Graph Queries — Lowering Patterns Without Repetition

*How `TranslatePass` lowers a `GraphMatchNode` into joins over the element
tables. The logical model is in [GraphTable.md](GraphTable.md); repetition is
in [GraphTable-repetition.md](GraphTable-repetition.md).*

## Stages

`Translator::GraphMatchLowering` runs in stages, each reading what the earlier
ones settled:

1. **Bind:** binds each pattern name to an element, and records the paths and
   the edge occurrences between their vertices. A plain subpath's patterns
   bind as part of the path, and a vertex pattern right after another binds
   the same element.
2. **Narrow:** drops the tables an element cannot match given its neighbors.
3. **Copy:** an element that several paths with a selector bind gets a copy
   for each of them but the first, since each such path is limited on its own
   before paths join.
4. **Fold:** a vertex at a single edge end joins inside the legs of that edge.
   Other vertices keep a relation of their own.
5. **Build:** builds each element's relation.
6. **Connect:** connects each edge to the unfolded vertices next to it, and
   each copy to its original, on their identities.
7. **Join:** joins each path with a selector on its own, filters it with its
   term predicates, and limits it. Then joins the rest of the connected
   elements and filters them with the other paths' term predicates. Groups
   that share no element join with a cross product, and the node's predicate
   filters the result.

## Subpaths and adjacent vertex patterns

A subpath without repetition only groups patterns: `(a) ((x) -[e]-> (y) WHERE
x.since > 2020) (b)` matches like `(a) -[e]-> (b)` with the subpath's
condition applied to each match. Its patterns bind as part of the path, and
its condition joins the path's term predicates. `path_length` of a named
subpath counts its edges.

Two vertex patterns next to each other match one vertex, so the second binds
the first one's element: its name, if any, names that element too, and the
element keeps only the tables both label expressions match. In
`(a IS Person) (x WHERE x.name = 'Alice') -[e]-> (b)`, `a` and `x` are one
vertex, and the edge leaves from it.

## Element relations

Each edge pattern, and each vertex pattern that does not fold into an edge,
lowers to a relation `R(p)`: a `UnionAll` with one leg per candidate table, or
the table's plan alone when there is one candidate. Each leg is the table's
plan, translated afresh for `p`, projected to:

- **Identity:** the key columns, preceded by the table ID as a literal when the
  pattern has several candidate tables.
- **Endpoints**, for an edge: the source columns, preceded by the source table
  ID as a literal when the endpoint can reference several vertex tables; then
  the same for the destination.
- **Properties** that an output or a predicate reads. A property the table
  does not define is a typed NULL.

Because each pattern translates its table afresh,
`(a IS Person) -[e IS Knows]-> (b IS Person)` reads `person` twice with
distinct columns, as a self-join does.

A term's predicate becomes a `Filter`. A predicate reads `a.name` as a
dereference of the ROW-typed `a`, which the lowering maps to the property's
column.

## Candidate tables

Candidate tables start from the tables the label expression matches. An edge
table names the vertex table at each endpoint, so the lowering narrows
adjacent patterns against each other until nothing changes:

- A vertex pattern keeps the tables that some candidate of each adjacent edge
  pattern references at that endpoint.
- An edge pattern keeps the tables whose endpoints reference candidates of
  both adjacent vertex patterns.

A pattern left with no candidate tables makes the match empty: an empty
`Values` of the node's output type.

## Folding a vertex into its edge

Each edge table fixes the vertex table at each end, so a vertex pattern that
sits at one edge end joins inside each leg of that edge instead of having a
relation of its own. In

```
(a IS Person) -[IS Knows | LivesIn]-> (b)
```

the edge's relation is `(knows ⋈ person) UNION ALL (lives_in ⋈ city)`, each
leg joining on its own keys. `b`'s keys stay inside the legs, so they need no
shared column and no table ID, and may differ in type. A folded vertex's
identity is its edge's end columns, so a selector or a copy that reads it
reads those columns.

When an edge table and the vertex table at one of its ends read the same
table, and the edge's end columns are the vertex's key, each edge row is the
vertex row, since the key is unique and never null. The leg then reads that
table once, scanning the columns both tables need, and evaluates both tables'
projections over it, with no join. `person AS lives_in` is such an edge: its
source is the `person` row it comes from.

A vertex that several patterns share keeps a relation of its own: one that
joins two edges, as `b` in `(a) -> (b) -> (c)`, or a reused name. Its identity
crosses a union, so its tables' keys share columns and must have the same data
types. Narrowing usually leaves such a vertex one key type; where it does not,
the lowering fails with an error.

## Joins

Adjacent patterns join on identity. For `(v) -[e]-> (w)`:

- `v` joins `e` on `v.tableId = e.sourceTableId` and `v.key = e.source`.
- `e` joins `w` on the destination columns the same way.
- `<-[e]-` swaps source and destination.
- `-[e]-` reads `R(e)` in both orientations, as a `UnionAll` of the two. The
  second leg drops self-loops, where the source identity equals the
  destination identity, so a self-loop matches once.

Table IDs are compared only when an endpoint can reference several vertex
tables. After narrowing, an edge pattern with one candidate table leaves the
vertex pattern at that endpoint with one table, and a vertex pattern with one
table leaves every edge candidate referencing it; either way the join compares
keys only.

A name that appears twice binds one element: the second occurrence joins the
first on identity. Paths that share a name join on that name's identity.

The joins of one path form one inner-join cluster, so DPhyp chooses where to
start and which way to go. `MATCH ... WHERE` becomes a `Filter` above the
match, and `PushdownAndPrune` moves each conjunct to the patterns it reads
when no selector is in the way.

## Example

For the running example, `R(a)` is `person` filtered on `name = 'Alice'`,
`R(k)` is `knows` and `R(b)` is `person`. Each has one candidate table, so
identity is the key alone and the plan is the plan for this SQL:

```sql
SELECT b.name AS friend, k.since
FROM person a
JOIN knows k ON a.id = k.src
JOIN person b ON k.dst = b.id
WHERE a.name = 'Alice'
```

## Selectors

A path with a selector lowers to its own relation, and the selector applies to
that relation before paths join, following the evaluation order in
[GraphTable.md](GraphTable.md). The other paths join onto it through the
elements they share. An element that two paths with a selector share gets a
copy for the second, and the two join on the element's identity. An edge's
identity is its table and key, like a vertex's.

In a path without repetition, every match has the same length:

- `ALL` and `ALL SHORTEST` keep every match and add nothing.
- `ANY`, `ANY SHORTEST`, `ANY k` and `SHORTEST k` keep up to k matches per pair
  of endpoint identities. The lowering emits a `Window` computing
  `row_number()` partitioned by those identities and a `Filter` on
  `rank <= k`. `PushdownAndPrune` fuses the two into a `RowNumber` with a
  per-partition limit of k, which stops each partition after k rows.
- `SHORTEST k GROUPS` keeps every match, since all matches form one group.
