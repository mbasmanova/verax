# Presto SQL Extensions

Axiom extends Presto SQL with several features not available in Presto Java.
These are Axiom-specific syntax additions that go beyond the standard Presto
SQL dialect.

## Named ROW Constructor

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
