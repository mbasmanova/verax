# Presto SQL Extensions

Axiom extends Presto SQL with several features not available in Presto Java.
These are Axiom-specific syntax additions that go beyond the standard Presto
SQL dialect.

## Friendly SQL

Some extensions are gated behind the `friendlySql` flag in `ParserOptions`.
These are inspired by [DuckDB's Friendly SQL](https://duckdb.org/docs/sql/dialect/friendly_sql)
and are enabled by default. To disable them, construct `PrestoParser` with
`ParserOptions{.friendlySql = false}`.

Friendly SQL features:

| Feature | Example |
|---------|---------|
| Named ROW constructor | `ROW(1 AS id, 'Alice' AS name)` |
| Trailing commas in SELECT | `SELECT a, b, FROM t` |
| FROM-first syntax | `FROM t WHERE x = 1` |
| Digit separators | `SELECT 1_000_000` |

## Named ROW Constructor

*Friendly SQL feature — requires `friendlySql` flag.*

See https://github.com/prestodb/presto/issues/26205.

Constructs a ROW value with named fields without requiring an explicit CAST.

**Syntax:**
```sql
ROW(expr1 AS name1, expr2 AS name2, ...)
```

**Equivalent Presto SQL:**
```sql
CAST(ROW(expr1, expr2, ...) AS ROW(name1 type1, name2 type2, ...))
```

Types are inferred from the expressions. All fields must be named — mixing
named and unnamed fields is not supported.

**Examples:**
```sql
-- Create a named ROW.
SELECT ROW(1 AS id, 'Alice' AS name)
-- Returns: {id=1, name=Alice}

-- Access fields by name.
SELECT a.id, a.name
FROM (SELECT ROW(1 AS id, 'Alice' AS name) AS a)
-- Returns: 1, Alice

-- Use with complex expressions.
SELECT ROW(count(*) AS total, max(price) AS max_price)
FROM orders
```

## Trailing Commas in SELECT

*Friendly SQL feature — requires `friendlySql` flag.*

Allows a trailing comma after the last item in a SELECT list.

```sql
SELECT
    n_nationkey,
    n_name,
    n_regionkey,
FROM nation
```

## FROM-First Syntax

*Friendly SQL feature — requires `friendlySql` flag.*

Allows queries to start with `FROM` instead of `SELECT`. An implicit
`SELECT *` is added.

```sql
-- Equivalent to: SELECT * FROM nation
FROM nation

-- With WHERE clause.
FROM nation WHERE n_regionkey = 1
```

## Underscores in Numeric Literals

*Friendly SQL feature — requires `friendlySql` flag.*

Allows underscores as digit separators in integer, decimal, and double
literals for readability.

```sql
SELECT 1_000_000
-- Returns: 1000000

SELECT 1_000.50
-- Returns: 1000.5

SELECT 1_000E3
-- Returns: 1000000.0
```

## EXCEPT ALL / INTERSECT ALL

Multiset versions of EXCEPT and INTERSECT that preserve duplicates.

**Syntax:**
```sql
query1 EXCEPT ALL query2
query1 INTERSECT ALL query2
```

Standard Presto supports only `EXCEPT` and `INTERSECT` (which are set
operations that deduplicate). `EXCEPT ALL` and `INTERSECT ALL` treat inputs as
multisets: a row that appears N times in the left and M times in the right
appears `max(N - M, 0)` times in `EXCEPT ALL` and `min(N, M)` times in
`INTERSECT ALL`.

## EXPLAIN (TYPE GRAPH)

Outputs the query plan as a graph representation.

**Syntax:**
```sql
EXPLAIN (TYPE GRAPH) query
```

## EXPLAIN (TYPE OPTIMIZED)

Outputs the optimized physical plan.

**Syntax:**
```sql
EXPLAIN (TYPE OPTIMIZED) query
```
