-- setup_file: common_setup.sql

-- A non-recursive CTE is not in scope within its own body, so a nested
-- same-name WITH resolves to the enclosing binding. These queries prove the
-- correctly-bound CTEs return the right values, not just that they parse.

-- Single-level shadowing. Inner body binds to outer t(a), main query to inner
-- t(b, c): a=1 -> b=1, c=2 -> r=3.
WITH t(a) AS (SELECT 1)
SELECT * FROM (
  WITH t(b, c) AS (SELECT a, a + 1 FROM t)
  SELECT b + c AS r FROM t) sub
----
-- Multi-level shadowing: inner reads mid's b, mid reads outer's a.
-- DuckDB rejects nested same-name CTEs as a circular reference, so the expected
-- result is supplied directly.
-- duckdb: SELECT 1 AS r
WITH t(a) AS (SELECT 1)
SELECT * FROM (
  WITH t(b) AS (SELECT a FROM t)
  SELECT * FROM (WITH t(c) AS (SELECT b FROM t) SELECT c AS r FROM t) s2) s1
----
-- A CTE body resolves names against its own FROM: `t.u` names the struct
-- column of `t`, not the same-named relation the referencing query reads.
WITH s AS (
  SELECT t.u.k AS k
  FROM (VALUES (CAST(ROW(1) AS ROW(k BIGINT)))) AS t(u)
)
SELECT u.b
FROM (VALUES (1, 'p'), (2, 'q')) AS u(k, b)
LEFT JOIN s ON u.k = s.k
----
-- A CTE body inside a correlated subquery still reads the correlated column.
WITH v AS (SELECT a, b FROM t)
SELECT a FROM v u
WHERE EXISTS (WITH w AS (SELECT b FROM t WHERE t.a = u.a) SELECT * FROM w)
