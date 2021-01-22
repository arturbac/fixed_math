#pragma once

#include <fixedmath/limits.h>
#include <fixedmath/math.h>

namespace fixedmath
{
  using detail::limits__;
  using detail::flimits__;
  using detail::dlimits__;

  
  #define make_const_value(x) const_val<decltype(x), x>
  #define static_assert_equal(x, y) static_assert( assert_equal_t< make_const_value( x ), make_const_value( y ) >::eq() )

  template<typename T, T val>
  struct const_val {
      static constexpr T value { val };
      constexpr const_val() = default;
      constexpr const_val(T) {}
  };


  template<typename T, typename U>
  struct assert_equal_t 
    {
    static constexpr bool eq()
      { return assert_equal_t<decltype(T::value), decltype(U::value)>::eq( T::value, U::value ); }
      
    static constexpr bool eq( T lh, U rh )
      {
  //       static_assert( lh == rh );
      return lh == rh;
      }
    static constexpr bool value { T::value == U::value };
    };
    
  template<typename expected, typename input>
  constexpr bool test_resulting_type( input ) { return std::is_same<expected,input>::value; }
  
}
