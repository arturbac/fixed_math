#pragma once

#include "../types.h"

namespace fixedmath::detail
  {
  using limits__ = std::numeric_limits<fixedmath::fixed_t>;
  using flimits__ = std::numeric_limits<float>;
  using dlimits__ = std::numeric_limits<double>;
  
  template<int digits>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_internal unsigned_shift_left_signed( fixed_internal value ) noexcept
    {
    using unsigned_internal = std::make_unsigned<fixed_internal>::type;
    return static_cast<fixed_internal>(
          (static_cast<unsigned_internal>( value ) << digits)
          | (static_cast<unsigned_internal>( value ) & ( unsigned_internal(1) << 63u))
      );
    }
  template<int digits>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_internal unsigned_shift_left_unsigned( fixed_internal value ) noexcept
    {
    using unsigned_internal = std::make_unsigned<fixed_internal>::type;
    return static_cast<fixed_internal>(
          (static_cast<unsigned_internal>( value ) << digits));
    }
    
  // concepts
  template<typename supported_type1, typename supported_type2>
  using arithmetic_and_one_is_fixed = typename std::integral_constant<bool,
                  is_arithemetic_t<supported_type1>::value && 
                  is_arithemetic_t<supported_type2>::value && 
                  ( is_fixed_t<supported_type1>::value || is_fixed_t<supported_type2>::value ) >::type;
                  
  ///\returns the highest power of 4 that is less than or equal to \param value
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_internal highest_pwr4_clz( fixed_internal value )
    {
    if( fixed_likely( value != 0 ) )
      {
      int clz{ cxx20::countl_zero( value ) };
      
      clz = (64 - clz);
      if( (clz & 1) == 0 )
        clz -= 1;

      return 1ll << (clz-1);
      }
    return 0;
    }
    
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_internal highest_pwr4( fixed_internal value )
    {
    // one starts at the highest power of four <= than the argument.
    fixed_internal pwr4 { 1ll << 62 }; // second-to-top bit set
    
    while (pwr4 > value)
      pwr4 >>= 2;
    return pwr4;
    }
    
  template<int precision>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_internal mul_( fixed_internal x, fixed_internal y ) 
    {
    return (x * y) >> precision;
    }
  template<int precision>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_internal div_( fixed_internal x, fixed_internal y ) 
    {
    return (x<<precision) / y;
    }
    
  template<int precision>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_internal fix_( fixed_internal x ) 
    {
    return (x<<precision);
    }
    
  constexpr fixed_t set_sign( bool sign_, fixed_internal result )
    {
    if(!sign_)
      return as_fixed(result);
    return as_fixed(-result);
    }
  }
