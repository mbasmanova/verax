-- Shared table 't' used by the .sql test files.
-- Three INSERT statements produce three TestConnector splits.

CREATE TABLE t (a BIGINT, b BIGINT, c DOUBLE)
----
INSERT INTO t VALUES
  (1, 10, 1.5),
  (2, 20, 2.5),
  (3, 30, 3.5),
  (1, 40, 4.5),
  (2, 50, 5.5)
----
INSERT INTO t VALUES
  (3, 60, 6.5),
  (1, 70, 7.5),
  (2, 80, 8.5),
  (3, 90, 9.5),
  (1, 100, 10.5)
----
INSERT INTO t VALUES
  (2, 110, 11.5),
  (3, 120, 12.5),
  (1, 130, 13.5),
  (2, 140, 14.5),
  (3, 150, 15.5)
