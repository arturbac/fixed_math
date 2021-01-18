# fixed_math 
written from scratch fixed point math library in C++17 as replacment to 20 years old code written in c++98 
stil under development
## features
* minimum c++17 compiler required
* fixed point 48.16 aritmethic strong type without implicit converions with assigment and construction
* all arithemtic types like float, integral types except double implicitly in base arithemitc operations are promoted to fixed_t
* all arithmetic operations of fixed_t with double type of some variables yealds double result type, are promoted to double operations
* entire code including trigonometry functions code is constexpr
* fully header only as everything is constexpr api interface, see [api](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixed_math.hpp) and [implementation](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/math.h)
* unit tests are checked always during compilation time, see [unittests](https://github.com/arturbac/fixed_math/blob/master/fixed_lib/include/fixedmath/compile_time_unit_tests.h)

## goals status
- [x] base arithemtic operations 
- [x] sqrt - abacus algorithm using CLZ (avail on x86 and >=armv6, aarch64)  error ~<= 0.000015
- [    ] hypot - partialy done, needs x,y normalization to suitable range, to avoid overflow and underflow
- [x] sin, cos - error ~<= 0.0001
- [x] tan - error on range -Pi/2 .. PI/2 ~<= 0.001
- [x] atan, atan2 - error  ~<= 0.000035
- [    ] asin - partialy done needs better aproxymation near x=1
