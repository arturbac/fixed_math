
## Bitwise Operations in FixedMath

The FixedMath library includes support for bitwise operations on fixed-point numbers (`fixed_t`), carefully implemented to preserve the integrity of fixed-point arithmetic while providing essential functionality.

### Right Shift Operator

- **`operator >> (fixed_t l, int r) noexcept`**: This function applies the bitwise right shift operation to a `fixed_t` value. If the shift count `r` is non-negative, the function performs the shift operation and returns the result. If `r` is negative, it returns NaN to indicate an invalid operation. This ensures that the operation only proceeds under valid conditions.

### Left Shift Operator

- **`operator << (fixed_t l, int r) noexcept`**: The bitwise left shift operation is more complex due to the need to handle the sign bit correctly in a fixed-point context. If the shift count `r` is non-negative, it performs the shift while maintaining the sign bit of the original value. This is achieved by:
  - Shifting the unsigned representation of the value left by `r` bits.
  - Clearing any bits that overflow into the sign bit area to avoid corrupting the sign.
  - Preserving the original sign bit of the `fixed_t` value.

### Safety and Correctness

Both operators incorporate checks to ensure that shift operations are only performed with non-negative shift counts, adhering to the principles of safety and precision that characterize fixed-point arithmetic in the FixedMath library. This approach prevents undefined or unexpected behavior that could arise from attempting to shift by negative counts or risking overflow/underflow conditions.

### Usage Example

```cpp
fixed_t a = ...; // Initialize with some value

// Right shift operation
fixed_t result_right_shift = a >> 2; // Shifts `a` right by 2 bits

// Left shift operation
fixed_t result_left_shift = a << 3; // Shifts `a` left by 3 bits, maintaining the sign bit
```

### Note on Bitwise Operations

While bitwise operations on fixed-point numbers can be useful, it's essential to use them judiciously, especially considering the potential for altering the numeric value in ways that are not directly analogous to integer arithmetic due to the fixed-point representation.
