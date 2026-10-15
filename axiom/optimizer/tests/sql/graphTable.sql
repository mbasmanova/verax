-- setup
-- People and who knows whom. Alice and Bob know each other, Bob knows Carol,
-- Carol knows Dave, and Dave knows himself. Alice and Carol live in Paris,
-- Bob lives in Rome, and Dave lives in New York, which is not a listed city.
CREATE TABLE person AS
SELECT * FROM (
  VALUES
    (1, 'Alice', 'PAR'),
    (2, 'Bob', 'ROM'),
    (3, 'Carol', 'PAR'),
    (4, 'Dave', 'NYC')
) AS t(id, name, city)
----
CREATE TABLE knows AS
SELECT * FROM (
  VALUES
    (1, 2, 2010),
    (2, 1, 2010),
    (2, 3, 2015),
    (3, 4, 2020),
    (4, 4, 2000)
) AS t(src, dst, since)
----
CREATE TABLE city AS
SELECT * FROM (
  VALUES
    ('PAR', 'Paris'),
    ('ROM', 'Rome')
) AS t(code, name)
-- end_setup

-- define graph
GRAPH g AS (
  VERTEX TABLES (
    person KEY (id) LABEL Person PROPERTIES (id, name),
    city KEY (code) LABEL City PROPERTIES (code, name, upper(name) AS upper_name))
  EDGE TABLES (
    knows KEY (src, dst)
      SOURCE KEY (src) REFERENCES person (id)
      DESTINATION KEY (dst) REFERENCES person (id)
      LABEL Knows,
    person AS lives_in KEY (id)
      SOURCE KEY (id) REFERENCES person (id)
      DESTINATION KEY (city) REFERENCES city (code)
      LABEL LivesIn PROPERTIES (city)))
-- end_define

-- Who knows whom, and since when.
-- duckdb:
--   VALUES
--     ('Alice', 'Bob', 2010),
--     ('Bob', 'Alice', 2010),
--     ('Bob', 'Carol', 2015),
--     ('Carol', 'Dave', 2020),
--     ('Dave', 'Dave', 2000)
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[k IS Knows]-> (b IS Person)
  COLUMNS (a.name AS a, b.name AS b, k.since))
----
-- Who is known by whom: a left-pointing edge leaves the vertex on its right.
-- duckdb:
--   VALUES
--     ('Alice', 'Bob'),
--     ('Bob', 'Alice'),
--     ('Bob', 'Carol'),
--     ('Carol', 'Dave'),
--     ('Dave', 'Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (b IS Person) <-[IS Knows]- (a IS Person)
  COLUMNS (a.name AS a, b.name AS b))
----
-- Whom people other than Alice have known since after 2010, among people
-- with a larger ID: a vertex predicate, an edge predicate, and a condition
-- across elements.
-- duckdb: VALUES ('Bob', 'Carol'), ('Carol', 'Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name <> 'Alice')
    -[k IS Knows WHERE k.since > 2010]-> (b IS Person)
  WHERE a.id < b.id
  COLUMNS (a.name AS a, b.name AS b))
----
-- Who knows someone who knows them back: a name that appears twice binds one
-- vertex. Dave's path follows his one edge twice.
-- duckdb: VALUES ('Alice', 'Bob', 2), ('Bob', 'Alice', 2), ('Dave', 'Dave', 2)
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH p = (a IS Person) -[IS Knows]-> (b IS Person) -[IS Knows]-> (a)
  COLUMNS (a.name AS a, b.name AS b, path_length(p) AS n))
----
-- Who knows whom through someone: paths that share a name join on it.
-- duckdb:
--   VALUES
--     ('Alice', 'Bob', 'Alice'),
--     ('Alice', 'Bob', 'Carol'),
--     ('Bob', 'Alice', 'Bob'),
--     ('Bob', 'Carol', 'Dave'),
--     ('Carol', 'Dave', 'Dave'),
--     ('Dave', 'Dave', 'Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[IS Knows]-> (b IS Person), (b) -[IS Knows]-> (c IS Person)
  COLUMNS (a.name AS a, b.name AS b, c.name AS c))
----
-- Who is a person and not a person: a label expression no table matches
-- matches nothing.
-- count 0
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH p = (a IS Person & !Person)
  COLUMNS (path_length(p) AS n))
----
-- Which cities there are: a path of one vertex. A property can be an
-- expression over its table's columns.
-- duckdb: VALUES ('PAR', 'PARIS'), ('ROM', 'ROME')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (c IS City)
  COLUMNS (c.code AS code, c.upper_name AS name))
----
-- Who lives where: an edge between vertices of different tables, backed by
-- the table of its source vertices. Dave's edge reaches no vertex, so it
-- matches nothing.
-- duckdb: VALUES ('Alice', 'Paris'), ('Bob', 'Rome'), ('Carol', 'Paris')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[IS LivesIn]-> (c IS City)
  COLUMNS (a.name AS person, c.name AS city))
----
-- Where people live, read from the city: a left-pointing edge reaches the
-- vertex on its left.
-- duckdb: VALUES ('Alice', 'Paris'), ('Bob', 'Rome'), ('Carol', 'Paris')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (c IS City) <-[IS LivesIn]- (a IS Person)
  COLUMNS (a.name AS person, c.name AS city))
----
-- Who lives in a person: an edge reaches only the vertex table it references.
-- count 0
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH p = (a IS Person) -[IS LivesIn]-> (b IS Person)
  COLUMNS (path_length(p) AS n))
----
-- Which city lives in a city: an edge matches only between the vertex tables
-- it connects.
-- count 0
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH p = (a IS City) -[IS LivesIn]-> (b IS City)
  COLUMNS (path_length(p) AS n))
----
-- Alice paired with every city: paths that share no name.
-- duckdb: VALUES ('Alice', 'Paris'), ('Alice', 'Rome')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice'), (c IS City)
  COLUMNS (a.name AS person, c.name AS city))
----
-- Who knows the same person as whom: two paths that meet at one vertex.
-- duckdb:
--   VALUES
--     ('Alice', 'Bob', 'Alice'),
--     ('Bob', 'Alice', 'Bob'),
--     ('Bob', 'Carol', 'Bob'),
--     ('Carol', 'Dave', 'Carol'),
--     ('Carol', 'Dave', 'Dave'),
--     ('Dave', 'Dave', 'Carol'),
--     ('Dave', 'Dave', 'Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[IS Knows]-> (b IS Person), (c IS Person) -[IS Knows]-> (b)
  COLUMNS (a.name AS a, b.name AS b, c.name AS c))
----
-- Which person who lives somewhere is also a city: a name that appears twice
-- matches only its first table.
-- count 0
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH p = (a IS Person) -[IS LivesIn]-> (c IS City), (a IS City)
  COLUMNS (path_length(p) AS n))
