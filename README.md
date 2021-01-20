# fixed_math ![MIT](https://img.shields.io/badge/license-MIT-blue.svg)

written from scratch fixed point math library in C++17

## features

* minimum c++17 compiler required
* fixed point 48.16 arithmethic strong type without implicit convertions with assignment and construction, fixed type is safe against unwanted type convertions
* all arithemtic types like float and integral types except double implicitly in base arithemitc operations are promoted to fixed_t
* all arithmetic operations of fixed_t with double type yelds double result type, are promoted and evaluated as double operations
* entire code including trigonometry functions is constexpr
* fully header only library as everything is constexpr, see api interface [api](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixed_math.hpp) and [implementation](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/math.h)
* unit tests are checked always during compilation time, see [unittests](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/compile_time_unit_tests.h)
* functions that are complement to std math functionality are available in std namespace as overloads for fixed_t type

## version 1.0 Goals status

- [x] base arithemtic operations 
- [x] sqrt - abacus algorithm using CLZ ( CLZ is available on x86 and >=armv6, aarch64)  error ~<= 0.000015
- [x] hypot - with normalization to suitable range, to avoid overflow and underflow
- [x] sin, cos - error ~<= 0.0001
- [    ] tan - error on normalized range |x| <= PI/4 ~<= 0.0001, PI/4 |x| <= PI/2 ~<=0.001 exept near 90deg ~<= 0.01
- [x] tan - improve calculations, limit tan__ to |x|<=pi/4
- [x] atan, atan2 - error  ~<= 0.000035
- [x] asin error  ~<= 0.0001
- [    ] remove all old compat code that is compiled
- [    ] cover all functionality with static_assert unit tests

## future Goals

- [    ] more math functionality
- [    ] performance comparisions on arm64 and x86 with float/double arithemetic
- [    ] more optimisations, calculation quality enchacments

## Feedback

If you think you have found a bug, please file an issue via issue submission [form](https://github.com/arturbac/fixed_math/issues). Include the relevant information to reproduce the bug for example as static_assert( expression ), if it is important also the compiler version and target architecture. Feature requests and contributions can be filed as issues or pull requests.

## License

This library is available to anybody free of charge, under the terms of MIT License (see LICENSE.md).
