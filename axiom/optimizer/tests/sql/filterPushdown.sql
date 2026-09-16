-- The WHERE predicate removes the a = 0 row before the scalar-subquery
-- expression divides by a. The remaining a = 1 row satisfies HAVING.
WITH
t AS (SELECT * FROM (VALUES (0), (1)) AS _(a)),
u AS (SELECT * FROM (VALUES (10)) AS _(b))
SELECT (SELECT max(b) FROM u) / a AS pt
FROM t WHERE a <> 0 GROUP BY 1
HAVING (SELECT max(b) FROM u) / a > 1
----
-- The base-column predicate 1/a > 7 is pushed onto t, so it evaluates on the
-- a = 0 row before the join predicate can remove that row.
-- error: division by zero
WITH
t AS (SELECT * FROM (VALUES 0, 1) AS _(a)),
u AS (SELECT * FROM (VALUES 1, 2) AS _(b))
SELECT * FROM t, u WHERE a >= b AND 1/a > 7
----
-- Nested Boolean filters spanning both join inputs preserve branch
-- correlations.
WITH
t(k, a) AS (VALUES (1, 1), (2, 1), (3, 2), (4, 2), (5, 2), (6, 3)),
u(k, x, y) AS (
  VALUES
    (1, 10, 100),
    (2, 20, 200),
    (3, 30, 300),
    (4, 40, 400),
    (5, 30, 400),
    (6, 10, 100)
)
SELECT t.k
FROM t JOIN u ON t.k = u.k
WHERE
  (t.a = 1 AND ((u.x = 10 AND u.y = 100) OR (u.x = 20 AND u.y = 200)))
  OR
  (t.a = 2 AND ((u.x = 30 AND u.y = 300) OR (u.x = 40 AND u.y = 400)))
