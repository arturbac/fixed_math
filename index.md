## fixedmath

written from scratch fixed point math library in C++17


## features

* fixed point 48.16 arithmethic strong type without implicit convertions with assignment and construction, fixed type is safe against unwanted type convertions
* all arithemtic types like float and integral types except double implicitly in base arithemitc operations are promoted to fixed_t
* all arithmetic operations of fixed_t with double type yelds double result type, are promoted and evaluated as double operations
* entire code including trigonometry functions is constexpr \[1\]
* fully header only library as everything is constexpr, see api interface [api](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/fixed_math.hpp) and [implementation](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/math.h)
* unit tests can be checked at compilation time just including header, see [unittests](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/compile_time_unit_tests.h)


\[1\] - By default is used std:sqrt as current cpu's has hardware support for sqrt, but constexpr abacus algorithm could be used defining FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO, which is slower than cpu one


## c++ compilers

Thise are known to compile without errors, if You found any problem with c++17 compiler let me know and post issue as stl shoudn't be a problem
 - clang version 11.0.1 + gcc-libstdc++ 10.2.0 \(main development platform\) on x86-64 and aarch64
 - clang version 11.0.1 + llvm-libcxx on x86-64
 - gcc 10.2.0 on x86-64
 - clang version 10.0.1 x86-64 + gcc-libstdc++ 10.2.0
 
 ### example

```C++
#include <fixedmath/fixed_math.hpp>

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

```
