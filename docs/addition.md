## Addition in FixedMath

The FixedMath library meticulously handles the addition of fixed-point numbers (`fixed_t`), ensuring precision and correctness across various operations. This includes support for mixed-type arithmetic involving `fixed_t`, integers, and floating-point numbers.

### Core Addition Functionality

- **`fixed_additioni(fixed_t lh, fixed_t rh) noexcept`**: This function calculates the sum of two `fixed_t` values, employing checks to prevent overflow and underflow. If the sum exceeds the representable range, it returns NaN to signal an error in the operation.

### Type Promotion and Arithmetic

- **Promotion to Double**: For operations involving a double, the `fixed_t` value is promoted to double precision before the addition, ensuring that the operation leverages floating-point precision.
  
- **Promotion to Fixed**: If an arithmetic operation involves types other than `fixed_t`, the non-fixed type is promoted to `fixed_t` using `promote_to_fixed`, allowing the operation to proceed with fixed-point precision.

### Addition Operator Overloads

- **Operator `+=`**: Modifies the left-hand operand by adding the right-hand operand to it. The operand on the right can be any arithmetic type, and the operation is conducted with appropriate type promotions to maintain precision.

- **Operator `+`**: Defines addition between two operands of potentially mixed types. The result is either a `fixed_t` or a double, depending on whether any operand is a double, to ensure the operation's precision is optimized for the operand types.

### Specialized Addition Functions

- **`promoted_double_addition`**: Specifically handles addition where at least one of the operands is a double, promoting the operation to double precision.

- **`promoted_fixed_addition`**: Manages the addition of two arithmetic values, promoting them to `fixed_t` if necessary, to perform the operation within the fixed-point domain.

### Safety and Precision

The FixedMath addition operations are designed with an emphasis on safety, ensuring that any potential overflow or underflow conditions are handled gracefully, returning NaN where appropriate.

### Usage Example

```cpp
fixed_t a = ...; // Initialize with some value
fixed_t b = ...; // Another fixed_t value
fixed_t result = a + b; // Addition of two fixed_t values

int scalar = 5;
fixed_t result2 = a + scalar; // Addition with an integer scalar

double d = 2.0;
auto result3 = a + d; // Addition with a double, result is promoted to double
```

