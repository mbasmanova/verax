/*
 * Copyright (c) Meta Platforms, Inc. and its affiliates.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// Generated from PrestoSql.g4 by ANTLR 4.13.2

#include "PrestoSqlListener.h"
#include "PrestoSqlVisitor.h"

#include "PrestoSqlParser.h"

using namespace antlrcpp;

using namespace antlr4;

namespace {

struct PrestoSqlParserStaticData final {
  PrestoSqlParserStaticData(
      std::vector<std::string> ruleNames,
      std::vector<std::string> literalNames,
      std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)),
        literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  PrestoSqlParserStaticData(const PrestoSqlParserStaticData&) = delete;
  PrestoSqlParserStaticData(PrestoSqlParserStaticData&&) = delete;
  PrestoSqlParserStaticData& operator=(const PrestoSqlParserStaticData&) =
      delete;
  PrestoSqlParserStaticData& operator=(PrestoSqlParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag prestosqlParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
    std::unique_ptr<PrestoSqlParserStaticData>
        prestosqlParserStaticData = nullptr;

void prestosqlParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (prestosqlParserStaticData != nullptr) {
    return;
  }
#else
  assert(prestosqlParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<PrestoSqlParserStaticData>(
      std::vector<std::string>{
          "singleStatement",
          "standaloneExpression",
          "standaloneRoutineBody",
          "statement",
          "query",
          "with",
          "tableElement",
          "columnDefinition",
          "likeClause",
          "properties",
          "property",
          "sqlParameterDeclaration",
          "routineCharacteristics",
          "routineCharacteristic",
          "alterRoutineCharacteristics",
          "alterRoutineCharacteristic",
          "routineBody",
          "returnStatement",
          "externalBodyReference",
          "language",
          "determinism",
          "nullCallClause",
          "externalRoutineName",
          "queryNoWith",
          "queryTerm",
          "queryPrimary",
          "sortItem",
          "querySpecification",
          "groupBy",
          "groupingElement",
          "groupingSet",
          "namedQuery",
          "setQuantifier",
          "selectItem",
          "starModifiers",
          "excludeClause",
          "replaceClause",
          "replaceItem",
          "relation",
          "joinType",
          "joinCriteria",
          "sampledRelation",
          "sampleType",
          "aliasedRelation",
          "columnAliases",
          "relationPrimary",
          "expression",
          "booleanExpression",
          "predicate",
          "valueExpression",
          "primaryExpression",
          "string",
          "nullTreatment",
          "timeZoneSpecifier",
          "comparisonOperator",
          "comparisonQuantifier",
          "booleanValue",
          "interval",
          "intervalField",
          "normalForm",
          "types",
          "type",
          "typeParameter",
          "baseType",
          "whenClause",
          "filter",
          "over",
          "windowFrame",
          "frameBound",
          "updateAssignment",
          "explainOption",
          "transactionMode",
          "levelOfIsolation",
          "callArgument",
          "privilege",
          "qualifiedName",
          "tableVersionExpression",
          "tableVersionState",
          "grantor",
          "principal",
          "roles",
          "identifier",
          "number",
          "constraintSpecification",
          "namedConstraintSpecification",
          "unnamedConstraintSpecification",
          "constraintType",
          "constraintQualifiers",
          "constraintQualifier",
          "constraintRely",
          "constraintEnabled",
          "constraintEnforced",
          "nonReserved"},
      std::vector<std::string>{
          "",
          "'.'",
          "'('",
          "')'",
          "','",
          "'\\u003F'",
          "'->'",
          "'['",
          "']'",
          "'=>'",
          "",
          "'ADD'",
          "'ADMIN'",
          "'ALL'",
          "'ALTER'",
          "'ANALYZE'",
          "'AND'",
          "'ANY'",
          "'ARRAY'",
          "'AS'",
          "'ASC'",
          "'AT'",
          "'BEFORE'",
          "'BERNOULLI'",
          "'BETWEEN'",
          "'BY'",
          "'CALL'",
          "'CALLED'",
          "'CASCADE'",
          "'CASE'",
          "'CAST'",
          "'CATALOGS'",
          "'COLUMN'",
          "'COLUMNS'",
          "'COMMENT'",
          "'COMMIT'",
          "'COMMITTED'",
          "'CONSTRAINT'",
          "'CREATE'",
          "'CROSS'",
          "'CUBE'",
          "'CURRENT'",
          "'CURRENT_DATE'",
          "'CURRENT_ROLE'",
          "'CURRENT_TIME'",
          "'CURRENT_TIMESTAMP'",
          "'CURRENT_USER'",
          "'DATA'",
          "'DATE'",
          "'DAY'",
          "'DEALLOCATE'",
          "'DEFINER'",
          "'DELETE'",
          "'DESC'",
          "'DESCRIBE'",
          "'DETERMINISTIC'",
          "'DISABLED'",
          "'DISTINCT'",
          "'DISTRIBUTED'",
          "'DROP'",
          "'ELSE'",
          "'ENABLED'",
          "'END'",
          "'ENFORCED'",
          "'ESCAPE'",
          "'EXCEPT'",
          "'EXCLUDE'",
          "'EXCLUDING'",
          "'EXECUTABLE'",
          "'EXECUTE'",
          "'EXISTS'",
          "'EXPLAIN'",
          "'EXTRACT'",
          "'EXTERNAL'",
          "'FALSE'",
          "'FETCH'",
          "'FILTER'",
          "'FIRST'",
          "'FOLLOWING'",
          "'FOR'",
          "'FORMAT'",
          "'FROM'",
          "'FULL'",
          "'FUNCTION'",
          "'FUNCTIONS'",
          "'GRANT'",
          "'GRANTED'",
          "'GRANTS'",
          "'GRAPH'",
          "'GRAPHVIZ'",
          "'GROUP'",
          "'GROUPING'",
          "'GROUPS'",
          "'HAVING'",
          "'HOUR'",
          "'IF'",
          "'IGNORE'",
          "'IN'",
          "'INCLUDING'",
          "'INNER'",
          "'INPUT'",
          "'INSERT'",
          "'INTERSECT'",
          "'INTERVAL'",
          "'INTO'",
          "'INVOKER'",
          "'IO'",
          "'IS'",
          "'ISOLATION'",
          "'JSON'",
          "'JOIN'",
          "'KEY'",
          "'LANGUAGE'",
          "'LAST'",
          "'LATERAL'",
          "'LEFT'",
          "'LEVEL'",
          "'LIKE'",
          "'LIMIT'",
          "'LOCALTIME'",
          "'LOCALTIMESTAMP'",
          "'LOGICAL'",
          "'MAP'",
          "'MATERIALIZED'",
          "'MINUTE'",
          "'MONTH'",
          "'NAME'",
          "'NATURAL'",
          "'NFC'",
          "'NFD'",
          "'NFKC'",
          "'NFKD'",
          "'NO'",
          "'NONE'",
          "'NORMALIZE'",
          "'NOT'",
          "'NULL'",
          "'NULLIF'",
          "'NULLS'",
          "'OF'",
          "'OFFSET'",
          "'ON'",
          "'ONLY'",
          "'OPTIMIZED'",
          "'OPTION'",
          "'OR'",
          "'ORDER'",
          "'ORDINALITY'",
          "'OUTER'",
          "'OUTPUT'",
          "'OVER'",
          "'PARTITION'",
          "'PARTITIONS'",
          "'POSITION'",
          "'PRECEDING'",
          "'PREPARE'",
          "'PRIMARY'",
          "'PRIVILEGES'",
          "'PROPERTIES'",
          "'RANGE'",
          "'READ'",
          "'RECURSIVE'",
          "'REFRESH'",
          "'RELY'",
          "'RENAME'",
          "'REPEATABLE'",
          "'REPLACE'",
          "'RESET'",
          "'RESPECT'",
          "'RESTRICT'",
          "'RETURN'",
          "'RETURNS'",
          "'REVOKE'",
          "'RIGHT'",
          "'ROLE'",
          "'ROLES'",
          "'ROLLBACK'",
          "'ROLLUP'",
          "'ROW'",
          "'ROWS'",
          "'SCHEMA'",
          "'SCHEMAS'",
          "'SECOND'",
          "'SECURITY'",
          "'SELECT'",
          "'SERIALIZABLE'",
          "'SESSION'",
          "'SET'",
          "'SETS'",
          "'SHOW'",
          "'SOME'",
          "'SQL'",
          "'START'",
          "'STATS'",
          "'SUBSTRING'",
          "'SYSTEM'",
          "'SYSTEM_TIME'",
          "'SYSTEM_VERSION'",
          "'TABLE'",
          "'TABLES'",
          "'TABLESAMPLE'",
          "'TEMPORARY'",
          "'TEXT'",
          "'THEN'",
          "'TIME'",
          "'TIMESTAMP'",
          "'TO'",
          "'TRANSACTION'",
          "'TRUE'",
          "'TRUNCATE'",
          "'TRY_CAST'",
          "'TYPE'",
          "'UESCAPE'",
          "'UNBOUNDED'",
          "'UNCOMMITTED'",
          "'UNION'",
          "'UNIQUE'",
          "'UNNEST'",
          "'UPDATE'",
          "'USE'",
          "'USER'",
          "'USING'",
          "'VALIDATE'",
          "'VALUES'",
          "'VERBOSE'",
          "'VERSION'",
          "'VIEW'",
          "'WHEN'",
          "'WHERE'",
          "'WITH'",
          "'WORK'",
          "'WRITE'",
          "'YEAR'",
          "'ZONE'",
          "'='",
          "",
          "'<'",
          "'<='",
          "'>'",
          "'>='",
          "'+'",
          "'-'",
          "'*'",
          "'/'",
          "'%'",
          "'||'"},
      std::vector<std::string>{
          "",
          "",
          "",
          "",
          "",
          "",
          "",
          "",
          "",
          "",
          "ENGLISH_TOKEN",
          "ADD",
          "ADMIN",
          "ALL",
          "ALTER",
          "ANALYZE",
          "AND",
          "ANY",
          "ARRAY",
          "AS",
          "ASC",
          "AT",
          "BEFORE",
          "BERNOULLI",
          "BETWEEN",
          "BY",
          "CALL",
          "CALLED",
          "CASCADE",
          "CASE",
          "CAST",
          "CATALOGS",
          "COLUMN",
          "COLUMNS",
          "COMMENT",
          "COMMIT",
          "COMMITTED",
          "CONSTRAINT",
          "CREATE",
          "CROSS",
          "CUBE",
          "CURRENT",
          "CURRENT_DATE",
          "CURRENT_ROLE",
          "CURRENT_TIME",
          "CURRENT_TIMESTAMP",
          "CURRENT_USER",
          "DATA",
          "DATE",
          "DAY",
          "DEALLOCATE",
          "DEFINER",
          "DELETE",
          "DESC",
          "DESCRIBE",
          "DETERMINISTIC",
          "DISABLED",
          "DISTINCT",
          "DISTRIBUTED",
          "DROP",
          "ELSE",
          "ENABLED",
          "END",
          "ENFORCED",
          "ESCAPE",
          "EXCEPT",
          "EXCLUDE",
          "EXCLUDING",
          "EXECUTABLE",
          "EXECUTE",
          "EXISTS",
          "EXPLAIN",
          "EXTRACT",
          "EXTERNAL",
          "FALSE",
          "FETCH",
          "FILTER",
          "FIRST",
          "FOLLOWING",
          "FOR",
          "FORMAT",
          "FROM",
          "FULL",
          "FUNCTION",
          "FUNCTIONS",
          "GRANT",
          "GRANTED",
          "GRANTS",
          "GRAPH",
          "GRAPHVIZ",
          "GROUP",
          "GROUPING",
          "GROUPS",
          "HAVING",
          "HOUR",
          "IF",
          "IGNORE",
          "IN",
          "INCLUDING",
          "INNER",
          "INPUT",
          "INSERT",
          "INTERSECT",
          "INTERVAL",
          "INTO",
          "INVOKER",
          "IO",
          "IS",
          "ISOLATION",
          "JSON",
          "JOIN",
          "KEY",
          "LANGUAGE",
          "LAST",
          "LATERAL",
          "LEFT",
          "LEVEL",
          "LIKE",
          "LIMIT",
          "LOCALTIME",
          "LOCALTIMESTAMP",
          "LOGICAL",
          "MAP",
          "MATERIALIZED",
          "MINUTE",
          "MONTH",
          "NAME",
          "NATURAL",
          "NFC",
          "NFD",
          "NFKC",
          "NFKD",
          "NO",
          "NONE",
          "NORMALIZE",
          "NOT",
          "NULL_LITERAL",
          "NULLIF",
          "NULLS",
          "OF",
          "OFFSET",
          "ON",
          "ONLY",
          "OPTIMIZED",
          "OPTION",
          "OR",
          "ORDER",
          "ORDINALITY",
          "OUTER",
          "OUTPUT",
          "OVER",
          "PARTITION",
          "PARTITIONS",
          "POSITION",
          "PRECEDING",
          "PREPARE",
          "PRIMARY",
          "PRIVILEGES",
          "PROPERTIES",
          "RANGE",
          "READ",
          "RECURSIVE",
          "REFRESH",
          "RELY",
          "RENAME",
          "REPEATABLE",
          "REPLACE",
          "RESET",
          "RESPECT",
          "RESTRICT",
          "RETURN",
          "RETURNS",
          "REVOKE",
          "RIGHT",
          "ROLE",
          "ROLES",
          "ROLLBACK",
          "ROLLUP",
          "ROW",
          "ROWS",
          "SCHEMA",
          "SCHEMAS",
          "SECOND",
          "SECURITY",
          "SELECT",
          "SERIALIZABLE",
          "SESSION",
          "SET",
          "SETS",
          "SHOW",
          "SOME",
          "SQL",
          "START",
          "STATS",
          "SUBSTRING",
          "SYSTEM",
          "SYSTEM_TIME",
          "SYSTEM_VERSION",
          "TABLE",
          "TABLES",
          "TABLESAMPLE",
          "TEMPORARY",
          "TEXT",
          "THEN",
          "TIME",
          "TIMESTAMP",
          "TO",
          "TRANSACTION",
          "TRUE",
          "TRUNCATE",
          "TRY_CAST",
          "TYPE",
          "UESCAPE",
          "UNBOUNDED",
          "UNCOMMITTED",
          "UNION",
          "UNIQUE",
          "UNNEST",
          "UPDATE",
          "USE",
          "USER",
          "USING",
          "VALIDATE",
          "VALUES",
          "VERBOSE",
          "VERSION",
          "VIEW",
          "WHEN",
          "WHERE",
          "WITH",
          "WORK",
          "WRITE",
          "YEAR",
          "ZONE",
          "EQ",
          "NEQ",
          "LT",
          "LTE",
          "GT",
          "GTE",
          "PLUS",
          "MINUS",
          "ASTERISK",
          "SLASH",
          "PERCENT",
          "CONCAT",
          "STRING",
          "UNICODE_STRING",
          "BINARY_LITERAL",
          "INTEGER_VALUE",
          "DECIMAL_VALUE",
          "DOUBLE_VALUE",
          "IDENTIFIER",
          "DIGIT_IDENTIFIER",
          "QUOTED_IDENTIFIER",
          "BACKQUOTED_IDENTIFIER",
          "TIME_WITH_TIME_ZONE",
          "TIMESTAMP_WITH_TIME_ZONE",
          "DOUBLE_PRECISION",
          "SIMPLE_COMMENT",
          "BRACKETED_COMMENT",
          "WS",
          "UNRECOGNIZED",
          "DELIMITER"});
  static const int32_t serializedATNSegment[] = {
      4,    1,    263,  2187, 2,    0,    7,    0,    2,    1,    7,    1,
      2,    2,    7,    2,    2,    3,    7,    3,    2,    4,    7,    4,
      2,    5,    7,    5,    2,    6,    7,    6,    2,    7,    7,    7,
      2,    8,    7,    8,    2,    9,    7,    9,    2,    10,   7,    10,
      2,    11,   7,    11,   2,    12,   7,    12,   2,    13,   7,    13,
      2,    14,   7,    14,   2,    15,   7,    15,   2,    16,   7,    16,
      2,    17,   7,    17,   2,    18,   7,    18,   2,    19,   7,    19,
      2,    20,   7,    20,   2,    21,   7,    21,   2,    22,   7,    22,
      2,    23,   7,    23,   2,    24,   7,    24,   2,    25,   7,    25,
      2,    26,   7,    26,   2,    27,   7,    27,   2,    28,   7,    28,
      2,    29,   7,    29,   2,    30,   7,    30,   2,    31,   7,    31,
      2,    32,   7,    32,   2,    33,   7,    33,   2,    34,   7,    34,
      2,    35,   7,    35,   2,    36,   7,    36,   2,    37,   7,    37,
      2,    38,   7,    38,   2,    39,   7,    39,   2,    40,   7,    40,
      2,    41,   7,    41,   2,    42,   7,    42,   2,    43,   7,    43,
      2,    44,   7,    44,   2,    45,   7,    45,   2,    46,   7,    46,
      2,    47,   7,    47,   2,    48,   7,    48,   2,    49,   7,    49,
      2,    50,   7,    50,   2,    51,   7,    51,   2,    52,   7,    52,
      2,    53,   7,    53,   2,    54,   7,    54,   2,    55,   7,    55,
      2,    56,   7,    56,   2,    57,   7,    57,   2,    58,   7,    58,
      2,    59,   7,    59,   2,    60,   7,    60,   2,    61,   7,    61,
      2,    62,   7,    62,   2,    63,   7,    63,   2,    64,   7,    64,
      2,    65,   7,    65,   2,    66,   7,    66,   2,    67,   7,    67,
      2,    68,   7,    68,   2,    69,   7,    69,   2,    70,   7,    70,
      2,    71,   7,    71,   2,    72,   7,    72,   2,    73,   7,    73,
      2,    74,   7,    74,   2,    75,   7,    75,   2,    76,   7,    76,
      2,    77,   7,    77,   2,    78,   7,    78,   2,    79,   7,    79,
      2,    80,   7,    80,   2,    81,   7,    81,   2,    82,   7,    82,
      2,    83,   7,    83,   2,    84,   7,    84,   2,    85,   7,    85,
      2,    86,   7,    86,   2,    87,   7,    87,   2,    88,   7,    88,
      2,    89,   7,    89,   2,    90,   7,    90,   2,    91,   7,    91,
      2,    92,   7,    92,   1,    0,    1,    0,    1,    0,    1,    1,
      1,    1,    1,    1,    1,    2,    1,    2,    1,    2,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      3,    3,    209,  8,    3,    1,    3,    1,    3,    1,    3,    3,
      3,    214,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      3,    3,    220,  8,    3,    1,    3,    1,    3,    3,    3,    224,
      8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    3,    3,    238,  8,    3,    1,    3,    1,    3,    3,
      3,    242,  8,    3,    1,    3,    1,    3,    3,    3,    246,  8,
      3,    1,    3,    1,    3,    3,    3,    250,  8,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,    3,
      258,  8,    3,    1,    3,    1,    3,    3,    3,    262,  8,    3,
      1,    3,    3,    3,    265,  8,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    3,    3,    272,  8,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    5,    3,    279,  8,
      3,    10,   3,    12,   3,    282,  9,    3,    1,    3,    1,    3,
      1,    3,    3,    3,    287,  8,    3,    1,    3,    1,    3,    3,
      3,    291,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      3,    3,    297,  8,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    3,    3,    304,  8,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,    3,
      313,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    3,    3,    322,  8,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    3,    3,    333,  8,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    3,    3,    340,  8,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    3,    3,    350,  8,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    3,    3,    357,  8,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      3,    3,    365,  8,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    3,    3,    373,  8,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,    3,
      381,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    3,    3,    391,  8,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,    3,
      398,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    3,    3,    406,  8,    3,    1,    3,    1,    3,
      1,    3,    3,    3,    411,  8,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    3,    3,    422,  8,    3,    1,    3,    1,    3,    1,    3,
      3,    3,    427,  8,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,
      3,    438,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,    3,
      449,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    5,    3,    459,  8,    3,
      10,   3,    12,   3,    462,  9,    3,    1,    3,    1,    3,    1,
      3,    3,    3,    467,  8,    3,    1,    3,    1,    3,    1,    3,
      3,    3,    472,  8,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    3,    3,    478,  8,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    3,    3,    487,  8,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    3,    3,    498,  8,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    3,    3,    507,  8,    3,    1,    3,    1,    3,    1,
      3,    3,    3,    512,  8,    3,    1,    3,    1,    3,    3,    3,
      516,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    3,    3,    524,  8,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    3,    3,    531,  8,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    3,    3,    544,
      8,    3,    1,    3,    3,    3,    547,  8,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    5,    3,    555,
      8,    3,    10,   3,    12,   3,    558,  9,    3,    3,    3,    560,
      8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      3,    3,    567,  8,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    3,    3,    576,  8,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    3,    3,    582,  8,
      3,    1,    3,    1,    3,    1,    3,    3,    3,    587,  8,    3,
      1,    3,    1,    3,    3,    3,    591,  8,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    5,    3,    599,
      8,    3,    10,   3,    12,   3,    602,  9,    3,    3,    3,    604,
      8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    3,    3,    614,  8,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    5,    3,    625,  8,    3,    10,   3,
      12,   3,    628,  9,    3,    1,    3,    1,    3,    1,    3,    3,
      3,    633,  8,    3,    1,    3,    1,    3,    1,    3,    3,    3,
      638,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,
      3,    644,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    5,    3,    651,  8,    3,    10,   3,    12,   3,    654,
      9,    3,    1,    3,    1,    3,    1,    3,    3,    3,    659,  8,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,
      3,    666,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      5,    3,    672,  8,    3,    10,   3,    12,   3,    675,  9,    3,
      1,    3,    1,    3,    3,    3,    679,  8,    3,    1,    3,    1,
      3,    3,    3,    683,  8,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    3,    3,    691,  8,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    3,    3,    697,  8,    3,
      1,    3,    1,    3,    1,    3,    5,    3,    702,  8,    3,    10,
      3,    12,   3,    705,  9,    3,    1,    3,    1,    3,    3,    3,
      709,  8,    3,    1,    3,    1,    3,    3,    3,    713,  8,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    3,    3,    723,  8,    3,    1,    3,    3,
      3,    726,  8,    3,    1,    3,    1,    3,    3,    3,    730,  8,
      3,    1,    3,    3,    3,    733,  8,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    5,    3,    739,  8,    3,    10,   3,    12,
      3,    742,  9,    3,    1,    3,    1,    3,    3,    3,    746,  8,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    3,    3,    767,  8,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    3,    3,    773,  8,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    3,    3,    779,  8,    3,    3,    3,
      781,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,
      3,    787,  8,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      3,    3,    793,  8,    3,    3,    3,    795,  8,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    3,    3,
      803,  8,    3,    3,    3,    805,  8,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    3,    3,    824,  8,    3,    1,
      3,    1,    3,    1,    3,    3,    3,    829,  8,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    3,    3,    836,  8,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    3,    3,    848,
      8,    3,    3,    3,    850,  8,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    3,    3,    858,  8,    3,
      3,    3,    860,  8,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    5,    3,    876,
      8,    3,    10,   3,    12,   3,    879,  9,    3,    3,    3,    881,
      8,    3,    1,    3,    1,    3,    3,    3,    885,  8,    3,    1,
      3,    1,    3,    3,    3,    889,  8,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,
      5,    3,    905,  8,    3,    10,   3,    12,   3,    908,  9,    3,
      3,    3,    910,  8,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    1,    3,    1,    3,    1,    3,    1,
      3,    1,    3,    1,    3,    5,    3,    924,  8,    3,    10,   3,
      12,   3,    927,  9,    3,    1,    3,    1,    3,    3,    3,    931,
      8,    3,    3,    3,    933,  8,    3,    1,    4,    3,    4,    936,
      8,    4,    1,    4,    1,    4,    1,    5,    1,    5,    3,    5,
      942,  8,    5,    1,    5,    1,    5,    1,    5,    5,    5,    947,
      8,    5,    10,   5,    12,   5,    950,  9,    5,    1,    6,    1,
      6,    1,    6,    3,    6,    955,  8,    6,    1,    7,    1,    7,
      1,    7,    1,    7,    3,    7,    961,  8,    7,    1,    7,    1,
      7,    3,    7,    965,  8,    7,    1,    7,    1,    7,    3,    7,
      969,  8,    7,    1,    8,    1,    8,    1,    8,    1,    8,    3,
      8,    975,  8,    8,    1,    9,    1,    9,    1,    9,    1,    9,
      5,    9,    981,  8,    9,    10,   9,    12,   9,    984,  9,    9,
      1,    9,    1,    9,    1,    10,   1,    10,   1,    10,   1,    10,
      1,    11,   1,    11,   1,    11,   1,    12,   5,    12,   996,  8,
      12,   10,   12,   12,   12,   999,  9,    12,   1,    13,   1,    13,
      1,    13,   1,    13,   3,    13,   1005, 8,    13,   1,    14,   5,
      14,   1008, 8,    14,   10,   14,   12,   14,   1011, 9,    14,   1,
      15,   1,    15,   1,    16,   1,    16,   3,    16,   1017, 8,    16,
      1,    17,   1,    17,   1,    17,   1,    18,   1,    18,   1,    18,
      3,    18,   1025, 8,    18,   1,    19,   1,    19,   3,    19,   1029,
      8,    19,   1,    20,   1,    20,   1,    20,   3,    20,   1034, 8,
      20,   1,    21,   1,    21,   1,    21,   1,    21,   1,    21,   1,
      21,   1,    21,   1,    21,   1,    21,   3,    21,   1045, 8,    21,
      1,    22,   1,    22,   1,    23,   1,    23,   1,    23,   1,    23,
      1,    23,   1,    23,   5,    23,   1055, 8,    23,   10,   23,   12,
      23,   1058, 9,    23,   3,    23,   1060, 8,    23,   1,    23,   1,
      23,   1,    23,   3,    23,   1065, 8,    23,   3,    23,   1067, 8,
      23,   1,    23,   1,    23,   1,    23,   1,    23,   1,    23,   1,
      23,   1,    23,   3,    23,   1076, 8,    23,   3,    23,   1078, 8,
      23,   1,    24,   1,    24,   1,    24,   1,    24,   1,    24,   1,
      24,   3,    24,   1086, 8,    24,   1,    24,   1,    24,   1,    24,
      1,    24,   3,    24,   1092, 8,    24,   1,    24,   5,    24,   1095,
      8,    24,   10,   24,   12,   24,   1098, 9,    24,   1,    25,   1,
      25,   1,    25,   1,    25,   1,    25,   1,    25,   1,    25,   5,
      25,   1107, 8,    25,   10,   25,   12,   25,   1110, 9,    25,   1,
      25,   1,    25,   1,    25,   1,    25,   3,    25,   1116, 8,    25,
      1,    26,   1,    26,   3,    26,   1120, 8,    26,   1,    26,   1,
      26,   3,    26,   1124, 8,    26,   1,    27,   1,    27,   3,    27,
      1128, 8,    27,   1,    27,   1,    27,   1,    27,   5,    27,   1133,
      8,    27,   10,   27,   12,   27,   1136, 9,    27,   1,    27,   3,
      27,   1139, 8,    27,   1,    27,   1,    27,   1,    27,   1,    27,
      5,    27,   1145, 8,    27,   10,   27,   12,   27,   1148, 9,    27,
      3,    27,   1150, 8,    27,   1,    27,   1,    27,   3,    27,   1154,
      8,    27,   1,    27,   1,    27,   1,    27,   3,    27,   1159, 8,
      27,   1,    27,   1,    27,   3,    27,   1163, 8,    27,   1,    27,
      1,    27,   1,    27,   1,    27,   5,    27,   1169, 8,    27,   10,
      27,   12,   27,   1172, 9,    27,   1,    27,   1,    27,   3,    27,
      1176, 8,    27,   1,    27,   1,    27,   1,    27,   3,    27,   1181,
      8,    27,   1,    27,   1,    27,   3,    27,   1185, 8,    27,   3,
      27,   1187, 8,    27,   1,    28,   3,    28,   1190, 8,    28,   1,
      28,   1,    28,   1,    28,   5,    28,   1195, 8,    28,   10,   28,
      12,   28,   1198, 9,    28,   1,    29,   1,    29,   1,    29,   1,
      29,   1,    29,   1,    29,   5,    29,   1206, 8,    29,   10,   29,
      12,   29,   1209, 9,    29,   3,    29,   1211, 8,    29,   1,    29,
      1,    29,   1,    29,   1,    29,   1,    29,   1,    29,   5,    29,
      1219, 8,    29,   10,   29,   12,   29,   1222, 9,    29,   3,    29,
      1224, 8,    29,   1,    29,   1,    29,   1,    29,   1,    29,   1,
      29,   1,    29,   1,    29,   5,    29,   1233, 8,    29,   10,   29,
      12,   29,   1236, 9,    29,   1,    29,   1,    29,   3,    29,   1240,
      8,    29,   1,    30,   1,    30,   1,    30,   1,    30,   5,    30,
      1246, 8,    30,   10,   30,   12,   30,   1249, 9,    30,   3,    30,
      1251, 8,    30,   1,    30,   1,    30,   3,    30,   1255, 8,    30,
      1,    31,   1,    31,   3,    31,   1259, 8,    31,   1,    31,   1,
      31,   1,    31,   1,    31,   1,    31,   1,    32,   1,    32,   1,
      33,   1,    33,   1,    33,   1,    33,   3,    33,   1272, 8,    33,
      1,    33,   1,    33,   3,    33,   1276, 8,    33,   1,    33,   1,
      33,   1,    33,   1,    33,   1,    33,   1,    33,   1,    33,   3,
      33,   1285, 8,    33,   1,    33,   1,    33,   1,    33,   1,    33,
      1,    33,   3,    33,   1292, 8,    33,   1,    33,   1,    33,   3,
      33,   1296, 8,    33,   1,    33,   3,    33,   1299, 8,    33,   3,
      33,   1301, 8,    33,   1,    34,   1,    34,   4,    34,   1305, 8,
      34,   11,   34,   12,   34,   1306, 1,    35,   1,    35,   1,    35,
      1,    35,   1,    35,   5,    35,   1314, 8,    35,   10,   35,   12,
      35,   1317, 9,    35,   1,    35,   1,    35,   1,    36,   1,    36,
      1,    36,   1,    36,   1,    36,   5,    36,   1326, 8,    36,   10,
      36,   12,   36,   1329, 9,    36,   1,    36,   1,    36,   1,    37,
      1,    37,   1,    37,   1,    37,   1,    38,   1,    38,   1,    38,
      1,    38,   1,    38,   1,    38,   1,    38,   1,    38,   1,    38,
      1,    38,   1,    38,   1,    38,   1,    38,   1,    38,   1,    38,
      1,    38,   1,    38,   3,    38,   1354, 8,    38,   5,    38,   1356,
      8,    38,   10,   38,   12,   38,   1359, 9,    38,   1,    39,   3,
      39,   1362, 8,    39,   1,    39,   1,    39,   3,    39,   1366, 8,
      39,   1,    39,   1,    39,   3,    39,   1370, 8,    39,   1,    39,
      1,    39,   3,    39,   1374, 8,    39,   3,    39,   1376, 8,    39,
      1,    40,   1,    40,   1,    40,   1,    40,   1,    40,   1,    40,
      1,    40,   5,    40,   1385, 8,    40,   10,   40,   12,   40,   1388,
      9,    40,   1,    40,   1,    40,   3,    40,   1392, 8,    40,   1,
      41,   1,    41,   1,    41,   1,    41,   1,    41,   1,    41,   1,
      41,   3,    41,   1401, 8,    41,   1,    42,   1,    42,   1,    43,
      1,    43,   3,    43,   1407, 8,    43,   1,    43,   1,    43,   3,
      43,   1411, 8,    43,   3,    43,   1413, 8,    43,   1,    44,   1,
      44,   1,    44,   1,    44,   5,    44,   1419, 8,    44,   10,   44,
      12,   44,   1422, 9,    44,   1,    44,   1,    44,   1,    45,   1,
      45,   3,    45,   1428, 8,    45,   1,    45,   1,    45,   1,    45,
      1,    45,   1,    45,   1,    45,   1,    45,   1,    45,   1,    45,
      5,    45,   1439, 8,    45,   10,   45,   12,   45,   1442, 9,    45,
      1,    45,   1,    45,   1,    45,   3,    45,   1447, 8,    45,   1,
      45,   1,    45,   1,    45,   1,    45,   1,    45,   1,    45,   1,
      45,   1,    45,   1,    45,   3,    45,   1458, 8,    45,   1,    46,
      1,    46,   1,    47,   1,    47,   1,    47,   3,    47,   1465, 8,
      47,   1,    47,   1,    47,   3,    47,   1469, 8,    47,   1,    47,
      1,    47,   1,    47,   1,    47,   1,    47,   1,    47,   5,    47,
      1477, 8,    47,   10,   47,   12,   47,   1480, 9,    47,   1,    48,
      1,    48,   1,    48,   1,    48,   1,    48,   1,    48,   1,    48,
      1,    48,   1,    48,   1,    48,   3,    48,   1492, 8,    48,   1,
      48,   1,    48,   1,    48,   1,    48,   1,    48,   1,    48,   3,
      48,   1500, 8,    48,   1,    48,   1,    48,   1,    48,   1,    48,
      1,    48,   5,    48,   1507, 8,    48,   10,   48,   12,   48,   1510,
      9,    48,   1,    48,   1,    48,   1,    48,   3,    48,   1515, 8,
      48,   1,    48,   1,    48,   1,    48,   1,    48,   1,    48,   1,
      48,   3,    48,   1523, 8,    48,   1,    48,   1,    48,   1,    48,
      1,    48,   3,    48,   1529, 8,    48,   1,    48,   1,    48,   3,
      48,   1533, 8,    48,   1,    48,   1,    48,   1,    48,   3,    48,
      1538, 8,    48,   1,    48,   1,    48,   1,    48,   3,    48,   1543,
      8,    48,   1,    49,   1,    49,   1,    49,   1,    49,   3,    49,
      1549, 8,    49,   1,    49,   1,    49,   1,    49,   1,    49,   1,
      49,   1,    49,   1,    49,   1,    49,   1,    49,   1,    49,   1,
      49,   1,    49,   5,    49,   1563, 8,    49,   10,   49,   12,   49,
      1566, 9,    49,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   4,    50,   1592, 8,    50,   11,   50,   12,   50,
      1593, 1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   5,    50,   1603, 8,    50,   10,   50,   12,   50,
      1606, 9,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   5,    50,   1620, 8,    50,   10,   50,   12,   50,
      1623, 9,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   3,    50,   1632, 8,    50,   1,    50,
      3,    50,   1635, 8,    50,   1,    50,   1,    50,   1,    50,   3,
      50,   1640, 8,    50,   1,    50,   1,    50,   1,    50,   5,    50,
      1645, 8,    50,   10,   50,   12,   50,   1648, 9,    50,   3,    50,
      1650, 8,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   5,    50,   1657, 8,    50,   10,   50,   12,   50,   1660, 9,
      50,   3,    50,   1662, 8,    50,   1,    50,   1,    50,   3,    50,
      1666, 8,    50,   1,    50,   3,    50,   1669, 8,    50,   1,    50,
      3,    50,   1672, 8,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   5,    50,   1682,
      8,    50,   10,   50,   12,   50,   1685, 9,    50,   3,    50,   1687,
      8,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,
      1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,
      1,    50,   1,    50,   1,    50,   1,    50,   4,    50,   1704, 8,
      50,   11,   50,   12,   50,   1705, 1,    50,   1,    50,   3,    50,
      1710, 8,    50,   1,    50,   1,    50,   1,    50,   1,    50,   4,
      50,   1716, 8,    50,   11,   50,   12,   50,   1717, 1,    50,   1,
      50,   3,    50,   1722, 8,    50,   1,    50,   1,    50,   1,    50,
      1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,
      1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,
      1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,
      5,    50,   1745, 8,    50,   10,   50,   12,   50,   1748, 9,    50,
      3,    50,   1750, 8,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   3,    50,   1759, 8,    50,
      1,    50,   1,    50,   1,    50,   1,    50,   3,    50,   1765, 8,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   3,    50,   1771,
      8,    50,   1,    50,   1,    50,   1,    50,   1,    50,   3,    50,
      1777, 8,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   3,    50,   1787, 8,    50,
      1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,
      1,    50,   3,    50,   1796, 8,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   5,    50,   1816, 8,    50,
      10,   50,   12,   50,   1819, 9,    50,   3,    50,   1821, 8,    50,
      1,    50,   3,    50,   1824, 8,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   1,
      50,   1,    50,   1,    50,   1,    50,   5,    50,   1838, 8,    50,
      10,   50,   12,   50,   1841, 9,    50,   3,    50,   1843, 8,    50,
      1,    50,   1,    50,   1,    50,   1,    50,   1,    50,   5,    50,
      1850, 8,    50,   10,   50,   12,   50,   1853, 9,    50,   1,    51,
      1,    51,   1,    51,   1,    51,   3,    51,   1859, 8,    51,   3,
      51,   1861, 8,    51,   1,    52,   1,    52,   1,    52,   1,    52,
      3,    52,   1867, 8,    52,   1,    53,   1,    53,   1,    53,   1,
      53,   1,    53,   1,    53,   3,    53,   1875, 8,    53,   1,    54,
      1,    54,   1,    55,   1,    55,   1,    56,   1,    56,   1,    57,
      1,    57,   3,    57,   1885, 8,    57,   1,    57,   1,    57,   1,
      57,   1,    57,   3,    57,   1891, 8,    57,   1,    58,   1,    58,
      1,    59,   1,    59,   1,    60,   1,    60,   1,    60,   1,    60,
      5,    60,   1901, 8,    60,   10,   60,   12,   60,   1904, 9,    60,
      3,    60,   1906, 8,    60,   1,    60,   1,    60,   1,    61,   1,
      61,   1,    61,   1,    61,   1,    61,   1,    61,   1,    61,   1,
      61,   1,    61,   1,    61,   1,    61,   1,    61,   1,    61,   1,
      61,   1,    61,   1,    61,   1,    61,   1,    61,   1,    61,   1,
      61,   1,    61,   5,    61,   1931, 8,    61,   10,   61,   12,   61,
      1934, 9,    61,   1,    61,   1,    61,   1,    61,   1,    61,   1,
      61,   1,    61,   1,    61,   5,    61,   1943, 8,    61,   10,   61,
      12,   61,   1946, 9,    61,   1,    61,   1,    61,   3,    61,   1950,
      8,    61,   1,    61,   1,    61,   1,    61,   1,    61,   1,    61,
      3,    61,   1957, 8,    61,   1,    61,   1,    61,   5,    61,   1961,
      8,    61,   10,   61,   12,   61,   1964, 9,    61,   1,    62,   1,
      62,   3,    62,   1968, 8,    62,   1,    63,   1,    63,   1,    63,
      1,    63,   3,    63,   1974, 8,    63,   1,    64,   1,    64,   1,
      64,   1,    64,   1,    64,   1,    65,   1,    65,   1,    65,   1,
      65,   1,    65,   1,    65,   1,    66,   1,    66,   1,    66,   1,
      66,   1,    66,   1,    66,   1,    66,   5,    66,   1994, 8,    66,
      10,   66,   12,   66,   1997, 9,    66,   3,    66,   1999, 8,    66,
      1,    66,   1,    66,   1,    66,   1,    66,   1,    66,   5,    66,
      2006, 8,    66,   10,   66,   12,   66,   2009, 9,    66,   3,    66,
      2011, 8,    66,   1,    66,   3,    66,   2014, 8,    66,   1,    66,
      1,    66,   1,    67,   1,    67,   1,    67,   1,    67,   1,    67,
      1,    67,   1,    67,   1,    67,   1,    67,   1,    67,   1,    67,
      1,    67,   1,    67,   1,    67,   1,    67,   1,    67,   1,    67,
      1,    67,   1,    67,   1,    67,   1,    67,   1,    67,   1,    67,
      1,    67,   3,    67,   2042, 8,    67,   1,    68,   1,    68,   1,
      68,   1,    68,   1,    68,   1,    68,   1,    68,   1,    68,   1,
      68,   3,    68,   2053, 8,    68,   1,    69,   1,    69,   1,    69,
      1,    69,   1,    70,   1,    70,   1,    70,   1,    70,   3,    70,
      2063, 8,    70,   1,    71,   1,    71,   1,    71,   1,    71,   1,
      71,   3,    71,   2070, 8,    71,   1,    72,   1,    72,   1,    72,
      1,    72,   1,    72,   1,    72,   1,    72,   3,    72,   2079, 8,
      72,   1,    73,   1,    73,   1,    73,   1,    73,   1,    73,   3,
      73,   2086, 8,    73,   1,    74,   1,    74,   1,    74,   1,    74,
      3,    74,   2092, 8,    74,   1,    75,   1,    75,   1,    75,   5,
      75,   2097, 8,    75,   10,   75,   12,   75,   2100, 9,    75,   1,
      76,   1,    76,   1,    76,   1,    76,   1,    76,   1,    77,   1,
      77,   1,    77,   3,    77,   2110, 8,    77,   1,    78,   1,    78,
      1,    78,   3,    78,   2115, 8,    78,   1,    79,   1,    79,   1,
      79,   1,    79,   1,    79,   3,    79,   2122, 8,    79,   1,    80,
      1,    80,   1,    80,   5,    80,   2127, 8,    80,   10,   80,   12,
      80,   2130, 9,    80,   1,    81,   1,    81,   1,    81,   1,    81,
      1,    81,   3,    81,   2137, 8,    81,   1,    82,   1,    82,   1,
      82,   3,    82,   2142, 8,    82,   1,    83,   1,    83,   3,    83,
      2146, 8,    83,   1,    84,   1,    84,   1,    84,   1,    84,   1,
      85,   1,    85,   1,    85,   3,    85,   2155, 8,    85,   1,    86,
      1,    86,   1,    86,   3,    86,   2160, 8,    86,   1,    87,   5,
      87,   2163, 8,    87,   10,   87,   12,   87,   2166, 9,    87,   1,
      88,   1,    88,   1,    88,   3,    88,   2171, 8,    88,   1,    89,
      1,    89,   1,    89,   3,    89,   2176, 8,    89,   1,    90,   1,
      90,   1,    91,   1,    91,   1,    91,   3,    91,   2183, 8,    91,
      1,    92,   1,    92,   1,    92,   0,    6,    48,   76,   94,   98,
      100,  122,  93,   0,    2,    4,    6,    8,    10,   12,   14,   16,
      18,   20,   22,   24,   26,   28,   30,   32,   34,   36,   38,   40,
      42,   44,   46,   48,   50,   52,   54,   56,   58,   60,   62,   64,
      66,   68,   70,   72,   74,   76,   78,   80,   82,   84,   86,   88,
      90,   92,   94,   96,   98,   100,  102,  104,  106,  108,  110,  112,
      114,  116,  118,  120,  122,  124,  126,  128,  130,  132,  134,  136,
      138,  140,  142,  144,  146,  148,  150,  152,  154,  156,  158,  160,
      162,  164,  166,  168,  170,  172,  174,  176,  178,  180,  182,  184,
      0,    25,   2,    0,    28,   28,   169,  169,  2,    0,    51,   51,
      105,  105,  2,    0,    81,   81,   97,   97,   2,    0,    67,   67,
      98,   98,   1,    0,    178,  179,  2,    0,    13,   13,   249,  249,
      2,    0,    65,   65,   215,  215,  2,    0,    20,   20,   53,   53,
      2,    0,    77,   77,   113,  113,  2,    0,    13,   13,   57,   57,
      2,    0,    23,   23,   195,  195,  1,    0,    240,  241,  1,    0,
      242,  244,  1,    0,    234,  239,  3,    0,    13,   13,   17,   17,
      190,  190,  2,    0,    74,   74,   208,  208,  5,    0,    49,   49,
      94,   94,   124,  125,  182,  182,  232,  232,  1,    0,    128,  131,
      2,    0,    78,   78,   154,  154,  3,    0,    89,   89,   109,  109,
      202,  202,  7,    0,    58,   58,   68,   68,   88,   88,   106,  106,
      121,  121,  143,  143,  222,  222,  2,    0,    142,  142,  231,  231,
      3,    0,    196,  197,  205,  205,  225,  225,  2,    0,    56,   56,
      61,   61,   51,   0,    11,   13,   15,   15,   17,   18,   20,   23,
      26,   28,   31,   36,   41,   41,   43,   43,   47,   49,   51,   51,
      53,   53,   55,   56,   58,   58,   61,   61,   63,   63,   66,   68,
      71,   71,   73,   73,   75,   78,   80,   80,   83,   89,   92,   92,
      94,   96,   98,   98,   100,  100,  103,  103,  105,  106,  108,  109,
      111,  114,  116,  116,  118,  118,  121,  126,  128,  133,  137,  140,
      142,  144,  147,  147,  149,  154,  156,  160,  162,  172,  174,  176,
      178,  183,  185,  197,  199,  202,  204,  207,  209,  211,  213,  214,
      216,  216,  218,  220,  222,  222,  224,  226,  230,  233,  2520, 0,
      186,  1,    0,    0,    0,    2,    189,  1,    0,    0,    0,    4,
      192,  1,    0,    0,    0,    6,    932,  1,    0,    0,    0,    8,
      935,  1,    0,    0,    0,    10,   939,  1,    0,    0,    0,    12,
      954,  1,    0,    0,    0,    14,   956,  1,    0,    0,    0,    16,
      970,  1,    0,    0,    0,    18,   976,  1,    0,    0,    0,    20,
      987,  1,    0,    0,    0,    22,   991,  1,    0,    0,    0,    24,
      997,  1,    0,    0,    0,    26,   1004, 1,    0,    0,    0,    28,
      1009, 1,    0,    0,    0,    30,   1012, 1,    0,    0,    0,    32,
      1016, 1,    0,    0,    0,    34,   1018, 1,    0,    0,    0,    36,
      1021, 1,    0,    0,    0,    38,   1028, 1,    0,    0,    0,    40,
      1033, 1,    0,    0,    0,    42,   1044, 1,    0,    0,    0,    44,
      1046, 1,    0,    0,    0,    46,   1048, 1,    0,    0,    0,    48,
      1079, 1,    0,    0,    0,    50,   1115, 1,    0,    0,    0,    52,
      1117, 1,    0,    0,    0,    54,   1186, 1,    0,    0,    0,    56,
      1189, 1,    0,    0,    0,    58,   1239, 1,    0,    0,    0,    60,
      1254, 1,    0,    0,    0,    62,   1256, 1,    0,    0,    0,    64,
      1265, 1,    0,    0,    0,    66,   1300, 1,    0,    0,    0,    68,
      1304, 1,    0,    0,    0,    70,   1308, 1,    0,    0,    0,    72,
      1320, 1,    0,    0,    0,    74,   1332, 1,    0,    0,    0,    76,
      1336, 1,    0,    0,    0,    78,   1375, 1,    0,    0,    0,    80,
      1391, 1,    0,    0,    0,    82,   1393, 1,    0,    0,    0,    84,
      1402, 1,    0,    0,    0,    86,   1404, 1,    0,    0,    0,    88,
      1414, 1,    0,    0,    0,    90,   1457, 1,    0,    0,    0,    92,
      1459, 1,    0,    0,    0,    94,   1468, 1,    0,    0,    0,    96,
      1542, 1,    0,    0,    0,    98,   1548, 1,    0,    0,    0,    100,
      1823, 1,    0,    0,    0,    102,  1860, 1,    0,    0,    0,    104,
      1866, 1,    0,    0,    0,    106,  1874, 1,    0,    0,    0,    108,
      1876, 1,    0,    0,    0,    110,  1878, 1,    0,    0,    0,    112,
      1880, 1,    0,    0,    0,    114,  1882, 1,    0,    0,    0,    116,
      1892, 1,    0,    0,    0,    118,  1894, 1,    0,    0,    0,    120,
      1896, 1,    0,    0,    0,    122,  1956, 1,    0,    0,    0,    124,
      1967, 1,    0,    0,    0,    126,  1973, 1,    0,    0,    0,    128,
      1975, 1,    0,    0,    0,    130,  1980, 1,    0,    0,    0,    132,
      1986, 1,    0,    0,    0,    134,  2041, 1,    0,    0,    0,    136,
      2052, 1,    0,    0,    0,    138,  2054, 1,    0,    0,    0,    140,
      2062, 1,    0,    0,    0,    142,  2069, 1,    0,    0,    0,    144,
      2078, 1,    0,    0,    0,    146,  2085, 1,    0,    0,    0,    148,
      2091, 1,    0,    0,    0,    150,  2093, 1,    0,    0,    0,    152,
      2101, 1,    0,    0,    0,    154,  2109, 1,    0,    0,    0,    156,
      2114, 1,    0,    0,    0,    158,  2121, 1,    0,    0,    0,    160,
      2123, 1,    0,    0,    0,    162,  2136, 1,    0,    0,    0,    164,
      2141, 1,    0,    0,    0,    166,  2145, 1,    0,    0,    0,    168,
      2147, 1,    0,    0,    0,    170,  2151, 1,    0,    0,    0,    172,
      2159, 1,    0,    0,    0,    174,  2164, 1,    0,    0,    0,    176,
      2170, 1,    0,    0,    0,    178,  2175, 1,    0,    0,    0,    180,
      2177, 1,    0,    0,    0,    182,  2182, 1,    0,    0,    0,    184,
      2184, 1,    0,    0,    0,    186,  187,  3,    6,    3,    0,    187,
      188,  5,    0,    0,    1,    188,  1,    1,    0,    0,    0,    189,
      190,  3,    92,   46,   0,    190,  191,  5,    0,    0,    1,    191,
      3,    1,    0,    0,    0,    192,  193,  3,    32,   16,   0,    193,
      194,  5,    0,    0,    1,    194,  5,    1,    0,    0,    0,    195,
      933,  3,    8,    4,    0,    196,  197,  5,    219,  0,    0,    197,
      933,  3,    162,  81,   0,    198,  199,  5,    219,  0,    0,    199,
      200,  3,    162,  81,   0,    200,  201,  5,    1,    0,    0,    201,
      202,  3,    162,  81,   0,    202,  933,  1,    0,    0,    0,    203,
      204,  5,    38,   0,    0,    204,  208,  5,    180,  0,    0,    205,
      206,  5,    95,   0,    0,    206,  207,  5,    135,  0,    0,    207,
      209,  5,    70,   0,    0,    208,  205,  1,    0,    0,    0,    208,
      209,  1,    0,    0,    0,    209,  210,  1,    0,    0,    0,    210,
      213,  3,    150,  75,   0,    211,  212,  5,    229,  0,    0,    212,
      214,  3,    18,   9,    0,    213,  211,  1,    0,    0,    0,    213,
      214,  1,    0,    0,    0,    214,  933,  1,    0,    0,    0,    215,
      216,  5,    59,   0,    0,    216,  219,  5,    180,  0,    0,    217,
      218,  5,    95,   0,    0,    218,  220,  5,    70,   0,    0,    219,
      217,  1,    0,    0,    0,    219,  220,  1,    0,    0,    0,    220,
      221,  1,    0,    0,    0,    221,  223,  3,    150,  75,   0,    222,
      224,  7,    0,    0,    0,    223,  222,  1,    0,    0,    0,    223,
      224,  1,    0,    0,    0,    224,  933,  1,    0,    0,    0,    225,
      226,  5,    14,   0,    0,    226,  227,  5,    180,  0,    0,    227,
      228,  3,    150,  75,   0,    228,  229,  5,    164,  0,    0,    229,
      230,  5,    206,  0,    0,    230,  231,  3,    162,  81,   0,    231,
      933,  1,    0,    0,    0,    232,  233,  5,    38,   0,    0,    233,
      237,  5,    198,  0,    0,    234,  235,  5,    95,   0,    0,    235,
      236,  5,    135,  0,    0,    236,  238,  5,    70,   0,    0,    237,
      234,  1,    0,    0,    0,    237,  238,  1,    0,    0,    0,    238,
      239,  1,    0,    0,    0,    239,  241,  3,    150,  75,   0,    240,
      242,  3,    88,   44,   0,    241,  240,  1,    0,    0,    0,    241,
      242,  1,    0,    0,    0,    242,  245,  1,    0,    0,    0,    243,
      244,  5,    34,   0,    0,    244,  246,  3,    102,  51,   0,    245,
      243,  1,    0,    0,    0,    245,  246,  1,    0,    0,    0,    246,
      249,  1,    0,    0,    0,    247,  248,  5,    229,  0,    0,    248,
      250,  3,    18,   9,    0,    249,  247,  1,    0,    0,    0,    249,
      250,  1,    0,    0,    0,    250,  251,  1,    0,    0,    0,    251,
      257,  5,    19,   0,    0,    252,  258,  3,    8,    4,    0,    253,
      254,  5,    2,    0,    0,    254,  255,  3,    8,    4,    0,    255,
      256,  5,    3,    0,    0,    256,  258,  1,    0,    0,    0,    257,
      252,  1,    0,    0,    0,    257,  253,  1,    0,    0,    0,    258,
      264,  1,    0,    0,    0,    259,  261,  5,    229,  0,    0,    260,
      262,  5,    132,  0,    0,    261,  260,  1,    0,    0,    0,    261,
      262,  1,    0,    0,    0,    262,  263,  1,    0,    0,    0,    263,
      265,  5,    47,   0,    0,    264,  259,  1,    0,    0,    0,    264,
      265,  1,    0,    0,    0,    265,  933,  1,    0,    0,    0,    266,
      267,  5,    38,   0,    0,    267,  271,  5,    198,  0,    0,    268,
      269,  5,    95,   0,    0,    269,  270,  5,    135,  0,    0,    270,
      272,  5,    70,   0,    0,    271,  268,  1,    0,    0,    0,    271,
      272,  1,    0,    0,    0,    272,  273,  1,    0,    0,    0,    273,
      274,  3,    150,  75,   0,    274,  275,  5,    2,    0,    0,    275,
      280,  3,    12,   6,    0,    276,  277,  5,    4,    0,    0,    277,
      279,  3,    12,   6,    0,    278,  276,  1,    0,    0,    0,    279,
      282,  1,    0,    0,    0,    280,  278,  1,    0,    0,    0,    280,
      281,  1,    0,    0,    0,    281,  283,  1,    0,    0,    0,    282,
      280,  1,    0,    0,    0,    283,  286,  5,    3,    0,    0,    284,
      285,  5,    34,   0,    0,    285,  287,  3,    102,  51,   0,    286,
      284,  1,    0,    0,    0,    286,  287,  1,    0,    0,    0,    287,
      290,  1,    0,    0,    0,    288,  289,  5,    229,  0,    0,    289,
      291,  3,    18,   9,    0,    290,  288,  1,    0,    0,    0,    290,
      291,  1,    0,    0,    0,    291,  933,  1,    0,    0,    0,    292,
      293,  5,    59,   0,    0,    293,  296,  5,    198,  0,    0,    294,
      295,  5,    95,   0,    0,    295,  297,  5,    70,   0,    0,    296,
      294,  1,    0,    0,    0,    296,  297,  1,    0,    0,    0,    297,
      298,  1,    0,    0,    0,    298,  933,  3,    150,  75,   0,    299,
      300,  5,    101,  0,    0,    300,  301,  5,    104,  0,    0,    301,
      303,  3,    150,  75,   0,    302,  304,  3,    88,   44,   0,    303,
      302,  1,    0,    0,    0,    303,  304,  1,    0,    0,    0,    304,
      305,  1,    0,    0,    0,    305,  306,  3,    8,    4,    0,    306,
      933,  1,    0,    0,    0,    307,  308,  5,    52,   0,    0,    308,
      309,  5,    81,   0,    0,    309,  312,  3,    150,  75,   0,    310,
      311,  5,    228,  0,    0,    311,  313,  3,    94,   47,   0,    312,
      310,  1,    0,    0,    0,    312,  313,  1,    0,    0,    0,    313,
      933,  1,    0,    0,    0,    314,  315,  5,    209,  0,    0,    315,
      316,  5,    198,  0,    0,    316,  933,  3,    150,  75,   0,    317,
      318,  5,    14,   0,    0,    318,  321,  5,    198,  0,    0,    319,
      320,  5,    95,   0,    0,    320,  322,  5,    70,   0,    0,    321,
      319,  1,    0,    0,    0,    321,  322,  1,    0,    0,    0,    322,
      323,  1,    0,    0,    0,    323,  324,  3,    150,  75,   0,    324,
      325,  5,    164,  0,    0,    325,  326,  5,    206,  0,    0,    326,
      327,  3,    150,  75,   0,    327,  933,  1,    0,    0,    0,    328,
      329,  5,    14,   0,    0,    329,  332,  5,    198,  0,    0,    330,
      331,  5,    95,   0,    0,    331,  333,  5,    70,   0,    0,    332,
      330,  1,    0,    0,    0,    332,  333,  1,    0,    0,    0,    333,
      334,  1,    0,    0,    0,    334,  335,  3,    150,  75,   0,    335,
      336,  5,    164,  0,    0,    336,  339,  5,    32,   0,    0,    337,
      338,  5,    95,   0,    0,    338,  340,  5,    70,   0,    0,    339,
      337,  1,    0,    0,    0,    339,  340,  1,    0,    0,    0,    340,
      341,  1,    0,    0,    0,    341,  342,  3,    162,  81,   0,    342,
      343,  5,    206,  0,    0,    343,  344,  3,    162,  81,   0,    344,
      933,  1,    0,    0,    0,    345,  346,  5,    14,   0,    0,    346,
      349,  5,    198,  0,    0,    347,  348,  5,    95,   0,    0,    348,
      350,  5,    70,   0,    0,    349,  347,  1,    0,    0,    0,    349,
      350,  1,    0,    0,    0,    350,  351,  1,    0,    0,    0,    351,
      352,  3,    150,  75,   0,    352,  353,  5,    59,   0,    0,    353,
      356,  5,    32,   0,    0,    354,  355,  5,    95,   0,    0,    355,
      357,  5,    70,   0,    0,    356,  354,  1,    0,    0,    0,    356,
      357,  1,    0,    0,    0,    357,  358,  1,    0,    0,    0,    358,
      359,  3,    150,  75,   0,    359,  933,  1,    0,    0,    0,    360,
      361,  5,    14,   0,    0,    361,  364,  5,    198,  0,    0,    362,
      363,  5,    95,   0,    0,    363,  365,  5,    70,   0,    0,    364,
      362,  1,    0,    0,    0,    364,  365,  1,    0,    0,    0,    365,
      366,  1,    0,    0,    0,    366,  367,  3,    150,  75,   0,    367,
      368,  5,    11,   0,    0,    368,  372,  5,    32,   0,    0,    369,
      370,  5,    95,   0,    0,    370,  371,  5,    135,  0,    0,    371,
      373,  5,    70,   0,    0,    372,  369,  1,    0,    0,    0,    372,
      373,  1,    0,    0,    0,    373,  374,  1,    0,    0,    0,    374,
      375,  3,    14,   7,    0,    375,  933,  1,    0,    0,    0,    376,
      377,  5,    14,   0,    0,    377,  380,  5,    198,  0,    0,    378,
      379,  5,    95,   0,    0,    379,  381,  5,    70,   0,    0,    380,
      378,  1,    0,    0,    0,    380,  381,  1,    0,    0,    0,    381,
      382,  1,    0,    0,    0,    382,  383,  3,    150,  75,   0,    383,
      384,  5,    11,   0,    0,    384,  385,  3,    166,  83,   0,    385,
      933,  1,    0,    0,    0,    386,  387,  5,    14,   0,    0,    387,
      390,  5,    198,  0,    0,    388,  389,  5,    95,   0,    0,    389,
      391,  5,    70,   0,    0,    390,  388,  1,    0,    0,    0,    390,
      391,  1,    0,    0,    0,    391,  392,  1,    0,    0,    0,    392,
      393,  3,    150,  75,   0,    393,  394,  5,    59,   0,    0,    394,
      397,  5,    37,   0,    0,    395,  396,  5,    95,   0,    0,    396,
      398,  5,    70,   0,    0,    397,  395,  1,    0,    0,    0,    397,
      398,  1,    0,    0,    0,    398,  399,  1,    0,    0,    0,    399,
      400,  3,    162,  81,   0,    400,  933,  1,    0,    0,    0,    401,
      402,  5,    14,   0,    0,    402,  405,  5,    198,  0,    0,    403,
      404,  5,    95,   0,    0,    404,  406,  5,    70,   0,    0,    405,
      403,  1,    0,    0,    0,    405,  406,  1,    0,    0,    0,    406,
      407,  1,    0,    0,    0,    407,  408,  3,    150,  75,   0,    408,
      410,  5,    14,   0,    0,    409,  411,  5,    32,   0,    0,    410,
      409,  1,    0,    0,    0,    410,  411,  1,    0,    0,    0,    411,
      412,  1,    0,    0,    0,    412,  413,  3,    162,  81,   0,    413,
      414,  5,    187,  0,    0,    414,  415,  5,    135,  0,    0,    415,
      416,  5,    136,  0,    0,    416,  933,  1,    0,    0,    0,    417,
      418,  5,    14,   0,    0,    418,  421,  5,    198,  0,    0,    419,
      420,  5,    95,   0,    0,    420,  422,  5,    70,   0,    0,    421,
      419,  1,    0,    0,    0,    421,  422,  1,    0,    0,    0,    422,
      423,  1,    0,    0,    0,    423,  424,  3,    150,  75,   0,    424,
      426,  5,    14,   0,    0,    425,  427,  5,    32,   0,    0,    426,
      425,  1,    0,    0,    0,    426,  427,  1,    0,    0,    0,    427,
      428,  1,    0,    0,    0,    428,  429,  3,    162,  81,   0,    429,
      430,  5,    59,   0,    0,    430,  431,  5,    135,  0,    0,    431,
      432,  5,    136,  0,    0,    432,  933,  1,    0,    0,    0,    433,
      434,  5,    14,   0,    0,    434,  437,  5,    198,  0,    0,    435,
      436,  5,    95,   0,    0,    436,  438,  5,    70,   0,    0,    437,
      435,  1,    0,    0,    0,    437,  438,  1,    0,    0,    0,    438,
      439,  1,    0,    0,    0,    439,  440,  3,    150,  75,   0,    440,
      441,  5,    187,  0,    0,    441,  442,  5,    158,  0,    0,    442,
      443,  3,    18,   9,    0,    443,  933,  1,    0,    0,    0,    444,
      445,  5,    15,   0,    0,    445,  448,  3,    150,  75,   0,    446,
      447,  5,    229,  0,    0,    447,  449,  3,    18,   9,    0,    448,
      446,  1,    0,    0,    0,    448,  449,  1,    0,    0,    0,    449,
      933,  1,    0,    0,    0,    450,  451,  5,    38,   0,    0,    451,
      452,  5,    211,  0,    0,    452,  453,  3,    150,  75,   0,    453,
      466,  5,    19,   0,    0,    454,  455,  5,    2,    0,    0,    455,
      460,  3,    22,   11,   0,    456,  457,  5,    4,    0,    0,    457,
      459,  3,    22,   11,   0,    458,  456,  1,    0,    0,    0,    459,
      462,  1,    0,    0,    0,    460,  458,  1,    0,    0,    0,    460,
      461,  1,    0,    0,    0,    461,  463,  1,    0,    0,    0,    462,
      460,  1,    0,    0,    0,    463,  464,  5,    3,    0,    0,    464,
      467,  1,    0,    0,    0,    465,  467,  3,    122,  61,   0,    466,
      454,  1,    0,    0,    0,    466,  465,  1,    0,    0,    0,    467,
      933,  1,    0,    0,    0,    468,  471,  5,    38,   0,    0,    469,
      470,  5,    145,  0,    0,    470,  472,  5,    166,  0,    0,    471,
      469,  1,    0,    0,    0,    471,  472,  1,    0,    0,    0,    472,
      473,  1,    0,    0,    0,    473,  474,  5,    226,  0,    0,    474,
      477,  3,    150,  75,   0,    475,  476,  5,    183,  0,    0,    476,
      478,  7,    1,    0,    0,    477,  475,  1,    0,    0,    0,    477,
      478,  1,    0,    0,    0,    478,  479,  1,    0,    0,    0,    479,
      480,  5,    19,   0,    0,    480,  481,  3,    8,    4,    0,    481,
      933,  1,    0,    0,    0,    482,  483,  5,    14,   0,    0,    483,
      486,  5,    226,  0,    0,    484,  485,  5,    95,   0,    0,    485,
      487,  5,    70,   0,    0,    486,  484,  1,    0,    0,    0,    486,
      487,  1,    0,    0,    0,    487,  488,  1,    0,    0,    0,    488,
      489,  3,    150,  75,   0,    489,  490,  5,    164,  0,    0,    490,
      491,  5,    206,  0,    0,    491,  492,  3,    150,  75,   0,    492,
      933,  1,    0,    0,    0,    493,  494,  5,    59,   0,    0,    494,
      497,  5,    226,  0,    0,    495,  496,  5,    95,   0,    0,    496,
      498,  5,    70,   0,    0,    497,  495,  1,    0,    0,    0,    497,
      498,  1,    0,    0,    0,    498,  499,  1,    0,    0,    0,    499,
      933,  3,    150,  75,   0,    500,  501,  5,    38,   0,    0,    501,
      502,  5,    123,  0,    0,    502,  506,  5,    226,  0,    0,    503,
      504,  5,    95,   0,    0,    504,  505,  5,    135,  0,    0,    505,
      507,  5,    70,   0,    0,    506,  503,  1,    0,    0,    0,    506,
      507,  1,    0,    0,    0,    507,  508,  1,    0,    0,    0,    508,
      511,  3,    150,  75,   0,    509,  510,  5,    34,   0,    0,    510,
      512,  3,    102,  51,   0,    511,  509,  1,    0,    0,    0,    511,
      512,  1,    0,    0,    0,    512,  515,  1,    0,    0,    0,    513,
      514,  5,    229,  0,    0,    514,  516,  3,    18,   9,    0,    515,
      513,  1,    0,    0,    0,    515,  516,  1,    0,    0,    0,    516,
      517,  1,    0,    0,    0,    517,  523,  5,    19,   0,    0,    518,
      524,  3,    8,    4,    0,    519,  520,  5,    2,    0,    0,    520,
      521,  3,    8,    4,    0,    521,  522,  5,    3,    0,    0,    522,
      524,  1,    0,    0,    0,    523,  518,  1,    0,    0,    0,    523,
      519,  1,    0,    0,    0,    524,  933,  1,    0,    0,    0,    525,
      526,  5,    59,   0,    0,    526,  527,  5,    123,  0,    0,    527,
      530,  5,    226,  0,    0,    528,  529,  5,    95,   0,    0,    529,
      531,  5,    70,   0,    0,    530,  528,  1,    0,    0,    0,    530,
      531,  1,    0,    0,    0,    531,  532,  1,    0,    0,    0,    532,
      933,  3,    150,  75,   0,    533,  534,  5,    162,  0,    0,    534,
      535,  5,    123,  0,    0,    535,  536,  5,    226,  0,    0,    536,
      537,  3,    150,  75,   0,    537,  538,  5,    228,  0,    0,    538,
      539,  3,    94,   47,   0,    539,  933,  1,    0,    0,    0,    540,
      543,  5,    38,   0,    0,    541,  542,  5,    145,  0,    0,    542,
      544,  5,    166,  0,    0,    543,  541,  1,    0,    0,    0,    543,
      544,  1,    0,    0,    0,    544,  546,  1,    0,    0,    0,    545,
      547,  5,    201,  0,    0,    546,  545,  1,    0,    0,    0,    546,
      547,  1,    0,    0,    0,    547,  548,  1,    0,    0,    0,    548,
      549,  5,    83,   0,    0,    549,  550,  3,    150,  75,   0,    550,
      559,  5,    2,    0,    0,    551,  556,  3,    22,   11,   0,    552,
      553,  5,    4,    0,    0,    553,  555,  3,    22,   11,   0,    554,
      552,  1,    0,    0,    0,    555,  558,  1,    0,    0,    0,    556,
      554,  1,    0,    0,    0,    556,  557,  1,    0,    0,    0,    557,
      560,  1,    0,    0,    0,    558,  556,  1,    0,    0,    0,    559,
      551,  1,    0,    0,    0,    559,  560,  1,    0,    0,    0,    560,
      561,  1,    0,    0,    0,    561,  562,  5,    3,    0,    0,    562,
      563,  5,    171,  0,    0,    563,  566,  3,    122,  61,   0,    564,
      565,  5,    34,   0,    0,    565,  567,  3,    102,  51,   0,    566,
      564,  1,    0,    0,    0,    566,  567,  1,    0,    0,    0,    567,
      568,  1,    0,    0,    0,    568,  569,  3,    24,   12,   0,    569,
      570,  3,    32,   16,   0,    570,  933,  1,    0,    0,    0,    571,
      572,  5,    14,   0,    0,    572,  573,  5,    83,   0,    0,    573,
      575,  3,    150,  75,   0,    574,  576,  3,    120,  60,   0,    575,
      574,  1,    0,    0,    0,    575,  576,  1,    0,    0,    0,    576,
      577,  1,    0,    0,    0,    577,  578,  3,    28,   14,   0,    578,
      933,  1,    0,    0,    0,    579,  581,  5,    59,   0,    0,    580,
      582,  5,    201,  0,    0,    581,  580,  1,    0,    0,    0,    581,
      582,  1,    0,    0,    0,    582,  583,  1,    0,    0,    0,    583,
      586,  5,    83,   0,    0,    584,  585,  5,    95,   0,    0,    585,
      587,  5,    70,   0,    0,    586,  584,  1,    0,    0,    0,    586,
      587,  1,    0,    0,    0,    587,  588,  1,    0,    0,    0,    588,
      590,  3,    150,  75,   0,    589,  591,  3,    120,  60,   0,    590,
      589,  1,    0,    0,    0,    590,  591,  1,    0,    0,    0,    591,
      933,  1,    0,    0,    0,    592,  593,  5,    26,   0,    0,    593,
      594,  3,    150,  75,   0,    594,  603,  5,    2,    0,    0,    595,
      600,  3,    146,  73,   0,    596,  597,  5,    4,    0,    0,    597,
      599,  3,    146,  73,   0,    598,  596,  1,    0,    0,    0,    599,
      602,  1,    0,    0,    0,    600,  598,  1,    0,    0,    0,    600,
      601,  1,    0,    0,    0,    601,  604,  1,    0,    0,    0,    602,
      600,  1,    0,    0,    0,    603,  595,  1,    0,    0,    0,    603,
      604,  1,    0,    0,    0,    604,  605,  1,    0,    0,    0,    605,
      606,  5,    3,    0,    0,    606,  933,  1,    0,    0,    0,    607,
      608,  5,    38,   0,    0,    608,  609,  5,    174,  0,    0,    609,
      613,  3,    162,  81,   0,    610,  611,  5,    229,  0,    0,    611,
      612,  5,    12,   0,    0,    612,  614,  3,    156,  78,   0,    613,
      610,  1,    0,    0,    0,    613,  614,  1,    0,    0,    0,    614,
      933,  1,    0,    0,    0,    615,  616,  5,    59,   0,    0,    616,
      617,  5,    174,  0,    0,    617,  933,  3,    162,  81,   0,    618,
      619,  5,    85,   0,    0,    619,  620,  3,    160,  80,   0,    620,
      621,  5,    206,  0,    0,    621,  626,  3,    158,  79,   0,    622,
      623,  5,    4,    0,    0,    623,  625,  3,    158,  79,   0,    624,
      622,  1,    0,    0,    0,    625,  628,  1,    0,    0,    0,    626,
      624,  1,    0,    0,    0,    626,  627,  1,    0,    0,    0,    627,
      632,  1,    0,    0,    0,    628,  626,  1,    0,    0,    0,    629,
      630,  5,    229,  0,    0,    630,  631,  5,    12,   0,    0,    631,
      633,  5,    144,  0,    0,    632,  629,  1,    0,    0,    0,    632,
      633,  1,    0,    0,    0,    633,  637,  1,    0,    0,    0,    634,
      635,  5,    86,   0,    0,    635,  636,  5,    25,   0,    0,    636,
      638,  3,    156,  78,   0,    637,  634,  1,    0,    0,    0,    637,
      638,  1,    0,    0,    0,    638,  933,  1,    0,    0,    0,    639,
      643,  5,    172,  0,    0,    640,  641,  5,    12,   0,    0,    641,
      642,  5,    144,  0,    0,    642,  644,  5,    79,   0,    0,    643,
      640,  1,    0,    0,    0,    643,  644,  1,    0,    0,    0,    644,
      645,  1,    0,    0,    0,    645,  646,  3,    160,  80,   0,    646,
      647,  5,    81,   0,    0,    647,  652,  3,    158,  79,   0,    648,
      649,  5,    4,    0,    0,    649,  651,  3,    158,  79,   0,    650,
      648,  1,    0,    0,    0,    651,  654,  1,    0,    0,    0,    652,
      650,  1,    0,    0,    0,    652,  653,  1,    0,    0,    0,    653,
      658,  1,    0,    0,    0,    654,  652,  1,    0,    0,    0,    655,
      656,  5,    86,   0,    0,    656,  657,  5,    25,   0,    0,    657,
      659,  3,    156,  78,   0,    658,  655,  1,    0,    0,    0,    658,
      659,  1,    0,    0,    0,    659,  933,  1,    0,    0,    0,    660,
      661,  5,    187,  0,    0,    661,  665,  5,    174,  0,    0,    662,
      666,  5,    13,   0,    0,    663,  666,  5,    133,  0,    0,    664,
      666,  3,    162,  81,   0,    665,  662,  1,    0,    0,    0,    665,
      663,  1,    0,    0,    0,    665,  664,  1,    0,    0,    0,    666,
      933,  1,    0,    0,    0,    667,  678,  5,    85,   0,    0,    668,
      673,  3,    148,  74,   0,    669,  670,  5,    4,    0,    0,    670,
      672,  3,    148,  74,   0,    671,  669,  1,    0,    0,    0,    672,
      675,  1,    0,    0,    0,    673,  671,  1,    0,    0,    0,    673,
      674,  1,    0,    0,    0,    674,  679,  1,    0,    0,    0,    675,
      673,  1,    0,    0,    0,    676,  677,  5,    13,   0,    0,    677,
      679,  5,    157,  0,    0,    678,  668,  1,    0,    0,    0,    678,
      676,  1,    0,    0,    0,    679,  680,  1,    0,    0,    0,    680,
      682,  5,    141,  0,    0,    681,  683,  5,    198,  0,    0,    682,
      681,  1,    0,    0,    0,    682,  683,  1,    0,    0,    0,    683,
      684,  1,    0,    0,    0,    684,  685,  3,    150,  75,   0,    685,
      686,  5,    206,  0,    0,    686,  690,  3,    158,  79,   0,    687,
      688,  5,    229,  0,    0,    688,  689,  5,    85,   0,    0,    689,
      691,  5,    144,  0,    0,    690,  687,  1,    0,    0,    0,    690,
      691,  1,    0,    0,    0,    691,  933,  1,    0,    0,    0,    692,
      696,  5,    172,  0,    0,    693,  694,  5,    85,   0,    0,    694,
      695,  5,    144,  0,    0,    695,  697,  5,    79,   0,    0,    696,
      693,  1,    0,    0,    0,    696,  697,  1,    0,    0,    0,    697,
      708,  1,    0,    0,    0,    698,  703,  3,    148,  74,   0,    699,
      700,  5,    4,    0,    0,    700,  702,  3,    148,  74,   0,    701,
      699,  1,    0,    0,    0,    702,  705,  1,    0,    0,    0,    703,
      701,  1,    0,    0,    0,    703,  704,  1,    0,    0,    0,    704,
      709,  1,    0,    0,    0,    705,  703,  1,    0,    0,    0,    706,
      707,  5,    13,   0,    0,    707,  709,  5,    157,  0,    0,    708,
      698,  1,    0,    0,    0,    708,  706,  1,    0,    0,    0,    709,
      710,  1,    0,    0,    0,    710,  712,  5,    141,  0,    0,    711,
      713,  5,    198,  0,    0,    712,  711,  1,    0,    0,    0,    712,
      713,  1,    0,    0,    0,    713,  714,  1,    0,    0,    0,    714,
      715,  3,    150,  75,   0,    715,  716,  5,    81,   0,    0,    716,
      717,  3,    158,  79,   0,    717,  933,  1,    0,    0,    0,    718,
      719,  5,    189,  0,    0,    719,  725,  5,    87,   0,    0,    720,
      722,  5,    141,  0,    0,    721,  723,  5,    198,  0,    0,    722,
      721,  1,    0,    0,    0,    722,  723,  1,    0,    0,    0,    723,
      724,  1,    0,    0,    0,    724,  726,  3,    150,  75,   0,    725,
      720,  1,    0,    0,    0,    725,  726,  1,    0,    0,    0,    726,
      933,  1,    0,    0,    0,    727,  729,  5,    71,   0,    0,    728,
      730,  5,    15,   0,    0,    729,  728,  1,    0,    0,    0,    729,
      730,  1,    0,    0,    0,    730,  732,  1,    0,    0,    0,    731,
      733,  5,    224,  0,    0,    732,  731,  1,    0,    0,    0,    732,
      733,  1,    0,    0,    0,    733,  745,  1,    0,    0,    0,    734,
      735,  5,    2,    0,    0,    735,  740,  3,    140,  70,   0,    736,
      737,  5,    4,    0,    0,    737,  739,  3,    140,  70,   0,    738,
      736,  1,    0,    0,    0,    739,  742,  1,    0,    0,    0,    740,
      738,  1,    0,    0,    0,    740,  741,  1,    0,    0,    0,    741,
      743,  1,    0,    0,    0,    742,  740,  1,    0,    0,    0,    743,
      744,  5,    3,    0,    0,    744,  746,  1,    0,    0,    0,    745,
      734,  1,    0,    0,    0,    745,  746,  1,    0,    0,    0,    746,
      747,  1,    0,    0,    0,    747,  933,  3,    6,    3,    0,    748,
      749,  5,    189,  0,    0,    749,  750,  5,    38,   0,    0,    750,
      751,  5,    198,  0,    0,    751,  933,  3,    150,  75,   0,    752,
      753,  5,    189,  0,    0,    753,  754,  5,    38,   0,    0,    754,
      755,  5,    226,  0,    0,    755,  933,  3,    150,  75,   0,    756,
      757,  5,    189,  0,    0,    757,  758,  5,    38,   0,    0,    758,
      759,  5,    123,  0,    0,    759,  760,  5,    226,  0,    0,    760,
      933,  3,    150,  75,   0,    761,  762,  5,    189,  0,    0,    762,
      763,  5,    38,   0,    0,    763,  764,  5,    83,   0,    0,    764,
      766,  3,    150,  75,   0,    765,  767,  3,    120,  60,   0,    766,
      765,  1,    0,    0,    0,    766,  767,  1,    0,    0,    0,    767,
      933,  1,    0,    0,    0,    768,  769,  5,    189,  0,    0,    769,
      772,  5,    199,  0,    0,    770,  771,  7,    2,    0,    0,    771,
      773,  3,    150,  75,   0,    772,  770,  1,    0,    0,    0,    772,
      773,  1,    0,    0,    0,    773,  780,  1,    0,    0,    0,    774,
      775,  5,    117,  0,    0,    775,  778,  3,    102,  51,   0,    776,
      777,  5,    64,   0,    0,    777,  779,  3,    102,  51,   0,    778,
      776,  1,    0,    0,    0,    778,  779,  1,    0,    0,    0,    779,
      781,  1,    0,    0,    0,    780,  774,  1,    0,    0,    0,    780,
      781,  1,    0,    0,    0,    781,  933,  1,    0,    0,    0,    782,
      783,  5,    189,  0,    0,    783,  786,  5,    181,  0,    0,    784,
      785,  7,    2,    0,    0,    785,  787,  3,    162,  81,   0,    786,
      784,  1,    0,    0,    0,    786,  787,  1,    0,    0,    0,    787,
      794,  1,    0,    0,    0,    788,  789,  5,    117,  0,    0,    789,
      792,  3,    102,  51,   0,    790,  791,  5,    64,   0,    0,    791,
      793,  3,    102,  51,   0,    792,  790,  1,    0,    0,    0,    792,
      793,  1,    0,    0,    0,    793,  795,  1,    0,    0,    0,    794,
      788,  1,    0,    0,    0,    794,  795,  1,    0,    0,    0,    795,
      933,  1,    0,    0,    0,    796,  797,  5,    189,  0,    0,    797,
      804,  5,    31,   0,    0,    798,  799,  5,    117,  0,    0,    799,
      802,  3,    102,  51,   0,    800,  801,  5,    64,   0,    0,    801,
      803,  3,    102,  51,   0,    802,  800,  1,    0,    0,    0,    802,
      803,  1,    0,    0,    0,    803,  805,  1,    0,    0,    0,    804,
      798,  1,    0,    0,    0,    804,  805,  1,    0,    0,    0,    805,
      933,  1,    0,    0,    0,    806,  807,  5,    189,  0,    0,    807,
      808,  5,    33,   0,    0,    808,  809,  7,    2,    0,    0,    809,
      933,  3,    150,  75,   0,    810,  811,  5,    189,  0,    0,    811,
      812,  5,    193,  0,    0,    812,  813,  5,    79,   0,    0,    813,
      933,  3,    150,  75,   0,    814,  815,  5,    189,  0,    0,    815,
      816,  5,    193,  0,    0,    816,  817,  5,    79,   0,    0,    817,
      818,  5,    2,    0,    0,    818,  819,  3,    54,   27,   0,    819,
      820,  5,    3,    0,    0,    820,  933,  1,    0,    0,    0,    821,
      823,  5,    189,  0,    0,    822,  824,  5,    41,   0,    0,    823,
      822,  1,    0,    0,    0,    823,  824,  1,    0,    0,    0,    824,
      825,  1,    0,    0,    0,    825,  828,  5,    175,  0,    0,    826,
      827,  7,    2,    0,    0,    827,  829,  3,    162,  81,   0,    828,
      826,  1,    0,    0,    0,    828,  829,  1,    0,    0,    0,    829,
      933,  1,    0,    0,    0,    830,  831,  5,    189,  0,    0,    831,
      832,  5,    174,  0,    0,    832,  835,  5,    87,   0,    0,    833,
      834,  7,    2,    0,    0,    834,  836,  3,    162,  81,   0,    835,
      833,  1,    0,    0,    0,    835,  836,  1,    0,    0,    0,    836,
      933,  1,    0,    0,    0,    837,  838,  5,    54,   0,    0,    838,
      933,  3,    150,  75,   0,    839,  840,  5,    53,   0,    0,    840,
      933,  3,    150,  75,   0,    841,  842,  5,    189,  0,    0,    842,
      849,  5,    84,   0,    0,    843,  844,  5,    117,  0,    0,    844,
      847,  3,    102,  51,   0,    845,  846,  5,    64,   0,    0,    846,
      848,  3,    102,  51,   0,    847,  845,  1,    0,    0,    0,    847,
      848,  1,    0,    0,    0,    848,  850,  1,    0,    0,    0,    849,
      843,  1,    0,    0,    0,    849,  850,  1,    0,    0,    0,    850,
      933,  1,    0,    0,    0,    851,  852,  5,    189,  0,    0,    852,
      859,  5,    186,  0,    0,    853,  854,  5,    117,  0,    0,    854,
      857,  3,    102,  51,   0,    855,  856,  5,    64,   0,    0,    856,
      858,  3,    102,  51,   0,    857,  855,  1,    0,    0,    0,    857,
      858,  1,    0,    0,    0,    858,  860,  1,    0,    0,    0,    859,
      853,  1,    0,    0,    0,    859,  860,  1,    0,    0,    0,    860,
      933,  1,    0,    0,    0,    861,  862,  5,    187,  0,    0,    862,
      863,  5,    186,  0,    0,    863,  864,  3,    150,  75,   0,    864,
      865,  5,    234,  0,    0,    865,  866,  3,    92,   46,   0,    866,
      933,  1,    0,    0,    0,    867,  868,  5,    167,  0,    0,    868,
      869,  5,    186,  0,    0,    869,  933,  3,    150,  75,   0,    870,
      871,  5,    192,  0,    0,    871,  880,  5,    207,  0,    0,    872,
      877,  3,    142,  71,   0,    873,  874,  5,    4,    0,    0,    874,
      876,  3,    142,  71,   0,    875,  873,  1,    0,    0,    0,    876,
      879,  1,    0,    0,    0,    877,  875,  1,    0,    0,    0,    877,
      878,  1,    0,    0,    0,    878,  881,  1,    0,    0,    0,    879,
      877,  1,    0,    0,    0,    880,  872,  1,    0,    0,    0,    880,
      881,  1,    0,    0,    0,    881,  933,  1,    0,    0,    0,    882,
      884,  5,    35,   0,    0,    883,  885,  5,    230,  0,    0,    884,
      883,  1,    0,    0,    0,    884,  885,  1,    0,    0,    0,    885,
      933,  1,    0,    0,    0,    886,  888,  5,    176,  0,    0,    887,
      889,  5,    230,  0,    0,    888,  887,  1,    0,    0,    0,    888,
      889,  1,    0,    0,    0,    889,  933,  1,    0,    0,    0,    890,
      891,  5,    155,  0,    0,    891,  892,  3,    162,  81,   0,    892,
      893,  5,    81,   0,    0,    893,  894,  3,    6,    3,    0,    894,
      933,  1,    0,    0,    0,    895,  896,  5,    50,   0,    0,    896,
      897,  5,    155,  0,    0,    897,  933,  3,    162,  81,   0,    898,
      899,  5,    69,   0,    0,    899,  909,  3,    162,  81,   0,    900,
      901,  5,    221,  0,    0,    901,  906,  3,    92,   46,   0,    902,
      903,  5,    4,    0,    0,    903,  905,  3,    92,   46,   0,    904,
      902,  1,    0,    0,    0,    905,  908,  1,    0,    0,    0,    906,
      904,  1,    0,    0,    0,    906,  907,  1,    0,    0,    0,    907,
      910,  1,    0,    0,    0,    908,  906,  1,    0,    0,    0,    909,
      900,  1,    0,    0,    0,    909,  910,  1,    0,    0,    0,    910,
      933,  1,    0,    0,    0,    911,  912,  5,    54,   0,    0,    912,
      913,  5,    100,  0,    0,    913,  933,  3,    162,  81,   0,    914,
      915,  5,    54,   0,    0,    915,  916,  5,    149,  0,    0,    916,
      933,  3,    162,  81,   0,    917,  918,  5,    218,  0,    0,    918,
      919,  3,    150,  75,   0,    919,  920,  5,    187,  0,    0,    920,
      925,  3,    138,  69,   0,    921,  922,  5,    4,    0,    0,    922,
      924,  3,    138,  69,   0,    923,  921,  1,    0,    0,    0,    924,
      927,  1,    0,    0,    0,    925,  923,  1,    0,    0,    0,    925,
      926,  1,    0,    0,    0,    926,  930,  1,    0,    0,    0,    927,
      925,  1,    0,    0,    0,    928,  929,  5,    228,  0,    0,    929,
      931,  3,    94,   47,   0,    930,  928,  1,    0,    0,    0,    930,
      931,  1,    0,    0,    0,    931,  933,  1,    0,    0,    0,    932,
      195,  1,    0,    0,    0,    932,  196,  1,    0,    0,    0,    932,
      198,  1,    0,    0,    0,    932,  203,  1,    0,    0,    0,    932,
      215,  1,    0,    0,    0,    932,  225,  1,    0,    0,    0,    932,
      232,  1,    0,    0,    0,    932,  266,  1,    0,    0,    0,    932,
      292,  1,    0,    0,    0,    932,  299,  1,    0,    0,    0,    932,
      307,  1,    0,    0,    0,    932,  314,  1,    0,    0,    0,    932,
      317,  1,    0,    0,    0,    932,  328,  1,    0,    0,    0,    932,
      345,  1,    0,    0,    0,    932,  360,  1,    0,    0,    0,    932,
      376,  1,    0,    0,    0,    932,  386,  1,    0,    0,    0,    932,
      401,  1,    0,    0,    0,    932,  417,  1,    0,    0,    0,    932,
      433,  1,    0,    0,    0,    932,  444,  1,    0,    0,    0,    932,
      450,  1,    0,    0,    0,    932,  468,  1,    0,    0,    0,    932,
      482,  1,    0,    0,    0,    932,  493,  1,    0,    0,    0,    932,
      500,  1,    0,    0,    0,    932,  525,  1,    0,    0,    0,    932,
      533,  1,    0,    0,    0,    932,  540,  1,    0,    0,    0,    932,
      571,  1,    0,    0,    0,    932,  579,  1,    0,    0,    0,    932,
      592,  1,    0,    0,    0,    932,  607,  1,    0,    0,    0,    932,
      615,  1,    0,    0,    0,    932,  618,  1,    0,    0,    0,    932,
      639,  1,    0,    0,    0,    932,  660,  1,    0,    0,    0,    932,
      667,  1,    0,    0,    0,    932,  692,  1,    0,    0,    0,    932,
      718,  1,    0,    0,    0,    932,  727,  1,    0,    0,    0,    932,
      748,  1,    0,    0,    0,    932,  752,  1,    0,    0,    0,    932,
      756,  1,    0,    0,    0,    932,  761,  1,    0,    0,    0,    932,
      768,  1,    0,    0,    0,    932,  782,  1,    0,    0,    0,    932,
      796,  1,    0,    0,    0,    932,  806,  1,    0,    0,    0,    932,
      810,  1,    0,    0,    0,    932,  814,  1,    0,    0,    0,    932,
      821,  1,    0,    0,    0,    932,  830,  1,    0,    0,    0,    932,
      837,  1,    0,    0,    0,    932,  839,  1,    0,    0,    0,    932,
      841,  1,    0,    0,    0,    932,  851,  1,    0,    0,    0,    932,
      861,  1,    0,    0,    0,    932,  867,  1,    0,    0,    0,    932,
      870,  1,    0,    0,    0,    932,  882,  1,    0,    0,    0,    932,
      886,  1,    0,    0,    0,    932,  890,  1,    0,    0,    0,    932,
      895,  1,    0,    0,    0,    932,  898,  1,    0,    0,    0,    932,
      911,  1,    0,    0,    0,    932,  914,  1,    0,    0,    0,    932,
      917,  1,    0,    0,    0,    933,  7,    1,    0,    0,    0,    934,
      936,  3,    10,   5,    0,    935,  934,  1,    0,    0,    0,    935,
      936,  1,    0,    0,    0,    936,  937,  1,    0,    0,    0,    937,
      938,  3,    46,   23,   0,    938,  9,    1,    0,    0,    0,    939,
      941,  5,    229,  0,    0,    940,  942,  5,    161,  0,    0,    941,
      940,  1,    0,    0,    0,    941,  942,  1,    0,    0,    0,    942,
      943,  1,    0,    0,    0,    943,  948,  3,    62,   31,   0,    944,
      945,  5,    4,    0,    0,    945,  947,  3,    62,   31,   0,    946,
      944,  1,    0,    0,    0,    947,  950,  1,    0,    0,    0,    948,
      946,  1,    0,    0,    0,    948,  949,  1,    0,    0,    0,    949,
      11,   1,    0,    0,    0,    950,  948,  1,    0,    0,    0,    951,
      955,  3,    166,  83,   0,    952,  955,  3,    14,   7,    0,    953,
      955,  3,    16,   8,    0,    954,  951,  1,    0,    0,    0,    954,
      952,  1,    0,    0,    0,    954,  953,  1,    0,    0,    0,    955,
      13,   1,    0,    0,    0,    956,  957,  3,    162,  81,   0,    957,
      960,  3,    122,  61,   0,    958,  959,  5,    135,  0,    0,    959,
      961,  5,    136,  0,    0,    960,  958,  1,    0,    0,    0,    960,
      961,  1,    0,    0,    0,    961,  964,  1,    0,    0,    0,    962,
      963,  5,    34,   0,    0,    963,  965,  3,    102,  51,   0,    964,
      962,  1,    0,    0,    0,    964,  965,  1,    0,    0,    0,    965,
      968,  1,    0,    0,    0,    966,  967,  5,    229,  0,    0,    967,
      969,  3,    18,   9,    0,    968,  966,  1,    0,    0,    0,    968,
      969,  1,    0,    0,    0,    969,  15,   1,    0,    0,    0,    970,
      971,  5,    117,  0,    0,    971,  974,  3,    150,  75,   0,    972,
      973,  7,    3,    0,    0,    973,  975,  5,    158,  0,    0,    974,
      972,  1,    0,    0,    0,    974,  975,  1,    0,    0,    0,    975,
      17,   1,    0,    0,    0,    976,  977,  5,    2,    0,    0,    977,
      982,  3,    20,   10,   0,    978,  979,  5,    4,    0,    0,    979,
      981,  3,    20,   10,   0,    980,  978,  1,    0,    0,    0,    981,
      984,  1,    0,    0,    0,    982,  980,  1,    0,    0,    0,    982,
      983,  1,    0,    0,    0,    983,  985,  1,    0,    0,    0,    984,
      982,  1,    0,    0,    0,    985,  986,  5,    3,    0,    0,    986,
      19,   1,    0,    0,    0,    987,  988,  3,    162,  81,   0,    988,
      989,  5,    234,  0,    0,    989,  990,  3,    92,   46,   0,    990,
      21,   1,    0,    0,    0,    991,  992,  3,    162,  81,   0,    992,
      993,  3,    122,  61,   0,    993,  23,   1,    0,    0,    0,    994,
      996,  3,    26,   13,   0,    995,  994,  1,    0,    0,    0,    996,
      999,  1,    0,    0,    0,    997,  995,  1,    0,    0,    0,    997,
      998,  1,    0,    0,    0,    998,  25,   1,    0,    0,    0,    999,
      997,  1,    0,    0,    0,    1000, 1001, 5,    112,  0,    0,    1001,
      1005, 3,    38,   19,   0,    1002, 1005, 3,    40,   20,   0,    1003,
      1005, 3,    42,   21,   0,    1004, 1000, 1,    0,    0,    0,    1004,
      1002, 1,    0,    0,    0,    1004, 1003, 1,    0,    0,    0,    1005,
      27,   1,    0,    0,    0,    1006, 1008, 3,    30,   15,   0,    1007,
      1006, 1,    0,    0,    0,    1008, 1011, 1,    0,    0,    0,    1009,
      1007, 1,    0,    0,    0,    1009, 1010, 1,    0,    0,    0,    1010,
      29,   1,    0,    0,    0,    1011, 1009, 1,    0,    0,    0,    1012,
      1013, 3,    42,   21,   0,    1013, 31,   1,    0,    0,    0,    1014,
      1017, 3,    34,   17,   0,    1015, 1017, 3,    36,   18,   0,    1016,
      1014, 1,    0,    0,    0,    1016, 1015, 1,    0,    0,    0,    1017,
      33,   1,    0,    0,    0,    1018, 1019, 5,    170,  0,    0,    1019,
      1020, 3,    92,   46,   0,    1020, 35,   1,    0,    0,    0,    1021,
      1024, 5,    73,   0,    0,    1022, 1023, 5,    126,  0,    0,    1023,
      1025, 3,    44,   22,   0,    1024, 1022, 1,    0,    0,    0,    1024,
      1025, 1,    0,    0,    0,    1025, 37,   1,    0,    0,    0,    1026,
      1029, 5,    191,  0,    0,    1027, 1029, 3,    162,  81,   0,    1028,
      1026, 1,    0,    0,    0,    1028, 1027, 1,    0,    0,    0,    1029,
      39,   1,    0,    0,    0,    1030, 1034, 5,    55,   0,    0,    1031,
      1032, 5,    135,  0,    0,    1032, 1034, 5,    55,   0,    0,    1033,
      1030, 1,    0,    0,    0,    1033, 1031, 1,    0,    0,    0,    1034,
      41,   1,    0,    0,    0,    1035, 1036, 5,    171,  0,    0,    1036,
      1037, 5,    136,  0,    0,    1037, 1038, 5,    141,  0,    0,    1038,
      1039, 5,    136,  0,    0,    1039, 1045, 5,    100,  0,    0,    1040,
      1041, 5,    27,   0,    0,    1041, 1042, 5,    141,  0,    0,    1042,
      1043, 5,    136,  0,    0,    1043, 1045, 5,    100,  0,    0,    1044,
      1035, 1,    0,    0,    0,    1044, 1040, 1,    0,    0,    0,    1045,
      43,   1,    0,    0,    0,    1046, 1047, 3,    162,  81,   0,    1047,
      45,   1,    0,    0,    0,    1048, 1059, 3,    48,   24,   0,    1049,
      1050, 5,    146,  0,    0,    1050, 1051, 5,    25,   0,    0,    1051,
      1056, 3,    52,   26,   0,    1052, 1053, 5,    4,    0,    0,    1053,
      1055, 3,    52,   26,   0,    1054, 1052, 1,    0,    0,    0,    1055,
      1058, 1,    0,    0,    0,    1056, 1054, 1,    0,    0,    0,    1056,
      1057, 1,    0,    0,    0,    1057, 1060, 1,    0,    0,    0,    1058,
      1056, 1,    0,    0,    0,    1059, 1049, 1,    0,    0,    0,    1059,
      1060, 1,    0,    0,    0,    1060, 1066, 1,    0,    0,    0,    1061,
      1062, 5,    140,  0,    0,    1062, 1064, 5,    249,  0,    0,    1063,
      1065, 7,    4,    0,    0,    1064, 1063, 1,    0,    0,    0,    1064,
      1065, 1,    0,    0,    0,    1065, 1067, 1,    0,    0,    0,    1066,
      1061, 1,    0,    0,    0,    1066, 1067, 1,    0,    0,    0,    1067,
      1077, 1,    0,    0,    0,    1068, 1069, 5,    118,  0,    0,    1069,
      1076, 7,    5,    0,    0,    1070, 1071, 5,    75,   0,    0,    1071,
      1072, 5,    77,   0,    0,    1072, 1073, 5,    249,  0,    0,    1073,
      1074, 5,    179,  0,    0,    1074, 1076, 5,    142,  0,    0,    1075,
      1068, 1,    0,    0,    0,    1075, 1070, 1,    0,    0,    0,    1076,
      1078, 1,    0,    0,    0,    1077, 1075, 1,    0,    0,    0,    1077,
      1078, 1,    0,    0,    0,    1078, 47,   1,    0,    0,    0,    1079,
      1080, 6,    24,   -1,   0,    1080, 1081, 3,    50,   25,   0,    1081,
      1096, 1,    0,    0,    0,    1082, 1083, 10,   2,    0,    0,    1083,
      1085, 5,    102,  0,    0,    1084, 1086, 3,    64,   32,   0,    1085,
      1084, 1,    0,    0,    0,    1085, 1086, 1,    0,    0,    0,    1086,
      1087, 1,    0,    0,    0,    1087, 1095, 3,    48,   24,   3,    1088,
      1089, 10,   1,    0,    0,    1089, 1091, 7,    6,    0,    0,    1090,
      1092, 3,    64,   32,   0,    1091, 1090, 1,    0,    0,    0,    1091,
      1092, 1,    0,    0,    0,    1092, 1093, 1,    0,    0,    0,    1093,
      1095, 3,    48,   24,   2,    1094, 1082, 1,    0,    0,    0,    1094,
      1088, 1,    0,    0,    0,    1095, 1098, 1,    0,    0,    0,    1096,
      1094, 1,    0,    0,    0,    1096, 1097, 1,    0,    0,    0,    1097,
      49,   1,    0,    0,    0,    1098, 1096, 1,    0,    0,    0,    1099,
      1116, 3,    54,   27,   0,    1100, 1101, 5,    198,  0,    0,    1101,
      1116, 3,    150,  75,   0,    1102, 1103, 5,    223,  0,    0,    1103,
      1108, 3,    92,   46,   0,    1104, 1105, 5,    4,    0,    0,    1105,
      1107, 3,    92,   46,   0,    1106, 1104, 1,    0,    0,    0,    1107,
      1110, 1,    0,    0,    0,    1108, 1106, 1,    0,    0,    0,    1108,
      1109, 1,    0,    0,    0,    1109, 1116, 1,    0,    0,    0,    1110,
      1108, 1,    0,    0,    0,    1111, 1112, 5,    2,    0,    0,    1112,
      1113, 3,    46,   23,   0,    1113, 1114, 5,    3,    0,    0,    1114,
      1116, 1,    0,    0,    0,    1115, 1099, 1,    0,    0,    0,    1115,
      1100, 1,    0,    0,    0,    1115, 1102, 1,    0,    0,    0,    1115,
      1111, 1,    0,    0,    0,    1116, 51,   1,    0,    0,    0,    1117,
      1119, 3,    92,   46,   0,    1118, 1120, 7,    7,    0,    0,    1119,
      1118, 1,    0,    0,    0,    1119, 1120, 1,    0,    0,    0,    1120,
      1123, 1,    0,    0,    0,    1121, 1122, 5,    138,  0,    0,    1122,
      1124, 7,    8,    0,    0,    1123, 1121, 1,    0,    0,    0,    1123,
      1124, 1,    0,    0,    0,    1124, 53,   1,    0,    0,    0,    1125,
      1127, 5,    184,  0,    0,    1126, 1128, 3,    64,   32,   0,    1127,
      1126, 1,    0,    0,    0,    1127, 1128, 1,    0,    0,    0,    1128,
      1129, 1,    0,    0,    0,    1129, 1134, 3,    66,   33,   0,    1130,
      1131, 5,    4,    0,    0,    1131, 1133, 3,    66,   33,   0,    1132,
      1130, 1,    0,    0,    0,    1133, 1136, 1,    0,    0,    0,    1134,
      1132, 1,    0,    0,    0,    1134, 1135, 1,    0,    0,    0,    1135,
      1138, 1,    0,    0,    0,    1136, 1134, 1,    0,    0,    0,    1137,
      1139, 5,    4,    0,    0,    1138, 1137, 1,    0,    0,    0,    1138,
      1139, 1,    0,    0,    0,    1139, 1149, 1,    0,    0,    0,    1140,
      1141, 5,    81,   0,    0,    1141, 1146, 3,    76,   38,   0,    1142,
      1143, 5,    4,    0,    0,    1143, 1145, 3,    76,   38,   0,    1144,
      1142, 1,    0,    0,    0,    1145, 1148, 1,    0,    0,    0,    1146,
      1144, 1,    0,    0,    0,    1146, 1147, 1,    0,    0,    0,    1147,
      1150, 1,    0,    0,    0,    1148, 1146, 1,    0,    0,    0,    1149,
      1140, 1,    0,    0,    0,    1149, 1150, 1,    0,    0,    0,    1150,
      1153, 1,    0,    0,    0,    1151, 1152, 5,    228,  0,    0,    1152,
      1154, 3,    94,   47,   0,    1153, 1151, 1,    0,    0,    0,    1153,
      1154, 1,    0,    0,    0,    1154, 1158, 1,    0,    0,    0,    1155,
      1156, 5,    90,   0,    0,    1156, 1157, 5,    25,   0,    0,    1157,
      1159, 3,    56,   28,   0,    1158, 1155, 1,    0,    0,    0,    1158,
      1159, 1,    0,    0,    0,    1159, 1162, 1,    0,    0,    0,    1160,
      1161, 5,    93,   0,    0,    1161, 1163, 3,    94,   47,   0,    1162,
      1160, 1,    0,    0,    0,    1162, 1163, 1,    0,    0,    0,    1163,
      1187, 1,    0,    0,    0,    1164, 1165, 5,    81,   0,    0,    1165,
      1170, 3,    76,   38,   0,    1166, 1167, 5,    4,    0,    0,    1167,
      1169, 3,    76,   38,   0,    1168, 1166, 1,    0,    0,    0,    1169,
      1172, 1,    0,    0,    0,    1170, 1168, 1,    0,    0,    0,    1170,
      1171, 1,    0,    0,    0,    1171, 1175, 1,    0,    0,    0,    1172,
      1170, 1,    0,    0,    0,    1173, 1174, 5,    228,  0,    0,    1174,
      1176, 3,    94,   47,   0,    1175, 1173, 1,    0,    0,    0,    1175,
      1176, 1,    0,    0,    0,    1176, 1180, 1,    0,    0,    0,    1177,
      1178, 5,    90,   0,    0,    1178, 1179, 5,    25,   0,    0,    1179,
      1181, 3,    56,   28,   0,    1180, 1177, 1,    0,    0,    0,    1180,
      1181, 1,    0,    0,    0,    1181, 1184, 1,    0,    0,    0,    1182,
      1183, 5,    93,   0,    0,    1183, 1185, 3,    94,   47,   0,    1184,
      1182, 1,    0,    0,    0,    1184, 1185, 1,    0,    0,    0,    1185,
      1187, 1,    0,    0,    0,    1186, 1125, 1,    0,    0,    0,    1186,
      1164, 1,    0,    0,    0,    1187, 55,   1,    0,    0,    0,    1188,
      1190, 3,    64,   32,   0,    1189, 1188, 1,    0,    0,    0,    1189,
      1190, 1,    0,    0,    0,    1190, 1191, 1,    0,    0,    0,    1191,
      1196, 3,    58,   29,   0,    1192, 1193, 5,    4,    0,    0,    1193,
      1195, 3,    58,   29,   0,    1194, 1192, 1,    0,    0,    0,    1195,
      1198, 1,    0,    0,    0,    1196, 1194, 1,    0,    0,    0,    1196,
      1197, 1,    0,    0,    0,    1197, 57,   1,    0,    0,    0,    1198,
      1196, 1,    0,    0,    0,    1199, 1240, 3,    60,   30,   0,    1200,
      1201, 5,    177,  0,    0,    1201, 1210, 5,    2,    0,    0,    1202,
      1207, 3,    92,   46,   0,    1203, 1204, 5,    4,    0,    0,    1204,
      1206, 3,    92,   46,   0,    1205, 1203, 1,    0,    0,    0,    1206,
      1209, 1,    0,    0,    0,    1207, 1205, 1,    0,    0,    0,    1207,
      1208, 1,    0,    0,    0,    1208, 1211, 1,    0,    0,    0,    1209,
      1207, 1,    0,    0,    0,    1210, 1202, 1,    0,    0,    0,    1210,
      1211, 1,    0,    0,    0,    1211, 1212, 1,    0,    0,    0,    1212,
      1240, 5,    3,    0,    0,    1213, 1214, 5,    40,   0,    0,    1214,
      1223, 5,    2,    0,    0,    1215, 1220, 3,    92,   46,   0,    1216,
      1217, 5,    4,    0,    0,    1217, 1219, 3,    92,   46,   0,    1218,
      1216, 1,    0,    0,    0,    1219, 1222, 1,    0,    0,    0,    1220,
      1218, 1,    0,    0,    0,    1220, 1221, 1,    0,    0,    0,    1221,
      1224, 1,    0,    0,    0,    1222, 1220, 1,    0,    0,    0,    1223,
      1215, 1,    0,    0,    0,    1223, 1224, 1,    0,    0,    0,    1224,
      1225, 1,    0,    0,    0,    1225, 1240, 5,    3,    0,    0,    1226,
      1227, 5,    91,   0,    0,    1227, 1228, 5,    188,  0,    0,    1228,
      1229, 5,    2,    0,    0,    1229, 1234, 3,    60,   30,   0,    1230,
      1231, 5,    4,    0,    0,    1231, 1233, 3,    60,   30,   0,    1232,
      1230, 1,    0,    0,    0,    1233, 1236, 1,    0,    0,    0,    1234,
      1232, 1,    0,    0,    0,    1234, 1235, 1,    0,    0,    0,    1235,
      1237, 1,    0,    0,    0,    1236, 1234, 1,    0,    0,    0,    1237,
      1238, 5,    3,    0,    0,    1238, 1240, 1,    0,    0,    0,    1239,
      1199, 1,    0,    0,    0,    1239, 1200, 1,    0,    0,    0,    1239,
      1213, 1,    0,    0,    0,    1239, 1226, 1,    0,    0,    0,    1240,
      59,   1,    0,    0,    0,    1241, 1250, 5,    2,    0,    0,    1242,
      1247, 3,    92,   46,   0,    1243, 1244, 5,    4,    0,    0,    1244,
      1246, 3,    92,   46,   0,    1245, 1243, 1,    0,    0,    0,    1246,
      1249, 1,    0,    0,    0,    1247, 1245, 1,    0,    0,    0,    1247,
      1248, 1,    0,    0,    0,    1248, 1251, 1,    0,    0,    0,    1249,
      1247, 1,    0,    0,    0,    1250, 1242, 1,    0,    0,    0,    1250,
      1251, 1,    0,    0,    0,    1251, 1252, 1,    0,    0,    0,    1252,
      1255, 5,    3,    0,    0,    1253, 1255, 3,    92,   46,   0,    1254,
      1241, 1,    0,    0,    0,    1254, 1253, 1,    0,    0,    0,    1255,
      61,   1,    0,    0,    0,    1256, 1258, 3,    162,  81,   0,    1257,
      1259, 3,    88,   44,   0,    1258, 1257, 1,    0,    0,    0,    1258,
      1259, 1,    0,    0,    0,    1259, 1260, 1,    0,    0,    0,    1260,
      1261, 5,    19,   0,    0,    1261, 1262, 5,    2,    0,    0,    1262,
      1263, 3,    8,    4,    0,    1263, 1264, 5,    3,    0,    0,    1264,
      63,   1,    0,    0,    0,    1265, 1266, 7,    9,    0,    0,    1266,
      65,   1,    0,    0,    0,    1267, 1268, 3,    150,  75,   0,    1268,
      1269, 5,    1,    0,    0,    1269, 1271, 5,    242,  0,    0,    1270,
      1272, 3,    68,   34,   0,    1271, 1270, 1,    0,    0,    0,    1271,
      1272, 1,    0,    0,    0,    1272, 1301, 1,    0,    0,    0,    1273,
      1275, 5,    242,  0,    0,    1274, 1276, 3,    68,   34,   0,    1275,
      1274, 1,    0,    0,    0,    1275, 1276, 1,    0,    0,    0,    1276,
      1301, 1,    0,    0,    0,    1277, 1278, 3,    150,  75,   0,    1278,
      1279, 5,    1,    0,    0,    1279, 1280, 5,    33,   0,    0,    1280,
      1281, 5,    2,    0,    0,    1281, 1282, 5,    246,  0,    0,    1282,
      1284, 5,    3,    0,    0,    1283, 1285, 3,    68,   34,   0,    1284,
      1283, 1,    0,    0,    0,    1284, 1285, 1,    0,    0,    0,    1285,
      1301, 1,    0,    0,    0,    1286, 1287, 5,    33,   0,    0,    1287,
      1288, 5,    2,    0,    0,    1288, 1289, 5,    246,  0,    0,    1289,
      1291, 5,    3,    0,    0,    1290, 1292, 3,    68,   34,   0,    1291,
      1290, 1,    0,    0,    0,    1291, 1292, 1,    0,    0,    0,    1292,
      1301, 1,    0,    0,    0,    1293, 1298, 3,    92,   46,   0,    1294,
      1296, 5,    19,   0,    0,    1295, 1294, 1,    0,    0,    0,    1295,
      1296, 1,    0,    0,    0,    1296, 1297, 1,    0,    0,    0,    1297,
      1299, 3,    162,  81,   0,    1298, 1295, 1,    0,    0,    0,    1298,
      1299, 1,    0,    0,    0,    1299, 1301, 1,    0,    0,    0,    1300,
      1267, 1,    0,    0,    0,    1300, 1273, 1,    0,    0,    0,    1300,
      1277, 1,    0,    0,    0,    1300, 1286, 1,    0,    0,    0,    1300,
      1293, 1,    0,    0,    0,    1301, 67,   1,    0,    0,    0,    1302,
      1305, 3,    70,   35,   0,    1303, 1305, 3,    72,   36,   0,    1304,
      1302, 1,    0,    0,    0,    1304, 1303, 1,    0,    0,    0,    1305,
      1306, 1,    0,    0,    0,    1306, 1304, 1,    0,    0,    0,    1306,
      1307, 1,    0,    0,    0,    1307, 69,   1,    0,    0,    0,    1308,
      1309, 5,    66,   0,    0,    1309, 1310, 5,    2,    0,    0,    1310,
      1315, 3,    162,  81,   0,    1311, 1312, 5,    4,    0,    0,    1312,
      1314, 3,    162,  81,   0,    1313, 1311, 1,    0,    0,    0,    1314,
      1317, 1,    0,    0,    0,    1315, 1313, 1,    0,    0,    0,    1315,
      1316, 1,    0,    0,    0,    1316, 1318, 1,    0,    0,    0,    1317,
      1315, 1,    0,    0,    0,    1318, 1319, 5,    3,    0,    0,    1319,
      71,   1,    0,    0,    0,    1320, 1321, 5,    166,  0,    0,    1321,
      1322, 5,    2,    0,    0,    1322, 1327, 3,    74,   37,   0,    1323,
      1324, 5,    4,    0,    0,    1324, 1326, 3,    74,   37,   0,    1325,
      1323, 1,    0,    0,    0,    1326, 1329, 1,    0,    0,    0,    1327,
      1325, 1,    0,    0,    0,    1327, 1328, 1,    0,    0,    0,    1328,
      1330, 1,    0,    0,    0,    1329, 1327, 1,    0,    0,    0,    1330,
      1331, 5,    3,    0,    0,    1331, 73,   1,    0,    0,    0,    1332,
      1333, 3,    92,   46,   0,    1333, 1334, 5,    19,   0,    0,    1334,
      1335, 3,    162,  81,   0,    1335, 75,   1,    0,    0,    0,    1336,
      1337, 6,    38,   -1,   0,    1337, 1338, 3,    82,   41,   0,    1338,
      1357, 1,    0,    0,    0,    1339, 1353, 10,   2,    0,    0,    1340,
      1341, 5,    39,   0,    0,    1341, 1342, 5,    110,  0,    0,    1342,
      1354, 3,    82,   41,   0,    1343, 1344, 3,    78,   39,   0,    1344,
      1345, 5,    110,  0,    0,    1345, 1346, 3,    76,   38,   0,    1346,
      1347, 3,    80,   40,   0,    1347, 1354, 1,    0,    0,    0,    1348,
      1349, 5,    127,  0,    0,    1349, 1350, 3,    78,   39,   0,    1350,
      1351, 5,    110,  0,    0,    1351, 1352, 3,    82,   41,   0,    1352,
      1354, 1,    0,    0,    0,    1353, 1340, 1,    0,    0,    0,    1353,
      1343, 1,    0,    0,    0,    1353, 1348, 1,    0,    0,    0,    1354,
      1356, 1,    0,    0,    0,    1355, 1339, 1,    0,    0,    0,    1356,
      1359, 1,    0,    0,    0,    1357, 1355, 1,    0,    0,    0,    1357,
      1358, 1,    0,    0,    0,    1358, 77,   1,    0,    0,    0,    1359,
      1357, 1,    0,    0,    0,    1360, 1362, 5,    99,   0,    0,    1361,
      1360, 1,    0,    0,    0,    1361, 1362, 1,    0,    0,    0,    1362,
      1376, 1,    0,    0,    0,    1363, 1365, 5,    115,  0,    0,    1364,
      1366, 5,    148,  0,    0,    1365, 1364, 1,    0,    0,    0,    1365,
      1366, 1,    0,    0,    0,    1366, 1376, 1,    0,    0,    0,    1367,
      1369, 5,    173,  0,    0,    1368, 1370, 5,    148,  0,    0,    1369,
      1368, 1,    0,    0,    0,    1369, 1370, 1,    0,    0,    0,    1370,
      1376, 1,    0,    0,    0,    1371, 1373, 5,    82,   0,    0,    1372,
      1374, 5,    148,  0,    0,    1373, 1372, 1,    0,    0,    0,    1373,
      1374, 1,    0,    0,    0,    1374, 1376, 1,    0,    0,    0,    1375,
      1361, 1,    0,    0,    0,    1375, 1363, 1,    0,    0,    0,    1375,
      1367, 1,    0,    0,    0,    1375, 1371, 1,    0,    0,    0,    1376,
      79,   1,    0,    0,    0,    1377, 1378, 5,    141,  0,    0,    1378,
      1392, 3,    94,   47,   0,    1379, 1380, 5,    221,  0,    0,    1380,
      1381, 5,    2,    0,    0,    1381, 1386, 3,    162,  81,   0,    1382,
      1383, 5,    4,    0,    0,    1383, 1385, 3,    162,  81,   0,    1384,
      1382, 1,    0,    0,    0,    1385, 1388, 1,    0,    0,    0,    1386,
      1384, 1,    0,    0,    0,    1386, 1387, 1,    0,    0,    0,    1387,
      1389, 1,    0,    0,    0,    1388, 1386, 1,    0,    0,    0,    1389,
      1390, 5,    3,    0,    0,    1390, 1392, 1,    0,    0,    0,    1391,
      1377, 1,    0,    0,    0,    1391, 1379, 1,    0,    0,    0,    1392,
      81,   1,    0,    0,    0,    1393, 1400, 3,    86,   43,   0,    1394,
      1395, 5,    200,  0,    0,    1395, 1396, 3,    84,   42,   0,    1396,
      1397, 5,    2,    0,    0,    1397, 1398, 3,    92,   46,   0,    1398,
      1399, 5,    3,    0,    0,    1399, 1401, 1,    0,    0,    0,    1400,
      1394, 1,    0,    0,    0,    1400, 1401, 1,    0,    0,    0,    1401,
      83,   1,    0,    0,    0,    1402, 1403, 7,    10,   0,    0,    1403,
      85,   1,    0,    0,    0,    1404, 1412, 3,    90,   45,   0,    1405,
      1407, 5,    19,   0,    0,    1406, 1405, 1,    0,    0,    0,    1406,
      1407, 1,    0,    0,    0,    1407, 1408, 1,    0,    0,    0,    1408,
      1410, 3,    162,  81,   0,    1409, 1411, 3,    88,   44,   0,    1410,
      1409, 1,    0,    0,    0,    1410, 1411, 1,    0,    0,    0,    1411,
      1413, 1,    0,    0,    0,    1412, 1406, 1,    0,    0,    0,    1412,
      1413, 1,    0,    0,    0,    1413, 87,   1,    0,    0,    0,    1414,
      1415, 5,    2,    0,    0,    1415, 1420, 3,    162,  81,   0,    1416,
      1417, 5,    4,    0,    0,    1417, 1419, 3,    162,  81,   0,    1418,
      1416, 1,    0,    0,    0,    1419, 1422, 1,    0,    0,    0,    1420,
      1418, 1,    0,    0,    0,    1420, 1421, 1,    0,    0,    0,    1421,
      1423, 1,    0,    0,    0,    1422, 1420, 1,    0,    0,    0,    1423,
      1424, 5,    3,    0,    0,    1424, 89,   1,    0,    0,    0,    1425,
      1427, 3,    150,  75,   0,    1426, 1428, 3,    152,  76,   0,    1427,
      1426, 1,    0,    0,    0,    1427, 1428, 1,    0,    0,    0,    1428,
      1458, 1,    0,    0,    0,    1429, 1430, 5,    2,    0,    0,    1430,
      1431, 3,    8,    4,    0,    1431, 1432, 5,    3,    0,    0,    1432,
      1458, 1,    0,    0,    0,    1433, 1434, 5,    217,  0,    0,    1434,
      1435, 5,    2,    0,    0,    1435, 1440, 3,    92,   46,   0,    1436,
      1437, 5,    4,    0,    0,    1437, 1439, 3,    92,   46,   0,    1438,
      1436, 1,    0,    0,    0,    1439, 1442, 1,    0,    0,    0,    1440,
      1438, 1,    0,    0,    0,    1440, 1441, 1,    0,    0,    0,    1441,
      1443, 1,    0,    0,    0,    1442, 1440, 1,    0,    0,    0,    1443,
      1446, 5,    3,    0,    0,    1444, 1445, 5,    229,  0,    0,    1445,
      1447, 5,    147,  0,    0,    1446, 1444, 1,    0,    0,    0,    1446,
      1447, 1,    0,    0,    0,    1447, 1458, 1,    0,    0,    0,    1448,
      1449, 5,    114,  0,    0,    1449, 1450, 5,    2,    0,    0,    1450,
      1451, 3,    8,    4,    0,    1451, 1452, 5,    3,    0,    0,    1452,
      1458, 1,    0,    0,    0,    1453, 1454, 5,    2,    0,    0,    1454,
      1455, 3,    76,   38,   0,    1455, 1456, 5,    3,    0,    0,    1456,
      1458, 1,    0,    0,    0,    1457, 1425, 1,    0,    0,    0,    1457,
      1429, 1,    0,    0,    0,    1457, 1433, 1,    0,    0,    0,    1457,
      1448, 1,    0,    0,    0,    1457, 1453, 1,    0,    0,    0,    1458,
      91,   1,    0,    0,    0,    1459, 1460, 3,    94,   47,   0,    1460,
      93,   1,    0,    0,    0,    1461, 1462, 6,    47,   -1,   0,    1462,
      1464, 3,    98,   49,   0,    1463, 1465, 3,    96,   48,   0,    1464,
      1463, 1,    0,    0,    0,    1464, 1465, 1,    0,    0,    0,    1465,
      1469, 1,    0,    0,    0,    1466, 1467, 5,    135,  0,    0,    1467,
      1469, 3,    94,   47,   3,    1468, 1461, 1,    0,    0,    0,    1468,
      1466, 1,    0,    0,    0,    1469, 1478, 1,    0,    0,    0,    1470,
      1471, 10,   2,    0,    0,    1471, 1472, 5,    16,   0,    0,    1472,
      1477, 3,    94,   47,   3,    1473, 1474, 10,   1,    0,    0,    1474,
      1475, 5,    145,  0,    0,    1475, 1477, 3,    94,   47,   2,    1476,
      1470, 1,    0,    0,    0,    1476, 1473, 1,    0,    0,    0,    1477,
      1480, 1,    0,    0,    0,    1478, 1476, 1,    0,    0,    0,    1478,
      1479, 1,    0,    0,    0,    1479, 95,   1,    0,    0,    0,    1480,
      1478, 1,    0,    0,    0,    1481, 1482, 3,    108,  54,   0,    1482,
      1483, 3,    98,   49,   0,    1483, 1543, 1,    0,    0,    0,    1484,
      1485, 3,    108,  54,   0,    1485, 1486, 3,    110,  55,   0,    1486,
      1487, 5,    2,    0,    0,    1487, 1488, 3,    8,    4,    0,    1488,
      1489, 5,    3,    0,    0,    1489, 1543, 1,    0,    0,    0,    1490,
      1492, 5,    135,  0,    0,    1491, 1490, 1,    0,    0,    0,    1491,
      1492, 1,    0,    0,    0,    1492, 1493, 1,    0,    0,    0,    1493,
      1494, 5,    24,   0,    0,    1494, 1495, 3,    98,   49,   0,    1495,
      1496, 5,    16,   0,    0,    1496, 1497, 3,    98,   49,   0,    1497,
      1543, 1,    0,    0,    0,    1498, 1500, 5,    135,  0,    0,    1499,
      1498, 1,    0,    0,    0,    1499, 1500, 1,    0,    0,    0,    1500,
      1501, 1,    0,    0,    0,    1501, 1502, 5,    97,   0,    0,    1502,
      1503, 5,    2,    0,    0,    1503, 1508, 3,    92,   46,   0,    1504,
      1505, 5,    4,    0,    0,    1505, 1507, 3,    92,   46,   0,    1506,
      1504, 1,    0,    0,    0,    1507, 1510, 1,    0,    0,    0,    1508,
      1506, 1,    0,    0,    0,    1508, 1509, 1,    0,    0,    0,    1509,
      1511, 1,    0,    0,    0,    1510, 1508, 1,    0,    0,    0,    1511,
      1512, 5,    3,    0,    0,    1512, 1543, 1,    0,    0,    0,    1513,
      1515, 5,    135,  0,    0,    1514, 1513, 1,    0,    0,    0,    1514,
      1515, 1,    0,    0,    0,    1515, 1516, 1,    0,    0,    0,    1516,
      1517, 5,    97,   0,    0,    1517, 1518, 5,    2,    0,    0,    1518,
      1519, 3,    8,    4,    0,    1519, 1520, 5,    3,    0,    0,    1520,
      1543, 1,    0,    0,    0,    1521, 1523, 5,    135,  0,    0,    1522,
      1521, 1,    0,    0,    0,    1522, 1523, 1,    0,    0,    0,    1523,
      1524, 1,    0,    0,    0,    1524, 1525, 5,    117,  0,    0,    1525,
      1528, 3,    98,   49,   0,    1526, 1527, 5,    64,   0,    0,    1527,
      1529, 3,    98,   49,   0,    1528, 1526, 1,    0,    0,    0,    1528,
      1529, 1,    0,    0,    0,    1529, 1543, 1,    0,    0,    0,    1530,
      1532, 5,    107,  0,    0,    1531, 1533, 5,    135,  0,    0,    1532,
      1531, 1,    0,    0,    0,    1532, 1533, 1,    0,    0,    0,    1533,
      1534, 1,    0,    0,    0,    1534, 1543, 5,    136,  0,    0,    1535,
      1537, 5,    107,  0,    0,    1536, 1538, 5,    135,  0,    0,    1537,
      1536, 1,    0,    0,    0,    1537, 1538, 1,    0,    0,    0,    1538,
      1539, 1,    0,    0,    0,    1539, 1540, 5,    57,   0,    0,    1540,
      1541, 5,    81,   0,    0,    1541, 1543, 3,    98,   49,   0,    1542,
      1481, 1,    0,    0,    0,    1542, 1484, 1,    0,    0,    0,    1542,
      1491, 1,    0,    0,    0,    1542, 1499, 1,    0,    0,    0,    1542,
      1514, 1,    0,    0,    0,    1542, 1522, 1,    0,    0,    0,    1542,
      1530, 1,    0,    0,    0,    1542, 1535, 1,    0,    0,    0,    1543,
      97,   1,    0,    0,    0,    1544, 1545, 6,    49,   -1,   0,    1545,
      1549, 3,    100,  50,   0,    1546, 1547, 7,    11,   0,    0,    1547,
      1549, 3,    98,   49,   4,    1548, 1544, 1,    0,    0,    0,    1548,
      1546, 1,    0,    0,    0,    1549, 1564, 1,    0,    0,    0,    1550,
      1551, 10,   3,    0,    0,    1551, 1552, 7,    12,   0,    0,    1552,
      1563, 3,    98,   49,   4,    1553, 1554, 10,   2,    0,    0,    1554,
      1555, 7,    11,   0,    0,    1555, 1563, 3,    98,   49,   3,    1556,
      1557, 10,   1,    0,    0,    1557, 1558, 5,    245,  0,    0,    1558,
      1563, 3,    98,   49,   2,    1559, 1560, 10,   5,    0,    0,    1560,
      1561, 5,    21,   0,    0,    1561, 1563, 3,    106,  53,   0,    1562,
      1550, 1,    0,    0,    0,    1562, 1553, 1,    0,    0,    0,    1562,
      1556, 1,    0,    0,    0,    1562, 1559, 1,    0,    0,    0,    1563,
      1566, 1,    0,    0,    0,    1564, 1562, 1,    0,    0,    0,    1564,
      1565, 1,    0,    0,    0,    1565, 99,   1,    0,    0,    0,    1566,
      1564, 1,    0,    0,    0,    1567, 1568, 6,    50,   -1,   0,    1568,
      1824, 5,    136,  0,    0,    1569, 1824, 3,    114,  57,   0,    1570,
      1571, 3,    122,  61,   0,    1571, 1572, 3,    102,  51,   0,    1572,
      1824, 1,    0,    0,    0,    1573, 1574, 5,    258,  0,    0,    1574,
      1824, 3,    102,  51,   0,    1575, 1824, 3,    164,  82,   0,    1576,
      1824, 3,    112,  56,   0,    1577, 1824, 3,    102,  51,   0,    1578,
      1824, 5,    248,  0,    0,    1579, 1824, 5,    5,    0,    0,    1580,
      1581, 5,    153,  0,    0,    1581, 1582, 5,    2,    0,    0,    1582,
      1583, 3,    98,   49,   0,    1583, 1584, 5,    97,   0,    0,    1584,
      1585, 3,    98,   49,   0,    1585, 1586, 5,    3,    0,    0,    1586,
      1824, 1,    0,    0,    0,    1587, 1588, 5,    2,    0,    0,    1588,
      1591, 3,    92,   46,   0,    1589, 1590, 5,    4,    0,    0,    1590,
      1592, 3,    92,   46,   0,    1591, 1589, 1,    0,    0,    0,    1592,
      1593, 1,    0,    0,    0,    1593, 1591, 1,    0,    0,    0,    1593,
      1594, 1,    0,    0,    0,    1594, 1595, 1,    0,    0,    0,    1595,
      1596, 5,    3,    0,    0,    1596, 1824, 1,    0,    0,    0,    1597,
      1598, 5,    178,  0,    0,    1598, 1599, 5,    2,    0,    0,    1599,
      1604, 3,    92,   46,   0,    1600, 1601, 5,    4,    0,    0,    1601,
      1603, 3,    92,   46,   0,    1602, 1600, 1,    0,    0,    0,    1603,
      1606, 1,    0,    0,    0,    1604, 1602, 1,    0,    0,    0,    1604,
      1605, 1,    0,    0,    0,    1605, 1607, 1,    0,    0,    0,    1606,
      1604, 1,    0,    0,    0,    1607, 1608, 5,    3,    0,    0,    1608,
      1824, 1,    0,    0,    0,    1609, 1610, 5,    178,  0,    0,    1610,
      1611, 5,    2,    0,    0,    1611, 1612, 3,    92,   46,   0,    1612,
      1613, 5,    19,   0,    0,    1613, 1621, 3,    162,  81,   0,    1614,
      1615, 5,    4,    0,    0,    1615, 1616, 3,    92,   46,   0,    1616,
      1617, 5,    19,   0,    0,    1617, 1618, 3,    162,  81,   0,    1618,
      1620, 1,    0,    0,    0,    1619, 1614, 1,    0,    0,    0,    1620,
      1623, 1,    0,    0,    0,    1621, 1619, 1,    0,    0,    0,    1621,
      1622, 1,    0,    0,    0,    1622, 1624, 1,    0,    0,    0,    1623,
      1621, 1,    0,    0,    0,    1624, 1625, 5,    3,    0,    0,    1625,
      1824, 1,    0,    0,    0,    1626, 1627, 3,    150,  75,   0,    1627,
      1628, 5,    2,    0,    0,    1628, 1629, 5,    242,  0,    0,    1629,
      1631, 5,    3,    0,    0,    1630, 1632, 3,    130,  65,   0,    1631,
      1630, 1,    0,    0,    0,    1631, 1632, 1,    0,    0,    0,    1632,
      1634, 1,    0,    0,    0,    1633, 1635, 3,    132,  66,   0,    1634,
      1633, 1,    0,    0,    0,    1634, 1635, 1,    0,    0,    0,    1635,
      1824, 1,    0,    0,    0,    1636, 1637, 3,    150,  75,   0,    1637,
      1649, 5,    2,    0,    0,    1638, 1640, 3,    64,   32,   0,    1639,
      1638, 1,    0,    0,    0,    1639, 1640, 1,    0,    0,    0,    1640,
      1641, 1,    0,    0,    0,    1641, 1646, 3,    92,   46,   0,    1642,
      1643, 5,    4,    0,    0,    1643, 1645, 3,    92,   46,   0,    1644,
      1642, 1,    0,    0,    0,    1645, 1648, 1,    0,    0,    0,    1646,
      1644, 1,    0,    0,    0,    1646, 1647, 1,    0,    0,    0,    1647,
      1650, 1,    0,    0,    0,    1648, 1646, 1,    0,    0,    0,    1649,
      1639, 1,    0,    0,    0,    1649, 1650, 1,    0,    0,    0,    1650,
      1661, 1,    0,    0,    0,    1651, 1652, 5,    146,  0,    0,    1652,
      1653, 5,    25,   0,    0,    1653, 1658, 3,    52,   26,   0,    1654,
      1655, 5,    4,    0,    0,    1655, 1657, 3,    52,   26,   0,    1656,
      1654, 1,    0,    0,    0,    1657, 1660, 1,    0,    0,    0,    1658,
      1656, 1,    0,    0,    0,    1658, 1659, 1,    0,    0,    0,    1659,
      1662, 1,    0,    0,    0,    1660, 1658, 1,    0,    0,    0,    1661,
      1651, 1,    0,    0,    0,    1661, 1662, 1,    0,    0,    0,    1662,
      1663, 1,    0,    0,    0,    1663, 1665, 5,    3,    0,    0,    1664,
      1666, 3,    130,  65,   0,    1665, 1664, 1,    0,    0,    0,    1665,
      1666, 1,    0,    0,    0,    1666, 1671, 1,    0,    0,    0,    1667,
      1669, 3,    104,  52,   0,    1668, 1667, 1,    0,    0,    0,    1668,
      1669, 1,    0,    0,    0,    1669, 1670, 1,    0,    0,    0,    1670,
      1672, 3,    132,  66,   0,    1671, 1668, 1,    0,    0,    0,    1671,
      1672, 1,    0,    0,    0,    1672, 1824, 1,    0,    0,    0,    1673,
      1674, 3,    162,  81,   0,    1674, 1675, 5,    6,    0,    0,    1675,
      1676, 3,    92,   46,   0,    1676, 1824, 1,    0,    0,    0,    1677,
      1686, 5,    2,    0,    0,    1678, 1683, 3,    162,  81,   0,    1679,
      1680, 5,    4,    0,    0,    1680, 1682, 3,    162,  81,   0,    1681,
      1679, 1,    0,    0,    0,    1682, 1685, 1,    0,    0,    0,    1683,
      1681, 1,    0,    0,    0,    1683, 1684, 1,    0,    0,    0,    1684,
      1687, 1,    0,    0,    0,    1685, 1683, 1,    0,    0,    0,    1686,
      1678, 1,    0,    0,    0,    1686, 1687, 1,    0,    0,    0,    1687,
      1688, 1,    0,    0,    0,    1688, 1689, 5,    3,    0,    0,    1689,
      1690, 5,    6,    0,    0,    1690, 1824, 3,    92,   46,   0,    1691,
      1692, 5,    2,    0,    0,    1692, 1693, 3,    8,    4,    0,    1693,
      1694, 5,    3,    0,    0,    1694, 1824, 1,    0,    0,    0,    1695,
      1696, 5,    70,   0,    0,    1696, 1697, 5,    2,    0,    0,    1697,
      1698, 3,    8,    4,    0,    1698, 1699, 5,    3,    0,    0,    1699,
      1824, 1,    0,    0,    0,    1700, 1701, 5,    29,   0,    0,    1701,
      1703, 3,    98,   49,   0,    1702, 1704, 3,    128,  64,   0,    1703,
      1702, 1,    0,    0,    0,    1704, 1705, 1,    0,    0,    0,    1705,
      1703, 1,    0,    0,    0,    1705, 1706, 1,    0,    0,    0,    1706,
      1709, 1,    0,    0,    0,    1707, 1708, 5,    60,   0,    0,    1708,
      1710, 3,    92,   46,   0,    1709, 1707, 1,    0,    0,    0,    1709,
      1710, 1,    0,    0,    0,    1710, 1711, 1,    0,    0,    0,    1711,
      1712, 5,    62,   0,    0,    1712, 1824, 1,    0,    0,    0,    1713,
      1715, 5,    29,   0,    0,    1714, 1716, 3,    128,  64,   0,    1715,
      1714, 1,    0,    0,    0,    1716, 1717, 1,    0,    0,    0,    1717,
      1715, 1,    0,    0,    0,    1717, 1718, 1,    0,    0,    0,    1718,
      1721, 1,    0,    0,    0,    1719, 1720, 5,    60,   0,    0,    1720,
      1722, 3,    92,   46,   0,    1721, 1719, 1,    0,    0,    0,    1721,
      1722, 1,    0,    0,    0,    1722, 1723, 1,    0,    0,    0,    1723,
      1724, 5,    62,   0,    0,    1724, 1824, 1,    0,    0,    0,    1725,
      1726, 5,    30,   0,    0,    1726, 1727, 5,    2,    0,    0,    1727,
      1728, 3,    92,   46,   0,    1728, 1729, 5,    19,   0,    0,    1729,
      1730, 3,    122,  61,   0,    1730, 1731, 5,    3,    0,    0,    1731,
      1824, 1,    0,    0,    0,    1732, 1733, 5,    210,  0,    0,    1733,
      1734, 5,    2,    0,    0,    1734, 1735, 3,    92,   46,   0,    1735,
      1736, 5,    19,   0,    0,    1736, 1737, 3,    122,  61,   0,    1737,
      1738, 5,    3,    0,    0,    1738, 1824, 1,    0,    0,    0,    1739,
      1740, 5,    18,   0,    0,    1740, 1749, 5,    7,    0,    0,    1741,
      1746, 3,    92,   46,   0,    1742, 1743, 5,    4,    0,    0,    1743,
      1745, 3,    92,   46,   0,    1744, 1742, 1,    0,    0,    0,    1745,
      1748, 1,    0,    0,    0,    1746, 1744, 1,    0,    0,    0,    1746,
      1747, 1,    0,    0,    0,    1747, 1750, 1,    0,    0,    0,    1748,
      1746, 1,    0,    0,    0,    1749, 1741, 1,    0,    0,    0,    1749,
      1750, 1,    0,    0,    0,    1750, 1751, 1,    0,    0,    0,    1751,
      1824, 5,    8,    0,    0,    1752, 1824, 3,    162,  81,   0,    1753,
      1824, 5,    42,   0,    0,    1754, 1758, 5,    44,   0,    0,    1755,
      1756, 5,    2,    0,    0,    1756, 1757, 5,    249,  0,    0,    1757,
      1759, 5,    3,    0,    0,    1758, 1755, 1,    0,    0,    0,    1758,
      1759, 1,    0,    0,    0,    1759, 1824, 1,    0,    0,    0,    1760,
      1764, 5,    45,   0,    0,    1761, 1762, 5,    2,    0,    0,    1762,
      1763, 5,    249,  0,    0,    1763, 1765, 5,    3,    0,    0,    1764,
      1761, 1,    0,    0,    0,    1764, 1765, 1,    0,    0,    0,    1765,
      1824, 1,    0,    0,    0,    1766, 1770, 5,    119,  0,    0,    1767,
      1768, 5,    2,    0,    0,    1768, 1769, 5,    249,  0,    0,    1769,
      1771, 5,    3,    0,    0,    1770, 1767, 1,    0,    0,    0,    1770,
      1771, 1,    0,    0,    0,    1771, 1824, 1,    0,    0,    0,    1772,
      1776, 5,    120,  0,    0,    1773, 1774, 5,    2,    0,    0,    1774,
      1775, 5,    249,  0,    0,    1775, 1777, 5,    3,    0,    0,    1776,
      1773, 1,    0,    0,    0,    1776, 1777, 1,    0,    0,    0,    1777,
      1824, 1,    0,    0,    0,    1778, 1824, 5,    46,   0,    0,    1779,
      1780, 5,    194,  0,    0,    1780, 1781, 5,    2,    0,    0,    1781,
      1782, 3,    98,   49,   0,    1782, 1783, 5,    81,   0,    0,    1783,
      1786, 3,    98,   49,   0,    1784, 1785, 5,    79,   0,    0,    1785,
      1787, 3,    98,   49,   0,    1786, 1784, 1,    0,    0,    0,    1786,
      1787, 1,    0,    0,    0,    1787, 1788, 1,    0,    0,    0,    1788,
      1789, 5,    3,    0,    0,    1789, 1824, 1,    0,    0,    0,    1790,
      1791, 5,    134,  0,    0,    1791, 1792, 5,    2,    0,    0,    1792,
      1795, 3,    98,   49,   0,    1793, 1794, 5,    4,    0,    0,    1794,
      1796, 3,    118,  59,   0,    1795, 1793, 1,    0,    0,    0,    1795,
      1796, 1,    0,    0,    0,    1796, 1797, 1,    0,    0,    0,    1797,
      1798, 5,    3,    0,    0,    1798, 1824, 1,    0,    0,    0,    1799,
      1800, 5,    72,   0,    0,    1800, 1801, 5,    2,    0,    0,    1801,
      1802, 3,    162,  81,   0,    1802, 1803, 5,    81,   0,    0,    1803,
      1804, 3,    98,   49,   0,    1804, 1805, 5,    3,    0,    0,    1805,
      1824, 1,    0,    0,    0,    1806, 1807, 5,    2,    0,    0,    1807,
      1808, 3,    92,   46,   0,    1808, 1809, 5,    3,    0,    0,    1809,
      1824, 1,    0,    0,    0,    1810, 1811, 5,    91,   0,    0,    1811,
      1820, 5,    2,    0,    0,    1812, 1817, 3,    150,  75,   0,    1813,
      1814, 5,    4,    0,    0,    1814, 1816, 3,    150,  75,   0,    1815,
      1813, 1,    0,    0,    0,    1816, 1819, 1,    0,    0,    0,    1817,
      1815, 1,    0,    0,    0,    1817, 1818, 1,    0,    0,    0,    1818,
      1821, 1,    0,    0,    0,    1819, 1817, 1,    0,    0,    0,    1820,
      1812, 1,    0,    0,    0,    1820, 1821, 1,    0,    0,    0,    1821,
      1822, 1,    0,    0,    0,    1822, 1824, 5,    3,    0,    0,    1823,
      1567, 1,    0,    0,    0,    1823, 1569, 1,    0,    0,    0,    1823,
      1570, 1,    0,    0,    0,    1823, 1573, 1,    0,    0,    0,    1823,
      1575, 1,    0,    0,    0,    1823, 1576, 1,    0,    0,    0,    1823,
      1577, 1,    0,    0,    0,    1823, 1578, 1,    0,    0,    0,    1823,
      1579, 1,    0,    0,    0,    1823, 1580, 1,    0,    0,    0,    1823,
      1587, 1,    0,    0,    0,    1823, 1597, 1,    0,    0,    0,    1823,
      1609, 1,    0,    0,    0,    1823, 1626, 1,    0,    0,    0,    1823,
      1636, 1,    0,    0,    0,    1823, 1673, 1,    0,    0,    0,    1823,
      1677, 1,    0,    0,    0,    1823, 1691, 1,    0,    0,    0,    1823,
      1695, 1,    0,    0,    0,    1823, 1700, 1,    0,    0,    0,    1823,
      1713, 1,    0,    0,    0,    1823, 1725, 1,    0,    0,    0,    1823,
      1732, 1,    0,    0,    0,    1823, 1739, 1,    0,    0,    0,    1823,
      1752, 1,    0,    0,    0,    1823, 1753, 1,    0,    0,    0,    1823,
      1754, 1,    0,    0,    0,    1823, 1760, 1,    0,    0,    0,    1823,
      1766, 1,    0,    0,    0,    1823, 1772, 1,    0,    0,    0,    1823,
      1778, 1,    0,    0,    0,    1823, 1779, 1,    0,    0,    0,    1823,
      1790, 1,    0,    0,    0,    1823, 1799, 1,    0,    0,    0,    1823,
      1806, 1,    0,    0,    0,    1823, 1810, 1,    0,    0,    0,    1824,
      1851, 1,    0,    0,    0,    1825, 1826, 10,   15,   0,    0,    1826,
      1827, 5,    7,    0,    0,    1827, 1828, 3,    98,   49,   0,    1828,
      1829, 5,    8,    0,    0,    1829, 1850, 1,    0,    0,    0,    1830,
      1831, 10,   13,   0,    0,    1831, 1832, 5,    1,    0,    0,    1832,
      1833, 3,    162,  81,   0,    1833, 1842, 5,    2,    0,    0,    1834,
      1839, 3,    92,   46,   0,    1835, 1836, 5,    4,    0,    0,    1836,
      1838, 3,    92,   46,   0,    1837, 1835, 1,    0,    0,    0,    1838,
      1841, 1,    0,    0,    0,    1839, 1837, 1,    0,    0,    0,    1839,
      1840, 1,    0,    0,    0,    1840, 1843, 1,    0,    0,    0,    1841,
      1839, 1,    0,    0,    0,    1842, 1834, 1,    0,    0,    0,    1842,
      1843, 1,    0,    0,    0,    1843, 1844, 1,    0,    0,    0,    1844,
      1845, 5,    3,    0,    0,    1845, 1850, 1,    0,    0,    0,    1846,
      1847, 10,   12,   0,    0,    1847, 1848, 5,    1,    0,    0,    1848,
      1850, 3,    162,  81,   0,    1849, 1825, 1,    0,    0,    0,    1849,
      1830, 1,    0,    0,    0,    1849, 1846, 1,    0,    0,    0,    1850,
      1853, 1,    0,    0,    0,    1851, 1849, 1,    0,    0,    0,    1851,
      1852, 1,    0,    0,    0,    1852, 101,  1,    0,    0,    0,    1853,
      1851, 1,    0,    0,    0,    1854, 1861, 5,    246,  0,    0,    1855,
      1858, 5,    247,  0,    0,    1856, 1857, 5,    212,  0,    0,    1857,
      1859, 5,    246,  0,    0,    1858, 1856, 1,    0,    0,    0,    1858,
      1859, 1,    0,    0,    0,    1859, 1861, 1,    0,    0,    0,    1860,
      1854, 1,    0,    0,    0,    1860, 1855, 1,    0,    0,    0,    1861,
      103,  1,    0,    0,    0,    1862, 1863, 5,    96,   0,    0,    1863,
      1867, 5,    138,  0,    0,    1864, 1865, 5,    168,  0,    0,    1865,
      1867, 5,    138,  0,    0,    1866, 1862, 1,    0,    0,    0,    1866,
      1864, 1,    0,    0,    0,    1867, 105,  1,    0,    0,    0,    1868,
      1869, 5,    204,  0,    0,    1869, 1870, 5,    233,  0,    0,    1870,
      1875, 3,    114,  57,   0,    1871, 1872, 5,    204,  0,    0,    1872,
      1873, 5,    233,  0,    0,    1873, 1875, 3,    102,  51,   0,    1874,
      1868, 1,    0,    0,    0,    1874, 1871, 1,    0,    0,    0,    1875,
      107,  1,    0,    0,    0,    1876, 1877, 7,    13,   0,    0,    1877,
      109,  1,    0,    0,    0,    1878, 1879, 7,    14,   0,    0,    1879,
      111,  1,    0,    0,    0,    1880, 1881, 7,    15,   0,    0,    1881,
      113,  1,    0,    0,    0,    1882, 1884, 5,    103,  0,    0,    1883,
      1885, 7,    11,   0,    0,    1884, 1883, 1,    0,    0,    0,    1884,
      1885, 1,    0,    0,    0,    1885, 1886, 1,    0,    0,    0,    1886,
      1887, 3,    102,  51,   0,    1887, 1890, 3,    116,  58,   0,    1888,
      1889, 5,    206,  0,    0,    1889, 1891, 3,    116,  58,   0,    1890,
      1888, 1,    0,    0,    0,    1890, 1891, 1,    0,    0,    0,    1891,
      115,  1,    0,    0,    0,    1892, 1893, 7,    16,   0,    0,    1893,
      117,  1,    0,    0,    0,    1894, 1895, 7,    17,   0,    0,    1895,
      119,  1,    0,    0,    0,    1896, 1905, 5,    2,    0,    0,    1897,
      1902, 3,    122,  61,   0,    1898, 1899, 5,    4,    0,    0,    1899,
      1901, 3,    122,  61,   0,    1900, 1898, 1,    0,    0,    0,    1901,
      1904, 1,    0,    0,    0,    1902, 1900, 1,    0,    0,    0,    1902,
      1903, 1,    0,    0,    0,    1903, 1906, 1,    0,    0,    0,    1904,
      1902, 1,    0,    0,    0,    1905, 1897, 1,    0,    0,    0,    1905,
      1906, 1,    0,    0,    0,    1906, 1907, 1,    0,    0,    0,    1907,
      1908, 5,    3,    0,    0,    1908, 121,  1,    0,    0,    0,    1909,
      1910, 6,    61,   -1,   0,    1910, 1911, 5,    18,   0,    0,    1911,
      1912, 5,    236,  0,    0,    1912, 1913, 3,    122,  61,   0,    1913,
      1914, 5,    238,  0,    0,    1914, 1957, 1,    0,    0,    0,    1915,
      1916, 5,    122,  0,    0,    1916, 1917, 5,    236,  0,    0,    1917,
      1918, 3,    122,  61,   0,    1918, 1919, 5,    4,    0,    0,    1919,
      1920, 3,    122,  61,   0,    1920, 1921, 5,    238,  0,    0,    1921,
      1957, 1,    0,    0,    0,    1922, 1923, 5,    178,  0,    0,    1923,
      1924, 5,    2,    0,    0,    1924, 1925, 3,    162,  81,   0,    1925,
      1932, 3,    122,  61,   0,    1926, 1927, 5,    4,    0,    0,    1927,
      1928, 3,    162,  81,   0,    1928, 1929, 3,    122,  61,   0,    1929,
      1931, 1,    0,    0,    0,    1930, 1926, 1,    0,    0,    0,    1931,
      1934, 1,    0,    0,    0,    1932, 1930, 1,    0,    0,    0,    1932,
      1933, 1,    0,    0,    0,    1933, 1935, 1,    0,    0,    0,    1934,
      1932, 1,    0,    0,    0,    1935, 1936, 5,    3,    0,    0,    1936,
      1957, 1,    0,    0,    0,    1937, 1949, 3,    126,  63,   0,    1938,
      1939, 5,    2,    0,    0,    1939, 1944, 3,    124,  62,   0,    1940,
      1941, 5,    4,    0,    0,    1941, 1943, 3,    124,  62,   0,    1942,
      1940, 1,    0,    0,    0,    1943, 1946, 1,    0,    0,    0,    1944,
      1942, 1,    0,    0,    0,    1944, 1945, 1,    0,    0,    0,    1945,
      1947, 1,    0,    0,    0,    1946, 1944, 1,    0,    0,    0,    1947,
      1948, 5,    3,    0,    0,    1948, 1950, 1,    0,    0,    0,    1949,
      1938, 1,    0,    0,    0,    1949, 1950, 1,    0,    0,    0,    1950,
      1957, 1,    0,    0,    0,    1951, 1952, 5,    103,  0,    0,    1952,
      1953, 3,    116,  58,   0,    1953, 1954, 5,    206,  0,    0,    1954,
      1955, 3,    116,  58,   0,    1955, 1957, 1,    0,    0,    0,    1956,
      1909, 1,    0,    0,    0,    1956, 1915, 1,    0,    0,    0,    1956,
      1922, 1,    0,    0,    0,    1956, 1937, 1,    0,    0,    0,    1956,
      1951, 1,    0,    0,    0,    1957, 1962, 1,    0,    0,    0,    1958,
      1959, 10,   6,    0,    0,    1959, 1961, 5,    18,   0,    0,    1960,
      1958, 1,    0,    0,    0,    1961, 1964, 1,    0,    0,    0,    1962,
      1960, 1,    0,    0,    0,    1962, 1963, 1,    0,    0,    0,    1963,
      123,  1,    0,    0,    0,    1964, 1962, 1,    0,    0,    0,    1965,
      1968, 5,    249,  0,    0,    1966, 1968, 3,    122,  61,   0,    1967,
      1965, 1,    0,    0,    0,    1967, 1966, 1,    0,    0,    0,    1968,
      125,  1,    0,    0,    0,    1969, 1974, 5,    256,  0,    0,    1970,
      1974, 5,    257,  0,    0,    1971, 1974, 5,    258,  0,    0,    1972,
      1974, 3,    150,  75,   0,    1973, 1969, 1,    0,    0,    0,    1973,
      1970, 1,    0,    0,    0,    1973, 1971, 1,    0,    0,    0,    1973,
      1972, 1,    0,    0,    0,    1974, 127,  1,    0,    0,    0,    1975,
      1976, 5,    227,  0,    0,    1976, 1977, 3,    92,   46,   0,    1977,
      1978, 5,    203,  0,    0,    1978, 1979, 3,    92,   46,   0,    1979,
      129,  1,    0,    0,    0,    1980, 1981, 5,    76,   0,    0,    1981,
      1982, 5,    2,    0,    0,    1982, 1983, 5,    228,  0,    0,    1983,
      1984, 3,    94,   47,   0,    1984, 1985, 5,    3,    0,    0,    1985,
      131,  1,    0,    0,    0,    1986, 1987, 5,    150,  0,    0,    1987,
      1998, 5,    2,    0,    0,    1988, 1989, 5,    151,  0,    0,    1989,
      1990, 5,    25,   0,    0,    1990, 1995, 3,    92,   46,   0,    1991,
      1992, 5,    4,    0,    0,    1992, 1994, 3,    92,   46,   0,    1993,
      1991, 1,    0,    0,    0,    1994, 1997, 1,    0,    0,    0,    1995,
      1993, 1,    0,    0,    0,    1995, 1996, 1,    0,    0,    0,    1996,
      1999, 1,    0,    0,    0,    1997, 1995, 1,    0,    0,    0,    1998,
      1988, 1,    0,    0,    0,    1998, 1999, 1,    0,    0,    0,    1999,
      2010, 1,    0,    0,    0,    2000, 2001, 5,    146,  0,    0,    2001,
      2002, 5,    25,   0,    0,    2002, 2007, 3,    52,   26,   0,    2003,
      2004, 5,    4,    0,    0,    2004, 2006, 3,    52,   26,   0,    2005,
      2003, 1,    0,    0,    0,    2006, 2009, 1,    0,    0,    0,    2007,
      2005, 1,    0,    0,    0,    2007, 2008, 1,    0,    0,    0,    2008,
      2011, 1,    0,    0,    0,    2009, 2007, 1,    0,    0,    0,    2010,
      2000, 1,    0,    0,    0,    2010, 2011, 1,    0,    0,    0,    2011,
      2013, 1,    0,    0,    0,    2012, 2014, 3,    134,  67,   0,    2013,
      2012, 1,    0,    0,    0,    2013, 2014, 1,    0,    0,    0,    2014,
      2015, 1,    0,    0,    0,    2015, 2016, 5,    3,    0,    0,    2016,
      133,  1,    0,    0,    0,    2017, 2018, 5,    159,  0,    0,    2018,
      2042, 3,    136,  68,   0,    2019, 2020, 5,    179,  0,    0,    2020,
      2042, 3,    136,  68,   0,    2021, 2022, 5,    92,   0,    0,    2022,
      2042, 3,    136,  68,   0,    2023, 2024, 5,    159,  0,    0,    2024,
      2025, 5,    24,   0,    0,    2025, 2026, 3,    136,  68,   0,    2026,
      2027, 5,    16,   0,    0,    2027, 2028, 3,    136,  68,   0,    2028,
      2042, 1,    0,    0,    0,    2029, 2030, 5,    179,  0,    0,    2030,
      2031, 5,    24,   0,    0,    2031, 2032, 3,    136,  68,   0,    2032,
      2033, 5,    16,   0,    0,    2033, 2034, 3,    136,  68,   0,    2034,
      2042, 1,    0,    0,    0,    2035, 2036, 5,    92,   0,    0,    2036,
      2037, 5,    24,   0,    0,    2037, 2038, 3,    136,  68,   0,    2038,
      2039, 5,    16,   0,    0,    2039, 2040, 3,    136,  68,   0,    2040,
      2042, 1,    0,    0,    0,    2041, 2017, 1,    0,    0,    0,    2041,
      2019, 1,    0,    0,    0,    2041, 2021, 1,    0,    0,    0,    2041,
      2023, 1,    0,    0,    0,    2041, 2029, 1,    0,    0,    0,    2041,
      2035, 1,    0,    0,    0,    2042, 135,  1,    0,    0,    0,    2043,
      2044, 5,    213,  0,    0,    2044, 2053, 5,    154,  0,    0,    2045,
      2046, 5,    213,  0,    0,    2046, 2053, 5,    78,   0,    0,    2047,
      2048, 5,    41,   0,    0,    2048, 2053, 5,    178,  0,    0,    2049,
      2050, 3,    92,   46,   0,    2050, 2051, 7,    18,   0,    0,    2051,
      2053, 1,    0,    0,    0,    2052, 2043, 1,    0,    0,    0,    2052,
      2045, 1,    0,    0,    0,    2052, 2047, 1,    0,    0,    0,    2052,
      2049, 1,    0,    0,    0,    2053, 137,  1,    0,    0,    0,    2054,
      2055, 3,    162,  81,   0,    2055, 2056, 5,    234,  0,    0,    2056,
      2057, 3,    92,   46,   0,    2057, 139,  1,    0,    0,    0,    2058,
      2059, 5,    80,   0,    0,    2059, 2063, 7,    19,   0,    0,    2060,
      2061, 5,    211,  0,    0,    2061, 2063, 7,    20,   0,    0,    2062,
      2058, 1,    0,    0,    0,    2062, 2060, 1,    0,    0,    0,    2063,
      141,  1,    0,    0,    0,    2064, 2065, 5,    108,  0,    0,    2065,
      2066, 5,    116,  0,    0,    2066, 2070, 3,    144,  72,   0,    2067,
      2068, 5,    160,  0,    0,    2068, 2070, 7,    21,   0,    0,    2069,
      2064, 1,    0,    0,    0,    2069, 2067, 1,    0,    0,    0,    2070,
      143,  1,    0,    0,    0,    2071, 2072, 5,    160,  0,    0,    2072,
      2079, 5,    214,  0,    0,    2073, 2074, 5,    160,  0,    0,    2074,
      2079, 5,    36,   0,    0,    2075, 2076, 5,    165,  0,    0,    2076,
      2079, 5,    160,  0,    0,    2077, 2079, 5,    185,  0,    0,    2078,
      2071, 1,    0,    0,    0,    2078, 2073, 1,    0,    0,    0,    2078,
      2075, 1,    0,    0,    0,    2078, 2077, 1,    0,    0,    0,    2079,
      145,  1,    0,    0,    0,    2080, 2086, 3,    92,   46,   0,    2081,
      2082, 3,    162,  81,   0,    2082, 2083, 5,    9,    0,    0,    2083,
      2084, 3,    92,   46,   0,    2084, 2086, 1,    0,    0,    0,    2085,
      2080, 1,    0,    0,    0,    2085, 2081, 1,    0,    0,    0,    2086,
      147,  1,    0,    0,    0,    2087, 2092, 5,    184,  0,    0,    2088,
      2092, 5,    52,   0,    0,    2089, 2092, 5,    101,  0,    0,    2090,
      2092, 3,    162,  81,   0,    2091, 2087, 1,    0,    0,    0,    2091,
      2088, 1,    0,    0,    0,    2091, 2089, 1,    0,    0,    0,    2091,
      2090, 1,    0,    0,    0,    2092, 149,  1,    0,    0,    0,    2093,
      2098, 3,    162,  81,   0,    2094, 2095, 5,    1,    0,    0,    2095,
      2097, 3,    162,  81,   0,    2096, 2094, 1,    0,    0,    0,    2097,
      2100, 1,    0,    0,    0,    2098, 2096, 1,    0,    0,    0,    2098,
      2099, 1,    0,    0,    0,    2099, 151,  1,    0,    0,    0,    2100,
      2098, 1,    0,    0,    0,    2101, 2102, 5,    79,   0,    0,    2102,
      2103, 7,    22,   0,    0,    2103, 2104, 3,    154,  77,   0,    2104,
      2105, 3,    98,   49,   0,    2105, 153,  1,    0,    0,    0,    2106,
      2107, 5,    19,   0,    0,    2107, 2110, 5,    139,  0,    0,    2108,
      2110, 5,    22,   0,    0,    2109, 2106, 1,    0,    0,    0,    2109,
      2108, 1,    0,    0,    0,    2110, 155,  1,    0,    0,    0,    2111,
      2115, 5,    46,   0,    0,    2112, 2115, 5,    43,   0,    0,    2113,
      2115, 3,    158,  79,   0,    2114, 2111, 1,    0,    0,    0,    2114,
      2112, 1,    0,    0,    0,    2114, 2113, 1,    0,    0,    0,    2115,
      157,  1,    0,    0,    0,    2116, 2117, 5,    220,  0,    0,    2117,
      2122, 3,    162,  81,   0,    2118, 2119, 5,    174,  0,    0,    2119,
      2122, 3,    162,  81,   0,    2120, 2122, 3,    162,  81,   0,    2121,
      2116, 1,    0,    0,    0,    2121, 2118, 1,    0,    0,    0,    2121,
      2120, 1,    0,    0,    0,    2122, 159,  1,    0,    0,    0,    2123,
      2128, 3,    162,  81,   0,    2124, 2125, 5,    4,    0,    0,    2125,
      2127, 3,    162,  81,   0,    2126, 2124, 1,    0,    0,    0,    2127,
      2130, 1,    0,    0,    0,    2128, 2126, 1,    0,    0,    0,    2128,
      2129, 1,    0,    0,    0,    2129, 161,  1,    0,    0,    0,    2130,
      2128, 1,    0,    0,    0,    2131, 2137, 5,    252,  0,    0,    2132,
      2137, 5,    254,  0,    0,    2133, 2137, 3,    184,  92,   0,    2134,
      2137, 5,    255,  0,    0,    2135, 2137, 5,    253,  0,    0,    2136,
      2131, 1,    0,    0,    0,    2136, 2132, 1,    0,    0,    0,    2136,
      2133, 1,    0,    0,    0,    2136, 2134, 1,    0,    0,    0,    2136,
      2135, 1,    0,    0,    0,    2137, 163,  1,    0,    0,    0,    2138,
      2142, 5,    250,  0,    0,    2139, 2142, 5,    251,  0,    0,    2140,
      2142, 5,    249,  0,    0,    2141, 2138, 1,    0,    0,    0,    2141,
      2139, 1,    0,    0,    0,    2141, 2140, 1,    0,    0,    0,    2142,
      165,  1,    0,    0,    0,    2143, 2146, 3,    168,  84,   0,    2144,
      2146, 3,    170,  85,   0,    2145, 2143, 1,    0,    0,    0,    2145,
      2144, 1,    0,    0,    0,    2146, 167,  1,    0,    0,    0,    2147,
      2148, 5,    37,   0,    0,    2148, 2149, 3,    162,  81,   0,    2149,
      2150, 3,    170,  85,   0,    2150, 169,  1,    0,    0,    0,    2151,
      2152, 3,    172,  86,   0,    2152, 2154, 3,    88,   44,   0,    2153,
      2155, 3,    174,  87,   0,    2154, 2153, 1,    0,    0,    0,    2154,
      2155, 1,    0,    0,    0,    2155, 171,  1,    0,    0,    0,    2156,
      2160, 5,    216,  0,    0,    2157, 2158, 5,    156,  0,    0,    2158,
      2160, 5,    111,  0,    0,    2159, 2156, 1,    0,    0,    0,    2159,
      2157, 1,    0,    0,    0,    2160, 173,  1,    0,    0,    0,    2161,
      2163, 3,    176,  88,   0,    2162, 2161, 1,    0,    0,    0,    2163,
      2166, 1,    0,    0,    0,    2164, 2162, 1,    0,    0,    0,    2164,
      2165, 1,    0,    0,    0,    2165, 175,  1,    0,    0,    0,    2166,
      2164, 1,    0,    0,    0,    2167, 2171, 3,    180,  90,   0,    2168,
      2171, 3,    178,  89,   0,    2169, 2171, 3,    182,  91,   0,    2170,
      2167, 1,    0,    0,    0,    2170, 2168, 1,    0,    0,    0,    2170,
      2169, 1,    0,    0,    0,    2171, 177,  1,    0,    0,    0,    2172,
      2176, 5,    163,  0,    0,    2173, 2174, 5,    135,  0,    0,    2174,
      2176, 5,    163,  0,    0,    2175, 2172, 1,    0,    0,    0,    2175,
      2173, 1,    0,    0,    0,    2176, 179,  1,    0,    0,    0,    2177,
      2178, 7,    23,   0,    0,    2178, 181,  1,    0,    0,    0,    2179,
      2183, 5,    63,   0,    0,    2180, 2181, 5,    135,  0,    0,    2181,
      2183, 5,    63,   0,    0,    2182, 2179, 1,    0,    0,    0,    2182,
      2180, 1,    0,    0,    0,    2183, 183,  1,    0,    0,    0,    2184,
      2185, 7,    24,   0,    0,    2185, 185,  1,    0,    0,    0,    279,
      208,  213,  219,  223,  237,  241,  245,  249,  257,  261,  264,  271,
      280,  286,  290,  296,  303,  312,  321,  332,  339,  349,  356,  364,
      372,  380,  390,  397,  405,  410,  421,  426,  437,  448,  460,  466,
      471,  477,  486,  497,  506,  511,  515,  523,  530,  543,  546,  556,
      559,  566,  575,  581,  586,  590,  600,  603,  613,  626,  632,  637,
      643,  652,  658,  665,  673,  678,  682,  690,  696,  703,  708,  712,
      722,  725,  729,  732,  740,  745,  766,  772,  778,  780,  786,  792,
      794,  802,  804,  823,  828,  835,  847,  849,  857,  859,  877,  880,
      884,  888,  906,  909,  925,  930,  932,  935,  941,  948,  954,  960,
      964,  968,  974,  982,  997,  1004, 1009, 1016, 1024, 1028, 1033, 1044,
      1056, 1059, 1064, 1066, 1075, 1077, 1085, 1091, 1094, 1096, 1108, 1115,
      1119, 1123, 1127, 1134, 1138, 1146, 1149, 1153, 1158, 1162, 1170, 1175,
      1180, 1184, 1186, 1189, 1196, 1207, 1210, 1220, 1223, 1234, 1239, 1247,
      1250, 1254, 1258, 1271, 1275, 1284, 1291, 1295, 1298, 1300, 1304, 1306,
      1315, 1327, 1353, 1357, 1361, 1365, 1369, 1373, 1375, 1386, 1391, 1400,
      1406, 1410, 1412, 1420, 1427, 1440, 1446, 1457, 1464, 1468, 1476, 1478,
      1491, 1499, 1508, 1514, 1522, 1528, 1532, 1537, 1542, 1548, 1562, 1564,
      1593, 1604, 1621, 1631, 1634, 1639, 1646, 1649, 1658, 1661, 1665, 1668,
      1671, 1683, 1686, 1705, 1709, 1717, 1721, 1746, 1749, 1758, 1764, 1770,
      1776, 1786, 1795, 1817, 1820, 1823, 1839, 1842, 1849, 1851, 1858, 1860,
      1866, 1874, 1884, 1890, 1902, 1905, 1932, 1944, 1949, 1956, 1962, 1967,
      1973, 1995, 1998, 2007, 2010, 2013, 2041, 2052, 2062, 2069, 2078, 2085,
      2091, 2098, 2109, 2114, 2121, 2128, 2136, 2141, 2145, 2154, 2159, 2164,
      2170, 2175, 2182};
  staticData->serializedATN = antlr4::atn::SerializedATNView(
      serializedATNSegment,
      sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) {
    staticData->decisionToDFA.emplace_back(
        staticData->atn->getDecisionState(i), i);
  }
  prestosqlParserStaticData = std::move(staticData);
}

} // namespace

PrestoSqlParser::PrestoSqlParser(TokenStream* input)
    : PrestoSqlParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

PrestoSqlParser::PrestoSqlParser(
    TokenStream* input,
    const antlr4::atn::ParserATNSimulatorOptions& options)
    : Parser(input) {
  PrestoSqlParser::initialize();
  _interpreter = new atn::ParserATNSimulator(
      this,
      *prestosqlParserStaticData->atn,
      prestosqlParserStaticData->decisionToDFA,
      prestosqlParserStaticData->sharedContextCache,
      options);
}

PrestoSqlParser::~PrestoSqlParser() {
  delete _interpreter;
}

const atn::ATN& PrestoSqlParser::getATN() const {
  return *prestosqlParserStaticData->atn;
}

std::string PrestoSqlParser::getGrammarFileName() const {
  return "PrestoSql.g4";
}

const std::vector<std::string>& PrestoSqlParser::getRuleNames() const {
  return prestosqlParserStaticData->ruleNames;
}

const dfa::Vocabulary& PrestoSqlParser::getVocabulary() const {
  return prestosqlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView PrestoSqlParser::getSerializedATN() const {
  return prestosqlParserStaticData->serializedATN;
}

//----------------- SingleStatementContext
//------------------------------------------------------------------

PrestoSqlParser::SingleStatementContext::SingleStatementContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::StatementContext*
PrestoSqlParser::SingleStatementContext::statement() {
  return getRuleContext<PrestoSqlParser::StatementContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SingleStatementContext::EOF() {
  return getToken(PrestoSqlParser::EOF, 0);
}

size_t PrestoSqlParser::SingleStatementContext::getRuleIndex() const {
  return PrestoSqlParser::RuleSingleStatement;
}

void PrestoSqlParser::SingleStatementContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingleStatement(this);
}

void PrestoSqlParser::SingleStatementContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingleStatement(this);
}

std::any PrestoSqlParser::SingleStatementContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSingleStatement(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::SingleStatementContext* PrestoSqlParser::singleStatement() {
  SingleStatementContext* _localctx =
      _tracker.createInstance<SingleStatementContext>(_ctx, getState());
  enterRule(_localctx, 0, PrestoSqlParser::RuleSingleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(186);
    statement();
    setState(187);
    match(PrestoSqlParser::EOF);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StandaloneExpressionContext
//------------------------------------------------------------------

PrestoSqlParser::StandaloneExpressionContext::StandaloneExpressionContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::StandaloneExpressionContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::StandaloneExpressionContext::EOF() {
  return getToken(PrestoSqlParser::EOF, 0);
}

size_t PrestoSqlParser::StandaloneExpressionContext::getRuleIndex() const {
  return PrestoSqlParser::RuleStandaloneExpression;
}

void PrestoSqlParser::StandaloneExpressionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterStandaloneExpression(this);
}

void PrestoSqlParser::StandaloneExpressionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitStandaloneExpression(this);
}

std::any PrestoSqlParser::StandaloneExpressionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitStandaloneExpression(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::StandaloneExpressionContext*
PrestoSqlParser::standaloneExpression() {
  StandaloneExpressionContext* _localctx =
      _tracker.createInstance<StandaloneExpressionContext>(_ctx, getState());
  enterRule(_localctx, 2, PrestoSqlParser::RuleStandaloneExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    expression();
    setState(190);
    match(PrestoSqlParser::EOF);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StandaloneRoutineBodyContext
//------------------------------------------------------------------

PrestoSqlParser::StandaloneRoutineBodyContext::StandaloneRoutineBodyContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::RoutineBodyContext*
PrestoSqlParser::StandaloneRoutineBodyContext::routineBody() {
  return getRuleContext<PrestoSqlParser::RoutineBodyContext>(0);
}

tree::TerminalNode* PrestoSqlParser::StandaloneRoutineBodyContext::EOF() {
  return getToken(PrestoSqlParser::EOF, 0);
}

size_t PrestoSqlParser::StandaloneRoutineBodyContext::getRuleIndex() const {
  return PrestoSqlParser::RuleStandaloneRoutineBody;
}

void PrestoSqlParser::StandaloneRoutineBodyContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterStandaloneRoutineBody(this);
}

void PrestoSqlParser::StandaloneRoutineBodyContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitStandaloneRoutineBody(this);
}

std::any PrestoSqlParser::StandaloneRoutineBodyContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitStandaloneRoutineBody(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::StandaloneRoutineBodyContext*
PrestoSqlParser::standaloneRoutineBody() {
  StandaloneRoutineBodyContext* _localctx =
      _tracker.createInstance<StandaloneRoutineBodyContext>(_ctx, getState());
  enterRule(_localctx, 4, PrestoSqlParser::RuleStandaloneRoutineBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(192);
    routineBody();
    setState(193);
    match(PrestoSqlParser::EOF);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext
//------------------------------------------------------------------

PrestoSqlParser::StatementContext::StatementContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::StatementContext::getRuleIndex() const {
  return PrestoSqlParser::RuleStatement;
}

void PrestoSqlParser::StatementContext::copyFrom(StatementContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExplainContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ExplainContext::EXPLAIN() {
  return getToken(PrestoSqlParser::EXPLAIN, 0);
}

PrestoSqlParser::StatementContext*
PrestoSqlParser::ExplainContext::statement() {
  return getRuleContext<PrestoSqlParser::StatementContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ExplainContext::ANALYZE() {
  return getToken(PrestoSqlParser::ANALYZE, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainContext::VERBOSE() {
  return getToken(PrestoSqlParser::VERBOSE, 0);
}

std::vector<PrestoSqlParser::ExplainOptionContext*>
PrestoSqlParser::ExplainContext::explainOption() {
  return getRuleContexts<PrestoSqlParser::ExplainOptionContext>();
}

PrestoSqlParser::ExplainOptionContext*
PrestoSqlParser::ExplainContext::explainOption(size_t i) {
  return getRuleContext<PrestoSqlParser::ExplainOptionContext>(i);
}

PrestoSqlParser::ExplainContext::ExplainContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ExplainContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplain(this);
}
void PrestoSqlParser::ExplainContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplain(this);
}

std::any PrestoSqlParser::ExplainContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExplain(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrepareContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::PrepareContext::PREPARE() {
  return getToken(PrestoSqlParser::PREPARE, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::PrepareContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::PrepareContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

PrestoSqlParser::StatementContext*
PrestoSqlParser::PrepareContext::statement() {
  return getRuleContext<PrestoSqlParser::StatementContext>(0);
}

PrestoSqlParser::PrepareContext::PrepareContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::PrepareContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrepare(this);
}
void PrestoSqlParser::PrepareContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrepare(this);
}

std::any PrestoSqlParser::PrepareContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitPrepare(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropMaterializedViewContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DropMaterializedViewContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode*
PrestoSqlParser::DropMaterializedViewContext::MATERIALIZED() {
  return getToken(PrestoSqlParser::MATERIALIZED, 0);
}

tree::TerminalNode* PrestoSqlParser::DropMaterializedViewContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::DropMaterializedViewContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::DropMaterializedViewContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::DropMaterializedViewContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::DropMaterializedViewContext::DropMaterializedViewContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DropMaterializedViewContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropMaterializedView(this);
}
void PrestoSqlParser::DropMaterializedViewContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropMaterializedView(this);
}

std::any PrestoSqlParser::DropMaterializedViewContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDropMaterializedView(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UseContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::UseContext::USE() {
  return getToken(PrestoSqlParser::USE, 0);
}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::UseContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext* PrestoSqlParser::UseContext::identifier(
    size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

PrestoSqlParser::UseContext::UseContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::UseContext::enterRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUse(this);
}
void PrestoSqlParser::UseContext::exitRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUse(this);
}

std::any PrestoSqlParser::UseContext::accept(tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUse(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddConstraintContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::AddConstraintContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::AddConstraintContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::AddConstraintContext::ADD() {
  return getToken(PrestoSqlParser::ADD, 0);
}

PrestoSqlParser::ConstraintSpecificationContext*
PrestoSqlParser::AddConstraintContext::constraintSpecification() {
  return getRuleContext<PrestoSqlParser::ConstraintSpecificationContext>(0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::AddConstraintContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::AddConstraintContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::AddConstraintContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::AddConstraintContext::AddConstraintContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::AddConstraintContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddConstraint(this);
}
void PrestoSqlParser::AddConstraintContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddConstraint(this);
}

std::any PrestoSqlParser::AddConstraintContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAddConstraint(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeallocateContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DeallocateContext::DEALLOCATE() {
  return getToken(PrestoSqlParser::DEALLOCATE, 0);
}

tree::TerminalNode* PrestoSqlParser::DeallocateContext::PREPARE() {
  return getToken(PrestoSqlParser::PREPARE, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::DeallocateContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::DeallocateContext::DeallocateContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DeallocateContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeallocate(this);
}
void PrestoSqlParser::DeallocateContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeallocate(this);
}

std::any PrestoSqlParser::DeallocateContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDeallocate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RenameTableContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RenameTableContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameTableContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameTableContext::RENAME() {
  return getToken(PrestoSqlParser::RENAME, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameTableContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

std::vector<PrestoSqlParser::QualifiedNameContext*>
PrestoSqlParser::RenameTableContext::qualifiedName() {
  return getRuleContexts<PrestoSqlParser::QualifiedNameContext>();
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::RenameTableContext::qualifiedName(size_t i) {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(i);
}

tree::TerminalNode* PrestoSqlParser::RenameTableContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameTableContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::RenameTableContext::RenameTableContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RenameTableContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRenameTable(this);
}
void PrestoSqlParser::RenameTableContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRenameTable(this);
}

std::any PrestoSqlParser::RenameTableContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRenameTable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CommitContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CommitContext::COMMIT() {
  return getToken(PrestoSqlParser::COMMIT, 0);
}

tree::TerminalNode* PrestoSqlParser::CommitContext::WORK() {
  return getToken(PrestoSqlParser::WORK, 0);
}

PrestoSqlParser::CommitContext::CommitContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CommitContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCommit(this);
}
void PrestoSqlParser::CommitContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCommit(this);
}

std::any PrestoSqlParser::CommitContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCommit(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CreateRoleContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CreateRoleContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateRoleContext::ROLE() {
  return getToken(PrestoSqlParser::ROLE, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::CreateRoleContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateRoleContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateRoleContext::ADMIN() {
  return getToken(PrestoSqlParser::ADMIN, 0);
}

PrestoSqlParser::GrantorContext* PrestoSqlParser::CreateRoleContext::grantor() {
  return getRuleContext<PrestoSqlParser::GrantorContext>(0);
}

PrestoSqlParser::CreateRoleContext::CreateRoleContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CreateRoleContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateRole(this);
}
void PrestoSqlParser::CreateRoleContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateRole(this);
}

std::any PrestoSqlParser::CreateRoleContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCreateRole(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowCreateFunctionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowCreateFunctionContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCreateFunctionContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCreateFunctionContext::FUNCTION() {
  return getToken(PrestoSqlParser::FUNCTION, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ShowCreateFunctionContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::TypesContext*
PrestoSqlParser::ShowCreateFunctionContext::types() {
  return getRuleContext<PrestoSqlParser::TypesContext>(0);
}

PrestoSqlParser::ShowCreateFunctionContext::ShowCreateFunctionContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowCreateFunctionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowCreateFunction(this);
}
void PrestoSqlParser::ShowCreateFunctionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowCreateFunction(this);
}

std::any PrestoSqlParser::ShowCreateFunctionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowCreateFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropColumnContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DropColumnContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::DropColumnContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::DropColumnContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode* PrestoSqlParser::DropColumnContext::COLUMN() {
  return getToken(PrestoSqlParser::COLUMN, 0);
}

std::vector<PrestoSqlParser::QualifiedNameContext*>
PrestoSqlParser::DropColumnContext::qualifiedName() {
  return getRuleContexts<PrestoSqlParser::QualifiedNameContext>();
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::DropColumnContext::qualifiedName(size_t i) {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(i);
}

std::vector<tree::TerminalNode*> PrestoSqlParser::DropColumnContext::IF() {
  return getTokens(PrestoSqlParser::IF);
}

tree::TerminalNode* PrestoSqlParser::DropColumnContext::IF(size_t i) {
  return getToken(PrestoSqlParser::IF, i);
}

std::vector<tree::TerminalNode*> PrestoSqlParser::DropColumnContext::EXISTS() {
  return getTokens(PrestoSqlParser::EXISTS);
}

tree::TerminalNode* PrestoSqlParser::DropColumnContext::EXISTS(size_t i) {
  return getToken(PrestoSqlParser::EXISTS, i);
}

PrestoSqlParser::DropColumnContext::DropColumnContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DropColumnContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropColumn(this);
}
void PrestoSqlParser::DropColumnContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropColumn(this);
}

std::any PrestoSqlParser::DropColumnContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDropColumn(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropViewContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DropViewContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode* PrestoSqlParser::DropViewContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::DropViewContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::DropViewContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::DropViewContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::DropViewContext::DropViewContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DropViewContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropView(this);
}
void PrestoSqlParser::DropViewContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropView(this);
}

std::any PrestoSqlParser::DropViewContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDropView(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowTablesContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowTablesContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowTablesContext::TABLES() {
  return getToken(PrestoSqlParser::TABLES, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ShowTablesContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ShowTablesContext::LIKE() {
  return getToken(PrestoSqlParser::LIKE, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowTablesContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowTablesContext::IN() {
  return getToken(PrestoSqlParser::IN, 0);
}

std::vector<PrestoSqlParser::StringContext*>
PrestoSqlParser::ShowTablesContext::string() {
  return getRuleContexts<PrestoSqlParser::StringContext>();
}

PrestoSqlParser::StringContext* PrestoSqlParser::ShowTablesContext::string(
    size_t i) {
  return getRuleContext<PrestoSqlParser::StringContext>(i);
}

tree::TerminalNode* PrestoSqlParser::ShowTablesContext::ESCAPE() {
  return getToken(PrestoSqlParser::ESCAPE, 0);
}

PrestoSqlParser::ShowTablesContext::ShowTablesContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowTablesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowTables(this);
}
void PrestoSqlParser::ShowTablesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowTables(this);
}

std::any PrestoSqlParser::ShowTablesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowTables(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowCatalogsContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowCatalogsContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCatalogsContext::CATALOGS() {
  return getToken(PrestoSqlParser::CATALOGS, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCatalogsContext::LIKE() {
  return getToken(PrestoSqlParser::LIKE, 0);
}

std::vector<PrestoSqlParser::StringContext*>
PrestoSqlParser::ShowCatalogsContext::string() {
  return getRuleContexts<PrestoSqlParser::StringContext>();
}

PrestoSqlParser::StringContext* PrestoSqlParser::ShowCatalogsContext::string(
    size_t i) {
  return getRuleContext<PrestoSqlParser::StringContext>(i);
}

tree::TerminalNode* PrestoSqlParser::ShowCatalogsContext::ESCAPE() {
  return getToken(PrestoSqlParser::ESCAPE, 0);
}

PrestoSqlParser::ShowCatalogsContext::ShowCatalogsContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowCatalogsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowCatalogs(this);
}
void PrestoSqlParser::ShowCatalogsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowCatalogs(this);
}

std::any PrestoSqlParser::ShowCatalogsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowCatalogs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowRolesContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowRolesContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowRolesContext::ROLES() {
  return getToken(PrestoSqlParser::ROLES, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowRolesContext::CURRENT() {
  return getToken(PrestoSqlParser::CURRENT, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ShowRolesContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ShowRolesContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowRolesContext::IN() {
  return getToken(PrestoSqlParser::IN, 0);
}

PrestoSqlParser::ShowRolesContext::ShowRolesContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowRolesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowRoles(this);
}
void PrestoSqlParser::ShowRolesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowRoles(this);
}

std::any PrestoSqlParser::ShowRolesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowRoles(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RenameColumnContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RenameColumnContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameColumnContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameColumnContext::RENAME() {
  return getToken(PrestoSqlParser::RENAME, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameColumnContext::COLUMN() {
  return getToken(PrestoSqlParser::COLUMN, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameColumnContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::RenameColumnContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::RenameColumnContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::RenameColumnContext::identifier(size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

std::vector<tree::TerminalNode*> PrestoSqlParser::RenameColumnContext::IF() {
  return getTokens(PrestoSqlParser::IF);
}

tree::TerminalNode* PrestoSqlParser::RenameColumnContext::IF(size_t i) {
  return getToken(PrestoSqlParser::IF, i);
}

std::vector<tree::TerminalNode*>
PrestoSqlParser::RenameColumnContext::EXISTS() {
  return getTokens(PrestoSqlParser::EXISTS);
}

tree::TerminalNode* PrestoSqlParser::RenameColumnContext::EXISTS(size_t i) {
  return getToken(PrestoSqlParser::EXISTS, i);
}

PrestoSqlParser::RenameColumnContext::RenameColumnContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RenameColumnContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRenameColumn(this);
}
void PrestoSqlParser::RenameColumnContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRenameColumn(this);
}

std::any PrestoSqlParser::RenameColumnContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRenameColumn(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RevokeRolesContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RevokeRolesContext::REVOKE() {
  return getToken(PrestoSqlParser::REVOKE, 0);
}

PrestoSqlParser::RolesContext* PrestoSqlParser::RevokeRolesContext::roles() {
  return getRuleContext<PrestoSqlParser::RolesContext>(0);
}

tree::TerminalNode* PrestoSqlParser::RevokeRolesContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

std::vector<PrestoSqlParser::PrincipalContext*>
PrestoSqlParser::RevokeRolesContext::principal() {
  return getRuleContexts<PrestoSqlParser::PrincipalContext>();
}

PrestoSqlParser::PrincipalContext*
PrestoSqlParser::RevokeRolesContext::principal(size_t i) {
  return getRuleContext<PrestoSqlParser::PrincipalContext>(i);
}

tree::TerminalNode* PrestoSqlParser::RevokeRolesContext::ADMIN() {
  return getToken(PrestoSqlParser::ADMIN, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeRolesContext::OPTION() {
  return getToken(PrestoSqlParser::OPTION, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeRolesContext::FOR() {
  return getToken(PrestoSqlParser::FOR, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeRolesContext::GRANTED() {
  return getToken(PrestoSqlParser::GRANTED, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeRolesContext::BY() {
  return getToken(PrestoSqlParser::BY, 0);
}

PrestoSqlParser::GrantorContext*
PrestoSqlParser::RevokeRolesContext::grantor() {
  return getRuleContext<PrestoSqlParser::GrantorContext>(0);
}

PrestoSqlParser::RevokeRolesContext::RevokeRolesContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RevokeRolesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRevokeRoles(this);
}
void PrestoSqlParser::RevokeRolesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRevokeRoles(this);
}

std::any PrestoSqlParser::RevokeRolesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRevokeRoles(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowCreateTableContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowCreateTableContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCreateTableContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCreateTableContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ShowCreateTableContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::ShowCreateTableContext::ShowCreateTableContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowCreateTableContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowCreateTable(this);
}
void PrestoSqlParser::ShowCreateTableContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowCreateTable(this);
}

std::any PrestoSqlParser::ShowCreateTableContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowCreateTable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowColumnsContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowColumnsContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowColumnsContext::COLUMNS() {
  return getToken(PrestoSqlParser::COLUMNS, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ShowColumnsContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ShowColumnsContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowColumnsContext::IN() {
  return getToken(PrestoSqlParser::IN, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowColumnsContext::DESCRIBE() {
  return getToken(PrestoSqlParser::DESCRIBE, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowColumnsContext::DESC() {
  return getToken(PrestoSqlParser::DESC, 0);
}

PrestoSqlParser::ShowColumnsContext::ShowColumnsContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowColumnsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowColumns(this);
}
void PrestoSqlParser::ShowColumnsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowColumns(this);
}

std::any PrestoSqlParser::ShowColumnsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowColumns(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowRoleGrantsContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowRoleGrantsContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowRoleGrantsContext::ROLE() {
  return getToken(PrestoSqlParser::ROLE, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowRoleGrantsContext::GRANTS() {
  return getToken(PrestoSqlParser::GRANTS, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ShowRoleGrantsContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ShowRoleGrantsContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowRoleGrantsContext::IN() {
  return getToken(PrestoSqlParser::IN, 0);
}

PrestoSqlParser::ShowRoleGrantsContext::ShowRoleGrantsContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowRoleGrantsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowRoleGrants(this);
}
void PrestoSqlParser::ShowRoleGrantsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowRoleGrants(this);
}

std::any PrestoSqlParser::ShowRoleGrantsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowRoleGrants(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddColumnContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::AddColumnContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::AddColumnContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::AddColumnContext::ADD() {
  return getToken(PrestoSqlParser::ADD, 0);
}

tree::TerminalNode* PrestoSqlParser::AddColumnContext::COLUMN() {
  return getToken(PrestoSqlParser::COLUMN, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::AddColumnContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::ColumnDefinitionContext*
PrestoSqlParser::AddColumnContext::columnDefinition() {
  return getRuleContext<PrestoSqlParser::ColumnDefinitionContext>(0);
}

std::vector<tree::TerminalNode*> PrestoSqlParser::AddColumnContext::IF() {
  return getTokens(PrestoSqlParser::IF);
}

tree::TerminalNode* PrestoSqlParser::AddColumnContext::IF(size_t i) {
  return getToken(PrestoSqlParser::IF, i);
}

std::vector<tree::TerminalNode*> PrestoSqlParser::AddColumnContext::EXISTS() {
  return getTokens(PrestoSqlParser::EXISTS);
}

tree::TerminalNode* PrestoSqlParser::AddColumnContext::EXISTS(size_t i) {
  return getToken(PrestoSqlParser::EXISTS, i);
}

tree::TerminalNode* PrestoSqlParser::AddColumnContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

PrestoSqlParser::AddColumnContext::AddColumnContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::AddColumnContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddColumn(this);
}
void PrestoSqlParser::AddColumnContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddColumn(this);
}

std::any PrestoSqlParser::AddColumnContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAddColumn(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ResetSessionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ResetSessionContext::RESET() {
  return getToken(PrestoSqlParser::RESET, 0);
}

tree::TerminalNode* PrestoSqlParser::ResetSessionContext::SESSION() {
  return getToken(PrestoSqlParser::SESSION, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ResetSessionContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::ResetSessionContext::ResetSessionContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ResetSessionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterResetSession(this);
}
void PrestoSqlParser::ResetSessionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitResetSession(this);
}

std::any PrestoSqlParser::ResetSessionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitResetSession(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropConstraintContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DropConstraintContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::DropConstraintContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::DropConstraintContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode* PrestoSqlParser::DropConstraintContext::CONSTRAINT() {
  return getToken(PrestoSqlParser::CONSTRAINT, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::DropConstraintContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::DropConstraintContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

std::vector<tree::TerminalNode*> PrestoSqlParser::DropConstraintContext::IF() {
  return getTokens(PrestoSqlParser::IF);
}

tree::TerminalNode* PrestoSqlParser::DropConstraintContext::IF(size_t i) {
  return getToken(PrestoSqlParser::IF, i);
}

std::vector<tree::TerminalNode*>
PrestoSqlParser::DropConstraintContext::EXISTS() {
  return getTokens(PrestoSqlParser::EXISTS);
}

tree::TerminalNode* PrestoSqlParser::DropConstraintContext::EXISTS(size_t i) {
  return getToken(PrestoSqlParser::EXISTS, i);
}

PrestoSqlParser::DropConstraintContext::DropConstraintContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DropConstraintContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropConstraint(this);
}
void PrestoSqlParser::DropConstraintContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropConstraint(this);
}

std::any PrestoSqlParser::DropConstraintContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDropConstraint(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InsertIntoContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::InsertIntoContext::INSERT() {
  return getToken(PrestoSqlParser::INSERT, 0);
}

tree::TerminalNode* PrestoSqlParser::InsertIntoContext::INTO() {
  return getToken(PrestoSqlParser::INTO, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::InsertIntoContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::QueryContext* PrestoSqlParser::InsertIntoContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

PrestoSqlParser::ColumnAliasesContext*
PrestoSqlParser::InsertIntoContext::columnAliases() {
  return getRuleContext<PrestoSqlParser::ColumnAliasesContext>(0);
}

PrestoSqlParser::InsertIntoContext::InsertIntoContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::InsertIntoContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterInsertInto(this);
}
void PrestoSqlParser::InsertIntoContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitInsertInto(this);
}

std::any PrestoSqlParser::InsertIntoContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitInsertInto(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowSessionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowSessionContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowSessionContext::SESSION() {
  return getToken(PrestoSqlParser::SESSION, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowSessionContext::LIKE() {
  return getToken(PrestoSqlParser::LIKE, 0);
}

std::vector<PrestoSqlParser::StringContext*>
PrestoSqlParser::ShowSessionContext::string() {
  return getRuleContexts<PrestoSqlParser::StringContext>();
}

PrestoSqlParser::StringContext* PrestoSqlParser::ShowSessionContext::string(
    size_t i) {
  return getRuleContext<PrestoSqlParser::StringContext>(i);
}

tree::TerminalNode* PrestoSqlParser::ShowSessionContext::ESCAPE() {
  return getToken(PrestoSqlParser::ESCAPE, 0);
}

PrestoSqlParser::ShowSessionContext::ShowSessionContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowSessionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowSession(this);
}
void PrestoSqlParser::ShowSessionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowSession(this);
}

std::any PrestoSqlParser::ShowSessionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowSession(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CreateSchemaContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CreateSchemaContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateSchemaContext::SCHEMA() {
  return getToken(PrestoSqlParser::SCHEMA, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::CreateSchemaContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateSchemaContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateSchemaContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateSchemaContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateSchemaContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

PrestoSqlParser::PropertiesContext*
PrestoSqlParser::CreateSchemaContext::properties() {
  return getRuleContext<PrestoSqlParser::PropertiesContext>(0);
}

PrestoSqlParser::CreateSchemaContext::CreateSchemaContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CreateSchemaContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateSchema(this);
}
void PrestoSqlParser::CreateSchemaContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateSchema(this);
}

std::any PrestoSqlParser::CreateSchemaContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCreateSchema(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExecuteContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ExecuteContext::EXECUTE() {
  return getToken(PrestoSqlParser::EXECUTE, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ExecuteContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ExecuteContext::USING() {
  return getToken(PrestoSqlParser::USING, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::ExecuteContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext* PrestoSqlParser::ExecuteContext::expression(
    size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

PrestoSqlParser::ExecuteContext::ExecuteContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ExecuteContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExecute(this);
}
void PrestoSqlParser::ExecuteContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExecute(this);
}

std::any PrestoSqlParser::ExecuteContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExecute(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RenameSchemaContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RenameSchemaContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameSchemaContext::SCHEMA() {
  return getToken(PrestoSqlParser::SCHEMA, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::RenameSchemaContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::RenameSchemaContext::RENAME() {
  return getToken(PrestoSqlParser::RENAME, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameSchemaContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::RenameSchemaContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::RenameSchemaContext::RenameSchemaContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RenameSchemaContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRenameSchema(this);
}
void PrestoSqlParser::RenameSchemaContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRenameSchema(this);
}

std::any PrestoSqlParser::RenameSchemaContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRenameSchema(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropRoleContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DropRoleContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode* PrestoSqlParser::DropRoleContext::ROLE() {
  return getToken(PrestoSqlParser::ROLE, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::DropRoleContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::DropRoleContext::DropRoleContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DropRoleContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropRole(this);
}
void PrestoSqlParser::DropRoleContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropRole(this);
}

std::any PrestoSqlParser::DropRoleContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDropRole(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AnalyzeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::AnalyzeContext::ANALYZE() {
  return getToken(PrestoSqlParser::ANALYZE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::AnalyzeContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::AnalyzeContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

PrestoSqlParser::PropertiesContext*
PrestoSqlParser::AnalyzeContext::properties() {
  return getRuleContext<PrestoSqlParser::PropertiesContext>(0);
}

PrestoSqlParser::AnalyzeContext::AnalyzeContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::AnalyzeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAnalyze(this);
}
void PrestoSqlParser::AnalyzeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAnalyze(this);
}

std::any PrestoSqlParser::AnalyzeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAnalyze(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SetRoleContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::SetRoleContext::SET() {
  return getToken(PrestoSqlParser::SET, 0);
}

tree::TerminalNode* PrestoSqlParser::SetRoleContext::ROLE() {
  return getToken(PrestoSqlParser::ROLE, 0);
}

tree::TerminalNode* PrestoSqlParser::SetRoleContext::ALL() {
  return getToken(PrestoSqlParser::ALL, 0);
}

tree::TerminalNode* PrestoSqlParser::SetRoleContext::NONE() {
  return getToken(PrestoSqlParser::NONE, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::SetRoleContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::SetRoleContext::SetRoleContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SetRoleContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetRole(this);
}
void PrestoSqlParser::SetRoleContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetRole(this);
}

std::any PrestoSqlParser::SetRoleContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSetRole(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CreateFunctionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CreateFunctionContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateFunctionContext::FUNCTION() {
  return getToken(PrestoSqlParser::FUNCTION, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateFunctionContext::RETURNS() {
  return getToken(PrestoSqlParser::RETURNS, 0);
}

PrestoSqlParser::RoutineCharacteristicsContext*
PrestoSqlParser::CreateFunctionContext::routineCharacteristics() {
  return getRuleContext<PrestoSqlParser::RoutineCharacteristicsContext>(0);
}

PrestoSqlParser::RoutineBodyContext*
PrestoSqlParser::CreateFunctionContext::routineBody() {
  return getRuleContext<PrestoSqlParser::RoutineBodyContext>(0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::CreateFunctionContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::TypeContext* PrestoSqlParser::CreateFunctionContext::type() {
  return getRuleContext<PrestoSqlParser::TypeContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateFunctionContext::OR() {
  return getToken(PrestoSqlParser::OR, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateFunctionContext::REPLACE() {
  return getToken(PrestoSqlParser::REPLACE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateFunctionContext::TEMPORARY() {
  return getToken(PrestoSqlParser::TEMPORARY, 0);
}

std::vector<PrestoSqlParser::SqlParameterDeclarationContext*>
PrestoSqlParser::CreateFunctionContext::sqlParameterDeclaration() {
  return getRuleContexts<PrestoSqlParser::SqlParameterDeclarationContext>();
}

PrestoSqlParser::SqlParameterDeclarationContext*
PrestoSqlParser::CreateFunctionContext::sqlParameterDeclaration(size_t i) {
  return getRuleContext<PrestoSqlParser::SqlParameterDeclarationContext>(i);
}

tree::TerminalNode* PrestoSqlParser::CreateFunctionContext::COMMENT() {
  return getToken(PrestoSqlParser::COMMENT, 0);
}

PrestoSqlParser::StringContext*
PrestoSqlParser::CreateFunctionContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

PrestoSqlParser::CreateFunctionContext::CreateFunctionContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CreateFunctionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateFunction(this);
}
void PrestoSqlParser::CreateFunctionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateFunction(this);
}

std::any PrestoSqlParser::CreateFunctionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCreateFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowGrantsContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowGrantsContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowGrantsContext::GRANTS() {
  return getToken(PrestoSqlParser::GRANTS, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowGrantsContext::ON() {
  return getToken(PrestoSqlParser::ON, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ShowGrantsContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ShowGrantsContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

PrestoSqlParser::ShowGrantsContext::ShowGrantsContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowGrantsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowGrants(this);
}
void PrestoSqlParser::ShowGrantsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowGrants(this);
}

std::any PrestoSqlParser::ShowGrantsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowGrants(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropSchemaContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DropSchemaContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode* PrestoSqlParser::DropSchemaContext::SCHEMA() {
  return getToken(PrestoSqlParser::SCHEMA, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::DropSchemaContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::DropSchemaContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::DropSchemaContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

tree::TerminalNode* PrestoSqlParser::DropSchemaContext::CASCADE() {
  return getToken(PrestoSqlParser::CASCADE, 0);
}

tree::TerminalNode* PrestoSqlParser::DropSchemaContext::RESTRICT() {
  return getToken(PrestoSqlParser::RESTRICT, 0);
}

PrestoSqlParser::DropSchemaContext::DropSchemaContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DropSchemaContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropSchema(this);
}
void PrestoSqlParser::DropSchemaContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropSchema(this);
}

std::any PrestoSqlParser::DropSchemaContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDropSchema(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowCreateViewContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowCreateViewContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCreateViewContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCreateViewContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ShowCreateViewContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::ShowCreateViewContext::ShowCreateViewContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowCreateViewContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowCreateView(this);
}
void PrestoSqlParser::ShowCreateViewContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowCreateView(this);
}

std::any PrestoSqlParser::ShowCreateViewContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowCreateView(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CreateTableContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CreateTableContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::CreateTableContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

std::vector<PrestoSqlParser::TableElementContext*>
PrestoSqlParser::CreateTableContext::tableElement() {
  return getRuleContexts<PrestoSqlParser::TableElementContext>();
}

PrestoSqlParser::TableElementContext*
PrestoSqlParser::CreateTableContext::tableElement(size_t i) {
  return getRuleContext<PrestoSqlParser::TableElementContext>(i);
}

tree::TerminalNode* PrestoSqlParser::CreateTableContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableContext::COMMENT() {
  return getToken(PrestoSqlParser::COMMENT, 0);
}

PrestoSqlParser::StringContext* PrestoSqlParser::CreateTableContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

PrestoSqlParser::PropertiesContext*
PrestoSqlParser::CreateTableContext::properties() {
  return getRuleContext<PrestoSqlParser::PropertiesContext>(0);
}

PrestoSqlParser::CreateTableContext::CreateTableContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CreateTableContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateTable(this);
}
void PrestoSqlParser::CreateTableContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateTable(this);
}

std::any PrestoSqlParser::CreateTableContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCreateTable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StartTransactionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::StartTransactionContext::START() {
  return getToken(PrestoSqlParser::START, 0);
}

tree::TerminalNode* PrestoSqlParser::StartTransactionContext::TRANSACTION() {
  return getToken(PrestoSqlParser::TRANSACTION, 0);
}

std::vector<PrestoSqlParser::TransactionModeContext*>
PrestoSqlParser::StartTransactionContext::transactionMode() {
  return getRuleContexts<PrestoSqlParser::TransactionModeContext>();
}

PrestoSqlParser::TransactionModeContext*
PrestoSqlParser::StartTransactionContext::transactionMode(size_t i) {
  return getRuleContext<PrestoSqlParser::TransactionModeContext>(i);
}

PrestoSqlParser::StartTransactionContext::StartTransactionContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::StartTransactionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterStartTransaction(this);
}
void PrestoSqlParser::StartTransactionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitStartTransaction(this);
}

std::any PrestoSqlParser::StartTransactionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitStartTransaction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CreateTableAsSelectContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::CreateTableAsSelectContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

PrestoSqlParser::QueryContext*
PrestoSqlParser::CreateTableAsSelectContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::ColumnAliasesContext*
PrestoSqlParser::CreateTableAsSelectContext::columnAliases() {
  return getRuleContext<PrestoSqlParser::ColumnAliasesContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::COMMENT() {
  return getToken(PrestoSqlParser::COMMENT, 0);
}

PrestoSqlParser::StringContext*
PrestoSqlParser::CreateTableAsSelectContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

std::vector<tree::TerminalNode*>
PrestoSqlParser::CreateTableAsSelectContext::WITH() {
  return getTokens(PrestoSqlParser::WITH);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::WITH(
    size_t i) {
  return getToken(PrestoSqlParser::WITH, i);
}

PrestoSqlParser::PropertiesContext*
PrestoSqlParser::CreateTableAsSelectContext::properties() {
  return getRuleContext<PrestoSqlParser::PropertiesContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::DATA() {
  return getToken(PrestoSqlParser::DATA, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTableAsSelectContext::NO() {
  return getToken(PrestoSqlParser::NO, 0);
}

PrestoSqlParser::CreateTableAsSelectContext::CreateTableAsSelectContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CreateTableAsSelectContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateTableAsSelect(this);
}
void PrestoSqlParser::CreateTableAsSelectContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateTableAsSelect(this);
}

std::any PrestoSqlParser::CreateTableAsSelectContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCreateTableAsSelect(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowStatsContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowStatsContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowStatsContext::STATS() {
  return getToken(PrestoSqlParser::STATS, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowStatsContext::FOR() {
  return getToken(PrestoSqlParser::FOR, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ShowStatsContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::ShowStatsContext::ShowStatsContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowStatsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowStats(this);
}
void PrestoSqlParser::ShowStatsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowStats(this);
}

std::any PrestoSqlParser::ShowStatsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowStats(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropFunctionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DropFunctionContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode* PrestoSqlParser::DropFunctionContext::FUNCTION() {
  return getToken(PrestoSqlParser::FUNCTION, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::DropFunctionContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::DropFunctionContext::TEMPORARY() {
  return getToken(PrestoSqlParser::TEMPORARY, 0);
}

tree::TerminalNode* PrestoSqlParser::DropFunctionContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::DropFunctionContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::TypesContext* PrestoSqlParser::DropFunctionContext::types() {
  return getRuleContext<PrestoSqlParser::TypesContext>(0);
}

PrestoSqlParser::DropFunctionContext::DropFunctionContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DropFunctionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropFunction(this);
}
void PrestoSqlParser::DropFunctionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropFunction(this);
}

std::any PrestoSqlParser::DropFunctionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDropFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RevokeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RevokeContext::REVOKE() {
  return getToken(PrestoSqlParser::REVOKE, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeContext::ON() {
  return getToken(PrestoSqlParser::ON, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::RevokeContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::RevokeContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

PrestoSqlParser::PrincipalContext* PrestoSqlParser::RevokeContext::principal() {
  return getRuleContext<PrestoSqlParser::PrincipalContext>(0);
}

std::vector<PrestoSqlParser::PrivilegeContext*>
PrestoSqlParser::RevokeContext::privilege() {
  return getRuleContexts<PrestoSqlParser::PrivilegeContext>();
}

PrestoSqlParser::PrivilegeContext* PrestoSqlParser::RevokeContext::privilege(
    size_t i) {
  return getRuleContext<PrestoSqlParser::PrivilegeContext>(i);
}

tree::TerminalNode* PrestoSqlParser::RevokeContext::ALL() {
  return getToken(PrestoSqlParser::ALL, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeContext::PRIVILEGES() {
  return getToken(PrestoSqlParser::PRIVILEGES, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeContext::GRANT() {
  return getToken(PrestoSqlParser::GRANT, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeContext::OPTION() {
  return getToken(PrestoSqlParser::OPTION, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeContext::FOR() {
  return getToken(PrestoSqlParser::FOR, 0);
}

tree::TerminalNode* PrestoSqlParser::RevokeContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

PrestoSqlParser::RevokeContext::RevokeContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RevokeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRevoke(this);
}
void PrestoSqlParser::RevokeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRevoke(this);
}

std::any PrestoSqlParser::RevokeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRevoke(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UpdateContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::UpdateContext::UPDATE() {
  return getToken(PrestoSqlParser::UPDATE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::UpdateContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::UpdateContext::SET() {
  return getToken(PrestoSqlParser::SET, 0);
}

std::vector<PrestoSqlParser::UpdateAssignmentContext*>
PrestoSqlParser::UpdateContext::updateAssignment() {
  return getRuleContexts<PrestoSqlParser::UpdateAssignmentContext>();
}

PrestoSqlParser::UpdateAssignmentContext*
PrestoSqlParser::UpdateContext::updateAssignment(size_t i) {
  return getRuleContext<PrestoSqlParser::UpdateAssignmentContext>(i);
}

tree::TerminalNode* PrestoSqlParser::UpdateContext::WHERE() {
  return getToken(PrestoSqlParser::WHERE, 0);
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::UpdateContext::booleanExpression() {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(0);
}

PrestoSqlParser::UpdateContext::UpdateContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::UpdateContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUpdate(this);
}
void PrestoSqlParser::UpdateContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUpdate(this);
}

std::any PrestoSqlParser::UpdateContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUpdate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CreateTypeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CreateTypeContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateTypeContext::TYPE() {
  return getToken(PrestoSqlParser::TYPE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::CreateTypeContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateTypeContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

std::vector<PrestoSqlParser::SqlParameterDeclarationContext*>
PrestoSqlParser::CreateTypeContext::sqlParameterDeclaration() {
  return getRuleContexts<PrestoSqlParser::SqlParameterDeclarationContext>();
}

PrestoSqlParser::SqlParameterDeclarationContext*
PrestoSqlParser::CreateTypeContext::sqlParameterDeclaration(size_t i) {
  return getRuleContext<PrestoSqlParser::SqlParameterDeclarationContext>(i);
}

PrestoSqlParser::TypeContext* PrestoSqlParser::CreateTypeContext::type() {
  return getRuleContext<PrestoSqlParser::TypeContext>(0);
}

PrestoSqlParser::CreateTypeContext::CreateTypeContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CreateTypeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateType(this);
}
void PrestoSqlParser::CreateTypeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateType(this);
}

std::any PrestoSqlParser::CreateTypeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCreateType(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeleteContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DeleteContext::DELETE() {
  return getToken(PrestoSqlParser::DELETE, 0);
}

tree::TerminalNode* PrestoSqlParser::DeleteContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::DeleteContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::DeleteContext::WHERE() {
  return getToken(PrestoSqlParser::WHERE, 0);
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::DeleteContext::booleanExpression() {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(0);
}

PrestoSqlParser::DeleteContext::DeleteContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DeleteContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDelete(this);
}
void PrestoSqlParser::DeleteContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDelete(this);
}

std::any PrestoSqlParser::DeleteContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDelete(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DescribeInputContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DescribeInputContext::DESCRIBE() {
  return getToken(PrestoSqlParser::DESCRIBE, 0);
}

tree::TerminalNode* PrestoSqlParser::DescribeInputContext::INPUT() {
  return getToken(PrestoSqlParser::INPUT, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::DescribeInputContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::DescribeInputContext::DescribeInputContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DescribeInputContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDescribeInput(this);
}
void PrestoSqlParser::DescribeInputContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDescribeInput(this);
}

std::any PrestoSqlParser::DescribeInputContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDescribeInput(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowStatsForQueryContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowStatsForQueryContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowStatsForQueryContext::STATS() {
  return getToken(PrestoSqlParser::STATS, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowStatsForQueryContext::FOR() {
  return getToken(PrestoSqlParser::FOR, 0);
}

PrestoSqlParser::QuerySpecificationContext*
PrestoSqlParser::ShowStatsForQueryContext::querySpecification() {
  return getRuleContext<PrestoSqlParser::QuerySpecificationContext>(0);
}

PrestoSqlParser::ShowStatsForQueryContext::ShowStatsForQueryContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowStatsForQueryContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowStatsForQuery(this);
}
void PrestoSqlParser::ShowStatsForQueryContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowStatsForQuery(this);
}

std::any PrestoSqlParser::ShowStatsForQueryContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowStatsForQuery(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StatementDefaultContext
//------------------------------------------------------------------

PrestoSqlParser::QueryContext*
PrestoSqlParser::StatementDefaultContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

PrestoSqlParser::StatementDefaultContext::StatementDefaultContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::StatementDefaultContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatementDefault(this);
}
void PrestoSqlParser::StatementDefaultContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatementDefault(this);
}

std::any PrestoSqlParser::StatementDefaultContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitStatementDefault(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TruncateTableContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::TruncateTableContext::TRUNCATE() {
  return getToken(PrestoSqlParser::TRUNCATE, 0);
}

tree::TerminalNode* PrestoSqlParser::TruncateTableContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::TruncateTableContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::TruncateTableContext::TruncateTableContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TruncateTableContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTruncateTable(this);
}
void PrestoSqlParser::TruncateTableContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTruncateTable(this);
}

std::any PrestoSqlParser::TruncateTableContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTruncateTable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AlterColumnSetNotNullContext
//------------------------------------------------------------------

std::vector<tree::TerminalNode*>
PrestoSqlParser::AlterColumnSetNotNullContext::ALTER() {
  return getTokens(PrestoSqlParser::ALTER);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnSetNotNullContext::ALTER(
    size_t i) {
  return getToken(PrestoSqlParser::ALTER, i);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnSetNotNullContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnSetNotNullContext::SET() {
  return getToken(PrestoSqlParser::SET, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnSetNotNullContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

tree::TerminalNode*
PrestoSqlParser::AlterColumnSetNotNullContext::NULL_LITERAL() {
  return getToken(PrestoSqlParser::NULL_LITERAL, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::AlterColumnSetNotNullContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::AlterColumnSetNotNullContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnSetNotNullContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnSetNotNullContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnSetNotNullContext::COLUMN() {
  return getToken(PrestoSqlParser::COLUMN, 0);
}

PrestoSqlParser::AlterColumnSetNotNullContext::AlterColumnSetNotNullContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::AlterColumnSetNotNullContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlterColumnSetNotNull(this);
}
void PrestoSqlParser::AlterColumnSetNotNullContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlterColumnSetNotNull(this);
}

std::any PrestoSqlParser::AlterColumnSetNotNullContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAlterColumnSetNotNull(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CreateMaterializedViewContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CreateMaterializedViewContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode*
PrestoSqlParser::CreateMaterializedViewContext::MATERIALIZED() {
  return getToken(PrestoSqlParser::MATERIALIZED, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateMaterializedViewContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::CreateMaterializedViewContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateMaterializedViewContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

PrestoSqlParser::QueryContext*
PrestoSqlParser::CreateMaterializedViewContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateMaterializedViewContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateMaterializedViewContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateMaterializedViewContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateMaterializedViewContext::COMMENT() {
  return getToken(PrestoSqlParser::COMMENT, 0);
}

PrestoSqlParser::StringContext*
PrestoSqlParser::CreateMaterializedViewContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateMaterializedViewContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

PrestoSqlParser::PropertiesContext*
PrestoSqlParser::CreateMaterializedViewContext::properties() {
  return getRuleContext<PrestoSqlParser::PropertiesContext>(0);
}

PrestoSqlParser::CreateMaterializedViewContext::CreateMaterializedViewContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CreateMaterializedViewContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateMaterializedView(this);
}
void PrestoSqlParser::CreateMaterializedViewContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateMaterializedView(this);
}

std::any PrestoSqlParser::CreateMaterializedViewContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCreateMaterializedView(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AlterFunctionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::AlterFunctionContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterFunctionContext::FUNCTION() {
  return getToken(PrestoSqlParser::FUNCTION, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::AlterFunctionContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::AlterRoutineCharacteristicsContext*
PrestoSqlParser::AlterFunctionContext::alterRoutineCharacteristics() {
  return getRuleContext<PrestoSqlParser::AlterRoutineCharacteristicsContext>(0);
}

PrestoSqlParser::TypesContext* PrestoSqlParser::AlterFunctionContext::types() {
  return getRuleContext<PrestoSqlParser::TypesContext>(0);
}

PrestoSqlParser::AlterFunctionContext::AlterFunctionContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::AlterFunctionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlterFunction(this);
}
void PrestoSqlParser::AlterFunctionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlterFunction(this);
}

std::any PrestoSqlParser::AlterFunctionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAlterFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SetSessionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::SetSessionContext::SET() {
  return getToken(PrestoSqlParser::SET, 0);
}

tree::TerminalNode* PrestoSqlParser::SetSessionContext::SESSION() {
  return getToken(PrestoSqlParser::SESSION, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::SetSessionContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SetSessionContext::EQ() {
  return getToken(PrestoSqlParser::EQ, 0);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::SetSessionContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

PrestoSqlParser::SetSessionContext::SetSessionContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SetSessionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetSession(this);
}
void PrestoSqlParser::SetSessionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetSession(this);
}

std::any PrestoSqlParser::SetSessionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSetSession(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CreateViewContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CreateViewContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateViewContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::CreateViewContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateViewContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

PrestoSqlParser::QueryContext* PrestoSqlParser::CreateViewContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CreateViewContext::OR() {
  return getToken(PrestoSqlParser::OR, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateViewContext::REPLACE() {
  return getToken(PrestoSqlParser::REPLACE, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateViewContext::SECURITY() {
  return getToken(PrestoSqlParser::SECURITY, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateViewContext::DEFINER() {
  return getToken(PrestoSqlParser::DEFINER, 0);
}

tree::TerminalNode* PrestoSqlParser::CreateViewContext::INVOKER() {
  return getToken(PrestoSqlParser::INVOKER, 0);
}

PrestoSqlParser::CreateViewContext::CreateViewContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CreateViewContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreateView(this);
}
void PrestoSqlParser::CreateViewContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreateView(this);
}

std::any PrestoSqlParser::CreateViewContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCreateView(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowSchemasContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowSchemasContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowSchemasContext::SCHEMAS() {
  return getToken(PrestoSqlParser::SCHEMAS, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ShowSchemasContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ShowSchemasContext::LIKE() {
  return getToken(PrestoSqlParser::LIKE, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowSchemasContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowSchemasContext::IN() {
  return getToken(PrestoSqlParser::IN, 0);
}

std::vector<PrestoSqlParser::StringContext*>
PrestoSqlParser::ShowSchemasContext::string() {
  return getRuleContexts<PrestoSqlParser::StringContext>();
}

PrestoSqlParser::StringContext* PrestoSqlParser::ShowSchemasContext::string(
    size_t i) {
  return getRuleContext<PrestoSqlParser::StringContext>(i);
}

tree::TerminalNode* PrestoSqlParser::ShowSchemasContext::ESCAPE() {
  return getToken(PrestoSqlParser::ESCAPE, 0);
}

PrestoSqlParser::ShowSchemasContext::ShowSchemasContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowSchemasContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowSchemas(this);
}
void PrestoSqlParser::ShowSchemasContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowSchemas(this);
}

std::any PrestoSqlParser::ShowSchemasContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowSchemas(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DropTableContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DropTableContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode* PrestoSqlParser::DropTableContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::DropTableContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::DropTableContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::DropTableContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::DropTableContext::DropTableContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DropTableContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDropTable(this);
}
void PrestoSqlParser::DropTableContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDropTable(this);
}

std::any PrestoSqlParser::DropTableContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDropTable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RollbackContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RollbackContext::ROLLBACK() {
  return getToken(PrestoSqlParser::ROLLBACK, 0);
}

tree::TerminalNode* PrestoSqlParser::RollbackContext::WORK() {
  return getToken(PrestoSqlParser::WORK, 0);
}

PrestoSqlParser::RollbackContext::RollbackContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RollbackContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRollback(this);
}
void PrestoSqlParser::RollbackContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRollback(this);
}

std::any PrestoSqlParser::RollbackContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRollback(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RenameViewContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RenameViewContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameViewContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameViewContext::RENAME() {
  return getToken(PrestoSqlParser::RENAME, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameViewContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

std::vector<PrestoSqlParser::QualifiedNameContext*>
PrestoSqlParser::RenameViewContext::qualifiedName() {
  return getRuleContexts<PrestoSqlParser::QualifiedNameContext>();
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::RenameViewContext::qualifiedName(size_t i) {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(i);
}

tree::TerminalNode* PrestoSqlParser::RenameViewContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::RenameViewContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::RenameViewContext::RenameViewContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RenameViewContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRenameView(this);
}
void PrestoSqlParser::RenameViewContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRenameView(this);
}

std::any PrestoSqlParser::RenameViewContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRenameView(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AlterColumnDropNotNullContext
//------------------------------------------------------------------

std::vector<tree::TerminalNode*>
PrestoSqlParser::AlterColumnDropNotNullContext::ALTER() {
  return getTokens(PrestoSqlParser::ALTER);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnDropNotNullContext::ALTER(
    size_t i) {
  return getToken(PrestoSqlParser::ALTER, i);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnDropNotNullContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnDropNotNullContext::DROP() {
  return getToken(PrestoSqlParser::DROP, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnDropNotNullContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

tree::TerminalNode*
PrestoSqlParser::AlterColumnDropNotNullContext::NULL_LITERAL() {
  return getToken(PrestoSqlParser::NULL_LITERAL, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::AlterColumnDropNotNullContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::AlterColumnDropNotNullContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnDropNotNullContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnDropNotNullContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

tree::TerminalNode* PrestoSqlParser::AlterColumnDropNotNullContext::COLUMN() {
  return getToken(PrestoSqlParser::COLUMN, 0);
}

PrestoSqlParser::AlterColumnDropNotNullContext::AlterColumnDropNotNullContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::AlterColumnDropNotNullContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlterColumnDropNotNull(this);
}
void PrestoSqlParser::AlterColumnDropNotNullContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlterColumnDropNotNull(this);
}

std::any PrestoSqlParser::AlterColumnDropNotNullContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAlterColumnDropNotNull(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GrantRolesContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::GrantRolesContext::GRANT() {
  return getToken(PrestoSqlParser::GRANT, 0);
}

PrestoSqlParser::RolesContext* PrestoSqlParser::GrantRolesContext::roles() {
  return getRuleContext<PrestoSqlParser::RolesContext>(0);
}

tree::TerminalNode* PrestoSqlParser::GrantRolesContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

std::vector<PrestoSqlParser::PrincipalContext*>
PrestoSqlParser::GrantRolesContext::principal() {
  return getRuleContexts<PrestoSqlParser::PrincipalContext>();
}

PrestoSqlParser::PrincipalContext*
PrestoSqlParser::GrantRolesContext::principal(size_t i) {
  return getRuleContext<PrestoSqlParser::PrincipalContext>(i);
}

tree::TerminalNode* PrestoSqlParser::GrantRolesContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

tree::TerminalNode* PrestoSqlParser::GrantRolesContext::ADMIN() {
  return getToken(PrestoSqlParser::ADMIN, 0);
}

tree::TerminalNode* PrestoSqlParser::GrantRolesContext::OPTION() {
  return getToken(PrestoSqlParser::OPTION, 0);
}

tree::TerminalNode* PrestoSqlParser::GrantRolesContext::GRANTED() {
  return getToken(PrestoSqlParser::GRANTED, 0);
}

tree::TerminalNode* PrestoSqlParser::GrantRolesContext::BY() {
  return getToken(PrestoSqlParser::BY, 0);
}

PrestoSqlParser::GrantorContext* PrestoSqlParser::GrantRolesContext::grantor() {
  return getRuleContext<PrestoSqlParser::GrantorContext>(0);
}

PrestoSqlParser::GrantRolesContext::GrantRolesContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::GrantRolesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterGrantRoles(this);
}
void PrestoSqlParser::GrantRolesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitGrantRoles(this);
}

std::any PrestoSqlParser::GrantRolesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitGrantRoles(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CallContext::CALL() {
  return getToken(PrestoSqlParser::CALL, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::CallContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

std::vector<PrestoSqlParser::CallArgumentContext*>
PrestoSqlParser::CallContext::callArgument() {
  return getRuleContexts<PrestoSqlParser::CallArgumentContext>();
}

PrestoSqlParser::CallArgumentContext*
PrestoSqlParser::CallContext::callArgument(size_t i) {
  return getRuleContext<PrestoSqlParser::CallArgumentContext>(i);
}

PrestoSqlParser::CallContext::CallContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CallContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall(this);
}
void PrestoSqlParser::CallContext::exitRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall(this);
}

std::any PrestoSqlParser::CallContext::accept(tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RefreshMaterializedViewContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RefreshMaterializedViewContext::REFRESH() {
  return getToken(PrestoSqlParser::REFRESH, 0);
}

tree::TerminalNode*
PrestoSqlParser::RefreshMaterializedViewContext::MATERIALIZED() {
  return getToken(PrestoSqlParser::MATERIALIZED, 0);
}

tree::TerminalNode* PrestoSqlParser::RefreshMaterializedViewContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::RefreshMaterializedViewContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::RefreshMaterializedViewContext::WHERE() {
  return getToken(PrestoSqlParser::WHERE, 0);
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::RefreshMaterializedViewContext::booleanExpression() {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(0);
}

PrestoSqlParser::RefreshMaterializedViewContext::RefreshMaterializedViewContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RefreshMaterializedViewContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRefreshMaterializedView(this);
}
void PrestoSqlParser::RefreshMaterializedViewContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRefreshMaterializedView(this);
}

std::any PrestoSqlParser::RefreshMaterializedViewContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRefreshMaterializedView(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowCreateMaterializedViewContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowCreateMaterializedViewContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode*
PrestoSqlParser::ShowCreateMaterializedViewContext::CREATE() {
  return getToken(PrestoSqlParser::CREATE, 0);
}

tree::TerminalNode*
PrestoSqlParser::ShowCreateMaterializedViewContext::MATERIALIZED() {
  return getToken(PrestoSqlParser::MATERIALIZED, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowCreateMaterializedViewContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::ShowCreateMaterializedViewContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::ShowCreateMaterializedViewContext::
    ShowCreateMaterializedViewContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowCreateMaterializedViewContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowCreateMaterializedView(this);
}
void PrestoSqlParser::ShowCreateMaterializedViewContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowCreateMaterializedView(this);
}

std::any PrestoSqlParser::ShowCreateMaterializedViewContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowCreateMaterializedView(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ShowFunctionsContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ShowFunctionsContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowFunctionsContext::FUNCTIONS() {
  return getToken(PrestoSqlParser::FUNCTIONS, 0);
}

tree::TerminalNode* PrestoSqlParser::ShowFunctionsContext::LIKE() {
  return getToken(PrestoSqlParser::LIKE, 0);
}

std::vector<PrestoSqlParser::StringContext*>
PrestoSqlParser::ShowFunctionsContext::string() {
  return getRuleContexts<PrestoSqlParser::StringContext>();
}

PrestoSqlParser::StringContext* PrestoSqlParser::ShowFunctionsContext::string(
    size_t i) {
  return getRuleContext<PrestoSqlParser::StringContext>(i);
}

tree::TerminalNode* PrestoSqlParser::ShowFunctionsContext::ESCAPE() {
  return getToken(PrestoSqlParser::ESCAPE, 0);
}

PrestoSqlParser::ShowFunctionsContext::ShowFunctionsContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ShowFunctionsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterShowFunctions(this);
}
void PrestoSqlParser::ShowFunctionsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitShowFunctions(this);
}

std::any PrestoSqlParser::ShowFunctionsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitShowFunctions(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DescribeOutputContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DescribeOutputContext::DESCRIBE() {
  return getToken(PrestoSqlParser::DESCRIBE, 0);
}

tree::TerminalNode* PrestoSqlParser::DescribeOutputContext::OUTPUT() {
  return getToken(PrestoSqlParser::OUTPUT, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::DescribeOutputContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::DescribeOutputContext::DescribeOutputContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DescribeOutputContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDescribeOutput(this);
}
void PrestoSqlParser::DescribeOutputContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDescribeOutput(this);
}

std::any PrestoSqlParser::DescribeOutputContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDescribeOutput(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GrantContext
//------------------------------------------------------------------

std::vector<tree::TerminalNode*> PrestoSqlParser::GrantContext::GRANT() {
  return getTokens(PrestoSqlParser::GRANT);
}

tree::TerminalNode* PrestoSqlParser::GrantContext::GRANT(size_t i) {
  return getToken(PrestoSqlParser::GRANT, i);
}

tree::TerminalNode* PrestoSqlParser::GrantContext::ON() {
  return getToken(PrestoSqlParser::ON, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::GrantContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::GrantContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

PrestoSqlParser::PrincipalContext* PrestoSqlParser::GrantContext::principal() {
  return getRuleContext<PrestoSqlParser::PrincipalContext>(0);
}

std::vector<PrestoSqlParser::PrivilegeContext*>
PrestoSqlParser::GrantContext::privilege() {
  return getRuleContexts<PrestoSqlParser::PrivilegeContext>();
}

PrestoSqlParser::PrivilegeContext* PrestoSqlParser::GrantContext::privilege(
    size_t i) {
  return getRuleContext<PrestoSqlParser::PrivilegeContext>(i);
}

tree::TerminalNode* PrestoSqlParser::GrantContext::ALL() {
  return getToken(PrestoSqlParser::ALL, 0);
}

tree::TerminalNode* PrestoSqlParser::GrantContext::PRIVILEGES() {
  return getToken(PrestoSqlParser::PRIVILEGES, 0);
}

tree::TerminalNode* PrestoSqlParser::GrantContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::GrantContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

tree::TerminalNode* PrestoSqlParser::GrantContext::OPTION() {
  return getToken(PrestoSqlParser::OPTION, 0);
}

PrestoSqlParser::GrantContext::GrantContext(StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::GrantContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterGrant(this);
}
void PrestoSqlParser::GrantContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitGrant(this);
}

std::any PrestoSqlParser::GrantContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitGrant(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SetTablePropertiesContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::SetTablePropertiesContext::ALTER() {
  return getToken(PrestoSqlParser::ALTER, 0);
}

tree::TerminalNode* PrestoSqlParser::SetTablePropertiesContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::SetTablePropertiesContext::SET() {
  return getToken(PrestoSqlParser::SET, 0);
}

tree::TerminalNode* PrestoSqlParser::SetTablePropertiesContext::PROPERTIES() {
  return getToken(PrestoSqlParser::PROPERTIES, 0);
}

PrestoSqlParser::PropertiesContext*
PrestoSqlParser::SetTablePropertiesContext::properties() {
  return getRuleContext<PrestoSqlParser::PropertiesContext>(0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::SetTablePropertiesContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SetTablePropertiesContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::SetTablePropertiesContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::SetTablePropertiesContext::SetTablePropertiesContext(
    StatementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SetTablePropertiesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetTableProperties(this);
}
void PrestoSqlParser::SetTablePropertiesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetTableProperties(this);
}

std::any PrestoSqlParser::SetTablePropertiesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSetTableProperties(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::StatementContext* PrestoSqlParser::statement() {
  StatementContext* _localctx =
      _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 6, PrestoSqlParser::RuleStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(932);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 102, _ctx)) {
      case 1: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::StatementDefaultContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(195);
        query();
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UseContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(196);
        match(PrestoSqlParser::USE);
        setState(197);
        antlrcpp::downCast<UseContext*>(_localctx)->schema = identifier();
        break;
      }

      case 3: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UseContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(198);
        match(PrestoSqlParser::USE);
        setState(199);
        antlrcpp::downCast<UseContext*>(_localctx)->catalog = identifier();
        setState(200);
        match(PrestoSqlParser::T__0);
        setState(201);
        antlrcpp::downCast<UseContext*>(_localctx)->schema = identifier();
        break;
      }

      case 4: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CreateSchemaContext>(
                _localctx);
        enterOuterAlt(_localctx, 4);
        setState(203);
        match(PrestoSqlParser::CREATE);
        setState(204);
        match(PrestoSqlParser::SCHEMA);
        setState(208);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 0, _ctx)) {
          case 1: {
            setState(205);
            match(PrestoSqlParser::IF);
            setState(206);
            match(PrestoSqlParser::NOT);
            setState(207);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(210);
        qualifiedName();
        setState(213);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(211);
          match(PrestoSqlParser::WITH);
          setState(212);
          properties();
        }
        break;
      }

      case 5: {
        _localctx = _tracker.createInstance<PrestoSqlParser::DropSchemaContext>(
            _localctx);
        enterOuterAlt(_localctx, 5);
        setState(215);
        match(PrestoSqlParser::DROP);
        setState(216);
        match(PrestoSqlParser::SCHEMA);
        setState(219);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 2, _ctx)) {
          case 1: {
            setState(217);
            match(PrestoSqlParser::IF);
            setState(218);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(221);
        qualifiedName();
        setState(223);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::CASCADE ||
            _la == PrestoSqlParser::RESTRICT) {
          setState(222);
          _la = _input->LA(1);
          if (!(_la == PrestoSqlParser::CASCADE ||
                _la == PrestoSqlParser::RESTRICT)) {
            _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
        }
        break;
      }

      case 6: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::RenameSchemaContext>(
                _localctx);
        enterOuterAlt(_localctx, 6);
        setState(225);
        match(PrestoSqlParser::ALTER);
        setState(226);
        match(PrestoSqlParser::SCHEMA);
        setState(227);
        qualifiedName();
        setState(228);
        match(PrestoSqlParser::RENAME);
        setState(229);
        match(PrestoSqlParser::TO);
        setState(230);
        identifier();
        break;
      }

      case 7: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::CreateTableAsSelectContext>(
                    _localctx);
        enterOuterAlt(_localctx, 7);
        setState(232);
        match(PrestoSqlParser::CREATE);
        setState(233);
        match(PrestoSqlParser::TABLE);
        setState(237);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 4, _ctx)) {
          case 1: {
            setState(234);
            match(PrestoSqlParser::IF);
            setState(235);
            match(PrestoSqlParser::NOT);
            setState(236);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(239);
        qualifiedName();
        setState(241);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::T__1) {
          setState(240);
          columnAliases();
        }
        setState(245);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::COMMENT) {
          setState(243);
          match(PrestoSqlParser::COMMENT);
          setState(244);
          string();
        }
        setState(249);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(247);
          match(PrestoSqlParser::WITH);
          setState(248);
          properties();
        }
        setState(251);
        match(PrestoSqlParser::AS);
        setState(257);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 8, _ctx)) {
          case 1: {
            setState(252);
            query();
            break;
          }

          case 2: {
            setState(253);
            match(PrestoSqlParser::T__1);
            setState(254);
            query();
            setState(255);
            match(PrestoSqlParser::T__2);
            break;
          }

          default:
            break;
        }
        setState(264);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(259);
          match(PrestoSqlParser::WITH);
          setState(261);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == PrestoSqlParser::NO) {
            setState(260);
            match(PrestoSqlParser::NO);
          }
          setState(263);
          match(PrestoSqlParser::DATA);
        }
        break;
      }

      case 8: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CreateTableContext>(
                _localctx);
        enterOuterAlt(_localctx, 8);
        setState(266);
        match(PrestoSqlParser::CREATE);
        setState(267);
        match(PrestoSqlParser::TABLE);
        setState(271);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 11, _ctx)) {
          case 1: {
            setState(268);
            match(PrestoSqlParser::IF);
            setState(269);
            match(PrestoSqlParser::NOT);
            setState(270);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(273);
        qualifiedName();
        setState(274);
        match(PrestoSqlParser::T__1);
        setState(275);
        tableElement();
        setState(280);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(276);
          match(PrestoSqlParser::T__3);
          setState(277);
          tableElement();
          setState(282);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(283);
        match(PrestoSqlParser::T__2);
        setState(286);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::COMMENT) {
          setState(284);
          match(PrestoSqlParser::COMMENT);
          setState(285);
          string();
        }
        setState(290);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(288);
          match(PrestoSqlParser::WITH);
          setState(289);
          properties();
        }
        break;
      }

      case 9: {
        _localctx = _tracker.createInstance<PrestoSqlParser::DropTableContext>(
            _localctx);
        enterOuterAlt(_localctx, 9);
        setState(292);
        match(PrestoSqlParser::DROP);
        setState(293);
        match(PrestoSqlParser::TABLE);
        setState(296);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 15, _ctx)) {
          case 1: {
            setState(294);
            match(PrestoSqlParser::IF);
            setState(295);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(298);
        qualifiedName();
        break;
      }

      case 10: {
        _localctx = _tracker.createInstance<PrestoSqlParser::InsertIntoContext>(
            _localctx);
        enterOuterAlt(_localctx, 10);
        setState(299);
        match(PrestoSqlParser::INSERT);
        setState(300);
        match(PrestoSqlParser::INTO);
        setState(301);
        qualifiedName();
        setState(303);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 16, _ctx)) {
          case 1: {
            setState(302);
            columnAliases();
            break;
          }

          default:
            break;
        }
        setState(305);
        query();
        break;
      }

      case 11: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DeleteContext>(_localctx);
        enterOuterAlt(_localctx, 11);
        setState(307);
        match(PrestoSqlParser::DELETE);
        setState(308);
        match(PrestoSqlParser::FROM);
        setState(309);
        qualifiedName();
        setState(312);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WHERE) {
          setState(310);
          match(PrestoSqlParser::WHERE);
          setState(311);
          booleanExpression(0);
        }
        break;
      }

      case 12: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::TruncateTableContext>(
                _localctx);
        enterOuterAlt(_localctx, 12);
        setState(314);
        match(PrestoSqlParser::TRUNCATE);
        setState(315);
        match(PrestoSqlParser::TABLE);
        setState(316);
        qualifiedName();
        break;
      }

      case 13: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::RenameTableContext>(
                _localctx);
        enterOuterAlt(_localctx, 13);
        setState(317);
        match(PrestoSqlParser::ALTER);
        setState(318);
        match(PrestoSqlParser::TABLE);
        setState(321);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 18, _ctx)) {
          case 1: {
            setState(319);
            match(PrestoSqlParser::IF);
            setState(320);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(323);
        antlrcpp::downCast<RenameTableContext*>(_localctx)->from =
            qualifiedName();
        setState(324);
        match(PrestoSqlParser::RENAME);
        setState(325);
        match(PrestoSqlParser::TO);
        setState(326);
        antlrcpp::downCast<RenameTableContext*>(_localctx)->to =
            qualifiedName();
        break;
      }

      case 14: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::RenameColumnContext>(
                _localctx);
        enterOuterAlt(_localctx, 14);
        setState(328);
        match(PrestoSqlParser::ALTER);
        setState(329);
        match(PrestoSqlParser::TABLE);
        setState(332);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 19, _ctx)) {
          case 1: {
            setState(330);
            match(PrestoSqlParser::IF);
            setState(331);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(334);
        antlrcpp::downCast<RenameColumnContext*>(_localctx)->tableName =
            qualifiedName();
        setState(335);
        match(PrestoSqlParser::RENAME);
        setState(336);
        match(PrestoSqlParser::COLUMN);
        setState(339);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 20, _ctx)) {
          case 1: {
            setState(337);
            match(PrestoSqlParser::IF);
            setState(338);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(341);
        antlrcpp::downCast<RenameColumnContext*>(_localctx)->from =
            identifier();
        setState(342);
        match(PrestoSqlParser::TO);
        setState(343);
        antlrcpp::downCast<RenameColumnContext*>(_localctx)->to = identifier();
        break;
      }

      case 15: {
        _localctx = _tracker.createInstance<PrestoSqlParser::DropColumnContext>(
            _localctx);
        enterOuterAlt(_localctx, 15);
        setState(345);
        match(PrestoSqlParser::ALTER);
        setState(346);
        match(PrestoSqlParser::TABLE);
        setState(349);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 21, _ctx)) {
          case 1: {
            setState(347);
            match(PrestoSqlParser::IF);
            setState(348);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(351);
        antlrcpp::downCast<DropColumnContext*>(_localctx)->tableName =
            qualifiedName();
        setState(352);
        match(PrestoSqlParser::DROP);
        setState(353);
        match(PrestoSqlParser::COLUMN);
        setState(356);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 22, _ctx)) {
          case 1: {
            setState(354);
            match(PrestoSqlParser::IF);
            setState(355);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(358);
        antlrcpp::downCast<DropColumnContext*>(_localctx)->column =
            qualifiedName();
        break;
      }

      case 16: {
        _localctx = _tracker.createInstance<PrestoSqlParser::AddColumnContext>(
            _localctx);
        enterOuterAlt(_localctx, 16);
        setState(360);
        match(PrestoSqlParser::ALTER);
        setState(361);
        match(PrestoSqlParser::TABLE);
        setState(364);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 23, _ctx)) {
          case 1: {
            setState(362);
            match(PrestoSqlParser::IF);
            setState(363);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(366);
        antlrcpp::downCast<AddColumnContext*>(_localctx)->tableName =
            qualifiedName();
        setState(367);
        match(PrestoSqlParser::ADD);
        setState(368);
        match(PrestoSqlParser::COLUMN);
        setState(372);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 24, _ctx)) {
          case 1: {
            setState(369);
            match(PrestoSqlParser::IF);
            setState(370);
            match(PrestoSqlParser::NOT);
            setState(371);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(374);
        antlrcpp::downCast<AddColumnContext*>(_localctx)->column =
            columnDefinition();
        break;
      }

      case 17: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::AddConstraintContext>(
                _localctx);
        enterOuterAlt(_localctx, 17);
        setState(376);
        match(PrestoSqlParser::ALTER);
        setState(377);
        match(PrestoSqlParser::TABLE);
        setState(380);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 25, _ctx)) {
          case 1: {
            setState(378);
            match(PrestoSqlParser::IF);
            setState(379);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(382);
        antlrcpp::downCast<AddConstraintContext*>(_localctx)->tableName =
            qualifiedName();
        setState(383);
        match(PrestoSqlParser::ADD);
        setState(384);
        constraintSpecification();
        break;
      }

      case 18: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DropConstraintContext>(
                _localctx);
        enterOuterAlt(_localctx, 18);
        setState(386);
        match(PrestoSqlParser::ALTER);
        setState(387);
        match(PrestoSqlParser::TABLE);
        setState(390);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 26, _ctx)) {
          case 1: {
            setState(388);
            match(PrestoSqlParser::IF);
            setState(389);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(392);
        antlrcpp::downCast<DropConstraintContext*>(_localctx)->tableName =
            qualifiedName();
        setState(393);
        match(PrestoSqlParser::DROP);
        setState(394);
        match(PrestoSqlParser::CONSTRAINT);
        setState(397);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 27, _ctx)) {
          case 1: {
            setState(395);
            match(PrestoSqlParser::IF);
            setState(396);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(399);
        antlrcpp::downCast<DropConstraintContext*>(_localctx)->name =
            identifier();
        break;
      }

      case 19: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::AlterColumnSetNotNullContext>(
                    _localctx);
        enterOuterAlt(_localctx, 19);
        setState(401);
        match(PrestoSqlParser::ALTER);
        setState(402);
        match(PrestoSqlParser::TABLE);
        setState(405);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 28, _ctx)) {
          case 1: {
            setState(403);
            match(PrestoSqlParser::IF);
            setState(404);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(407);
        antlrcpp::downCast<AlterColumnSetNotNullContext*>(_localctx)
            ->tableName = qualifiedName();
        setState(408);
        match(PrestoSqlParser::ALTER);
        setState(410);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 29, _ctx)) {
          case 1: {
            setState(409);
            match(PrestoSqlParser::COLUMN);
            break;
          }

          default:
            break;
        }
        setState(412);
        antlrcpp::downCast<AlterColumnSetNotNullContext*>(_localctx)->column =
            identifier();
        setState(413);
        match(PrestoSqlParser::SET);
        setState(414);
        match(PrestoSqlParser::NOT);
        setState(415);
        match(PrestoSqlParser::NULL_LITERAL);
        break;
      }

      case 20: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::AlterColumnDropNotNullContext>(
                    _localctx);
        enterOuterAlt(_localctx, 20);
        setState(417);
        match(PrestoSqlParser::ALTER);
        setState(418);
        match(PrestoSqlParser::TABLE);
        setState(421);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 30, _ctx)) {
          case 1: {
            setState(419);
            match(PrestoSqlParser::IF);
            setState(420);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(423);
        antlrcpp::downCast<AlterColumnDropNotNullContext*>(_localctx)
            ->tableName = qualifiedName();
        setState(424);
        match(PrestoSqlParser::ALTER);
        setState(426);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 31, _ctx)) {
          case 1: {
            setState(425);
            match(PrestoSqlParser::COLUMN);
            break;
          }

          default:
            break;
        }
        setState(428);
        antlrcpp::downCast<AlterColumnDropNotNullContext*>(_localctx)->column =
            identifier();
        setState(429);
        match(PrestoSqlParser::DROP);
        setState(430);
        match(PrestoSqlParser::NOT);
        setState(431);
        match(PrestoSqlParser::NULL_LITERAL);
        break;
      }

      case 21: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SetTablePropertiesContext>(
                _localctx);
        enterOuterAlt(_localctx, 21);
        setState(433);
        match(PrestoSqlParser::ALTER);
        setState(434);
        match(PrestoSqlParser::TABLE);
        setState(437);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 32, _ctx)) {
          case 1: {
            setState(435);
            match(PrestoSqlParser::IF);
            setState(436);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(439);
        antlrcpp::downCast<SetTablePropertiesContext*>(_localctx)->tableName =
            qualifiedName();
        setState(440);
        match(PrestoSqlParser::SET);
        setState(441);
        match(PrestoSqlParser::PROPERTIES);
        setState(442);
        properties();
        break;
      }

      case 22: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::AnalyzeContext>(_localctx);
        enterOuterAlt(_localctx, 22);
        setState(444);
        match(PrestoSqlParser::ANALYZE);
        setState(445);
        qualifiedName();
        setState(448);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(446);
          match(PrestoSqlParser::WITH);
          setState(447);
          properties();
        }
        break;
      }

      case 23: {
        _localctx = _tracker.createInstance<PrestoSqlParser::CreateTypeContext>(
            _localctx);
        enterOuterAlt(_localctx, 23);
        setState(450);
        match(PrestoSqlParser::CREATE);
        setState(451);
        match(PrestoSqlParser::TYPE);
        setState(452);
        qualifiedName();
        setState(453);
        match(PrestoSqlParser::AS);
        setState(466);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PrestoSqlParser::T__1: {
            setState(454);
            match(PrestoSqlParser::T__1);
            setState(455);
            sqlParameterDeclaration();
            setState(460);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == PrestoSqlParser::T__3) {
              setState(456);
              match(PrestoSqlParser::T__3);
              setState(457);
              sqlParameterDeclaration();
              setState(462);
              _errHandler->sync(this);
              _la = _input->LA(1);
            }
            setState(463);
            match(PrestoSqlParser::T__2);
            break;
          }

          case PrestoSqlParser::ADD:
          case PrestoSqlParser::ADMIN:
          case PrestoSqlParser::ALL:
          case PrestoSqlParser::ANALYZE:
          case PrestoSqlParser::ANY:
          case PrestoSqlParser::ARRAY:
          case PrestoSqlParser::ASC:
          case PrestoSqlParser::AT:
          case PrestoSqlParser::BEFORE:
          case PrestoSqlParser::BERNOULLI:
          case PrestoSqlParser::CALL:
          case PrestoSqlParser::CALLED:
          case PrestoSqlParser::CASCADE:
          case PrestoSqlParser::CATALOGS:
          case PrestoSqlParser::COLUMN:
          case PrestoSqlParser::COLUMNS:
          case PrestoSqlParser::COMMENT:
          case PrestoSqlParser::COMMIT:
          case PrestoSqlParser::COMMITTED:
          case PrestoSqlParser::CURRENT:
          case PrestoSqlParser::CURRENT_ROLE:
          case PrestoSqlParser::DATA:
          case PrestoSqlParser::DATE:
          case PrestoSqlParser::DAY:
          case PrestoSqlParser::DEFINER:
          case PrestoSqlParser::DESC:
          case PrestoSqlParser::DETERMINISTIC:
          case PrestoSqlParser::DISABLED:
          case PrestoSqlParser::DISTRIBUTED:
          case PrestoSqlParser::ENABLED:
          case PrestoSqlParser::ENFORCED:
          case PrestoSqlParser::EXCLUDE:
          case PrestoSqlParser::EXCLUDING:
          case PrestoSqlParser::EXECUTABLE:
          case PrestoSqlParser::EXPLAIN:
          case PrestoSqlParser::EXTERNAL:
          case PrestoSqlParser::FETCH:
          case PrestoSqlParser::FILTER:
          case PrestoSqlParser::FIRST:
          case PrestoSqlParser::FOLLOWING:
          case PrestoSqlParser::FORMAT:
          case PrestoSqlParser::FUNCTION:
          case PrestoSqlParser::FUNCTIONS:
          case PrestoSqlParser::GRANT:
          case PrestoSqlParser::GRANTED:
          case PrestoSqlParser::GRANTS:
          case PrestoSqlParser::GRAPH:
          case PrestoSqlParser::GRAPHVIZ:
          case PrestoSqlParser::GROUPS:
          case PrestoSqlParser::HOUR:
          case PrestoSqlParser::IF:
          case PrestoSqlParser::IGNORE:
          case PrestoSqlParser::INCLUDING:
          case PrestoSqlParser::INPUT:
          case PrestoSqlParser::INTERVAL:
          case PrestoSqlParser::INVOKER:
          case PrestoSqlParser::IO:
          case PrestoSqlParser::ISOLATION:
          case PrestoSqlParser::JSON:
          case PrestoSqlParser::KEY:
          case PrestoSqlParser::LANGUAGE:
          case PrestoSqlParser::LAST:
          case PrestoSqlParser::LATERAL:
          case PrestoSqlParser::LEVEL:
          case PrestoSqlParser::LIMIT:
          case PrestoSqlParser::LOGICAL:
          case PrestoSqlParser::MAP:
          case PrestoSqlParser::MATERIALIZED:
          case PrestoSqlParser::MINUTE:
          case PrestoSqlParser::MONTH:
          case PrestoSqlParser::NAME:
          case PrestoSqlParser::NFC:
          case PrestoSqlParser::NFD:
          case PrestoSqlParser::NFKC:
          case PrestoSqlParser::NFKD:
          case PrestoSqlParser::NO:
          case PrestoSqlParser::NONE:
          case PrestoSqlParser::NULLIF:
          case PrestoSqlParser::NULLS:
          case PrestoSqlParser::OF:
          case PrestoSqlParser::OFFSET:
          case PrestoSqlParser::ONLY:
          case PrestoSqlParser::OPTIMIZED:
          case PrestoSqlParser::OPTION:
          case PrestoSqlParser::ORDINALITY:
          case PrestoSqlParser::OUTPUT:
          case PrestoSqlParser::OVER:
          case PrestoSqlParser::PARTITION:
          case PrestoSqlParser::PARTITIONS:
          case PrestoSqlParser::POSITION:
          case PrestoSqlParser::PRECEDING:
          case PrestoSqlParser::PRIMARY:
          case PrestoSqlParser::PRIVILEGES:
          case PrestoSqlParser::PROPERTIES:
          case PrestoSqlParser::RANGE:
          case PrestoSqlParser::READ:
          case PrestoSqlParser::REFRESH:
          case PrestoSqlParser::RELY:
          case PrestoSqlParser::RENAME:
          case PrestoSqlParser::REPEATABLE:
          case PrestoSqlParser::REPLACE:
          case PrestoSqlParser::RESET:
          case PrestoSqlParser::RESPECT:
          case PrestoSqlParser::RESTRICT:
          case PrestoSqlParser::RETURN:
          case PrestoSqlParser::RETURNS:
          case PrestoSqlParser::REVOKE:
          case PrestoSqlParser::ROLE:
          case PrestoSqlParser::ROLES:
          case PrestoSqlParser::ROLLBACK:
          case PrestoSqlParser::ROW:
          case PrestoSqlParser::ROWS:
          case PrestoSqlParser::SCHEMA:
          case PrestoSqlParser::SCHEMAS:
          case PrestoSqlParser::SECOND:
          case PrestoSqlParser::SECURITY:
          case PrestoSqlParser::SERIALIZABLE:
          case PrestoSqlParser::SESSION:
          case PrestoSqlParser::SET:
          case PrestoSqlParser::SETS:
          case PrestoSqlParser::SHOW:
          case PrestoSqlParser::SOME:
          case PrestoSqlParser::SQL:
          case PrestoSqlParser::START:
          case PrestoSqlParser::STATS:
          case PrestoSqlParser::SUBSTRING:
          case PrestoSqlParser::SYSTEM:
          case PrestoSqlParser::SYSTEM_TIME:
          case PrestoSqlParser::SYSTEM_VERSION:
          case PrestoSqlParser::TABLES:
          case PrestoSqlParser::TABLESAMPLE:
          case PrestoSqlParser::TEMPORARY:
          case PrestoSqlParser::TEXT:
          case PrestoSqlParser::TIME:
          case PrestoSqlParser::TIMESTAMP:
          case PrestoSqlParser::TO:
          case PrestoSqlParser::TRANSACTION:
          case PrestoSqlParser::TRUNCATE:
          case PrestoSqlParser::TRY_CAST:
          case PrestoSqlParser::TYPE:
          case PrestoSqlParser::UNBOUNDED:
          case PrestoSqlParser::UNCOMMITTED:
          case PrestoSqlParser::UNIQUE:
          case PrestoSqlParser::UPDATE:
          case PrestoSqlParser::USE:
          case PrestoSqlParser::USER:
          case PrestoSqlParser::VALIDATE:
          case PrestoSqlParser::VERBOSE:
          case PrestoSqlParser::VERSION:
          case PrestoSqlParser::VIEW:
          case PrestoSqlParser::WORK:
          case PrestoSqlParser::WRITE:
          case PrestoSqlParser::YEAR:
          case PrestoSqlParser::ZONE:
          case PrestoSqlParser::IDENTIFIER:
          case PrestoSqlParser::DIGIT_IDENTIFIER:
          case PrestoSqlParser::QUOTED_IDENTIFIER:
          case PrestoSqlParser::BACKQUOTED_IDENTIFIER:
          case PrestoSqlParser::TIME_WITH_TIME_ZONE:
          case PrestoSqlParser::TIMESTAMP_WITH_TIME_ZONE:
          case PrestoSqlParser::DOUBLE_PRECISION: {
            setState(465);
            type(0);
            break;
          }

          default:
            throw NoViableAltException(this);
        }
        break;
      }

      case 24: {
        _localctx = _tracker.createInstance<PrestoSqlParser::CreateViewContext>(
            _localctx);
        enterOuterAlt(_localctx, 24);
        setState(468);
        match(PrestoSqlParser::CREATE);
        setState(471);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::OR) {
          setState(469);
          match(PrestoSqlParser::OR);
          setState(470);
          match(PrestoSqlParser::REPLACE);
        }
        setState(473);
        match(PrestoSqlParser::VIEW);
        setState(474);
        qualifiedName();
        setState(477);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::SECURITY) {
          setState(475);
          match(PrestoSqlParser::SECURITY);
          setState(476);
          _la = _input->LA(1);
          if (!(_la == PrestoSqlParser::DEFINER

                || _la == PrestoSqlParser::INVOKER)) {
            _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
        }
        setState(479);
        match(PrestoSqlParser::AS);
        setState(480);
        query();
        break;
      }

      case 25: {
        _localctx = _tracker.createInstance<PrestoSqlParser::RenameViewContext>(
            _localctx);
        enterOuterAlt(_localctx, 25);
        setState(482);
        match(PrestoSqlParser::ALTER);
        setState(483);
        match(PrestoSqlParser::VIEW);
        setState(486);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 38, _ctx)) {
          case 1: {
            setState(484);
            match(PrestoSqlParser::IF);
            setState(485);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(488);
        antlrcpp::downCast<RenameViewContext*>(_localctx)->from =
            qualifiedName();
        setState(489);
        match(PrestoSqlParser::RENAME);
        setState(490);
        match(PrestoSqlParser::TO);
        setState(491);
        antlrcpp::downCast<RenameViewContext*>(_localctx)->to = qualifiedName();
        break;
      }

      case 26: {
        _localctx = _tracker.createInstance<PrestoSqlParser::DropViewContext>(
            _localctx);
        enterOuterAlt(_localctx, 26);
        setState(493);
        match(PrestoSqlParser::DROP);
        setState(494);
        match(PrestoSqlParser::VIEW);
        setState(497);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 39, _ctx)) {
          case 1: {
            setState(495);
            match(PrestoSqlParser::IF);
            setState(496);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(499);
        qualifiedName();
        break;
      }

      case 27: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::CreateMaterializedViewContext>(
                    _localctx);
        enterOuterAlt(_localctx, 27);
        setState(500);
        match(PrestoSqlParser::CREATE);
        setState(501);
        match(PrestoSqlParser::MATERIALIZED);
        setState(502);
        match(PrestoSqlParser::VIEW);
        setState(506);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 40, _ctx)) {
          case 1: {
            setState(503);
            match(PrestoSqlParser::IF);
            setState(504);
            match(PrestoSqlParser::NOT);
            setState(505);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(508);
        qualifiedName();
        setState(511);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::COMMENT) {
          setState(509);
          match(PrestoSqlParser::COMMENT);
          setState(510);
          string();
        }
        setState(515);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(513);
          match(PrestoSqlParser::WITH);
          setState(514);
          properties();
        }
        setState(517);
        match(PrestoSqlParser::AS);
        setState(523);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 43, _ctx)) {
          case 1: {
            setState(518);
            query();
            break;
          }

          case 2: {
            setState(519);
            match(PrestoSqlParser::T__1);
            setState(520);
            query();
            setState(521);
            match(PrestoSqlParser::T__2);
            break;
          }

          default:
            break;
        }
        break;
      }

      case 28: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::DropMaterializedViewContext>(
                    _localctx);
        enterOuterAlt(_localctx, 28);
        setState(525);
        match(PrestoSqlParser::DROP);
        setState(526);
        match(PrestoSqlParser::MATERIALIZED);
        setState(527);
        match(PrestoSqlParser::VIEW);
        setState(530);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 44, _ctx)) {
          case 1: {
            setState(528);
            match(PrestoSqlParser::IF);
            setState(529);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(532);
        qualifiedName();
        break;
      }

      case 29: {
        _localctx = _tracker.createInstance<
            PrestoSqlParser::RefreshMaterializedViewContext>(_localctx);
        enterOuterAlt(_localctx, 29);
        setState(533);
        match(PrestoSqlParser::REFRESH);
        setState(534);
        match(PrestoSqlParser::MATERIALIZED);
        setState(535);
        match(PrestoSqlParser::VIEW);
        setState(536);
        qualifiedName();
        setState(537);
        match(PrestoSqlParser::WHERE);
        setState(538);
        booleanExpression(0);
        break;
      }

      case 30: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CreateFunctionContext>(
                _localctx);
        enterOuterAlt(_localctx, 30);
        setState(540);
        match(PrestoSqlParser::CREATE);
        setState(543);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::OR) {
          setState(541);
          match(PrestoSqlParser::OR);
          setState(542);
          match(PrestoSqlParser::REPLACE);
        }
        setState(546);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::TEMPORARY) {
          setState(545);
          match(PrestoSqlParser::TEMPORARY);
        }
        setState(548);
        match(PrestoSqlParser::FUNCTION);
        setState(549);
        antlrcpp::downCast<CreateFunctionContext*>(_localctx)->functionName =
            qualifiedName();
        setState(550);
        match(PrestoSqlParser::T__1);
        setState(559);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6508956968051886080) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2335699536833519961) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260209) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & 4323456680975908335) != 0)) {
          setState(551);
          sqlParameterDeclaration();
          setState(556);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(552);
            match(PrestoSqlParser::T__3);
            setState(553);
            sqlParameterDeclaration();
            setState(558);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(561);
        match(PrestoSqlParser::T__2);
        setState(562);
        match(PrestoSqlParser::RETURNS);
        setState(563);
        antlrcpp::downCast<CreateFunctionContext*>(_localctx)->returnType =
            type(0);
        setState(566);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::COMMENT) {
          setState(564);
          match(PrestoSqlParser::COMMENT);
          setState(565);
          string();
        }
        setState(568);
        routineCharacteristics();
        setState(569);
        routineBody();
        break;
      }

      case 31: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::AlterFunctionContext>(
                _localctx);
        enterOuterAlt(_localctx, 31);
        setState(571);
        match(PrestoSqlParser::ALTER);
        setState(572);
        match(PrestoSqlParser::FUNCTION);
        setState(573);
        qualifiedName();
        setState(575);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::T__1) {
          setState(574);
          types();
        }
        setState(577);
        alterRoutineCharacteristics();
        break;
      }

      case 32: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DropFunctionContext>(
                _localctx);
        enterOuterAlt(_localctx, 32);
        setState(579);
        match(PrestoSqlParser::DROP);
        setState(581);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::TEMPORARY) {
          setState(580);
          match(PrestoSqlParser::TEMPORARY);
        }
        setState(583);
        match(PrestoSqlParser::FUNCTION);
        setState(586);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 52, _ctx)) {
          case 1: {
            setState(584);
            match(PrestoSqlParser::IF);
            setState(585);
            match(PrestoSqlParser::EXISTS);
            break;
          }

          default:
            break;
        }
        setState(588);
        qualifiedName();
        setState(590);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::T__1) {
          setState(589);
          types();
        }
        break;
      }

      case 33: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CallContext>(_localctx);
        enterOuterAlt(_localctx, 33);
        setState(592);
        match(PrestoSqlParser::CALL);
        setState(593);
        qualifiedName();
        setState(594);
        match(PrestoSqlParser::T__1);
        setState(603);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6508829423092451292) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2308677939035742217) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260097) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & -4291454694588945) != 0) ||
            _la == PrestoSqlParser::DOUBLE_PRECISION) {
          setState(595);
          callArgument();
          setState(600);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(596);
            match(PrestoSqlParser::T__3);
            setState(597);
            callArgument();
            setState(602);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(605);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 34: {
        _localctx = _tracker.createInstance<PrestoSqlParser::CreateRoleContext>(
            _localctx);
        enterOuterAlt(_localctx, 34);
        setState(607);
        match(PrestoSqlParser::CREATE);
        setState(608);
        match(PrestoSqlParser::ROLE);
        setState(609);
        antlrcpp::downCast<CreateRoleContext*>(_localctx)->name = identifier();
        setState(613);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(610);
          match(PrestoSqlParser::WITH);
          setState(611);
          match(PrestoSqlParser::ADMIN);
          setState(612);
          grantor();
        }
        break;
      }

      case 35: {
        _localctx = _tracker.createInstance<PrestoSqlParser::DropRoleContext>(
            _localctx);
        enterOuterAlt(_localctx, 35);
        setState(615);
        match(PrestoSqlParser::DROP);
        setState(616);
        match(PrestoSqlParser::ROLE);
        setState(617);
        antlrcpp::downCast<DropRoleContext*>(_localctx)->name = identifier();
        break;
      }

      case 36: {
        _localctx = _tracker.createInstance<PrestoSqlParser::GrantRolesContext>(
            _localctx);
        enterOuterAlt(_localctx, 36);
        setState(618);
        match(PrestoSqlParser::GRANT);
        setState(619);
        roles();
        setState(620);
        match(PrestoSqlParser::TO);
        setState(621);
        principal();
        setState(626);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(622);
          match(PrestoSqlParser::T__3);
          setState(623);
          principal();
          setState(628);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(632);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(629);
          match(PrestoSqlParser::WITH);
          setState(630);
          match(PrestoSqlParser::ADMIN);
          setState(631);
          match(PrestoSqlParser::OPTION);
        }
        setState(637);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::GRANTED) {
          setState(634);
          match(PrestoSqlParser::GRANTED);
          setState(635);
          match(PrestoSqlParser::BY);
          setState(636);
          grantor();
        }
        break;
      }

      case 37: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::RevokeRolesContext>(
                _localctx);
        enterOuterAlt(_localctx, 37);
        setState(639);
        match(PrestoSqlParser::REVOKE);
        setState(643);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 60, _ctx)) {
          case 1: {
            setState(640);
            match(PrestoSqlParser::ADMIN);
            setState(641);
            match(PrestoSqlParser::OPTION);
            setState(642);
            match(PrestoSqlParser::FOR);
            break;
          }

          default:
            break;
        }
        setState(645);
        roles();
        setState(646);
        match(PrestoSqlParser::FROM);
        setState(647);
        principal();
        setState(652);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(648);
          match(PrestoSqlParser::T__3);
          setState(649);
          principal();
          setState(654);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(658);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::GRANTED) {
          setState(655);
          match(PrestoSqlParser::GRANTED);
          setState(656);
          match(PrestoSqlParser::BY);
          setState(657);
          grantor();
        }
        break;
      }

      case 38: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SetRoleContext>(_localctx);
        enterOuterAlt(_localctx, 38);
        setState(660);
        match(PrestoSqlParser::SET);
        setState(661);
        match(PrestoSqlParser::ROLE);
        setState(665);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 63, _ctx)) {
          case 1: {
            setState(662);
            match(PrestoSqlParser::ALL);
            break;
          }

          case 2: {
            setState(663);
            match(PrestoSqlParser::NONE);
            break;
          }

          case 3: {
            setState(664);
            antlrcpp::downCast<SetRoleContext*>(_localctx)->role = identifier();
            break;
          }

          default:
            break;
        }
        break;
      }

      case 39: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::GrantContext>(_localctx);
        enterOuterAlt(_localctx, 39);
        setState(667);
        match(PrestoSqlParser::GRANT);
        setState(678);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 65, _ctx)) {
          case 1: {
            setState(668);
            privilege();
            setState(673);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == PrestoSqlParser::T__3) {
              setState(669);
              match(PrestoSqlParser::T__3);
              setState(670);
              privilege();
              setState(675);
              _errHandler->sync(this);
              _la = _input->LA(1);
            }
            break;
          }

          case 2: {
            setState(676);
            match(PrestoSqlParser::ALL);
            setState(677);
            match(PrestoSqlParser::PRIVILEGES);
            break;
          }

          default:
            break;
        }
        setState(680);
        match(PrestoSqlParser::ON);
        setState(682);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::TABLE) {
          setState(681);
          match(PrestoSqlParser::TABLE);
        }
        setState(684);
        qualifiedName();
        setState(685);
        match(PrestoSqlParser::TO);
        setState(686);
        antlrcpp::downCast<GrantContext*>(_localctx)->grantee = principal();
        setState(690);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WITH) {
          setState(687);
          match(PrestoSqlParser::WITH);
          setState(688);
          match(PrestoSqlParser::GRANT);
          setState(689);
          match(PrestoSqlParser::OPTION);
        }
        break;
      }

      case 40: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::RevokeContext>(_localctx);
        enterOuterAlt(_localctx, 40);
        setState(692);
        match(PrestoSqlParser::REVOKE);
        setState(696);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 68, _ctx)) {
          case 1: {
            setState(693);
            match(PrestoSqlParser::GRANT);
            setState(694);
            match(PrestoSqlParser::OPTION);
            setState(695);
            match(PrestoSqlParser::FOR);
            break;
          }

          default:
            break;
        }
        setState(708);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 70, _ctx)) {
          case 1: {
            setState(698);
            privilege();
            setState(703);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == PrestoSqlParser::T__3) {
              setState(699);
              match(PrestoSqlParser::T__3);
              setState(700);
              privilege();
              setState(705);
              _errHandler->sync(this);
              _la = _input->LA(1);
            }
            break;
          }

          case 2: {
            setState(706);
            match(PrestoSqlParser::ALL);
            setState(707);
            match(PrestoSqlParser::PRIVILEGES);
            break;
          }

          default:
            break;
        }
        setState(710);
        match(PrestoSqlParser::ON);
        setState(712);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::TABLE) {
          setState(711);
          match(PrestoSqlParser::TABLE);
        }
        setState(714);
        qualifiedName();
        setState(715);
        match(PrestoSqlParser::FROM);
        setState(716);
        antlrcpp::downCast<RevokeContext*>(_localctx)->grantee = principal();
        break;
      }

      case 41: {
        _localctx = _tracker.createInstance<PrestoSqlParser::ShowGrantsContext>(
            _localctx);
        enterOuterAlt(_localctx, 41);
        setState(718);
        match(PrestoSqlParser::SHOW);
        setState(719);
        match(PrestoSqlParser::GRANTS);
        setState(725);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::ON) {
          setState(720);
          match(PrestoSqlParser::ON);
          setState(722);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == PrestoSqlParser::TABLE) {
            setState(721);
            match(PrestoSqlParser::TABLE);
          }
          setState(724);
          qualifiedName();
        }
        break;
      }

      case 42: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ExplainContext>(_localctx);
        enterOuterAlt(_localctx, 42);
        setState(727);
        match(PrestoSqlParser::EXPLAIN);
        setState(729);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 74, _ctx)) {
          case 1: {
            setState(728);
            match(PrestoSqlParser::ANALYZE);
            break;
          }

          default:
            break;
        }
        setState(732);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::VERBOSE) {
          setState(731);
          match(PrestoSqlParser::VERBOSE);
        }
        setState(745);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 77, _ctx)) {
          case 1: {
            setState(734);
            match(PrestoSqlParser::T__1);
            setState(735);
            explainOption();
            setState(740);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == PrestoSqlParser::T__3) {
              setState(736);
              match(PrestoSqlParser::T__3);
              setState(737);
              explainOption();
              setState(742);
              _errHandler->sync(this);
              _la = _input->LA(1);
            }
            setState(743);
            match(PrestoSqlParser::T__2);
            break;
          }

          default:
            break;
        }
        setState(747);
        statement();
        break;
      }

      case 43: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowCreateTableContext>(
                _localctx);
        enterOuterAlt(_localctx, 43);
        setState(748);
        match(PrestoSqlParser::SHOW);
        setState(749);
        match(PrestoSqlParser::CREATE);
        setState(750);
        match(PrestoSqlParser::TABLE);
        setState(751);
        qualifiedName();
        break;
      }

      case 44: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowCreateViewContext>(
                _localctx);
        enterOuterAlt(_localctx, 44);
        setState(752);
        match(PrestoSqlParser::SHOW);
        setState(753);
        match(PrestoSqlParser::CREATE);
        setState(754);
        match(PrestoSqlParser::VIEW);
        setState(755);
        qualifiedName();
        break;
      }

      case 45: {
        _localctx = _tracker.createInstance<
            PrestoSqlParser::ShowCreateMaterializedViewContext>(_localctx);
        enterOuterAlt(_localctx, 45);
        setState(756);
        match(PrestoSqlParser::SHOW);
        setState(757);
        match(PrestoSqlParser::CREATE);
        setState(758);
        match(PrestoSqlParser::MATERIALIZED);
        setState(759);
        match(PrestoSqlParser::VIEW);
        setState(760);
        qualifiedName();
        break;
      }

      case 46: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowCreateFunctionContext>(
                _localctx);
        enterOuterAlt(_localctx, 46);
        setState(761);
        match(PrestoSqlParser::SHOW);
        setState(762);
        match(PrestoSqlParser::CREATE);
        setState(763);
        match(PrestoSqlParser::FUNCTION);
        setState(764);
        qualifiedName();
        setState(766);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::T__1) {
          setState(765);
          types();
        }
        break;
      }

      case 47: {
        _localctx = _tracker.createInstance<PrestoSqlParser::ShowTablesContext>(
            _localctx);
        enterOuterAlt(_localctx, 47);
        setState(768);
        match(PrestoSqlParser::SHOW);
        setState(769);
        match(PrestoSqlParser::TABLES);
        setState(772);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::FROM

            || _la == PrestoSqlParser::IN) {
          setState(770);
          _la = _input->LA(1);
          if (!(_la == PrestoSqlParser::FROM

                || _la == PrestoSqlParser::IN)) {
            _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(771);
          qualifiedName();
        }
        setState(780);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::LIKE) {
          setState(774);
          match(PrestoSqlParser::LIKE);
          setState(775);
          antlrcpp::downCast<ShowTablesContext*>(_localctx)->pattern = string();
          setState(778);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == PrestoSqlParser::ESCAPE) {
            setState(776);
            match(PrestoSqlParser::ESCAPE);
            setState(777);
            antlrcpp::downCast<ShowTablesContext*>(_localctx)->escape =
                string();
          }
        }
        break;
      }

      case 48: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowSchemasContext>(
                _localctx);
        enterOuterAlt(_localctx, 48);
        setState(782);
        match(PrestoSqlParser::SHOW);
        setState(783);
        match(PrestoSqlParser::SCHEMAS);
        setState(786);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::FROM

            || _la == PrestoSqlParser::IN) {
          setState(784);
          _la = _input->LA(1);
          if (!(_la == PrestoSqlParser::FROM

                || _la == PrestoSqlParser::IN)) {
            _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(785);
          identifier();
        }
        setState(794);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::LIKE) {
          setState(788);
          match(PrestoSqlParser::LIKE);
          setState(789);
          antlrcpp::downCast<ShowSchemasContext*>(_localctx)->pattern =
              string();
          setState(792);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == PrestoSqlParser::ESCAPE) {
            setState(790);
            match(PrestoSqlParser::ESCAPE);
            setState(791);
            antlrcpp::downCast<ShowSchemasContext*>(_localctx)->escape =
                string();
          }
        }
        break;
      }

      case 49: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowCatalogsContext>(
                _localctx);
        enterOuterAlt(_localctx, 49);
        setState(796);
        match(PrestoSqlParser::SHOW);
        setState(797);
        match(PrestoSqlParser::CATALOGS);
        setState(804);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::LIKE) {
          setState(798);
          match(PrestoSqlParser::LIKE);
          setState(799);
          antlrcpp::downCast<ShowCatalogsContext*>(_localctx)->pattern =
              string();
          setState(802);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == PrestoSqlParser::ESCAPE) {
            setState(800);
            match(PrestoSqlParser::ESCAPE);
            setState(801);
            antlrcpp::downCast<ShowCatalogsContext*>(_localctx)->escape =
                string();
          }
        }
        break;
      }

      case 50: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowColumnsContext>(
                _localctx);
        enterOuterAlt(_localctx, 50);
        setState(806);
        match(PrestoSqlParser::SHOW);
        setState(807);
        match(PrestoSqlParser::COLUMNS);
        setState(808);
        _la = _input->LA(1);
        if (!(_la == PrestoSqlParser::FROM

              || _la == PrestoSqlParser::IN)) {
          _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(809);
        qualifiedName();
        break;
      }

      case 51: {
        _localctx = _tracker.createInstance<PrestoSqlParser::ShowStatsContext>(
            _localctx);
        enterOuterAlt(_localctx, 51);
        setState(810);
        match(PrestoSqlParser::SHOW);
        setState(811);
        match(PrestoSqlParser::STATS);
        setState(812);
        match(PrestoSqlParser::FOR);
        setState(813);
        qualifiedName();
        break;
      }

      case 52: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowStatsForQueryContext>(
                _localctx);
        enterOuterAlt(_localctx, 52);
        setState(814);
        match(PrestoSqlParser::SHOW);
        setState(815);
        match(PrestoSqlParser::STATS);
        setState(816);
        match(PrestoSqlParser::FOR);
        setState(817);
        match(PrestoSqlParser::T__1);
        setState(818);
        querySpecification();
        setState(819);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 53: {
        _localctx = _tracker.createInstance<PrestoSqlParser::ShowRolesContext>(
            _localctx);
        enterOuterAlt(_localctx, 53);
        setState(821);
        match(PrestoSqlParser::SHOW);
        setState(823);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::CURRENT) {
          setState(822);
          match(PrestoSqlParser::CURRENT);
        }
        setState(825);
        match(PrestoSqlParser::ROLES);
        setState(828);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::FROM

            || _la == PrestoSqlParser::IN) {
          setState(826);
          _la = _input->LA(1);
          if (!(_la == PrestoSqlParser::FROM

                || _la == PrestoSqlParser::IN)) {
            _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(827);
          identifier();
        }
        break;
      }

      case 54: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowRoleGrantsContext>(
                _localctx);
        enterOuterAlt(_localctx, 54);
        setState(830);
        match(PrestoSqlParser::SHOW);
        setState(831);
        match(PrestoSqlParser::ROLE);
        setState(832);
        match(PrestoSqlParser::GRANTS);
        setState(835);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::FROM

            || _la == PrestoSqlParser::IN) {
          setState(833);
          _la = _input->LA(1);
          if (!(_la == PrestoSqlParser::FROM

                || _la == PrestoSqlParser::IN)) {
            _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(834);
          identifier();
        }
        break;
      }

      case 55: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowColumnsContext>(
                _localctx);
        enterOuterAlt(_localctx, 55);
        setState(837);
        match(PrestoSqlParser::DESCRIBE);
        setState(838);
        qualifiedName();
        break;
      }

      case 56: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowColumnsContext>(
                _localctx);
        enterOuterAlt(_localctx, 56);
        setState(839);
        match(PrestoSqlParser::DESC);
        setState(840);
        qualifiedName();
        break;
      }

      case 57: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowFunctionsContext>(
                _localctx);
        enterOuterAlt(_localctx, 57);
        setState(841);
        match(PrestoSqlParser::SHOW);
        setState(842);
        match(PrestoSqlParser::FUNCTIONS);
        setState(849);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::LIKE) {
          setState(843);
          match(PrestoSqlParser::LIKE);
          setState(844);
          antlrcpp::downCast<ShowFunctionsContext*>(_localctx)->pattern =
              string();
          setState(847);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == PrestoSqlParser::ESCAPE) {
            setState(845);
            match(PrestoSqlParser::ESCAPE);
            setState(846);
            antlrcpp::downCast<ShowFunctionsContext*>(_localctx)->escape =
                string();
          }
        }
        break;
      }

      case 58: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ShowSessionContext>(
                _localctx);
        enterOuterAlt(_localctx, 58);
        setState(851);
        match(PrestoSqlParser::SHOW);
        setState(852);
        match(PrestoSqlParser::SESSION);
        setState(859);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::LIKE) {
          setState(853);
          match(PrestoSqlParser::LIKE);
          setState(854);
          antlrcpp::downCast<ShowSessionContext*>(_localctx)->pattern =
              string();
          setState(857);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == PrestoSqlParser::ESCAPE) {
            setState(855);
            match(PrestoSqlParser::ESCAPE);
            setState(856);
            antlrcpp::downCast<ShowSessionContext*>(_localctx)->escape =
                string();
          }
        }
        break;
      }

      case 59: {
        _localctx = _tracker.createInstance<PrestoSqlParser::SetSessionContext>(
            _localctx);
        enterOuterAlt(_localctx, 59);
        setState(861);
        match(PrestoSqlParser::SET);
        setState(862);
        match(PrestoSqlParser::SESSION);
        setState(863);
        qualifiedName();
        setState(864);
        match(PrestoSqlParser::EQ);
        setState(865);
        expression();
        break;
      }

      case 60: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ResetSessionContext>(
                _localctx);
        enterOuterAlt(_localctx, 60);
        setState(867);
        match(PrestoSqlParser::RESET);
        setState(868);
        match(PrestoSqlParser::SESSION);
        setState(869);
        qualifiedName();
        break;
      }

      case 61: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::StartTransactionContext>(
                _localctx);
        enterOuterAlt(_localctx, 61);
        setState(870);
        match(PrestoSqlParser::START);
        setState(871);
        match(PrestoSqlParser::TRANSACTION);
        setState(880);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::ISOLATION

            || _la == PrestoSqlParser::READ) {
          setState(872);
          transactionMode();
          setState(877);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(873);
            match(PrestoSqlParser::T__3);
            setState(874);
            transactionMode();
            setState(879);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        break;
      }

      case 62: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CommitContext>(_localctx);
        enterOuterAlt(_localctx, 62);
        setState(882);
        match(PrestoSqlParser::COMMIT);
        setState(884);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WORK) {
          setState(883);
          match(PrestoSqlParser::WORK);
        }
        break;
      }

      case 63: {
        _localctx = _tracker.createInstance<PrestoSqlParser::RollbackContext>(
            _localctx);
        enterOuterAlt(_localctx, 63);
        setState(886);
        match(PrestoSqlParser::ROLLBACK);
        setState(888);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WORK) {
          setState(887);
          match(PrestoSqlParser::WORK);
        }
        break;
      }

      case 64: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::PrepareContext>(_localctx);
        enterOuterAlt(_localctx, 64);
        setState(890);
        match(PrestoSqlParser::PREPARE);
        setState(891);
        identifier();
        setState(892);
        match(PrestoSqlParser::FROM);
        setState(893);
        statement();
        break;
      }

      case 65: {
        _localctx = _tracker.createInstance<PrestoSqlParser::DeallocateContext>(
            _localctx);
        enterOuterAlt(_localctx, 65);
        setState(895);
        match(PrestoSqlParser::DEALLOCATE);
        setState(896);
        match(PrestoSqlParser::PREPARE);
        setState(897);
        identifier();
        break;
      }

      case 66: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ExecuteContext>(_localctx);
        enterOuterAlt(_localctx, 66);
        setState(898);
        match(PrestoSqlParser::EXECUTE);
        setState(899);
        identifier();
        setState(909);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::USING) {
          setState(900);
          match(PrestoSqlParser::USING);
          setState(901);
          expression();
          setState(906);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(902);
            match(PrestoSqlParser::T__3);
            setState(903);
            expression();
            setState(908);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        break;
      }

      case 67: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DescribeInputContext>(
                _localctx);
        enterOuterAlt(_localctx, 67);
        setState(911);
        match(PrestoSqlParser::DESCRIBE);
        setState(912);
        match(PrestoSqlParser::INPUT);
        setState(913);
        identifier();
        break;
      }

      case 68: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DescribeOutputContext>(
                _localctx);
        enterOuterAlt(_localctx, 68);
        setState(914);
        match(PrestoSqlParser::DESCRIBE);
        setState(915);
        match(PrestoSqlParser::OUTPUT);
        setState(916);
        identifier();
        break;
      }

      case 69: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UpdateContext>(_localctx);
        enterOuterAlt(_localctx, 69);
        setState(917);
        match(PrestoSqlParser::UPDATE);
        setState(918);
        qualifiedName();
        setState(919);
        match(PrestoSqlParser::SET);
        setState(920);
        updateAssignment();
        setState(925);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(921);
          match(PrestoSqlParser::T__3);
          setState(922);
          updateAssignment();
          setState(927);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(930);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::WHERE) {
          setState(928);
          match(PrestoSqlParser::WHERE);
          setState(929);
          antlrcpp::downCast<UpdateContext*>(_localctx)->where =
              booleanExpression(0);
        }
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryContext
//------------------------------------------------------------------

PrestoSqlParser::QueryContext::QueryContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::QueryNoWithContext*
PrestoSqlParser::QueryContext::queryNoWith() {
  return getRuleContext<PrestoSqlParser::QueryNoWithContext>(0);
}

PrestoSqlParser::WithContext* PrestoSqlParser::QueryContext::with() {
  return getRuleContext<PrestoSqlParser::WithContext>(0);
}

size_t PrestoSqlParser::QueryContext::getRuleIndex() const {
  return PrestoSqlParser::RuleQuery;
}

void PrestoSqlParser::QueryContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterQuery(this);
}

void PrestoSqlParser::QueryContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitQuery(this);
}

std::any PrestoSqlParser::QueryContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitQuery(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::QueryContext* PrestoSqlParser::query() {
  QueryContext* _localctx =
      _tracker.createInstance<QueryContext>(_ctx, getState());
  enterRule(_localctx, 8, PrestoSqlParser::RuleQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(935);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::WITH) {
      setState(934);
      with();
    }
    setState(937);
    queryNoWith();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WithContext
//------------------------------------------------------------------

PrestoSqlParser::WithContext::WithContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::WithContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

std::vector<PrestoSqlParser::NamedQueryContext*>
PrestoSqlParser::WithContext::namedQuery() {
  return getRuleContexts<PrestoSqlParser::NamedQueryContext>();
}

PrestoSqlParser::NamedQueryContext* PrestoSqlParser::WithContext::namedQuery(
    size_t i) {
  return getRuleContext<PrestoSqlParser::NamedQueryContext>(i);
}

tree::TerminalNode* PrestoSqlParser::WithContext::RECURSIVE() {
  return getToken(PrestoSqlParser::RECURSIVE, 0);
}

size_t PrestoSqlParser::WithContext::getRuleIndex() const {
  return PrestoSqlParser::RuleWith;
}

void PrestoSqlParser::WithContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterWith(this);
}

void PrestoSqlParser::WithContext::exitRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitWith(this);
}

std::any PrestoSqlParser::WithContext::accept(tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitWith(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::WithContext* PrestoSqlParser::with() {
  WithContext* _localctx =
      _tracker.createInstance<WithContext>(_ctx, getState());
  enterRule(_localctx, 10, PrestoSqlParser::RuleWith);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(939);
    match(PrestoSqlParser::WITH);
    setState(941);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::RECURSIVE) {
      setState(940);
      match(PrestoSqlParser::RECURSIVE);
    }
    setState(943);
    namedQuery();
    setState(948);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrestoSqlParser::T__3) {
      setState(944);
      match(PrestoSqlParser::T__3);
      setState(945);
      namedQuery();
      setState(950);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableElementContext
//------------------------------------------------------------------

PrestoSqlParser::TableElementContext::TableElementContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::ConstraintSpecificationContext*
PrestoSqlParser::TableElementContext::constraintSpecification() {
  return getRuleContext<PrestoSqlParser::ConstraintSpecificationContext>(0);
}

PrestoSqlParser::ColumnDefinitionContext*
PrestoSqlParser::TableElementContext::columnDefinition() {
  return getRuleContext<PrestoSqlParser::ColumnDefinitionContext>(0);
}

PrestoSqlParser::LikeClauseContext*
PrestoSqlParser::TableElementContext::likeClause() {
  return getRuleContext<PrestoSqlParser::LikeClauseContext>(0);
}

size_t PrestoSqlParser::TableElementContext::getRuleIndex() const {
  return PrestoSqlParser::RuleTableElement;
}

void PrestoSqlParser::TableElementContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTableElement(this);
}

void PrestoSqlParser::TableElementContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTableElement(this);
}

std::any PrestoSqlParser::TableElementContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTableElement(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::TableElementContext* PrestoSqlParser::tableElement() {
  TableElementContext* _localctx =
      _tracker.createInstance<TableElementContext>(_ctx, getState());
  enterRule(_localctx, 12, PrestoSqlParser::RuleTableElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(954);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 106, _ctx)) {
      case 1: {
        enterOuterAlt(_localctx, 1);
        setState(951);
        constraintSpecification();
        break;
      }

      case 2: {
        enterOuterAlt(_localctx, 2);
        setState(952);
        columnDefinition();
        break;
      }

      case 3: {
        enterOuterAlt(_localctx, 3);
        setState(953);
        likeClause();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnDefinitionContext
//------------------------------------------------------------------

PrestoSqlParser::ColumnDefinitionContext::ColumnDefinitionContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ColumnDefinitionContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::TypeContext* PrestoSqlParser::ColumnDefinitionContext::type() {
  return getRuleContext<PrestoSqlParser::TypeContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ColumnDefinitionContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

tree::TerminalNode* PrestoSqlParser::ColumnDefinitionContext::NULL_LITERAL() {
  return getToken(PrestoSqlParser::NULL_LITERAL, 0);
}

tree::TerminalNode* PrestoSqlParser::ColumnDefinitionContext::COMMENT() {
  return getToken(PrestoSqlParser::COMMENT, 0);
}

PrestoSqlParser::StringContext*
PrestoSqlParser::ColumnDefinitionContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ColumnDefinitionContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

PrestoSqlParser::PropertiesContext*
PrestoSqlParser::ColumnDefinitionContext::properties() {
  return getRuleContext<PrestoSqlParser::PropertiesContext>(0);
}

size_t PrestoSqlParser::ColumnDefinitionContext::getRuleIndex() const {
  return PrestoSqlParser::RuleColumnDefinition;
}

void PrestoSqlParser::ColumnDefinitionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumnDefinition(this);
}

void PrestoSqlParser::ColumnDefinitionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumnDefinition(this);
}

std::any PrestoSqlParser::ColumnDefinitionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitColumnDefinition(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ColumnDefinitionContext* PrestoSqlParser::columnDefinition() {
  ColumnDefinitionContext* _localctx =
      _tracker.createInstance<ColumnDefinitionContext>(_ctx, getState());
  enterRule(_localctx, 14, PrestoSqlParser::RuleColumnDefinition);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(956);
    identifier();
    setState(957);
    type(0);
    setState(960);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::NOT) {
      setState(958);
      match(PrestoSqlParser::NOT);
      setState(959);
      match(PrestoSqlParser::NULL_LITERAL);
    }
    setState(964);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::COMMENT) {
      setState(962);
      match(PrestoSqlParser::COMMENT);
      setState(963);
      string();
    }
    setState(968);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::WITH) {
      setState(966);
      match(PrestoSqlParser::WITH);
      setState(967);
      properties();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LikeClauseContext
//------------------------------------------------------------------

PrestoSqlParser::LikeClauseContext::LikeClauseContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::LikeClauseContext::LIKE() {
  return getToken(PrestoSqlParser::LIKE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::LikeClauseContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::LikeClauseContext::PROPERTIES() {
  return getToken(PrestoSqlParser::PROPERTIES, 0);
}

tree::TerminalNode* PrestoSqlParser::LikeClauseContext::INCLUDING() {
  return getToken(PrestoSqlParser::INCLUDING, 0);
}

tree::TerminalNode* PrestoSqlParser::LikeClauseContext::EXCLUDING() {
  return getToken(PrestoSqlParser::EXCLUDING, 0);
}

size_t PrestoSqlParser::LikeClauseContext::getRuleIndex() const {
  return PrestoSqlParser::RuleLikeClause;
}

void PrestoSqlParser::LikeClauseContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterLikeClause(this);
}

void PrestoSqlParser::LikeClauseContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitLikeClause(this);
}

std::any PrestoSqlParser::LikeClauseContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitLikeClause(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::LikeClauseContext* PrestoSqlParser::likeClause() {
  LikeClauseContext* _localctx =
      _tracker.createInstance<LikeClauseContext>(_ctx, getState());
  enterRule(_localctx, 16, PrestoSqlParser::RuleLikeClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(970);
    match(PrestoSqlParser::LIKE);
    setState(971);
    qualifiedName();
    setState(974);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::EXCLUDING

        || _la == PrestoSqlParser::INCLUDING) {
      setState(972);
      antlrcpp::downCast<LikeClauseContext*>(_localctx)->optionType =
          _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == PrestoSqlParser::EXCLUDING

            || _la == PrestoSqlParser::INCLUDING)) {
        antlrcpp::downCast<LikeClauseContext*>(_localctx)->optionType =
            _errHandler->recoverInline(this);
      } else {
        _errHandler->reportMatch(this);
        consume();
      }
      setState(973);
      match(PrestoSqlParser::PROPERTIES);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertiesContext
//------------------------------------------------------------------

PrestoSqlParser::PropertiesContext::PropertiesContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::PropertyContext*>
PrestoSqlParser::PropertiesContext::property() {
  return getRuleContexts<PrestoSqlParser::PropertyContext>();
}

PrestoSqlParser::PropertyContext* PrestoSqlParser::PropertiesContext::property(
    size_t i) {
  return getRuleContext<PrestoSqlParser::PropertyContext>(i);
}

size_t PrestoSqlParser::PropertiesContext::getRuleIndex() const {
  return PrestoSqlParser::RuleProperties;
}

void PrestoSqlParser::PropertiesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperties(this);
}

void PrestoSqlParser::PropertiesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperties(this);
}

std::any PrestoSqlParser::PropertiesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitProperties(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::PropertiesContext* PrestoSqlParser::properties() {
  PropertiesContext* _localctx =
      _tracker.createInstance<PropertiesContext>(_ctx, getState());
  enterRule(_localctx, 18, PrestoSqlParser::RuleProperties);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(976);
    match(PrestoSqlParser::T__1);
    setState(977);
    property();
    setState(982);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrestoSqlParser::T__3) {
      setState(978);
      match(PrestoSqlParser::T__3);
      setState(979);
      property();
      setState(984);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(985);
    match(PrestoSqlParser::T__2);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyContext
//------------------------------------------------------------------

PrestoSqlParser::PropertyContext::PropertyContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::PropertyContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::PropertyContext::EQ() {
  return getToken(PrestoSqlParser::EQ, 0);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::PropertyContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

size_t PrestoSqlParser::PropertyContext::getRuleIndex() const {
  return PrestoSqlParser::RuleProperty;
}

void PrestoSqlParser::PropertyContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty(this);
}

void PrestoSqlParser::PropertyContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty(this);
}

std::any PrestoSqlParser::PropertyContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitProperty(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::PropertyContext* PrestoSqlParser::property() {
  PropertyContext* _localctx =
      _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 20, PrestoSqlParser::RuleProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(987);
    identifier();
    setState(988);
    match(PrestoSqlParser::EQ);
    setState(989);
    expression();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SqlParameterDeclarationContext
//------------------------------------------------------------------

PrestoSqlParser::SqlParameterDeclarationContext::SqlParameterDeclarationContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::SqlParameterDeclarationContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::TypeContext*
PrestoSqlParser::SqlParameterDeclarationContext::type() {
  return getRuleContext<PrestoSqlParser::TypeContext>(0);
}

size_t PrestoSqlParser::SqlParameterDeclarationContext::getRuleIndex() const {
  return PrestoSqlParser::RuleSqlParameterDeclaration;
}

void PrestoSqlParser::SqlParameterDeclarationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSqlParameterDeclaration(this);
}

void PrestoSqlParser::SqlParameterDeclarationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSqlParameterDeclaration(this);
}

std::any PrestoSqlParser::SqlParameterDeclarationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSqlParameterDeclaration(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::SqlParameterDeclarationContext*
PrestoSqlParser::sqlParameterDeclaration() {
  SqlParameterDeclarationContext* _localctx =
      _tracker.createInstance<SqlParameterDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 22, PrestoSqlParser::RuleSqlParameterDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(991);
    identifier();
    setState(992);
    type(0);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RoutineCharacteristicsContext
//------------------------------------------------------------------

PrestoSqlParser::RoutineCharacteristicsContext::RoutineCharacteristicsContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::RoutineCharacteristicContext*>
PrestoSqlParser::RoutineCharacteristicsContext::routineCharacteristic() {
  return getRuleContexts<PrestoSqlParser::RoutineCharacteristicContext>();
}

PrestoSqlParser::RoutineCharacteristicContext*
PrestoSqlParser::RoutineCharacteristicsContext::routineCharacteristic(
    size_t i) {
  return getRuleContext<PrestoSqlParser::RoutineCharacteristicContext>(i);
}

size_t PrestoSqlParser::RoutineCharacteristicsContext::getRuleIndex() const {
  return PrestoSqlParser::RuleRoutineCharacteristics;
}

void PrestoSqlParser::RoutineCharacteristicsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoutineCharacteristics(this);
}

void PrestoSqlParser::RoutineCharacteristicsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoutineCharacteristics(this);
}

std::any PrestoSqlParser::RoutineCharacteristicsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRoutineCharacteristics(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::RoutineCharacteristicsContext*
PrestoSqlParser::routineCharacteristics() {
  RoutineCharacteristicsContext* _localctx =
      _tracker.createInstance<RoutineCharacteristicsContext>(_ctx, getState());
  enterRule(_localctx, 24, PrestoSqlParser::RuleRoutineCharacteristics);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(997);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrestoSqlParser::CALLED

           || _la == PrestoSqlParser::DETERMINISTIC ||
           ((((_la - 112) & ~0x3fULL) == 0) &&
            ((1ULL << (_la - 112)) & 576460752311812097) != 0)) {
      setState(994);
      routineCharacteristic();
      setState(999);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RoutineCharacteristicContext
//------------------------------------------------------------------

PrestoSqlParser::RoutineCharacteristicContext::RoutineCharacteristicContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::RoutineCharacteristicContext::LANGUAGE() {
  return getToken(PrestoSqlParser::LANGUAGE, 0);
}

PrestoSqlParser::LanguageContext*
PrestoSqlParser::RoutineCharacteristicContext::language() {
  return getRuleContext<PrestoSqlParser::LanguageContext>(0);
}

PrestoSqlParser::DeterminismContext*
PrestoSqlParser::RoutineCharacteristicContext::determinism() {
  return getRuleContext<PrestoSqlParser::DeterminismContext>(0);
}

PrestoSqlParser::NullCallClauseContext*
PrestoSqlParser::RoutineCharacteristicContext::nullCallClause() {
  return getRuleContext<PrestoSqlParser::NullCallClauseContext>(0);
}

size_t PrestoSqlParser::RoutineCharacteristicContext::getRuleIndex() const {
  return PrestoSqlParser::RuleRoutineCharacteristic;
}

void PrestoSqlParser::RoutineCharacteristicContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoutineCharacteristic(this);
}

void PrestoSqlParser::RoutineCharacteristicContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoutineCharacteristic(this);
}

std::any PrestoSqlParser::RoutineCharacteristicContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRoutineCharacteristic(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::RoutineCharacteristicContext*
PrestoSqlParser::routineCharacteristic() {
  RoutineCharacteristicContext* _localctx =
      _tracker.createInstance<RoutineCharacteristicContext>(_ctx, getState());
  enterRule(_localctx, 26, PrestoSqlParser::RuleRoutineCharacteristic);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1004);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::LANGUAGE: {
        enterOuterAlt(_localctx, 1);
        setState(1000);
        match(PrestoSqlParser::LANGUAGE);
        setState(1001);
        language();
        break;
      }

      case PrestoSqlParser::DETERMINISTIC:
      case PrestoSqlParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(1002);
        determinism();
        break;
      }

      case PrestoSqlParser::CALLED:
      case PrestoSqlParser::RETURNS: {
        enterOuterAlt(_localctx, 3);
        setState(1003);
        nullCallClause();
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlterRoutineCharacteristicsContext
//------------------------------------------------------------------

PrestoSqlParser::AlterRoutineCharacteristicsContext::
    AlterRoutineCharacteristicsContext(
        ParserRuleContext* parent,
        size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::AlterRoutineCharacteristicContext*>
PrestoSqlParser::AlterRoutineCharacteristicsContext::
    alterRoutineCharacteristic() {
  return getRuleContexts<PrestoSqlParser::AlterRoutineCharacteristicContext>();
}

PrestoSqlParser::AlterRoutineCharacteristicContext*
PrestoSqlParser::AlterRoutineCharacteristicsContext::alterRoutineCharacteristic(
    size_t i) {
  return getRuleContext<PrestoSqlParser::AlterRoutineCharacteristicContext>(i);
}

size_t PrestoSqlParser::AlterRoutineCharacteristicsContext::getRuleIndex()
    const {
  return PrestoSqlParser::RuleAlterRoutineCharacteristics;
}

void PrestoSqlParser::AlterRoutineCharacteristicsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlterRoutineCharacteristics(this);
}

void PrestoSqlParser::AlterRoutineCharacteristicsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlterRoutineCharacteristics(this);
}

std::any PrestoSqlParser::AlterRoutineCharacteristicsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAlterRoutineCharacteristics(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::AlterRoutineCharacteristicsContext*
PrestoSqlParser::alterRoutineCharacteristics() {
  AlterRoutineCharacteristicsContext* _localctx =
      _tracker.createInstance<AlterRoutineCharacteristicsContext>(
          _ctx, getState());
  enterRule(_localctx, 28, PrestoSqlParser::RuleAlterRoutineCharacteristics);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1009);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrestoSqlParser::CALLED || _la == PrestoSqlParser::RETURNS) {
      setState(1006);
      alterRoutineCharacteristic();
      setState(1011);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AlterRoutineCharacteristicContext
//------------------------------------------------------------------

PrestoSqlParser::AlterRoutineCharacteristicContext::
    AlterRoutineCharacteristicContext(
        ParserRuleContext* parent,
        size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::NullCallClauseContext*
PrestoSqlParser::AlterRoutineCharacteristicContext::nullCallClause() {
  return getRuleContext<PrestoSqlParser::NullCallClauseContext>(0);
}

size_t PrestoSqlParser::AlterRoutineCharacteristicContext::getRuleIndex()
    const {
  return PrestoSqlParser::RuleAlterRoutineCharacteristic;
}

void PrestoSqlParser::AlterRoutineCharacteristicContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAlterRoutineCharacteristic(this);
}

void PrestoSqlParser::AlterRoutineCharacteristicContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAlterRoutineCharacteristic(this);
}

std::any PrestoSqlParser::AlterRoutineCharacteristicContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAlterRoutineCharacteristic(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::AlterRoutineCharacteristicContext*
PrestoSqlParser::alterRoutineCharacteristic() {
  AlterRoutineCharacteristicContext* _localctx =
      _tracker.createInstance<AlterRoutineCharacteristicContext>(
          _ctx, getState());
  enterRule(_localctx, 30, PrestoSqlParser::RuleAlterRoutineCharacteristic);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1012);
    nullCallClause();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RoutineBodyContext
//------------------------------------------------------------------

PrestoSqlParser::RoutineBodyContext::RoutineBodyContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::ReturnStatementContext*
PrestoSqlParser::RoutineBodyContext::returnStatement() {
  return getRuleContext<PrestoSqlParser::ReturnStatementContext>(0);
}

PrestoSqlParser::ExternalBodyReferenceContext*
PrestoSqlParser::RoutineBodyContext::externalBodyReference() {
  return getRuleContext<PrestoSqlParser::ExternalBodyReferenceContext>(0);
}

size_t PrestoSqlParser::RoutineBodyContext::getRuleIndex() const {
  return PrestoSqlParser::RuleRoutineBody;
}

void PrestoSqlParser::RoutineBodyContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoutineBody(this);
}

void PrestoSqlParser::RoutineBodyContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoutineBody(this);
}

std::any PrestoSqlParser::RoutineBodyContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRoutineBody(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::RoutineBodyContext* PrestoSqlParser::routineBody() {
  RoutineBodyContext* _localctx =
      _tracker.createInstance<RoutineBodyContext>(_ctx, getState());
  enterRule(_localctx, 32, PrestoSqlParser::RuleRoutineBody);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1016);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::RETURN: {
        enterOuterAlt(_localctx, 1);
        setState(1014);
        returnStatement();
        break;
      }

      case PrestoSqlParser::EXTERNAL: {
        enterOuterAlt(_localctx, 2);
        setState(1015);
        externalBodyReference();
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext
//------------------------------------------------------------------

PrestoSqlParser::ReturnStatementContext::ReturnStatementContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ReturnStatementContext::RETURN() {
  return getToken(PrestoSqlParser::RETURN, 0);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::ReturnStatementContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

size_t PrestoSqlParser::ReturnStatementContext::getRuleIndex() const {
  return PrestoSqlParser::RuleReturnStatement;
}

void PrestoSqlParser::ReturnStatementContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturnStatement(this);
}

void PrestoSqlParser::ReturnStatementContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturnStatement(this);
}

std::any PrestoSqlParser::ReturnStatementContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ReturnStatementContext* PrestoSqlParser::returnStatement() {
  ReturnStatementContext* _localctx =
      _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, PrestoSqlParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1018);
    match(PrestoSqlParser::RETURN);
    setState(1019);
    expression();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternalBodyReferenceContext
//------------------------------------------------------------------

PrestoSqlParser::ExternalBodyReferenceContext::ExternalBodyReferenceContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ExternalBodyReferenceContext::EXTERNAL() {
  return getToken(PrestoSqlParser::EXTERNAL, 0);
}

tree::TerminalNode* PrestoSqlParser::ExternalBodyReferenceContext::NAME() {
  return getToken(PrestoSqlParser::NAME, 0);
}

PrestoSqlParser::ExternalRoutineNameContext*
PrestoSqlParser::ExternalBodyReferenceContext::externalRoutineName() {
  return getRuleContext<PrestoSqlParser::ExternalRoutineNameContext>(0);
}

size_t PrestoSqlParser::ExternalBodyReferenceContext::getRuleIndex() const {
  return PrestoSqlParser::RuleExternalBodyReference;
}

void PrestoSqlParser::ExternalBodyReferenceContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternalBodyReference(this);
}

void PrestoSqlParser::ExternalBodyReferenceContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternalBodyReference(this);
}

std::any PrestoSqlParser::ExternalBodyReferenceContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExternalBodyReference(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ExternalBodyReferenceContext*
PrestoSqlParser::externalBodyReference() {
  ExternalBodyReferenceContext* _localctx =
      _tracker.createInstance<ExternalBodyReferenceContext>(_ctx, getState());
  enterRule(_localctx, 36, PrestoSqlParser::RuleExternalBodyReference);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1021);
    match(PrestoSqlParser::EXTERNAL);
    setState(1024);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::NAME) {
      setState(1022);
      match(PrestoSqlParser::NAME);
      setState(1023);
      externalRoutineName();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LanguageContext
//------------------------------------------------------------------

PrestoSqlParser::LanguageContext::LanguageContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::LanguageContext::SQL() {
  return getToken(PrestoSqlParser::SQL, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::LanguageContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

size_t PrestoSqlParser::LanguageContext::getRuleIndex() const {
  return PrestoSqlParser::RuleLanguage;
}

void PrestoSqlParser::LanguageContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterLanguage(this);
}

void PrestoSqlParser::LanguageContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitLanguage(this);
}

std::any PrestoSqlParser::LanguageContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitLanguage(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::LanguageContext* PrestoSqlParser::language() {
  LanguageContext* _localctx =
      _tracker.createInstance<LanguageContext>(_ctx, getState());
  enterRule(_localctx, 38, PrestoSqlParser::RuleLanguage);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1028);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 117, _ctx)) {
      case 1: {
        enterOuterAlt(_localctx, 1);
        setState(1026);
        match(PrestoSqlParser::SQL);
        break;
      }

      case 2: {
        enterOuterAlt(_localctx, 2);
        setState(1027);
        identifier();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- DeterminismContext
//------------------------------------------------------------------

PrestoSqlParser::DeterminismContext::DeterminismContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::DeterminismContext::DETERMINISTIC() {
  return getToken(PrestoSqlParser::DETERMINISTIC, 0);
}

tree::TerminalNode* PrestoSqlParser::DeterminismContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

size_t PrestoSqlParser::DeterminismContext::getRuleIndex() const {
  return PrestoSqlParser::RuleDeterminism;
}

void PrestoSqlParser::DeterminismContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeterminism(this);
}

void PrestoSqlParser::DeterminismContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeterminism(this);
}

std::any PrestoSqlParser::DeterminismContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDeterminism(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::DeterminismContext* PrestoSqlParser::determinism() {
  DeterminismContext* _localctx =
      _tracker.createInstance<DeterminismContext>(_ctx, getState());
  enterRule(_localctx, 40, PrestoSqlParser::RuleDeterminism);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1033);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::DETERMINISTIC: {
        enterOuterAlt(_localctx, 1);
        setState(1030);
        match(PrestoSqlParser::DETERMINISTIC);
        break;
      }

      case PrestoSqlParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(1031);
        match(PrestoSqlParser::NOT);
        setState(1032);
        match(PrestoSqlParser::DETERMINISTIC);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NullCallClauseContext
//------------------------------------------------------------------

PrestoSqlParser::NullCallClauseContext::NullCallClauseContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::NullCallClauseContext::RETURNS() {
  return getToken(PrestoSqlParser::RETURNS, 0);
}

std::vector<tree::TerminalNode*>
PrestoSqlParser::NullCallClauseContext::NULL_LITERAL() {
  return getTokens(PrestoSqlParser::NULL_LITERAL);
}

tree::TerminalNode* PrestoSqlParser::NullCallClauseContext::NULL_LITERAL(
    size_t i) {
  return getToken(PrestoSqlParser::NULL_LITERAL, i);
}

tree::TerminalNode* PrestoSqlParser::NullCallClauseContext::ON() {
  return getToken(PrestoSqlParser::ON, 0);
}

tree::TerminalNode* PrestoSqlParser::NullCallClauseContext::INPUT() {
  return getToken(PrestoSqlParser::INPUT, 0);
}

tree::TerminalNode* PrestoSqlParser::NullCallClauseContext::CALLED() {
  return getToken(PrestoSqlParser::CALLED, 0);
}

size_t PrestoSqlParser::NullCallClauseContext::getRuleIndex() const {
  return PrestoSqlParser::RuleNullCallClause;
}

void PrestoSqlParser::NullCallClauseContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNullCallClause(this);
}

void PrestoSqlParser::NullCallClauseContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNullCallClause(this);
}

std::any PrestoSqlParser::NullCallClauseContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNullCallClause(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::NullCallClauseContext* PrestoSqlParser::nullCallClause() {
  NullCallClauseContext* _localctx =
      _tracker.createInstance<NullCallClauseContext>(_ctx, getState());
  enterRule(_localctx, 42, PrestoSqlParser::RuleNullCallClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1044);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::RETURNS: {
        enterOuterAlt(_localctx, 1);
        setState(1035);
        match(PrestoSqlParser::RETURNS);
        setState(1036);
        match(PrestoSqlParser::NULL_LITERAL);
        setState(1037);
        match(PrestoSqlParser::ON);
        setState(1038);
        match(PrestoSqlParser::NULL_LITERAL);
        setState(1039);
        match(PrestoSqlParser::INPUT);
        break;
      }

      case PrestoSqlParser::CALLED: {
        enterOuterAlt(_localctx, 2);
        setState(1040);
        match(PrestoSqlParser::CALLED);
        setState(1041);
        match(PrestoSqlParser::ON);
        setState(1042);
        match(PrestoSqlParser::NULL_LITERAL);
        setState(1043);
        match(PrestoSqlParser::INPUT);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExternalRoutineNameContext
//------------------------------------------------------------------

PrestoSqlParser::ExternalRoutineNameContext::ExternalRoutineNameContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ExternalRoutineNameContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

size_t PrestoSqlParser::ExternalRoutineNameContext::getRuleIndex() const {
  return PrestoSqlParser::RuleExternalRoutineName;
}

void PrestoSqlParser::ExternalRoutineNameContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExternalRoutineName(this);
}

void PrestoSqlParser::ExternalRoutineNameContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExternalRoutineName(this);
}

std::any PrestoSqlParser::ExternalRoutineNameContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExternalRoutineName(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ExternalRoutineNameContext*
PrestoSqlParser::externalRoutineName() {
  ExternalRoutineNameContext* _localctx =
      _tracker.createInstance<ExternalRoutineNameContext>(_ctx, getState());
  enterRule(_localctx, 44, PrestoSqlParser::RuleExternalRoutineName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1046);
    identifier();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryNoWithContext
//------------------------------------------------------------------

PrestoSqlParser::QueryNoWithContext::QueryNoWithContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::QueryTermContext*
PrestoSqlParser::QueryNoWithContext::queryTerm() {
  return getRuleContext<PrestoSqlParser::QueryTermContext>(0);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::ORDER() {
  return getToken(PrestoSqlParser::ORDER, 0);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::BY() {
  return getToken(PrestoSqlParser::BY, 0);
}

std::vector<PrestoSqlParser::SortItemContext*>
PrestoSqlParser::QueryNoWithContext::sortItem() {
  return getRuleContexts<PrestoSqlParser::SortItemContext>();
}

PrestoSqlParser::SortItemContext* PrestoSqlParser::QueryNoWithContext::sortItem(
    size_t i) {
  return getRuleContext<PrestoSqlParser::SortItemContext>(i);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::OFFSET() {
  return getToken(PrestoSqlParser::OFFSET, 0);
}

std::vector<tree::TerminalNode*>
PrestoSqlParser::QueryNoWithContext::INTEGER_VALUE() {
  return getTokens(PrestoSqlParser::INTEGER_VALUE);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::INTEGER_VALUE(
    size_t i) {
  return getToken(PrestoSqlParser::INTEGER_VALUE, i);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::LIMIT() {
  return getToken(PrestoSqlParser::LIMIT, 0);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::ROW() {
  return getToken(PrestoSqlParser::ROW, 0);
}

std::vector<tree::TerminalNode*> PrestoSqlParser::QueryNoWithContext::ROWS() {
  return getTokens(PrestoSqlParser::ROWS);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::ROWS(size_t i) {
  return getToken(PrestoSqlParser::ROWS, i);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::ALL() {
  return getToken(PrestoSqlParser::ALL, 0);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::FETCH() {
  return getToken(PrestoSqlParser::FETCH, 0);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::FIRST() {
  return getToken(PrestoSqlParser::FIRST, 0);
}

tree::TerminalNode* PrestoSqlParser::QueryNoWithContext::ONLY() {
  return getToken(PrestoSqlParser::ONLY, 0);
}

size_t PrestoSqlParser::QueryNoWithContext::getRuleIndex() const {
  return PrestoSqlParser::RuleQueryNoWith;
}

void PrestoSqlParser::QueryNoWithContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterQueryNoWith(this);
}

void PrestoSqlParser::QueryNoWithContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitQueryNoWith(this);
}

std::any PrestoSqlParser::QueryNoWithContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitQueryNoWith(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::QueryNoWithContext* PrestoSqlParser::queryNoWith() {
  QueryNoWithContext* _localctx =
      _tracker.createInstance<QueryNoWithContext>(_ctx, getState());
  enterRule(_localctx, 46, PrestoSqlParser::RuleQueryNoWith);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1048);
    queryTerm(0);
    setState(1059);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::ORDER) {
      setState(1049);
      match(PrestoSqlParser::ORDER);
      setState(1050);
      match(PrestoSqlParser::BY);
      setState(1051);
      sortItem();
      setState(1056);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PrestoSqlParser::T__3) {
        setState(1052);
        match(PrestoSqlParser::T__3);
        setState(1053);
        sortItem();
        setState(1058);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1066);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::OFFSET) {
      setState(1061);
      match(PrestoSqlParser::OFFSET);
      setState(1062);
      antlrcpp::downCast<QueryNoWithContext*>(_localctx)->offset =
          match(PrestoSqlParser::INTEGER_VALUE);
      setState(1064);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == PrestoSqlParser::ROW

          || _la == PrestoSqlParser::ROWS) {
        setState(1063);
        _la = _input->LA(1);
        if (!(_la == PrestoSqlParser::ROW

              || _la == PrestoSqlParser::ROWS)) {
          _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
      }
    }
    setState(1077);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::FETCH

        || _la == PrestoSqlParser::LIMIT) {
      setState(1075);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case PrestoSqlParser::LIMIT: {
          setState(1068);
          match(PrestoSqlParser::LIMIT);
          setState(1069);
          antlrcpp::downCast<QueryNoWithContext*>(_localctx)->limit =
              _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == PrestoSqlParser::ALL ||
                _la == PrestoSqlParser::INTEGER_VALUE)) {
            antlrcpp::downCast<QueryNoWithContext*>(_localctx)->limit =
                _errHandler->recoverInline(this);
          } else {
            _errHandler->reportMatch(this);
            consume();
          }
          break;
        }

        case PrestoSqlParser::FETCH: {
          setState(1070);
          match(PrestoSqlParser::FETCH);
          setState(1071);
          match(PrestoSqlParser::FIRST);
          setState(1072);
          antlrcpp::downCast<QueryNoWithContext*>(_localctx)->fetchFirstNRows =
              match(PrestoSqlParser::INTEGER_VALUE);
          setState(1073);
          match(PrestoSqlParser::ROWS);
          setState(1074);
          match(PrestoSqlParser::ONLY);
          break;
        }

        default:
          throw NoViableAltException(this);
      }
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QueryTermContext
//------------------------------------------------------------------

PrestoSqlParser::QueryTermContext::QueryTermContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::QueryTermContext::getRuleIndex() const {
  return PrestoSqlParser::RuleQueryTerm;
}

void PrestoSqlParser::QueryTermContext::copyFrom(QueryTermContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- QueryTermDefaultContext
//------------------------------------------------------------------

PrestoSqlParser::QueryPrimaryContext*
PrestoSqlParser::QueryTermDefaultContext::queryPrimary() {
  return getRuleContext<PrestoSqlParser::QueryPrimaryContext>(0);
}

PrestoSqlParser::QueryTermDefaultContext::QueryTermDefaultContext(
    QueryTermContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::QueryTermDefaultContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterQueryTermDefault(this);
}
void PrestoSqlParser::QueryTermDefaultContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitQueryTermDefault(this);
}

std::any PrestoSqlParser::QueryTermDefaultContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitQueryTermDefault(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SetOperationContext
//------------------------------------------------------------------

std::vector<PrestoSqlParser::QueryTermContext*>
PrestoSqlParser::SetOperationContext::queryTerm() {
  return getRuleContexts<PrestoSqlParser::QueryTermContext>();
}

PrestoSqlParser::QueryTermContext*
PrestoSqlParser::SetOperationContext::queryTerm(size_t i) {
  return getRuleContext<PrestoSqlParser::QueryTermContext>(i);
}

tree::TerminalNode* PrestoSqlParser::SetOperationContext::INTERSECT() {
  return getToken(PrestoSqlParser::INTERSECT, 0);
}

PrestoSqlParser::SetQuantifierContext*
PrestoSqlParser::SetOperationContext::setQuantifier() {
  return getRuleContext<PrestoSqlParser::SetQuantifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SetOperationContext::UNION() {
  return getToken(PrestoSqlParser::UNION, 0);
}

tree::TerminalNode* PrestoSqlParser::SetOperationContext::EXCEPT() {
  return getToken(PrestoSqlParser::EXCEPT, 0);
}

PrestoSqlParser::SetOperationContext::SetOperationContext(
    QueryTermContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SetOperationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetOperation(this);
}
void PrestoSqlParser::SetOperationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetOperation(this);
}

std::any PrestoSqlParser::SetOperationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSetOperation(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::QueryTermContext* PrestoSqlParser::queryTerm() {
  return queryTerm(0);
}

PrestoSqlParser::QueryTermContext* PrestoSqlParser::queryTerm(int precedence) {
  ParserRuleContext* parentContext = _ctx;
  size_t parentState = getState();
  PrestoSqlParser::QueryTermContext* _localctx =
      _tracker.createInstance<QueryTermContext>(_ctx, parentState);
  PrestoSqlParser::QueryTermContext* previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by
                         // generated code.
  size_t startState = 48;
  enterRecursionRule(_localctx, 48, PrestoSqlParser::RuleQueryTerm, precedence);

  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<QueryTermDefaultContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(1080);
    queryPrimary();
    _ctx->stop = _input->LT(-1);
    setState(1096);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 129, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(1094);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 128, _ctx)) {
          case 1: {
            auto newContext = _tracker.createInstance<SetOperationContext>(
                _tracker.createInstance<QueryTermContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->left = previousContext;
            pushNewRecursionContext(newContext, startState, RuleQueryTerm);
            setState(1082);

            if (!(precpred(_ctx, 2)))
              throw FailedPredicateException(this, "precpred(_ctx, 2)");
            setState(1083);
            antlrcpp::downCast<SetOperationContext*>(_localctx)->op =
                match(PrestoSqlParser::INTERSECT);
            setState(1085);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == PrestoSqlParser::ALL

                || _la == PrestoSqlParser::DISTINCT) {
              setState(1084);
              setQuantifier();
            }
            setState(1087);
            antlrcpp::downCast<SetOperationContext*>(_localctx)->right =
                queryTerm(3);
            break;
          }

          case 2: {
            auto newContext = _tracker.createInstance<SetOperationContext>(
                _tracker.createInstance<QueryTermContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->left = previousContext;
            pushNewRecursionContext(newContext, startState, RuleQueryTerm);
            setState(1088);

            if (!(precpred(_ctx, 1)))
              throw FailedPredicateException(this, "precpred(_ctx, 1)");
            setState(1089);
            antlrcpp::downCast<SetOperationContext*>(_localctx)->op =
                _input->LT(1);
            _la = _input->LA(1);
            if (!(_la == PrestoSqlParser::EXCEPT ||
                  _la == PrestoSqlParser::UNION)) {
              antlrcpp::downCast<SetOperationContext*>(_localctx)->op =
                  _errHandler->recoverInline(this);
            } else {
              _errHandler->reportMatch(this);
              consume();
            }
            setState(1091);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == PrestoSqlParser::ALL

                || _la == PrestoSqlParser::DISTINCT) {
              setState(1090);
              setQuantifier();
            }
            setState(1093);
            antlrcpp::downCast<SetOperationContext*>(_localctx)->right =
                queryTerm(2);
            break;
          }

          default:
            break;
        }
      }
      setState(1098);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 129, _ctx);
    }
  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- QueryPrimaryContext
//------------------------------------------------------------------

PrestoSqlParser::QueryPrimaryContext::QueryPrimaryContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::QueryPrimaryContext::getRuleIndex() const {
  return PrestoSqlParser::RuleQueryPrimary;
}

void PrestoSqlParser::QueryPrimaryContext::copyFrom(QueryPrimaryContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SubqueryContext
//------------------------------------------------------------------

PrestoSqlParser::QueryNoWithContext*
PrestoSqlParser::SubqueryContext::queryNoWith() {
  return getRuleContext<PrestoSqlParser::QueryNoWithContext>(0);
}

PrestoSqlParser::SubqueryContext::SubqueryContext(QueryPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SubqueryContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubquery(this);
}
void PrestoSqlParser::SubqueryContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubquery(this);
}

std::any PrestoSqlParser::SubqueryContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSubquery(this);
  else
    return visitor->visitChildren(this);
}
//----------------- QueryPrimaryDefaultContext
//------------------------------------------------------------------

PrestoSqlParser::QuerySpecificationContext*
PrestoSqlParser::QueryPrimaryDefaultContext::querySpecification() {
  return getRuleContext<PrestoSqlParser::QuerySpecificationContext>(0);
}

PrestoSqlParser::QueryPrimaryDefaultContext::QueryPrimaryDefaultContext(
    QueryPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::QueryPrimaryDefaultContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterQueryPrimaryDefault(this);
}
void PrestoSqlParser::QueryPrimaryDefaultContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitQueryPrimaryDefault(this);
}

std::any PrestoSqlParser::QueryPrimaryDefaultContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitQueryPrimaryDefault(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TableContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::TableContext::TABLE() {
  return getToken(PrestoSqlParser::TABLE, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::TableContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::TableContext::TableContext(QueryPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TableContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTable(this);
}
void PrestoSqlParser::TableContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTable(this);
}

std::any PrestoSqlParser::TableContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InlineTableContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::InlineTableContext::VALUES() {
  return getToken(PrestoSqlParser::VALUES, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::InlineTableContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::InlineTableContext::expression(size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

PrestoSqlParser::InlineTableContext::InlineTableContext(
    QueryPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::InlineTableContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterInlineTable(this);
}
void PrestoSqlParser::InlineTableContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitInlineTable(this);
}

std::any PrestoSqlParser::InlineTableContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitInlineTable(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::QueryPrimaryContext* PrestoSqlParser::queryPrimary() {
  QueryPrimaryContext* _localctx =
      _tracker.createInstance<QueryPrimaryContext>(_ctx, getState());
  enterRule(_localctx, 50, PrestoSqlParser::RuleQueryPrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(1115);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::FROM:
      case PrestoSqlParser::SELECT: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::QueryPrimaryDefaultContext>(
                    _localctx);
        enterOuterAlt(_localctx, 1);
        setState(1099);
        querySpecification();
        break;
      }

      case PrestoSqlParser::TABLE: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::TableContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(1100);
        match(PrestoSqlParser::TABLE);
        setState(1101);
        qualifiedName();
        break;
      }

      case PrestoSqlParser::VALUES: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::InlineTableContext>(
                _localctx);
        enterOuterAlt(_localctx, 3);
        setState(1102);
        match(PrestoSqlParser::VALUES);
        setState(1103);
        expression();
        setState(1108);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 130, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1104);
            match(PrestoSqlParser::T__3);
            setState(1105);
            expression();
          }
          setState(1110);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
              _input, 130, _ctx);
        }
        break;
      }

      case PrestoSqlParser::T__1: {
        _localctx = _tracker.createInstance<PrestoSqlParser::SubqueryContext>(
            _localctx);
        enterOuterAlt(_localctx, 4);
        setState(1111);
        match(PrestoSqlParser::T__1);
        setState(1112);
        queryNoWith();
        setState(1113);
        match(PrestoSqlParser::T__2);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SortItemContext
//------------------------------------------------------------------

PrestoSqlParser::SortItemContext::SortItemContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::SortItemContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SortItemContext::NULLS() {
  return getToken(PrestoSqlParser::NULLS, 0);
}

tree::TerminalNode* PrestoSqlParser::SortItemContext::ASC() {
  return getToken(PrestoSqlParser::ASC, 0);
}

tree::TerminalNode* PrestoSqlParser::SortItemContext::DESC() {
  return getToken(PrestoSqlParser::DESC, 0);
}

tree::TerminalNode* PrestoSqlParser::SortItemContext::FIRST() {
  return getToken(PrestoSqlParser::FIRST, 0);
}

tree::TerminalNode* PrestoSqlParser::SortItemContext::LAST() {
  return getToken(PrestoSqlParser::LAST, 0);
}

size_t PrestoSqlParser::SortItemContext::getRuleIndex() const {
  return PrestoSqlParser::RuleSortItem;
}

void PrestoSqlParser::SortItemContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSortItem(this);
}

void PrestoSqlParser::SortItemContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSortItem(this);
}

std::any PrestoSqlParser::SortItemContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSortItem(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::SortItemContext* PrestoSqlParser::sortItem() {
  SortItemContext* _localctx =
      _tracker.createInstance<SortItemContext>(_ctx, getState());
  enterRule(_localctx, 52, PrestoSqlParser::RuleSortItem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1117);
    expression();
    setState(1119);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::ASC

        || _la == PrestoSqlParser::DESC) {
      setState(1118);
      antlrcpp::downCast<SortItemContext*>(_localctx)->ordering = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == PrestoSqlParser::ASC

            || _la == PrestoSqlParser::DESC)) {
        antlrcpp::downCast<SortItemContext*>(_localctx)->ordering =
            _errHandler->recoverInline(this);
      } else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(1123);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::NULLS) {
      setState(1121);
      match(PrestoSqlParser::NULLS);
      setState(1122);
      antlrcpp::downCast<SortItemContext*>(_localctx)->nullOrdering =
          _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == PrestoSqlParser::FIRST

            || _la == PrestoSqlParser::LAST)) {
        antlrcpp::downCast<SortItemContext*>(_localctx)->nullOrdering =
            _errHandler->recoverInline(this);
      } else {
        _errHandler->reportMatch(this);
        consume();
      }
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QuerySpecificationContext
//------------------------------------------------------------------

PrestoSqlParser::QuerySpecificationContext::QuerySpecificationContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::QuerySpecificationContext::SELECT() {
  return getToken(PrestoSqlParser::SELECT, 0);
}

std::vector<PrestoSqlParser::SelectItemContext*>
PrestoSqlParser::QuerySpecificationContext::selectItem() {
  return getRuleContexts<PrestoSqlParser::SelectItemContext>();
}

PrestoSqlParser::SelectItemContext*
PrestoSqlParser::QuerySpecificationContext::selectItem(size_t i) {
  return getRuleContext<PrestoSqlParser::SelectItemContext>(i);
}

PrestoSqlParser::SetQuantifierContext*
PrestoSqlParser::QuerySpecificationContext::setQuantifier() {
  return getRuleContext<PrestoSqlParser::SetQuantifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::QuerySpecificationContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

std::vector<PrestoSqlParser::RelationContext*>
PrestoSqlParser::QuerySpecificationContext::relation() {
  return getRuleContexts<PrestoSqlParser::RelationContext>();
}

PrestoSqlParser::RelationContext*
PrestoSqlParser::QuerySpecificationContext::relation(size_t i) {
  return getRuleContext<PrestoSqlParser::RelationContext>(i);
}

tree::TerminalNode* PrestoSqlParser::QuerySpecificationContext::WHERE() {
  return getToken(PrestoSqlParser::WHERE, 0);
}

tree::TerminalNode* PrestoSqlParser::QuerySpecificationContext::GROUP() {
  return getToken(PrestoSqlParser::GROUP, 0);
}

tree::TerminalNode* PrestoSqlParser::QuerySpecificationContext::BY() {
  return getToken(PrestoSqlParser::BY, 0);
}

PrestoSqlParser::GroupByContext*
PrestoSqlParser::QuerySpecificationContext::groupBy() {
  return getRuleContext<PrestoSqlParser::GroupByContext>(0);
}

tree::TerminalNode* PrestoSqlParser::QuerySpecificationContext::HAVING() {
  return getToken(PrestoSqlParser::HAVING, 0);
}

std::vector<PrestoSqlParser::BooleanExpressionContext*>
PrestoSqlParser::QuerySpecificationContext::booleanExpression() {
  return getRuleContexts<PrestoSqlParser::BooleanExpressionContext>();
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::QuerySpecificationContext::booleanExpression(size_t i) {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(i);
}

size_t PrestoSqlParser::QuerySpecificationContext::getRuleIndex() const {
  return PrestoSqlParser::RuleQuerySpecification;
}

void PrestoSqlParser::QuerySpecificationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterQuerySpecification(this);
}

void PrestoSqlParser::QuerySpecificationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitQuerySpecification(this);
}

std::any PrestoSqlParser::QuerySpecificationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitQuerySpecification(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::QuerySpecificationContext*
PrestoSqlParser::querySpecification() {
  QuerySpecificationContext* _localctx =
      _tracker.createInstance<QuerySpecificationContext>(_ctx, getState());
  enterRule(_localctx, 54, PrestoSqlParser::RuleQuerySpecification);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    setState(1186);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::SELECT: {
        enterOuterAlt(_localctx, 1);
        setState(1125);
        match(PrestoSqlParser::SELECT);
        setState(1127);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 134, _ctx)) {
          case 1: {
            setState(1126);
            setQuantifier();
            break;
          }

          default:
            break;
        }
        setState(1129);
        selectItem();
        setState(1134);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 135, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1130);
            match(PrestoSqlParser::T__3);
            setState(1131);
            selectItem();
          }
          setState(1136);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
              _input, 135, _ctx);
        }
        setState(1138);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 136, _ctx)) {
          case 1: {
            setState(1137);
            match(PrestoSqlParser::T__3);
            break;
          }

          default:
            break;
        }
        setState(1149);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 138, _ctx)) {
          case 1: {
            setState(1140);
            match(PrestoSqlParser::FROM);
            setState(1141);
            relation(0);
            setState(1146);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
                _input, 137, _ctx);
            while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
              if (alt == 1) {
                setState(1142);
                match(PrestoSqlParser::T__3);
                setState(1143);
                relation(0);
              }
              setState(1148);
              _errHandler->sync(this);
              alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
                  _input, 137, _ctx);
            }
            break;
          }

          default:
            break;
        }
        setState(1153);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 139, _ctx)) {
          case 1: {
            setState(1151);
            match(PrestoSqlParser::WHERE);
            setState(1152);
            antlrcpp::downCast<QuerySpecificationContext*>(_localctx)->where =
                booleanExpression(0);
            break;
          }

          default:
            break;
        }
        setState(1158);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 140, _ctx)) {
          case 1: {
            setState(1155);
            match(PrestoSqlParser::GROUP);
            setState(1156);
            match(PrestoSqlParser::BY);
            setState(1157);
            groupBy();
            break;
          }

          default:
            break;
        }
        setState(1162);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 141, _ctx)) {
          case 1: {
            setState(1160);
            match(PrestoSqlParser::HAVING);
            setState(1161);
            antlrcpp::downCast<QuerySpecificationContext*>(_localctx)->having =
                booleanExpression(0);
            break;
          }

          default:
            break;
        }
        break;
      }

      case PrestoSqlParser::FROM: {
        enterOuterAlt(_localctx, 2);
        setState(1164);
        match(PrestoSqlParser::FROM);
        setState(1165);
        relation(0);
        setState(1170);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 142, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(1166);
            match(PrestoSqlParser::T__3);
            setState(1167);
            relation(0);
          }
          setState(1172);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
              _input, 142, _ctx);
        }
        setState(1175);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 143, _ctx)) {
          case 1: {
            setState(1173);
            match(PrestoSqlParser::WHERE);
            setState(1174);
            antlrcpp::downCast<QuerySpecificationContext*>(_localctx)->where =
                booleanExpression(0);
            break;
          }

          default:
            break;
        }
        setState(1180);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 144, _ctx)) {
          case 1: {
            setState(1177);
            match(PrestoSqlParser::GROUP);
            setState(1178);
            match(PrestoSqlParser::BY);
            setState(1179);
            groupBy();
            break;
          }

          default:
            break;
        }
        setState(1184);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 145, _ctx)) {
          case 1: {
            setState(1182);
            match(PrestoSqlParser::HAVING);
            setState(1183);
            antlrcpp::downCast<QuerySpecificationContext*>(_localctx)->having =
                booleanExpression(0);
            break;
          }

          default:
            break;
        }
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupByContext
//------------------------------------------------------------------

PrestoSqlParser::GroupByContext::GroupByContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::GroupingElementContext*>
PrestoSqlParser::GroupByContext::groupingElement() {
  return getRuleContexts<PrestoSqlParser::GroupingElementContext>();
}

PrestoSqlParser::GroupingElementContext*
PrestoSqlParser::GroupByContext::groupingElement(size_t i) {
  return getRuleContext<PrestoSqlParser::GroupingElementContext>(i);
}

PrestoSqlParser::SetQuantifierContext*
PrestoSqlParser::GroupByContext::setQuantifier() {
  return getRuleContext<PrestoSqlParser::SetQuantifierContext>(0);
}

size_t PrestoSqlParser::GroupByContext::getRuleIndex() const {
  return PrestoSqlParser::RuleGroupBy;
}

void PrestoSqlParser::GroupByContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterGroupBy(this);
}

void PrestoSqlParser::GroupByContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitGroupBy(this);
}

std::any PrestoSqlParser::GroupByContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitGroupBy(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::GroupByContext* PrestoSqlParser::groupBy() {
  GroupByContext* _localctx =
      _tracker.createInstance<GroupByContext>(_ctx, getState());
  enterRule(_localctx, 56, PrestoSqlParser::RuleGroupBy);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1189);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 147, _ctx)) {
      case 1: {
        setState(1188);
        setQuantifier();
        break;
      }

      default:
        break;
    }
    setState(1191);
    groupingElement();
    setState(1196);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 148, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1192);
        match(PrestoSqlParser::T__3);
        setState(1193);
        groupingElement();
      }
      setState(1198);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 148, _ctx);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupingElementContext
//------------------------------------------------------------------

PrestoSqlParser::GroupingElementContext::GroupingElementContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::GroupingElementContext::getRuleIndex() const {
  return PrestoSqlParser::RuleGroupingElement;
}

void PrestoSqlParser::GroupingElementContext::copyFrom(
    GroupingElementContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MultipleGroupingSetsContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::MultipleGroupingSetsContext::GROUPING() {
  return getToken(PrestoSqlParser::GROUPING, 0);
}

tree::TerminalNode* PrestoSqlParser::MultipleGroupingSetsContext::SETS() {
  return getToken(PrestoSqlParser::SETS, 0);
}

std::vector<PrestoSqlParser::GroupingSetContext*>
PrestoSqlParser::MultipleGroupingSetsContext::groupingSet() {
  return getRuleContexts<PrestoSqlParser::GroupingSetContext>();
}

PrestoSqlParser::GroupingSetContext*
PrestoSqlParser::MultipleGroupingSetsContext::groupingSet(size_t i) {
  return getRuleContext<PrestoSqlParser::GroupingSetContext>(i);
}

PrestoSqlParser::MultipleGroupingSetsContext::MultipleGroupingSetsContext(
    GroupingElementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::MultipleGroupingSetsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultipleGroupingSets(this);
}
void PrestoSqlParser::MultipleGroupingSetsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultipleGroupingSets(this);
}

std::any PrestoSqlParser::MultipleGroupingSetsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitMultipleGroupingSets(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleGroupingSetContext
//------------------------------------------------------------------

PrestoSqlParser::GroupingSetContext*
PrestoSqlParser::SingleGroupingSetContext::groupingSet() {
  return getRuleContext<PrestoSqlParser::GroupingSetContext>(0);
}

PrestoSqlParser::SingleGroupingSetContext::SingleGroupingSetContext(
    GroupingElementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SingleGroupingSetContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingleGroupingSet(this);
}
void PrestoSqlParser::SingleGroupingSetContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingleGroupingSet(this);
}

std::any PrestoSqlParser::SingleGroupingSetContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSingleGroupingSet(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CubeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CubeContext::CUBE() {
  return getToken(PrestoSqlParser::CUBE, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::CubeContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext* PrestoSqlParser::CubeContext::expression(
    size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

PrestoSqlParser::CubeContext::CubeContext(GroupingElementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CubeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCube(this);
}
void PrestoSqlParser::CubeContext::exitRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCube(this);
}

std::any PrestoSqlParser::CubeContext::accept(tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCube(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RollupContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RollupContext::ROLLUP() {
  return getToken(PrestoSqlParser::ROLLUP, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::RollupContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext* PrestoSqlParser::RollupContext::expression(
    size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

PrestoSqlParser::RollupContext::RollupContext(GroupingElementContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RollupContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRollup(this);
}
void PrestoSqlParser::RollupContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRollup(this);
}

std::any PrestoSqlParser::RollupContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRollup(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::GroupingElementContext* PrestoSqlParser::groupingElement() {
  GroupingElementContext* _localctx =
      _tracker.createInstance<GroupingElementContext>(_ctx, getState());
  enterRule(_localctx, 58, PrestoSqlParser::RuleGroupingElement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1239);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 154, _ctx)) {
      case 1: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SingleGroupingSetContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(1199);
        groupingSet();
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::RollupContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(1200);
        match(PrestoSqlParser::ROLLUP);
        setState(1201);
        match(PrestoSqlParser::T__1);
        setState(1210);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6508829423092451292) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2308677939035742217) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260097) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & -4291454694588945) != 0) ||
            _la == PrestoSqlParser::DOUBLE_PRECISION) {
          setState(1202);
          expression();
          setState(1207);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(1203);
            match(PrestoSqlParser::T__3);
            setState(1204);
            expression();
            setState(1209);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(1212);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 3: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CubeContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(1213);
        match(PrestoSqlParser::CUBE);
        setState(1214);
        match(PrestoSqlParser::T__1);
        setState(1223);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6508829423092451292) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2308677939035742217) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260097) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & -4291454694588945) != 0) ||
            _la == PrestoSqlParser::DOUBLE_PRECISION) {
          setState(1215);
          expression();
          setState(1220);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(1216);
            match(PrestoSqlParser::T__3);
            setState(1217);
            expression();
            setState(1222);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(1225);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 4: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::MultipleGroupingSetsContext>(
                    _localctx);
        enterOuterAlt(_localctx, 4);
        setState(1226);
        match(PrestoSqlParser::GROUPING);
        setState(1227);
        match(PrestoSqlParser::SETS);
        setState(1228);
        match(PrestoSqlParser::T__1);
        setState(1229);
        groupingSet();
        setState(1234);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(1230);
          match(PrestoSqlParser::T__3);
          setState(1231);
          groupingSet();
          setState(1236);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1237);
        match(PrestoSqlParser::T__2);
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GroupingSetContext
//------------------------------------------------------------------

PrestoSqlParser::GroupingSetContext::GroupingSetContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::GroupingSetContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::GroupingSetContext::expression(size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

size_t PrestoSqlParser::GroupingSetContext::getRuleIndex() const {
  return PrestoSqlParser::RuleGroupingSet;
}

void PrestoSqlParser::GroupingSetContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterGroupingSet(this);
}

void PrestoSqlParser::GroupingSetContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitGroupingSet(this);
}

std::any PrestoSqlParser::GroupingSetContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitGroupingSet(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::GroupingSetContext* PrestoSqlParser::groupingSet() {
  GroupingSetContext* _localctx =
      _tracker.createInstance<GroupingSetContext>(_ctx, getState());
  enterRule(_localctx, 60, PrestoSqlParser::RuleGroupingSet);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1254);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 157, _ctx)) {
      case 1: {
        enterOuterAlt(_localctx, 1);
        setState(1241);
        match(PrestoSqlParser::T__1);
        setState(1250);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6508829423092451292) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2308677939035742217) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260097) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & -4291454694588945) != 0) ||
            _la == PrestoSqlParser::DOUBLE_PRECISION) {
          setState(1242);
          expression();
          setState(1247);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(1243);
            match(PrestoSqlParser::T__3);
            setState(1244);
            expression();
            setState(1249);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(1252);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 2: {
        enterOuterAlt(_localctx, 2);
        setState(1253);
        expression();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamedQueryContext
//------------------------------------------------------------------

PrestoSqlParser::NamedQueryContext::NamedQueryContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::NamedQueryContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

PrestoSqlParser::QueryContext* PrestoSqlParser::NamedQueryContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::NamedQueryContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::ColumnAliasesContext*
PrestoSqlParser::NamedQueryContext::columnAliases() {
  return getRuleContext<PrestoSqlParser::ColumnAliasesContext>(0);
}

size_t PrestoSqlParser::NamedQueryContext::getRuleIndex() const {
  return PrestoSqlParser::RuleNamedQuery;
}

void PrestoSqlParser::NamedQueryContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamedQuery(this);
}

void PrestoSqlParser::NamedQueryContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamedQuery(this);
}

std::any PrestoSqlParser::NamedQueryContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNamedQuery(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::NamedQueryContext* PrestoSqlParser::namedQuery() {
  NamedQueryContext* _localctx =
      _tracker.createInstance<NamedQueryContext>(_ctx, getState());
  enterRule(_localctx, 62, PrestoSqlParser::RuleNamedQuery);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1256);
    antlrcpp::downCast<NamedQueryContext*>(_localctx)->name = identifier();
    setState(1258);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::T__1) {
      setState(1257);
      columnAliases();
    }
    setState(1260);
    match(PrestoSqlParser::AS);
    setState(1261);
    match(PrestoSqlParser::T__1);
    setState(1262);
    query();
    setState(1263);
    match(PrestoSqlParser::T__2);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetQuantifierContext
//------------------------------------------------------------------

PrestoSqlParser::SetQuantifierContext::SetQuantifierContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::SetQuantifierContext::DISTINCT() {
  return getToken(PrestoSqlParser::DISTINCT, 0);
}

tree::TerminalNode* PrestoSqlParser::SetQuantifierContext::ALL() {
  return getToken(PrestoSqlParser::ALL, 0);
}

size_t PrestoSqlParser::SetQuantifierContext::getRuleIndex() const {
  return PrestoSqlParser::RuleSetQuantifier;
}

void PrestoSqlParser::SetQuantifierContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSetQuantifier(this);
}

void PrestoSqlParser::SetQuantifierContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSetQuantifier(this);
}

std::any PrestoSqlParser::SetQuantifierContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSetQuantifier(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::SetQuantifierContext* PrestoSqlParser::setQuantifier() {
  SetQuantifierContext* _localctx =
      _tracker.createInstance<SetQuantifierContext>(_ctx, getState());
  enterRule(_localctx, 64, PrestoSqlParser::RuleSetQuantifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1265);
    _la = _input->LA(1);
    if (!(_la == PrestoSqlParser::ALL

          || _la == PrestoSqlParser::DISTINCT)) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SelectItemContext
//------------------------------------------------------------------

PrestoSqlParser::SelectItemContext::SelectItemContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::SelectItemContext::getRuleIndex() const {
  return PrestoSqlParser::RuleSelectItem;
}

void PrestoSqlParser::SelectItemContext::copyFrom(SelectItemContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SelectAllContext
//------------------------------------------------------------------

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::SelectAllContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SelectAllContext::ASTERISK() {
  return getToken(PrestoSqlParser::ASTERISK, 0);
}

PrestoSqlParser::StarModifiersContext*
PrestoSqlParser::SelectAllContext::starModifiers() {
  return getRuleContext<PrestoSqlParser::StarModifiersContext>(0);
}

PrestoSqlParser::SelectAllContext::SelectAllContext(SelectItemContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SelectAllContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectAll(this);
}
void PrestoSqlParser::SelectAllContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectAll(this);
}

std::any PrestoSqlParser::SelectAllContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSelectAll(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SelectSingleContext
//------------------------------------------------------------------

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::SelectSingleContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::SelectSingleContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SelectSingleContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

PrestoSqlParser::SelectSingleContext::SelectSingleContext(
    SelectItemContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SelectSingleContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectSingle(this);
}
void PrestoSqlParser::SelectSingleContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectSingle(this);
}

std::any PrestoSqlParser::SelectSingleContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSelectSingle(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SelectColumnsContext
//------------------------------------------------------------------

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::SelectColumnsContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SelectColumnsContext::COLUMNS() {
  return getToken(PrestoSqlParser::COLUMNS, 0);
}

tree::TerminalNode* PrestoSqlParser::SelectColumnsContext::STRING() {
  return getToken(PrestoSqlParser::STRING, 0);
}

PrestoSqlParser::StarModifiersContext*
PrestoSqlParser::SelectColumnsContext::starModifiers() {
  return getRuleContext<PrestoSqlParser::StarModifiersContext>(0);
}

PrestoSqlParser::SelectColumnsContext::SelectColumnsContext(
    SelectItemContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SelectColumnsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelectColumns(this);
}
void PrestoSqlParser::SelectColumnsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelectColumns(this);
}

std::any PrestoSqlParser::SelectColumnsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSelectColumns(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::SelectItemContext* PrestoSqlParser::selectItem() {
  SelectItemContext* _localctx =
      _tracker.createInstance<SelectItemContext>(_ctx, getState());
  enterRule(_localctx, 66, PrestoSqlParser::RuleSelectItem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1300);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 165, _ctx)) {
      case 1: {
        _localctx = _tracker.createInstance<PrestoSqlParser::SelectAllContext>(
            _localctx);
        enterOuterAlt(_localctx, 1);
        setState(1267);
        qualifiedName();
        setState(1268);
        match(PrestoSqlParser::T__0);
        setState(1269);
        match(PrestoSqlParser::ASTERISK);
        setState(1271);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 159, _ctx)) {
          case 1: {
            setState(1270);
            starModifiers();
            break;
          }

          default:
            break;
        }
        break;
      }

      case 2: {
        _localctx = _tracker.createInstance<PrestoSqlParser::SelectAllContext>(
            _localctx);
        enterOuterAlt(_localctx, 2);
        setState(1273);
        match(PrestoSqlParser::ASTERISK);
        setState(1275);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 160, _ctx)) {
          case 1: {
            setState(1274);
            starModifiers();
            break;
          }

          default:
            break;
        }
        break;
      }

      case 3: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SelectColumnsContext>(
                _localctx);
        enterOuterAlt(_localctx, 3);
        setState(1277);
        qualifiedName();
        setState(1278);
        match(PrestoSqlParser::T__0);
        setState(1279);
        match(PrestoSqlParser::COLUMNS);
        setState(1280);
        match(PrestoSqlParser::T__1);
        setState(1281);
        antlrcpp::downCast<SelectColumnsContext*>(_localctx)->pattern =
            match(PrestoSqlParser::STRING);
        setState(1282);
        match(PrestoSqlParser::T__2);
        setState(1284);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 161, _ctx)) {
          case 1: {
            setState(1283);
            starModifiers();
            break;
          }

          default:
            break;
        }
        break;
      }

      case 4: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SelectColumnsContext>(
                _localctx);
        enterOuterAlt(_localctx, 4);
        setState(1286);
        match(PrestoSqlParser::COLUMNS);
        setState(1287);
        match(PrestoSqlParser::T__1);
        setState(1288);
        antlrcpp::downCast<SelectColumnsContext*>(_localctx)->pattern =
            match(PrestoSqlParser::STRING);
        setState(1289);
        match(PrestoSqlParser::T__2);
        setState(1291);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 162, _ctx)) {
          case 1: {
            setState(1290);
            starModifiers();
            break;
          }

          default:
            break;
        }
        break;
      }

      case 5: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SelectSingleContext>(
                _localctx);
        enterOuterAlt(_localctx, 5);
        setState(1293);
        expression();
        setState(1298);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 164, _ctx)) {
          case 1: {
            setState(1295);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == PrestoSqlParser::AS) {
              setState(1294);
              match(PrestoSqlParser::AS);
            }
            setState(1297);
            identifier();
            break;
          }

          default:
            break;
        }
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StarModifiersContext
//------------------------------------------------------------------

PrestoSqlParser::StarModifiersContext::StarModifiersContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::ExcludeClauseContext*>
PrestoSqlParser::StarModifiersContext::excludeClause() {
  return getRuleContexts<PrestoSqlParser::ExcludeClauseContext>();
}

PrestoSqlParser::ExcludeClauseContext*
PrestoSqlParser::StarModifiersContext::excludeClause(size_t i) {
  return getRuleContext<PrestoSqlParser::ExcludeClauseContext>(i);
}

std::vector<PrestoSqlParser::ReplaceClauseContext*>
PrestoSqlParser::StarModifiersContext::replaceClause() {
  return getRuleContexts<PrestoSqlParser::ReplaceClauseContext>();
}

PrestoSqlParser::ReplaceClauseContext*
PrestoSqlParser::StarModifiersContext::replaceClause(size_t i) {
  return getRuleContext<PrestoSqlParser::ReplaceClauseContext>(i);
}

size_t PrestoSqlParser::StarModifiersContext::getRuleIndex() const {
  return PrestoSqlParser::RuleStarModifiers;
}

void PrestoSqlParser::StarModifiersContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterStarModifiers(this);
}

void PrestoSqlParser::StarModifiersContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitStarModifiers(this);
}

std::any PrestoSqlParser::StarModifiersContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitStarModifiers(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::StarModifiersContext* PrestoSqlParser::starModifiers() {
  StarModifiersContext* _localctx =
      _tracker.createInstance<StarModifiersContext>(_ctx, getState());
  enterRule(_localctx, 68, PrestoSqlParser::RuleStarModifiers);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1304);
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
          setState(1304);
          _errHandler->sync(this);
          switch (_input->LA(1)) {
            case PrestoSqlParser::EXCLUDE: {
              setState(1302);
              excludeClause();
              break;
            }

            case PrestoSqlParser::REPLACE: {
              setState(1303);
              replaceClause();
              break;
            }

            default:
              throw NoViableAltException(this);
          }
          break;
        }

        default:
          throw NoViableAltException(this);
      }
      setState(1306);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 167, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExcludeClauseContext
//------------------------------------------------------------------

PrestoSqlParser::ExcludeClauseContext::ExcludeClauseContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ExcludeClauseContext::EXCLUDE() {
  return getToken(PrestoSqlParser::EXCLUDE, 0);
}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::ExcludeClauseContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ExcludeClauseContext::identifier(size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

size_t PrestoSqlParser::ExcludeClauseContext::getRuleIndex() const {
  return PrestoSqlParser::RuleExcludeClause;
}

void PrestoSqlParser::ExcludeClauseContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExcludeClause(this);
}

void PrestoSqlParser::ExcludeClauseContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExcludeClause(this);
}

std::any PrestoSqlParser::ExcludeClauseContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExcludeClause(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ExcludeClauseContext* PrestoSqlParser::excludeClause() {
  ExcludeClauseContext* _localctx =
      _tracker.createInstance<ExcludeClauseContext>(_ctx, getState());
  enterRule(_localctx, 70, PrestoSqlParser::RuleExcludeClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1308);
    match(PrestoSqlParser::EXCLUDE);
    setState(1309);
    match(PrestoSqlParser::T__1);
    setState(1310);
    identifier();
    setState(1315);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrestoSqlParser::T__3) {
      setState(1311);
      match(PrestoSqlParser::T__3);
      setState(1312);
      identifier();
      setState(1317);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1318);
    match(PrestoSqlParser::T__2);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReplaceClauseContext
//------------------------------------------------------------------

PrestoSqlParser::ReplaceClauseContext::ReplaceClauseContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ReplaceClauseContext::REPLACE() {
  return getToken(PrestoSqlParser::REPLACE, 0);
}

std::vector<PrestoSqlParser::ReplaceItemContext*>
PrestoSqlParser::ReplaceClauseContext::replaceItem() {
  return getRuleContexts<PrestoSqlParser::ReplaceItemContext>();
}

PrestoSqlParser::ReplaceItemContext*
PrestoSqlParser::ReplaceClauseContext::replaceItem(size_t i) {
  return getRuleContext<PrestoSqlParser::ReplaceItemContext>(i);
}

size_t PrestoSqlParser::ReplaceClauseContext::getRuleIndex() const {
  return PrestoSqlParser::RuleReplaceClause;
}

void PrestoSqlParser::ReplaceClauseContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterReplaceClause(this);
}

void PrestoSqlParser::ReplaceClauseContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitReplaceClause(this);
}

std::any PrestoSqlParser::ReplaceClauseContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitReplaceClause(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ReplaceClauseContext* PrestoSqlParser::replaceClause() {
  ReplaceClauseContext* _localctx =
      _tracker.createInstance<ReplaceClauseContext>(_ctx, getState());
  enterRule(_localctx, 72, PrestoSqlParser::RuleReplaceClause);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1320);
    match(PrestoSqlParser::REPLACE);
    setState(1321);
    match(PrestoSqlParser::T__1);
    setState(1322);
    replaceItem();
    setState(1327);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrestoSqlParser::T__3) {
      setState(1323);
      match(PrestoSqlParser::T__3);
      setState(1324);
      replaceItem();
      setState(1329);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1330);
    match(PrestoSqlParser::T__2);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReplaceItemContext
//------------------------------------------------------------------

PrestoSqlParser::ReplaceItemContext::ReplaceItemContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::ReplaceItemContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ReplaceItemContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ReplaceItemContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

size_t PrestoSqlParser::ReplaceItemContext::getRuleIndex() const {
  return PrestoSqlParser::RuleReplaceItem;
}

void PrestoSqlParser::ReplaceItemContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterReplaceItem(this);
}

void PrestoSqlParser::ReplaceItemContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitReplaceItem(this);
}

std::any PrestoSqlParser::ReplaceItemContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitReplaceItem(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ReplaceItemContext* PrestoSqlParser::replaceItem() {
  ReplaceItemContext* _localctx =
      _tracker.createInstance<ReplaceItemContext>(_ctx, getState());
  enterRule(_localctx, 74, PrestoSqlParser::RuleReplaceItem);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1332);
    expression();
    setState(1333);
    match(PrestoSqlParser::AS);
    setState(1334);
    identifier();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationContext
//------------------------------------------------------------------

PrestoSqlParser::RelationContext::RelationContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::RelationContext::getRuleIndex() const {
  return PrestoSqlParser::RuleRelation;
}

void PrestoSqlParser::RelationContext::copyFrom(RelationContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- RelationDefaultContext
//------------------------------------------------------------------

PrestoSqlParser::SampledRelationContext*
PrestoSqlParser::RelationDefaultContext::sampledRelation() {
  return getRuleContext<PrestoSqlParser::SampledRelationContext>(0);
}

PrestoSqlParser::RelationDefaultContext::RelationDefaultContext(
    RelationContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RelationDefaultContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelationDefault(this);
}
void PrestoSqlParser::RelationDefaultContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelationDefault(this);
}

std::any PrestoSqlParser::RelationDefaultContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRelationDefault(this);
  else
    return visitor->visitChildren(this);
}
//----------------- JoinRelationContext
//------------------------------------------------------------------

std::vector<PrestoSqlParser::RelationContext*>
PrestoSqlParser::JoinRelationContext::relation() {
  return getRuleContexts<PrestoSqlParser::RelationContext>();
}

PrestoSqlParser::RelationContext*
PrestoSqlParser::JoinRelationContext::relation(size_t i) {
  return getRuleContext<PrestoSqlParser::RelationContext>(i);
}

tree::TerminalNode* PrestoSqlParser::JoinRelationContext::CROSS() {
  return getToken(PrestoSqlParser::CROSS, 0);
}

tree::TerminalNode* PrestoSqlParser::JoinRelationContext::JOIN() {
  return getToken(PrestoSqlParser::JOIN, 0);
}

PrestoSqlParser::JoinTypeContext*
PrestoSqlParser::JoinRelationContext::joinType() {
  return getRuleContext<PrestoSqlParser::JoinTypeContext>(0);
}

PrestoSqlParser::JoinCriteriaContext*
PrestoSqlParser::JoinRelationContext::joinCriteria() {
  return getRuleContext<PrestoSqlParser::JoinCriteriaContext>(0);
}

tree::TerminalNode* PrestoSqlParser::JoinRelationContext::NATURAL() {
  return getToken(PrestoSqlParser::NATURAL, 0);
}

PrestoSqlParser::SampledRelationContext*
PrestoSqlParser::JoinRelationContext::sampledRelation() {
  return getRuleContext<PrestoSqlParser::SampledRelationContext>(0);
}

PrestoSqlParser::JoinRelationContext::JoinRelationContext(
    RelationContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::JoinRelationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterJoinRelation(this);
}
void PrestoSqlParser::JoinRelationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitJoinRelation(this);
}

std::any PrestoSqlParser::JoinRelationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitJoinRelation(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::RelationContext* PrestoSqlParser::relation() {
  return relation(0);
}

PrestoSqlParser::RelationContext* PrestoSqlParser::relation(int precedence) {
  ParserRuleContext* parentContext = _ctx;
  size_t parentState = getState();
  PrestoSqlParser::RelationContext* _localctx =
      _tracker.createInstance<RelationContext>(_ctx, parentState);
  PrestoSqlParser::RelationContext* previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by
                         // generated code.
  size_t startState = 76;
  enterRecursionRule(_localctx, 76, PrestoSqlParser::RuleRelation, precedence);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _localctx = _tracker.createInstance<RelationDefaultContext>(_localctx);
    _ctx = _localctx;
    previousContext = _localctx;

    setState(1337);
    sampledRelation();
    _ctx->stop = _input->LT(-1);
    setState(1357);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 171, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<JoinRelationContext>(
            _tracker.createInstance<RelationContext>(
                parentContext, parentState));
        _localctx = newContext;
        newContext->left = previousContext;
        pushNewRecursionContext(newContext, startState, RuleRelation);
        setState(1339);

        if (!(precpred(_ctx, 2)))
          throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(1353);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
          case PrestoSqlParser::CROSS: {
            setState(1340);
            match(PrestoSqlParser::CROSS);
            setState(1341);
            match(PrestoSqlParser::JOIN);
            setState(1342);
            antlrcpp::downCast<JoinRelationContext*>(_localctx)->right =
                sampledRelation();
            break;
          }

          case PrestoSqlParser::FULL:
          case PrestoSqlParser::INNER:
          case PrestoSqlParser::JOIN:
          case PrestoSqlParser::LEFT:
          case PrestoSqlParser::RIGHT: {
            setState(1343);
            joinType();
            setState(1344);
            match(PrestoSqlParser::JOIN);
            setState(1345);
            antlrcpp::downCast<JoinRelationContext*>(_localctx)->rightRelation =
                relation(0);
            setState(1346);
            joinCriteria();
            break;
          }

          case PrestoSqlParser::NATURAL: {
            setState(1348);
            match(PrestoSqlParser::NATURAL);
            setState(1349);
            joinType();
            setState(1350);
            match(PrestoSqlParser::JOIN);
            setState(1351);
            antlrcpp::downCast<JoinRelationContext*>(_localctx)->right =
                sampledRelation();
            break;
          }

          default:
            throw NoViableAltException(this);
        }
      }
      setState(1359);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 171, _ctx);
    }
  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- JoinTypeContext
//------------------------------------------------------------------

PrestoSqlParser::JoinTypeContext::JoinTypeContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::JoinTypeContext::INNER() {
  return getToken(PrestoSqlParser::INNER, 0);
}

tree::TerminalNode* PrestoSqlParser::JoinTypeContext::LEFT() {
  return getToken(PrestoSqlParser::LEFT, 0);
}

tree::TerminalNode* PrestoSqlParser::JoinTypeContext::OUTER() {
  return getToken(PrestoSqlParser::OUTER, 0);
}

tree::TerminalNode* PrestoSqlParser::JoinTypeContext::RIGHT() {
  return getToken(PrestoSqlParser::RIGHT, 0);
}

tree::TerminalNode* PrestoSqlParser::JoinTypeContext::FULL() {
  return getToken(PrestoSqlParser::FULL, 0);
}

size_t PrestoSqlParser::JoinTypeContext::getRuleIndex() const {
  return PrestoSqlParser::RuleJoinType;
}

void PrestoSqlParser::JoinTypeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterJoinType(this);
}

void PrestoSqlParser::JoinTypeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitJoinType(this);
}

std::any PrestoSqlParser::JoinTypeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitJoinType(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::JoinTypeContext* PrestoSqlParser::joinType() {
  JoinTypeContext* _localctx =
      _tracker.createInstance<JoinTypeContext>(_ctx, getState());
  enterRule(_localctx, 78, PrestoSqlParser::RuleJoinType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1375);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::INNER:
      case PrestoSqlParser::JOIN: {
        enterOuterAlt(_localctx, 1);
        setState(1361);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::INNER) {
          setState(1360);
          match(PrestoSqlParser::INNER);
        }
        break;
      }

      case PrestoSqlParser::LEFT: {
        enterOuterAlt(_localctx, 2);
        setState(1363);
        match(PrestoSqlParser::LEFT);
        setState(1365);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::OUTER) {
          setState(1364);
          match(PrestoSqlParser::OUTER);
        }
        break;
      }

      case PrestoSqlParser::RIGHT: {
        enterOuterAlt(_localctx, 3);
        setState(1367);
        match(PrestoSqlParser::RIGHT);
        setState(1369);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::OUTER) {
          setState(1368);
          match(PrestoSqlParser::OUTER);
        }
        break;
      }

      case PrestoSqlParser::FULL: {
        enterOuterAlt(_localctx, 4);
        setState(1371);
        match(PrestoSqlParser::FULL);
        setState(1373);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::OUTER) {
          setState(1372);
          match(PrestoSqlParser::OUTER);
        }
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- JoinCriteriaContext
//------------------------------------------------------------------

PrestoSqlParser::JoinCriteriaContext::JoinCriteriaContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::JoinCriteriaContext::ON() {
  return getToken(PrestoSqlParser::ON, 0);
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::JoinCriteriaContext::booleanExpression() {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::JoinCriteriaContext::USING() {
  return getToken(PrestoSqlParser::USING, 0);
}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::JoinCriteriaContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::JoinCriteriaContext::identifier(size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

size_t PrestoSqlParser::JoinCriteriaContext::getRuleIndex() const {
  return PrestoSqlParser::RuleJoinCriteria;
}

void PrestoSqlParser::JoinCriteriaContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterJoinCriteria(this);
}

void PrestoSqlParser::JoinCriteriaContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitJoinCriteria(this);
}

std::any PrestoSqlParser::JoinCriteriaContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitJoinCriteria(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::JoinCriteriaContext* PrestoSqlParser::joinCriteria() {
  JoinCriteriaContext* _localctx =
      _tracker.createInstance<JoinCriteriaContext>(_ctx, getState());
  enterRule(_localctx, 80, PrestoSqlParser::RuleJoinCriteria);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1391);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::ON: {
        enterOuterAlt(_localctx, 1);
        setState(1377);
        match(PrestoSqlParser::ON);
        setState(1378);
        booleanExpression(0);
        break;
      }

      case PrestoSqlParser::USING: {
        enterOuterAlt(_localctx, 2);
        setState(1379);
        match(PrestoSqlParser::USING);
        setState(1380);
        match(PrestoSqlParser::T__1);
        setState(1381);
        identifier();
        setState(1386);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(1382);
          match(PrestoSqlParser::T__3);
          setState(1383);
          identifier();
          setState(1388);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1389);
        match(PrestoSqlParser::T__2);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SampledRelationContext
//------------------------------------------------------------------

PrestoSqlParser::SampledRelationContext::SampledRelationContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::AliasedRelationContext*
PrestoSqlParser::SampledRelationContext::aliasedRelation() {
  return getRuleContext<PrestoSqlParser::AliasedRelationContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SampledRelationContext::TABLESAMPLE() {
  return getToken(PrestoSqlParser::TABLESAMPLE, 0);
}

PrestoSqlParser::SampleTypeContext*
PrestoSqlParser::SampledRelationContext::sampleType() {
  return getRuleContext<PrestoSqlParser::SampleTypeContext>(0);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::SampledRelationContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

size_t PrestoSqlParser::SampledRelationContext::getRuleIndex() const {
  return PrestoSqlParser::RuleSampledRelation;
}

void PrestoSqlParser::SampledRelationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSampledRelation(this);
}

void PrestoSqlParser::SampledRelationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSampledRelation(this);
}

std::any PrestoSqlParser::SampledRelationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSampledRelation(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::SampledRelationContext* PrestoSqlParser::sampledRelation() {
  SampledRelationContext* _localctx =
      _tracker.createInstance<SampledRelationContext>(_ctx, getState());
  enterRule(_localctx, 82, PrestoSqlParser::RuleSampledRelation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1393);
    aliasedRelation();
    setState(1400);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 179, _ctx)) {
      case 1: {
        setState(1394);
        match(PrestoSqlParser::TABLESAMPLE);
        setState(1395);
        sampleType();
        setState(1396);
        match(PrestoSqlParser::T__1);
        setState(1397);
        antlrcpp::downCast<SampledRelationContext*>(_localctx)->percentage =
            expression();
        setState(1398);
        match(PrestoSqlParser::T__2);
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SampleTypeContext
//------------------------------------------------------------------

PrestoSqlParser::SampleTypeContext::SampleTypeContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::SampleTypeContext::BERNOULLI() {
  return getToken(PrestoSqlParser::BERNOULLI, 0);
}

tree::TerminalNode* PrestoSqlParser::SampleTypeContext::SYSTEM() {
  return getToken(PrestoSqlParser::SYSTEM, 0);
}

size_t PrestoSqlParser::SampleTypeContext::getRuleIndex() const {
  return PrestoSqlParser::RuleSampleType;
}

void PrestoSqlParser::SampleTypeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSampleType(this);
}

void PrestoSqlParser::SampleTypeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSampleType(this);
}

std::any PrestoSqlParser::SampleTypeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSampleType(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::SampleTypeContext* PrestoSqlParser::sampleType() {
  SampleTypeContext* _localctx =
      _tracker.createInstance<SampleTypeContext>(_ctx, getState());
  enterRule(_localctx, 84, PrestoSqlParser::RuleSampleType);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1402);
    _la = _input->LA(1);
    if (!(_la == PrestoSqlParser::BERNOULLI ||
          _la == PrestoSqlParser::SYSTEM)) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AliasedRelationContext
//------------------------------------------------------------------

PrestoSqlParser::AliasedRelationContext::AliasedRelationContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::RelationPrimaryContext*
PrestoSqlParser::AliasedRelationContext::relationPrimary() {
  return getRuleContext<PrestoSqlParser::RelationPrimaryContext>(0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::AliasedRelationContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::AliasedRelationContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

PrestoSqlParser::ColumnAliasesContext*
PrestoSqlParser::AliasedRelationContext::columnAliases() {
  return getRuleContext<PrestoSqlParser::ColumnAliasesContext>(0);
}

size_t PrestoSqlParser::AliasedRelationContext::getRuleIndex() const {
  return PrestoSqlParser::RuleAliasedRelation;
}

void PrestoSqlParser::AliasedRelationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAliasedRelation(this);
}

void PrestoSqlParser::AliasedRelationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAliasedRelation(this);
}

std::any PrestoSqlParser::AliasedRelationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAliasedRelation(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::AliasedRelationContext* PrestoSqlParser::aliasedRelation() {
  AliasedRelationContext* _localctx =
      _tracker.createInstance<AliasedRelationContext>(_ctx, getState());
  enterRule(_localctx, 86, PrestoSqlParser::RuleAliasedRelation);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1404);
    relationPrimary();
    setState(1412);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 182, _ctx)) {
      case 1: {
        setState(1406);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::AS) {
          setState(1405);
          match(PrestoSqlParser::AS);
        }
        setState(1408);
        identifier();
        setState(1410);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 181, _ctx)) {
          case 1: {
            setState(1409);
            columnAliases();
            break;
          }

          default:
            break;
        }
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ColumnAliasesContext
//------------------------------------------------------------------

PrestoSqlParser::ColumnAliasesContext::ColumnAliasesContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::ColumnAliasesContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ColumnAliasesContext::identifier(size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

size_t PrestoSqlParser::ColumnAliasesContext::getRuleIndex() const {
  return PrestoSqlParser::RuleColumnAliases;
}

void PrestoSqlParser::ColumnAliasesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumnAliases(this);
}

void PrestoSqlParser::ColumnAliasesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumnAliases(this);
}

std::any PrestoSqlParser::ColumnAliasesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitColumnAliases(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ColumnAliasesContext* PrestoSqlParser::columnAliases() {
  ColumnAliasesContext* _localctx =
      _tracker.createInstance<ColumnAliasesContext>(_ctx, getState());
  enterRule(_localctx, 88, PrestoSqlParser::RuleColumnAliases);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1414);
    match(PrestoSqlParser::T__1);
    setState(1415);
    identifier();
    setState(1420);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrestoSqlParser::T__3) {
      setState(1416);
      match(PrestoSqlParser::T__3);
      setState(1417);
      identifier();
      setState(1422);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(1423);
    match(PrestoSqlParser::T__2);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelationPrimaryContext
//------------------------------------------------------------------

PrestoSqlParser::RelationPrimaryContext::RelationPrimaryContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::RelationPrimaryContext::getRuleIndex() const {
  return PrestoSqlParser::RuleRelationPrimary;
}

void PrestoSqlParser::RelationPrimaryContext::copyFrom(
    RelationPrimaryContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SubqueryRelationContext
//------------------------------------------------------------------

PrestoSqlParser::QueryContext*
PrestoSqlParser::SubqueryRelationContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

PrestoSqlParser::SubqueryRelationContext::SubqueryRelationContext(
    RelationPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SubqueryRelationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubqueryRelation(this);
}
void PrestoSqlParser::SubqueryRelationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubqueryRelation(this);
}

std::any PrestoSqlParser::SubqueryRelationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSubqueryRelation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesizedRelationContext
//------------------------------------------------------------------

PrestoSqlParser::RelationContext*
PrestoSqlParser::ParenthesizedRelationContext::relation() {
  return getRuleContext<PrestoSqlParser::RelationContext>(0);
}

PrestoSqlParser::ParenthesizedRelationContext::ParenthesizedRelationContext(
    RelationPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ParenthesizedRelationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenthesizedRelation(this);
}
void PrestoSqlParser::ParenthesizedRelationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenthesizedRelation(this);
}

std::any PrestoSqlParser::ParenthesizedRelationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitParenthesizedRelation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnnestContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::UnnestContext::UNNEST() {
  return getToken(PrestoSqlParser::UNNEST, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::UnnestContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext* PrestoSqlParser::UnnestContext::expression(
    size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::UnnestContext::WITH() {
  return getToken(PrestoSqlParser::WITH, 0);
}

tree::TerminalNode* PrestoSqlParser::UnnestContext::ORDINALITY() {
  return getToken(PrestoSqlParser::ORDINALITY, 0);
}

PrestoSqlParser::UnnestContext::UnnestContext(RelationPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::UnnestContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnnest(this);
}
void PrestoSqlParser::UnnestContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnnest(this);
}

std::any PrestoSqlParser::UnnestContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUnnest(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LateralContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::LateralContext::LATERAL() {
  return getToken(PrestoSqlParser::LATERAL, 0);
}

PrestoSqlParser::QueryContext* PrestoSqlParser::LateralContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

PrestoSqlParser::LateralContext::LateralContext(RelationPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::LateralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterLateral(this);
}
void PrestoSqlParser::LateralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitLateral(this);
}

std::any PrestoSqlParser::LateralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitLateral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TableNameContext
//------------------------------------------------------------------

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::TableNameContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

PrestoSqlParser::TableVersionExpressionContext*
PrestoSqlParser::TableNameContext::tableVersionExpression() {
  return getRuleContext<PrestoSqlParser::TableVersionExpressionContext>(0);
}

PrestoSqlParser::TableNameContext::TableNameContext(
    RelationPrimaryContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TableNameContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTableName(this);
}
void PrestoSqlParser::TableNameContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTableName(this);
}

std::any PrestoSqlParser::TableNameContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTableName(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::RelationPrimaryContext* PrestoSqlParser::relationPrimary() {
  RelationPrimaryContext* _localctx =
      _tracker.createInstance<RelationPrimaryContext>(_ctx, getState());
  enterRule(_localctx, 90, PrestoSqlParser::RuleRelationPrimary);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1457);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 187, _ctx)) {
      case 1: {
        _localctx = _tracker.createInstance<PrestoSqlParser::TableNameContext>(
            _localctx);
        enterOuterAlt(_localctx, 1);
        setState(1425);
        qualifiedName();
        setState(1427);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 184, _ctx)) {
          case 1: {
            setState(1426);
            tableVersionExpression();
            break;
          }

          default:
            break;
        }
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SubqueryRelationContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(1429);
        match(PrestoSqlParser::T__1);
        setState(1430);
        query();
        setState(1431);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 3: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UnnestContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(1433);
        match(PrestoSqlParser::UNNEST);
        setState(1434);
        match(PrestoSqlParser::T__1);
        setState(1435);
        expression();
        setState(1440);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(1436);
          match(PrestoSqlParser::T__3);
          setState(1437);
          expression();
          setState(1442);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1443);
        match(PrestoSqlParser::T__2);
        setState(1446);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 186, _ctx)) {
          case 1: {
            setState(1444);
            match(PrestoSqlParser::WITH);
            setState(1445);
            match(PrestoSqlParser::ORDINALITY);
            break;
          }

          default:
            break;
        }
        break;
      }

      case 4: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::LateralContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(1448);
        match(PrestoSqlParser::LATERAL);
        setState(1449);
        match(PrestoSqlParser::T__1);
        setState(1450);
        query();
        setState(1451);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 5: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::ParenthesizedRelationContext>(
                    _localctx);
        enterOuterAlt(_localctx, 5);
        setState(1453);
        match(PrestoSqlParser::T__1);
        setState(1454);
        relation(0);
        setState(1455);
        match(PrestoSqlParser::T__2);
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext
//------------------------------------------------------------------

PrestoSqlParser::ExpressionContext::ExpressionContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::ExpressionContext::booleanExpression() {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(0);
}

size_t PrestoSqlParser::ExpressionContext::getRuleIndex() const {
  return PrestoSqlParser::RuleExpression;
}

void PrestoSqlParser::ExpressionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void PrestoSqlParser::ExpressionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}

std::any PrestoSqlParser::ExpressionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ExpressionContext* PrestoSqlParser::expression() {
  ExpressionContext* _localctx =
      _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 92, PrestoSqlParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1459);
    booleanExpression(0);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanExpressionContext
//------------------------------------------------------------------

PrestoSqlParser::BooleanExpressionContext::BooleanExpressionContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::BooleanExpressionContext::getRuleIndex() const {
  return PrestoSqlParser::RuleBooleanExpression;
}

void PrestoSqlParser::BooleanExpressionContext::copyFrom(
    BooleanExpressionContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- LogicalNotContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::LogicalNotContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::LogicalNotContext::booleanExpression() {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(0);
}

PrestoSqlParser::LogicalNotContext::LogicalNotContext(
    BooleanExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::LogicalNotContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalNot(this);
}
void PrestoSqlParser::LogicalNotContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalNot(this);
}

std::any PrestoSqlParser::LogicalNotContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitLogicalNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PredicatedContext
//------------------------------------------------------------------

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::PredicatedContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

PrestoSqlParser::PredicateContext*
PrestoSqlParser::PredicatedContext::predicate() {
  return getRuleContext<PrestoSqlParser::PredicateContext>(0);
}

PrestoSqlParser::PredicatedContext::PredicatedContext(
    BooleanExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::PredicatedContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterPredicated(this);
}
void PrestoSqlParser::PredicatedContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitPredicated(this);
}

std::any PrestoSqlParser::PredicatedContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitPredicated(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalBinaryContext
//------------------------------------------------------------------

std::vector<PrestoSqlParser::BooleanExpressionContext*>
PrestoSqlParser::LogicalBinaryContext::booleanExpression() {
  return getRuleContexts<PrestoSqlParser::BooleanExpressionContext>();
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::LogicalBinaryContext::booleanExpression(size_t i) {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::LogicalBinaryContext::AND() {
  return getToken(PrestoSqlParser::AND, 0);
}

tree::TerminalNode* PrestoSqlParser::LogicalBinaryContext::OR() {
  return getToken(PrestoSqlParser::OR, 0);
}

PrestoSqlParser::LogicalBinaryContext::LogicalBinaryContext(
    BooleanExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::LogicalBinaryContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalBinary(this);
}
void PrestoSqlParser::LogicalBinaryContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalBinary(this);
}

std::any PrestoSqlParser::LogicalBinaryContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitLogicalBinary(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::booleanExpression() {
  return booleanExpression(0);
}

PrestoSqlParser::BooleanExpressionContext* PrestoSqlParser::booleanExpression(
    int precedence) {
  ParserRuleContext* parentContext = _ctx;
  size_t parentState = getState();
  PrestoSqlParser::BooleanExpressionContext* _localctx =
      _tracker.createInstance<BooleanExpressionContext>(_ctx, parentState);
  PrestoSqlParser::BooleanExpressionContext* previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by
                         // generated code.
  size_t startState = 94;
  enterRecursionRule(
      _localctx, 94, PrestoSqlParser::RuleBooleanExpression, precedence);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1468);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::T__1:
      case PrestoSqlParser::T__4:
      case PrestoSqlParser::ADD:
      case PrestoSqlParser::ADMIN:
      case PrestoSqlParser::ALL:
      case PrestoSqlParser::ANALYZE:
      case PrestoSqlParser::ANY:
      case PrestoSqlParser::ARRAY:
      case PrestoSqlParser::ASC:
      case PrestoSqlParser::AT:
      case PrestoSqlParser::BEFORE:
      case PrestoSqlParser::BERNOULLI:
      case PrestoSqlParser::CALL:
      case PrestoSqlParser::CALLED:
      case PrestoSqlParser::CASCADE:
      case PrestoSqlParser::CASE:
      case PrestoSqlParser::CAST:
      case PrestoSqlParser::CATALOGS:
      case PrestoSqlParser::COLUMN:
      case PrestoSqlParser::COLUMNS:
      case PrestoSqlParser::COMMENT:
      case PrestoSqlParser::COMMIT:
      case PrestoSqlParser::COMMITTED:
      case PrestoSqlParser::CURRENT:
      case PrestoSqlParser::CURRENT_DATE:
      case PrestoSqlParser::CURRENT_ROLE:
      case PrestoSqlParser::CURRENT_TIME:
      case PrestoSqlParser::CURRENT_TIMESTAMP:
      case PrestoSqlParser::CURRENT_USER:
      case PrestoSqlParser::DATA:
      case PrestoSqlParser::DATE:
      case PrestoSqlParser::DAY:
      case PrestoSqlParser::DEFINER:
      case PrestoSqlParser::DESC:
      case PrestoSqlParser::DETERMINISTIC:
      case PrestoSqlParser::DISABLED:
      case PrestoSqlParser::DISTRIBUTED:
      case PrestoSqlParser::ENABLED:
      case PrestoSqlParser::ENFORCED:
      case PrestoSqlParser::EXCLUDE:
      case PrestoSqlParser::EXCLUDING:
      case PrestoSqlParser::EXECUTABLE:
      case PrestoSqlParser::EXISTS:
      case PrestoSqlParser::EXPLAIN:
      case PrestoSqlParser::EXTRACT:
      case PrestoSqlParser::EXTERNAL:
      case PrestoSqlParser::FALSE:
      case PrestoSqlParser::FETCH:
      case PrestoSqlParser::FILTER:
      case PrestoSqlParser::FIRST:
      case PrestoSqlParser::FOLLOWING:
      case PrestoSqlParser::FORMAT:
      case PrestoSqlParser::FUNCTION:
      case PrestoSqlParser::FUNCTIONS:
      case PrestoSqlParser::GRANT:
      case PrestoSqlParser::GRANTED:
      case PrestoSqlParser::GRANTS:
      case PrestoSqlParser::GRAPH:
      case PrestoSqlParser::GRAPHVIZ:
      case PrestoSqlParser::GROUPING:
      case PrestoSqlParser::GROUPS:
      case PrestoSqlParser::HOUR:
      case PrestoSqlParser::IF:
      case PrestoSqlParser::IGNORE:
      case PrestoSqlParser::INCLUDING:
      case PrestoSqlParser::INPUT:
      case PrestoSqlParser::INTERVAL:
      case PrestoSqlParser::INVOKER:
      case PrestoSqlParser::IO:
      case PrestoSqlParser::ISOLATION:
      case PrestoSqlParser::JSON:
      case PrestoSqlParser::KEY:
      case PrestoSqlParser::LANGUAGE:
      case PrestoSqlParser::LAST:
      case PrestoSqlParser::LATERAL:
      case PrestoSqlParser::LEVEL:
      case PrestoSqlParser::LIMIT:
      case PrestoSqlParser::LOCALTIME:
      case PrestoSqlParser::LOCALTIMESTAMP:
      case PrestoSqlParser::LOGICAL:
      case PrestoSqlParser::MAP:
      case PrestoSqlParser::MATERIALIZED:
      case PrestoSqlParser::MINUTE:
      case PrestoSqlParser::MONTH:
      case PrestoSqlParser::NAME:
      case PrestoSqlParser::NFC:
      case PrestoSqlParser::NFD:
      case PrestoSqlParser::NFKC:
      case PrestoSqlParser::NFKD:
      case PrestoSqlParser::NO:
      case PrestoSqlParser::NONE:
      case PrestoSqlParser::NORMALIZE:
      case PrestoSqlParser::NULL_LITERAL:
      case PrestoSqlParser::NULLIF:
      case PrestoSqlParser::NULLS:
      case PrestoSqlParser::OF:
      case PrestoSqlParser::OFFSET:
      case PrestoSqlParser::ONLY:
      case PrestoSqlParser::OPTIMIZED:
      case PrestoSqlParser::OPTION:
      case PrestoSqlParser::ORDINALITY:
      case PrestoSqlParser::OUTPUT:
      case PrestoSqlParser::OVER:
      case PrestoSqlParser::PARTITION:
      case PrestoSqlParser::PARTITIONS:
      case PrestoSqlParser::POSITION:
      case PrestoSqlParser::PRECEDING:
      case PrestoSqlParser::PRIMARY:
      case PrestoSqlParser::PRIVILEGES:
      case PrestoSqlParser::PROPERTIES:
      case PrestoSqlParser::RANGE:
      case PrestoSqlParser::READ:
      case PrestoSqlParser::REFRESH:
      case PrestoSqlParser::RELY:
      case PrestoSqlParser::RENAME:
      case PrestoSqlParser::REPEATABLE:
      case PrestoSqlParser::REPLACE:
      case PrestoSqlParser::RESET:
      case PrestoSqlParser::RESPECT:
      case PrestoSqlParser::RESTRICT:
      case PrestoSqlParser::RETURN:
      case PrestoSqlParser::RETURNS:
      case PrestoSqlParser::REVOKE:
      case PrestoSqlParser::ROLE:
      case PrestoSqlParser::ROLES:
      case PrestoSqlParser::ROLLBACK:
      case PrestoSqlParser::ROW:
      case PrestoSqlParser::ROWS:
      case PrestoSqlParser::SCHEMA:
      case PrestoSqlParser::SCHEMAS:
      case PrestoSqlParser::SECOND:
      case PrestoSqlParser::SECURITY:
      case PrestoSqlParser::SERIALIZABLE:
      case PrestoSqlParser::SESSION:
      case PrestoSqlParser::SET:
      case PrestoSqlParser::SETS:
      case PrestoSqlParser::SHOW:
      case PrestoSqlParser::SOME:
      case PrestoSqlParser::SQL:
      case PrestoSqlParser::START:
      case PrestoSqlParser::STATS:
      case PrestoSqlParser::SUBSTRING:
      case PrestoSqlParser::SYSTEM:
      case PrestoSqlParser::SYSTEM_TIME:
      case PrestoSqlParser::SYSTEM_VERSION:
      case PrestoSqlParser::TABLES:
      case PrestoSqlParser::TABLESAMPLE:
      case PrestoSqlParser::TEMPORARY:
      case PrestoSqlParser::TEXT:
      case PrestoSqlParser::TIME:
      case PrestoSqlParser::TIMESTAMP:
      case PrestoSqlParser::TO:
      case PrestoSqlParser::TRANSACTION:
      case PrestoSqlParser::TRUE:
      case PrestoSqlParser::TRUNCATE:
      case PrestoSqlParser::TRY_CAST:
      case PrestoSqlParser::TYPE:
      case PrestoSqlParser::UNBOUNDED:
      case PrestoSqlParser::UNCOMMITTED:
      case PrestoSqlParser::UNIQUE:
      case PrestoSqlParser::UPDATE:
      case PrestoSqlParser::USE:
      case PrestoSqlParser::USER:
      case PrestoSqlParser::VALIDATE:
      case PrestoSqlParser::VERBOSE:
      case PrestoSqlParser::VERSION:
      case PrestoSqlParser::VIEW:
      case PrestoSqlParser::WORK:
      case PrestoSqlParser::WRITE:
      case PrestoSqlParser::YEAR:
      case PrestoSqlParser::ZONE:
      case PrestoSqlParser::PLUS:
      case PrestoSqlParser::MINUS:
      case PrestoSqlParser::STRING:
      case PrestoSqlParser::UNICODE_STRING:
      case PrestoSqlParser::BINARY_LITERAL:
      case PrestoSqlParser::INTEGER_VALUE:
      case PrestoSqlParser::DECIMAL_VALUE:
      case PrestoSqlParser::DOUBLE_VALUE:
      case PrestoSqlParser::IDENTIFIER:
      case PrestoSqlParser::DIGIT_IDENTIFIER:
      case PrestoSqlParser::QUOTED_IDENTIFIER:
      case PrestoSqlParser::BACKQUOTED_IDENTIFIER:
      case PrestoSqlParser::TIME_WITH_TIME_ZONE:
      case PrestoSqlParser::TIMESTAMP_WITH_TIME_ZONE:
      case PrestoSqlParser::DOUBLE_PRECISION: {
        _localctx = _tracker.createInstance<PredicatedContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(1462);
        antlrcpp::downCast<PredicatedContext*>(_localctx)
            ->valueExpressionContext = valueExpression(0);
        setState(1464);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 188, _ctx)) {
          case 1: {
            setState(1463);
            predicate(
                antlrcpp::downCast<PredicatedContext*>(_localctx)
                    ->valueExpressionContext);
            break;
          }

          default:
            break;
        }
        break;
      }

      case PrestoSqlParser::NOT: {
        _localctx = _tracker.createInstance<LogicalNotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1466);
        match(PrestoSqlParser::NOT);
        setState(1467);
        booleanExpression(3);
        break;
      }

      default:
        throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(1478);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 191, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(1476);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 190, _ctx)) {
          case 1: {
            auto newContext = _tracker.createInstance<LogicalBinaryContext>(
                _tracker.createInstance<BooleanExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->left = previousContext;
            pushNewRecursionContext(
                newContext, startState, RuleBooleanExpression);
            setState(1470);

            if (!(precpred(_ctx, 2)))
              throw FailedPredicateException(this, "precpred(_ctx, 2)");
            setState(1471);
            antlrcpp::downCast<LogicalBinaryContext*>(_localctx)->op =
                match(PrestoSqlParser::AND);
            setState(1472);
            antlrcpp::downCast<LogicalBinaryContext*>(_localctx)->right =
                booleanExpression(3);
            break;
          }

          case 2: {
            auto newContext = _tracker.createInstance<LogicalBinaryContext>(
                _tracker.createInstance<BooleanExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->left = previousContext;
            pushNewRecursionContext(
                newContext, startState, RuleBooleanExpression);
            setState(1473);

            if (!(precpred(_ctx, 1)))
              throw FailedPredicateException(this, "precpred(_ctx, 1)");
            setState(1474);
            antlrcpp::downCast<LogicalBinaryContext*>(_localctx)->op =
                match(PrestoSqlParser::OR);
            setState(1475);
            antlrcpp::downCast<LogicalBinaryContext*>(_localctx)->right =
                booleanExpression(2);
            break;
          }

          default:
            break;
        }
      }
      setState(1480);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 191, _ctx);
    }
  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PredicateContext
//------------------------------------------------------------------

PrestoSqlParser::PredicateContext::PredicateContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::PredicateContext::PredicateContext(
    ParserRuleContext* parent,
    size_t invokingState,
    antlr4::ParserRuleContext* value)
    : ParserRuleContext(parent, invokingState) {
  this->value = value;
}

size_t PrestoSqlParser::PredicateContext::getRuleIndex() const {
  return PrestoSqlParser::RulePredicate;
}

void PrestoSqlParser::PredicateContext::copyFrom(PredicateContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
  this->value = ctx->value;
}

//----------------- ComparisonContext
//------------------------------------------------------------------

PrestoSqlParser::ComparisonOperatorContext*
PrestoSqlParser::ComparisonContext::comparisonOperator() {
  return getRuleContext<PrestoSqlParser::ComparisonOperatorContext>(0);
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::ComparisonContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

PrestoSqlParser::ComparisonContext::ComparisonContext(PredicateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ComparisonContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparison(this);
}
void PrestoSqlParser::ComparisonContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparison(this);
}

std::any PrestoSqlParser::ComparisonContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LikeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::LikeContext::LIKE() {
  return getToken(PrestoSqlParser::LIKE, 0);
}

std::vector<PrestoSqlParser::ValueExpressionContext*>
PrestoSqlParser::LikeContext::valueExpression() {
  return getRuleContexts<PrestoSqlParser::ValueExpressionContext>();
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::LikeContext::valueExpression(size_t i) {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::LikeContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

tree::TerminalNode* PrestoSqlParser::LikeContext::ESCAPE() {
  return getToken(PrestoSqlParser::ESCAPE, 0);
}

PrestoSqlParser::LikeContext::LikeContext(PredicateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::LikeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterLike(this);
}
void PrestoSqlParser::LikeContext::exitRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitLike(this);
}

std::any PrestoSqlParser::LikeContext::accept(tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitLike(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InSubqueryContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::InSubqueryContext::IN() {
  return getToken(PrestoSqlParser::IN, 0);
}

PrestoSqlParser::QueryContext* PrestoSqlParser::InSubqueryContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

tree::TerminalNode* PrestoSqlParser::InSubqueryContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

PrestoSqlParser::InSubqueryContext::InSubqueryContext(PredicateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::InSubqueryContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterInSubquery(this);
}
void PrestoSqlParser::InSubqueryContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitInSubquery(this);
}

std::any PrestoSqlParser::InSubqueryContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitInSubquery(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DistinctFromContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DistinctFromContext::IS() {
  return getToken(PrestoSqlParser::IS, 0);
}

tree::TerminalNode* PrestoSqlParser::DistinctFromContext::DISTINCT() {
  return getToken(PrestoSqlParser::DISTINCT, 0);
}

tree::TerminalNode* PrestoSqlParser::DistinctFromContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::DistinctFromContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::DistinctFromContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

PrestoSqlParser::DistinctFromContext::DistinctFromContext(
    PredicateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DistinctFromContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDistinctFrom(this);
}
void PrestoSqlParser::DistinctFromContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDistinctFrom(this);
}

std::any PrestoSqlParser::DistinctFromContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDistinctFrom(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InListContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::InListContext::IN() {
  return getToken(PrestoSqlParser::IN, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::InListContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext* PrestoSqlParser::InListContext::expression(
    size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::InListContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

PrestoSqlParser::InListContext::InListContext(PredicateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::InListContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterInList(this);
}
void PrestoSqlParser::InListContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitInList(this);
}

std::any PrestoSqlParser::InListContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitInList(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NullPredicateContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::NullPredicateContext::IS() {
  return getToken(PrestoSqlParser::IS, 0);
}

tree::TerminalNode* PrestoSqlParser::NullPredicateContext::NULL_LITERAL() {
  return getToken(PrestoSqlParser::NULL_LITERAL, 0);
}

tree::TerminalNode* PrestoSqlParser::NullPredicateContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

PrestoSqlParser::NullPredicateContext::NullPredicateContext(
    PredicateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::NullPredicateContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNullPredicate(this);
}
void PrestoSqlParser::NullPredicateContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNullPredicate(this);
}

std::any PrestoSqlParser::NullPredicateContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNullPredicate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BetweenContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::BetweenContext::BETWEEN() {
  return getToken(PrestoSqlParser::BETWEEN, 0);
}

tree::TerminalNode* PrestoSqlParser::BetweenContext::AND() {
  return getToken(PrestoSqlParser::AND, 0);
}

std::vector<PrestoSqlParser::ValueExpressionContext*>
PrestoSqlParser::BetweenContext::valueExpression() {
  return getRuleContexts<PrestoSqlParser::ValueExpressionContext>();
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::BetweenContext::valueExpression(size_t i) {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::BetweenContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

PrestoSqlParser::BetweenContext::BetweenContext(PredicateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::BetweenContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterBetween(this);
}
void PrestoSqlParser::BetweenContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitBetween(this);
}

std::any PrestoSqlParser::BetweenContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitBetween(this);
  else
    return visitor->visitChildren(this);
}
//----------------- QuantifiedComparisonContext
//------------------------------------------------------------------

PrestoSqlParser::ComparisonOperatorContext*
PrestoSqlParser::QuantifiedComparisonContext::comparisonOperator() {
  return getRuleContext<PrestoSqlParser::ComparisonOperatorContext>(0);
}

PrestoSqlParser::ComparisonQuantifierContext*
PrestoSqlParser::QuantifiedComparisonContext::comparisonQuantifier() {
  return getRuleContext<PrestoSqlParser::ComparisonQuantifierContext>(0);
}

PrestoSqlParser::QueryContext*
PrestoSqlParser::QuantifiedComparisonContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

PrestoSqlParser::QuantifiedComparisonContext::QuantifiedComparisonContext(
    PredicateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::QuantifiedComparisonContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterQuantifiedComparison(this);
}
void PrestoSqlParser::QuantifiedComparisonContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitQuantifiedComparison(this);
}

std::any PrestoSqlParser::QuantifiedComparisonContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitQuantifiedComparison(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::PredicateContext* PrestoSqlParser::predicate(
    antlr4::ParserRuleContext* value) {
  PredicateContext* _localctx =
      _tracker.createInstance<PredicateContext>(_ctx, getState(), value);
  enterRule(_localctx, 96, PrestoSqlParser::RulePredicate);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1542);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 200, _ctx)) {
      case 1: {
        _localctx = _tracker.createInstance<PrestoSqlParser::ComparisonContext>(
            _localctx);
        enterOuterAlt(_localctx, 1);
        setState(1481);
        comparisonOperator();
        setState(1482);
        antlrcpp::downCast<ComparisonContext*>(_localctx)->right =
            valueExpression(0);
        break;
      }

      case 2: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::QuantifiedComparisonContext>(
                    _localctx);
        enterOuterAlt(_localctx, 2);
        setState(1484);
        comparisonOperator();
        setState(1485);
        comparisonQuantifier();
        setState(1486);
        match(PrestoSqlParser::T__1);
        setState(1487);
        query();
        setState(1488);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 3: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::BetweenContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(1491);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::NOT) {
          setState(1490);
          match(PrestoSqlParser::NOT);
        }
        setState(1493);
        match(PrestoSqlParser::BETWEEN);
        setState(1494);
        antlrcpp::downCast<BetweenContext*>(_localctx)->lower =
            valueExpression(0);
        setState(1495);
        match(PrestoSqlParser::AND);
        setState(1496);
        antlrcpp::downCast<BetweenContext*>(_localctx)->upper =
            valueExpression(0);
        break;
      }

      case 4: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::InListContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(1499);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::NOT) {
          setState(1498);
          match(PrestoSqlParser::NOT);
        }
        setState(1501);
        match(PrestoSqlParser::IN);
        setState(1502);
        match(PrestoSqlParser::T__1);
        setState(1503);
        expression();
        setState(1508);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(1504);
          match(PrestoSqlParser::T__3);
          setState(1505);
          expression();
          setState(1510);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1511);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 5: {
        _localctx = _tracker.createInstance<PrestoSqlParser::InSubqueryContext>(
            _localctx);
        enterOuterAlt(_localctx, 5);
        setState(1514);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::NOT) {
          setState(1513);
          match(PrestoSqlParser::NOT);
        }
        setState(1516);
        match(PrestoSqlParser::IN);
        setState(1517);
        match(PrestoSqlParser::T__1);
        setState(1518);
        query();
        setState(1519);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 6: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::LikeContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(1522);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::NOT) {
          setState(1521);
          match(PrestoSqlParser::NOT);
        }
        setState(1524);
        match(PrestoSqlParser::LIKE);
        setState(1525);
        antlrcpp::downCast<LikeContext*>(_localctx)->pattern =
            valueExpression(0);
        setState(1528);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 197, _ctx)) {
          case 1: {
            setState(1526);
            match(PrestoSqlParser::ESCAPE);
            setState(1527);
            antlrcpp::downCast<LikeContext*>(_localctx)->escape =
                valueExpression(0);
            break;
          }

          default:
            break;
        }
        break;
      }

      case 7: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::NullPredicateContext>(
                _localctx);
        enterOuterAlt(_localctx, 7);
        setState(1530);
        match(PrestoSqlParser::IS);
        setState(1532);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::NOT) {
          setState(1531);
          match(PrestoSqlParser::NOT);
        }
        setState(1534);
        match(PrestoSqlParser::NULL_LITERAL);
        break;
      }

      case 8: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DistinctFromContext>(
                _localctx);
        enterOuterAlt(_localctx, 8);
        setState(1535);
        match(PrestoSqlParser::IS);
        setState(1537);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::NOT) {
          setState(1536);
          match(PrestoSqlParser::NOT);
        }
        setState(1539);
        match(PrestoSqlParser::DISTINCT);
        setState(1540);
        match(PrestoSqlParser::FROM);
        setState(1541);
        antlrcpp::downCast<DistinctFromContext*>(_localctx)->right =
            valueExpression(0);
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ValueExpressionContext
//------------------------------------------------------------------

PrestoSqlParser::ValueExpressionContext::ValueExpressionContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::ValueExpressionContext::getRuleIndex() const {
  return PrestoSqlParser::RuleValueExpression;
}

void PrestoSqlParser::ValueExpressionContext::copyFrom(
    ValueExpressionContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ValueExpressionDefaultContext
//------------------------------------------------------------------

PrestoSqlParser::PrimaryExpressionContext*
PrestoSqlParser::ValueExpressionDefaultContext::primaryExpression() {
  return getRuleContext<PrestoSqlParser::PrimaryExpressionContext>(0);
}

PrestoSqlParser::ValueExpressionDefaultContext::ValueExpressionDefaultContext(
    ValueExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ValueExpressionDefaultContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterValueExpressionDefault(this);
}
void PrestoSqlParser::ValueExpressionDefaultContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitValueExpressionDefault(this);
}

std::any PrestoSqlParser::ValueExpressionDefaultContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitValueExpressionDefault(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ConcatenationContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ConcatenationContext::CONCAT() {
  return getToken(PrestoSqlParser::CONCAT, 0);
}

std::vector<PrestoSqlParser::ValueExpressionContext*>
PrestoSqlParser::ConcatenationContext::valueExpression() {
  return getRuleContexts<PrestoSqlParser::ValueExpressionContext>();
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::ConcatenationContext::valueExpression(size_t i) {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(i);
}

PrestoSqlParser::ConcatenationContext::ConcatenationContext(
    ValueExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ConcatenationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterConcatenation(this);
}
void PrestoSqlParser::ConcatenationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitConcatenation(this);
}

std::any PrestoSqlParser::ConcatenationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitConcatenation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArithmeticBinaryContext
//------------------------------------------------------------------

std::vector<PrestoSqlParser::ValueExpressionContext*>
PrestoSqlParser::ArithmeticBinaryContext::valueExpression() {
  return getRuleContexts<PrestoSqlParser::ValueExpressionContext>();
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::ArithmeticBinaryContext::valueExpression(size_t i) {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::ArithmeticBinaryContext::ASTERISK() {
  return getToken(PrestoSqlParser::ASTERISK, 0);
}

tree::TerminalNode* PrestoSqlParser::ArithmeticBinaryContext::SLASH() {
  return getToken(PrestoSqlParser::SLASH, 0);
}

tree::TerminalNode* PrestoSqlParser::ArithmeticBinaryContext::PERCENT() {
  return getToken(PrestoSqlParser::PERCENT, 0);
}

tree::TerminalNode* PrestoSqlParser::ArithmeticBinaryContext::PLUS() {
  return getToken(PrestoSqlParser::PLUS, 0);
}

tree::TerminalNode* PrestoSqlParser::ArithmeticBinaryContext::MINUS() {
  return getToken(PrestoSqlParser::MINUS, 0);
}

PrestoSqlParser::ArithmeticBinaryContext::ArithmeticBinaryContext(
    ValueExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ArithmeticBinaryContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterArithmeticBinary(this);
}
void PrestoSqlParser::ArithmeticBinaryContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitArithmeticBinary(this);
}

std::any PrestoSqlParser::ArithmeticBinaryContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitArithmeticBinary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArithmeticUnaryContext
//------------------------------------------------------------------

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::ArithmeticUnaryContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ArithmeticUnaryContext::MINUS() {
  return getToken(PrestoSqlParser::MINUS, 0);
}

tree::TerminalNode* PrestoSqlParser::ArithmeticUnaryContext::PLUS() {
  return getToken(PrestoSqlParser::PLUS, 0);
}

PrestoSqlParser::ArithmeticUnaryContext::ArithmeticUnaryContext(
    ValueExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ArithmeticUnaryContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterArithmeticUnary(this);
}
void PrestoSqlParser::ArithmeticUnaryContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitArithmeticUnary(this);
}

std::any PrestoSqlParser::ArithmeticUnaryContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitArithmeticUnary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AtTimeZoneContext
//------------------------------------------------------------------

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::AtTimeZoneContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::AtTimeZoneContext::AT() {
  return getToken(PrestoSqlParser::AT, 0);
}

PrestoSqlParser::TimeZoneSpecifierContext*
PrestoSqlParser::AtTimeZoneContext::timeZoneSpecifier() {
  return getRuleContext<PrestoSqlParser::TimeZoneSpecifierContext>(0);
}

PrestoSqlParser::AtTimeZoneContext::AtTimeZoneContext(
    ValueExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::AtTimeZoneContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterAtTimeZone(this);
}
void PrestoSqlParser::AtTimeZoneContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitAtTimeZone(this);
}

std::any PrestoSqlParser::AtTimeZoneContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitAtTimeZone(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ValueExpressionContext* PrestoSqlParser::valueExpression() {
  return valueExpression(0);
}

PrestoSqlParser::ValueExpressionContext* PrestoSqlParser::valueExpression(
    int precedence) {
  ParserRuleContext* parentContext = _ctx;
  size_t parentState = getState();
  PrestoSqlParser::ValueExpressionContext* _localctx =
      _tracker.createInstance<ValueExpressionContext>(_ctx, parentState);
  PrestoSqlParser::ValueExpressionContext* previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by
                         // generated code.
  size_t startState = 98;
  enterRecursionRule(
      _localctx, 98, PrestoSqlParser::RuleValueExpression, precedence);

  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1548);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::T__1:
      case PrestoSqlParser::T__4:
      case PrestoSqlParser::ADD:
      case PrestoSqlParser::ADMIN:
      case PrestoSqlParser::ALL:
      case PrestoSqlParser::ANALYZE:
      case PrestoSqlParser::ANY:
      case PrestoSqlParser::ARRAY:
      case PrestoSqlParser::ASC:
      case PrestoSqlParser::AT:
      case PrestoSqlParser::BEFORE:
      case PrestoSqlParser::BERNOULLI:
      case PrestoSqlParser::CALL:
      case PrestoSqlParser::CALLED:
      case PrestoSqlParser::CASCADE:
      case PrestoSqlParser::CASE:
      case PrestoSqlParser::CAST:
      case PrestoSqlParser::CATALOGS:
      case PrestoSqlParser::COLUMN:
      case PrestoSqlParser::COLUMNS:
      case PrestoSqlParser::COMMENT:
      case PrestoSqlParser::COMMIT:
      case PrestoSqlParser::COMMITTED:
      case PrestoSqlParser::CURRENT:
      case PrestoSqlParser::CURRENT_DATE:
      case PrestoSqlParser::CURRENT_ROLE:
      case PrestoSqlParser::CURRENT_TIME:
      case PrestoSqlParser::CURRENT_TIMESTAMP:
      case PrestoSqlParser::CURRENT_USER:
      case PrestoSqlParser::DATA:
      case PrestoSqlParser::DATE:
      case PrestoSqlParser::DAY:
      case PrestoSqlParser::DEFINER:
      case PrestoSqlParser::DESC:
      case PrestoSqlParser::DETERMINISTIC:
      case PrestoSqlParser::DISABLED:
      case PrestoSqlParser::DISTRIBUTED:
      case PrestoSqlParser::ENABLED:
      case PrestoSqlParser::ENFORCED:
      case PrestoSqlParser::EXCLUDE:
      case PrestoSqlParser::EXCLUDING:
      case PrestoSqlParser::EXECUTABLE:
      case PrestoSqlParser::EXISTS:
      case PrestoSqlParser::EXPLAIN:
      case PrestoSqlParser::EXTRACT:
      case PrestoSqlParser::EXTERNAL:
      case PrestoSqlParser::FALSE:
      case PrestoSqlParser::FETCH:
      case PrestoSqlParser::FILTER:
      case PrestoSqlParser::FIRST:
      case PrestoSqlParser::FOLLOWING:
      case PrestoSqlParser::FORMAT:
      case PrestoSqlParser::FUNCTION:
      case PrestoSqlParser::FUNCTIONS:
      case PrestoSqlParser::GRANT:
      case PrestoSqlParser::GRANTED:
      case PrestoSqlParser::GRANTS:
      case PrestoSqlParser::GRAPH:
      case PrestoSqlParser::GRAPHVIZ:
      case PrestoSqlParser::GROUPING:
      case PrestoSqlParser::GROUPS:
      case PrestoSqlParser::HOUR:
      case PrestoSqlParser::IF:
      case PrestoSqlParser::IGNORE:
      case PrestoSqlParser::INCLUDING:
      case PrestoSqlParser::INPUT:
      case PrestoSqlParser::INTERVAL:
      case PrestoSqlParser::INVOKER:
      case PrestoSqlParser::IO:
      case PrestoSqlParser::ISOLATION:
      case PrestoSqlParser::JSON:
      case PrestoSqlParser::KEY:
      case PrestoSqlParser::LANGUAGE:
      case PrestoSqlParser::LAST:
      case PrestoSqlParser::LATERAL:
      case PrestoSqlParser::LEVEL:
      case PrestoSqlParser::LIMIT:
      case PrestoSqlParser::LOCALTIME:
      case PrestoSqlParser::LOCALTIMESTAMP:
      case PrestoSqlParser::LOGICAL:
      case PrestoSqlParser::MAP:
      case PrestoSqlParser::MATERIALIZED:
      case PrestoSqlParser::MINUTE:
      case PrestoSqlParser::MONTH:
      case PrestoSqlParser::NAME:
      case PrestoSqlParser::NFC:
      case PrestoSqlParser::NFD:
      case PrestoSqlParser::NFKC:
      case PrestoSqlParser::NFKD:
      case PrestoSqlParser::NO:
      case PrestoSqlParser::NONE:
      case PrestoSqlParser::NORMALIZE:
      case PrestoSqlParser::NULL_LITERAL:
      case PrestoSqlParser::NULLIF:
      case PrestoSqlParser::NULLS:
      case PrestoSqlParser::OF:
      case PrestoSqlParser::OFFSET:
      case PrestoSqlParser::ONLY:
      case PrestoSqlParser::OPTIMIZED:
      case PrestoSqlParser::OPTION:
      case PrestoSqlParser::ORDINALITY:
      case PrestoSqlParser::OUTPUT:
      case PrestoSqlParser::OVER:
      case PrestoSqlParser::PARTITION:
      case PrestoSqlParser::PARTITIONS:
      case PrestoSqlParser::POSITION:
      case PrestoSqlParser::PRECEDING:
      case PrestoSqlParser::PRIMARY:
      case PrestoSqlParser::PRIVILEGES:
      case PrestoSqlParser::PROPERTIES:
      case PrestoSqlParser::RANGE:
      case PrestoSqlParser::READ:
      case PrestoSqlParser::REFRESH:
      case PrestoSqlParser::RELY:
      case PrestoSqlParser::RENAME:
      case PrestoSqlParser::REPEATABLE:
      case PrestoSqlParser::REPLACE:
      case PrestoSqlParser::RESET:
      case PrestoSqlParser::RESPECT:
      case PrestoSqlParser::RESTRICT:
      case PrestoSqlParser::RETURN:
      case PrestoSqlParser::RETURNS:
      case PrestoSqlParser::REVOKE:
      case PrestoSqlParser::ROLE:
      case PrestoSqlParser::ROLES:
      case PrestoSqlParser::ROLLBACK:
      case PrestoSqlParser::ROW:
      case PrestoSqlParser::ROWS:
      case PrestoSqlParser::SCHEMA:
      case PrestoSqlParser::SCHEMAS:
      case PrestoSqlParser::SECOND:
      case PrestoSqlParser::SECURITY:
      case PrestoSqlParser::SERIALIZABLE:
      case PrestoSqlParser::SESSION:
      case PrestoSqlParser::SET:
      case PrestoSqlParser::SETS:
      case PrestoSqlParser::SHOW:
      case PrestoSqlParser::SOME:
      case PrestoSqlParser::SQL:
      case PrestoSqlParser::START:
      case PrestoSqlParser::STATS:
      case PrestoSqlParser::SUBSTRING:
      case PrestoSqlParser::SYSTEM:
      case PrestoSqlParser::SYSTEM_TIME:
      case PrestoSqlParser::SYSTEM_VERSION:
      case PrestoSqlParser::TABLES:
      case PrestoSqlParser::TABLESAMPLE:
      case PrestoSqlParser::TEMPORARY:
      case PrestoSqlParser::TEXT:
      case PrestoSqlParser::TIME:
      case PrestoSqlParser::TIMESTAMP:
      case PrestoSqlParser::TO:
      case PrestoSqlParser::TRANSACTION:
      case PrestoSqlParser::TRUE:
      case PrestoSqlParser::TRUNCATE:
      case PrestoSqlParser::TRY_CAST:
      case PrestoSqlParser::TYPE:
      case PrestoSqlParser::UNBOUNDED:
      case PrestoSqlParser::UNCOMMITTED:
      case PrestoSqlParser::UNIQUE:
      case PrestoSqlParser::UPDATE:
      case PrestoSqlParser::USE:
      case PrestoSqlParser::USER:
      case PrestoSqlParser::VALIDATE:
      case PrestoSqlParser::VERBOSE:
      case PrestoSqlParser::VERSION:
      case PrestoSqlParser::VIEW:
      case PrestoSqlParser::WORK:
      case PrestoSqlParser::WRITE:
      case PrestoSqlParser::YEAR:
      case PrestoSqlParser::ZONE:
      case PrestoSqlParser::STRING:
      case PrestoSqlParser::UNICODE_STRING:
      case PrestoSqlParser::BINARY_LITERAL:
      case PrestoSqlParser::INTEGER_VALUE:
      case PrestoSqlParser::DECIMAL_VALUE:
      case PrestoSqlParser::DOUBLE_VALUE:
      case PrestoSqlParser::IDENTIFIER:
      case PrestoSqlParser::DIGIT_IDENTIFIER:
      case PrestoSqlParser::QUOTED_IDENTIFIER:
      case PrestoSqlParser::BACKQUOTED_IDENTIFIER:
      case PrestoSqlParser::TIME_WITH_TIME_ZONE:
      case PrestoSqlParser::TIMESTAMP_WITH_TIME_ZONE:
      case PrestoSqlParser::DOUBLE_PRECISION: {
        _localctx =
            _tracker.createInstance<ValueExpressionDefaultContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(1545);
        primaryExpression(0);
        break;
      }

      case PrestoSqlParser::PLUS:
      case PrestoSqlParser::MINUS: {
        _localctx = _tracker.createInstance<ArithmeticUnaryContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1546);
        antlrcpp::downCast<ArithmeticUnaryContext*>(_localctx)->op =
            _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == PrestoSqlParser::PLUS

              || _la == PrestoSqlParser::MINUS)) {
          antlrcpp::downCast<ArithmeticUnaryContext*>(_localctx)->op =
              _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(1547);
        valueExpression(4);
        break;
      }

      default:
        throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(1564);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 203, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(1562);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 202, _ctx)) {
          case 1: {
            auto newContext = _tracker.createInstance<ArithmeticBinaryContext>(
                _tracker.createInstance<ValueExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->left = previousContext;
            pushNewRecursionContext(
                newContext, startState, RuleValueExpression);
            setState(1550);

            if (!(precpred(_ctx, 3)))
              throw FailedPredicateException(this, "precpred(_ctx, 3)");
            setState(1551);
            antlrcpp::downCast<ArithmeticBinaryContext*>(_localctx)->op =
                _input->LT(1);
            _la = _input->LA(1);
            if (!(((((_la - 242) & ~0x3fULL) == 0) &&
                   ((1ULL << (_la - 242)) & 7) != 0))) {
              antlrcpp::downCast<ArithmeticBinaryContext*>(_localctx)->op =
                  _errHandler->recoverInline(this);
            } else {
              _errHandler->reportMatch(this);
              consume();
            }
            setState(1552);
            antlrcpp::downCast<ArithmeticBinaryContext*>(_localctx)->right =
                valueExpression(4);
            break;
          }

          case 2: {
            auto newContext = _tracker.createInstance<ArithmeticBinaryContext>(
                _tracker.createInstance<ValueExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->left = previousContext;
            pushNewRecursionContext(
                newContext, startState, RuleValueExpression);
            setState(1553);

            if (!(precpred(_ctx, 2)))
              throw FailedPredicateException(this, "precpred(_ctx, 2)");
            setState(1554);
            antlrcpp::downCast<ArithmeticBinaryContext*>(_localctx)->op =
                _input->LT(1);
            _la = _input->LA(1);
            if (!(_la == PrestoSqlParser::PLUS

                  || _la == PrestoSqlParser::MINUS)) {
              antlrcpp::downCast<ArithmeticBinaryContext*>(_localctx)->op =
                  _errHandler->recoverInline(this);
            } else {
              _errHandler->reportMatch(this);
              consume();
            }
            setState(1555);
            antlrcpp::downCast<ArithmeticBinaryContext*>(_localctx)->right =
                valueExpression(3);
            break;
          }

          case 3: {
            auto newContext = _tracker.createInstance<ConcatenationContext>(
                _tracker.createInstance<ValueExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->left = previousContext;
            pushNewRecursionContext(
                newContext, startState, RuleValueExpression);
            setState(1556);

            if (!(precpred(_ctx, 1)))
              throw FailedPredicateException(this, "precpred(_ctx, 1)");
            setState(1557);
            match(PrestoSqlParser::CONCAT);
            setState(1558);
            antlrcpp::downCast<ConcatenationContext*>(_localctx)->right =
                valueExpression(2);
            break;
          }

          case 4: {
            auto newContext = _tracker.createInstance<AtTimeZoneContext>(
                _tracker.createInstance<ValueExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            pushNewRecursionContext(
                newContext, startState, RuleValueExpression);
            setState(1559);

            if (!(precpred(_ctx, 5)))
              throw FailedPredicateException(this, "precpred(_ctx, 5)");
            setState(1560);
            match(PrestoSqlParser::AT);
            setState(1561);
            timeZoneSpecifier();
            break;
          }

          default:
            break;
        }
      }
      setState(1566);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 203, _ctx);
    }
  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PrimaryExpressionContext
//------------------------------------------------------------------

PrestoSqlParser::PrimaryExpressionContext::PrimaryExpressionContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::PrimaryExpressionContext::getRuleIndex() const {
  return PrestoSqlParser::RulePrimaryExpression;
}

void PrestoSqlParser::PrimaryExpressionContext::copyFrom(
    PrimaryExpressionContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DereferenceContext
//------------------------------------------------------------------

PrestoSqlParser::PrimaryExpressionContext*
PrestoSqlParser::DereferenceContext::primaryExpression() {
  return getRuleContext<PrestoSqlParser::PrimaryExpressionContext>(0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::DereferenceContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::DereferenceContext::DereferenceContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DereferenceContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDereference(this);
}
void PrestoSqlParser::DereferenceContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDereference(this);
}

std::any PrestoSqlParser::DereferenceContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDereference(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TypeConstructorContext
//------------------------------------------------------------------

PrestoSqlParser::TypeContext* PrestoSqlParser::TypeConstructorContext::type() {
  return getRuleContext<PrestoSqlParser::TypeContext>(0);
}

PrestoSqlParser::StringContext*
PrestoSqlParser::TypeConstructorContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

tree::TerminalNode*
PrestoSqlParser::TypeConstructorContext::DOUBLE_PRECISION() {
  return getToken(PrestoSqlParser::DOUBLE_PRECISION, 0);
}

PrestoSqlParser::TypeConstructorContext::TypeConstructorContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TypeConstructorContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeConstructor(this);
}
void PrestoSqlParser::TypeConstructorContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeConstructor(this);
}

std::any PrestoSqlParser::TypeConstructorContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTypeConstructor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SpecialDateTimeFunctionContext
//------------------------------------------------------------------

tree::TerminalNode*
PrestoSqlParser::SpecialDateTimeFunctionContext::CURRENT_DATE() {
  return getToken(PrestoSqlParser::CURRENT_DATE, 0);
}

tree::TerminalNode*
PrestoSqlParser::SpecialDateTimeFunctionContext::CURRENT_TIME() {
  return getToken(PrestoSqlParser::CURRENT_TIME, 0);
}

tree::TerminalNode*
PrestoSqlParser::SpecialDateTimeFunctionContext::INTEGER_VALUE() {
  return getToken(PrestoSqlParser::INTEGER_VALUE, 0);
}

tree::TerminalNode*
PrestoSqlParser::SpecialDateTimeFunctionContext::CURRENT_TIMESTAMP() {
  return getToken(PrestoSqlParser::CURRENT_TIMESTAMP, 0);
}

tree::TerminalNode*
PrestoSqlParser::SpecialDateTimeFunctionContext::LOCALTIME() {
  return getToken(PrestoSqlParser::LOCALTIME, 0);
}

tree::TerminalNode*
PrestoSqlParser::SpecialDateTimeFunctionContext::LOCALTIMESTAMP() {
  return getToken(PrestoSqlParser::LOCALTIMESTAMP, 0);
}

PrestoSqlParser::SpecialDateTimeFunctionContext::SpecialDateTimeFunctionContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SpecialDateTimeFunctionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSpecialDateTimeFunction(this);
}
void PrestoSqlParser::SpecialDateTimeFunctionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSpecialDateTimeFunction(this);
}

std::any PrestoSqlParser::SpecialDateTimeFunctionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSpecialDateTimeFunction(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubstringContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::SubstringContext::SUBSTRING() {
  return getToken(PrestoSqlParser::SUBSTRING, 0);
}

std::vector<PrestoSqlParser::ValueExpressionContext*>
PrestoSqlParser::SubstringContext::valueExpression() {
  return getRuleContexts<PrestoSqlParser::ValueExpressionContext>();
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::SubstringContext::valueExpression(size_t i) {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::SubstringContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

tree::TerminalNode* PrestoSqlParser::SubstringContext::FOR() {
  return getToken(PrestoSqlParser::FOR, 0);
}

PrestoSqlParser::SubstringContext::SubstringContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SubstringContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubstring(this);
}
void PrestoSqlParser::SubstringContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubstring(this);
}

std::any PrestoSqlParser::SubstringContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSubstring(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CastContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CastContext::CAST() {
  return getToken(PrestoSqlParser::CAST, 0);
}

PrestoSqlParser::ExpressionContext* PrestoSqlParser::CastContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CastContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

PrestoSqlParser::TypeContext* PrestoSqlParser::CastContext::type() {
  return getRuleContext<PrestoSqlParser::TypeContext>(0);
}

tree::TerminalNode* PrestoSqlParser::CastContext::TRY_CAST() {
  return getToken(PrestoSqlParser::TRY_CAST, 0);
}

PrestoSqlParser::CastContext::CastContext(PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CastContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCast(this);
}
void PrestoSqlParser::CastContext::exitRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCast(this);
}

std::any PrestoSqlParser::CastContext::accept(tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCast(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LambdaContext
//------------------------------------------------------------------

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::LambdaContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext* PrestoSqlParser::LambdaContext::identifier(
    size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::LambdaContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

PrestoSqlParser::LambdaContext::LambdaContext(PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::LambdaContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterLambda(this);
}
void PrestoSqlParser::LambdaContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitLambda(this);
}

std::any PrestoSqlParser::LambdaContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitLambda(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenthesizedExpressionContext
//------------------------------------------------------------------

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::ParenthesizedExpressionContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

PrestoSqlParser::ParenthesizedExpressionContext::ParenthesizedExpressionContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ParenthesizedExpressionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenthesizedExpression(this);
}
void PrestoSqlParser::ParenthesizedExpressionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenthesizedExpression(this);
}

std::any PrestoSqlParser::ParenthesizedExpressionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitParenthesizedExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParameterContext
//------------------------------------------------------------------

PrestoSqlParser::ParameterContext::ParameterContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ParameterContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter(this);
}
void PrestoSqlParser::ParameterContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter(this);
}

std::any PrestoSqlParser::ParameterContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NormalizeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::NormalizeContext::NORMALIZE() {
  return getToken(PrestoSqlParser::NORMALIZE, 0);
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::NormalizeContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

PrestoSqlParser::NormalFormContext*
PrestoSqlParser::NormalizeContext::normalForm() {
  return getRuleContext<PrestoSqlParser::NormalFormContext>(0);
}

PrestoSqlParser::NormalizeContext::NormalizeContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::NormalizeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNormalize(this);
}
void PrestoSqlParser::NormalizeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNormalize(this);
}

std::any PrestoSqlParser::NormalizeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNormalize(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntervalLiteralContext
//------------------------------------------------------------------

PrestoSqlParser::IntervalContext*
PrestoSqlParser::IntervalLiteralContext::interval() {
  return getRuleContext<PrestoSqlParser::IntervalContext>(0);
}

PrestoSqlParser::IntervalLiteralContext::IntervalLiteralContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::IntervalLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntervalLiteral(this);
}
void PrestoSqlParser::IntervalLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntervalLiteral(this);
}

std::any PrestoSqlParser::IntervalLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitIntervalLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumericLiteralContext
//------------------------------------------------------------------

PrestoSqlParser::NumberContext*
PrestoSqlParser::NumericLiteralContext::number() {
  return getRuleContext<PrestoSqlParser::NumberContext>(0);
}

PrestoSqlParser::NumericLiteralContext::NumericLiteralContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::NumericLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumericLiteral(this);
}
void PrestoSqlParser::NumericLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumericLiteral(this);
}

std::any PrestoSqlParser::NumericLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNumericLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleanLiteralContext
//------------------------------------------------------------------

PrestoSqlParser::BooleanValueContext*
PrestoSqlParser::BooleanLiteralContext::booleanValue() {
  return getRuleContext<PrestoSqlParser::BooleanValueContext>(0);
}

PrestoSqlParser::BooleanLiteralContext::BooleanLiteralContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::BooleanLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanLiteral(this);
}
void PrestoSqlParser::BooleanLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanLiteral(this);
}

std::any PrestoSqlParser::BooleanLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitBooleanLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SimpleCaseContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::SimpleCaseContext::CASE() {
  return getToken(PrestoSqlParser::CASE, 0);
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::SimpleCaseContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::SimpleCaseContext::END() {
  return getToken(PrestoSqlParser::END, 0);
}

std::vector<PrestoSqlParser::WhenClauseContext*>
PrestoSqlParser::SimpleCaseContext::whenClause() {
  return getRuleContexts<PrestoSqlParser::WhenClauseContext>();
}

PrestoSqlParser::WhenClauseContext*
PrestoSqlParser::SimpleCaseContext::whenClause(size_t i) {
  return getRuleContext<PrestoSqlParser::WhenClauseContext>(i);
}

tree::TerminalNode* PrestoSqlParser::SimpleCaseContext::ELSE() {
  return getToken(PrestoSqlParser::ELSE, 0);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::SimpleCaseContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

PrestoSqlParser::SimpleCaseContext::SimpleCaseContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SimpleCaseContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimpleCase(this);
}
void PrestoSqlParser::SimpleCaseContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimpleCase(this);
}

std::any PrestoSqlParser::SimpleCaseContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSimpleCase(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ColumnReferenceContext
//------------------------------------------------------------------

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ColumnReferenceContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::ColumnReferenceContext::ColumnReferenceContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ColumnReferenceContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterColumnReference(this);
}
void PrestoSqlParser::ColumnReferenceContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitColumnReference(this);
}

std::any PrestoSqlParser::ColumnReferenceContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitColumnReference(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NullLiteralContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::NullLiteralContext::NULL_LITERAL() {
  return getToken(PrestoSqlParser::NULL_LITERAL, 0);
}

PrestoSqlParser::NullLiteralContext::NullLiteralContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::NullLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNullLiteral(this);
}
void PrestoSqlParser::NullLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNullLiteral(this);
}

std::any PrestoSqlParser::NullLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNullLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RowConstructorContext
//------------------------------------------------------------------

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::RowConstructorContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::RowConstructorContext::expression(size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::RowConstructorContext::ROW() {
  return getToken(PrestoSqlParser::ROW, 0);
}

PrestoSqlParser::RowConstructorContext::RowConstructorContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RowConstructorContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRowConstructor(this);
}
void PrestoSqlParser::RowConstructorContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRowConstructor(this);
}

std::any PrestoSqlParser::RowConstructorContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRowConstructor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NamedRowConstructorContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::NamedRowConstructorContext::ROW() {
  return getToken(PrestoSqlParser::ROW, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::NamedRowConstructorContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::NamedRowConstructorContext::expression(size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

std::vector<tree::TerminalNode*>
PrestoSqlParser::NamedRowConstructorContext::AS() {
  return getTokens(PrestoSqlParser::AS);
}

tree::TerminalNode* PrestoSqlParser::NamedRowConstructorContext::AS(size_t i) {
  return getToken(PrestoSqlParser::AS, i);
}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::NamedRowConstructorContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::NamedRowConstructorContext::identifier(size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

PrestoSqlParser::NamedRowConstructorContext::NamedRowConstructorContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::NamedRowConstructorContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamedRowConstructor(this);
}
void PrestoSqlParser::NamedRowConstructorContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamedRowConstructor(this);
}

std::any PrestoSqlParser::NamedRowConstructorContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNamedRowConstructor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubscriptContext
//------------------------------------------------------------------

PrestoSqlParser::PrimaryExpressionContext*
PrestoSqlParser::SubscriptContext::primaryExpression() {
  return getRuleContext<PrestoSqlParser::PrimaryExpressionContext>(0);
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::SubscriptContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

PrestoSqlParser::SubscriptContext::SubscriptContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SubscriptContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubscript(this);
}
void PrestoSqlParser::SubscriptContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubscript(this);
}

std::any PrestoSqlParser::SubscriptContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSubscript(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SubqueryExpressionContext
//------------------------------------------------------------------

PrestoSqlParser::QueryContext*
PrestoSqlParser::SubqueryExpressionContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

PrestoSqlParser::SubqueryExpressionContext::SubqueryExpressionContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SubqueryExpressionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubqueryExpression(this);
}
void PrestoSqlParser::SubqueryExpressionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubqueryExpression(this);
}

std::any PrestoSqlParser::SubqueryExpressionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSubqueryExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BinaryLiteralContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::BinaryLiteralContext::BINARY_LITERAL() {
  return getToken(PrestoSqlParser::BINARY_LITERAL, 0);
}

PrestoSqlParser::BinaryLiteralContext::BinaryLiteralContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::BinaryLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterBinaryLiteral(this);
}
void PrestoSqlParser::BinaryLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitBinaryLiteral(this);
}

std::any PrestoSqlParser::BinaryLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitBinaryLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CurrentUserContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CurrentUserContext::CURRENT_USER() {
  return getToken(PrestoSqlParser::CURRENT_USER, 0);
}

PrestoSqlParser::CurrentUserContext::CurrentUserContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CurrentUserContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCurrentUser(this);
}
void PrestoSqlParser::CurrentUserContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCurrentUser(this);
}

std::any PrestoSqlParser::CurrentUserContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCurrentUser(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExtractContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ExtractContext::EXTRACT() {
  return getToken(PrestoSqlParser::EXTRACT, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::ExtractContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::ExtractContext::FROM() {
  return getToken(PrestoSqlParser::FROM, 0);
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::ExtractContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

PrestoSqlParser::ExtractContext::ExtractContext(PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ExtractContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExtract(this);
}
void PrestoSqlParser::ExtractContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExtract(this);
}

std::any PrestoSqlParser::ExtractContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExtract(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StringLiteralContext
//------------------------------------------------------------------

PrestoSqlParser::StringContext*
PrestoSqlParser::StringLiteralContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

PrestoSqlParser::StringLiteralContext::StringLiteralContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::StringLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringLiteral(this);
}
void PrestoSqlParser::StringLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringLiteral(this);
}

std::any PrestoSqlParser::StringLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArrayConstructorContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ArrayConstructorContext::ARRAY() {
  return getToken(PrestoSqlParser::ARRAY, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::ArrayConstructorContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::ArrayConstructorContext::expression(size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

PrestoSqlParser::ArrayConstructorContext::ArrayConstructorContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ArrayConstructorContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterArrayConstructor(this);
}
void PrestoSqlParser::ArrayConstructorContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitArrayConstructor(this);
}

std::any PrestoSqlParser::ArrayConstructorContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitArrayConstructor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext
//------------------------------------------------------------------

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::FunctionCallContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

tree::TerminalNode* PrestoSqlParser::FunctionCallContext::ASTERISK() {
  return getToken(PrestoSqlParser::ASTERISK, 0);
}

PrestoSqlParser::FilterContext* PrestoSqlParser::FunctionCallContext::filter() {
  return getRuleContext<PrestoSqlParser::FilterContext>(0);
}

PrestoSqlParser::OverContext* PrestoSqlParser::FunctionCallContext::over() {
  return getRuleContext<PrestoSqlParser::OverContext>(0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::FunctionCallContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::FunctionCallContext::expression(size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::FunctionCallContext::ORDER() {
  return getToken(PrestoSqlParser::ORDER, 0);
}

tree::TerminalNode* PrestoSqlParser::FunctionCallContext::BY() {
  return getToken(PrestoSqlParser::BY, 0);
}

std::vector<PrestoSqlParser::SortItemContext*>
PrestoSqlParser::FunctionCallContext::sortItem() {
  return getRuleContexts<PrestoSqlParser::SortItemContext>();
}

PrestoSqlParser::SortItemContext*
PrestoSqlParser::FunctionCallContext::sortItem(size_t i) {
  return getRuleContext<PrestoSqlParser::SortItemContext>(i);
}

PrestoSqlParser::SetQuantifierContext*
PrestoSqlParser::FunctionCallContext::setQuantifier() {
  return getRuleContext<PrestoSqlParser::SetQuantifierContext>(0);
}

PrestoSqlParser::NullTreatmentContext*
PrestoSqlParser::FunctionCallContext::nullTreatment() {
  return getRuleContext<PrestoSqlParser::NullTreatmentContext>(0);
}

PrestoSqlParser::FunctionCallContext::FunctionCallContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::FunctionCallContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}
void PrestoSqlParser::FunctionCallContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}

std::any PrestoSqlParser::FunctionCallContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExistsContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ExistsContext::EXISTS() {
  return getToken(PrestoSqlParser::EXISTS, 0);
}

PrestoSqlParser::QueryContext* PrestoSqlParser::ExistsContext::query() {
  return getRuleContext<PrestoSqlParser::QueryContext>(0);
}

PrestoSqlParser::ExistsContext::ExistsContext(PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ExistsContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExists(this);
}
void PrestoSqlParser::ExistsContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExists(this);
}

std::any PrestoSqlParser::ExistsContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExists(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PositionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::PositionContext::POSITION() {
  return getToken(PrestoSqlParser::POSITION, 0);
}

std::vector<PrestoSqlParser::ValueExpressionContext*>
PrestoSqlParser::PositionContext::valueExpression() {
  return getRuleContexts<PrestoSqlParser::ValueExpressionContext>();
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::PositionContext::valueExpression(size_t i) {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(i);
}

tree::TerminalNode* PrestoSqlParser::PositionContext::IN() {
  return getToken(PrestoSqlParser::IN, 0);
}

PrestoSqlParser::PositionContext::PositionContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::PositionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterPosition(this);
}
void PrestoSqlParser::PositionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitPosition(this);
}

std::any PrestoSqlParser::PositionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitPosition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SearchedCaseContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::SearchedCaseContext::CASE() {
  return getToken(PrestoSqlParser::CASE, 0);
}

tree::TerminalNode* PrestoSqlParser::SearchedCaseContext::END() {
  return getToken(PrestoSqlParser::END, 0);
}

std::vector<PrestoSqlParser::WhenClauseContext*>
PrestoSqlParser::SearchedCaseContext::whenClause() {
  return getRuleContexts<PrestoSqlParser::WhenClauseContext>();
}

PrestoSqlParser::WhenClauseContext*
PrestoSqlParser::SearchedCaseContext::whenClause(size_t i) {
  return getRuleContext<PrestoSqlParser::WhenClauseContext>(i);
}

tree::TerminalNode* PrestoSqlParser::SearchedCaseContext::ELSE() {
  return getToken(PrestoSqlParser::ELSE, 0);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::SearchedCaseContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

PrestoSqlParser::SearchedCaseContext::SearchedCaseContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SearchedCaseContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSearchedCase(this);
}
void PrestoSqlParser::SearchedCaseContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSearchedCase(this);
}

std::any PrestoSqlParser::SearchedCaseContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSearchedCase(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GroupingOperationContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::GroupingOperationContext::GROUPING() {
  return getToken(PrestoSqlParser::GROUPING, 0);
}

std::vector<PrestoSqlParser::QualifiedNameContext*>
PrestoSqlParser::GroupingOperationContext::qualifiedName() {
  return getRuleContexts<PrestoSqlParser::QualifiedNameContext>();
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::GroupingOperationContext::qualifiedName(size_t i) {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(i);
}

PrestoSqlParser::GroupingOperationContext::GroupingOperationContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::GroupingOperationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterGroupingOperation(this);
}
void PrestoSqlParser::GroupingOperationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitGroupingOperation(this);
}

std::any PrestoSqlParser::GroupingOperationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitGroupingOperation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MethodCallContext
//------------------------------------------------------------------

PrestoSqlParser::PrimaryExpressionContext*
PrestoSqlParser::MethodCallContext::primaryExpression() {
  return getRuleContext<PrestoSqlParser::PrimaryExpressionContext>(0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::MethodCallContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::MethodCallContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::MethodCallContext::expression(size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

PrestoSqlParser::MethodCallContext::MethodCallContext(
    PrimaryExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::MethodCallContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterMethodCall(this);
}
void PrestoSqlParser::MethodCallContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitMethodCall(this);
}

std::any PrestoSqlParser::MethodCallContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitMethodCall(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::PrimaryExpressionContext*
PrestoSqlParser::primaryExpression() {
  return primaryExpression(0);
}

PrestoSqlParser::PrimaryExpressionContext* PrestoSqlParser::primaryExpression(
    int precedence) {
  ParserRuleContext* parentContext = _ctx;
  size_t parentState = getState();
  PrestoSqlParser::PrimaryExpressionContext* _localctx =
      _tracker.createInstance<PrimaryExpressionContext>(_ctx, parentState);
  PrestoSqlParser::PrimaryExpressionContext* previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by
                         // generated code.
  size_t startState = 100;
  enterRecursionRule(
      _localctx, 100, PrestoSqlParser::RulePrimaryExpression, precedence);

  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1823);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 233, _ctx)) {
      case 1: {
        _localctx = _tracker.createInstance<NullLiteralContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(1568);
        match(PrestoSqlParser::NULL_LITERAL);
        break;
      }

      case 2: {
        _localctx = _tracker.createInstance<IntervalLiteralContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1569);
        interval();
        break;
      }

      case 3: {
        _localctx = _tracker.createInstance<TypeConstructorContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1570);
        type(0);
        setState(1571);
        string();
        break;
      }

      case 4: {
        _localctx = _tracker.createInstance<TypeConstructorContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1573);
        match(PrestoSqlParser::DOUBLE_PRECISION);
        setState(1574);
        string();
        break;
      }

      case 5: {
        _localctx = _tracker.createInstance<NumericLiteralContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1575);
        number();
        break;
      }

      case 6: {
        _localctx = _tracker.createInstance<BooleanLiteralContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1576);
        booleanValue();
        break;
      }

      case 7: {
        _localctx = _tracker.createInstance<StringLiteralContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1577);
        string();
        break;
      }

      case 8: {
        _localctx = _tracker.createInstance<BinaryLiteralContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1578);
        match(PrestoSqlParser::BINARY_LITERAL);
        break;
      }

      case 9: {
        _localctx = _tracker.createInstance<ParameterContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1579);
        match(PrestoSqlParser::T__4);
        break;
      }

      case 10: {
        _localctx = _tracker.createInstance<PositionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1580);
        match(PrestoSqlParser::POSITION);
        setState(1581);
        match(PrestoSqlParser::T__1);
        setState(1582);
        valueExpression(0);
        setState(1583);
        match(PrestoSqlParser::IN);
        setState(1584);
        valueExpression(0);
        setState(1585);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 11: {
        _localctx = _tracker.createInstance<RowConstructorContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1587);
        match(PrestoSqlParser::T__1);
        setState(1588);
        expression();
        setState(1591);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(1589);
          match(PrestoSqlParser::T__3);
          setState(1590);
          expression();
          setState(1593);
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == PrestoSqlParser::T__3);
        setState(1595);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 12: {
        _localctx = _tracker.createInstance<RowConstructorContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1597);
        match(PrestoSqlParser::ROW);
        setState(1598);
        match(PrestoSqlParser::T__1);
        setState(1599);
        expression();
        setState(1604);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(1600);
          match(PrestoSqlParser::T__3);
          setState(1601);
          expression();
          setState(1606);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1607);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 13: {
        _localctx =
            _tracker.createInstance<NamedRowConstructorContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1609);
        match(PrestoSqlParser::ROW);
        setState(1610);
        match(PrestoSqlParser::T__1);
        setState(1611);
        expression();
        setState(1612);
        match(PrestoSqlParser::AS);
        setState(1613);
        identifier();
        setState(1621);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(1614);
          match(PrestoSqlParser::T__3);
          setState(1615);
          expression();
          setState(1616);
          match(PrestoSqlParser::AS);
          setState(1617);
          identifier();
          setState(1623);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1624);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 14: {
        _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1626);
        qualifiedName();
        setState(1627);
        match(PrestoSqlParser::T__1);
        setState(1628);
        match(PrestoSqlParser::ASTERISK);
        setState(1629);
        match(PrestoSqlParser::T__2);
        setState(1631);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 207, _ctx)) {
          case 1: {
            setState(1630);
            filter();
            break;
          }

          default:
            break;
        }
        setState(1634);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 208, _ctx)) {
          case 1: {
            setState(1633);
            over();
            break;
          }

          default:
            break;
        }
        break;
      }

      case 15: {
        _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1636);
        qualifiedName();
        setState(1637);
        match(PrestoSqlParser::T__1);
        setState(1649);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6364714235016595420) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2308677939035742217) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260097) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & -4291454694588945) != 0) ||
            _la == PrestoSqlParser::DOUBLE_PRECISION) {
          setState(1639);
          _errHandler->sync(this);

          switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
              _input, 209, _ctx)) {
            case 1: {
              setState(1638);
              setQuantifier();
              break;
            }

            default:
              break;
          }
          setState(1641);
          expression();
          setState(1646);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(1642);
            match(PrestoSqlParser::T__3);
            setState(1643);
            expression();
            setState(1648);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(1661);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::ORDER) {
          setState(1651);
          match(PrestoSqlParser::ORDER);
          setState(1652);
          match(PrestoSqlParser::BY);
          setState(1653);
          sortItem();
          setState(1658);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(1654);
            match(PrestoSqlParser::T__3);
            setState(1655);
            sortItem();
            setState(1660);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(1663);
        match(PrestoSqlParser::T__2);
        setState(1665);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 214, _ctx)) {
          case 1: {
            setState(1664);
            filter();
            break;
          }

          default:
            break;
        }
        setState(1671);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 216, _ctx)) {
          case 1: {
            setState(1668);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == PrestoSqlParser::IGNORE ||
                _la == PrestoSqlParser::RESPECT) {
              setState(1667);
              nullTreatment();
            }
            setState(1670);
            over();
            break;
          }

          default:
            break;
        }
        break;
      }

      case 16: {
        _localctx = _tracker.createInstance<LambdaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1673);
        identifier();
        setState(1674);
        match(PrestoSqlParser::T__5);
        setState(1675);
        expression();
        break;
      }

      case 17: {
        _localctx = _tracker.createInstance<LambdaContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1677);
        match(PrestoSqlParser::T__1);
        setState(1686);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6508956968051886080) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2335699536833519961) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260209) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & 4323456680975908335) != 0)) {
          setState(1678);
          identifier();
          setState(1683);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(1679);
            match(PrestoSqlParser::T__3);
            setState(1680);
            identifier();
            setState(1685);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(1688);
        match(PrestoSqlParser::T__2);
        setState(1689);
        match(PrestoSqlParser::T__5);
        setState(1690);
        expression();
        break;
      }

      case 18: {
        _localctx =
            _tracker.createInstance<SubqueryExpressionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1691);
        match(PrestoSqlParser::T__1);
        setState(1692);
        query();
        setState(1693);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 19: {
        _localctx = _tracker.createInstance<ExistsContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1695);
        match(PrestoSqlParser::EXISTS);
        setState(1696);
        match(PrestoSqlParser::T__1);
        setState(1697);
        query();
        setState(1698);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 20: {
        _localctx = _tracker.createInstance<SimpleCaseContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1700);
        match(PrestoSqlParser::CASE);
        setState(1701);
        valueExpression(0);
        setState(1703);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(1702);
          whenClause();
          setState(1705);
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == PrestoSqlParser::WHEN);
        setState(1709);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::ELSE) {
          setState(1707);
          match(PrestoSqlParser::ELSE);
          setState(1708);
          antlrcpp::downCast<SimpleCaseContext*>(_localctx)->elseExpression =
              expression();
        }
        setState(1711);
        match(PrestoSqlParser::END);
        break;
      }

      case 21: {
        _localctx = _tracker.createInstance<SearchedCaseContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1713);
        match(PrestoSqlParser::CASE);
        setState(1715);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
          setState(1714);
          whenClause();
          setState(1717);
          _errHandler->sync(this);
          _la = _input->LA(1);
        } while (_la == PrestoSqlParser::WHEN);
        setState(1721);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::ELSE) {
          setState(1719);
          match(PrestoSqlParser::ELSE);
          setState(1720);
          antlrcpp::downCast<SearchedCaseContext*>(_localctx)->elseExpression =
              expression();
        }
        setState(1723);
        match(PrestoSqlParser::END);
        break;
      }

      case 22: {
        _localctx = _tracker.createInstance<CastContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1725);
        match(PrestoSqlParser::CAST);
        setState(1726);
        match(PrestoSqlParser::T__1);
        setState(1727);
        expression();
        setState(1728);
        match(PrestoSqlParser::AS);
        setState(1729);
        type(0);
        setState(1730);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 23: {
        _localctx = _tracker.createInstance<CastContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1732);
        match(PrestoSqlParser::TRY_CAST);
        setState(1733);
        match(PrestoSqlParser::T__1);
        setState(1734);
        expression();
        setState(1735);
        match(PrestoSqlParser::AS);
        setState(1736);
        type(0);
        setState(1737);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 24: {
        _localctx = _tracker.createInstance<ArrayConstructorContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1739);
        match(PrestoSqlParser::ARRAY);
        setState(1740);
        match(PrestoSqlParser::T__6);
        setState(1749);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6508829423092451292) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2308677939035742217) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260097) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & -4291454694588945) != 0) ||
            _la == PrestoSqlParser::DOUBLE_PRECISION) {
          setState(1741);
          expression();
          setState(1746);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(1742);
            match(PrestoSqlParser::T__3);
            setState(1743);
            expression();
            setState(1748);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(1751);
        match(PrestoSqlParser::T__7);
        break;
      }

      case 25: {
        _localctx = _tracker.createInstance<ColumnReferenceContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1752);
        identifier();
        break;
      }

      case 26: {
        _localctx =
            _tracker.createInstance<SpecialDateTimeFunctionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1753);
        antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)->name =
            match(PrestoSqlParser::CURRENT_DATE);
        break;
      }

      case 27: {
        _localctx =
            _tracker.createInstance<SpecialDateTimeFunctionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1754);
        antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)->name =
            match(PrestoSqlParser::CURRENT_TIME);
        setState(1758);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 225, _ctx)) {
          case 1: {
            setState(1755);
            match(PrestoSqlParser::T__1);
            setState(1756);
            antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)
                ->precision = match(PrestoSqlParser::INTEGER_VALUE);
            setState(1757);
            match(PrestoSqlParser::T__2);
            break;
          }

          default:
            break;
        }
        break;
      }

      case 28: {
        _localctx =
            _tracker.createInstance<SpecialDateTimeFunctionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1760);
        antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)->name =
            match(PrestoSqlParser::CURRENT_TIMESTAMP);
        setState(1764);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 226, _ctx)) {
          case 1: {
            setState(1761);
            match(PrestoSqlParser::T__1);
            setState(1762);
            antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)
                ->precision = match(PrestoSqlParser::INTEGER_VALUE);
            setState(1763);
            match(PrestoSqlParser::T__2);
            break;
          }

          default:
            break;
        }
        break;
      }

      case 29: {
        _localctx =
            _tracker.createInstance<SpecialDateTimeFunctionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1766);
        antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)->name =
            match(PrestoSqlParser::LOCALTIME);
        setState(1770);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 227, _ctx)) {
          case 1: {
            setState(1767);
            match(PrestoSqlParser::T__1);
            setState(1768);
            antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)
                ->precision = match(PrestoSqlParser::INTEGER_VALUE);
            setState(1769);
            match(PrestoSqlParser::T__2);
            break;
          }

          default:
            break;
        }
        break;
      }

      case 30: {
        _localctx =
            _tracker.createInstance<SpecialDateTimeFunctionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1772);
        antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)->name =
            match(PrestoSqlParser::LOCALTIMESTAMP);
        setState(1776);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 228, _ctx)) {
          case 1: {
            setState(1773);
            match(PrestoSqlParser::T__1);
            setState(1774);
            antlrcpp::downCast<SpecialDateTimeFunctionContext*>(_localctx)
                ->precision = match(PrestoSqlParser::INTEGER_VALUE);
            setState(1775);
            match(PrestoSqlParser::T__2);
            break;
          }

          default:
            break;
        }
        break;
      }

      case 31: {
        _localctx = _tracker.createInstance<CurrentUserContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1778);
        antlrcpp::downCast<CurrentUserContext*>(_localctx)->name =
            match(PrestoSqlParser::CURRENT_USER);
        break;
      }

      case 32: {
        _localctx = _tracker.createInstance<SubstringContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1779);
        match(PrestoSqlParser::SUBSTRING);
        setState(1780);
        match(PrestoSqlParser::T__1);
        setState(1781);
        valueExpression(0);
        setState(1782);
        match(PrestoSqlParser::FROM);
        setState(1783);
        valueExpression(0);
        setState(1786);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::FOR) {
          setState(1784);
          match(PrestoSqlParser::FOR);
          setState(1785);
          valueExpression(0);
        }
        setState(1788);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 33: {
        _localctx = _tracker.createInstance<NormalizeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1790);
        match(PrestoSqlParser::NORMALIZE);
        setState(1791);
        match(PrestoSqlParser::T__1);
        setState(1792);
        valueExpression(0);
        setState(1795);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == PrestoSqlParser::T__3) {
          setState(1793);
          match(PrestoSqlParser::T__3);
          setState(1794);
          normalForm();
        }
        setState(1797);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 34: {
        _localctx = _tracker.createInstance<ExtractContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1799);
        match(PrestoSqlParser::EXTRACT);
        setState(1800);
        match(PrestoSqlParser::T__1);
        setState(1801);
        identifier();
        setState(1802);
        match(PrestoSqlParser::FROM);
        setState(1803);
        valueExpression(0);
        setState(1804);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 35: {
        _localctx =
            _tracker.createInstance<ParenthesizedExpressionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1806);
        match(PrestoSqlParser::T__1);
        setState(1807);
        expression();
        setState(1808);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 36: {
        _localctx =
            _tracker.createInstance<GroupingOperationContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(1810);
        match(PrestoSqlParser::GROUPING);
        setState(1811);
        match(PrestoSqlParser::T__1);
        setState(1820);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) & -6508956968051886080) != 0) ||
            ((((_la - 66) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 66)) & -2335699536833519961) != 0) ||
            ((((_la - 130) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 130)) & -18163934272260209) != 0) ||
            ((((_la - 194) & ~0x3fULL) == 0) &&
             ((1ULL << (_la - 194)) & 4323456680975908335) != 0)) {
          setState(1812);
          qualifiedName();
          setState(1817);
          _errHandler->sync(this);
          _la = _input->LA(1);
          while (_la == PrestoSqlParser::T__3) {
            setState(1813);
            match(PrestoSqlParser::T__3);
            setState(1814);
            qualifiedName();
            setState(1819);
            _errHandler->sync(this);
            _la = _input->LA(1);
          }
        }
        setState(1822);
        match(PrestoSqlParser::T__2);
        break;
      }

      default:
        break;
    }
    _ctx->stop = _input->LT(-1);
    setState(1851);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 237, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(1849);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 236, _ctx)) {
          case 1: {
            auto newContext = _tracker.createInstance<SubscriptContext>(
                _tracker.createInstance<PrimaryExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->value = previousContext;
            pushNewRecursionContext(
                newContext, startState, RulePrimaryExpression);
            setState(1825);

            if (!(precpred(_ctx, 15)))
              throw FailedPredicateException(this, "precpred(_ctx, 15)");
            setState(1826);
            match(PrestoSqlParser::T__6);
            setState(1827);
            antlrcpp::downCast<SubscriptContext*>(_localctx)->index =
                valueExpression(0);
            setState(1828);
            match(PrestoSqlParser::T__7);
            break;
          }

          case 2: {
            auto newContext = _tracker.createInstance<MethodCallContext>(
                _tracker.createInstance<PrimaryExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->base = previousContext;
            pushNewRecursionContext(
                newContext, startState, RulePrimaryExpression);
            setState(1830);

            if (!(precpred(_ctx, 13)))
              throw FailedPredicateException(this, "precpred(_ctx, 13)");
            setState(1831);
            match(PrestoSqlParser::T__0);
            setState(1832);
            antlrcpp::downCast<MethodCallContext*>(_localctx)->functionName =
                identifier();
            setState(1833);
            match(PrestoSqlParser::T__1);
            setState(1842);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if ((((_la & ~0x3fULL) == 0) &&
                 ((1ULL << _la) & -6508829423092451292) != 0) ||
                ((((_la - 66) & ~0x3fULL) == 0) &&
                 ((1ULL << (_la - 66)) & -2308677939035742217) != 0) ||
                ((((_la - 130) & ~0x3fULL) == 0) &&
                 ((1ULL << (_la - 130)) & -18163934272260097) != 0) ||
                ((((_la - 194) & ~0x3fULL) == 0) &&
                 ((1ULL << (_la - 194)) & -4291454694588945) != 0) ||
                _la == PrestoSqlParser::DOUBLE_PRECISION) {
              setState(1834);
              antlrcpp::downCast<MethodCallContext*>(_localctx)
                  ->expressionContext = expression();
              antlrcpp::downCast<MethodCallContext*>(_localctx)
                  ->arguments.push_back(
                      antlrcpp::downCast<MethodCallContext*>(_localctx)
                          ->expressionContext);
              setState(1839);
              _errHandler->sync(this);
              _la = _input->LA(1);
              while (_la == PrestoSqlParser::T__3) {
                setState(1835);
                match(PrestoSqlParser::T__3);
                setState(1836);
                antlrcpp::downCast<MethodCallContext*>(_localctx)
                    ->expressionContext = expression();
                antlrcpp::downCast<MethodCallContext*>(_localctx)
                    ->arguments.push_back(
                        antlrcpp::downCast<MethodCallContext*>(_localctx)
                            ->expressionContext);
                setState(1841);
                _errHandler->sync(this);
                _la = _input->LA(1);
              }
            }
            setState(1844);
            match(PrestoSqlParser::T__2);
            break;
          }

          case 3: {
            auto newContext = _tracker.createInstance<DereferenceContext>(
                _tracker.createInstance<PrimaryExpressionContext>(
                    parentContext, parentState));
            _localctx = newContext;
            newContext->base = previousContext;
            pushNewRecursionContext(
                newContext, startState, RulePrimaryExpression);
            setState(1846);

            if (!(precpred(_ctx, 12)))
              throw FailedPredicateException(this, "precpred(_ctx, 12)");
            setState(1847);
            match(PrestoSqlParser::T__0);
            setState(1848);
            antlrcpp::downCast<DereferenceContext*>(_localctx)->fieldName =
                identifier();
            break;
          }

          default:
            break;
        }
      }
      setState(1853);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 237, _ctx);
    }
  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StringContext
//------------------------------------------------------------------

PrestoSqlParser::StringContext::StringContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::StringContext::getRuleIndex() const {
  return PrestoSqlParser::RuleString;
}

void PrestoSqlParser::StringContext::copyFrom(StringContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnicodeStringLiteralContext
//------------------------------------------------------------------

tree::TerminalNode*
PrestoSqlParser::UnicodeStringLiteralContext::UNICODE_STRING() {
  return getToken(PrestoSqlParser::UNICODE_STRING, 0);
}

tree::TerminalNode* PrestoSqlParser::UnicodeStringLiteralContext::UESCAPE() {
  return getToken(PrestoSqlParser::UESCAPE, 0);
}

tree::TerminalNode* PrestoSqlParser::UnicodeStringLiteralContext::STRING() {
  return getToken(PrestoSqlParser::STRING, 0);
}

PrestoSqlParser::UnicodeStringLiteralContext::UnicodeStringLiteralContext(
    StringContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::UnicodeStringLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnicodeStringLiteral(this);
}
void PrestoSqlParser::UnicodeStringLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnicodeStringLiteral(this);
}

std::any PrestoSqlParser::UnicodeStringLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUnicodeStringLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BasicStringLiteralContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::BasicStringLiteralContext::STRING() {
  return getToken(PrestoSqlParser::STRING, 0);
}

PrestoSqlParser::BasicStringLiteralContext::BasicStringLiteralContext(
    StringContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::BasicStringLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterBasicStringLiteral(this);
}
void PrestoSqlParser::BasicStringLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitBasicStringLiteral(this);
}

std::any PrestoSqlParser::BasicStringLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitBasicStringLiteral(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::StringContext* PrestoSqlParser::string() {
  StringContext* _localctx =
      _tracker.createInstance<StringContext>(_ctx, getState());
  enterRule(_localctx, 102, PrestoSqlParser::RuleString);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1860);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::STRING: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::BasicStringLiteralContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(1854);
        match(PrestoSqlParser::STRING);
        break;
      }

      case PrestoSqlParser::UNICODE_STRING: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::UnicodeStringLiteralContext>(
                    _localctx);
        enterOuterAlt(_localctx, 2);
        setState(1855);
        match(PrestoSqlParser::UNICODE_STRING);
        setState(1858);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 238, _ctx)) {
          case 1: {
            setState(1856);
            match(PrestoSqlParser::UESCAPE);
            setState(1857);
            match(PrestoSqlParser::STRING);
            break;
          }

          default:
            break;
        }
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NullTreatmentContext
//------------------------------------------------------------------

PrestoSqlParser::NullTreatmentContext::NullTreatmentContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::NullTreatmentContext::IGNORE() {
  return getToken(PrestoSqlParser::IGNORE, 0);
}

tree::TerminalNode* PrestoSqlParser::NullTreatmentContext::NULLS() {
  return getToken(PrestoSqlParser::NULLS, 0);
}

tree::TerminalNode* PrestoSqlParser::NullTreatmentContext::RESPECT() {
  return getToken(PrestoSqlParser::RESPECT, 0);
}

size_t PrestoSqlParser::NullTreatmentContext::getRuleIndex() const {
  return PrestoSqlParser::RuleNullTreatment;
}

void PrestoSqlParser::NullTreatmentContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNullTreatment(this);
}

void PrestoSqlParser::NullTreatmentContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNullTreatment(this);
}

std::any PrestoSqlParser::NullTreatmentContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNullTreatment(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::NullTreatmentContext* PrestoSqlParser::nullTreatment() {
  NullTreatmentContext* _localctx =
      _tracker.createInstance<NullTreatmentContext>(_ctx, getState());
  enterRule(_localctx, 104, PrestoSqlParser::RuleNullTreatment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1866);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::IGNORE: {
        enterOuterAlt(_localctx, 1);
        setState(1862);
        match(PrestoSqlParser::IGNORE);
        setState(1863);
        match(PrestoSqlParser::NULLS);
        break;
      }

      case PrestoSqlParser::RESPECT: {
        enterOuterAlt(_localctx, 2);
        setState(1864);
        match(PrestoSqlParser::RESPECT);
        setState(1865);
        match(PrestoSqlParser::NULLS);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TimeZoneSpecifierContext
//------------------------------------------------------------------

PrestoSqlParser::TimeZoneSpecifierContext::TimeZoneSpecifierContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::TimeZoneSpecifierContext::getRuleIndex() const {
  return PrestoSqlParser::RuleTimeZoneSpecifier;
}

void PrestoSqlParser::TimeZoneSpecifierContext::copyFrom(
    TimeZoneSpecifierContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TimeZoneIntervalContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::TimeZoneIntervalContext::TIME() {
  return getToken(PrestoSqlParser::TIME, 0);
}

tree::TerminalNode* PrestoSqlParser::TimeZoneIntervalContext::ZONE() {
  return getToken(PrestoSqlParser::ZONE, 0);
}

PrestoSqlParser::IntervalContext*
PrestoSqlParser::TimeZoneIntervalContext::interval() {
  return getRuleContext<PrestoSqlParser::IntervalContext>(0);
}

PrestoSqlParser::TimeZoneIntervalContext::TimeZoneIntervalContext(
    TimeZoneSpecifierContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TimeZoneIntervalContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTimeZoneInterval(this);
}
void PrestoSqlParser::TimeZoneIntervalContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTimeZoneInterval(this);
}

std::any PrestoSqlParser::TimeZoneIntervalContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTimeZoneInterval(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TimeZoneStringContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::TimeZoneStringContext::TIME() {
  return getToken(PrestoSqlParser::TIME, 0);
}

tree::TerminalNode* PrestoSqlParser::TimeZoneStringContext::ZONE() {
  return getToken(PrestoSqlParser::ZONE, 0);
}

PrestoSqlParser::StringContext*
PrestoSqlParser::TimeZoneStringContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

PrestoSqlParser::TimeZoneStringContext::TimeZoneStringContext(
    TimeZoneSpecifierContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TimeZoneStringContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTimeZoneString(this);
}
void PrestoSqlParser::TimeZoneStringContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTimeZoneString(this);
}

std::any PrestoSqlParser::TimeZoneStringContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTimeZoneString(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::TimeZoneSpecifierContext*
PrestoSqlParser::timeZoneSpecifier() {
  TimeZoneSpecifierContext* _localctx =
      _tracker.createInstance<TimeZoneSpecifierContext>(_ctx, getState());
  enterRule(_localctx, 106, PrestoSqlParser::RuleTimeZoneSpecifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1874);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 241, _ctx)) {
      case 1: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::TimeZoneIntervalContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(1868);
        match(PrestoSqlParser::TIME);
        setState(1869);
        match(PrestoSqlParser::ZONE);
        setState(1870);
        interval();
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::TimeZoneStringContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(1871);
        match(PrestoSqlParser::TIME);
        setState(1872);
        match(PrestoSqlParser::ZONE);
        setState(1873);
        string();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonOperatorContext
//------------------------------------------------------------------

PrestoSqlParser::ComparisonOperatorContext::ComparisonOperatorContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ComparisonOperatorContext::EQ() {
  return getToken(PrestoSqlParser::EQ, 0);
}

tree::TerminalNode* PrestoSqlParser::ComparisonOperatorContext::NEQ() {
  return getToken(PrestoSqlParser::NEQ, 0);
}

tree::TerminalNode* PrestoSqlParser::ComparisonOperatorContext::LT() {
  return getToken(PrestoSqlParser::LT, 0);
}

tree::TerminalNode* PrestoSqlParser::ComparisonOperatorContext::LTE() {
  return getToken(PrestoSqlParser::LTE, 0);
}

tree::TerminalNode* PrestoSqlParser::ComparisonOperatorContext::GT() {
  return getToken(PrestoSqlParser::GT, 0);
}

tree::TerminalNode* PrestoSqlParser::ComparisonOperatorContext::GTE() {
  return getToken(PrestoSqlParser::GTE, 0);
}

size_t PrestoSqlParser::ComparisonOperatorContext::getRuleIndex() const {
  return PrestoSqlParser::RuleComparisonOperator;
}

void PrestoSqlParser::ComparisonOperatorContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparisonOperator(this);
}

void PrestoSqlParser::ComparisonOperatorContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparisonOperator(this);
}

std::any PrestoSqlParser::ComparisonOperatorContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitComparisonOperator(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ComparisonOperatorContext*
PrestoSqlParser::comparisonOperator() {
  ComparisonOperatorContext* _localctx =
      _tracker.createInstance<ComparisonOperatorContext>(_ctx, getState());
  enterRule(_localctx, 108, PrestoSqlParser::RuleComparisonOperator);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1876);
    _la = _input->LA(1);
    if (!(((((_la - 234) & ~0x3fULL) == 0) &&
           ((1ULL << (_la - 234)) & 63) != 0))) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ComparisonQuantifierContext
//------------------------------------------------------------------

PrestoSqlParser::ComparisonQuantifierContext::ComparisonQuantifierContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ComparisonQuantifierContext::ALL() {
  return getToken(PrestoSqlParser::ALL, 0);
}

tree::TerminalNode* PrestoSqlParser::ComparisonQuantifierContext::SOME() {
  return getToken(PrestoSqlParser::SOME, 0);
}

tree::TerminalNode* PrestoSqlParser::ComparisonQuantifierContext::ANY() {
  return getToken(PrestoSqlParser::ANY, 0);
}

size_t PrestoSqlParser::ComparisonQuantifierContext::getRuleIndex() const {
  return PrestoSqlParser::RuleComparisonQuantifier;
}

void PrestoSqlParser::ComparisonQuantifierContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparisonQuantifier(this);
}

void PrestoSqlParser::ComparisonQuantifierContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparisonQuantifier(this);
}

std::any PrestoSqlParser::ComparisonQuantifierContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitComparisonQuantifier(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ComparisonQuantifierContext*
PrestoSqlParser::comparisonQuantifier() {
  ComparisonQuantifierContext* _localctx =
      _tracker.createInstance<ComparisonQuantifierContext>(_ctx, getState());
  enterRule(_localctx, 110, PrestoSqlParser::RuleComparisonQuantifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1878);
    _la = _input->LA(1);
    if (!(_la == PrestoSqlParser::ALL

          || _la == PrestoSqlParser::ANY || _la == PrestoSqlParser::SOME)) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BooleanValueContext
//------------------------------------------------------------------

PrestoSqlParser::BooleanValueContext::BooleanValueContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::BooleanValueContext::TRUE() {
  return getToken(PrestoSqlParser::TRUE, 0);
}

tree::TerminalNode* PrestoSqlParser::BooleanValueContext::FALSE() {
  return getToken(PrestoSqlParser::FALSE, 0);
}

size_t PrestoSqlParser::BooleanValueContext::getRuleIndex() const {
  return PrestoSqlParser::RuleBooleanValue;
}

void PrestoSqlParser::BooleanValueContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanValue(this);
}

void PrestoSqlParser::BooleanValueContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanValue(this);
}

std::any PrestoSqlParser::BooleanValueContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitBooleanValue(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::BooleanValueContext* PrestoSqlParser::booleanValue() {
  BooleanValueContext* _localctx =
      _tracker.createInstance<BooleanValueContext>(_ctx, getState());
  enterRule(_localctx, 112, PrestoSqlParser::RuleBooleanValue);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1880);
    _la = _input->LA(1);
    if (!(_la == PrestoSqlParser::FALSE || _la == PrestoSqlParser::TRUE)) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalContext
//------------------------------------------------------------------

PrestoSqlParser::IntervalContext::IntervalContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::IntervalContext::INTERVAL() {
  return getToken(PrestoSqlParser::INTERVAL, 0);
}

PrestoSqlParser::StringContext* PrestoSqlParser::IntervalContext::string() {
  return getRuleContext<PrestoSqlParser::StringContext>(0);
}

std::vector<PrestoSqlParser::IntervalFieldContext*>
PrestoSqlParser::IntervalContext::intervalField() {
  return getRuleContexts<PrestoSqlParser::IntervalFieldContext>();
}

PrestoSqlParser::IntervalFieldContext*
PrestoSqlParser::IntervalContext::intervalField(size_t i) {
  return getRuleContext<PrestoSqlParser::IntervalFieldContext>(i);
}

tree::TerminalNode* PrestoSqlParser::IntervalContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

tree::TerminalNode* PrestoSqlParser::IntervalContext::PLUS() {
  return getToken(PrestoSqlParser::PLUS, 0);
}

tree::TerminalNode* PrestoSqlParser::IntervalContext::MINUS() {
  return getToken(PrestoSqlParser::MINUS, 0);
}

size_t PrestoSqlParser::IntervalContext::getRuleIndex() const {
  return PrestoSqlParser::RuleInterval;
}

void PrestoSqlParser::IntervalContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterInterval(this);
}

void PrestoSqlParser::IntervalContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitInterval(this);
}

std::any PrestoSqlParser::IntervalContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitInterval(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::IntervalContext* PrestoSqlParser::interval() {
  IntervalContext* _localctx =
      _tracker.createInstance<IntervalContext>(_ctx, getState());
  enterRule(_localctx, 114, PrestoSqlParser::RuleInterval);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1882);
    match(PrestoSqlParser::INTERVAL);
    setState(1884);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::PLUS

        || _la == PrestoSqlParser::MINUS) {
      setState(1883);
      antlrcpp::downCast<IntervalContext*>(_localctx)->sign = _input->LT(1);
      _la = _input->LA(1);
      if (!(_la == PrestoSqlParser::PLUS

            || _la == PrestoSqlParser::MINUS)) {
        antlrcpp::downCast<IntervalContext*>(_localctx)->sign =
            _errHandler->recoverInline(this);
      } else {
        _errHandler->reportMatch(this);
        consume();
      }
    }
    setState(1886);
    string();
    setState(1887);
    antlrcpp::downCast<IntervalContext*>(_localctx)->from = intervalField();
    setState(1890);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 243, _ctx)) {
      case 1: {
        setState(1888);
        match(PrestoSqlParser::TO);
        setState(1889);
        antlrcpp::downCast<IntervalContext*>(_localctx)->to = intervalField();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntervalFieldContext
//------------------------------------------------------------------

PrestoSqlParser::IntervalFieldContext::IntervalFieldContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::IntervalFieldContext::YEAR() {
  return getToken(PrestoSqlParser::YEAR, 0);
}

tree::TerminalNode* PrestoSqlParser::IntervalFieldContext::MONTH() {
  return getToken(PrestoSqlParser::MONTH, 0);
}

tree::TerminalNode* PrestoSqlParser::IntervalFieldContext::DAY() {
  return getToken(PrestoSqlParser::DAY, 0);
}

tree::TerminalNode* PrestoSqlParser::IntervalFieldContext::HOUR() {
  return getToken(PrestoSqlParser::HOUR, 0);
}

tree::TerminalNode* PrestoSqlParser::IntervalFieldContext::MINUTE() {
  return getToken(PrestoSqlParser::MINUTE, 0);
}

tree::TerminalNode* PrestoSqlParser::IntervalFieldContext::SECOND() {
  return getToken(PrestoSqlParser::SECOND, 0);
}

size_t PrestoSqlParser::IntervalFieldContext::getRuleIndex() const {
  return PrestoSqlParser::RuleIntervalField;
}

void PrestoSqlParser::IntervalFieldContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntervalField(this);
}

void PrestoSqlParser::IntervalFieldContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntervalField(this);
}

std::any PrestoSqlParser::IntervalFieldContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitIntervalField(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::IntervalFieldContext* PrestoSqlParser::intervalField() {
  IntervalFieldContext* _localctx =
      _tracker.createInstance<IntervalFieldContext>(_ctx, getState());
  enterRule(_localctx, 116, PrestoSqlParser::RuleIntervalField);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1892);
    _la = _input->LA(1);
    if (!(_la == PrestoSqlParser::DAY ||
          ((((_la - 94) & ~0x3fULL) == 0) &&
           ((1ULL << (_la - 94)) & 3221225473) != 0) ||
          _la == PrestoSqlParser::SECOND

          || _la == PrestoSqlParser::YEAR)) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NormalFormContext
//------------------------------------------------------------------

PrestoSqlParser::NormalFormContext::NormalFormContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::NormalFormContext::NFD() {
  return getToken(PrestoSqlParser::NFD, 0);
}

tree::TerminalNode* PrestoSqlParser::NormalFormContext::NFC() {
  return getToken(PrestoSqlParser::NFC, 0);
}

tree::TerminalNode* PrestoSqlParser::NormalFormContext::NFKD() {
  return getToken(PrestoSqlParser::NFKD, 0);
}

tree::TerminalNode* PrestoSqlParser::NormalFormContext::NFKC() {
  return getToken(PrestoSqlParser::NFKC, 0);
}

size_t PrestoSqlParser::NormalFormContext::getRuleIndex() const {
  return PrestoSqlParser::RuleNormalForm;
}

void PrestoSqlParser::NormalFormContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNormalForm(this);
}

void PrestoSqlParser::NormalFormContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNormalForm(this);
}

std::any PrestoSqlParser::NormalFormContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNormalForm(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::NormalFormContext* PrestoSqlParser::normalForm() {
  NormalFormContext* _localctx =
      _tracker.createInstance<NormalFormContext>(_ctx, getState());
  enterRule(_localctx, 118, PrestoSqlParser::RuleNormalForm);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1894);
    _la = _input->LA(1);
    if (!(((((_la - 128) & ~0x3fULL) == 0) &&
           ((1ULL << (_la - 128)) & 15) != 0))) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypesContext
//------------------------------------------------------------------

PrestoSqlParser::TypesContext::TypesContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::TypeContext*>
PrestoSqlParser::TypesContext::type() {
  return getRuleContexts<PrestoSqlParser::TypeContext>();
}

PrestoSqlParser::TypeContext* PrestoSqlParser::TypesContext::type(size_t i) {
  return getRuleContext<PrestoSqlParser::TypeContext>(i);
}

size_t PrestoSqlParser::TypesContext::getRuleIndex() const {
  return PrestoSqlParser::RuleTypes;
}

void PrestoSqlParser::TypesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypes(this);
}

void PrestoSqlParser::TypesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypes(this);
}

std::any PrestoSqlParser::TypesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTypes(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::TypesContext* PrestoSqlParser::types() {
  TypesContext* _localctx =
      _tracker.createInstance<TypesContext>(_ctx, getState());
  enterRule(_localctx, 120, PrestoSqlParser::RuleTypes);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1896);
    match(PrestoSqlParser::T__1);
    setState(1905);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 11) & ~0x3fULL) == 0) &&
         ((1ULL << (_la - 11)) & 6022638099777167063) != 0) ||
        ((((_la - 75) & ~0x3fULL) == 0) &&
         ((1ULL << (_la - 75)) & -4039787179281842385) != 0) ||
        ((((_la - 139) & ~0x3fULL) == 0) &&
         ((1ULL << (_la - 139)) & -576496228737548997) != 0) ||
        ((((_la - 204) & ~0x3fULL) == 0) &&
         ((1ULL << (_la - 204)) & 35747323056609007) != 0)) {
      setState(1897);
      type(0);
      setState(1902);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PrestoSqlParser::T__3) {
        setState(1898);
        match(PrestoSqlParser::T__3);
        setState(1899);
        type(0);
        setState(1904);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1907);
    match(PrestoSqlParser::T__2);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeContext
//------------------------------------------------------------------

PrestoSqlParser::TypeContext::TypeContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::TypeContext::ARRAY() {
  return getToken(PrestoSqlParser::ARRAY, 0);
}

tree::TerminalNode* PrestoSqlParser::TypeContext::LT() {
  return getToken(PrestoSqlParser::LT, 0);
}

std::vector<PrestoSqlParser::TypeContext*>
PrestoSqlParser::TypeContext::type() {
  return getRuleContexts<PrestoSqlParser::TypeContext>();
}

PrestoSqlParser::TypeContext* PrestoSqlParser::TypeContext::type(size_t i) {
  return getRuleContext<PrestoSqlParser::TypeContext>(i);
}

tree::TerminalNode* PrestoSqlParser::TypeContext::GT() {
  return getToken(PrestoSqlParser::GT, 0);
}

tree::TerminalNode* PrestoSqlParser::TypeContext::MAP() {
  return getToken(PrestoSqlParser::MAP, 0);
}

tree::TerminalNode* PrestoSqlParser::TypeContext::ROW() {
  return getToken(PrestoSqlParser::ROW, 0);
}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::TypeContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext* PrestoSqlParser::TypeContext::identifier(
    size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

PrestoSqlParser::BaseTypeContext* PrestoSqlParser::TypeContext::baseType() {
  return getRuleContext<PrestoSqlParser::BaseTypeContext>(0);
}

std::vector<PrestoSqlParser::TypeParameterContext*>
PrestoSqlParser::TypeContext::typeParameter() {
  return getRuleContexts<PrestoSqlParser::TypeParameterContext>();
}

PrestoSqlParser::TypeParameterContext*
PrestoSqlParser::TypeContext::typeParameter(size_t i) {
  return getRuleContext<PrestoSqlParser::TypeParameterContext>(i);
}

tree::TerminalNode* PrestoSqlParser::TypeContext::INTERVAL() {
  return getToken(PrestoSqlParser::INTERVAL, 0);
}

tree::TerminalNode* PrestoSqlParser::TypeContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

std::vector<PrestoSqlParser::IntervalFieldContext*>
PrestoSqlParser::TypeContext::intervalField() {
  return getRuleContexts<PrestoSqlParser::IntervalFieldContext>();
}

PrestoSqlParser::IntervalFieldContext*
PrestoSqlParser::TypeContext::intervalField(size_t i) {
  return getRuleContext<PrestoSqlParser::IntervalFieldContext>(i);
}

size_t PrestoSqlParser::TypeContext::getRuleIndex() const {
  return PrestoSqlParser::RuleType;
}

void PrestoSqlParser::TypeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterType(this);
}

void PrestoSqlParser::TypeContext::exitRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitType(this);
}

std::any PrestoSqlParser::TypeContext::accept(tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitType(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::TypeContext* PrestoSqlParser::type() {
  return type(0);
}

PrestoSqlParser::TypeContext* PrestoSqlParser::type(int precedence) {
  ParserRuleContext* parentContext = _ctx;
  size_t parentState = getState();
  PrestoSqlParser::TypeContext* _localctx =
      _tracker.createInstance<TypeContext>(_ctx, parentState);
  PrestoSqlParser::TypeContext* previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by
                         // generated code.
  size_t startState = 122;
  enterRecursionRule(_localctx, 122, PrestoSqlParser::RuleType, precedence);

  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1956);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 249, _ctx)) {
      case 1: {
        setState(1910);
        match(PrestoSqlParser::ARRAY);
        setState(1911);
        match(PrestoSqlParser::LT);
        setState(1912);
        type(0);
        setState(1913);
        match(PrestoSqlParser::GT);
        break;
      }

      case 2: {
        setState(1915);
        match(PrestoSqlParser::MAP);
        setState(1916);
        match(PrestoSqlParser::LT);
        setState(1917);
        type(0);
        setState(1918);
        match(PrestoSqlParser::T__3);
        setState(1919);
        type(0);
        setState(1920);
        match(PrestoSqlParser::GT);
        break;
      }

      case 3: {
        setState(1922);
        match(PrestoSqlParser::ROW);
        setState(1923);
        match(PrestoSqlParser::T__1);
        setState(1924);
        identifier();
        setState(1925);
        type(0);
        setState(1932);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == PrestoSqlParser::T__3) {
          setState(1926);
          match(PrestoSqlParser::T__3);
          setState(1927);
          identifier();
          setState(1928);
          type(0);
          setState(1934);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(1935);
        match(PrestoSqlParser::T__2);
        break;
      }

      case 4: {
        setState(1937);
        baseType();
        setState(1949);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 248, _ctx)) {
          case 1: {
            setState(1938);
            match(PrestoSqlParser::T__1);
            setState(1939);
            typeParameter();
            setState(1944);
            _errHandler->sync(this);
            _la = _input->LA(1);
            while (_la == PrestoSqlParser::T__3) {
              setState(1940);
              match(PrestoSqlParser::T__3);
              setState(1941);
              typeParameter();
              setState(1946);
              _errHandler->sync(this);
              _la = _input->LA(1);
            }
            setState(1947);
            match(PrestoSqlParser::T__2);
            break;
          }

          default:
            break;
        }
        break;
      }

      case 5: {
        setState(1951);
        match(PrestoSqlParser::INTERVAL);
        setState(1952);
        antlrcpp::downCast<TypeContext*>(_localctx)->from = intervalField();
        setState(1953);
        match(PrestoSqlParser::TO);
        setState(1954);
        antlrcpp::downCast<TypeContext*>(_localctx)->to = intervalField();
        break;
      }

      default:
        break;
    }
    _ctx->stop = _input->LT(-1);
    setState(1962);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 250, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx =
            _tracker.createInstance<TypeContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleType);
        setState(1958);

        if (!(precpred(_ctx, 6)))
          throw FailedPredicateException(this, "precpred(_ctx, 6)");
        setState(1959);
        match(PrestoSqlParser::ARRAY);
      }
      setState(1964);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 250, _ctx);
    }
  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- TypeParameterContext
//------------------------------------------------------------------

PrestoSqlParser::TypeParameterContext::TypeParameterContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::TypeParameterContext::INTEGER_VALUE() {
  return getToken(PrestoSqlParser::INTEGER_VALUE, 0);
}

PrestoSqlParser::TypeContext* PrestoSqlParser::TypeParameterContext::type() {
  return getRuleContext<PrestoSqlParser::TypeContext>(0);
}

size_t PrestoSqlParser::TypeParameterContext::getRuleIndex() const {
  return PrestoSqlParser::RuleTypeParameter;
}

void PrestoSqlParser::TypeParameterContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeParameter(this);
}

void PrestoSqlParser::TypeParameterContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeParameter(this);
}

std::any PrestoSqlParser::TypeParameterContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTypeParameter(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::TypeParameterContext* PrestoSqlParser::typeParameter() {
  TypeParameterContext* _localctx =
      _tracker.createInstance<TypeParameterContext>(_ctx, getState());
  enterRule(_localctx, 124, PrestoSqlParser::RuleTypeParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1967);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::INTEGER_VALUE: {
        enterOuterAlt(_localctx, 1);
        setState(1965);
        match(PrestoSqlParser::INTEGER_VALUE);
        break;
      }

      case PrestoSqlParser::ADD:
      case PrestoSqlParser::ADMIN:
      case PrestoSqlParser::ALL:
      case PrestoSqlParser::ANALYZE:
      case PrestoSqlParser::ANY:
      case PrestoSqlParser::ARRAY:
      case PrestoSqlParser::ASC:
      case PrestoSqlParser::AT:
      case PrestoSqlParser::BEFORE:
      case PrestoSqlParser::BERNOULLI:
      case PrestoSqlParser::CALL:
      case PrestoSqlParser::CALLED:
      case PrestoSqlParser::CASCADE:
      case PrestoSqlParser::CATALOGS:
      case PrestoSqlParser::COLUMN:
      case PrestoSqlParser::COLUMNS:
      case PrestoSqlParser::COMMENT:
      case PrestoSqlParser::COMMIT:
      case PrestoSqlParser::COMMITTED:
      case PrestoSqlParser::CURRENT:
      case PrestoSqlParser::CURRENT_ROLE:
      case PrestoSqlParser::DATA:
      case PrestoSqlParser::DATE:
      case PrestoSqlParser::DAY:
      case PrestoSqlParser::DEFINER:
      case PrestoSqlParser::DESC:
      case PrestoSqlParser::DETERMINISTIC:
      case PrestoSqlParser::DISABLED:
      case PrestoSqlParser::DISTRIBUTED:
      case PrestoSqlParser::ENABLED:
      case PrestoSqlParser::ENFORCED:
      case PrestoSqlParser::EXCLUDE:
      case PrestoSqlParser::EXCLUDING:
      case PrestoSqlParser::EXECUTABLE:
      case PrestoSqlParser::EXPLAIN:
      case PrestoSqlParser::EXTERNAL:
      case PrestoSqlParser::FETCH:
      case PrestoSqlParser::FILTER:
      case PrestoSqlParser::FIRST:
      case PrestoSqlParser::FOLLOWING:
      case PrestoSqlParser::FORMAT:
      case PrestoSqlParser::FUNCTION:
      case PrestoSqlParser::FUNCTIONS:
      case PrestoSqlParser::GRANT:
      case PrestoSqlParser::GRANTED:
      case PrestoSqlParser::GRANTS:
      case PrestoSqlParser::GRAPH:
      case PrestoSqlParser::GRAPHVIZ:
      case PrestoSqlParser::GROUPS:
      case PrestoSqlParser::HOUR:
      case PrestoSqlParser::IF:
      case PrestoSqlParser::IGNORE:
      case PrestoSqlParser::INCLUDING:
      case PrestoSqlParser::INPUT:
      case PrestoSqlParser::INTERVAL:
      case PrestoSqlParser::INVOKER:
      case PrestoSqlParser::IO:
      case PrestoSqlParser::ISOLATION:
      case PrestoSqlParser::JSON:
      case PrestoSqlParser::KEY:
      case PrestoSqlParser::LANGUAGE:
      case PrestoSqlParser::LAST:
      case PrestoSqlParser::LATERAL:
      case PrestoSqlParser::LEVEL:
      case PrestoSqlParser::LIMIT:
      case PrestoSqlParser::LOGICAL:
      case PrestoSqlParser::MAP:
      case PrestoSqlParser::MATERIALIZED:
      case PrestoSqlParser::MINUTE:
      case PrestoSqlParser::MONTH:
      case PrestoSqlParser::NAME:
      case PrestoSqlParser::NFC:
      case PrestoSqlParser::NFD:
      case PrestoSqlParser::NFKC:
      case PrestoSqlParser::NFKD:
      case PrestoSqlParser::NO:
      case PrestoSqlParser::NONE:
      case PrestoSqlParser::NULLIF:
      case PrestoSqlParser::NULLS:
      case PrestoSqlParser::OF:
      case PrestoSqlParser::OFFSET:
      case PrestoSqlParser::ONLY:
      case PrestoSqlParser::OPTIMIZED:
      case PrestoSqlParser::OPTION:
      case PrestoSqlParser::ORDINALITY:
      case PrestoSqlParser::OUTPUT:
      case PrestoSqlParser::OVER:
      case PrestoSqlParser::PARTITION:
      case PrestoSqlParser::PARTITIONS:
      case PrestoSqlParser::POSITION:
      case PrestoSqlParser::PRECEDING:
      case PrestoSqlParser::PRIMARY:
      case PrestoSqlParser::PRIVILEGES:
      case PrestoSqlParser::PROPERTIES:
      case PrestoSqlParser::RANGE:
      case PrestoSqlParser::READ:
      case PrestoSqlParser::REFRESH:
      case PrestoSqlParser::RELY:
      case PrestoSqlParser::RENAME:
      case PrestoSqlParser::REPEATABLE:
      case PrestoSqlParser::REPLACE:
      case PrestoSqlParser::RESET:
      case PrestoSqlParser::RESPECT:
      case PrestoSqlParser::RESTRICT:
      case PrestoSqlParser::RETURN:
      case PrestoSqlParser::RETURNS:
      case PrestoSqlParser::REVOKE:
      case PrestoSqlParser::ROLE:
      case PrestoSqlParser::ROLES:
      case PrestoSqlParser::ROLLBACK:
      case PrestoSqlParser::ROW:
      case PrestoSqlParser::ROWS:
      case PrestoSqlParser::SCHEMA:
      case PrestoSqlParser::SCHEMAS:
      case PrestoSqlParser::SECOND:
      case PrestoSqlParser::SECURITY:
      case PrestoSqlParser::SERIALIZABLE:
      case PrestoSqlParser::SESSION:
      case PrestoSqlParser::SET:
      case PrestoSqlParser::SETS:
      case PrestoSqlParser::SHOW:
      case PrestoSqlParser::SOME:
      case PrestoSqlParser::SQL:
      case PrestoSqlParser::START:
      case PrestoSqlParser::STATS:
      case PrestoSqlParser::SUBSTRING:
      case PrestoSqlParser::SYSTEM:
      case PrestoSqlParser::SYSTEM_TIME:
      case PrestoSqlParser::SYSTEM_VERSION:
      case PrestoSqlParser::TABLES:
      case PrestoSqlParser::TABLESAMPLE:
      case PrestoSqlParser::TEMPORARY:
      case PrestoSqlParser::TEXT:
      case PrestoSqlParser::TIME:
      case PrestoSqlParser::TIMESTAMP:
      case PrestoSqlParser::TO:
      case PrestoSqlParser::TRANSACTION:
      case PrestoSqlParser::TRUNCATE:
      case PrestoSqlParser::TRY_CAST:
      case PrestoSqlParser::TYPE:
      case PrestoSqlParser::UNBOUNDED:
      case PrestoSqlParser::UNCOMMITTED:
      case PrestoSqlParser::UNIQUE:
      case PrestoSqlParser::UPDATE:
      case PrestoSqlParser::USE:
      case PrestoSqlParser::USER:
      case PrestoSqlParser::VALIDATE:
      case PrestoSqlParser::VERBOSE:
      case PrestoSqlParser::VERSION:
      case PrestoSqlParser::VIEW:
      case PrestoSqlParser::WORK:
      case PrestoSqlParser::WRITE:
      case PrestoSqlParser::YEAR:
      case PrestoSqlParser::ZONE:
      case PrestoSqlParser::IDENTIFIER:
      case PrestoSqlParser::DIGIT_IDENTIFIER:
      case PrestoSqlParser::QUOTED_IDENTIFIER:
      case PrestoSqlParser::BACKQUOTED_IDENTIFIER:
      case PrestoSqlParser::TIME_WITH_TIME_ZONE:
      case PrestoSqlParser::TIMESTAMP_WITH_TIME_ZONE:
      case PrestoSqlParser::DOUBLE_PRECISION: {
        enterOuterAlt(_localctx, 2);
        setState(1966);
        type(0);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BaseTypeContext
//------------------------------------------------------------------

PrestoSqlParser::BaseTypeContext::BaseTypeContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::BaseTypeContext::TIME_WITH_TIME_ZONE() {
  return getToken(PrestoSqlParser::TIME_WITH_TIME_ZONE, 0);
}

tree::TerminalNode*
PrestoSqlParser::BaseTypeContext::TIMESTAMP_WITH_TIME_ZONE() {
  return getToken(PrestoSqlParser::TIMESTAMP_WITH_TIME_ZONE, 0);
}

tree::TerminalNode* PrestoSqlParser::BaseTypeContext::DOUBLE_PRECISION() {
  return getToken(PrestoSqlParser::DOUBLE_PRECISION, 0);
}

PrestoSqlParser::QualifiedNameContext*
PrestoSqlParser::BaseTypeContext::qualifiedName() {
  return getRuleContext<PrestoSqlParser::QualifiedNameContext>(0);
}

size_t PrestoSqlParser::BaseTypeContext::getRuleIndex() const {
  return PrestoSqlParser::RuleBaseType;
}

void PrestoSqlParser::BaseTypeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterBaseType(this);
}

void PrestoSqlParser::BaseTypeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitBaseType(this);
}

std::any PrestoSqlParser::BaseTypeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitBaseType(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::BaseTypeContext* PrestoSqlParser::baseType() {
  BaseTypeContext* _localctx =
      _tracker.createInstance<BaseTypeContext>(_ctx, getState());
  enterRule(_localctx, 126, PrestoSqlParser::RuleBaseType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(1973);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::TIME_WITH_TIME_ZONE: {
        enterOuterAlt(_localctx, 1);
        setState(1969);
        match(PrestoSqlParser::TIME_WITH_TIME_ZONE);
        break;
      }

      case PrestoSqlParser::TIMESTAMP_WITH_TIME_ZONE: {
        enterOuterAlt(_localctx, 2);
        setState(1970);
        match(PrestoSqlParser::TIMESTAMP_WITH_TIME_ZONE);
        break;
      }

      case PrestoSqlParser::DOUBLE_PRECISION: {
        enterOuterAlt(_localctx, 3);
        setState(1971);
        match(PrestoSqlParser::DOUBLE_PRECISION);
        break;
      }

      case PrestoSqlParser::ADD:
      case PrestoSqlParser::ADMIN:
      case PrestoSqlParser::ALL:
      case PrestoSqlParser::ANALYZE:
      case PrestoSqlParser::ANY:
      case PrestoSqlParser::ARRAY:
      case PrestoSqlParser::ASC:
      case PrestoSqlParser::AT:
      case PrestoSqlParser::BEFORE:
      case PrestoSqlParser::BERNOULLI:
      case PrestoSqlParser::CALL:
      case PrestoSqlParser::CALLED:
      case PrestoSqlParser::CASCADE:
      case PrestoSqlParser::CATALOGS:
      case PrestoSqlParser::COLUMN:
      case PrestoSqlParser::COLUMNS:
      case PrestoSqlParser::COMMENT:
      case PrestoSqlParser::COMMIT:
      case PrestoSqlParser::COMMITTED:
      case PrestoSqlParser::CURRENT:
      case PrestoSqlParser::CURRENT_ROLE:
      case PrestoSqlParser::DATA:
      case PrestoSqlParser::DATE:
      case PrestoSqlParser::DAY:
      case PrestoSqlParser::DEFINER:
      case PrestoSqlParser::DESC:
      case PrestoSqlParser::DETERMINISTIC:
      case PrestoSqlParser::DISABLED:
      case PrestoSqlParser::DISTRIBUTED:
      case PrestoSqlParser::ENABLED:
      case PrestoSqlParser::ENFORCED:
      case PrestoSqlParser::EXCLUDE:
      case PrestoSqlParser::EXCLUDING:
      case PrestoSqlParser::EXECUTABLE:
      case PrestoSqlParser::EXPLAIN:
      case PrestoSqlParser::EXTERNAL:
      case PrestoSqlParser::FETCH:
      case PrestoSqlParser::FILTER:
      case PrestoSqlParser::FIRST:
      case PrestoSqlParser::FOLLOWING:
      case PrestoSqlParser::FORMAT:
      case PrestoSqlParser::FUNCTION:
      case PrestoSqlParser::FUNCTIONS:
      case PrestoSqlParser::GRANT:
      case PrestoSqlParser::GRANTED:
      case PrestoSqlParser::GRANTS:
      case PrestoSqlParser::GRAPH:
      case PrestoSqlParser::GRAPHVIZ:
      case PrestoSqlParser::GROUPS:
      case PrestoSqlParser::HOUR:
      case PrestoSqlParser::IF:
      case PrestoSqlParser::IGNORE:
      case PrestoSqlParser::INCLUDING:
      case PrestoSqlParser::INPUT:
      case PrestoSqlParser::INTERVAL:
      case PrestoSqlParser::INVOKER:
      case PrestoSqlParser::IO:
      case PrestoSqlParser::ISOLATION:
      case PrestoSqlParser::JSON:
      case PrestoSqlParser::KEY:
      case PrestoSqlParser::LANGUAGE:
      case PrestoSqlParser::LAST:
      case PrestoSqlParser::LATERAL:
      case PrestoSqlParser::LEVEL:
      case PrestoSqlParser::LIMIT:
      case PrestoSqlParser::LOGICAL:
      case PrestoSqlParser::MAP:
      case PrestoSqlParser::MATERIALIZED:
      case PrestoSqlParser::MINUTE:
      case PrestoSqlParser::MONTH:
      case PrestoSqlParser::NAME:
      case PrestoSqlParser::NFC:
      case PrestoSqlParser::NFD:
      case PrestoSqlParser::NFKC:
      case PrestoSqlParser::NFKD:
      case PrestoSqlParser::NO:
      case PrestoSqlParser::NONE:
      case PrestoSqlParser::NULLIF:
      case PrestoSqlParser::NULLS:
      case PrestoSqlParser::OF:
      case PrestoSqlParser::OFFSET:
      case PrestoSqlParser::ONLY:
      case PrestoSqlParser::OPTIMIZED:
      case PrestoSqlParser::OPTION:
      case PrestoSqlParser::ORDINALITY:
      case PrestoSqlParser::OUTPUT:
      case PrestoSqlParser::OVER:
      case PrestoSqlParser::PARTITION:
      case PrestoSqlParser::PARTITIONS:
      case PrestoSqlParser::POSITION:
      case PrestoSqlParser::PRECEDING:
      case PrestoSqlParser::PRIMARY:
      case PrestoSqlParser::PRIVILEGES:
      case PrestoSqlParser::PROPERTIES:
      case PrestoSqlParser::RANGE:
      case PrestoSqlParser::READ:
      case PrestoSqlParser::REFRESH:
      case PrestoSqlParser::RELY:
      case PrestoSqlParser::RENAME:
      case PrestoSqlParser::REPEATABLE:
      case PrestoSqlParser::REPLACE:
      case PrestoSqlParser::RESET:
      case PrestoSqlParser::RESPECT:
      case PrestoSqlParser::RESTRICT:
      case PrestoSqlParser::RETURN:
      case PrestoSqlParser::RETURNS:
      case PrestoSqlParser::REVOKE:
      case PrestoSqlParser::ROLE:
      case PrestoSqlParser::ROLES:
      case PrestoSqlParser::ROLLBACK:
      case PrestoSqlParser::ROW:
      case PrestoSqlParser::ROWS:
      case PrestoSqlParser::SCHEMA:
      case PrestoSqlParser::SCHEMAS:
      case PrestoSqlParser::SECOND:
      case PrestoSqlParser::SECURITY:
      case PrestoSqlParser::SERIALIZABLE:
      case PrestoSqlParser::SESSION:
      case PrestoSqlParser::SET:
      case PrestoSqlParser::SETS:
      case PrestoSqlParser::SHOW:
      case PrestoSqlParser::SOME:
      case PrestoSqlParser::SQL:
      case PrestoSqlParser::START:
      case PrestoSqlParser::STATS:
      case PrestoSqlParser::SUBSTRING:
      case PrestoSqlParser::SYSTEM:
      case PrestoSqlParser::SYSTEM_TIME:
      case PrestoSqlParser::SYSTEM_VERSION:
      case PrestoSqlParser::TABLES:
      case PrestoSqlParser::TABLESAMPLE:
      case PrestoSqlParser::TEMPORARY:
      case PrestoSqlParser::TEXT:
      case PrestoSqlParser::TIME:
      case PrestoSqlParser::TIMESTAMP:
      case PrestoSqlParser::TO:
      case PrestoSqlParser::TRANSACTION:
      case PrestoSqlParser::TRUNCATE:
      case PrestoSqlParser::TRY_CAST:
      case PrestoSqlParser::TYPE:
      case PrestoSqlParser::UNBOUNDED:
      case PrestoSqlParser::UNCOMMITTED:
      case PrestoSqlParser::UNIQUE:
      case PrestoSqlParser::UPDATE:
      case PrestoSqlParser::USE:
      case PrestoSqlParser::USER:
      case PrestoSqlParser::VALIDATE:
      case PrestoSqlParser::VERBOSE:
      case PrestoSqlParser::VERSION:
      case PrestoSqlParser::VIEW:
      case PrestoSqlParser::WORK:
      case PrestoSqlParser::WRITE:
      case PrestoSqlParser::YEAR:
      case PrestoSqlParser::ZONE:
      case PrestoSqlParser::IDENTIFIER:
      case PrestoSqlParser::DIGIT_IDENTIFIER:
      case PrestoSqlParser::QUOTED_IDENTIFIER:
      case PrestoSqlParser::BACKQUOTED_IDENTIFIER: {
        enterOuterAlt(_localctx, 4);
        setState(1972);
        qualifiedName();
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhenClauseContext
//------------------------------------------------------------------

PrestoSqlParser::WhenClauseContext::WhenClauseContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::WhenClauseContext::WHEN() {
  return getToken(PrestoSqlParser::WHEN, 0);
}

tree::TerminalNode* PrestoSqlParser::WhenClauseContext::THEN() {
  return getToken(PrestoSqlParser::THEN, 0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::WhenClauseContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::WhenClauseContext::expression(size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

size_t PrestoSqlParser::WhenClauseContext::getRuleIndex() const {
  return PrestoSqlParser::RuleWhenClause;
}

void PrestoSqlParser::WhenClauseContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterWhenClause(this);
}

void PrestoSqlParser::WhenClauseContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitWhenClause(this);
}

std::any PrestoSqlParser::WhenClauseContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitWhenClause(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::WhenClauseContext* PrestoSqlParser::whenClause() {
  WhenClauseContext* _localctx =
      _tracker.createInstance<WhenClauseContext>(_ctx, getState());
  enterRule(_localctx, 128, PrestoSqlParser::RuleWhenClause);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1975);
    match(PrestoSqlParser::WHEN);
    setState(1976);
    antlrcpp::downCast<WhenClauseContext*>(_localctx)->condition = expression();
    setState(1977);
    match(PrestoSqlParser::THEN);
    setState(1978);
    antlrcpp::downCast<WhenClauseContext*>(_localctx)->result = expression();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FilterContext
//------------------------------------------------------------------

PrestoSqlParser::FilterContext::FilterContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::FilterContext::FILTER() {
  return getToken(PrestoSqlParser::FILTER, 0);
}

tree::TerminalNode* PrestoSqlParser::FilterContext::WHERE() {
  return getToken(PrestoSqlParser::WHERE, 0);
}

PrestoSqlParser::BooleanExpressionContext*
PrestoSqlParser::FilterContext::booleanExpression() {
  return getRuleContext<PrestoSqlParser::BooleanExpressionContext>(0);
}

size_t PrestoSqlParser::FilterContext::getRuleIndex() const {
  return PrestoSqlParser::RuleFilter;
}

void PrestoSqlParser::FilterContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterFilter(this);
}

void PrestoSqlParser::FilterContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitFilter(this);
}

std::any PrestoSqlParser::FilterContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitFilter(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::FilterContext* PrestoSqlParser::filter() {
  FilterContext* _localctx =
      _tracker.createInstance<FilterContext>(_ctx, getState());
  enterRule(_localctx, 130, PrestoSqlParser::RuleFilter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1980);
    match(PrestoSqlParser::FILTER);
    setState(1981);
    match(PrestoSqlParser::T__1);
    setState(1982);
    match(PrestoSqlParser::WHERE);
    setState(1983);
    booleanExpression(0);
    setState(1984);
    match(PrestoSqlParser::T__2);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OverContext
//------------------------------------------------------------------

PrestoSqlParser::OverContext::OverContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::OverContext::OVER() {
  return getToken(PrestoSqlParser::OVER, 0);
}

tree::TerminalNode* PrestoSqlParser::OverContext::PARTITION() {
  return getToken(PrestoSqlParser::PARTITION, 0);
}

std::vector<tree::TerminalNode*> PrestoSqlParser::OverContext::BY() {
  return getTokens(PrestoSqlParser::BY);
}

tree::TerminalNode* PrestoSqlParser::OverContext::BY(size_t i) {
  return getToken(PrestoSqlParser::BY, i);
}

tree::TerminalNode* PrestoSqlParser::OverContext::ORDER() {
  return getToken(PrestoSqlParser::ORDER, 0);
}

std::vector<PrestoSqlParser::SortItemContext*>
PrestoSqlParser::OverContext::sortItem() {
  return getRuleContexts<PrestoSqlParser::SortItemContext>();
}

PrestoSqlParser::SortItemContext* PrestoSqlParser::OverContext::sortItem(
    size_t i) {
  return getRuleContext<PrestoSqlParser::SortItemContext>(i);
}

PrestoSqlParser::WindowFrameContext*
PrestoSqlParser::OverContext::windowFrame() {
  return getRuleContext<PrestoSqlParser::WindowFrameContext>(0);
}

std::vector<PrestoSqlParser::ExpressionContext*>
PrestoSqlParser::OverContext::expression() {
  return getRuleContexts<PrestoSqlParser::ExpressionContext>();
}

PrestoSqlParser::ExpressionContext* PrestoSqlParser::OverContext::expression(
    size_t i) {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(i);
}

size_t PrestoSqlParser::OverContext::getRuleIndex() const {
  return PrestoSqlParser::RuleOver;
}

void PrestoSqlParser::OverContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterOver(this);
}

void PrestoSqlParser::OverContext::exitRule(tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitOver(this);
}

std::any PrestoSqlParser::OverContext::accept(tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitOver(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::OverContext* PrestoSqlParser::over() {
  OverContext* _localctx =
      _tracker.createInstance<OverContext>(_ctx, getState());
  enterRule(_localctx, 132, PrestoSqlParser::RuleOver);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1986);
    match(PrestoSqlParser::OVER);
    setState(1987);
    match(PrestoSqlParser::T__1);
    setState(1998);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::PARTITION) {
      setState(1988);
      match(PrestoSqlParser::PARTITION);
      setState(1989);
      match(PrestoSqlParser::BY);
      setState(1990);
      antlrcpp::downCast<OverContext*>(_localctx)->expressionContext =
          expression();
      antlrcpp::downCast<OverContext*>(_localctx)->partition.push_back(
          antlrcpp::downCast<OverContext*>(_localctx)->expressionContext);
      setState(1995);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PrestoSqlParser::T__3) {
        setState(1991);
        match(PrestoSqlParser::T__3);
        setState(1992);
        antlrcpp::downCast<OverContext*>(_localctx)->expressionContext =
            expression();
        antlrcpp::downCast<OverContext*>(_localctx)->partition.push_back(
            antlrcpp::downCast<OverContext*>(_localctx)->expressionContext);
        setState(1997);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(2010);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::ORDER) {
      setState(2000);
      match(PrestoSqlParser::ORDER);
      setState(2001);
      match(PrestoSqlParser::BY);
      setState(2002);
      sortItem();
      setState(2007);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == PrestoSqlParser::T__3) {
        setState(2003);
        match(PrestoSqlParser::T__3);
        setState(2004);
        sortItem();
        setState(2009);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(2013);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == PrestoSqlParser::GROUPS || _la == PrestoSqlParser::RANGE

        || _la == PrestoSqlParser::ROWS) {
      setState(2012);
      windowFrame();
    }
    setState(2015);
    match(PrestoSqlParser::T__2);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WindowFrameContext
//------------------------------------------------------------------

PrestoSqlParser::WindowFrameContext::WindowFrameContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::WindowFrameContext::RANGE() {
  return getToken(PrestoSqlParser::RANGE, 0);
}

std::vector<PrestoSqlParser::FrameBoundContext*>
PrestoSqlParser::WindowFrameContext::frameBound() {
  return getRuleContexts<PrestoSqlParser::FrameBoundContext>();
}

PrestoSqlParser::FrameBoundContext*
PrestoSqlParser::WindowFrameContext::frameBound(size_t i) {
  return getRuleContext<PrestoSqlParser::FrameBoundContext>(i);
}

tree::TerminalNode* PrestoSqlParser::WindowFrameContext::ROWS() {
  return getToken(PrestoSqlParser::ROWS, 0);
}

tree::TerminalNode* PrestoSqlParser::WindowFrameContext::GROUPS() {
  return getToken(PrestoSqlParser::GROUPS, 0);
}

tree::TerminalNode* PrestoSqlParser::WindowFrameContext::BETWEEN() {
  return getToken(PrestoSqlParser::BETWEEN, 0);
}

tree::TerminalNode* PrestoSqlParser::WindowFrameContext::AND() {
  return getToken(PrestoSqlParser::AND, 0);
}

size_t PrestoSqlParser::WindowFrameContext::getRuleIndex() const {
  return PrestoSqlParser::RuleWindowFrame;
}

void PrestoSqlParser::WindowFrameContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterWindowFrame(this);
}

void PrestoSqlParser::WindowFrameContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitWindowFrame(this);
}

std::any PrestoSqlParser::WindowFrameContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitWindowFrame(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::WindowFrameContext* PrestoSqlParser::windowFrame() {
  WindowFrameContext* _localctx =
      _tracker.createInstance<WindowFrameContext>(_ctx, getState());
  enterRule(_localctx, 134, PrestoSqlParser::RuleWindowFrame);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2041);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 258, _ctx)) {
      case 1: {
        enterOuterAlt(_localctx, 1);
        setState(2017);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->frameType =
            match(PrestoSqlParser::RANGE);
        setState(2018);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->start =
            frameBound();
        break;
      }

      case 2: {
        enterOuterAlt(_localctx, 2);
        setState(2019);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->frameType =
            match(PrestoSqlParser::ROWS);
        setState(2020);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->start =
            frameBound();
        break;
      }

      case 3: {
        enterOuterAlt(_localctx, 3);
        setState(2021);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->frameType =
            match(PrestoSqlParser::GROUPS);
        setState(2022);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->start =
            frameBound();
        break;
      }

      case 4: {
        enterOuterAlt(_localctx, 4);
        setState(2023);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->frameType =
            match(PrestoSqlParser::RANGE);
        setState(2024);
        match(PrestoSqlParser::BETWEEN);
        setState(2025);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->start =
            frameBound();
        setState(2026);
        match(PrestoSqlParser::AND);
        setState(2027);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->end = frameBound();
        break;
      }

      case 5: {
        enterOuterAlt(_localctx, 5);
        setState(2029);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->frameType =
            match(PrestoSqlParser::ROWS);
        setState(2030);
        match(PrestoSqlParser::BETWEEN);
        setState(2031);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->start =
            frameBound();
        setState(2032);
        match(PrestoSqlParser::AND);
        setState(2033);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->end = frameBound();
        break;
      }

      case 6: {
        enterOuterAlt(_localctx, 6);
        setState(2035);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->frameType =
            match(PrestoSqlParser::GROUPS);
        setState(2036);
        match(PrestoSqlParser::BETWEEN);
        setState(2037);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->start =
            frameBound();
        setState(2038);
        match(PrestoSqlParser::AND);
        setState(2039);
        antlrcpp::downCast<WindowFrameContext*>(_localctx)->end = frameBound();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FrameBoundContext
//------------------------------------------------------------------

PrestoSqlParser::FrameBoundContext::FrameBoundContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::FrameBoundContext::getRuleIndex() const {
  return PrestoSqlParser::RuleFrameBound;
}

void PrestoSqlParser::FrameBoundContext::copyFrom(FrameBoundContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BoundedFrameContext
//------------------------------------------------------------------

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::BoundedFrameContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::BoundedFrameContext::PRECEDING() {
  return getToken(PrestoSqlParser::PRECEDING, 0);
}

tree::TerminalNode* PrestoSqlParser::BoundedFrameContext::FOLLOWING() {
  return getToken(PrestoSqlParser::FOLLOWING, 0);
}

PrestoSqlParser::BoundedFrameContext::BoundedFrameContext(
    FrameBoundContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::BoundedFrameContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoundedFrame(this);
}
void PrestoSqlParser::BoundedFrameContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoundedFrame(this);
}

std::any PrestoSqlParser::BoundedFrameContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitBoundedFrame(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnboundedFrameContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::UnboundedFrameContext::UNBOUNDED() {
  return getToken(PrestoSqlParser::UNBOUNDED, 0);
}

tree::TerminalNode* PrestoSqlParser::UnboundedFrameContext::PRECEDING() {
  return getToken(PrestoSqlParser::PRECEDING, 0);
}

tree::TerminalNode* PrestoSqlParser::UnboundedFrameContext::FOLLOWING() {
  return getToken(PrestoSqlParser::FOLLOWING, 0);
}

PrestoSqlParser::UnboundedFrameContext::UnboundedFrameContext(
    FrameBoundContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::UnboundedFrameContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnboundedFrame(this);
}
void PrestoSqlParser::UnboundedFrameContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnboundedFrame(this);
}

std::any PrestoSqlParser::UnboundedFrameContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUnboundedFrame(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CurrentRowBoundContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CurrentRowBoundContext::CURRENT() {
  return getToken(PrestoSqlParser::CURRENT, 0);
}

tree::TerminalNode* PrestoSqlParser::CurrentRowBoundContext::ROW() {
  return getToken(PrestoSqlParser::ROW, 0);
}

PrestoSqlParser::CurrentRowBoundContext::CurrentRowBoundContext(
    FrameBoundContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CurrentRowBoundContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCurrentRowBound(this);
}
void PrestoSqlParser::CurrentRowBoundContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCurrentRowBound(this);
}

std::any PrestoSqlParser::CurrentRowBoundContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCurrentRowBound(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::FrameBoundContext* PrestoSqlParser::frameBound() {
  FrameBoundContext* _localctx =
      _tracker.createInstance<FrameBoundContext>(_ctx, getState());
  enterRule(_localctx, 136, PrestoSqlParser::RuleFrameBound);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2052);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 259, _ctx)) {
      case 1: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UnboundedFrameContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2043);
        match(PrestoSqlParser::UNBOUNDED);
        setState(2044);
        antlrcpp::downCast<UnboundedFrameContext*>(_localctx)->boundType =
            match(PrestoSqlParser::PRECEDING);
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UnboundedFrameContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2045);
        match(PrestoSqlParser::UNBOUNDED);
        setState(2046);
        antlrcpp::downCast<UnboundedFrameContext*>(_localctx)->boundType =
            match(PrestoSqlParser::FOLLOWING);
        break;
      }

      case 3: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CurrentRowBoundContext>(
                _localctx);
        enterOuterAlt(_localctx, 3);
        setState(2047);
        match(PrestoSqlParser::CURRENT);
        setState(2048);
        match(PrestoSqlParser::ROW);
        break;
      }

      case 4: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::BoundedFrameContext>(
                _localctx);
        enterOuterAlt(_localctx, 4);
        setState(2049);
        expression();
        setState(2050);
        antlrcpp::downCast<BoundedFrameContext*>(_localctx)->boundType =
            _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == PrestoSqlParser::FOLLOWING ||
              _la == PrestoSqlParser::PRECEDING)) {
          antlrcpp::downCast<BoundedFrameContext*>(_localctx)->boundType =
              _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UpdateAssignmentContext
//------------------------------------------------------------------

PrestoSqlParser::UpdateAssignmentContext::UpdateAssignmentContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::UpdateAssignmentContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

tree::TerminalNode* PrestoSqlParser::UpdateAssignmentContext::EQ() {
  return getToken(PrestoSqlParser::EQ, 0);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::UpdateAssignmentContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

size_t PrestoSqlParser::UpdateAssignmentContext::getRuleIndex() const {
  return PrestoSqlParser::RuleUpdateAssignment;
}

void PrestoSqlParser::UpdateAssignmentContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUpdateAssignment(this);
}

void PrestoSqlParser::UpdateAssignmentContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUpdateAssignment(this);
}

std::any PrestoSqlParser::UpdateAssignmentContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUpdateAssignment(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::UpdateAssignmentContext* PrestoSqlParser::updateAssignment() {
  UpdateAssignmentContext* _localctx =
      _tracker.createInstance<UpdateAssignmentContext>(_ctx, getState());
  enterRule(_localctx, 138, PrestoSqlParser::RuleUpdateAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2054);
    identifier();
    setState(2055);
    match(PrestoSqlParser::EQ);
    setState(2056);
    expression();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExplainOptionContext
//------------------------------------------------------------------

PrestoSqlParser::ExplainOptionContext::ExplainOptionContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::ExplainOptionContext::getRuleIndex() const {
  return PrestoSqlParser::RuleExplainOption;
}

void PrestoSqlParser::ExplainOptionContext::copyFrom(
    ExplainOptionContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ExplainFormatContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ExplainFormatContext::FORMAT() {
  return getToken(PrestoSqlParser::FORMAT, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainFormatContext::TEXT() {
  return getToken(PrestoSqlParser::TEXT, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainFormatContext::GRAPHVIZ() {
  return getToken(PrestoSqlParser::GRAPHVIZ, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainFormatContext::JSON() {
  return getToken(PrestoSqlParser::JSON, 0);
}

PrestoSqlParser::ExplainFormatContext::ExplainFormatContext(
    ExplainOptionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ExplainFormatContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplainFormat(this);
}
void PrestoSqlParser::ExplainFormatContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplainFormat(this);
}

std::any PrestoSqlParser::ExplainFormatContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExplainFormat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExplainTypeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ExplainTypeContext::TYPE() {
  return getToken(PrestoSqlParser::TYPE, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainTypeContext::LOGICAL() {
  return getToken(PrestoSqlParser::LOGICAL, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainTypeContext::GRAPH() {
  return getToken(PrestoSqlParser::GRAPH, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainTypeContext::OPTIMIZED() {
  return getToken(PrestoSqlParser::OPTIMIZED, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainTypeContext::EXECUTABLE() {
  return getToken(PrestoSqlParser::EXECUTABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainTypeContext::DISTRIBUTED() {
  return getToken(PrestoSqlParser::DISTRIBUTED, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainTypeContext::VALIDATE() {
  return getToken(PrestoSqlParser::VALIDATE, 0);
}

tree::TerminalNode* PrestoSqlParser::ExplainTypeContext::IO() {
  return getToken(PrestoSqlParser::IO, 0);
}

PrestoSqlParser::ExplainTypeContext::ExplainTypeContext(
    ExplainOptionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ExplainTypeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterExplainType(this);
}
void PrestoSqlParser::ExplainTypeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitExplainType(this);
}

std::any PrestoSqlParser::ExplainTypeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitExplainType(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::ExplainOptionContext* PrestoSqlParser::explainOption() {
  ExplainOptionContext* _localctx =
      _tracker.createInstance<ExplainOptionContext>(_ctx, getState());
  enterRule(_localctx, 140, PrestoSqlParser::RuleExplainOption);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2062);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::FORMAT: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ExplainFormatContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2058);
        match(PrestoSqlParser::FORMAT);
        setState(2059);
        antlrcpp::downCast<ExplainFormatContext*>(_localctx)->value =
            _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == PrestoSqlParser::GRAPHVIZ

              || _la == PrestoSqlParser::JSON ||
              _la == PrestoSqlParser::TEXT)) {
          antlrcpp::downCast<ExplainFormatContext*>(_localctx)->value =
              _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      case PrestoSqlParser::TYPE: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ExplainTypeContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2060);
        match(PrestoSqlParser::TYPE);
        setState(2061);
        antlrcpp::downCast<ExplainTypeContext*>(_localctx)->value =
            _input->LT(1);
        _la = _input->LA(1);
        if (!(((((_la - 58) & ~0x3fULL) == 0) &&
               ((1ULL << (_la - 58)) & -9223090560804322303) != 0) ||
              _la == PrestoSqlParser::OPTIMIZED ||
              _la == PrestoSqlParser::VALIDATE)) {
          antlrcpp::downCast<ExplainTypeContext*>(_localctx)->value =
              _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TransactionModeContext
//------------------------------------------------------------------

PrestoSqlParser::TransactionModeContext::TransactionModeContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::TransactionModeContext::getRuleIndex() const {
  return PrestoSqlParser::RuleTransactionMode;
}

void PrestoSqlParser::TransactionModeContext::copyFrom(
    TransactionModeContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TransactionAccessModeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::TransactionAccessModeContext::READ() {
  return getToken(PrestoSqlParser::READ, 0);
}

tree::TerminalNode* PrestoSqlParser::TransactionAccessModeContext::ONLY() {
  return getToken(PrestoSqlParser::ONLY, 0);
}

tree::TerminalNode* PrestoSqlParser::TransactionAccessModeContext::WRITE() {
  return getToken(PrestoSqlParser::WRITE, 0);
}

PrestoSqlParser::TransactionAccessModeContext::TransactionAccessModeContext(
    TransactionModeContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TransactionAccessModeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTransactionAccessMode(this);
}
void PrestoSqlParser::TransactionAccessModeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTransactionAccessMode(this);
}

std::any PrestoSqlParser::TransactionAccessModeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTransactionAccessMode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IsolationLevelContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::IsolationLevelContext::ISOLATION() {
  return getToken(PrestoSqlParser::ISOLATION, 0);
}

tree::TerminalNode* PrestoSqlParser::IsolationLevelContext::LEVEL() {
  return getToken(PrestoSqlParser::LEVEL, 0);
}

PrestoSqlParser::LevelOfIsolationContext*
PrestoSqlParser::IsolationLevelContext::levelOfIsolation() {
  return getRuleContext<PrestoSqlParser::LevelOfIsolationContext>(0);
}

PrestoSqlParser::IsolationLevelContext::IsolationLevelContext(
    TransactionModeContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::IsolationLevelContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterIsolationLevel(this);
}
void PrestoSqlParser::IsolationLevelContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitIsolationLevel(this);
}

std::any PrestoSqlParser::IsolationLevelContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitIsolationLevel(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::TransactionModeContext* PrestoSqlParser::transactionMode() {
  TransactionModeContext* _localctx =
      _tracker.createInstance<TransactionModeContext>(_ctx, getState());
  enterRule(_localctx, 142, PrestoSqlParser::RuleTransactionMode);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2069);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::ISOLATION: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::IsolationLevelContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2064);
        match(PrestoSqlParser::ISOLATION);
        setState(2065);
        match(PrestoSqlParser::LEVEL);
        setState(2066);
        levelOfIsolation();
        break;
      }

      case PrestoSqlParser::READ: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::TransactionAccessModeContext>(
                    _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2067);
        match(PrestoSqlParser::READ);
        setState(2068);
        antlrcpp::downCast<TransactionAccessModeContext*>(_localctx)
            ->accessMode = _input->LT(1);
        _la = _input->LA(1);
        if (!(_la == PrestoSqlParser::ONLY || _la == PrestoSqlParser::WRITE)) {
          antlrcpp::downCast<TransactionAccessModeContext*>(_localctx)
              ->accessMode = _errHandler->recoverInline(this);
        } else {
          _errHandler->reportMatch(this);
          consume();
        }
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LevelOfIsolationContext
//------------------------------------------------------------------

PrestoSqlParser::LevelOfIsolationContext::LevelOfIsolationContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::LevelOfIsolationContext::getRuleIndex() const {
  return PrestoSqlParser::RuleLevelOfIsolation;
}

void PrestoSqlParser::LevelOfIsolationContext::copyFrom(
    LevelOfIsolationContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ReadUncommittedContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ReadUncommittedContext::READ() {
  return getToken(PrestoSqlParser::READ, 0);
}

tree::TerminalNode* PrestoSqlParser::ReadUncommittedContext::UNCOMMITTED() {
  return getToken(PrestoSqlParser::UNCOMMITTED, 0);
}

PrestoSqlParser::ReadUncommittedContext::ReadUncommittedContext(
    LevelOfIsolationContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ReadUncommittedContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterReadUncommitted(this);
}
void PrestoSqlParser::ReadUncommittedContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitReadUncommitted(this);
}

std::any PrestoSqlParser::ReadUncommittedContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitReadUncommitted(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SerializableContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::SerializableContext::SERIALIZABLE() {
  return getToken(PrestoSqlParser::SERIALIZABLE, 0);
}

PrestoSqlParser::SerializableContext::SerializableContext(
    LevelOfIsolationContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SerializableContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSerializable(this);
}
void PrestoSqlParser::SerializableContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSerializable(this);
}

std::any PrestoSqlParser::SerializableContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSerializable(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ReadCommittedContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::ReadCommittedContext::READ() {
  return getToken(PrestoSqlParser::READ, 0);
}

tree::TerminalNode* PrestoSqlParser::ReadCommittedContext::COMMITTED() {
  return getToken(PrestoSqlParser::COMMITTED, 0);
}

PrestoSqlParser::ReadCommittedContext::ReadCommittedContext(
    LevelOfIsolationContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::ReadCommittedContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterReadCommitted(this);
}
void PrestoSqlParser::ReadCommittedContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitReadCommitted(this);
}

std::any PrestoSqlParser::ReadCommittedContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitReadCommitted(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RepeatableReadContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RepeatableReadContext::REPEATABLE() {
  return getToken(PrestoSqlParser::REPEATABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::RepeatableReadContext::READ() {
  return getToken(PrestoSqlParser::READ, 0);
}

PrestoSqlParser::RepeatableReadContext::RepeatableReadContext(
    LevelOfIsolationContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RepeatableReadContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRepeatableRead(this);
}
void PrestoSqlParser::RepeatableReadContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRepeatableRead(this);
}

std::any PrestoSqlParser::RepeatableReadContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRepeatableRead(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::LevelOfIsolationContext* PrestoSqlParser::levelOfIsolation() {
  LevelOfIsolationContext* _localctx =
      _tracker.createInstance<LevelOfIsolationContext>(_ctx, getState());
  enterRule(_localctx, 144, PrestoSqlParser::RuleLevelOfIsolation);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2078);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 262, _ctx)) {
      case 1: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ReadUncommittedContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2071);
        match(PrestoSqlParser::READ);
        setState(2072);
        match(PrestoSqlParser::UNCOMMITTED);
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::ReadCommittedContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2073);
        match(PrestoSqlParser::READ);
        setState(2074);
        match(PrestoSqlParser::COMMITTED);
        break;
      }

      case 3: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::RepeatableReadContext>(
                _localctx);
        enterOuterAlt(_localctx, 3);
        setState(2075);
        match(PrestoSqlParser::REPEATABLE);
        setState(2076);
        match(PrestoSqlParser::READ);
        break;
      }

      case 4: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SerializableContext>(
                _localctx);
        enterOuterAlt(_localctx, 4);
        setState(2077);
        match(PrestoSqlParser::SERIALIZABLE);
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallArgumentContext
//------------------------------------------------------------------

PrestoSqlParser::CallArgumentContext::CallArgumentContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::CallArgumentContext::getRuleIndex() const {
  return PrestoSqlParser::RuleCallArgument;
}

void PrestoSqlParser::CallArgumentContext::copyFrom(CallArgumentContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PositionalArgumentContext
//------------------------------------------------------------------

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::PositionalArgumentContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

PrestoSqlParser::PositionalArgumentContext::PositionalArgumentContext(
    CallArgumentContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::PositionalArgumentContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterPositionalArgument(this);
}
void PrestoSqlParser::PositionalArgumentContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitPositionalArgument(this);
}

std::any PrestoSqlParser::PositionalArgumentContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitPositionalArgument(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NamedArgumentContext
//------------------------------------------------------------------

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::NamedArgumentContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::ExpressionContext*
PrestoSqlParser::NamedArgumentContext::expression() {
  return getRuleContext<PrestoSqlParser::ExpressionContext>(0);
}

PrestoSqlParser::NamedArgumentContext::NamedArgumentContext(
    CallArgumentContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::NamedArgumentContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamedArgument(this);
}
void PrestoSqlParser::NamedArgumentContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamedArgument(this);
}

std::any PrestoSqlParser::NamedArgumentContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNamedArgument(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::CallArgumentContext* PrestoSqlParser::callArgument() {
  CallArgumentContext* _localctx =
      _tracker.createInstance<CallArgumentContext>(_ctx, getState());
  enterRule(_localctx, 146, PrestoSqlParser::RuleCallArgument);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2085);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 263, _ctx)) {
      case 1: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::PositionalArgumentContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2080);
        expression();
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::NamedArgumentContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2081);
        identifier();
        setState(2082);
        match(PrestoSqlParser::T__8);
        setState(2083);
        expression();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrivilegeContext
//------------------------------------------------------------------

PrestoSqlParser::PrivilegeContext::PrivilegeContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::PrivilegeContext::SELECT() {
  return getToken(PrestoSqlParser::SELECT, 0);
}

tree::TerminalNode* PrestoSqlParser::PrivilegeContext::DELETE() {
  return getToken(PrestoSqlParser::DELETE, 0);
}

tree::TerminalNode* PrestoSqlParser::PrivilegeContext::INSERT() {
  return getToken(PrestoSqlParser::INSERT, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::PrivilegeContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

size_t PrestoSqlParser::PrivilegeContext::getRuleIndex() const {
  return PrestoSqlParser::RulePrivilege;
}

void PrestoSqlParser::PrivilegeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterPrivilege(this);
}

void PrestoSqlParser::PrivilegeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitPrivilege(this);
}

std::any PrestoSqlParser::PrivilegeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitPrivilege(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::PrivilegeContext* PrestoSqlParser::privilege() {
  PrivilegeContext* _localctx =
      _tracker.createInstance<PrivilegeContext>(_ctx, getState());
  enterRule(_localctx, 148, PrestoSqlParser::RulePrivilege);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2091);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::SELECT: {
        enterOuterAlt(_localctx, 1);
        setState(2087);
        match(PrestoSqlParser::SELECT);
        break;
      }

      case PrestoSqlParser::DELETE: {
        enterOuterAlt(_localctx, 2);
        setState(2088);
        match(PrestoSqlParser::DELETE);
        break;
      }

      case PrestoSqlParser::INSERT: {
        enterOuterAlt(_localctx, 3);
        setState(2089);
        match(PrestoSqlParser::INSERT);
        break;
      }

      case PrestoSqlParser::ADD:
      case PrestoSqlParser::ADMIN:
      case PrestoSqlParser::ALL:
      case PrestoSqlParser::ANALYZE:
      case PrestoSqlParser::ANY:
      case PrestoSqlParser::ARRAY:
      case PrestoSqlParser::ASC:
      case PrestoSqlParser::AT:
      case PrestoSqlParser::BEFORE:
      case PrestoSqlParser::BERNOULLI:
      case PrestoSqlParser::CALL:
      case PrestoSqlParser::CALLED:
      case PrestoSqlParser::CASCADE:
      case PrestoSqlParser::CATALOGS:
      case PrestoSqlParser::COLUMN:
      case PrestoSqlParser::COLUMNS:
      case PrestoSqlParser::COMMENT:
      case PrestoSqlParser::COMMIT:
      case PrestoSqlParser::COMMITTED:
      case PrestoSqlParser::CURRENT:
      case PrestoSqlParser::CURRENT_ROLE:
      case PrestoSqlParser::DATA:
      case PrestoSqlParser::DATE:
      case PrestoSqlParser::DAY:
      case PrestoSqlParser::DEFINER:
      case PrestoSqlParser::DESC:
      case PrestoSqlParser::DETERMINISTIC:
      case PrestoSqlParser::DISABLED:
      case PrestoSqlParser::DISTRIBUTED:
      case PrestoSqlParser::ENABLED:
      case PrestoSqlParser::ENFORCED:
      case PrestoSqlParser::EXCLUDE:
      case PrestoSqlParser::EXCLUDING:
      case PrestoSqlParser::EXECUTABLE:
      case PrestoSqlParser::EXPLAIN:
      case PrestoSqlParser::EXTERNAL:
      case PrestoSqlParser::FETCH:
      case PrestoSqlParser::FILTER:
      case PrestoSqlParser::FIRST:
      case PrestoSqlParser::FOLLOWING:
      case PrestoSqlParser::FORMAT:
      case PrestoSqlParser::FUNCTION:
      case PrestoSqlParser::FUNCTIONS:
      case PrestoSqlParser::GRANT:
      case PrestoSqlParser::GRANTED:
      case PrestoSqlParser::GRANTS:
      case PrestoSqlParser::GRAPH:
      case PrestoSqlParser::GRAPHVIZ:
      case PrestoSqlParser::GROUPS:
      case PrestoSqlParser::HOUR:
      case PrestoSqlParser::IF:
      case PrestoSqlParser::IGNORE:
      case PrestoSqlParser::INCLUDING:
      case PrestoSqlParser::INPUT:
      case PrestoSqlParser::INTERVAL:
      case PrestoSqlParser::INVOKER:
      case PrestoSqlParser::IO:
      case PrestoSqlParser::ISOLATION:
      case PrestoSqlParser::JSON:
      case PrestoSqlParser::KEY:
      case PrestoSqlParser::LANGUAGE:
      case PrestoSqlParser::LAST:
      case PrestoSqlParser::LATERAL:
      case PrestoSqlParser::LEVEL:
      case PrestoSqlParser::LIMIT:
      case PrestoSqlParser::LOGICAL:
      case PrestoSqlParser::MAP:
      case PrestoSqlParser::MATERIALIZED:
      case PrestoSqlParser::MINUTE:
      case PrestoSqlParser::MONTH:
      case PrestoSqlParser::NAME:
      case PrestoSqlParser::NFC:
      case PrestoSqlParser::NFD:
      case PrestoSqlParser::NFKC:
      case PrestoSqlParser::NFKD:
      case PrestoSqlParser::NO:
      case PrestoSqlParser::NONE:
      case PrestoSqlParser::NULLIF:
      case PrestoSqlParser::NULLS:
      case PrestoSqlParser::OF:
      case PrestoSqlParser::OFFSET:
      case PrestoSqlParser::ONLY:
      case PrestoSqlParser::OPTIMIZED:
      case PrestoSqlParser::OPTION:
      case PrestoSqlParser::ORDINALITY:
      case PrestoSqlParser::OUTPUT:
      case PrestoSqlParser::OVER:
      case PrestoSqlParser::PARTITION:
      case PrestoSqlParser::PARTITIONS:
      case PrestoSqlParser::POSITION:
      case PrestoSqlParser::PRECEDING:
      case PrestoSqlParser::PRIMARY:
      case PrestoSqlParser::PRIVILEGES:
      case PrestoSqlParser::PROPERTIES:
      case PrestoSqlParser::RANGE:
      case PrestoSqlParser::READ:
      case PrestoSqlParser::REFRESH:
      case PrestoSqlParser::RELY:
      case PrestoSqlParser::RENAME:
      case PrestoSqlParser::REPEATABLE:
      case PrestoSqlParser::REPLACE:
      case PrestoSqlParser::RESET:
      case PrestoSqlParser::RESPECT:
      case PrestoSqlParser::RESTRICT:
      case PrestoSqlParser::RETURN:
      case PrestoSqlParser::RETURNS:
      case PrestoSqlParser::REVOKE:
      case PrestoSqlParser::ROLE:
      case PrestoSqlParser::ROLES:
      case PrestoSqlParser::ROLLBACK:
      case PrestoSqlParser::ROW:
      case PrestoSqlParser::ROWS:
      case PrestoSqlParser::SCHEMA:
      case PrestoSqlParser::SCHEMAS:
      case PrestoSqlParser::SECOND:
      case PrestoSqlParser::SECURITY:
      case PrestoSqlParser::SERIALIZABLE:
      case PrestoSqlParser::SESSION:
      case PrestoSqlParser::SET:
      case PrestoSqlParser::SETS:
      case PrestoSqlParser::SHOW:
      case PrestoSqlParser::SOME:
      case PrestoSqlParser::SQL:
      case PrestoSqlParser::START:
      case PrestoSqlParser::STATS:
      case PrestoSqlParser::SUBSTRING:
      case PrestoSqlParser::SYSTEM:
      case PrestoSqlParser::SYSTEM_TIME:
      case PrestoSqlParser::SYSTEM_VERSION:
      case PrestoSqlParser::TABLES:
      case PrestoSqlParser::TABLESAMPLE:
      case PrestoSqlParser::TEMPORARY:
      case PrestoSqlParser::TEXT:
      case PrestoSqlParser::TIME:
      case PrestoSqlParser::TIMESTAMP:
      case PrestoSqlParser::TO:
      case PrestoSqlParser::TRANSACTION:
      case PrestoSqlParser::TRUNCATE:
      case PrestoSqlParser::TRY_CAST:
      case PrestoSqlParser::TYPE:
      case PrestoSqlParser::UNBOUNDED:
      case PrestoSqlParser::UNCOMMITTED:
      case PrestoSqlParser::UNIQUE:
      case PrestoSqlParser::UPDATE:
      case PrestoSqlParser::USE:
      case PrestoSqlParser::USER:
      case PrestoSqlParser::VALIDATE:
      case PrestoSqlParser::VERBOSE:
      case PrestoSqlParser::VERSION:
      case PrestoSqlParser::VIEW:
      case PrestoSqlParser::WORK:
      case PrestoSqlParser::WRITE:
      case PrestoSqlParser::YEAR:
      case PrestoSqlParser::ZONE:
      case PrestoSqlParser::IDENTIFIER:
      case PrestoSqlParser::DIGIT_IDENTIFIER:
      case PrestoSqlParser::QUOTED_IDENTIFIER:
      case PrestoSqlParser::BACKQUOTED_IDENTIFIER: {
        enterOuterAlt(_localctx, 4);
        setState(2090);
        identifier();
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- QualifiedNameContext
//------------------------------------------------------------------

PrestoSqlParser::QualifiedNameContext::QualifiedNameContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::QualifiedNameContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::QualifiedNameContext::identifier(size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

size_t PrestoSqlParser::QualifiedNameContext::getRuleIndex() const {
  return PrestoSqlParser::RuleQualifiedName;
}

void PrestoSqlParser::QualifiedNameContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterQualifiedName(this);
}

void PrestoSqlParser::QualifiedNameContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitQualifiedName(this);
}

std::any PrestoSqlParser::QualifiedNameContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitQualifiedName(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::QualifiedNameContext* PrestoSqlParser::qualifiedName() {
  QualifiedNameContext* _localctx =
      _tracker.createInstance<QualifiedNameContext>(_ctx, getState());
  enterRule(_localctx, 150, PrestoSqlParser::RuleQualifiedName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(2093);
    identifier();
    setState(2098);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 265, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(2094);
        match(PrestoSqlParser::T__0);
        setState(2095);
        identifier();
      }
      setState(2100);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
          _input, 265, _ctx);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableVersionExpressionContext
//------------------------------------------------------------------

PrestoSqlParser::TableVersionExpressionContext::TableVersionExpressionContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::TableVersionExpressionContext::getRuleIndex() const {
  return PrestoSqlParser::RuleTableVersionExpression;
}

void PrestoSqlParser::TableVersionExpressionContext::copyFrom(
    TableVersionExpressionContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TableVersionContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::TableVersionContext::FOR() {
  return getToken(PrestoSqlParser::FOR, 0);
}

PrestoSqlParser::TableVersionStateContext*
PrestoSqlParser::TableVersionContext::tableVersionState() {
  return getRuleContext<PrestoSqlParser::TableVersionStateContext>(0);
}

PrestoSqlParser::ValueExpressionContext*
PrestoSqlParser::TableVersionContext::valueExpression() {
  return getRuleContext<PrestoSqlParser::ValueExpressionContext>(0);
}

tree::TerminalNode* PrestoSqlParser::TableVersionContext::SYSTEM_TIME() {
  return getToken(PrestoSqlParser::SYSTEM_TIME, 0);
}

tree::TerminalNode* PrestoSqlParser::TableVersionContext::SYSTEM_VERSION() {
  return getToken(PrestoSqlParser::SYSTEM_VERSION, 0);
}

tree::TerminalNode* PrestoSqlParser::TableVersionContext::TIMESTAMP() {
  return getToken(PrestoSqlParser::TIMESTAMP, 0);
}

tree::TerminalNode* PrestoSqlParser::TableVersionContext::VERSION() {
  return getToken(PrestoSqlParser::VERSION, 0);
}

PrestoSqlParser::TableVersionContext::TableVersionContext(
    TableVersionExpressionContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TableVersionContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTableVersion(this);
}
void PrestoSqlParser::TableVersionContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTableVersion(this);
}

std::any PrestoSqlParser::TableVersionContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTableVersion(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::TableVersionExpressionContext*
PrestoSqlParser::tableVersionExpression() {
  TableVersionExpressionContext* _localctx =
      _tracker.createInstance<TableVersionExpressionContext>(_ctx, getState());
  enterRule(_localctx, 152, PrestoSqlParser::RuleTableVersionExpression);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<PrestoSqlParser::TableVersionContext>(
        _localctx);
    enterOuterAlt(_localctx, 1);
    setState(2101);
    match(PrestoSqlParser::FOR);
    setState(2102);
    antlrcpp::downCast<TableVersionContext*>(_localctx)->tableVersionType =
        _input->LT(1);
    _la = _input->LA(1);
    if (!(((((_la - 196) & ~0x3fULL) == 0) &&
           ((1ULL << (_la - 196)) & 536871427) != 0))) {
      antlrcpp::downCast<TableVersionContext*>(_localctx)->tableVersionType =
          _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(2103);
    tableVersionState();
    setState(2104);
    valueExpression(0);

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TableVersionStateContext
//------------------------------------------------------------------

PrestoSqlParser::TableVersionStateContext::TableVersionStateContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::TableVersionStateContext::getRuleIndex() const {
  return PrestoSqlParser::RuleTableVersionState;
}

void PrestoSqlParser::TableVersionStateContext::copyFrom(
    TableVersionStateContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- TableversionbeforeContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::TableversionbeforeContext::BEFORE() {
  return getToken(PrestoSqlParser::BEFORE, 0);
}

PrestoSqlParser::TableversionbeforeContext::TableversionbeforeContext(
    TableVersionStateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TableversionbeforeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTableversionbefore(this);
}
void PrestoSqlParser::TableversionbeforeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTableversionbefore(this);
}

std::any PrestoSqlParser::TableversionbeforeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTableversionbefore(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TableversionasofContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::TableversionasofContext::AS() {
  return getToken(PrestoSqlParser::AS, 0);
}

tree::TerminalNode* PrestoSqlParser::TableversionasofContext::OF() {
  return getToken(PrestoSqlParser::OF, 0);
}

PrestoSqlParser::TableversionasofContext::TableversionasofContext(
    TableVersionStateContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::TableversionasofContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterTableversionasof(this);
}
void PrestoSqlParser::TableversionasofContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitTableversionasof(this);
}

std::any PrestoSqlParser::TableversionasofContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitTableversionasof(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::TableVersionStateContext*
PrestoSqlParser::tableVersionState() {
  TableVersionStateContext* _localctx =
      _tracker.createInstance<TableVersionStateContext>(_ctx, getState());
  enterRule(_localctx, 154, PrestoSqlParser::RuleTableVersionState);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2109);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::AS: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::TableversionasofContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2106);
        match(PrestoSqlParser::AS);
        setState(2107);
        match(PrestoSqlParser::OF);
        break;
      }

      case PrestoSqlParser::BEFORE: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::TableversionbeforeContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2108);
        match(PrestoSqlParser::BEFORE);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- GrantorContext
//------------------------------------------------------------------

PrestoSqlParser::GrantorContext::GrantorContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::GrantorContext::getRuleIndex() const {
  return PrestoSqlParser::RuleGrantor;
}

void PrestoSqlParser::GrantorContext::copyFrom(GrantorContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- CurrentUserGrantorContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CurrentUserGrantorContext::CURRENT_USER() {
  return getToken(PrestoSqlParser::CURRENT_USER, 0);
}

PrestoSqlParser::CurrentUserGrantorContext::CurrentUserGrantorContext(
    GrantorContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CurrentUserGrantorContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCurrentUserGrantor(this);
}
void PrestoSqlParser::CurrentUserGrantorContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCurrentUserGrantor(this);
}

std::any PrestoSqlParser::CurrentUserGrantorContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCurrentUserGrantor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SpecifiedPrincipalContext
//------------------------------------------------------------------

PrestoSqlParser::PrincipalContext*
PrestoSqlParser::SpecifiedPrincipalContext::principal() {
  return getRuleContext<PrestoSqlParser::PrincipalContext>(0);
}

PrestoSqlParser::SpecifiedPrincipalContext::SpecifiedPrincipalContext(
    GrantorContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::SpecifiedPrincipalContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterSpecifiedPrincipal(this);
}
void PrestoSqlParser::SpecifiedPrincipalContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitSpecifiedPrincipal(this);
}

std::any PrestoSqlParser::SpecifiedPrincipalContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitSpecifiedPrincipal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CurrentRoleGrantorContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::CurrentRoleGrantorContext::CURRENT_ROLE() {
  return getToken(PrestoSqlParser::CURRENT_ROLE, 0);
}

PrestoSqlParser::CurrentRoleGrantorContext::CurrentRoleGrantorContext(
    GrantorContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::CurrentRoleGrantorContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterCurrentRoleGrantor(this);
}
void PrestoSqlParser::CurrentRoleGrantorContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitCurrentRoleGrantor(this);
}

std::any PrestoSqlParser::CurrentRoleGrantorContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitCurrentRoleGrantor(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::GrantorContext* PrestoSqlParser::grantor() {
  GrantorContext* _localctx =
      _tracker.createInstance<GrantorContext>(_ctx, getState());
  enterRule(_localctx, 156, PrestoSqlParser::RuleGrantor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2114);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 267, _ctx)) {
      case 1: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CurrentUserGrantorContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2111);
        match(PrestoSqlParser::CURRENT_USER);
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::CurrentRoleGrantorContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2112);
        match(PrestoSqlParser::CURRENT_ROLE);
        break;
      }

      case 3: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::SpecifiedPrincipalContext>(
                _localctx);
        enterOuterAlt(_localctx, 3);
        setState(2113);
        principal();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrincipalContext
//------------------------------------------------------------------

PrestoSqlParser::PrincipalContext::PrincipalContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::PrincipalContext::getRuleIndex() const {
  return PrestoSqlParser::RulePrincipal;
}

void PrestoSqlParser::PrincipalContext::copyFrom(PrincipalContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- UnspecifiedPrincipalContext
//------------------------------------------------------------------

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::UnspecifiedPrincipalContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::UnspecifiedPrincipalContext::UnspecifiedPrincipalContext(
    PrincipalContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::UnspecifiedPrincipalContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnspecifiedPrincipal(this);
}
void PrestoSqlParser::UnspecifiedPrincipalContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnspecifiedPrincipal(this);
}

std::any PrestoSqlParser::UnspecifiedPrincipalContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUnspecifiedPrincipal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UserPrincipalContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::UserPrincipalContext::USER() {
  return getToken(PrestoSqlParser::USER, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::UserPrincipalContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::UserPrincipalContext::UserPrincipalContext(
    PrincipalContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::UserPrincipalContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUserPrincipal(this);
}
void PrestoSqlParser::UserPrincipalContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUserPrincipal(this);
}

std::any PrestoSqlParser::UserPrincipalContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUserPrincipal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- RolePrincipalContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::RolePrincipalContext::ROLE() {
  return getToken(PrestoSqlParser::ROLE, 0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::RolePrincipalContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

PrestoSqlParser::RolePrincipalContext::RolePrincipalContext(
    PrincipalContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::RolePrincipalContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRolePrincipal(this);
}
void PrestoSqlParser::RolePrincipalContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRolePrincipal(this);
}

std::any PrestoSqlParser::RolePrincipalContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRolePrincipal(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::PrincipalContext* PrestoSqlParser::principal() {
  PrincipalContext* _localctx =
      _tracker.createInstance<PrincipalContext>(_ctx, getState());
  enterRule(_localctx, 158, PrestoSqlParser::RulePrincipal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2121);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 268, _ctx)) {
      case 1: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UserPrincipalContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2116);
        match(PrestoSqlParser::USER);
        setState(2117);
        identifier();
        break;
      }

      case 2: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::RolePrincipalContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2118);
        match(PrestoSqlParser::ROLE);
        setState(2119);
        identifier();
        break;
      }

      case 3: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::UnspecifiedPrincipalContext>(
                    _localctx);
        enterOuterAlt(_localctx, 3);
        setState(2120);
        identifier();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RolesContext
//------------------------------------------------------------------

PrestoSqlParser::RolesContext::RolesContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::IdentifierContext*>
PrestoSqlParser::RolesContext::identifier() {
  return getRuleContexts<PrestoSqlParser::IdentifierContext>();
}

PrestoSqlParser::IdentifierContext* PrestoSqlParser::RolesContext::identifier(
    size_t i) {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(i);
}

size_t PrestoSqlParser::RolesContext::getRuleIndex() const {
  return PrestoSqlParser::RuleRoles;
}

void PrestoSqlParser::RolesContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterRoles(this);
}

void PrestoSqlParser::RolesContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitRoles(this);
}

std::any PrestoSqlParser::RolesContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitRoles(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::RolesContext* PrestoSqlParser::roles() {
  RolesContext* _localctx =
      _tracker.createInstance<RolesContext>(_ctx, getState());
  enterRule(_localctx, 160, PrestoSqlParser::RuleRoles);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2123);
    identifier();
    setState(2128);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == PrestoSqlParser::T__3) {
      setState(2124);
      match(PrestoSqlParser::T__3);
      setState(2125);
      identifier();
      setState(2130);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext
//------------------------------------------------------------------

PrestoSqlParser::IdentifierContext::IdentifierContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::IdentifierContext::getRuleIndex() const {
  return PrestoSqlParser::RuleIdentifier;
}

void PrestoSqlParser::IdentifierContext::copyFrom(IdentifierContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- BackQuotedIdentifierContext
//------------------------------------------------------------------

tree::TerminalNode*
PrestoSqlParser::BackQuotedIdentifierContext::BACKQUOTED_IDENTIFIER() {
  return getToken(PrestoSqlParser::BACKQUOTED_IDENTIFIER, 0);
}

PrestoSqlParser::BackQuotedIdentifierContext::BackQuotedIdentifierContext(
    IdentifierContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::BackQuotedIdentifierContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterBackQuotedIdentifier(this);
}
void PrestoSqlParser::BackQuotedIdentifierContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitBackQuotedIdentifier(this);
}

std::any PrestoSqlParser::BackQuotedIdentifierContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitBackQuotedIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- QuotedIdentifierContext
//------------------------------------------------------------------

tree::TerminalNode*
PrestoSqlParser::QuotedIdentifierContext::QUOTED_IDENTIFIER() {
  return getToken(PrestoSqlParser::QUOTED_IDENTIFIER, 0);
}

PrestoSqlParser::QuotedIdentifierContext::QuotedIdentifierContext(
    IdentifierContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::QuotedIdentifierContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterQuotedIdentifier(this);
}
void PrestoSqlParser::QuotedIdentifierContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitQuotedIdentifier(this);
}

std::any PrestoSqlParser::QuotedIdentifierContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitQuotedIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DigitIdentifierContext
//------------------------------------------------------------------

tree::TerminalNode*
PrestoSqlParser::DigitIdentifierContext::DIGIT_IDENTIFIER() {
  return getToken(PrestoSqlParser::DIGIT_IDENTIFIER, 0);
}

PrestoSqlParser::DigitIdentifierContext::DigitIdentifierContext(
    IdentifierContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DigitIdentifierContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDigitIdentifier(this);
}
void PrestoSqlParser::DigitIdentifierContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDigitIdentifier(this);
}

std::any PrestoSqlParser::DigitIdentifierContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDigitIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- UnquotedIdentifierContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::UnquotedIdentifierContext::IDENTIFIER() {
  return getToken(PrestoSqlParser::IDENTIFIER, 0);
}

PrestoSqlParser::NonReservedContext*
PrestoSqlParser::UnquotedIdentifierContext::nonReserved() {
  return getRuleContext<PrestoSqlParser::NonReservedContext>(0);
}

PrestoSqlParser::UnquotedIdentifierContext::UnquotedIdentifierContext(
    IdentifierContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::UnquotedIdentifierContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnquotedIdentifier(this);
}
void PrestoSqlParser::UnquotedIdentifierContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnquotedIdentifier(this);
}

std::any PrestoSqlParser::UnquotedIdentifierContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUnquotedIdentifier(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::IdentifierContext* PrestoSqlParser::identifier() {
  IdentifierContext* _localctx =
      _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 162, PrestoSqlParser::RuleIdentifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2136);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::IDENTIFIER: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UnquotedIdentifierContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2131);
        match(PrestoSqlParser::IDENTIFIER);
        break;
      }

      case PrestoSqlParser::QUOTED_IDENTIFIER: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::QuotedIdentifierContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2132);
        match(PrestoSqlParser::QUOTED_IDENTIFIER);
        break;
      }

      case PrestoSqlParser::ADD:
      case PrestoSqlParser::ADMIN:
      case PrestoSqlParser::ALL:
      case PrestoSqlParser::ANALYZE:
      case PrestoSqlParser::ANY:
      case PrestoSqlParser::ARRAY:
      case PrestoSqlParser::ASC:
      case PrestoSqlParser::AT:
      case PrestoSqlParser::BEFORE:
      case PrestoSqlParser::BERNOULLI:
      case PrestoSqlParser::CALL:
      case PrestoSqlParser::CALLED:
      case PrestoSqlParser::CASCADE:
      case PrestoSqlParser::CATALOGS:
      case PrestoSqlParser::COLUMN:
      case PrestoSqlParser::COLUMNS:
      case PrestoSqlParser::COMMENT:
      case PrestoSqlParser::COMMIT:
      case PrestoSqlParser::COMMITTED:
      case PrestoSqlParser::CURRENT:
      case PrestoSqlParser::CURRENT_ROLE:
      case PrestoSqlParser::DATA:
      case PrestoSqlParser::DATE:
      case PrestoSqlParser::DAY:
      case PrestoSqlParser::DEFINER:
      case PrestoSqlParser::DESC:
      case PrestoSqlParser::DETERMINISTIC:
      case PrestoSqlParser::DISABLED:
      case PrestoSqlParser::DISTRIBUTED:
      case PrestoSqlParser::ENABLED:
      case PrestoSqlParser::ENFORCED:
      case PrestoSqlParser::EXCLUDE:
      case PrestoSqlParser::EXCLUDING:
      case PrestoSqlParser::EXECUTABLE:
      case PrestoSqlParser::EXPLAIN:
      case PrestoSqlParser::EXTERNAL:
      case PrestoSqlParser::FETCH:
      case PrestoSqlParser::FILTER:
      case PrestoSqlParser::FIRST:
      case PrestoSqlParser::FOLLOWING:
      case PrestoSqlParser::FORMAT:
      case PrestoSqlParser::FUNCTION:
      case PrestoSqlParser::FUNCTIONS:
      case PrestoSqlParser::GRANT:
      case PrestoSqlParser::GRANTED:
      case PrestoSqlParser::GRANTS:
      case PrestoSqlParser::GRAPH:
      case PrestoSqlParser::GRAPHVIZ:
      case PrestoSqlParser::GROUPS:
      case PrestoSqlParser::HOUR:
      case PrestoSqlParser::IF:
      case PrestoSqlParser::IGNORE:
      case PrestoSqlParser::INCLUDING:
      case PrestoSqlParser::INPUT:
      case PrestoSqlParser::INTERVAL:
      case PrestoSqlParser::INVOKER:
      case PrestoSqlParser::IO:
      case PrestoSqlParser::ISOLATION:
      case PrestoSqlParser::JSON:
      case PrestoSqlParser::KEY:
      case PrestoSqlParser::LANGUAGE:
      case PrestoSqlParser::LAST:
      case PrestoSqlParser::LATERAL:
      case PrestoSqlParser::LEVEL:
      case PrestoSqlParser::LIMIT:
      case PrestoSqlParser::LOGICAL:
      case PrestoSqlParser::MAP:
      case PrestoSqlParser::MATERIALIZED:
      case PrestoSqlParser::MINUTE:
      case PrestoSqlParser::MONTH:
      case PrestoSqlParser::NAME:
      case PrestoSqlParser::NFC:
      case PrestoSqlParser::NFD:
      case PrestoSqlParser::NFKC:
      case PrestoSqlParser::NFKD:
      case PrestoSqlParser::NO:
      case PrestoSqlParser::NONE:
      case PrestoSqlParser::NULLIF:
      case PrestoSqlParser::NULLS:
      case PrestoSqlParser::OF:
      case PrestoSqlParser::OFFSET:
      case PrestoSqlParser::ONLY:
      case PrestoSqlParser::OPTIMIZED:
      case PrestoSqlParser::OPTION:
      case PrestoSqlParser::ORDINALITY:
      case PrestoSqlParser::OUTPUT:
      case PrestoSqlParser::OVER:
      case PrestoSqlParser::PARTITION:
      case PrestoSqlParser::PARTITIONS:
      case PrestoSqlParser::POSITION:
      case PrestoSqlParser::PRECEDING:
      case PrestoSqlParser::PRIMARY:
      case PrestoSqlParser::PRIVILEGES:
      case PrestoSqlParser::PROPERTIES:
      case PrestoSqlParser::RANGE:
      case PrestoSqlParser::READ:
      case PrestoSqlParser::REFRESH:
      case PrestoSqlParser::RELY:
      case PrestoSqlParser::RENAME:
      case PrestoSqlParser::REPEATABLE:
      case PrestoSqlParser::REPLACE:
      case PrestoSqlParser::RESET:
      case PrestoSqlParser::RESPECT:
      case PrestoSqlParser::RESTRICT:
      case PrestoSqlParser::RETURN:
      case PrestoSqlParser::RETURNS:
      case PrestoSqlParser::REVOKE:
      case PrestoSqlParser::ROLE:
      case PrestoSqlParser::ROLES:
      case PrestoSqlParser::ROLLBACK:
      case PrestoSqlParser::ROW:
      case PrestoSqlParser::ROWS:
      case PrestoSqlParser::SCHEMA:
      case PrestoSqlParser::SCHEMAS:
      case PrestoSqlParser::SECOND:
      case PrestoSqlParser::SECURITY:
      case PrestoSqlParser::SERIALIZABLE:
      case PrestoSqlParser::SESSION:
      case PrestoSqlParser::SET:
      case PrestoSqlParser::SETS:
      case PrestoSqlParser::SHOW:
      case PrestoSqlParser::SOME:
      case PrestoSqlParser::SQL:
      case PrestoSqlParser::START:
      case PrestoSqlParser::STATS:
      case PrestoSqlParser::SUBSTRING:
      case PrestoSqlParser::SYSTEM:
      case PrestoSqlParser::SYSTEM_TIME:
      case PrestoSqlParser::SYSTEM_VERSION:
      case PrestoSqlParser::TABLES:
      case PrestoSqlParser::TABLESAMPLE:
      case PrestoSqlParser::TEMPORARY:
      case PrestoSqlParser::TEXT:
      case PrestoSqlParser::TIME:
      case PrestoSqlParser::TIMESTAMP:
      case PrestoSqlParser::TO:
      case PrestoSqlParser::TRANSACTION:
      case PrestoSqlParser::TRUNCATE:
      case PrestoSqlParser::TRY_CAST:
      case PrestoSqlParser::TYPE:
      case PrestoSqlParser::UNBOUNDED:
      case PrestoSqlParser::UNCOMMITTED:
      case PrestoSqlParser::UNIQUE:
      case PrestoSqlParser::UPDATE:
      case PrestoSqlParser::USE:
      case PrestoSqlParser::USER:
      case PrestoSqlParser::VALIDATE:
      case PrestoSqlParser::VERBOSE:
      case PrestoSqlParser::VERSION:
      case PrestoSqlParser::VIEW:
      case PrestoSqlParser::WORK:
      case PrestoSqlParser::WRITE:
      case PrestoSqlParser::YEAR:
      case PrestoSqlParser::ZONE: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::UnquotedIdentifierContext>(
                _localctx);
        enterOuterAlt(_localctx, 3);
        setState(2133);
        nonReserved();
        break;
      }

      case PrestoSqlParser::BACKQUOTED_IDENTIFIER: {
        _localctx =
            _tracker
                .createInstance<PrestoSqlParser::BackQuotedIdentifierContext>(
                    _localctx);
        enterOuterAlt(_localctx, 4);
        setState(2134);
        match(PrestoSqlParser::BACKQUOTED_IDENTIFIER);
        break;
      }

      case PrestoSqlParser::DIGIT_IDENTIFIER: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DigitIdentifierContext>(
                _localctx);
        enterOuterAlt(_localctx, 5);
        setState(2135);
        match(PrestoSqlParser::DIGIT_IDENTIFIER);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NumberContext
//------------------------------------------------------------------

PrestoSqlParser::NumberContext::NumberContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t PrestoSqlParser::NumberContext::getRuleIndex() const {
  return PrestoSqlParser::RuleNumber;
}

void PrestoSqlParser::NumberContext::copyFrom(NumberContext* ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- DecimalLiteralContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DecimalLiteralContext::DECIMAL_VALUE() {
  return getToken(PrestoSqlParser::DECIMAL_VALUE, 0);
}

PrestoSqlParser::DecimalLiteralContext::DecimalLiteralContext(
    NumberContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DecimalLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDecimalLiteral(this);
}
void PrestoSqlParser::DecimalLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDecimalLiteral(this);
}

std::any PrestoSqlParser::DecimalLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDecimalLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DoubleLiteralContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::DoubleLiteralContext::DOUBLE_VALUE() {
  return getToken(PrestoSqlParser::DOUBLE_VALUE, 0);
}

PrestoSqlParser::DoubleLiteralContext::DoubleLiteralContext(
    NumberContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::DoubleLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterDoubleLiteral(this);
}
void PrestoSqlParser::DoubleLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitDoubleLiteral(this);
}

std::any PrestoSqlParser::DoubleLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitDoubleLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IntegerLiteralContext
//------------------------------------------------------------------

tree::TerminalNode* PrestoSqlParser::IntegerLiteralContext::INTEGER_VALUE() {
  return getToken(PrestoSqlParser::INTEGER_VALUE, 0);
}

PrestoSqlParser::IntegerLiteralContext::IntegerLiteralContext(
    NumberContext* ctx) {
  copyFrom(ctx);
}

void PrestoSqlParser::IntegerLiteralContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntegerLiteral(this);
}
void PrestoSqlParser::IntegerLiteralContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntegerLiteral(this);
}

std::any PrestoSqlParser::IntegerLiteralContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitIntegerLiteral(this);
  else
    return visitor->visitChildren(this);
}
PrestoSqlParser::NumberContext* PrestoSqlParser::number() {
  NumberContext* _localctx =
      _tracker.createInstance<NumberContext>(_ctx, getState());
  enterRule(_localctx, 164, PrestoSqlParser::RuleNumber);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2141);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::DECIMAL_VALUE: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DecimalLiteralContext>(
                _localctx);
        enterOuterAlt(_localctx, 1);
        setState(2138);
        match(PrestoSqlParser::DECIMAL_VALUE);
        break;
      }

      case PrestoSqlParser::DOUBLE_VALUE: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::DoubleLiteralContext>(
                _localctx);
        enterOuterAlt(_localctx, 2);
        setState(2139);
        match(PrestoSqlParser::DOUBLE_VALUE);
        break;
      }

      case PrestoSqlParser::INTEGER_VALUE: {
        _localctx =
            _tracker.createInstance<PrestoSqlParser::IntegerLiteralContext>(
                _localctx);
        enterOuterAlt(_localctx, 3);
        setState(2140);
        match(PrestoSqlParser::INTEGER_VALUE);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintSpecificationContext
//------------------------------------------------------------------

PrestoSqlParser::ConstraintSpecificationContext::ConstraintSpecificationContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::NamedConstraintSpecificationContext* PrestoSqlParser::
    ConstraintSpecificationContext::namedConstraintSpecification() {
  return getRuleContext<PrestoSqlParser::NamedConstraintSpecificationContext>(
      0);
}

PrestoSqlParser::UnnamedConstraintSpecificationContext* PrestoSqlParser::
    ConstraintSpecificationContext::unnamedConstraintSpecification() {
  return getRuleContext<PrestoSqlParser::UnnamedConstraintSpecificationContext>(
      0);
}

size_t PrestoSqlParser::ConstraintSpecificationContext::getRuleIndex() const {
  return PrestoSqlParser::RuleConstraintSpecification;
}

void PrestoSqlParser::ConstraintSpecificationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraintSpecification(this);
}

void PrestoSqlParser::ConstraintSpecificationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraintSpecification(this);
}

std::any PrestoSqlParser::ConstraintSpecificationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitConstraintSpecification(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ConstraintSpecificationContext*
PrestoSqlParser::constraintSpecification() {
  ConstraintSpecificationContext* _localctx =
      _tracker.createInstance<ConstraintSpecificationContext>(_ctx, getState());
  enterRule(_localctx, 166, PrestoSqlParser::RuleConstraintSpecification);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2145);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::CONSTRAINT: {
        enterOuterAlt(_localctx, 1);
        setState(2143);
        namedConstraintSpecification();
        break;
      }

      case PrestoSqlParser::PRIMARY:
      case PrestoSqlParser::UNIQUE: {
        enterOuterAlt(_localctx, 2);
        setState(2144);
        unnamedConstraintSpecification();
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NamedConstraintSpecificationContext
//------------------------------------------------------------------

PrestoSqlParser::NamedConstraintSpecificationContext::
    NamedConstraintSpecificationContext(
        ParserRuleContext* parent,
        size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode*
PrestoSqlParser::NamedConstraintSpecificationContext::CONSTRAINT() {
  return getToken(PrestoSqlParser::CONSTRAINT, 0);
}

PrestoSqlParser::UnnamedConstraintSpecificationContext* PrestoSqlParser::
    NamedConstraintSpecificationContext::unnamedConstraintSpecification() {
  return getRuleContext<PrestoSqlParser::UnnamedConstraintSpecificationContext>(
      0);
}

PrestoSqlParser::IdentifierContext*
PrestoSqlParser::NamedConstraintSpecificationContext::identifier() {
  return getRuleContext<PrestoSqlParser::IdentifierContext>(0);
}

size_t PrestoSqlParser::NamedConstraintSpecificationContext::getRuleIndex()
    const {
  return PrestoSqlParser::RuleNamedConstraintSpecification;
}

void PrestoSqlParser::NamedConstraintSpecificationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNamedConstraintSpecification(this);
}

void PrestoSqlParser::NamedConstraintSpecificationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNamedConstraintSpecification(this);
}

std::any PrestoSqlParser::NamedConstraintSpecificationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNamedConstraintSpecification(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::NamedConstraintSpecificationContext*
PrestoSqlParser::namedConstraintSpecification() {
  NamedConstraintSpecificationContext* _localctx =
      _tracker.createInstance<NamedConstraintSpecificationContext>(
          _ctx, getState());
  enterRule(_localctx, 168, PrestoSqlParser::RuleNamedConstraintSpecification);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2147);
    match(PrestoSqlParser::CONSTRAINT);
    setState(2148);
    antlrcpp::downCast<NamedConstraintSpecificationContext*>(_localctx)->name =
        identifier();
    setState(2149);
    unnamedConstraintSpecification();

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- UnnamedConstraintSpecificationContext
//------------------------------------------------------------------

PrestoSqlParser::UnnamedConstraintSpecificationContext::
    UnnamedConstraintSpecificationContext(
        ParserRuleContext* parent,
        size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::ConstraintTypeContext*
PrestoSqlParser::UnnamedConstraintSpecificationContext::constraintType() {
  return getRuleContext<PrestoSqlParser::ConstraintTypeContext>(0);
}

PrestoSqlParser::ColumnAliasesContext*
PrestoSqlParser::UnnamedConstraintSpecificationContext::columnAliases() {
  return getRuleContext<PrestoSqlParser::ColumnAliasesContext>(0);
}

PrestoSqlParser::ConstraintQualifiersContext*
PrestoSqlParser::UnnamedConstraintSpecificationContext::constraintQualifiers() {
  return getRuleContext<PrestoSqlParser::ConstraintQualifiersContext>(0);
}

size_t PrestoSqlParser::UnnamedConstraintSpecificationContext::getRuleIndex()
    const {
  return PrestoSqlParser::RuleUnnamedConstraintSpecification;
}

void PrestoSqlParser::UnnamedConstraintSpecificationContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterUnnamedConstraintSpecification(this);
}

void PrestoSqlParser::UnnamedConstraintSpecificationContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitUnnamedConstraintSpecification(this);
}

std::any PrestoSqlParser::UnnamedConstraintSpecificationContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitUnnamedConstraintSpecification(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::UnnamedConstraintSpecificationContext*
PrestoSqlParser::unnamedConstraintSpecification() {
  UnnamedConstraintSpecificationContext* _localctx =
      _tracker.createInstance<UnnamedConstraintSpecificationContext>(
          _ctx, getState());
  enterRule(
      _localctx, 170, PrestoSqlParser::RuleUnnamedConstraintSpecification);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2151);
    constraintType();
    setState(2152);
    columnAliases();
    setState(2154);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 273, _ctx)) {
      case 1: {
        setState(2153);
        constraintQualifiers();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintTypeContext
//------------------------------------------------------------------

PrestoSqlParser::ConstraintTypeContext::ConstraintTypeContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ConstraintTypeContext::UNIQUE() {
  return getToken(PrestoSqlParser::UNIQUE, 0);
}

tree::TerminalNode* PrestoSqlParser::ConstraintTypeContext::PRIMARY() {
  return getToken(PrestoSqlParser::PRIMARY, 0);
}

tree::TerminalNode* PrestoSqlParser::ConstraintTypeContext::KEY() {
  return getToken(PrestoSqlParser::KEY, 0);
}

size_t PrestoSqlParser::ConstraintTypeContext::getRuleIndex() const {
  return PrestoSqlParser::RuleConstraintType;
}

void PrestoSqlParser::ConstraintTypeContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraintType(this);
}

void PrestoSqlParser::ConstraintTypeContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraintType(this);
}

std::any PrestoSqlParser::ConstraintTypeContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitConstraintType(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ConstraintTypeContext* PrestoSqlParser::constraintType() {
  ConstraintTypeContext* _localctx =
      _tracker.createInstance<ConstraintTypeContext>(_ctx, getState());
  enterRule(_localctx, 172, PrestoSqlParser::RuleConstraintType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2159);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::UNIQUE: {
        enterOuterAlt(_localctx, 1);
        setState(2156);
        match(PrestoSqlParser::UNIQUE);
        break;
      }

      case PrestoSqlParser::PRIMARY: {
        enterOuterAlt(_localctx, 2);
        setState(2157);
        match(PrestoSqlParser::PRIMARY);
        setState(2158);
        match(PrestoSqlParser::KEY);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintQualifiersContext
//------------------------------------------------------------------

PrestoSqlParser::ConstraintQualifiersContext::ConstraintQualifiersContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<PrestoSqlParser::ConstraintQualifierContext*>
PrestoSqlParser::ConstraintQualifiersContext::constraintQualifier() {
  return getRuleContexts<PrestoSqlParser::ConstraintQualifierContext>();
}

PrestoSqlParser::ConstraintQualifierContext*
PrestoSqlParser::ConstraintQualifiersContext::constraintQualifier(size_t i) {
  return getRuleContext<PrestoSqlParser::ConstraintQualifierContext>(i);
}

size_t PrestoSqlParser::ConstraintQualifiersContext::getRuleIndex() const {
  return PrestoSqlParser::RuleConstraintQualifiers;
}

void PrestoSqlParser::ConstraintQualifiersContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraintQualifiers(this);
}

void PrestoSqlParser::ConstraintQualifiersContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraintQualifiers(this);
}

std::any PrestoSqlParser::ConstraintQualifiersContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitConstraintQualifiers(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ConstraintQualifiersContext*
PrestoSqlParser::constraintQualifiers() {
  ConstraintQualifiersContext* _localctx =
      _tracker.createInstance<ConstraintQualifiersContext>(_ctx, getState());
  enterRule(_localctx, 174, PrestoSqlParser::RuleConstraintQualifiers);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2164);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~0x3fULL) == 0) &&
            ((1ULL << _la) & -6845471433603153920) != 0) ||
           _la == PrestoSqlParser::NOT

           || _la == PrestoSqlParser::RELY) {
      setState(2161);
      constraintQualifier();
      setState(2166);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintQualifierContext
//------------------------------------------------------------------

PrestoSqlParser::ConstraintQualifierContext::ConstraintQualifierContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

PrestoSqlParser::ConstraintEnabledContext*
PrestoSqlParser::ConstraintQualifierContext::constraintEnabled() {
  return getRuleContext<PrestoSqlParser::ConstraintEnabledContext>(0);
}

PrestoSqlParser::ConstraintRelyContext*
PrestoSqlParser::ConstraintQualifierContext::constraintRely() {
  return getRuleContext<PrestoSqlParser::ConstraintRelyContext>(0);
}

PrestoSqlParser::ConstraintEnforcedContext*
PrestoSqlParser::ConstraintQualifierContext::constraintEnforced() {
  return getRuleContext<PrestoSqlParser::ConstraintEnforcedContext>(0);
}

size_t PrestoSqlParser::ConstraintQualifierContext::getRuleIndex() const {
  return PrestoSqlParser::RuleConstraintQualifier;
}

void PrestoSqlParser::ConstraintQualifierContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraintQualifier(this);
}

void PrestoSqlParser::ConstraintQualifierContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraintQualifier(this);
}

std::any PrestoSqlParser::ConstraintQualifierContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitConstraintQualifier(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ConstraintQualifierContext*
PrestoSqlParser::constraintQualifier() {
  ConstraintQualifierContext* _localctx =
      _tracker.createInstance<ConstraintQualifierContext>(_ctx, getState());
  enterRule(_localctx, 176, PrestoSqlParser::RuleConstraintQualifier);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2170);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
        _input, 276, _ctx)) {
      case 1: {
        enterOuterAlt(_localctx, 1);
        setState(2167);
        constraintEnabled();
        break;
      }

      case 2: {
        enterOuterAlt(_localctx, 2);
        setState(2168);
        constraintRely();
        break;
      }

      case 3: {
        enterOuterAlt(_localctx, 3);
        setState(2169);
        constraintEnforced();
        break;
      }

      default:
        break;
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintRelyContext
//------------------------------------------------------------------

PrestoSqlParser::ConstraintRelyContext::ConstraintRelyContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ConstraintRelyContext::RELY() {
  return getToken(PrestoSqlParser::RELY, 0);
}

tree::TerminalNode* PrestoSqlParser::ConstraintRelyContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

size_t PrestoSqlParser::ConstraintRelyContext::getRuleIndex() const {
  return PrestoSqlParser::RuleConstraintRely;
}

void PrestoSqlParser::ConstraintRelyContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraintRely(this);
}

void PrestoSqlParser::ConstraintRelyContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraintRely(this);
}

std::any PrestoSqlParser::ConstraintRelyContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitConstraintRely(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ConstraintRelyContext* PrestoSqlParser::constraintRely() {
  ConstraintRelyContext* _localctx =
      _tracker.createInstance<ConstraintRelyContext>(_ctx, getState());
  enterRule(_localctx, 178, PrestoSqlParser::RuleConstraintRely);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2175);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::RELY: {
        enterOuterAlt(_localctx, 1);
        setState(2172);
        match(PrestoSqlParser::RELY);
        break;
      }

      case PrestoSqlParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(2173);
        match(PrestoSqlParser::NOT);
        setState(2174);
        match(PrestoSqlParser::RELY);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintEnabledContext
//------------------------------------------------------------------

PrestoSqlParser::ConstraintEnabledContext::ConstraintEnabledContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ConstraintEnabledContext::ENABLED() {
  return getToken(PrestoSqlParser::ENABLED, 0);
}

tree::TerminalNode* PrestoSqlParser::ConstraintEnabledContext::DISABLED() {
  return getToken(PrestoSqlParser::DISABLED, 0);
}

size_t PrestoSqlParser::ConstraintEnabledContext::getRuleIndex() const {
  return PrestoSqlParser::RuleConstraintEnabled;
}

void PrestoSqlParser::ConstraintEnabledContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraintEnabled(this);
}

void PrestoSqlParser::ConstraintEnabledContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraintEnabled(this);
}

std::any PrestoSqlParser::ConstraintEnabledContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitConstraintEnabled(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ConstraintEnabledContext*
PrestoSqlParser::constraintEnabled() {
  ConstraintEnabledContext* _localctx =
      _tracker.createInstance<ConstraintEnabledContext>(_ctx, getState());
  enterRule(_localctx, 180, PrestoSqlParser::RuleConstraintEnabled);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2177);
    _la = _input->LA(1);
    if (!(_la == PrestoSqlParser::DISABLED

          || _la == PrestoSqlParser::ENABLED)) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConstraintEnforcedContext
//------------------------------------------------------------------

PrestoSqlParser::ConstraintEnforcedContext::ConstraintEnforcedContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::ConstraintEnforcedContext::ENFORCED() {
  return getToken(PrestoSqlParser::ENFORCED, 0);
}

tree::TerminalNode* PrestoSqlParser::ConstraintEnforcedContext::NOT() {
  return getToken(PrestoSqlParser::NOT, 0);
}

size_t PrestoSqlParser::ConstraintEnforcedContext::getRuleIndex() const {
  return PrestoSqlParser::RuleConstraintEnforced;
}

void PrestoSqlParser::ConstraintEnforcedContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterConstraintEnforced(this);
}

void PrestoSqlParser::ConstraintEnforcedContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitConstraintEnforced(this);
}

std::any PrestoSqlParser::ConstraintEnforcedContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitConstraintEnforced(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::ConstraintEnforcedContext*
PrestoSqlParser::constraintEnforced() {
  ConstraintEnforcedContext* _localctx =
      _tracker.createInstance<ConstraintEnforcedContext>(_ctx, getState());
  enterRule(_localctx, 182, PrestoSqlParser::RuleConstraintEnforced);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(2182);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case PrestoSqlParser::ENFORCED: {
        enterOuterAlt(_localctx, 1);
        setState(2179);
        match(PrestoSqlParser::ENFORCED);
        break;
      }

      case PrestoSqlParser::NOT: {
        enterOuterAlt(_localctx, 2);
        setState(2180);
        match(PrestoSqlParser::NOT);
        setState(2181);
        match(PrestoSqlParser::ENFORCED);
        break;
      }

      default:
        throw NoViableAltException(this);
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NonReservedContext
//------------------------------------------------------------------

PrestoSqlParser::NonReservedContext::NonReservedContext(
    ParserRuleContext* parent,
    size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ADD() {
  return getToken(PrestoSqlParser::ADD, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ADMIN() {
  return getToken(PrestoSqlParser::ADMIN, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ALL() {
  return getToken(PrestoSqlParser::ALL, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ANALYZE() {
  return getToken(PrestoSqlParser::ANALYZE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ANY() {
  return getToken(PrestoSqlParser::ANY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ARRAY() {
  return getToken(PrestoSqlParser::ARRAY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ASC() {
  return getToken(PrestoSqlParser::ASC, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::AT() {
  return getToken(PrestoSqlParser::AT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::BEFORE() {
  return getToken(PrestoSqlParser::BEFORE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::BERNOULLI() {
  return getToken(PrestoSqlParser::BERNOULLI, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::CALL() {
  return getToken(PrestoSqlParser::CALL, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::CALLED() {
  return getToken(PrestoSqlParser::CALLED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::CASCADE() {
  return getToken(PrestoSqlParser::CASCADE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::CATALOGS() {
  return getToken(PrestoSqlParser::CATALOGS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::COLUMN() {
  return getToken(PrestoSqlParser::COLUMN, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::COLUMNS() {
  return getToken(PrestoSqlParser::COLUMNS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::COMMENT() {
  return getToken(PrestoSqlParser::COMMENT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::COMMIT() {
  return getToken(PrestoSqlParser::COMMIT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::COMMITTED() {
  return getToken(PrestoSqlParser::COMMITTED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::CURRENT() {
  return getToken(PrestoSqlParser::CURRENT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::CURRENT_ROLE() {
  return getToken(PrestoSqlParser::CURRENT_ROLE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::DATA() {
  return getToken(PrestoSqlParser::DATA, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::DATE() {
  return getToken(PrestoSqlParser::DATE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::DAY() {
  return getToken(PrestoSqlParser::DAY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::DEFINER() {
  return getToken(PrestoSqlParser::DEFINER, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::DESC() {
  return getToken(PrestoSqlParser::DESC, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::DETERMINISTIC() {
  return getToken(PrestoSqlParser::DETERMINISTIC, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::DISABLED() {
  return getToken(PrestoSqlParser::DISABLED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::DISTRIBUTED() {
  return getToken(PrestoSqlParser::DISTRIBUTED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ENABLED() {
  return getToken(PrestoSqlParser::ENABLED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ENFORCED() {
  return getToken(PrestoSqlParser::ENFORCED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::EXECUTABLE() {
  return getToken(PrestoSqlParser::EXECUTABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::EXCLUDE() {
  return getToken(PrestoSqlParser::EXCLUDE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::EXCLUDING() {
  return getToken(PrestoSqlParser::EXCLUDING, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::EXPLAIN() {
  return getToken(PrestoSqlParser::EXPLAIN, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::EXTERNAL() {
  return getToken(PrestoSqlParser::EXTERNAL, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::FETCH() {
  return getToken(PrestoSqlParser::FETCH, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::FILTER() {
  return getToken(PrestoSqlParser::FILTER, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::FIRST() {
  return getToken(PrestoSqlParser::FIRST, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::FOLLOWING() {
  return getToken(PrestoSqlParser::FOLLOWING, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::FORMAT() {
  return getToken(PrestoSqlParser::FORMAT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::FUNCTION() {
  return getToken(PrestoSqlParser::FUNCTION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::FUNCTIONS() {
  return getToken(PrestoSqlParser::FUNCTIONS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::GRANT() {
  return getToken(PrestoSqlParser::GRANT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::GRANTED() {
  return getToken(PrestoSqlParser::GRANTED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::GRANTS() {
  return getToken(PrestoSqlParser::GRANTS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::GRAPH() {
  return getToken(PrestoSqlParser::GRAPH, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::GRAPHVIZ() {
  return getToken(PrestoSqlParser::GRAPHVIZ, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::GROUPS() {
  return getToken(PrestoSqlParser::GROUPS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::HOUR() {
  return getToken(PrestoSqlParser::HOUR, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::IF() {
  return getToken(PrestoSqlParser::IF, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::IGNORE() {
  return getToken(PrestoSqlParser::IGNORE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::INCLUDING() {
  return getToken(PrestoSqlParser::INCLUDING, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::INPUT() {
  return getToken(PrestoSqlParser::INPUT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::INTERVAL() {
  return getToken(PrestoSqlParser::INTERVAL, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::INVOKER() {
  return getToken(PrestoSqlParser::INVOKER, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::IO() {
  return getToken(PrestoSqlParser::IO, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ISOLATION() {
  return getToken(PrestoSqlParser::ISOLATION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::JSON() {
  return getToken(PrestoSqlParser::JSON, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::KEY() {
  return getToken(PrestoSqlParser::KEY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::LANGUAGE() {
  return getToken(PrestoSqlParser::LANGUAGE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::LAST() {
  return getToken(PrestoSqlParser::LAST, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::LATERAL() {
  return getToken(PrestoSqlParser::LATERAL, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::LEVEL() {
  return getToken(PrestoSqlParser::LEVEL, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::LIMIT() {
  return getToken(PrestoSqlParser::LIMIT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::LOGICAL() {
  return getToken(PrestoSqlParser::LOGICAL, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::MAP() {
  return getToken(PrestoSqlParser::MAP, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::MATERIALIZED() {
  return getToken(PrestoSqlParser::MATERIALIZED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::MINUTE() {
  return getToken(PrestoSqlParser::MINUTE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::MONTH() {
  return getToken(PrestoSqlParser::MONTH, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NAME() {
  return getToken(PrestoSqlParser::NAME, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NFC() {
  return getToken(PrestoSqlParser::NFC, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NFD() {
  return getToken(PrestoSqlParser::NFD, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NFKC() {
  return getToken(PrestoSqlParser::NFKC, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NFKD() {
  return getToken(PrestoSqlParser::NFKD, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NO() {
  return getToken(PrestoSqlParser::NO, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NONE() {
  return getToken(PrestoSqlParser::NONE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NULLIF() {
  return getToken(PrestoSqlParser::NULLIF, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::NULLS() {
  return getToken(PrestoSqlParser::NULLS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::OF() {
  return getToken(PrestoSqlParser::OF, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::OFFSET() {
  return getToken(PrestoSqlParser::OFFSET, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ONLY() {
  return getToken(PrestoSqlParser::ONLY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::OPTIMIZED() {
  return getToken(PrestoSqlParser::OPTIMIZED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::OPTION() {
  return getToken(PrestoSqlParser::OPTION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ORDINALITY() {
  return getToken(PrestoSqlParser::ORDINALITY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::OUTPUT() {
  return getToken(PrestoSqlParser::OUTPUT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::OVER() {
  return getToken(PrestoSqlParser::OVER, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::PARTITION() {
  return getToken(PrestoSqlParser::PARTITION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::PARTITIONS() {
  return getToken(PrestoSqlParser::PARTITIONS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::POSITION() {
  return getToken(PrestoSqlParser::POSITION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::PRECEDING() {
  return getToken(PrestoSqlParser::PRECEDING, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::PRIMARY() {
  return getToken(PrestoSqlParser::PRIMARY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::PRIVILEGES() {
  return getToken(PrestoSqlParser::PRIVILEGES, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::PROPERTIES() {
  return getToken(PrestoSqlParser::PROPERTIES, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::RANGE() {
  return getToken(PrestoSqlParser::RANGE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::READ() {
  return getToken(PrestoSqlParser::READ, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::REFRESH() {
  return getToken(PrestoSqlParser::REFRESH, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::RELY() {
  return getToken(PrestoSqlParser::RELY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::RENAME() {
  return getToken(PrestoSqlParser::RENAME, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::REPEATABLE() {
  return getToken(PrestoSqlParser::REPEATABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::REPLACE() {
  return getToken(PrestoSqlParser::REPLACE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::RESET() {
  return getToken(PrestoSqlParser::RESET, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::RESPECT() {
  return getToken(PrestoSqlParser::RESPECT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::RESTRICT() {
  return getToken(PrestoSqlParser::RESTRICT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::RETURN() {
  return getToken(PrestoSqlParser::RETURN, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::RETURNS() {
  return getToken(PrestoSqlParser::RETURNS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::REVOKE() {
  return getToken(PrestoSqlParser::REVOKE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ROLE() {
  return getToken(PrestoSqlParser::ROLE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ROLES() {
  return getToken(PrestoSqlParser::ROLES, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ROLLBACK() {
  return getToken(PrestoSqlParser::ROLLBACK, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ROW() {
  return getToken(PrestoSqlParser::ROW, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ROWS() {
  return getToken(PrestoSqlParser::ROWS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SCHEMA() {
  return getToken(PrestoSqlParser::SCHEMA, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SCHEMAS() {
  return getToken(PrestoSqlParser::SCHEMAS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SECOND() {
  return getToken(PrestoSqlParser::SECOND, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SECURITY() {
  return getToken(PrestoSqlParser::SECURITY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SERIALIZABLE() {
  return getToken(PrestoSqlParser::SERIALIZABLE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SESSION() {
  return getToken(PrestoSqlParser::SESSION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SET() {
  return getToken(PrestoSqlParser::SET, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SETS() {
  return getToken(PrestoSqlParser::SETS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SQL() {
  return getToken(PrestoSqlParser::SQL, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SHOW() {
  return getToken(PrestoSqlParser::SHOW, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SOME() {
  return getToken(PrestoSqlParser::SOME, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::START() {
  return getToken(PrestoSqlParser::START, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::STATS() {
  return getToken(PrestoSqlParser::STATS, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SUBSTRING() {
  return getToken(PrestoSqlParser::SUBSTRING, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SYSTEM() {
  return getToken(PrestoSqlParser::SYSTEM, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SYSTEM_TIME() {
  return getToken(PrestoSqlParser::SYSTEM_TIME, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::SYSTEM_VERSION() {
  return getToken(PrestoSqlParser::SYSTEM_VERSION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TABLES() {
  return getToken(PrestoSqlParser::TABLES, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TABLESAMPLE() {
  return getToken(PrestoSqlParser::TABLESAMPLE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TEMPORARY() {
  return getToken(PrestoSqlParser::TEMPORARY, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TEXT() {
  return getToken(PrestoSqlParser::TEXT, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TIME() {
  return getToken(PrestoSqlParser::TIME, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TIMESTAMP() {
  return getToken(PrestoSqlParser::TIMESTAMP, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TO() {
  return getToken(PrestoSqlParser::TO, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TRANSACTION() {
  return getToken(PrestoSqlParser::TRANSACTION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TRUNCATE() {
  return getToken(PrestoSqlParser::TRUNCATE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TRY_CAST() {
  return getToken(PrestoSqlParser::TRY_CAST, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::TYPE() {
  return getToken(PrestoSqlParser::TYPE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::UNBOUNDED() {
  return getToken(PrestoSqlParser::UNBOUNDED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::UNCOMMITTED() {
  return getToken(PrestoSqlParser::UNCOMMITTED, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::UNIQUE() {
  return getToken(PrestoSqlParser::UNIQUE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::UPDATE() {
  return getToken(PrestoSqlParser::UPDATE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::USE() {
  return getToken(PrestoSqlParser::USE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::USER() {
  return getToken(PrestoSqlParser::USER, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::VALIDATE() {
  return getToken(PrestoSqlParser::VALIDATE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::VERBOSE() {
  return getToken(PrestoSqlParser::VERBOSE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::VERSION() {
  return getToken(PrestoSqlParser::VERSION, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::VIEW() {
  return getToken(PrestoSqlParser::VIEW, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::WORK() {
  return getToken(PrestoSqlParser::WORK, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::WRITE() {
  return getToken(PrestoSqlParser::WRITE, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::YEAR() {
  return getToken(PrestoSqlParser::YEAR, 0);
}

tree::TerminalNode* PrestoSqlParser::NonReservedContext::ZONE() {
  return getToken(PrestoSqlParser::ZONE, 0);
}

size_t PrestoSqlParser::NonReservedContext::getRuleIndex() const {
  return PrestoSqlParser::RuleNonReserved;
}

void PrestoSqlParser::NonReservedContext::enterRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->enterNonReserved(this);
}

void PrestoSqlParser::NonReservedContext::exitRule(
    tree::ParseTreeListener* listener) {
  auto parserListener = dynamic_cast<PrestoSqlListener*>(listener);
  if (parserListener != nullptr)
    parserListener->exitNonReserved(this);
}

std::any PrestoSqlParser::NonReservedContext::accept(
    tree::ParseTreeVisitor* visitor) {
  if (auto parserVisitor = dynamic_cast<PrestoSqlVisitor*>(visitor))
    return parserVisitor->visitNonReserved(this);
  else
    return visitor->visitChildren(this);
}

PrestoSqlParser::NonReservedContext* PrestoSqlParser::nonReserved() {
  NonReservedContext* _localctx =
      _tracker.createInstance<NonReservedContext>(_ctx, getState());
  enterRule(_localctx, 184, PrestoSqlParser::RuleNonReserved);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(2184);
    _la = _input->LA(1);
    if (!((((_la & ~0x3fULL) == 0) &&
           ((1ULL << _la) & -6508956968051886080) != 0) ||
          ((((_la - 66) & ~0x3fULL) == 0) &&
           ((1ULL << (_la - 66)) & -2335699536833519961) != 0) ||
          ((((_la - 130) & ~0x3fULL) == 0) &&
           ((1ULL << (_la - 130)) & -18163934272260209) != 0) ||
          ((((_la - 194) & ~0x3fULL) == 0) &&
           ((1ULL << (_la - 194)) & 1038700232175) != 0))) {
      _errHandler->recoverInline(this);
    } else {
      _errHandler->reportMatch(this);
      consume();
    }

  } catch (RecognitionException& e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool PrestoSqlParser::sempred(
    RuleContext* context,
    size_t ruleIndex,
    size_t predicateIndex) {
  switch (ruleIndex) {
    case 24:
      return queryTermSempred(
          antlrcpp::downCast<QueryTermContext*>(context), predicateIndex);
    case 38:
      return relationSempred(
          antlrcpp::downCast<RelationContext*>(context), predicateIndex);
    case 47:
      return booleanExpressionSempred(
          antlrcpp::downCast<BooleanExpressionContext*>(context),
          predicateIndex);
    case 49:
      return valueExpressionSempred(
          antlrcpp::downCast<ValueExpressionContext*>(context), predicateIndex);
    case 50:
      return primaryExpressionSempred(
          antlrcpp::downCast<PrimaryExpressionContext*>(context),
          predicateIndex);
    case 61:
      return typeSempred(
          antlrcpp::downCast<TypeContext*>(context), predicateIndex);

    default:
      break;
  }
  return true;
}

bool PrestoSqlParser::queryTermSempred(
    QueryTermContext* _localctx,
    size_t predicateIndex) {
  switch (predicateIndex) {
    case 0:
      return precpred(_ctx, 2);
    case 1:
      return precpred(_ctx, 1);

    default:
      break;
  }
  return true;
}

bool PrestoSqlParser::relationSempred(
    RelationContext* _localctx,
    size_t predicateIndex) {
  switch (predicateIndex) {
    case 2:
      return precpred(_ctx, 2);

    default:
      break;
  }
  return true;
}

bool PrestoSqlParser::booleanExpressionSempred(
    BooleanExpressionContext* _localctx,
    size_t predicateIndex) {
  switch (predicateIndex) {
    case 3:
      return precpred(_ctx, 2);
    case 4:
      return precpred(_ctx, 1);

    default:
      break;
  }
  return true;
}

bool PrestoSqlParser::valueExpressionSempred(
    ValueExpressionContext* _localctx,
    size_t predicateIndex) {
  switch (predicateIndex) {
    case 5:
      return precpred(_ctx, 3);
    case 6:
      return precpred(_ctx, 2);
    case 7:
      return precpred(_ctx, 1);
    case 8:
      return precpred(_ctx, 5);

    default:
      break;
  }
  return true;
}

bool PrestoSqlParser::primaryExpressionSempred(
    PrimaryExpressionContext* _localctx,
    size_t predicateIndex) {
  switch (predicateIndex) {
    case 9:
      return precpred(_ctx, 15);
    case 10:
      return precpred(_ctx, 13);
    case 11:
      return precpred(_ctx, 12);

    default:
      break;
  }
  return true;
}

bool PrestoSqlParser::typeSempred(
    TypeContext* _localctx,
    size_t predicateIndex) {
  switch (predicateIndex) {
    case 12:
      return precpred(_ctx, 6);

    default:
      break;
  }
  return true;
}

void PrestoSqlParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  prestosqlParserInitialize();
#else
  ::antlr4::internal::call_once(
      prestosqlParserOnceFlag, prestosqlParserInitialize);
#endif
}
