#pragma once

#include "../types.h"

#define FIXEDMATH_PUBLIC gnu::visibility("default")

#if defined(__GNUC__) || defined(__clang__)
  #define fixed_likely(x)    __builtin_expect(static_cast<bool>(x), 1)
  #define fixed_unlikely(x)  __builtin_expect(static_cast<bool>(x), 0)
#else
  #define fixed_likely(x)    ((x))
  #define fixed_unlikely(x)  ((x))
#endif

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
    
  template<int size>
  struct signed_type_by_size {};
  
  template<>
  struct signed_type_by_size<1> { using type = int8_t; };
  
  template<>
  struct signed_type_by_size<2> { using type = int16_t; };
  
  template<>
  struct signed_type_by_size<4> { using type = int32_t; };
  
  template<>
  struct signed_type_by_size<8> { using type = int64_t; };
  
  template<>
  struct signed_type_by_size<16> { using type = int64_t; };
  
  template<typename value_type>
  constexpr auto promote_type_to_signed( value_type value )
    {
    if constexpr ( std::is_signed_v<value_type> )
      return value;
    else
      {
      using signed_type = typename signed_type_by_size<((sizeof(value_type)<<1))>::type;
      return static_cast<signed_type>( value );
      }
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

  template<typename supported_type>
  using is_fixed = typename std::integral_constant<bool,std::is_same<cxx20::remove_cvref_t<supported_type>,fixed_t>::value>::type;
  
  template<typename supported_type>
  using is_double = typename std::integral_constant<bool,std::is_same<cxx20::remove_cvref_t<supported_type>,double>::value>::type;
  
  template<typename supported_type>
  using is_integral = typename std::integral_constant<bool,std::is_integral<cxx20::remove_cvref_t<supported_type>>::value>::type;
  
  template<typename supported_type>
  using is_floating_point = std::is_floating_point<supported_type>;
    
  template<typename supported_type>
  using is_arithemetic = typename std::integral_constant<bool,
                  (std::is_integral<supported_type>::value) 
                  || (std::is_floating_point<supported_type>::value)
                  || is_fixed<supported_type>{}
                    >::type;
  
  template<typename supported_type>
  using is_arithmetic_and_not_fixed_v = typename std::integral_constant<bool,
                  is_arithemetic<supported_type>{} && (!is_fixed<supported_type>{})>::type;
                  
  template<typename supported_type1, typename supported_type2>
  using arithmetic_and_one_is_fixed = typename std::integral_constant<bool,
                  is_arithemetic<supported_type1>{} && 
                  is_arithemetic<supported_type2>{} && 
                  ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} ) >::type;
                  
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
