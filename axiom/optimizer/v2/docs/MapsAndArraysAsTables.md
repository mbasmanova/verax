# Maps and Arrays as Tables

*Map and array functions as relational operators over a table made of a
complex value's entries.*

## Motivation

Subfield pruning reads only the parts of a complex column a query touches:
`m['k'].x` should fetch one key and one field rather than the whole map. That
requires knowing, for every function standing between the column and the
access, how an access on the result maps back to the arguments.

The functions that stand there are already relational operators over the
value's entries. `map_filter` keeps the entries matching a predicate — a
Filter. `transform_values` rewrites each entry's value — a Project.
`cardinality` counts them. Read a map as a two-column table of its entries and
the vocabulary needed is one the optimizer already has.

Presto describes each function's subfield behavior with a per-function
descriptor: a lambda-binding record, a "result subfields come from argument
*n*" flag, and a bespoke matcher for constant keys. Those three shapes look
like special cases of something more general.

`element_at(transform_values(m, f), k)` reaches one key because a filter on the
key can move below a projection. Presto encodes that single instance as the
`subfieldArg` flag. If map and array functions are relational operators, it is
not a flag but an instance of pushing Filter below Project.

## The model

Each complex value is a table:

| Type | Table | Constraints |
|---|---|---|
| `ARRAY(T)` | `(ord BIGINT, e T)` | `ord` contiguous from 1, defines order |
| `MAP(K,V)` | `(k K, v V)` | `k` unique, no order |
| `ROW(a, b, ...)` | one row, columns `a`, `b`, ... | exactly one row |

`ROW` is the weak member. The only operators over it are Project and
construct — there is no Filter, no Union, and `count(*)` is always 1 — so
treating it as a table buys consistent notation rather than reach.

The tables are lateral: one exists per row of the enclosing table, and a
function over it is evaluated once per outer row.

**Order.** Arrays are ordered bags and maps are unordered, so operators divide
into those that preserve the position correspondence between input and output
and those that do not. `slice` preserves it; `array_sort` and array `filter`
do not, since a given output position may originate from any input position.

`map_keys` and `map_values` are barriers for a different reason: their input
is a map, which has no order, so there is no input position for an output
position to correspond to. A bound on `map_values(m)` therefore says nothing
about which entries of `m` are needed.

### Where a table comes from

A mini-table has two possible origins, and the model does not distinguish them.

**A stored value.** `t.int_map` yields its table by reading the column.

**An operator.** `map_agg(k, v)` yields one by aggregating real rows, running
the model in reverse — relational to nested. A constant subscript on its
result, `map_agg(k, v)[42]`, is still a Filter on `k` of the mini-table; that
Filter simply lands on the aggregate's input rows rather than on a column read.

Constructors such as `map`, `array`, and `map_from_entries` are the degenerate
operator case, building the table from their arguments.

The same reading therefore covers both "which parts of a stored value are
needed" and "which rows need to reach an aggregate".

## Catalog

A function earns a place here only if its reading can make some access
narrower — if it contributes to required-columns or to a key domain. Functions
that compare whole elements contribute to neither: `array_intersect`,
`array_union`, `array_except`, `array_distinct`, and comparator-less
`array_sort` all require equality over entire elements, so their inputs are
fully required regardless of what the result feeds. They are modelable and
worthless, and are left out. `array_sort` with a comparator lambda does
qualify, since the comparator names the fields it reads.

A second kind of exclusion is category rather than value. `arbitrary(m)` is an
aggregate over the enclosing relation that passes a complex value through
unchanged; it never reads inside the value, so it is plan-structure
propagation and not a mini-table operator at all.

A third kind is simply absence. The model does not aim to cover every
function; one that goes undescribed is opaque, poisons its scope, and is
correct while doing so.

| Function | Operator | Notes |
|---|---|---|
| `map_filter`, `filter` | Filter | |
| `map_remove_null_values` | Filter `v IS NOT NULL` | |
| `map_subset` | Filter `k IN (...)` | |
| `transform`, `transform_keys`, `transform_values` | Project | |
| `map_keys`, `map_values` | Project one column | array order is unspecified, so none need be chosen |
| `cardinality` | `count(*)` | |
| `element_at`, `m[k]`, `a[i]` | Filter to one row, then scalar | relies on key uniqueness; null-versus-throw on a missing key is an assertion neither analysis consults |
| `array_sort` with a comparator | Sort | |
| `slice` | Filter on `ord` range | |
| `concat`, `flatten` | Union all, with `ord` offset | |
| `map_concat` | Union with last-wins on `k` | the conflict rule defines the operator, it does not qualify the reading |
| `zip_with`, `zip` | Full outer join on `ord` | |
| `map_zip_with` | Full outer join on `k` | |
| `contains` | `x IN (SELECT e ...)` | `IN` is three-valued, so no null rule is needed alongside |
| `any_match`, `all_match`, `none_match` | `IN` over the projected predicate | `any_match(a, p)` is `TRUE IN (SELECT p(e) FROM a)` |
| `array_agg`, `map_agg` | Aggregate, producing the table | |
| `make_row_from_map`, `padded_make_row_from_map` | Row constructor over one `element_at` per key | see below |
| `s.a` (dereference) | Project one column | |
| `row(...)` | Construct the one-row table | a projected column maps to the argument that supplied it |
| `map`, `array`, `map_from_entries` | Construct the table | |
| `reduce` | none | an ordered fold is an aggregate only if the combiner is associative and commutative, which nothing guarantees |

### Dialect functions outside Presto

The catalog is not Presto-shaped. Koski's `make_row_from_map(m,
make_array(1, 2), make_array('a', 'b'))` returns `ROW<a, b>` and needs no new
operator: it is a row constructor over one `element_at` per key, which is
`row(m[1], m[2])` with the field names supplied by the third argument. Both
pieces are already in the catalog.

A path `.a.x` on the result therefore resolves the way any constructor
dereference does — to argument 0, which is `m[1]`, and then to field `x`. The
key domain is the constant array. `padded_make_row_from_map` differs only in
what fills an absent key, which `element_at` already yields as null.

Koski's implementation declines to push down when a column feeds two such
calls. Read as two constructors over one mini-table, the union of their key
sets is what must be read, so the model covers a case the hand-written rule
gives up on.

## What a declaration must state

Which operator a function denotes is semantics and cannot be inferred from a
signature: two functions with identical signatures may differ. The model
therefore replaces three declaration shapes with one.

A declaration names the arguments that become scopes, the operator, how a
lambda's parameters bind to a scope's columns (`ord`/`e`, or `k`/`v`), and
which scope the result corresponds to.

Declaring the operator also settles how the function reaches the scope: a
Project's only access is its expression, a Filter's is its predicate. Presto
needs a separate `isAccessingInputValues()` claim because its descriptors
record a lambda binding without an operator to bound it.

## Rewrites the model makes expressible

A model earns its keep by what it makes expressible, so this list doubles as a
test of it.

The first group are not rewrites anything performs. They are propagation
rules the analysis needs in order to see through composition — pushing a key
domain into `transform_values`' argument, not rebuilding the expression. A
rule is needed only where something moves or combines; a composition in which
every operator applies its own rule in place, such as
`cardinality(map_filter(...))` or nested `transform`, needs none.

There are two such rules, both ordinary pushdown applied one scope down.

**Key-domain pushdown.** A domain established above an operator moves to its
inputs, and what each operator does with it is the operator's own rule:

| Operator | Behavior | Example |
|---|---|---|
| Project | into the lambda's scope | `element_at(transform_values(m, f), k)` reaches one key, subsuming `subfieldArg` |
| Filter | intersect with the filter's own domain | `map_filter(map_filter(m, P), Q)` gives `P AND Q` |
| Union | to every input | `map_concat(m1, m2)[k]` needs `k` from both |
| Join | to both sides | `map_zip_with(m1, m2, f)[k]` needs `k` from both |

**Bound propagation.** An array bound moves only through operators that
preserve position, which transform it — `slice(a, 1, 3)[2]` yields a bound of
3. Every other operator drops it, so `array_sort(a)[1]` leaves the bound
unrestricted. Only this rule involves order; marking operators as barriers is
enough for it, and full ordered-bag semantics would be needed only by a
rewrite that reorders operators.

A few are worth materializing as plan changes, because they remove work rather
than narrowing a read:

| Rewrite | Example | Effect |
|---|---|---|
| Empty domain eliminates the read | `map_filter(m, (k,v) -> k = 1 AND k = 2)` | domain is empty, so the column is not read |
| Aggregate over a constructor | `cardinality(array[a, b, c])` | 3, and `a`, `b`, `c` go unreferenced |
| Filter into an aggregate's input | `map_agg(k, v)[42]` | rows eliminated upstream |

The second entry is not constant folding: `a`, `b`, `c` need not be constants,
and what is statically known is the constructed table's row count, taken from
the constructor's arity. For a map constructor it holds only when the keys are
distinct.

The second table is where the model reaches past subfield pruning. The last
entry narrows no complex value at all: it turns a subscript into an ordinary
predicate on the aggregate's input, which then travels by normal filter
pushdown and may reach a scan, where partition and row-group pruning apply. A
subscript on an aggregated map can therefore eliminate files.
