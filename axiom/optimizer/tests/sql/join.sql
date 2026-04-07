-- JOIN with UNION ALL subquery.
SELECT t1.a, t1.b
FROM t t1 JOIN (SELECT a FROM t WHERE a = 1 UNION ALL SELECT a FROM t WHERE a = 2) t2 ON t1.a = t2.a

----
-- LEFT JOIN with cardinality(coalesce(...)) in WHERE clause.
-- duckdb: SELECT a, 2, NULL FROM t
WITH s AS (SELECT a, ARRAY[a, b] AS numbers FROM t),
r AS (SELECT a, ARRAY[a, b] AS numbers FROM t WHERE false)
SELECT s.a, cardinality(coalesce(r.numbers, s.numbers)), cardinality(r.numbers)
FROM s LEFT JOIN r ON s.a = r.a WHERE cardinality(coalesce(r.numbers, s.numbers)) > 0

----
-- LEFT JOIN with element_at(coalesce(...)) in WHERE clause.
-- duckdb: SELECT a, b FROM t
WITH s AS (SELECT a, ARRAY[a, b] AS numbers FROM t),
r AS (SELECT a, ARRAY[a, b] AS numbers FROM t WHERE false)
SELECT s.a, element_at(coalesce(r.numbers, s.numbers), 2)
FROM s LEFT JOIN r ON s.a = r.a WHERE element_at(coalesce(r.numbers, s.numbers), 1) > 0

----
-- LEFT-to-INNER JOIN conversion with aggregation. replaceJoinOutputs must not
-- replace post-aggregation references (exprs) with pre-aggregation expressions.
SELECT DISTINCT b.c
FROM t AS a
LEFT JOIN (
    SELECT a, CAST(c AS REAL) AS c FROM t
    CROSS JOIN UNNEST(ARRAY[1]) AS v(x)
) AS b ON a.a = b.a
WHERE b.a > 0
----
-- Two aliases of the same source column (v AS x, v AS y) from a LEFT JOIN.
-- Join output columns must not produce duplicates.
SELECT x, y
FROM (SELECT 1 AS k) AS a
LEFT JOIN (
    SELECT k, m, v AS x, v AS y
    FROM (SELECT 1 AS k, 1 AS m, 1 AS v)
) AS b ON a.k = b.k
----
-- Same join, with DISTINCT. The duplicate aliases must not produce duplicate
-- grouping keys in the aggregation.
SELECT DISTINCT b.x, b.y
FROM (SELECT 1 AS k) AS a
LEFT JOIN (
    SELECT k, m, v AS x, v AS y
    FROM (SELECT 1 AS k, 1 AS m, 1 AS v)
) AS b ON a.k = b.k
----
-- Same join, with DISTINCT and WHERE that converts LEFT to INNER. The
-- aggregation must not have duplicate grouping keys after join replacement.
SELECT DISTINCT b.x, b.y
FROM (SELECT 1 AS k) AS a
LEFT JOIN (
    SELECT k, m, v AS x, v AS y
    FROM (SELECT 1 AS k, 1 AS m, 1 AS v)
) AS b ON a.k = b.k
WHERE b.m = 1
