-- setup_file: common_setup.sql

-- NULLIF tests.

-- NULLIF with non-deterministic expression. Result must contain only NULL and
-- false, never true.
-- duckdb: VALUES (null::boolean), (false)
SELECT DISTINCT nullif(rand() < 0.5, true) FROM unnest(sequence(1, 1000))
----
-- NULLIF with scalar subquery.
SELECT nullif((SELECT count(*) FROM t), 10)
