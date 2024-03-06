
## Conversion between Fixed and Arithmetic Types in FixedMath

The FixedMath library provides seamless conversion mechanisms between fixed-point numbers (`fixed_t`) and standard arithmetic types (integers and floating-point numbers). These conversions ensure that fixed-point arithmetic integrates well with the broader C++ type system, allowing for efficient and type-safe operations across different numeric types.

### Conversion from `fixed_t` to Arithmetic Types

- **`fixed_to_arithmetic<arithmetic_type>(fixed_t value) noexcept`**: Converts a `fixed_t` value to a specified arithmetic type (`arithmetic_type`). The function discriminates between integral and floating-point types, using the most appropriate conversion method for each case:
  - For integral types, it converts the `fixed_t` value to the corresponding integral conversion.
  - For floating-point types, it converts the `fixed_t` value to the corresponding floating-point conversion.

- **`fixed_t::operator arithmetic_type() const noexcept`**: A type conversion operator that allows a `fixed_t` object to be automatically converted to an arithmetic type when required. This leverages the `fixed_to_arithmetic` template function internally to perform the conversion.

### Conversion from Arithmetic Types to `fixed_t`

- **`arithmetic_to_fixed<arithmetic_type>(arithmetic_type value) noexcept`**: Provides a clear interface for converting arithmetic types to `fixed_t`.

### Examples of Use

Conversion from `fixed_t` to arithmetic types:

```cpp
fixed_t fixedValue = 2.5_fix; // Initialize with some fixed-point value

// Convert to an integer
int intValue = fixed_to_arithmetic<int>(fixedValue);

// Convert to a floating-point
double doubleValue = fixedValue; // Implicitly uses fixed_t::operator double() const
```

Conversion from arithmetic types to `fixed_t`:

```cpp
int intInput = 5;
// Convert from integer to fixed_t
fixed_t fixedFromInt = arithmetic_to_fixed(intInput);

double doubleInput = 2.5;
// Convert from floating-point to fixed_t
fixed_t fixedFromDouble = arithmetic_to_fixed(doubleInput);

fixedFromDouble = static_cast<double>(arithmetic_to_fixed(doubleInput));
```

These conversion functions and operators ensure that working with fixed-point numbers in a mixed arithmetic context is both natural and efficient, maintaining type safety and precision across conversions.
