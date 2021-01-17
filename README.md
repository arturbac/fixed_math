# fixed_math 
written from scratch fixed point math library in C++17 as replacment to 20 years old code written in c++98 
stil under development
## features
* minimum c++17 compiler required
* fixed point 48.16 aritmethic strong type without implicit converions with assigment and construction
* all arithemtic types like float, integral types except double implicitly in base arithemitc operations are promoted to fixed_t
* all arithmetic operations of fixed_t with double type of some variables yealds double result type, are promoted to double operations
* entire code including trigonometry functions code is constexpr
* fully header only as everything is constexpr
* unit tests are checked always during compilation time
