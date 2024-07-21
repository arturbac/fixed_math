#pragma once

#include <fixedmath/limits.h>
#include <fixedmath/core_ops.h>

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
      consteval const_val() = default;
      consteval const_val(T) {}
  };

  template<typename expected, typename input>
  consteval bool test_resulting_type( input ) { return std::is_same<expected,input>::value; }
  
  template<concepts::arithmetic value_type>
  consteval value_type ut_abs( value_type value ) 
    {
    return value > value_type{0} ? value : -value;
    }
}
