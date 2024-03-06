## Division Operator `/` in FixedMath

The FixedMath library provides comprehensive support for division operations among fixed-point numbers (`fixed_t`), integral types, and floating-point numbers with an emphasis on safety, efficiency, and precision.

### Core Division Functionality

- **`fixed_divisionf(fixed_t x, fixed_t y) noexcept`**: Performs division between two `fixed_t` values. This function ensures that division by zero is handled gracefully, returning a NaN (`quiet_NaN_result()`) in such cases. The division result is left-shifted by 16 bits to maintain fixed-point precision.

### Safety Checks

- **`check_division_result(fixed_t result)`**: Validates that the division result is within the permissible range to prevent overflow. This check is currently commented out but can be enabled as needed to ensure result integrity.

### Template Specializations for Division

- **`promoted_fixed_division(supported_type1 lh, supported_type2 rh) noexcept`**: Facilitates division where at least one of the operands is a `fixed_t` type. The other operand is implicitly promoted to `fixed_t` for the operation.

- **`promoted_double_division(supported_type1 lh, supported_type2 rh) noexcept`**: When one of the operands is a `double` and the other is compatible with `fixed_t`, the division operation is performed in double precision. This ensures that the operation's precision is maximized.

- **`fixed_division_by_scalar(fixed_t lh, integral_type rh) noexcept`**: Specializes division operations where the `fixed_t` value is divided by an integral scalar. This function maintains the precision of `fixed_t` while ensuring efficient computation.

### Division Operator Overloads

- **Operator `/=`**: The `/=` operator modifies the left-hand operand by dividing it by the right-hand operand, which can be of any arithmetic type. This operator uses `fixed_division` internally to determine the most appropriate division operation based on the operand types.

- **Operator `/`**: Defines division between two operands of potentially mixed types (one of which must be `fixed_t`). The result type is determined based on the operand types — it could either be `fixed_t` or `double`.

### Usage

```cpp
fixed_t a = ...; // Initialize with some value
fixed_t b = ...; // Initialize with another value

fixed_t result1 = a / b; // Division of two fixed_t values

int scalar = 5;
fixed_t result2 = a / scalar; // Division by an integral scalar

double d = 2.0;
auto result3 = a / d; // Division with a double, result is promoted to double
```

