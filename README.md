# fixed_math ![MIT](https://img.shields.io/badge/license-MIT-blue.svg) ![License](https://img.shields.io/badge/License-Boost%201.0-lightblue.svg) ![CMake](https://github.com/arturbac/fixed_math/workflows/CMake/badge.svg) ![language](https://img.shields.io/badge/language-C%2B%2B17-blue.svg)

written from scratch fixed point math library in C++17

## features

* minimum c++17 compiler required
* fixed point 48.16 arithmethic strong type without implicit convertions with assignment and construction, fixed type is safe against unwanted type convertions
* all arithemtic types like float and integral types except double implicitly in base arithemitc operations are promoted to fixed_t
* all arithmetic operations of fixed_t with double type yelds double result type, are promoted and evaluated as double operations
* entire code including trigonometry functions is constexpr \[1\]
* fully header only library as everything is constexpr, see api interface [api](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/fixed_math.hpp) and [implementation](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/math.h)
* unit tests can be checked at compilation time just including header, see [unittests](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/compile_time_unit_tests.h)


\[1\] - By default is used std:sqrt as current cpu's has hardware support for sqrt, but constexpr abacus algorithm could be used defining FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO, which is slower than cpu one.

### performance comparisions of code 0.9.1
At this point code wasn't been optimised, so results are from just from code written with quality only at this point in mind. Results are relative times of computing functions over bigtable of source values in function type (no value convertions)

**Cortex-A73 - Snapdragon 865+**
tag | function | fixed clang | fixed gcc | float | double | status
------|-----|-------|-|------|--------|----
0.9.1 | sin | 50 ms | | 31 ms | 77 ms
0.9.4 | sin | 30 ms | 24ms |  31 ms | 77 ms | optimized
0.9.1 | asin | 124 ms | |  75 ms | 128 ms 
0.9.4 | asin | 63 ms | 54 ms | 75 ms | 127 ms  | optimized
0.9.1 | tan | 136 ms | |  104 ms | 206 ms 
0.9.4 | tan | 136 ms | 130 ms |  104 ms | 206 ms 
0.9.1 | atan | 113 ms | |  110 ms | 165 ms
0.9.5 | atan | 80 ms | 65 ms | 110 ms | 165 ms | optimized

**Ryzen 9 - 3900X**
tag | function | fixed clang | fixed gcc | float | double | status
----|-----|-------|-----|--|------------|------
0.9.1 | sin | 27 ms | | 22 ms | 75 ms |
0.9.4 | sin | 20 ms | 18ms | 21 ms | 74 ms | optimized
0.9.1 | asin | 92 ms | | 58 ms | 106 ms |
0.9.4 | asin | 49 ms | 44 ms| 57 ms | 104 ms  | optimized
0.9.1 | tan | 81 ms | | 66 ms | 180 ms |
0.9.4 | tan | 78 ms | 88 ms | 67 ms | 176 ms |
0.9.1 | atan | 90 ms | | 78 ms | 162 ms |
0.9.5 | atan | 64 ms | 55ms | 77 ms | 161 ms  | optimized

## installation

this library is header only except tabelarized trigonometric functions. So If you can use precise trigonometric functions You don't have to build anything.
Just add fixed_lib/include to include path and #include <fixedmath/fixed_math.hpp>. If you want additional inprecise aproxymated functions compile project like any other ordinary CMake project. At this point it doesn't have any tuning parameters for CMake.

## c++ compilers

Thise are known to compile without errors, if You found any problem with c++17 compiler let me know and post issue as stl shoudn't be a problem
 - clang version 13.0.0 + llvm-libcxx on gentoo x86-64
 - clang version 13.0.0 + gcc-libstdc++ 11.2.1 on gentoo x86-64
 - clang version 12.0.1 + llvm-libcxx on freebsd 13 x86-64
 - clang version 11.0.1 + gcc-libstdc++ 10.2.0 on gentoo linux x86-64 and aarch64
 - clang version 11.0.1 + llvm-libcxx on x86-64
 - clang version 10.0.1 + llvm-libcxx on freebsd 13 x86-64
 - gcc version 11.2.1 20211127 on gentoo x86-64
 - gcc 10.2.0 on x86-64 on gentoo x86-64
 - gcc 9.4.0 on gentoo x86-64
 - msvc19 support
 
 \*  msvc problems
  - constexpresions evaulated at compile time may cause compiler crash like one below in code block.
  - there is no eficient easy way to calculate clz at compile timeand runtime with single code  with c++17.There is implementation of countl_zero in msvc c++20 witch is supported.
  
  ```
  1>D:\projects\fixed_math\fixed_lib\include\fixedmath\unittests\addition.h(19,43): fatal error C1001: Wewnętrzny błšd kompilatora.
  1 > (plik kompilatora d : \A01\_work\2\s\src\vctools\Compiler\CxxFE\sl\p1\c\constexpr\constexpr.cpp, wiersz 6887)
  ```
## usage
fixed_t is typename of fixed point arithmetic type with common operators like, +, -, * ..

### example

```C++
#include <fixedmath/fixed_math.hpp>
#include <fixedmath/iostream.h>

using fixedmath::fixed_t;

//fixed and all functionality is constexpr so You can declare constants see features [1]
inline constexpr fixed_t foo_constant{ fixedmath::tan( 15 * fixedmath::phi/180) };

constexpr fixed_t my_function( fixed_t value )
 {
 using namespace fixedmath;
 return foo_constant + sin(value) / (1.41_fix - 2*cos(value) / 4);
 }

// converting to/from fixed_t
// construction from other arithmetic types is explicit
fixed_t val { 3.14 };
fixed_t val { 3u };
 
//- there is no implicit assignment from other types
float some_float{};
fixed_t some_fixed{};
...
some_fixed = fixed_t{some_float};
 
//- converting to other arithmetic types coud be done with static cast and is explicit
double some_double { static_cast<double>(some_fixed) };
 
// for constant values postfix operator _fix may be used
some_fixed = some_float * 2.45_fix; //operation with float is promoted to fixed_t
some_double = 4.15 * some_fixed; //operation with double is promoted to double

std::cout << some_fixed;

```
## unit tests

To check unit tests just #include <fixedmath/unittests/compile_time_unit_tests.h> in any of Your source file.
or run them wit CMake/CTest "ninja/make test" as they are available in default CMakeConfiguration of source folder see ENABLE_UNIT_TESTS cmake feature i CMakeLists.txt


## version 1.0 goals status

- [x] base arithemtic operations 
- [x] sqrt - abacus algorithm using CLZ ( CLZ is available on x86 and >=armv6, aarch64)  error ~<= 0.000015
- [x] hypot - with normalization to suitable range, to avoid overflow and underflow
- [x] sin, cos - error ~<= 0.0001
- [x] tan - error on normalized range |x| <= PI/4 ~<= 0.0001, PI/4 |x| <= PI/2 ~<=0.001 exept near 90deg ~<= 0.01
- [x] tan - improve calculations, limit tan__ to |x|<=pi/4
- [x] atan, atan2 - error  ~<= 0.00005
- [x] asin error  ~<= 0.0001
- [x] support clang, gcc c++17 compilers
- [x] support msvc c++17 compiler, partial see notes for compilers tested in \"c++ compilers\"
- [x] performance comparisions on arm64 and x86 with float/double arithemetic
- [x] dual licence project with MIT Licence and Boost Software License

## release notes
### version 0.9.10
  - improved unit testing dual c++17 and c++20
  - rewrite of static asserts to function concept restrictions with std::enable_if_t
  
## future goals

- [    ] more math functionality, if somthing is missing in library that You need post issue and let me know about that.
- [    ] more unit tests
- [    ] more optimisations, calculation quality enchacments

## Feedback

If you think you have found a bug, please file an issue via issue submission [form](https://github.com/arturbac/fixed_math/issues). Include the relevant information to reproduce the bug for example as static_assert( expression ), if it is important also the compiler version and target architecture. Feature requests and contributions can be filed as issues or pull requests.

## Licence

This library is available to anybody free of charge, under the terms of MIT License or Boost Software License - Version 1.0 (see LICENSE.md).
