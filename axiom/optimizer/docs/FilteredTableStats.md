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

## Connector API: `TableLayout::co_estimateStats`

Defined in `ConnectorMetadata.h`:

```cpp
struct FilteredTableStats {
  uint64_t numRows{0};
  std::vector<ColumnStatistics> columnStats;
  std::vector<int32_t> rejectedFilterIndices;
};

virtual folly::coro::Task<std::optional<FilteredTableStats>> co_estimateStats(
    ConnectorSessionPtr session,
    velox::connector::ConnectorTableHandlePtr tableHandle,
    std::vector<std::string> columns,
    std::vector<velox::core::TypedExprPtr> filterConjuncts) const;
```

The default implementation returns `std::nullopt`, meaning the connector does
not support stats estimation. Connectors opt in by overriding.

**Parameters:**
- `columns` -- names of table columns the optimizer is interested in. If the
  connector provides per-column statistics, it must return them for all
  requested columns in the same order (1:1), or return an empty `columnStats`
  vector if per-column stats are unavailable.
- `filterConjuncts` -- filter conjuncts applied to the table. The connector
  reports indices of conjuncts it could not account for via
  `rejectedFilterIndices`.

**Return value:**
- `std::nullopt` -- connector does not support stats estimation; optimizer
  falls back to column-stats-based estimation and optional sampling.
- `FilteredTableStats` -- `numRows` is the estimated row count after applying
  filters the connector can evaluate. `columnStats` maps 1:1 to `columns`
  (or is empty). `rejectedFilterIndices` lists conjuncts the connector could
  not account for.

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

**Pass 1** walks the DT tree top-down, calling `distributeConjuncts()` on each
DT. No stats dependency.

**Pass 2** (`Optimization::estimateAllBaseTableSelectivity`) collects all base
tables from the DT tree, prepares table handles, launches all
`co_estimateStats` coroutines concurrently via
`folly::coro::collectAllRange`, waits once, then applies results. Gated by the
`useFilteredTableStats` optimizer option (default: true).

**Pass 3** walks bottom-up, calling `finalizeJoins()` and `makeInitialPlan()`
on each DT. `estimateLeafSelectivity()` is still called in this pass for base
tables in existence-pushdown DTs created by `finalizeJoins` ->
`pushExistencesIntoSubquery`. A dedup guard in `estimateLeafSelectivity`
prevents double-processing.

### Applying Connector Stats

`Optimization::applyFilteredStats` processes the connector response:

1. If `stats` is `std::nullopt`, falls back to `History::estimateLeafSelectivity`
   (column-stats-based estimation + optional sampling).
2. If column stats are present, applies them positionally to the base table's
   columns (NDV, min, max, null fraction).
3. If `rejectedFilterIndices` is empty, sets `filteredCardinality = numRows`.
4. Otherwise, maps rejected indices back to the original filter conjuncts,
   calls `conjunctsSelectivity` to estimate selectivity for the rejected
   subset, and sets `filteredCardinality = numRows * selectivity`. Column
   constraints from the rejected filters are also applied.

### Filter Conjunct Indexing

`filterConjuncts` passed to `co_estimateStats` are built from the base table's
`columnFilters` followed by `filter`, in that order. The same ordering is used
when mapping `rejectedFilterIndices` back to `ExprCP` objects.

### `ToVelox::LeafTableData`

`ToVelox` stores per-leaf-table data in `LeafTableData`:
- `handle` -- table handle with filters pushed into the connector.
- `extraFilters` -- filters rejected by `createTableHandle`, evaluated
  post-scan.
- `filterConjuncts` -- all filter conjuncts (columnFilters + filter) as
  `TypedExprPtr`, used by `co_estimateStats` so the connector can report
  rejected indices.

## LocalHive Implementation

`LocalHiveTableLayout::co_estimateStats` in `LocalHiveConnectorMetadata.cpp`
implements the API for the local Hive connector:

1. **Classify filter conjuncts** (`classifyFilterConjuncts`): converts each
   conjunct to `subfieldFilters` via `extractFiltersFromRemainingFilter`. If
   all subfields reference metadata-evaluable columns (partition keys, `$path`,
   `$bucket`) and no remainder expression is left, the conjunct is classified
   as a metadata filter. Otherwise, its index goes into
   `rejectedFilterIndices`.

2. **Filter files** by metadata: iterates over all files, testing each against
   all metadata filters. `testPartitionValue` handles type-specific conversion
   (BOOLEAN, TINYINT/SMALLINT/INTEGER/BIGINT, VARCHAR) and null testing.
   `testFileMetadata` handles `$path` and `$bucket` filters.

3. **Aggregate row counts**: sums `file->numRows` across selected files.

4. **Aggregate column stats** (`aggregateColumnStats`): for each requested
   column, computes min (minimum of per-file mins), max (maximum of per-file
   maxes), numValues (sum), nullPct, and estimated NDV. NDV estimation uses
   the coupon collector formula: `ndv * (1 - (1 - 1/ndv)^sampleRows)`.
   Skipped for Parquet format because `Reader::columnStatistics()` returns
   nullptr.

### Per-File Stats Collection

During `loadTable()`, per-file stats are populated from file header metadata:
- `FileInfo::numRows` from `reader->numberOfRows()`.
- `FileInfo::columnStats` maps column name to `ColumnStatistics` with
  `numValues`, `min`, `max` extracted via `reader->columnStatistics(nodeId)`.
  Node ID 0 is the root RowType; top-level columns use `i + 1`.
  Typed stats are extracted by dynamic_casting to
  `IntegerColumnStatistics`, `DoubleColumnStatistics`, or
  `StringColumnStatistics`.

## Testing

- **`FilteredTableStatsTest`** (`axiom/optimizer/tests/FilteredTableStatsTest.cpp`):
  end-to-end tests using DWRF format with `sampleFilters=false` to force the
  `co_estimateStats` path.
  - `noFilter` -- verifies base cardinality for an unpartitioned table.
  - `dataFilter` -- verifies range selectivity from per-file min/max.
  - `partitionFilter` -- verifies partition pruning (equality and IN list).
  - `partitionAndDataFilter` -- verifies combined partition pruning + data
    filter selectivity.
