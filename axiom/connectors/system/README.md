# System Connector

## Overview

The system connector provides read-only access to runtime metadata —
active queries, session properties, and other operational state. The
application registers it under a catalog name of its choice (the CLI
uses `system`).

## Schemas and Tables

### system.metadata

Configuration metadata, including session-scoped properties and function
signatures.

| Table | Description |
|-------|-------------|
| `session_properties` | All registered session properties with current values, defaults, and descriptions. |
| `functions` | All registered function signatures with types, arguments, and metadata. |

### system.runtime

Runtime state that changes as the server operates.

| Table | Description |
|-------|-------------|
| `queries` | One row per active or recent query with state, timing, resource usage, and split progress. |

## Usage

```sql
-- Show all session properties for a component.
SELECT name, current_value, default_value
FROM system.metadata.session_properties
WHERE component = 'optimizer';

-- Find overridden session properties.
SELECT component, name, current_value, default_value
FROM system.metadata.session_properties
WHERE current_value <> default_value;

-- Distinct function names by kind.
SELECT DISTINCT name FROM system.metadata.functions
WHERE kind = 'aggregate' ORDER BY 1;

-- Find functions that accept a variable number of arguments.
SELECT DISTINCT name FROM system.metadata.functions
WHERE is_variadic ORDER BY 1;

-- List all active queries.
SELECT query_id, state, query, elapsed_time_ms
FROM system.runtime.queries;
```

## Table Schemas

### system.metadata.session_properties

| Column | Type | Description |
|--------|------|-------------|
| `component` | VARCHAR | Namespace prefix (e.g. `optimizer`, `execution`, connector ID). |
| `name` | VARCHAR | Property name. |
| `type` | VARCHAR | Property type (BOOLEAN, INTEGER, DOUBLE, STRING). |
| `default_value` | VARCHAR | Default value (empty string if none). |
| `current_value` | VARCHAR | Current session value (reflects SET SESSION overrides). |
| `description` | VARCHAR | Human-readable description. |

### system.metadata.functions

| Column | Type | Description |
|--------|------|-------------|
| `name` | VARCHAR | Function name. |
| `kind` | VARCHAR | `scalar`, `aggregate`, or `window`. |
| `return_type` | VARCHAR | Return type signature (e.g. `bigint`, `array(T)`). |
| `argument_types` | ARRAY(VARCHAR) | Argument type signatures. |
| `is_variadic` | BOOLEAN | Whether the function accepts a variable number of arguments. |
| `owner` | VARCHAR | Responsible team (empty if not set). |
| `properties` | VARCHAR | Type-specific metadata as JSON (e.g. `{"deterministic": true}`). |

One row per function signature (overload).

<details>
<summary>system.runtime.queries (30 columns)</summary>

| Column | Type | Description |
|--------|------|-------------|
| `query_id` | VARCHAR | Unique query identifier. |
| `state` | VARCHAR | Current state (QUEUED, RUNNING, FINISHED, FAILED). |
| `query` | VARCHAR | SQL text. |
| `catalog` | VARCHAR | Default catalog. |
| `schema` | VARCHAR | Default schema. |
| `user` | VARCHAR | User who submitted the query. |
| `source` | VARCHAR | Client source identifier (nullable). |
| `query_type` | VARCHAR | Statement type (SELECT, INSERT, etc.). |
| `planning_time_ms` | BIGINT | Time spent in planning (ms). |
| `optimization_time_ms` | BIGINT | Time spent in optimization (ms). |
| `queue_time_ms` | BIGINT | Time spent in queue (ms). |
| `execution_time_ms` | BIGINT | Time spent in execution (ms). |
| `elapsed_time_ms` | BIGINT | Total wall-clock time (ms). |
| `cpu_time_ms` | BIGINT | Total CPU time (ms). |
| `wall_time_ms` | BIGINT | Total wall time (ms). |
| `total_splits` | BIGINT | Total number of splits. |
| `queued_splits` | BIGINT | Splits waiting to run. |
| `running_splits` | BIGINT | Splits currently executing. |
| `finished_splits` | BIGINT | Splits completed. |
| `output_rows` | BIGINT | Rows returned to client. |
| `output_bytes` | BIGINT | Bytes returned to client. |
| `processed_rows` | BIGINT | Rows read from storage. |
| `processed_bytes` | BIGINT | Bytes read from storage. |
| `written_rows` | BIGINT | Rows written (INSERT queries). |
| `written_bytes` | BIGINT | Bytes written (INSERT queries). |
| `peak_memory_bytes` | BIGINT | Peak memory usage. |
| `spilled_bytes` | BIGINT | Bytes spilled to disk. |
| `create_time` | TIMESTAMP | When the query was created. |
| `start_time` | TIMESTAMP | When execution started (nullable). |
| `end_time` | TIMESTAMP | When execution finished (nullable). |

</details>

## Architecture

The system connector has two layers:

- **Velox layer** (`SystemConnector`): implements the Velox `Connector`
  interface. Dispatches `createDataSource()` to the appropriate data
  source based on the table being scanned.

- **Axiom metadata layer** (`SystemConnectorMetadata`): implements the
  Axiom `ConnectorMetadata` interface. Provides table discovery, column
  handles, table handles, and split management.

Each system table has a corresponding data source class that knows how
to populate its columns. The data source reads from a **provider
interface** — `QueryInfoProvider` for the queries table,
`SessionPropertiesProvider` for session properties, and
`FunctionsProvider` for function metadata. These interfaces
decouple the connector from the rest of the system: the connector
defines what data it needs, and the application supplies it.

At registration time, the application creates provider implementations
and passes them to `SystemConnector`. For example, the CLI creates an
adapter that reads from `SessionConfig` and passes it as the
`SessionPropertiesProvider`:

```
Registration (startup):
  Application creates provider adapters
    → passes them to SystemConnector
    → creates SystemConnectorMetadata(connector)
    → registers both globally

Query time:
  SQL "SELECT ... FROM system.metadata.session_properties"
    → optimizer resolves table via SystemConnectorMetadata::findTable()
    → creates SystemTableHandle + SystemColumnHandles
    → runner calls SystemConnector::createDataSource()
    → connector dispatches to SessionPropertiesDataSource
    → data source calls SessionPropertiesProvider::getSessionProperties()
    → returns rows
```
