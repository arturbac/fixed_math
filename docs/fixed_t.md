## About `fixed_t`

`fixed_t` is a central type in this library, designed for high-precision fixed-point arithmetic. Its purpose is to facilitate arithmetic operations with fixed-point numbers while avoiding the pitfalls of implicit conversions from standard integer types.

### Key Characteristics

- **Carrier Mechanism**: Utilizes `fix_carrier_t` as an internal carrier for the `fixed_internal` type. This approach ensures clear differentiation from standard `int64` types, encapsulating the fixed-point value securely.
- **Hermetization**: `fixed_t` prevents implicit conversions from `int64`, `long long`, and similar types, preserving the integrity and intended precision of calculations.
- **Explicit Conversions**: Offers explicit conversion operators to and from arithmetic types, ensuring that conversions are deliberate and clear in user code.
- **Operators**: Supports common arithmetic operators such as `+`, `-`, `*`, ensuring `fixed_t` can be used seamlessly in mathematical expressions.
- **Comparison Operators**: Provides comparison functionality (`==`, `!=`, `<`, `>`, `<=`, `>=`), enabling straightforward equality and relational comparisons.

### Constructors and Assignment

- Default, copy, and move constructors and assignment operators are `constexpr` and `noexcept`, emphasizing efficiency and compatibility with compile-time evaluation.


### Utility Functions

- `as_fixed`: Constructs a `fixed_t` instance from a raw value in its internal format, facilitating direct manipulation of fixed-point values with explicit control.
- Comparison operators (`==`, `!=`, `<`, `>`, `<=`, `>=`) are marked as `constexpr`, `gnu::const`, and `gnu::always_inline`, optimizing for performance and inline expansion where supported.

