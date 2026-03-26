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
| Method-call syntax | `'hello'.upper().substr(1, 3)` |
| Lateral column aliases | `SELECT i+1 AS j, j+2 AS k` |

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

## Method-Call Syntax for Function Chaining

*Friendly SQL feature — requires `friendlySql` flag.*

Allows calling functions using dot notation, where the base expression becomes
the first argument: `expr.func(args...)` desugars to `func(expr, args...)`.

```sql
-- Basic method call.
SELECT 'hello'.upper()
-- Equivalent to: SELECT upper('hello')

-- With arguments.
SELECT 'hello'.substr(1, 3)
-- Equivalent to: SELECT substr('hello', 1, 3)

-- Chaining multiple calls (left-to-right).
SELECT 'hello'.trim().upper().substr(1, 3)
-- Equivalent to: SELECT substr(upper(trim('hello')), 1, 3)

-- Works with any non-identifier base expression.
SELECT (price * quantity).abs()
-- Equivalent to: SELECT abs(price * quantity)
```

The method-call syntax supports simple function calls only — no `DISTINCT`,
`ORDER BY`, `FILTER`, or `OVER` clauses. For those, use standard function call
syntax.

## Lateral Column Aliases

*Friendly SQL feature — requires `friendlySql` flag.*

Allows referencing aliases defined in earlier SELECT items within the same
SELECT list. The alias is expanded inline — semantically identical to writing
the expression out by hand.

```sql
-- Basic reuse.
SELECT price * quantity AS total, total * tax_rate AS tax FROM orders
-- Equivalent to: SELECT price * quantity AS total, (price * quantity) * tax_rate AS tax

-- Chaining.
SELECT a + 1 AS x, x + 2 AS y, y * 3 AS z FROM t
-- Equivalent to: SELECT a + 1 AS x, (a + 1) + 2 AS y, ((a + 1) + 2) * 3 AS z

-- With functions (combines with method-call syntax).
SELECT upper(name) AS u, u.substr(1, 3) AS abbrev FROM t
```

Rules:
- **Left-to-right only.** Forward references and self-references fail.
- **Columns take priority.** If a name is both a FROM column and an alias, the
  column wins (preserves backward compatibility).
- **SELECT list scope only.** Aliases are not expanded in GROUP BY, HAVING,
  WHERE, or ORDER BY.

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
