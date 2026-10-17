# Graph Queries — Repetition

*How optimizer v2 plans a repeated edge pattern such as `-[IS Knows]->{1,3}`,
or a repeated subpath: the `Repeat` node, each pass's rule for it, and its
lowering to a `FixedPoint`. Patterns without repetition are in
[GraphTable-lowering.md](GraphTable-lowering.md); the loop itself is in
[FixedPoint.md](FixedPoint.md).*

## Walks

`-[e]->{m,n}` matches a walk of between m and n edges. In `WALK` mode, the
default, a walk may visit a vertex or an edge more than once, and walks that
differ only in their edges are distinct matches:

```sql
SELECT * FROM GRAPH_TABLE (social
  MATCH (a IS Person WHERE a.name = 'Alice') -[IS Knows]->{1,3} (b IS Person)
  COLUMNS (b.name AS name))
```

returns one row for each walk of one to three `Knows` edges from Alice.

A condition inside the edge pattern applies to each hop:
`-[k IS Knows WHERE k.since > 2020]->{1,3}` walks only over edges since 2020.
Outside its pattern, `k` stands for one value per hop, an array.

A walk of zero hops ends at the vertex it starts from: with `{0,n}`, the
patterns on either side of the repetition also match one vertex. A repetition
`{1,1}` is a plain edge.

## The Repeat node

`Repeat` returns one row per walk of between `minHops` and `maxHops` hops from
a row of `start` to a row of `end`:

| Field | Meaning |
|---|---|
| `start`, `hop`, `end` | The three inputs: the path's patterns before the repetition, joined, with their predicates; one repetition of the repeated pattern, filtered by its conditions; the path's patterns after it. `end` is null when the walk ends at a row of `start`. |
| `startKeys` | The identity of the vertex the walk leaves from, over `start`. |
| `hopSourceKeys`, `hopDestinationKeys` | The identities of the vertex a hop leaves from and the one it reaches, over `hop`. |
| `endKeys` | The identity of the vertex the walk reaches, over `end`, or over `start` when `end` is null. |
| `minHops`, `maxHops` | The bounds, with `0 <= minHops <= maxHops`. Exactly one hop, `{1,1}`, is a plain join. |
| `outputColumns`, `sourceColumns` | The outputs and the columns they carry, by position. A column of `start` or `end` keeps its identity; `sourceColumns` is empty when every output is a column of `start` or `end`. A column of `hop` gives a fresh output: an array of its values on the walk's hops, from start to end, or, with `maxHops` of at most 1, its value, NULL for a walk of zero hops. |
| `hopCount` | Optional: the output that holds the walk's number of hops. |

The four key lists line up by position, as a join's keys do. Like a join's
keys, they are expressions over the inputs' columns.

**Identity.** Two vertex tables can hold the same key, so the identity a walk
follows includes the table ID wherever its vertices can come from more than
one table: as the ID column where it varies, or as a literal. Otherwise it is
the key alone. The tables counted are those a hop can leave from or reach, and
the start's and end's, which a walk of zero hops compares directly.

**Narrowing.** A walk leaves from a table a hop leaves from and reaches a table
a hop reaches. With `minHops` of 0, the start may also match any table the end
can, and the end any table the start can.

**Ends.** A walk's endpoints do not fold into the hop: the hop's relation
carries both end identities, and each endpoint keeps its own relation, or
reads its identity from another edge it folds into.

**Empty hop.** A `Repeat` whose hop is empty keeps only its walks of zero hops:
it is empty when `minHops` is above 0, and becomes `{0,0}` otherwise.

**Zero hops.** A walk of zero hops ends where it starts, so a repetition of
`{0,0}` lowers to its ends joined on their identity, with the names inside it
NULL. A repetition with `minHops` of 0 whose hop matches no table lowers the
same way.

## Repeated subpaths

A repeated subpath repeats a pattern with several elements, with a condition
that can read any of them:

```sql
MATCH (a IS Person WHERE a.name = 'Alice')
  ((x IS Person) -[IS Knows]-> (y IS Person) WHERE x.id < y.id){1,3}
  (b IS Person)
```

walks one to three `Knows` edges from Alice, each to a person with a larger
id. The first `x` is `a`, each repetition's `y` is the next one's `x`, and the
last `y` is `b`.

Its `Repeat` has the subpath's patterns, joined and filtered with their
conditions and the subpath's, as the hop. A hop leaves from the identity of the
subpath's first vertex and reaches that of its last. The patterns inside bind
elements of their own, which no join outside the walk reads, and the start and
end narrow to the tables of those two vertices as they do to a repeated edge's
ends. The subpath starts and ends with a vertex pattern, so repetitions meet at
a vertex.

## Optional subpaths

An optional subpath `( ... )?` matches its patterns once or not at all. Its
names stand for one element, or NULL when it matches zero times:

```sql
MATCH (a IS Person WHERE a.name = 'Alice')
  ((x IS Person) -[IS Knows]-> (m IS Person))? (v IS Person)
  -[IS Knows]-> (b IS Person)
COLUMNS (b.name AS reached, m.name AS via)
```

returns whom Alice knows, with `via` NULL, and whom they know, with `via` the
person in between. Both matches count, so a vertex reachable both ways appears
twice.

It lowers as a repeated subpath `{0,1}`, and its `Repeat` also outputs the
hop's columns, which the names inside it read. The subpath's condition filters
the hop, so it limits only the matches of one hop. A condition outside the
subpath that reads its names stays above the `Repeat`, since the names are NULL
for a walk of zero hops.

## Group variables and path length

A name inside a repetition stands for one element per hop, so a property read
outside it is an array of the values on the walk's hops, in order from start
to end, empty for a walk of zero hops:

```sql
MATCH (a IS Person WHERE a.name = 'Alice')
  ((x IS Person) -[IS Knows]-> (m IS Person)){1,3} (b IS Person)
COLUMNS (b.name AS b, m.name AS path)
```

returns whom Alice reaches and the people the walk passes through, such as
`('Dave', ['Bob', 'Carol', 'Dave'])`. The `Repeat` outputs an array for each
property the outputs read.

`path_length(p)` adds to the edges outside repetitions the edges on each walk's
hops: the walk's hop count times the edges in one hop. Each `Repeat` outputs
its hop count, which pruning drops when nothing reads it.

## Nested repetition

A repetition or an optional subpath inside a repeated or optional subpath fails
as not supported:

```sql
MATCH (a IS Person)
  ((x IS Person) -[IS Knows]->{1,2} (y IS Person))? (b IS Person)
```

Supporting it means the outer `Repeat`'s hop holds the inner walk: building
the hop lowers the inner repetition between the subpath's vertices, so the hop
is itself a `Repeat`, and LowerRepeat turns it into a fixed point inside the
outer fixed point's step.

## Where the Repeat sits

The lowering joins every connection except the repeated patterns. The rest of
the pattern then falls into connected groups. Each repeated pattern becomes a
`Repeat` from the group that holds its `from` vertex to the group that holds
its `to` vertex, which merges the two:

- In `(a) -[k]-> (x) -[e]->{1,3} (b)`, the start is `a ⋈ k ⋈ x`, so the
  predicates on `a` and `k` shrink the start before the loop runs.
- When both ends are already in one group, as in `(a) -[e]->{1,3} (a)`, the
  `Repeat` has no end: the walk only has to finish at `a`.
- A path with two repetitions nests: the second `Repeat`'s start holds the
  first.
- A selector over a path with repetition limits the joined rows, as it does
  for a path without one.

## Rules before the lowering

| Pass | Rule |
|---|---|
| `Decorrelate` | Rewrites the inputs. |
| `LimitAndOrder` | Barrier. |
| `PushdownAndPrune` | A `Repeat` row carries its start row's and end row's columns unchanged, so a conjunct that reads only one side moves into that side. A conjunct that reads a hop column it outputs stays above. Prunes the hop to its keys and the hop columns read above, and each side to its keys and the columns read above. |
| `FoldMetadataAggregate` | Rewrites the inputs. |
| `ConnectorPushdown` | Offers the `Repeat` whole when all its inputs belong to one connector that supports pushdown, otherwise its inputs. |
| `EstimateLeafStats` | Estimates the inputs. The `Repeat` itself has an unknown cardinality, like `FixedPoint`. |

## LowerRepeat

`LowerRepeatPass` runs after `EstimateLeafStats` and replaces each `Repeat`
with a `FixedPoint`, or with joins when no walk has more than one hop. It is
skipped when translation produced no `Repeat`.

The walk starts from the side with fewer estimated rows: the start, or the end
when it is present and smaller. Starting from the end is the mirror image, with
each hop read from its destination to its source. Starting from the start:

- **State:** the columns of the start that the result reads, the walk's
  current vertex, the arrays the result reads, and its hop count.
- **Anchor:** the start, with the current vertex set to the start key, empty
  arrays, and zero hops.
- **Step:** the latest walks with fewer than `maxHops` hops, joined with the hop
  on the current vertex and the hop's source. The current vertex becomes the
  hop's destination, each array gains the hop's value, and the hop count grows
  by one. A walk from the end prepends to the arrays, so they list the hops
  from start to end either way.
- **Result:** the walks with at least `minHops` hops, joined with the end on
  the current vertex and the end key. Without an end, the walks whose current
  vertex equals the end key. With `minHops` of 0, the anchor's walks of zero
  hops are part of the result.
- **Bound:** `maxIterations = maxHops + 1`. The step adds no rows once every
  walk has `maxHops` hops, and the loop stops on the empty delta one iteration
  later. Reaching `maxIterations` without converging fails the query.

Walks of at most one hop need no loop, so `{0,1}` and `{0,0}` carry a hop
count only when the result reads it. The walks are the anchor for zero hops,
the start joined with the hop for one, or the `UNION ALL` of the two, and the
result joins them with the end as above. The hop values the `Repeat` outputs
travel with the walks, as NULL in the anchor.

The hop appears once in the plan, as the build side of the step's join. Each
iteration reads only the latest walks. With several workers, each task that
reads part of the start runs its own walks, and the hop is broadcast to every
task (see [FixedPoint.md](FixedPoint.md#distributed-execution)). A hop too large
to broadcast needs the walks repartitioned on the new current vertex each
iteration, with the hop partitioned on its source; that plan is not built yet.

The hop count grows and the arrays gain values through the optimizer's
internal functions, which belong to no dialect: `bigint_add`, `array_append`
and `array_prepend`, in `velox/functions/axiom`. A process that runs these
plans registers them with `velox::functions::axiom::registerFunctions(prefix)`,
and the process that optimizes them records the prefix with
`FunctionRegistry::registerInternalPrefix`. A worker needs only Velox.

For `(a IS Person) -[IS Knows]->{1,2} (b IS Person)`, the Velox plan is:

```
- Project
  - HashJoin [walk_vertex = b.id]
    - Filter [walk_hops >= 1]
      - FixedPoint
          state walk (append), initial plan:
            - Project [a.name, a.id AS walk_vertex, 0 AS walk_hops]
              - TableScan person
          state walk_0 (hash table, key src), initial plan:
            - TableScan knows
          step:
            - Project [name, dst AS walk_vertex, bigint_add(walk_hops, 1)]
              - StateHashJoin [walk_0, probe walk_vertex]
                - Filter [walk_hops < 2]
                  - StateSource walk (delta)
    - TableScan person (b)
```

## Emit and the loop's state

Velox delivers table splits to a fixed point's initial plans, which run once
before the first iteration, and to the nodes above the loop, never to the step.
Emit therefore computes each part of the step that reads no recursive state
once, as an initial plan, and the step reads the result from loop state:

- An inner equi-join's build side becomes a `HashTableStateDeclaration`,
  probed by a `StateHashJoinNode`. The hop's hash table is built once for the
  whole loop.
- Any other such part becomes a `VectorStateDeclaration`, read by a
  `StateSourceNode`.

A join that does not qualify, such as one whose build side repeats a key,
uses the general form. Emit translates any valid IR; the hash table is how the
common case avoids rebuilding.

## Path modes and shortest paths

The lowering above covers `WALK`. Restrictive modes and shortest paths extend
the same `FixedPoint`:

- **`TRAIL` and `ACYCLIC`:** the state carries an array of visited edge or
  vertex identities, and the step keeps only rows that do not revisit one.
- **`ANY SHORTEST`, `ALL SHORTEST` and unbounded repetition:** the step drops
  walks whose search state was reached in an earlier iteration, an anti-join
  against the accumulated result. Without it, a cyclic graph never empties the
  frontier.
- **`SHORTEST k`:** the step counts the walks each pair of endpoints already
  has and drops rows past k.
- **Single-target shortest path:** the loop stops once the target is reached,
  a convergence predicate.

These need the fixed point to read the accumulated result and to stop on a
predicate. Velox supports both. The v2 `FixedPoint` can read the accumulated
result but stops only on an empty delta, and the logical plan exposes neither,
so Translate never produces them. A visited set that grows
incrementally also needs mutable keyed state in Velox; without it, the
anti-join rebuilds a hash table over all reached rows every iteration.
