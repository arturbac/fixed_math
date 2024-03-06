## Multiplication in FixedMath

The FixedMath library provides detailed functionality for performing multiplication operations on fixed-point numbers (`fixed_t`), integrating precision management and type safety into its core design.

### Core Multiplication Functionality

- **`fixed_multiplyi(fixed_t lh, fixed_t rh) noexcept`**: Calculates the product of two `fixed_t` values. This function performs a preliminary check to ensure that the result is within the valid range, returning a NaN (`quiet_NaN_result()`) if it exceeds the permissible bounds.

### Safety Checks

- **`check_multiply_result(fixed_t result)`**: Validates the multiplication result to ensure it doesn't overflow. It checks if the result is within the limits defined by `fixed_internal(0x7fffffffffff0000ll)` and its negative counterpart.

### Template Specializations for Multiplication

- **`promoted_double_multiply(supported_type1 lh, supported_type2 rh) noexcept`**: For operations involving a `double`, this function promotes the `fixed_t` operand to double precision before multiplication, ensuring the operation is executed with double precision.

- **`promoted_fixed_multiply(supported_type1 lh, supported_type2 rh) noexcept`**: When both operands are of arithmetic types (with at least one being `fixed_t`), this function promotes them to `fixed_t` before performing the multiplication, ensuring type safety and precision.

- **`fixed_multiply_scalar(fixed_t lh, integral_type rh) noexcept` and its overload**: These functions specialize in multiplying a `fixed_t` value by an integral scalar, directly converting the scalar to a signed type to maintain precision.

### Multiplication Operator Overloads

- **Operator `*=`**: The `*=` operator modifies the left-hand operand (`fixed_t`) by multiplying it by the right-hand operand, which can be of any arithmetic type. This operator leverages `fixed_multiply` to perform the operation accurately.

- **Operator `*`**: Defines multiplication between two operands, potentially of different types. The result type is determined based on the operand types — it can either be `fixed_t` or `double`, ensuring that the operation's precision is optimized based on the context.

### Usage

```cpp
fixed_t a = ...; // Initialize with some value
fixed_t b = ...; // Initialize with another value

fixed_t result1 = a * b; // Multiplication of two fixed_t values

int scalar = 5;
fixed_t result2 = a * scalar; // Multiplication by an integral scalar

double d = 2.0;
auto result3 = a * d; // Multiplication with a double, result is promoted to double
```

