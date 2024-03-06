
## Subtraction in FixedMath

The FixedMath library precisely manages the subtraction of fixed-point numbers (`fixed_t`), ensuring accuracy and robustness across various operations. This includes support for mixed-type arithmetic involving `fixed_t`, integers, and floating-point numbers.

### Core Subtraction Functionality

- **`fixed_substracti(fixed_t lh, fixed_t rh) noexcept`**: This function computes the difference between two `fixed_t` values, incorporating checks to prevent anomalous results. It returns NaN to indicate an error when the operation results in an overflow or underflow, especially when subtracting values across different signs that should normally produce a valid range but don't due to fixed-point constraints.

### Type Promotion and Arithmetic

- **Promotion to Double**: For operations that involve a double, the `fixed_t` value is promoted to double precision prior to subtraction, ensuring the operation benefits from the precision of floating-point arithmetic.

- **Promotion to Fixed**: When an arithmetic operation includes types other than `fixed_t`, the non-fixed type is elevated to `fixed_t` using `promote_to_fixed`. This enables the operation to proceed with fixed-point accuracy.

### Subtraction Operator Overloads

- **Operator `-=`**: Adjusts the left-hand operand by subtracting the right-hand operand from it. The right operand can be any arithmetic type, with the operation performed after suitable type promotions to ensure accuracy.

- **Operator `-`**: Implements subtraction between two operands of potentially mixed types. The outcome is either a `fixed_t` or a double, depending on whether any of the operands is a double, to optimize the operation's precision for the given operand types.

### Specialized Subtraction Functions

- **`promoted_double_substract`**: Specially caters to subtraction operations where at least one of the operands is a double, elevating the operation to double precision.

- **`promoted_fixed_substract`**: Facilitates the subtraction of two arithmetic values, promoting them to `fixed_t` as necessary, to ensure the operation is executed within the fixed-point realm.

### Safety and Precision

Subtraction operations in the FixedMath library are crafted with a focus on safety, ensuring that conditions like potential overflows or underflows are managed adeptly, returning NaN in situations where accurate results cannot be guaranteed.

### Usage Example

```cpp
fixed_t a = ...; // Initialize with some value
fixed_t b = ...; // Another fixed_t value
fixed_t result = a - b; // Subtraction of two fixed_t values

int scalar = 5;
fixed_t result2 = a - scalar; // Subtraction with an integer scalar

double d = 2.0;
auto result3 = a - d; // Subtraction with a double, result is promoted to double
```
