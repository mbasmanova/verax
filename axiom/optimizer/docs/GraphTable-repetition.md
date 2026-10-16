# Graph Queries — Repeated Edges

*How optimizer v2 plans a repeated edge pattern such as `-[IS Knows]->{1,3}`:
the `Repeat` node, each pass's rule for it, and its lowering to a
`FixedPoint`. Patterns without repetition are in
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
| `start`, `hop`, `end` | The three inputs: the path's patterns before the repetition, joined, with their predicates; the repeated edge's relation, filtered by its own condition; the path's patterns after it. `end` is null when the walk ends at a row of `start`. |
| `startKeys` | The identity of the vertex the walk leaves from, over `start`. |
| `hopSourceKeys`, `hopDestinationKeys` | The identities of the vertex a hop leaves from and the one it reaches, over `hop`. |
| `endKeys` | The identity of the vertex the walk reaches, over `end`, or over `start` when `end` is null. |
| `minHops`, `maxHops` | The bounds, with `0 <= minHops <= maxHops`. Exactly one hop, `{1,1}`, is a plain join. |
| `outputColumns` | A subset of the columns `start` and `end` output, with the same identities. |

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

## Where the Repeat sits

The lowering joins every connection except the repeated edges. The rest of
the pattern then falls into connected groups. Each repeated edge becomes a
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
| `PushdownAndPrune` | A `Repeat` row carries its start row's and end row's columns unchanged, so a conjunct that reads only one side moves into that side. Prunes the hop to its keys and each side to its keys and the columns read above. |
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
  current vertex, and its hop count.
- **Anchor:** the start, with the current vertex set to the start key and zero
  hops.
- **Step:** the latest walks with fewer than `maxHops` hops, joined with the hop
  on the current vertex and the hop's source. The current vertex becomes the
  hop's destination, and the hop count grows by one.
- **Result:** the walks with at least `minHops` hops, joined with the end on
  the current vertex and the end key. Without an end, the walks whose current
  vertex equals the end key. With `minHops` of 0, the anchor's walks of zero
  hops are part of the result.
- **Bound:** `maxIterations = maxHops + 1`. The step adds no rows once every
  walk has `maxHops` hops, and the loop stops on the empty delta one iteration
  later. Reaching `maxIterations` without converging fails the query.

Walks of at most one hop need no loop, so `{0,1}` and `{0,0}` carry no hop
count. The walks are the anchor for zero hops, the start joined with the hop
for one, or the `UNION ALL` of the two, and the result joins them with the end
as above.

The hop appears once in the plan, as the build side of the step's join. Each
iteration reads only the latest walks. A fixed point runs on a single node
today; distributed, the walks would be repartitioned on the new current vertex
each iteration, and the hop would stay partitioned on its source.

The hop count is a `BIGINT` that grows by one per step. The lowering adds with
the function the dialect registers through
`FunctionRegistry::registerBigintAddition`, which the optimizer calls only
where the sum fits in `BIGINT`.

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
            - Project [name, dst AS walk_vertex, walk_hops + 1]
              - StateHashJoin [walk_0, probe walk_vertex]
                - Filter [walk_hops < 2]
                  - StateSource walk (delta)
    - TableScan person (b)
```

## Emit and the loop's state

Velox delivers table splits only to a fixed point's initial plans, which run
once before the first iteration, and to its trailing plan above the loop.
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
predicate. Velox and the v2 `FixedPoint` support both; the logical plan does
not expose them, so Translate never produces them. A visited set that grows
incrementally also needs mutable keyed state in Velox; without it, the
anti-join rebuilds a hash table over all reached rows every iteration.

`path_length` of a path with repetition is the literal length of its other
edges plus the walk's hop count, which the state already carries.
