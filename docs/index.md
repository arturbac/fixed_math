# FixedMath Library Reference

## Overview

The FixedMath library provides a comprehensive suite for fixed-point arithmetic operations, optimized for performance and precision. It includes basic arithmetic operations, trigonometric functions, conversion utilities, and more.

## Main Type

- [`struct fixed_t`](fixed_t.md): The main type used in calculations.

## Arithmetic Operations

### Negation

- `constexpr fixed_t operator -(fixed_t l) noexcept`: Negates a fixed number.

### Addition

See [documentation of addition](addition.md) for more details.

- `auto operator +(supported_type1 l, supported_type2 r) noexcept` : Operator overload for addition.
- `fixed_t &operator +=(fixed_t &l, supported_type r) noexcept`: Addition assignment.

### Subtraction

See [documentation of subtraction](subtraction.md) for more details.

- `auto operator -(supported_type1 l, supported_type2 r) noexcept`: Operator overload for subtraction.
- `fixed_t & operator -=(fixed_t &lh, supported_type rh) noexcept`: Subtraction assignment.

### Multiplication

See [documentation of multiplication](multiplication.md) for more details.

- `auto operator *(supported_type1 lh, supported_type2 rh) noexcept`: Operator overload for multiplication.
- `fixed_t & operator *=(fixed_t &lh, supported_type rh) noexcept`: Multiplication assignment.

### Division

See [documentation of division](division.md) for more details.

- `auto operator /(supported_type1 lh, supported_type2 rh) noexcept`: Operator overload for division.
- `fixed_t & operator /=(fixed_t &lh, supported_type rh) noexcept`: Division assignment.

### Modulo

- `auto operator %(supported_type1 lh, supported_type2 rh) noexcept`: Operator overload for modulo.
- `fixed_t & operator %=(fixed_t &lh, supported_type rh) noexcept`: modulo assignment.

## Bitwise Operations

See [documentation of bitwise operations](bitwise_operations.md) for more details.

- `fixed_t operator >>(fixed_t l, int r) noexcept`: Shifts right the value of `l` by `r` digits.
- `fixed_t operator <<(fixed_t l, int r) noexcept`: Shifts left the value of `l` by `r` digits.

## Conversion Operations

See [documentation of conversion between fixed and arithmetic types](conversion_between_fixed_and_arithmetic.md) for more details.

- `fixed_t arithmetic_to_fixed(arithmetic_type value) noexcept`: Converts any floating point or integral value into a fixed point.
- `arithmetic_type fixed_to_arithmetic(fixed_t value) noexcept`: Converts `fixed_t` into any floating point or integral type.

## Trigonometric Functions

- [`fixed_t sin(fixed_t rad) noexcept`](sine.md): Returns the sine of `rad` in radians.
- `fixed_t cos(fixed_t rad) noexcept`: Returns the cosine of `rad` in radians.
- `fixed_t tan(fixed_t rad) noexcept`: Returns the tangent of `rad`.
- `fixed_t asin(fixed_t x) noexcept`: Returns the arc sine of `x`.
- `fixed_t acos(fixed_t x) noexcept`: Returns the arc cosine of `x`.
- `fixed_t atan(fixed_t x) noexcept`: Returns the arc tangent of `x`.
- `fixed_t atan2(fixed_t y, fixed_t x) noexcept`: Returns the arc tangent of `y/x` using the signs of arguments to determine the correct quadrant.

## Utility Functions

- `fixed_t abs(fixed_t value) noexcept`: Returns the absolute value of `fixed_t`.
- `bool isnan(fixed_t value) noexcept`: Tests for NaN fixed. Returns true if `value` is NaN.
- `fixed_t ceil(fixed_t value) noexcept`: Returns the smallest integral value that is not less than `value`.
- `fixed_t floor(fixed_t value) noexcept`: Returns the largest integral value that is not greater than `value`.
- `fixed_t angle_to_radians(integral_type angle) noexcept`: Converts angle 0 - 360 to radians.
- `fixed_t sqrt(fixed_t value) noexcept`: Returns the square root of `value`.
- `fixed_t hypot(fixed_t lh, fixed_t rh) noexcept`: Returns the hypotenuse of `lh` and `rh`.
- `fixed_t fmod(fixed_t value) noexcept`: Returns the modulo of `value`.
- `from_string(std::string_view str) noexcept` : Returns `std::optional<fixed_t>` defined in `fixedmath/fixed_string.h`
- `to_string(fixed_t value, int precision) noexcept` : Returns `std::string` representation of fixed value defined in `fixedmath/fixed_string.h`
- `std::formatter<fixedmath::fixed_t>` defined in `fixedmath/std_formatter.h`
- `operator<<(std::ostream & outstr, fixed_t src)` defined in `fixedmath/iostream.h`
- `operator>>(std::istream & instr, fixed_t & dst)` defined in `fixedmath/iostream.h`

## FixedMath Applications and Use Cases

Explore the FixedMath [applications.](aplication.md)
