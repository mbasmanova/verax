-- setup_file: graph_setup.sql

-- define graph
GRAPH g AS (
  VERTEX TABLES (
    person KEY (id) LABEL Person PROPERTIES (id, name),
    city KEY (code) LABEL City PROPERTIES (code, name, upper(name) AS upper_name),
    company KEY (id) LABEL Company PROPERTIES (id, name),
    office KEY (company, city) LABEL Office PROPERTIES (city))
  EDGE TABLES (
    knows KEY (src, dst)
      SOURCE KEY (src) REFERENCES person (id)
      DESTINATION KEY (dst) REFERENCES person (id)
      LABEL Knows,
    person AS lives_in KEY (id)
      SOURCE KEY (id) REFERENCES person (id)
      DESTINATION KEY (city) REFERENCES city (code)
      LABEL LivesIn PROPERTIES (city),
    works_at KEY (person)
      SOURCE KEY (person) REFERENCES person (id)
      DESTINATION KEY (company) REFERENCES company (id)
      LABEL WorksAt,
    works_in KEY (person)
      SOURCE KEY (person) REFERENCES person (id)
      DESTINATION KEY (company, city) REFERENCES office (company, city)
      LABEL WorksIn))
-- end_define

-- Who reaches whom in one or two Knows hops: one row per walk, so Carol
-- reaches Dave twice, directly and through Dave's edge to himself.
-- duckdb:
--   VALUES
--     ('Alice', 'Bob'),
--     ('Bob', 'Alice'),
--     ('Bob', 'Carol'),
--     ('Carol', 'Dave'),
--     ('Dave', 'Dave'),
--     ('Alice', 'Alice'),
--     ('Alice', 'Carol'),
--     ('Bob', 'Bob'),
--     ('Bob', 'Dave'),
--     ('Carol', 'Dave'),
--     ('Dave', 'Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[IS Knows]->{1,2} (b IS Person)
  COLUMNS (a.name AS a, b.name AS b))
----
-- Whom Alice reaches in two or three hops.
-- duckdb: VALUES ('Alice'), ('Carol'), ('Bob'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice') -[IS Knows]->{2,3} (b IS Person)
  COLUMNS (b.name AS b))
----
-- Whom Alice reaches in up to three hops over edges since 2010: each hop
-- satisfies the edge pattern's condition, so Dave's edge to himself is never
-- taken.
-- duckdb: VALUES ('Bob'), ('Alice'), ('Carol'), ('Bob'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice')
    -[k IS Knows WHERE k.since >= 2010]->{1,3} (b IS Person)
  COLUMNS (b.name AS b))
----
-- Who gets back to themselves in one to three hops.
-- duckdb: VALUES ('Dave'), ('Alice'), ('Bob'), ('Dave'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[IS Knows]->{1,3} (a)
  COLUMNS (a.name AS a))
----
-- Whom Alice reaches in zero to two hops: a walk of zero hops ends where it
-- starts.
-- duckdb: VALUES ('Alice'), ('Bob'), ('Alice'), ('Carol')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice') -[IS Knows]->{0,2} (b IS Person)
  COLUMNS (b.name AS b))
----
-- Whom Alice reaches in zero or one hop.
-- duckdb: VALUES ('Alice'), ('Bob')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice') -[IS Knows]->{0,1} (b IS Person)
  COLUMNS (b.name AS b))
----
-- A walk of zero hops matches only Alice's own row: company 1 shares her key
-- but is a different vertex.
-- duckdb: VALUES ('Alice'), ('Acme')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice') -[IS WorksAt]->{0,1} (b)
  COLUMNS (b.name AS b))
----
-- Who gets back to themselves in zero to two hops: everyone in zero.
-- duckdb: VALUES ('Alice'), ('Bob'), ('Carol'), ('Dave'), ('Dave'), ('Alice'), ('Bob'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[IS Knows]->{0,2} (a)
  COLUMNS (a.name AS a))
----
-- A repetition of zero hops only.
-- duckdb: VALUES ('Carol')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Carol') -[IS Knows]->{0,0} (b IS Person)
  COLUMNS (b.name AS b))
----
-- Who reaches Dave in one or two hops: a left-pointing repeated edge walks
-- from the vertex on its right.
-- duckdb: VALUES ('Carol'), ('Dave'), ('Bob'), ('Carol'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (b IS Person WHERE b.name = 'Dave') <-[IS Knows]-{1,2} (a IS Person)
  COLUMNS (a.name AS a))
----
-- Whom Carol reaches in exactly two hops in either direction. Alice and Bob
-- know each other through two edges, and Dave's edge to himself counts once.
-- duckdb: VALUES ('Alice'), ('Alice'), ('Carol'), ('Carol'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Carol') -[IS Knows]-{2,2} (b IS Person)
  COLUMNS (b.name AS b))
----
-- Who reaches Dave in one or two hops: the end has fewer rows than the start,
-- so the walk leaves from Dave and reads each hop backwards.
-- duckdb: VALUES ('Carol'), ('Dave'), ('Bob'), ('Carol'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[IS Knows]->{1,2} (b IS Person WHERE b.name = 'Dave')
  COLUMNS (a.name AS a))
----
-- Whom people living in Rome reach in one or two hops: the walk leaves from a
-- vertex that also joins another edge.
-- duckdb: VALUES ('Bob', 'Alice'), ('Bob', 'Carol'), ('Bob', 'Bob'), ('Bob', 'Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (c IS City WHERE c.name = 'Rome') <-[IS LivesIn]- (a IS Person)
    -[IS Knows]->{1,2} (b IS Person)
  COLUMNS (a.name AS a, b.name AS b))
----
-- Whom Alice reaches in one or two hops over Knows or WorksAt edges. Company 1
-- and person 1 share a key, so the walk follows the table along with the key:
-- it stops at Acme rather than continuing along Alice's own edges.
-- duckdb: VALUES ('Bob'), ('Acme'), ('Alice'), ('Carol')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice') -[IS Knows | WorksAt]->{1,2} (b)
  COLUMNS (b.name AS b))
----
-- Two repeated edges in one path: whom Alice reaches in one or two hops, then
-- in exactly two more.
-- duckdb: VALUES ('Bob'), ('Dave'), ('Alice'), ('Carol'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice') -[IS Knows]->{1,2} (b IS Person)
    -[IS Knows]->{2,2} (c IS Person)
  COLUMNS (c.name AS c))
----
-- Whom Alice reaches in one to three hops, each to a person with a larger id:
-- a repeated subpath's condition reads both ends of each hop.
-- duckdb: VALUES ('Bob'), ('Carol'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice')
    ((x IS Person) -[IS Knows]-> (y IS Person) WHERE x.id < y.id){1,3}
    (b IS Person)
  COLUMNS (b.name AS b))
----
-- Alice's colleagues and their colleagues: each repetition goes through a
-- company two people work at.
-- duckdb: VALUES ('Alice'), ('Carol'), ('Alice'), ('Carol'), ('Alice'), ('Carol')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice')
    ((x) -[IS WorksAt]-> (IS Company) <-[IS WorksAt]- (y)){1,2} (b)
  COLUMNS (b.name AS b))
----
-- A repeated subpath matched zero times ends where it starts.
-- duckdb: VALUES ('Bob'), ('Carol'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Bob')
    ((x) -[IS Knows]-> (y) WHERE x.id < y.id){0,2} (b)
  COLUMNS (b.name AS b))
----
-- A name inside a repeated subpath stands for one value per repetition
-- outside it.
-- error: Reading a repeated graph pattern outside its own pattern is not supported yet: y
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) ((x) -[IS Knows]-> (y)){1,2} (b)
  COLUMNS (y.name))
----
-- Whom Alice reaches in one or two Knows hops, and through whom: an optional
-- subpath matched zero times leaves its names NULL.
-- duckdb: VALUES ('Bob', CAST(NULL AS VARCHAR)), ('Alice', 'Bob'), ('Carol', 'Bob')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice')
    ((x IS Person) -[IS Knows]-> (m IS Person))? (v IS Person)
    -[IS Knows]-> (b IS Person)
  COLUMNS (b.name AS reached, m.name AS via))
----
-- The optional subpath's condition limits only the match of one hop: Alice's
-- one Knows edge is from 2010.
-- duckdb: VALUES ('Bob', CAST(NULL AS VARCHAR))
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice')
    ((x IS Person) -[k IS Knows]-> (m IS Person) WHERE k.since > 2012)?
    (v IS Person) -[IS Knows]-> (b IS Person)
  COLUMNS (b.name AS reached, m.name AS via))
----
-- A condition on an optional name outside the subpath keeps only the matches
-- of one hop, since the name is NULL in the others.
-- duckdb: VALUES ('Alice', 'Bob'), ('Carol', 'Bob')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Alice')
    ((x IS Person) -[IS Knows]-> (m IS Person))? (v IS Person)
    -[IS Knows]-> (b IS Person)
  WHERE m.name = 'Bob'
  COLUMNS (b.name AS reached, m.name AS via))
----
-- Dave knows himself, so both matches exist: zero hops and one.
-- duckdb: VALUES ('Dave', CAST(NULL AS VARCHAR)), ('Dave', 'Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Dave')
    ((x IS Person) -[IS Knows]-> (m IS Person))? (v IS Person)
    -[IS Knows]-> (b IS Person)
  COLUMNS (b.name AS reached, m.name AS via))
----
-- An optional subpath at the end of a path: Carol, and whom she knows.
-- duckdb: VALUES ('Carol'), ('Dave')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Carol')
    ((x IS Person) -[IS Knows]-> (y IS Person))? (b IS Person)
  COLUMNS (b.name AS b))
----
-- An optional subpath that can never match still leaves the match that skips
-- it.
-- duckdb: VALUES ('Carol')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Carol')
    ((x IS Person) -[IS Knows]-> (y IS Person) WHERE 1 = 0)? (b IS Person)
  COLUMNS (b.name AS b))
----
-- So does a repetition with a lower bound of zero.
-- duckdb: VALUES ('Carol')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Carol')
    ((x IS Person) -[IS Knows]-> (y IS Person) WHERE 1 = 0){0,2} (b IS Person)
  COLUMNS (b.name AS b))
----
-- WorksAt edges reach companies, so an optional subpath that reaches a person
-- over one never matches, and the match that skips it remains.
-- duckdb: VALUES ('Carol', CAST(NULL AS VARCHAR))
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Carol')
    ((x IS Person) -[IS WorksAt]-> (m IS Person))? (b IS Person)
  COLUMNS (b.name AS b, m.name AS via))
----
-- So does a repetition with a lower bound of zero.
-- duckdb: VALUES ('Carol')
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person WHERE a.name = 'Carol')
    ((x IS Person) -[IS WorksAt]-> (m IS Person)){0,2} (b IS Person)
  COLUMNS (b.name AS b))
----
-- error: Optional graph subpath pattern that starts or ends with an edge pattern is not supported yet
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) (-[IS WorksAt]-> (c IS Company))?
  COLUMNS (a.name AS a))
----
-- error: Optional graph subpath pattern that holds a repetition or an optional subpath is not supported yet
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person)
    ((x IS Person) -[IS Knows]->{1,2} (y IS Person))? (b IS Person)
  COLUMNS (b.name AS b))
----
-- error: Repeated graph subpath pattern that holds a repetition or an optional subpath is not supported yet
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person)
    ((x IS Person) ((y IS Person) -[IS Knows]-> (z IS Person))? (w IS Person)){1,2}
    (b IS Person)
  COLUMNS (b.name AS b))
----
-- A repeated edge pattern's name stands for one value per hop outside it.
-- error: Reading a repeated graph pattern outside its own pattern is not supported yet: k
WITH ${graph}
SELECT * FROM GRAPH_TABLE (g
  MATCH (a IS Person) -[k IS Knows]->{1,2} (b IS Person)
  COLUMNS (k.since))
