-- A recursive CTE produces one row per iteration until its step returns none.
WITH RECURSIVE r(n) AS (
  SELECT 1
  UNION ALL
  SELECT n + 1 FROM r WHERE n < 5
)
SELECT n FROM r
----
-- A step that returns no rows leaves only the anchor's rows.
WITH RECURSIVE r(n) AS (
  SELECT 1
  UNION ALL
  SELECT n + 1 FROM r WHERE false
)
SELECT n FROM r
----
-- A constant above a recursive CTE is computed for every iteration, rather
-- than reading the equal constant that produced the anchor row.
WITH RECURSIVE r(n) AS (
  SELECT 1
  UNION ALL
  SELECT n + 1 FROM r WHERE n < 3
)
SELECT n, 1 AS one FROM r
