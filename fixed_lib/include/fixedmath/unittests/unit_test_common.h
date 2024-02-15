#pragma once

#include <fixedmath/limits.h>
#include <fixedmath/math.h>

namespace fixedmath
{
  using detail::limits_;
  using detail::flimits_;
  using detail::dlimits_;

  
  #define make_const_value(x) const_val<decltype(x), x>
  #define static_assert_equal(x, y) static_assert( assert_equal_t< make_const_value( x ), make_const_value( y ) >::eq() )

  template<typename T, T val>
  struct const_val {
      static constexpr T value { val };
      constexpr const_val() = default;
      constexpr const_val(T) {}
  };

  template<typename expected, typename input>
  constexpr bool test_resulting_type( input ) { return std::is_same<expected,input>::value; }
  
  //llvm11 libcxx is not constexpr ready
  template<typename value_type,
    typename = std::enable_if_t<detail::is_arithmetic_v<value_type>>>
  constexpr value_type ut_abs( value_type value ) 
    {
    static_assert( detail::is_arithmetic_v<value_type> );
    return value > value_type{0} ? value : -value;
    }
}
