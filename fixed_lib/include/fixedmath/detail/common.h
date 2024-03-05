#pragma once

#include "../types.h"
#include <type_traits>

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
    
  template<typename value_type,
    typename = std::enable_if_t<is_integral_v<value_type>
                              && is_unsigned_v<value_type>>
    >
  [[nodiscard, gnu::const, gnu::always_inline ]]
  constexpr auto promote_integral_unsigned_to_signed( value_type value ) noexcept
    {
    using signed_type = typename signed_type_by_size<((sizeof(value_type)<<1))>::type;
    return static_cast<signed_type>( value );
    }
  
  template<typename value_type>
  [[nodiscard, gnu::const, gnu::always_inline ]]
  constexpr auto promote_type_to_signed( value_type value ) noexcept
    {
    if constexpr ( detail::is_signed_v<value_type> )
      return value;
    else
      return promote_integral_unsigned_to_signed( value );
    }
    
  template<int digits>
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_internal unsigned_shift_left_unsigned( fixed_internal value ) noexcept
    {
    using unsigned_internal = std::make_unsigned<fixed_internal>::type;
    return static_cast<fixed_internal>(
          (static_cast<unsigned_internal>( value ) << digits));
    }
    
  ///\returns the highest power of 4 that is less than or equal to \param value
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_internal highest_pwr4_clz( fixed_internal_unsigned value ) noexcept
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
    
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_internal highest_pwr4( fixed_internal_unsigned value ) noexcept
    {
    // one starts at the highest power of four <= than the argument.
    fixed_internal_unsigned pwr4 { 1ll << 62 }; // second-to-top bit set
    
    while (pwr4 > value)
      pwr4 >>= 2;
    return pwr4;
    }
    
  template<int precision>
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_internal mul_( fixed_internal x, fixed_internal y ) noexcept
    {
    return (x * y) >> precision;
    }
  template<int precision>
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_internal div_( fixed_internal x, fixed_internal y ) noexcept
    {
    return (x<<precision) / y;
    }
    
  template<int precision>
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_internal fix_( fixed_internal x ) noexcept
    {
    return (x<<precision);
    }
  
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t set_sign( bool sign_, fixed_internal result )
    {
    if(!sign_)
      return as_fixed(result);
    return as_fixed(-result);
    }
    
  template<typename T, typename = std::enable_if_t<std::is_arithmetic<T>::value>>
  constexpr void swap(T& a, T& b) noexcept 
    {
    T temp = a;
    a = b;
    b = temp;
    }
  }

