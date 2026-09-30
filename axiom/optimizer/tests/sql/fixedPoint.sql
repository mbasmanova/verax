-- A recursive CTE produces one row per iteration until its step returns none.
WITH RECURSIVE r(n) AS (
  SELECT 1
  UNION ALL
  SELECT n + 1 FROM r WHERE n < 5
)
SELECT n FROM r
