![MIT](https://img.shields.io/badge/license-MIT-blue.svg) ![License](https://img.shields.io/badge/License-Boost%201.0-lightblue.svg) ![CMake](https://github.com/arturbac/fixed_math/workflows/CMake/badge.svg) ![language](https://img.shields.io/badge/language-C%2B%2B23-blue.svg)

# FixedMath

A comprehensive fixed-point math library written in C++23 and C++17, designed for high precision and efficiency.

## Major changes 12.08.2024
- master contains version 2.x rewritten in c++23
- branch 1.x contains stable c++17 which will be still maintained for compatibility and bugfixes
  
## Differences between 1.x branch and master branch ( version 2.x)
- version 2.x requires C++23 standard to compile while 1.x only C++17
- version 2.x version has both math functions avaiable as plain functions and as function objects, while 1.x only as plain functions
- version 2.x has much more constraints for validity of types checking at compile time compared to 1.x and exploits C++23 standard
- API is a bit different in version 2.x as plain functions in 2.x comapred to 1.x are defined in sub namespace `fixedmath::func` and function objects in sub namespace `fixedmath::fobj`,  however You can use `namesapce fixedmath{ using namesapce fixedmath::func; }` for getting backward compatibility.
- version 2.x is tested with every PR if it works with clang libstdc++, clang libc++, gcc, msvc, msvc clang-cl compilers
  
## Features

- **Modern C++ Standards**: Requires a minimum of C++23, (branch 1.x c++17) leveraging modern language features for optimal performance and reliability.
- **Strongly Typed Fixed-Point Arithmetic**: Utilizes a 48.16 fixed-point arithmetic model, ensuring type safety with explicit conversions and operations. The `fixed_t` type is robust against unintentional type conversions, fostering code correctness.
- **Implicit Type Promotion**: Supports implicit promotion of all arithmetic types (excluding `double`) to `fixed_t` in basic arithmetic operations, enhancing ease of use without sacrificing precision.
- **Double Precision Compatibility**: Interactions between `fixed_t` and `double` types automatically yield a `double` result type. Arithmetic operations involving `double` are seamlessly elevated to double precision, ensuring accuracy for critical calculations.
- **Compile-Time Evaluation**: The entire codebase, including trigonometric functions, is `constexpr`, enabling compile-time evaluations where applicable. This feature significantly reduces runtime overhead and allows for constant expressions.\[1\]
- **Header-Only Library**: As a fully header-only library with extensive use of `constexpr`, FixedMath simplifies integration into projects. Explore the API interface and implementation details: [API Reference](https://arturbac.github.io/fixed_math/) | [Implementation](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/math.h).
- **Compile-Time Unit Testing**: Offers a robust suite of compile-time unit tests, streamlining test-driven development and ensuring library correctness. Dive into the unit tests: [Compile-Time Unit Tests](https://github.com/arturbac/fixed_math/tree/master/fixed_lib/include/fixedmath/unittests).

FixedMath is committed to delivering precision, efficiency, and ease of use, making it an ideal choice for projects requiring fixed-point arithmetic in a modern C++ environment.

\[1\] The `sqrt` function is always available as `constexpr`, utilizing the Abacus algorithm for constant evaluation, alongside the standard `std::sqrt` for runtime execution. On windows msvc toolset (not clang-cl) still is not fully compatibile with c++23 and still has nonsense compiletime evaluation errors, [for example I had to split consteval function into constant](https://github.com/arturbac/fixed_math/blob/4f7b5f00b60dce007305d44ed4d2edb4ea98eb65/unit_tests/addition_ut.cc#L8) but this change does not has any sense.

### Performance Comparisons of Code Version 0.9.1

At this stage, the code has not been optimized, and the results presented below are based solely on initial implementations focused on code quality. The performance metrics indicate the relative computation times for executing functions across a large dataset of input values, without considering value conversions.

**Cortex-A73 - Snapdragon 865+**

| Tag   | Function | Fixed (Clang) | Fixed (GCC) | Float  | Double | Status    |
|-------|----------|---------------|-------------|--------|--------|-----------|
| 0.9.1 | sin      | 50 ms         | -           | 31 ms  | 77 ms  | -         |
| 0.9.4 | sin      | 30 ms         | 24 ms       | 31 ms  | 77 ms  | Optimized |
| 0.9.1 | asin     | 124 ms        | -           | 75 ms  | 128 ms | -         |
| 0.9.4 | asin     | 63 ms         | 54 ms       | 75 ms  | 127 ms | Optimized |
| 0.9.1 | tan      | 136 ms        | -           | 104 ms | 206 ms | -         |
| 0.9.4 | tan      | 136 ms        | 130 ms      | 104 ms | 206 ms | -         |
| 0.9.1 | atan     | 113 ms        | -           | 110 ms | 165 ms | -         |
| 0.9.5 | atan     | 80 ms         | 65 ms       | 110 ms | 165 ms | Optimized |

**Ryzen 9 - 3900X**

| Tag   | Function | Fixed (Clang) | Fixed (GCC) | Float | Double | Status    |
|-------|----------|---------------|-------------|-------|--------|-----------|
| 0.9.1 | sin      | 27 ms         | -           | 22 ms | 75 ms  | -         |
| 0.9.4 | sin      | 20 ms         | 18 ms       | 21 ms | 74 ms  | Optimized |
| 0.9.1 | asin     | 92 ms         | -           | 58 ms | 106 ms | -         |
| 0.9.4 | asin     | 49 ms         | 44 ms       | 57 ms | 104 ms | Optimized |
| 0.9.1 | tan      | 81 ms         | -           | 66 ms | 180 ms | -         |
| 0.9.4 | tan      | 78 ms         | 88 ms       | 67 ms | 176 ms | -         |
| 0.9.1 | atan     | 90 ms         | -           | 78 ms | 162 ms | -         |
| 0.9.5 | atan     | 64 ms         | 55 ms       | 77 ms | 161 ms | Optimized |


## Installation

This library is predominantly header-only, with the exception of tabularized trigonometric functions. Therefore, if you require only the precise trigonometric functions, there is no need for compilation. Simply add `fixed_lib/include` to your include path and use `#include <fixedmath/fixed_math.hpp>` in your code.

For access to additional, approximate trigonometric functions, the library should be compiled like any standard CMake project. Currently, the project does not offer any specific tuning parameters for CMake.

### Integrating FixedMath into Your Project Using CPM

For projects utilizing CPM (CMake Package Manager) for dependency management, you can easily integrate FixedMath by adding the following lines to your `CMakeLists.txt`:

```cmake
CPMAddPackage(
  NAME fixed_math
  GITHUB_REPOSITORY arturbac/fixed_math
  GIT_TAG        v2.0.0
)

find_package(fixed_math REQUIRED)
# optional PCH
target_precompile_headers( fixed_math INTERFACE <fixedmath/fixed_math.hpp>)

```

## C++ Compilers Compatibility

The following compilers are confirmed to compile the project in branches

### version 2.x with C++23 standard, master development branch.
- Clang version 18.0.1 with llvm-libcxx on Gentoo x86-64
- Clang version 18.0.1 with gcc-libstdc++ 14.1.1 on Gentoo x86-64
- Clang version 18 on ubuntu-24.04
- GCC 14.1.1_p20240720 p4 on Gentoo x86-64
- GCC 14.0.1 on ubuntu-24.04 
- MSVC ClanCL-toolset 17.0.3 from MSVC 19.40.33813.0
- MSVC toolset 19.40.33813.0

  
### version 1.x with C++17 standard on stable 1.x branch
- Clang 18.0.1 with llvm-libcxx on Gentoo x86-64
- Clang 17.0.6 with llvm-libcxx on Gentoo x86-64
- Clang 13.0.0 with llvm-libcxx on Gentoo x86-64
- Clang 13.0.0 with gcc-libstdc++ 11.2.1 on Gentoo x86-64
- Clang 12.0.1 with llvm-libcxx on FreeBSD 13 x86-64
- Clang 11.0.1 with gcc-libstdc++ 10.2.0 on Gentoo Linux x86-64 and aarch64
- Clang 11.0.1 with llvm-libcxx on x86-64
- Clang 10.0.1 with llvm-libcxx on FreeBSD 13 x86-64
- GCC 14.1.1_p20240720 p4 on Gentoo x86-64
- GCC 13.2.1_p20240210 p13 on Gentoo x86-64
- GCC 12.3.1_p20240209 p2 on Gentoo x86-64
- GCC 11.2.1 20211127 on Gentoo x86-64
- GCC 10.2.0 on x86-64 on Gentoo x86-64
- GCC 9.4.0 on Gentoo x86-64
- MSVC 19 (Visual Studio 2019) support

If you encounter any issues, please report it by submitting an issue.
 
## Usage

`fixed_t` serves as the typename for the fixed-point arithmetic type within this library, supporting common operators such as `+`, `-`, `*`, and more. 


### example

```C++
#include <fixedmath/fixed_math.hpp>
#include <fixedmath/iostream.h>

using fixedmath::fixed_t;
using fixedmath::operator""_fix;

// fixed and all functionality is constexpr so You can declare constants see features [1]
inline constexpr fixed_t foo_constant{fixedmath::tan(15 * fixedmath::phi / 180)};

constexpr fixed_t my_function(fixed_t value)
  {
  using namespace fixedmath;
  return foo_constant + sin(value) / (1.41_fix - 2 * cos(value) / 4);
  }

int main()
  {
  // converting to/from fixed_t
  // construction from other arithmetic types is explicit
  fixed_t val1{3.14};
  fixed_t val2{3u};

  //- there is no implicit assignment from other types
  float some_float{3.14f};
  fixed_t some_fixed;
  some_fixed = fixed_t{some_float};

  //- converting to other arithmetic types coud be done with static cast and is explicit
  double some_double(some_fixed);

  // for constant values postfix operator _fix may be used
  some_fixed = some_float * 2.45_fix;  // operation with float is promoted to fixed_t
  some_double = 4.15 * some_fixed;     // operation with double is promoted to double

  std::cout << some_double << " " << my_function(some_fixed) << std::endl;
  }
```
## Unit Tests

To execute the unit tests, simply `#include <fixedmath/unittests/compile_time_unit_tests.h>` in any source file of your project. This enables you to validate the functionality at compile time, ensuring the library's reliability.

Alternatively, unit tests can be executed using CMake/CTest with clang. Run `ninja test` or `make test` commands, depending on your build system, as the tests are included in the default CMake configuration of the source folder. To enable or disable this feature, modify the `FIXEDMATH_ENABLE_UNIT_TESTS` option in the `CMakeLists.txt` file.

This flexible testing approach ensures that you can easily integrate and verify the functionality of the library within your development workflow.



## Version 1.0 Goals Status

The development of version 1.0 focused on establishing a robust foundation for fixed-point arithmetic operations, with significant achievements as outlined below:

- [x] Basic arithmetic operations have been successfully implemented.
- [x] Square root calculation using the abacus algorithm and CLZ (Count Leading Zeros), which is supported on x86, ARMv6, and newer, and AArch64 architectures. The approximation error is approximately <= 0.000015.
- [x] Hypotenuse function (`hypot`) implemented with normalization to prevent overflow and underflow.
- [x] Sine and cosine functions with an error margin of approximately <= 0.0001.
- [x] Tangent function accuracy within |x| <= PI/4 is approximately <= 0.0001. For PI/4 < |x| <= PI/2, the error is <= 0.001, except near 90 degrees where it is <= 0.01.
- [x] Improvements to tangent calculations to limit the domain to |x|<=pi/4.
- [x] Inverse tangent functions (`atan`, `atan2`) with an error margin of approximately <= 0.00005.
- [x] Arcsine function (`asin`) accuracy of approximately <= 0.0001.
- [x] Compatibility with Clang and GCC C++17 compilers confirmed.
- [x] Partial support for MSVC C++17 compiler; refer to "C++ Compilers" notes for details on compiler compatibility.
- [x] Performance comparisons conducted between ARM64 and x86 architectures, demonstrating parity with float/double arithmetic.
- [x] The project is dual-licensed under the MIT License and the Boost Software License, offering flexibility in usage and distribution.

## Future Goals

Looking forward, the project aims to expand its offerings and improve in several key areas:

- [ ] Expand mathematical functionality based on user needs. If there's something missing that you need, please post an issue to let us know.
- [ ] Increase the number of unit tests to cover more scenarios and ensure robustness.
- [ ] Pursue further optimizations and enhancements to calculation quality, striving for even higher accuracy and efficiency.


## Feedback

Should you encounter any bugs, we encourage you to file an issue through our issue submission [form](https://github.com/arturbac/fixed_math/issues). When reporting a bug, please include sufficient information for reproduction, such as a `static_assert(expression)`, along with the compiler version and target architecture if pertinent. We welcome feature requests and contributions; these can be submitted either as issues or pull requests.

## License

The library is freely available to everyone under the terms of the MIT License or the Boost Software License - Version 1.0. For more details, please refer to the LICENSE.md file.

