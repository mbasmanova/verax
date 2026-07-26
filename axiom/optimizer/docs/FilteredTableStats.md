# Connector-Level Filtered Table Statistics

## Motivation

Queries on large Hive-partitioned tables typically filter on partition keys
(`ds`, etc.) to access a few partitions out of thousands. The optimizer needs
accurate cardinality estimates for filtered tables to produce good join plans.

The optimizer estimates `filterSelectivity` via two mechanisms:

1. **Column statistics** (`conjunctsSelectivity`) -- uses NDV, min/max, null
   fraction from the connector's `ColumnStatistics`. Works when the connector
   provides per-column stats, but not all connectors do.
2. **Sampling** (`TableLayout::sample()`) -- reads actual data to measure what
   fraction of rows pass filters. Expensive when data is remote.

For connectors with access to partition-level metadata (e.g., Hive Metastore),
there is a better option: resolve which partitions match a filter and aggregate
their stats -- without touching any data.

## Contract: one accept/reject point

`createTableHandle` is the single point at which a connector decides which
filters it takes over. Whatever it accepts is encoded in the returned table
handle (in whatever representation the connector chooses -- Hive uses
`common::Filter` subfield filters plus a `TypedExpr` remaining filter); whatever
it rejects is reported by index into the input `filters` (in
`rejectedFilterIndices`) for the optimizer to apply.

From that point the connector owns its accepted filters end-to-end: it applies
them at scan time and estimates their effect in `co_estimateStats`. The
optimizer estimates only the filters `createTableHandle` rejected. There is no
separate filter argument to `co_estimateStats` and no notion of rejected filters
in its result.

## Connector API: `TableLayout::co_estimateStats`

Defined in `ConnectorMetadata.h`:

```cpp
struct FilteredTableStats {
  uint64_t numRows{0};
  std::vector<ColumnStatistics> columnStats;
};

virtual folly::coro::Task<std::optional<FilteredTableStats>> co_estimateStats(
    ConnectorSessionPtr session,
    velox::connector::ConnectorTableHandlePtr tableHandle,
    std::vector<std::string> columns,
    const FilterSelectivityEstimator& estimator) const;
```

The default implementation returns `std::nullopt`, meaning the connector does
not support stats estimation. Connectors opt in by overriding.

**Parameters:**
- `tableHandle` -- the connector reads its accepted filters from it, in whatever
  representation it stored them.
- `columns` -- names of table columns the optimizer is interested in. If the
  connector provides per-column statistics, it must return them for all
  requested columns in the same order (1:1), or return an empty `columnStats`
  vector if per-column stats are unavailable.
- `estimator` -- an optional shared helper (see below) for estimating filter
  selectivity and refined column statistics from column statistics. The
  connector may use it or estimate with its own logic.

**Return value:**
- `std::nullopt` -- connector does not support stats estimation; optimizer
  falls back to column-stats-based estimation and optional sampling.
- `FilteredTableStats` -- `numRows` is the estimated row count after applying
  the filters the connector accepted into the handle. `columnStats` maps 1:1 to
  `columns` (or is empty).

## `FilterSelectivityEstimator`

An optional helper offered to `co_estimateStats`, analogous to the
`ExpressionEvaluator` offered to a `DataSource`, so a connector need not
reimplement selectivity math. It has two entry points, keyed by column name:

- `estimate(std::vector<TypedExprPtr> filters, columnStats)` -- for filters the
  connector kept as `TypedExpr` (e.g. Hive's remaining filter).
- `estimate(F14FastMap<std::string, const common::Filter*> filters, columnStats)`
  -- for single-column filters the connector kept as `common::Filter` (e.g.
  Hive subfield filters).

Both return a `FilterEstimate { selectivity, columnStats }`: the fraction of
rows passing the filters and the refined per-column statistics of the surviving
rows. The default implementation, `StatsFilterSelectivityEstimator`, runs both
over the shared `SelectivityEngine` formula layer (range/IN/null selectivity and
constraint refinement in `SelectivityEngine.h`'s `detail` namespace), so the
two entry points and the optimizer's own `ExprCP` path share one implementation.
The estimator captures the optimizer's `QueryGraphContext` at construction and
restores it inside `estimate()` (under a lock) so a connector may call it from
another thread, e.g. its executor.

## Optimizer Integration

### Three-Pass `initializePlans`

`DerivedTable::initializePlans()` uses three passes over the DT tree to
separate filter pushdown from stats estimation, enabling batch async requests.

```
initializePlans():
  // Pass 1 (top-down): push filters down the entire DT tree.
  distributeAllConjuncts()

  // Pass 2 (batch): estimate stats for all base tables concurrently.
  estimateAllBaseTableSelectivity()

  // Pass 3 (bottom-up): finalize joins and build plans.
  finalizeJoinsAndMakePlans()
```

**Pass 2** (`Optimization::estimateAllBaseTableSelectivity`) collects all base
tables, prepares table handles via `ToVelox::filterUpdated`, constructs one
`StatsFilterSelectivityEstimator`, and launches all `co_estimateStats`
coroutines concurrently via `folly::coro::collectAllRange`, passing the
estimator. Gated by the `useFilteredTableStats` optimizer option
(default: true).

### Applying Connector Stats

`Optimization::applyFilteredStats` processes the connector response:

1. If `stats` is `std::nullopt`, falls back to `History::estimateLeafSelectivity`
   (column-stats-based estimation + optional sampling).
2. If column stats are present, applies them positionally to the base table's
   columns (NDV, min, max, null fraction).
3. Post-applies selectivity for the filters `createTableHandle` rejected, held
   as `ExprCP` in `LeafTableData::rejectedExprs`: when empty (the common Hive
   case, where the connector accepts everything), `filteredCardinality =
   numRows`; otherwise `conjunctsSelectivity` estimates the rejected subset and
   `filteredCardinality = numRows * selectivity`, plus the rejected filters'
   column constraints.

The v2 path (`EstimateLeafStatsPass` + `ScanHandle`) mirrors this.

### `ToVelox::LeafTableData` / `ScanHandle`

Per-leaf-table data stores:
- `handle` -- table handle with filters pushed into the connector.
- `extraFilters` -- filters rejected by `createTableHandle`, evaluated
  post-scan (execution).
- `rejectedExprs` -- the same `createTableHandle`-rejected filters as `ExprCP`,
  for the optimizer to post-apply selectivity. Built by mapping each rejected
  index back to the aligned `ExprCP` conjunct.

## Hive-family Implementation

`LocalHiveTableLayout::co_estimateStats` (and `PrismTableLayout`, which also
extends `HiveTableLayout`) reads the accepted filters from the `HiveTableHandle`
and estimates in two parts:

1. **Partition-key subfield filters** drive the base estimate. LocalHive matches
   them against per-partition metadata (row counts and column stats); Prism
   fetches matching-partition stats from the Metastore.
2. **The remaining accepted filters** -- non-partition single-column
   `common::Filter`s and the `TypedExpr` remaining filter -- are folded into the
   base estimate by the shared `HiveTableLayout::foldNonPartitionFilterStats`,
   which delegates to `connector::applyFilterEstimates`. That helper runs the
   provided `estimator` over the base column statistics, multiplies the
   selectivity into `numRows`, and overwrites the refined per-column fields.

`connector::applyFilterEstimates` is connector-agnostic (it takes column-name
-keyed filters plus an optional remaining `TypedExpr`), so a non-Hive connector
such as Impulse -- which has no partitions and reads its filters from an
`ImpulseTableHandle` -- reuses the same fold.

## Testing

- **`FiltersTest`** (`axiom/optimizer/tests/FiltersTest.cpp`): each filter case
  additionally lowers the same filters to `TypedExpr`, runs
  `StatsFilterSelectivityEstimator`, and asserts it agrees with the `ExprCP`
  `SelectivityEngine` on both selectivity and refined per-column statistics.
- **`FilteredTableStatsTest`**
  (`axiom/optimizer/tests/FilteredTableStatsTest.cpp`): end-to-end tests forcing
  the `co_estimateStats` path (`noFilter`, `dataFilter`, `partitionFilter`,
  `partitionAndDataFilter`).
