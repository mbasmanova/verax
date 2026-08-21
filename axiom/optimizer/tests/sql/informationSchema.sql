-- connector: hive
-- setup
CREATE TABLE t (a BIGINT, b VARCHAR, c DOUBLE, d DECIMAL(10, 2))
----
CREATE TABLE p (v BIGINT, k BIGINT) WITH (partitioned_by = ARRAY['k'])
-- end_setup

-- A catalog's tables and columns are described by information_schema, for
-- queries whose filters name the tables to describe.

-- The columns of a table, in declaration order.
-- ordered
-- duckdb: VALUES ('a', 'bigint', 1), ('b', 'varchar', 2), ('c', 'double', 3), ('d', 'decimal(10,2)', 4)
SELECT column_name, data_type, ordinal_position
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name = 't'
ORDER BY ordinal_position

----

-- Every column reports as nullable and carries no default or comment.
-- count 4
SELECT column_name
FROM information_schema.columns
WHERE table_schema = 'default'
  AND table_name = 't'
  AND is_nullable = 'YES'
  AND column_default IS NULL
  AND comment IS NULL

----

-- A numeric type reports the digits it holds, a decimal its declared
-- precision and scale, and a string type neither.
-- ordered
-- duckdb: VALUES ('a', 19, NULL), ('b', NULL, NULL), ('c', 53, NULL), ('d', 10, 2)
SELECT column_name, precision, scale
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name = 't'
ORDER BY ordinal_position

----

-- A column the table is partitioned by says so; the others say nothing.
-- ordered
-- duckdb: VALUES ('k', 'partition key'), ('v', NULL)
SELECT column_name, extra_info
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name = 'p'
ORDER BY column_name

----

-- A filter naming several schemas describes the tables of each it has.
-- duckdb: VALUES ('default')
SELECT DISTINCT table_schema
FROM information_schema.columns
WHERE table_schema IN ('default', 'absent') AND table_name = 't'

----

-- A filter naming several tables describes each of them.
-- count 6
SELECT column_name
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name IN ('t', 'p')

----

-- A name no table answers to contributes no rows.
-- count 0
SELECT column_name
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name = 'absent'

----

-- A table is reported as a base table.
-- duckdb: VALUES ('t', 'BASE TABLE')
SELECT table_name, table_type
FROM information_schema.tables
WHERE table_schema = 'default' AND table_name = 't'

----

-- A table is not a view, so views describes none of it.
-- count 0
SELECT table_name
FROM information_schema.views
WHERE table_schema = 'default' AND table_name = 't'

----

-- Counting selects no column of the relation.
-- duckdb: VALUES (4)
SELECT count(*)
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name = 't'

----

-- A filter on any other column narrows the rows the query returns.
-- duckdb: VALUES ('c')
SELECT column_name
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name = 't' AND data_type = 'double'

----

-- A query naming no schema describes no tables and fails.
-- error: requires a filter naming table_schema
SELECT column_name FROM information_schema.columns

----

-- Naming the schema alone leaves the tables to describe unbounded.
-- error: requires a filter naming table_name
SELECT table_name FROM information_schema.tables WHERE table_schema = 'default'

----

-- A pattern does not name the tables to describe.
-- error: requires a filter naming table_name
SELECT column_name
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name LIKE 't%'

----

-- Neither does a range.
-- error: requires a filter naming table_name
SELECT column_name
FROM information_schema.columns
WHERE table_schema = 'default' AND table_name > 't'
