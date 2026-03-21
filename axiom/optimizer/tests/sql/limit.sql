-- Table t(a BIGINT, b BIGINT) with 15 rows across 3 splits:
--   a |   b
--  ---+-----
--   1 |  10
--   2 |  20
--   3 |  30
--   1 |  40
--   2 |  50
--   3 |  60
--   1 |  70
--   2 |  80
--   3 |  90
--   1 | 100
--   2 | 110
--   3 | 120
--   1 | 130
--   2 | 140
--   3 | 150
--
-- ordered
SELECT a, b FROM t ORDER BY b LIMIT 3
----
-- count 0
SELECT a, b FROM t LIMIT 0
----
-- LIMIT ALL means "no limit" — returns all rows.
SELECT * FROM t LIMIT ALL
----
-- LIMIT 0 in CTE with self-join.
-- count 0
WITH final AS (SELECT a, SUM(b) AS total FROM t GROUP BY 1 LIMIT 0)
SELECT x.total FROM final x, final y WHERE x.a = y.a AND x.a = 1
