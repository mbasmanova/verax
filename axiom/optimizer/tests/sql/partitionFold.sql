-- connector: hive
-- setup
CREATE TABLE t (v BIGINT, ds VARCHAR) WITH (partitioned_by = ARRAY['ds'])
----
INSERT INTO t VALUES
  (1, '2025-01-01'),
  (2, '2025-01-02'),
  (3, '2025-01-02')
----
CREATE TABLE u (d VARCHAR)
----
INSERT INTO u VALUES ('2025-01-01'), ('2025-01-02'), ('2025-01-03')
-- end_setup

-- An aggregate reading only a partition column is answered from the listing.
SELECT max(ds) FROM t
----
SELECT max(ds), min(ds) FROM t
----
-- Each UNION ALL branch is answered on its own.
SELECT max(ds) AS m FROM t UNION ALL SELECT min(ds) AS m FROM t
----
-- count() counts rows, not partitions.
SELECT count(*) FROM t
----
-- An aggregation whose value is never read still produces its single row.
SELECT count(*) FROM (SELECT max(ds) FROM t)
----
-- The folded value restricts the outer scan.
SELECT v FROM t WHERE ds = (SELECT max(ds) FROM t)
----
-- A filter on a non-partition column is not answerable from the listing.
SELECT v FROM t WHERE ds = (SELECT max(ds) FROM t WHERE v > 1)
----
-- HAVING can reject the aggregate's row, leaving the subquery null, so
-- nothing matches.
-- count 0
SELECT v FROM t WHERE ds = (SELECT max(ds) FROM t HAVING max(ds) > '2030-01-01')
----
-- A correlated predicate reads a column the listing does not have.
SELECT d, (SELECT max(ds) FROM t WHERE t.ds > u.d) AS m FROM u
