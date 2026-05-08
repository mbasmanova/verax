-- UNION ALL queries. Uses table t(a BIGINT, b BIGINT, c DOUBLE) with 15
-- rows across 3 splits (a in {1,2,3}). See sql/set.sql for the full data.
--
-- ROW subfield access in UNION ALL with positional subscript.
-- duckdb: VALUES (1), (3)
SELECT x[1] FROM (SELECT ROW(1, 2) AS x UNION ALL SELECT ROW(3, 4))
----
-- ROW subfield access in UNION ALL with named field.
-- duckdb: VALUES (1), (3)
SELECT x.a FROM (SELECT ROW(1 AS a, 2 AS b) AS x UNION ALL SELECT ROW(3 AS a, 4 AS b))
----
-- UNION ALL mixing EXCEPT (multi-task) with Values (single-task).
SELECT * FROM (SELECT a FROM t EXCEPT SELECT a FROM t WHERE a > 2) UNION ALL SELECT 42
----
-- UNION ALL mixing INTERSECT (multi-task, semi-join) with Values
-- (single-task). INTERSECT goes through a different code path than EXCEPT
-- (semi-join vs anti-join).
SELECT * FROM (
  SELECT a FROM t WHERE a <= 2
  INTERSECT
  SELECT a FROM t WHERE a = 1
) UNION ALL SELECT 42
----
-- UNION ALL with a multi-task input (EXCEPT) and multiple single-task
-- inputs. Exercises grouping of multiple kSingle legs into one wrap.
SELECT * FROM (
  SELECT a FROM t WHERE a <= 2
  EXCEPT
  SELECT a FROM t WHERE a = 1
) UNION ALL SELECT 42 UNION ALL SELECT 99
----
-- UNION ALL mixing DISTINCT subquery with scan.
SELECT * FROM (SELECT DISTINCT a FROM t) UNION ALL (SELECT a FROM t)
----
-- UNION ALL of DISTINCT (kFixed N) and Values (kSingle).
SELECT a FROM (
  SELECT DISTINCT a FROM t UNION ALL SELECT 42
)
----
-- UNION ALL of DISTINCT (kFixed N) and global aggregation (kSingle).
SELECT a FROM (
  SELECT DISTINCT a FROM t UNION ALL SELECT COUNT(*) AS a FROM t
)
----
-- UNION ALL of DISTINCT (kFixed N) and LIMIT (kSingle). LIMIT 3 without
-- ORDER BY is non-deterministic, so verify row count only.
-- 3 distinct + 3 from LIMIT = 6 rows total.
-- count 6
SELECT a FROM (
  SELECT DISTINCT a FROM t
  UNION ALL
  SELECT a FROM (SELECT a FROM t LIMIT 3)
)
----
-- ORDER BY over UNION ALL of scan + Values. Verifies the gather above the
-- union and the merging exchange feeding ORDER BY.
SELECT * FROM (
  SELECT a FROM t
  UNION ALL SELECT 42
) ORDER BY 1
