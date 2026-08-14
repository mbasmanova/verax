-- setup_file: common_setup.sql

-- Table t(a BIGINT, b BIGINT, c DOUBLE) with 15 rows across 3 splits:
--   a |   b |    c
--  ---+-----+------
--   1 |  10 |  1.5
--   2 |  20 |  2.5
--   3 |  30 |  3.5
--   1 |  40 |  4.5
--   2 |  50 |  5.5
--   3 |  60 |  6.5
--   1 |  70 |  7.5
--   2 |  80 |  8.5
--   3 |  90 |  9.5
--   1 | 100 | 10.5
--   2 | 110 | 11.5
--   3 | 120 | 12.5
--   1 | 130 | 13.5
--   2 | 140 | 14.5
--   3 | 150 | 15.5
--
-- ORDER BY queries.

-- ORDER BY an expression that is not in the select list.
-- ordered
SELECT * FROM t ORDER BY b + c DESC
----
-- ORDER BY an expression, descending on one key and ascending on another.
-- ordered
SELECT * FROM t ORDER BY a * -1 DESC, b + c ASC
----
-- ORDER BY a qualified key naming one side of a join, where both sides
-- contribute a column of that name.
-- ordered
SELECT y.v AS v
FROM (VALUES (1, 10), (2, 5)) x(k, v)
JOIN (VALUES (1, 200), (2, 300)) y(k, v) ON x.k = y.k
ORDER BY x.v DESC
----
-- SELECT DISTINCT ordered by a qualified key.
-- ordered
SELECT DISTINCT t.a FROM t ORDER BY t.a DESC
----
-- SELECT DISTINCT ordered by a qualified key naming one side of a join, where
-- both sides contribute a column of that name.
-- ordered
SELECT DISTINCT x.v AS xv, y.v AS yv
FROM (VALUES (1, 10), (2, 5), (1, 10)) x(k, v)
JOIN (VALUES (1, 200), (2, 300)) y(k, v) ON x.k = y.k
ORDER BY y.v DESC
----
-- SELECT DISTINCT with GROUP BY, ordered by a qualified key.
-- ordered
SELECT DISTINCT t.a, count(1) FROM t GROUP BY t.a ORDER BY t.a DESC
