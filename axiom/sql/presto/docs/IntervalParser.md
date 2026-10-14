# Presto interval literals

`IntervalParser` converts an `IntervalLiteral` AST node to a typed constant.
This guide describes the syntax and limits for developers maintaining the Presto
parser. Day-time intervals store milliseconds in `int64_t`; year-month intervals
store months in `int32_t`.

## Qualifiers and separators

A literal has the form `INTERVAL [sign] 'value' start [TO end]`.
The qualifier selects the fields in the value, from the largest unit to the
smallest. Both fields must belong to the same group, in the order shown below.

| Group | Field order | Separator between adjacent fields |
| --- | --- | --- |
| Year-month | `YEAR`, `MONTH` | `-` |
| Day-time | `DAY`, `HOUR`, `MINUTE`, `SECOND` | One space between day and hour; `:` between hour, minute, and second |

Each field can be used alone. Compound qualifiers are `YEAR TO MONTH`,
`DAY TO HOUR`, `DAY TO MINUTE`, `DAY TO SECOND`, `HOUR TO MINUTE`,
`HOUR TO SECOND`, and `MINUTE TO SECOND`. Repeating a field, such as
`SECOND TO SECOND`, has the same meaning as the single field.

```sql
INTERVAL '1-6' YEAR TO MONTH          -- 18 months
INTERVAL '1 02:03:04.5' DAY TO SECOND -- 1 day, 2 hours, 3 minutes, 4.5 seconds
INTERVAL '03:.004' MINUTE TO SECOND  -- 3 minutes and 4 milliseconds
```

Fields contribute durations. A later field can exceed its clock range:
`INTERVAL '1:60' HOUR TO MINUTE` is two hours, and
`INTERVAL '124-30' YEAR TO MONTH` is 1,518 months.

## Omitted fields

A value can end after any complete field; the remaining fields are zero.
`INTERVAL '12' DAY TO SECOND` is twelve days, and
`INTERVAL '10:45' HOUR TO SECOND` is ten hours and forty-five minutes.
An empty value is zero for every valid qualifier.

A separator must be followed by a field. Values such as `'1:' HOUR TO SECOND`
and `'1-' YEAR TO MONTH` are rejected. Leading and trailing whitespace are also
rejected, except for the single space separating day and hour.

## Signs

A leading minus sign inside the value negates the whole duration. Each field
can have one leading plus sign. Negative later fields are rejected.

```sql
INTERVAL '-1-6' YEAR TO MONTH     -- -18 months
INTERVAL '1:+2' HOUR TO MINUTE   -- 1 hour and 2 minutes
INTERVAL '-+1' SECOND           -- -1 second
INTERVAL -'-1' SECOND           -- 1 second
```

The sign outside the quotes multiplies the sign inside. To match Presto,
a value consisting of just `'-'` is zero. A lone `'+'` or a repeated plus sign,
such as `'++1'`, is rejected.

## Fractional seconds

Only seconds accept a decimal fraction, separated by `.`. The integer part or
the fraction can be omitted, as in `'.001'` and `'1.'`. At least one digit must
be present: `'.'` is rejected. Fractions are truncated to milliseconds:
`'1.123456' SECOND` is 1,123 milliseconds, and `'-0.00049' SECOND` is zero.
Comma decimals and exponent notation are rejected.

## Numeric limits

The limits match Presto's period parser:

- Each field's integer part is between zero and `2,147,483,647`.
- Each field contains at most ten digits, including leading zeros. For seconds,
  this counts the integer and fraction together.
- A decimal point requires fewer than ten integer digits before it.
  `'123456789.9' SECOND` is valid; `'2147483647.' SECOND` and
  `'2147483647.999' SECOND` are rejected.
- The total magnitude of a year-month interval is at most `2,147,483,647` months.
  `'178956970-7' YEAR TO MONTH` reaches this limit; adding another month fails.

The bounded day-time fields fit together in `int64_t` milliseconds. Applying
signs and truncating fractions therefore preserve the value without overflow.
Invalid qualifiers, malformed values, and values outside these limits produce
Presto semantic errors at the literal's source location.

## Diagnostics

Value errors name the qualifier and input, followed by the reason:

```text
Invalid INTERVAL HOUR TO MINUTE value: 1:-2; The MINUTE field must be non-negative
Invalid INTERVAL SECOND value: 1,5; Unexpected characters: ,5
```

Qualifier errors name the fields and explain their required grouping or order.
Numeric errors identify the limit that failed. The semantic error also carries
the literal's location in the SQL text.
