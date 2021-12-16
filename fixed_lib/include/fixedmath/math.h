// MIT License
// 
// Copyright (c) 2020-2021 Artur Bac
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include <cmath>
#include "types.h"
#include "limits.h"
#include "numbers.h"
#include "detail/common.h"
#include <algorithm>

namespace fixedmath
{
  template<typename arithmethic_type,
    typename = std::enable_if_t<detail::is_arithmetic_and_not_fixed_v<arithmethic_type>>
    >
  constexpr fixed_t arithmetic_to_fixed( arithmethic_type value ) noexcept;
  
  template<typename arithmethic_type, typename>
  constexpr fixed_t::fixed_t( arithmethic_type const & value )
    : v{ arithmetic_to_fixed(value).v }
    {
    static_assert( detail::is_arithmetic_and_not_fixed_v<arithmethic_type> );
    }
  
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t operator -( fixed_t l ) noexcept { return fix_carrier_t{-l.v}; }
  
  //------------------------------------------------------------------------------------------------------
  ///\brief Converts an integral to a fixed_t
  /// \returns fixed on success or NaN if source value is out of range
  template<typename integral_type,
    typename = std::enable_if_t<detail::is_integral_v<integral_type>>
    >
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t integral_to_fixed(integral_type value) noexcept
    { 
    if( fixed_likely(cxx20::cmp_less_equal(value, detail::limits__::max_integral()) && 
                     cxx20::cmp_greater_equal(value, detail::limits__::min_integral()) ) ) 
      {
      if constexpr ( std::is_unsigned<integral_type>::value )
        return fix_carrier_t{detail::unsigned_shift_left_unsigned<16>(value)};
      else
        return fix_carrier_t{detail::unsigned_shift_left_signed<16>(value)};
      }
    return quiet_NaN_result();
    }
  
  constexpr fixed_t operator"" _fix ( unsigned long long value )
    {
    return integral_to_fixed( static_cast<int64_t>( value ));
    }
    
  //------------------------------------------------------------------------------------------------------
  /// \brief Converts a floating point value to a fixed_t
  /// \returns fixed on success or NaN if source value is out of range
  template<typename floating_point_type,
    typename = std::enable_if_t<detail::is_floating_point_and_not_fixed_v<floating_point_type>>
    >
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t floating_point_to_fixed (floating_point_type value) noexcept
    { 
    using ft = floating_point_type;
    
    if( fixed_likely( value < double(detail::limits__::max_integral()) &&
                      value > double(detail::limits__::min_integral())) )
      return fix_carrier_t( static_cast<fixed_internal>(value * 65536 + (value < ft(0) ? ft(-0.5) : ft(0.5) )) );

    return quiet_NaN_result();
    }
  
  constexpr fixed_t operator"" _fix ( long double value )
    {
    return floating_point_to_fixed( static_cast<double>( value ));
    }

  //------------------------------------------------------------------------------------------------------
  ///\brief Converts an fixed_t point value to an integral.
  template<typename integral_type,
    typename = std::enable_if_t<detail::is_integral_v<integral_type>>>
  [[ gnu::const, gnu::always_inline ]]
  constexpr integral_type fixed_to_integral ( fixed_t value ) noexcept
    { 
    fixed_internal tmp{ ( value.v >> 16 ) /*+ (( value.v & 0x8000) >> 15)*/ };
    using al = std::numeric_limits<integral_type>;
    if( cxx20::cmp_greater_equal( tmp, al::min() ) && cxx20::cmp_less_equal( tmp, al::max() ) )
      return static_cast<integral_type>( tmp );
    return std::numeric_limits<integral_type>::quiet_NaN();
    }

  //------------------------------------------------------------------------------------------------------
  
  template<typename floating_point_type,
    typename = std::enable_if_t<detail::is_floating_point_and_not_fixed_v<floating_point_type>>
    >
  [[ gnu::const, gnu::always_inline ]]
  constexpr floating_point_type fixed_to_floating_point( fixed_t value ) noexcept
    {
    using ft = floating_point_type;
    return static_cast<ft>(value.v) / ft(65536);
    }

  //------------------------------------------------------------------------------------------------------

  template<typename arithmethic_type,
    typename = std::enable_if_t<detail::is_arithmetic_and_not_fixed_v<arithmethic_type>>
    >
  constexpr arithmethic_type fixed_to_arithmetic( fixed_t value ) noexcept
    {
    if constexpr ( detail::is_integral_v<arithmethic_type> )
      return fixed_to_integral<arithmethic_type>( value );
    else
      return fixed_to_floating_point<arithmethic_type>( value );
    }
    
  template<typename arithmethic_type, typename>
  [[ nodiscard ]]
  constexpr fixed_t::operator arithmethic_type() const noexcept
    {
    return fixed_to_arithmetic<arithmethic_type>( *this );
    }
  //------------------------------------------------------------------------------------------------------
  template<typename arithmethic_type,
    typename = std::enable_if_t<detail::is_arithmetic_and_not_fixed_v<arithmethic_type>>
    >
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t make_fixed( arithmethic_type value ) noexcept
    {
    if constexpr( detail::is_floating_point_v<arithmethic_type> )
      return floating_point_to_fixed( value );
    else
      return integral_to_fixed(value);
    }
    
  template<typename arithmethic_type, typename>
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t arithmetic_to_fixed( arithmethic_type value ) noexcept
    { return make_fixed( value ); }
  //------------------------------------------------------------------------------------------------------

  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t abs( fixed_t value ) noexcept
    {
    // cmp     x0, #0                          // =0
    // cneg    x0, x0, mi
    return as_fixed(value.v > 0 ? value.v : -value.v);
    }
  //------------------------------------------------------------------------------------------------------
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr bool isnan( fixed_t value ) noexcept
    {
    return abs( value ) == quiet_NaN_result();
    }

  //------------------------------------------------------------------------------------------------------
  
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t operator >> ( fixed_t l, int r ) noexcept
    { 
    if( fixed_likely(r >= 0 ) )
      return fix_carrier_t{l.v >> r};
    return quiet_NaN_result();
    }
    
  //------------------------------------------------------------------------------------------------------
  
  [[ gnu::const ]]
  constexpr fixed_t operator << ( fixed_t l, int r ) noexcept 
    { 
    using unsigned_fix_internal = std::make_unsigned<fixed_internal>::type;
    
    if( fixed_likely( r >= 0 ) )
    return 
      fix_carrier_t{fixed_internal(
        (( ( unsigned_fix_internal(l.v) ) << r ) & unsigned_fix_internal(0x7fffffffffffffffull)) //lsh unsigned value and clear overwritten sign bit
        | ( (1ull<<63) & unsigned_fix_internal(l.v) ) //transfer source sign bit
        )};
    return quiet_NaN_result();
    }
  //------------------------------------------------------------------------------------------------------
  
  [[ gnu::const, gnu::always_inline ]]
  inline fixed_t constexpr
  operator & ( fixed_t l, fixed_t r ) noexcept { return fix_carrier_t{l.v & r.v}; }

  //------------------------------------------------------------------------------------------------------
  namespace detail
    {
    ///\brief Returns the sum of two fixed_t point values.
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_additioni(fixed_t lh, fixed_t rh ) noexcept
      {
      fixed_t result { fix_carrier_t{lh.v + rh.v} };
      if( fixed_unlikely(result >= 0_fix) ) 
        {
        if( fixed_unlikely((lh < 0_fix ) && ( rh < 0_fix)) )
          return -quiet_NaN_result();
        }
      else 
        {
        if( fixed_unlikely((lh > 0_fix ) && ( rh > 0_fix )) ) 
          return quiet_NaN_result();
        }
      return result;
      }
    
    template<typename supported_type>
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promote_to_double( supported_type  value )
      {
      if constexpr( is_double_v<supported_type> )
        return value;
      else
        return fixed_to_floating_point<double>( value );
      }
      
    template<typename supported_type,
      typename = std::enable_if_t<detail::is_arithmetic_v<supported_type>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promote_to_fixed( supported_type  value )
      {
      if constexpr( detail::is_fixed_v<supported_type> )
        return value;
      else
        return arithmetic_to_fixed( value );
      }
      
    template<typename supported_type1, typename supported_type2,
      typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promoted_double_addition( supported_type1 lh, supported_type2 rh ) noexcept
      {
      return promote_to_double(lh) + promote_to_double( rh );
      }
      
    template<typename supported_type1, typename supported_type2,
      typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promoted_fixed_addition( supported_type1 lh, supported_type2 rh ) noexcept
      {
      return fixed_additioni(promote_to_fixed(lh), promote_to_fixed( rh ) );
      }
    }
  
  ///\brief returns result of addition of to arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  template<typename supported_type1, typename supported_type2,
    typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
    >
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto fixed_addition( supported_type1 lh, supported_type2 rh) noexcept
    {
    if constexpr( detail::one_of_is_double_v<supported_type1,supported_type2> )
      return detail::promoted_double_addition( rh, lh );
    else
      return detail::promoted_fixed_addition( lh, rh );
    }
    
  template<typename supported_type,
    typename = std::enable_if_t<detail::is_arithmetic_v<supported_type>>
    >
  [[ gnu::always_inline ]]
  constexpr fixed_t & operator += ( fixed_t & l, supported_type r ) noexcept
    { 
    l = fixed_addition(l,r);
    return l; 
    }

  ///\brief returns result of addition of to arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  template<typename supported_type1, typename supported_type2,
          typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto operator + ( supported_type1 l, supported_type2 r ) noexcept { return fixed_addition(l,r); }

  //------------------------------------------------------------------------------------------------------
  namespace detail
    {
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_substracti(fixed_t lh, fixed_t rh) noexcept
      {
      fixed_t result { fix_carrier_t{lh.v - rh.v}};

      if(fixed_unlikely(result >= 0_fix)) 
        {
        if( fixed_unlikely((lh < 0_fix) && (rh > 0_fix)) ) 
          return -quiet_NaN_result();
        }
      else 
        {
        if( fixed_unlikely((lh > 0_fix) && (rh < 0_fix)) )
          return quiet_NaN_result();
        }

      return result;
      }
      
    template<typename supported_type1, typename supported_type2,
      typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promoted_double_substract( supported_type1 lh, supported_type2 rh ) noexcept
      {
      return promote_to_double(lh) - promote_to_double( rh );
      }
      
    template<typename supported_type1, typename supported_type2,
      typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promoted_fixed_substract( supported_type1 lh, supported_type2 rh ) noexcept
      {
      return fixed_substracti(promote_to_fixed(lh), promote_to_fixed( rh ) );
      }
    }
    
  ///\brief returns result of addition of to arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  template<typename supported_type1, typename supported_type2,
    typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
    >
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto fixed_substract( supported_type1 lh, supported_type2 rh) noexcept
    {
    if constexpr( detail::is_double_v<supported_type1> || detail::is_double_v<supported_type2> )
      return detail::promoted_double_substract( lh, rh );
    else
      return detail::promoted_fixed_substract( lh, rh );
    }
    
  template<typename supported_type,
    typename = std::enable_if_t<detail::is_arithmetic_v<supported_type>>
    >
  [[ gnu::always_inline ]]
  inline fixed_t & operator -= ( fixed_t & lh, supported_type rh ) noexcept 
    { 
    lh = fixed_substract(lh,rh);
    return lh;
    } 
    
  //3 overloads to avoid problem with vector implicit convertion 
  //see https://www.reddit.com/r/cpp_questions/comments/l2cbqe/bug_in_libstdc_or_not_question_about_static/
  
  template<typename supported_type1, typename supported_type2,
           typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
           >
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto operator - ( supported_type1 lh, supported_type2 rh ) noexcept
    {
    return fixed_substract(lh,rh);
    }
    
  //------------------------------------------------------------------------------------------------------
  /// \brief Returns the product of two fixed_t point values.
  namespace detail
    {
    constexpr bool check_multiply_result( fixed_t result )
      { 
      return (result < as_fixed( fixed_internal(0x7fffffffffff0000ll) )
        || result > as_fixed( fixed_internal(-0x7fffffffffff0000ll)) );
      }
    
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_multiplyi (fixed_t lh, fixed_t rh) noexcept
      {
      fixed_t result { fix_carrier_t{ lh.v * rh.v }};

      if( fixed_likely( check_multiply_result(result)) )
        return fix_carrier_t{ result.v >> 16 };
      
      return quiet_NaN_result();
      }
    //double will promote fixed
    template<typename supported_type1, typename supported_type2,
      typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promoted_double_multiply( supported_type1 lh, supported_type2 rh ) noexcept
      {
      return promote_to_double(lh) * promote_to_double( rh );
      }
      
    //floats will be promoted
    template<typename supported_type1, typename supported_type2,
      typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promoted_fixed_multiply( supported_type1 lh, supported_type2 rh ) noexcept
      {
      return fixed_multiplyi(promote_to_fixed(lh), promote_to_fixed( rh ) );
      }
      
    template<typename integral_type,
      typename = std::enable_if_t<is_integral_v<integral_type>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_multiply_scalar (fixed_t lh, integral_type rh) noexcept
      {
      fixed_t result { fix_carrier_t{ lh.v * promote_type_to_signed(rh) }};

      if( fixed_likely( check_multiply_result(result)) )
        return result;
      return quiet_NaN_result();
      }
    template<typename integral_type,
      typename = std::enable_if_t<is_integral_v<integral_type>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_multiply_scalar (integral_type lh, fixed_t rh ) noexcept
      { return fixed_multiply_scalar(rh,lh); }
    }
    
  ///\brief returns result of addition of to arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  template<typename supported_type1, typename supported_type2,
    typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
    >
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto fixed_multiply( supported_type1 lh, supported_type2 rh) noexcept
    {
    if constexpr( detail::is_double_v<supported_type1> || detail::is_double_v<supported_type2> )
      return detail::promoted_double_multiply( lh, rh );
    else if constexpr( detail::is_integral_v<supported_type1> || detail::is_integral_v<supported_type2> )
      return detail::fixed_multiply_scalar( lh, rh);
    else
      return detail::promoted_fixed_multiply( lh, rh );
    }
    
  template<typename supported_type,
    typename = std::enable_if_t<detail::is_arithmetic_v<supported_type>>
    >
  [[ gnu::always_inline ]]
  constexpr fixed_t & operator *= ( fixed_t & lh, supported_type rh ) noexcept
    {
    lh = fixed_multiply(lh,rh);
    return lh;
    }
  
  template<typename supported_type1, typename supported_type2,
          typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
          >
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto operator * ( supported_type1 lh, supported_type2 rh ) noexcept
    { 
    return fixed_multiply(lh,rh);
    }

  //------------------------------------------------------------------------------------------------------
  namespace detail
    {
    constexpr bool check_division_result( fixed_t result )
      { 
      return  result <= as_fixed( fixed_internal(0x7fffffffffffll) ) 
           && result >= as_fixed( fixed_internal(-0x7fffffffffffll) );
      }

    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_divisionf( fixed_t x, fixed_t y) noexcept
      {
      if( fixed_likely(y.v != 0) )
        {
        fixed_t result { as_fixed( (x << 16).v / y.v ) };
//         if( fixed_likely( check_division_result(result)) )
          return result;
        }
      return quiet_NaN_result(); //abort ?
      }

    //floats will be promoted
    template<typename supported_type1, typename supported_type2,
      typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promoted_fixed_division( supported_type1 lh, supported_type2 rh ) noexcept
      {
      //promote only one of arguments, doesnt allow using this function for ppromothing twu not fixed types
      return fixed_divisionf(promote_to_fixed(lh), promote_to_fixed( rh ) );
      }
      
    //double will promote fixed
    template<typename supported_type1, typename supported_type2,
      typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promoted_double_division( supported_type1 lh, supported_type2 rh ) noexcept
      {
      //promote only one of arguments, doesnt allow using this function for ppromothing twu not fixed types
      return promote_to_double(lh) / promote_to_double( rh );
      }
      
    template<typename integral_type,
      typename = std::enable_if_t<is_integral_v<integral_type>>
      >
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_division_by_scalar(fixed_t lh, integral_type rh ) noexcept
      {
      if( fixed_likely(rh != 0) )
        {
        fixed_t const result = as_fixed( lh.v / promote_type_to_signed(rh) );
//         if( fixed_likely( check_division_result(result)) )
          return result;
        }
      return quiet_NaN_result(); //abort ?
      }
    }
    
  template<typename supported_type1, typename supported_type2,
    typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>
    >
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto fixed_division(supported_type1 lh, supported_type2 rh ) noexcept
    {
    if constexpr( detail::is_integral_v<supported_type2> )
      return detail::fixed_division_by_scalar( lh, rh );
    else if constexpr ( detail::one_of_is_double_v<supported_type1,supported_type2> )
      return detail::promoted_double_division( lh, rh );
    else
      return detail::promoted_fixed_division( lh, rh );
    }

  template<typename supported_type,
    typename = std::enable_if_t<detail::is_arithmetic_v<supported_type>>
    >
  [[ gnu::always_inline ]]
  constexpr fixed_t & operator /= ( fixed_t & lh, supported_type rh ) noexcept
    {
    lh = fixed_division(lh,rh);
    return lh;
    }
    
  template<typename supported_type1, typename supported_type2,
          typename = std::enable_if_t<detail::arithmetic_and_one_is_fixed_v<supported_type1,supported_type2>>>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto operator / ( supported_type1 lh, supported_type2 rh ) noexcept
    { 
    return fixed_division(lh,rh);
    }

  //------------------------------------------------------------------------------------------------------

  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t ceil( fixed_t value ) noexcept
    {
    fixed_internal result { (value.v + 0xffff) & ~((1<<16ll)-1) };
    if( value.v < result ) 
      return as_fixed(result);
    return quiet_NaN_result();
    }
  
  //------------------------------------------------------------------------------------------------------
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t floor( fixed_t value ) noexcept
    {
    value = as_fixed( value.v & ~((1<<16)-1) );
    return value;
    }
    
  //------------------------------------------------------------------------------------------------------
  ///\brief converts angle 0 - 360 to radians.
  template<typename integral_type,
    typename = std::enable_if_t<detail::is_integral_v<integral_type>>
    >
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t angle_to_radians( integral_type angle ) noexcept
    {
    if( angle >= integral_type(0) && angle <= integral_type(360) )
      return integral_to_fixed(angle) * fixedmath::phi / 180;
    return quiet_NaN_result(); 
    }

  
  //------------------------------------------------------------------------------------------------------
  uint16_t square_root_tab( uint8_t index ) noexcept;
  
  [[nodiscard,FIXEDMATH_PUBLIC, deprecated]]
  fixed_t sqrt_aprox(fixed_t value) noexcept;
    
#if defined(FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO)
  ///\brief Square root by abacus algorithm
  [[ nodiscard, gnu::const]]
  constexpr fixed_t sqrt( fixed_t value ) noexcept
    {
    if( fixed_unlikely(value.v < 0 || value.v >= (1ll<<48)) )
      return std::numeric_limits<fixed_t>::quiet_NaN();

    value.v <<= 16;
    
    fixed_internal pwr4 { detail::highest_pwr4_clz(value.v) };
    
    fixed_internal result{};
    while( pwr4 != 0 )
      {
      if( value.v >= ( result + pwr4 ) )
        {
        value.v -= result + pwr4;
        result += pwr4 << 1;
        }
      result >>= 1;
      pwr4 >>= 2;
      }
    return as_fixed(result);
    }
#else
  [[ nodiscard, gnu::const]]
  inline fixed_t sqrt( fixed_t value ) noexcept
    {
    return floating_point_to_fixed(std::sqrt( fixed_to_floating_point<double>(value)));
    }
#endif
  [[nodiscard,FIXEDMATH_PUBLIC,deprecated]]
  fixed_t hypot_aprox (fixed_t lh, fixed_t rh ) noexcept;

#if defined(FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO)
  #define FIXED_MATH_HYPOT_CONSTEXPR constexpr
#else
  #define FIXED_MATH_HYPOT_CONSTEXPR inline
#endif
  [[ nodiscard, gnu::const]]
  FIXED_MATH_HYPOT_CONSTEXPR fixed_t hypot(fixed_t lh, fixed_t rh ) noexcept
    {
    constexpr int prec_ = 16;
    //sqrt(X^2+Y^2) = sqrt( (X/D)^2+(Y/D)^2) * D
    //D = 2^n
    if( lh < 0_fix )
      lh = -lh;
    if( rh < 0_fix )
      rh = -rh;
    uint64_t uhi { static_cast<uint64_t>(lh.v)};
    uint64_t ulo { static_cast<uint64_t>(rh.v)};
    
    //reorder hi/lo
    if( uhi < ulo )
      {
      uhi = ulo;
      ulo = static_cast<uint64_t>(lh.v);
      }
    if( fixed_unlikely(uhi == 0) )
      return 0_fix;
    //check hi for overflow and shift right with d
    else if( uhi >= (1ull<<30) )
      {
      int rshbits{ 48 - cxx20::countl_zero( uhi ) };
      uhi >>= rshbits;
      ulo >>= rshbits;
      return as_fixed(sqrt( as_fixed( (uhi*uhi+ulo*ulo)>>prec_ ) ).v << rshbits)  ;
      }
    //else check lo for underflow and shift left with d
    else if( ulo < (1<<16) )
      {
      int lshbits{ std::max(cxx20::countl_zero( uhi ) - 30,0) >> 1 };
      uhi <<= lshbits;
      ulo <<= lshbits;
      return as_fixed( sqrt( as_fixed( (uhi*uhi+ulo*ulo)>>prec_) ).v  >> lshbits);
      }
    else
      return sqrt( as_fixed( (uhi*uhi+ulo*ulo)>>prec_ ) );
    }

  //------------------------------------------------------------------------------------------------------
  // for trigonometric functions maclurin taylor series are used
  // https://en.wikipedia.org/wiki/Taylor_series
  namespace detail
    {
    ///\returns \param rad normalized into range -phi/2 .. 3phi/2
    [[ nodiscard, gnu::const, gnu::always_inline ]]
    constexpr fixed_t sin_range( fixed_t rad )
      {
      constexpr fixed_t phi2 { phi/2 };
      constexpr fixed_t _2phi { 2*phi };
      
      //maximum performance for values in range thus fixed_unlikely
      if( fixed_unlikely( rad < -phi2 || rad > phi+phi2 ) )
        {
        rad = as_fixed( ( phi2.v + rad.v) % _2phi.v - phi2.v );
        if( fixed_unlikely( rad < -phi2 ) )
          rad = as_fixed( rad.v + _2phi.v );
        }
      return rad;
      }
    }
  ///\returns sine of value in radians
  /// Y = X - X^3/ 3! + X^5/ 5! - ... + (-1)^(n+1) * X^(2*n-1)/(2n-1)!
  /// X - X^3/ 3! + X^5/ 5! - X^7/7! 
  /// X - X^3/6 + x^3*x^2/(6*20) - x^3*x^2*x^2/(6*20*42)
  ///
  /// let X2 = X*X
  /// X * (1 - X2*(1 - X2*(1 - X2/42)/20)/6)
  ///
  /// error is less or equal to X^9/9!
  [[ nodiscard,gnu::const ]]
  constexpr fixed_t sin( fixed_t rad ) noexcept
    {
    constexpr fixed_t phi2 { phi/2 };
    using detail::mul_;
    
    rad = detail::sin_range(rad);
      
    // on arm64 condition is compiled as  substraction with csel instruction without jump
    //         mov     w9, #9279
    //         movk    w9, #3, lsl #16
    //         cmp     x0, x8
    //         sub     x9, x9, x0
    //         csel    x9, x9, x0, gt
    if(fixed_unlikely( rad > phi2) )
      rad = phi - rad; //inverse of phi/2 .. -phi/2

    //aprox valid for -phi/2 .. phi/2
    constexpr int prec_ = 16;
    fixed_internal x { rad.v };
    fixed_internal x2{ mul_<prec_>(x,x) };
#if 0
    constexpr fixed_internal one__{ fixed_internal{1}<<prec_};
    fixed_internal result{ mul_<prec_>(x,( one__ - mul_<prec_+1>(x2,( one__ - mul_<prec_+2>(x2,( one__-x2/42))/5))/3)) };
#else
  // reduce number of divisions
  // { x left ( { 1 - x ^ 2 left ( { 1 - x ^ 2 left ( { 1 - x ^ 2 cdot { 1 over 42 } } right ) cdot { 1 over 20 } } right ) { 1 over 6 } } right ) } 
  // { x left ( { 1 - x ^ 2 left ( { 1 - x ^ 2 left ( { 1 - x ^ 2 cdot { 1 over 2 } { 1 over 21 } } right ) cdot { 1 over 4 } cdot { 1 over 5 } } right ) { 1 over 2 } cdot { 1 over 3 } } right ) } 
  // { x left ( { 1 - x ^ 2 left ( { 1 - x ^ 2 { 1 over 21 } left ( { 21 - x ^ 2 cdot { 1 over 2 } } right ) cdot { 1 over 4 } cdot { 1 over 5 } } right ) { 1 over 2 } cdot { 1 over 3 } } right ) } 
  // { x left ( { 1 - x ^ 2 left ( { 1 - x ^ 2 { 1 over { 5 cdot 21 } } left ( { 21 - x ^ 2 cdot { 1 over 2 } } right ) cdot { 1 over 4 } } right ) { 1 over 2 } cdot { 1 over 3 } } right ) } 
  // { x left ( { 1 - x ^ 2 { 1 over { 3 cdot 5 cdot 21 } } left ( { 5 cdot 21 - x ^ 2 left ( { 21 - x ^ 2 cdot { 1 over 2 } } right ) cdot { 1 over 4 } } right ) { 1 over 2 } } right ) } 
  // { x left ( { 3 cdot 5 cdot 21 - x ^ 2 left ( { 5 cdot 21 - x ^ 2 left ( { 21 - x ^ 2 cdot { 1 over 2 } } right ) cdot { 1 over 4 } } right ) { 1 over 2 } } right ) { 1 over { 3 cdot 5 cdot 21 } } } 
  // { x left ( { 315 - x ^ 2 left ( { 105 - x ^ 2 left ( { 21 - x ^ 2 cdot { 1 over 2 } } right ) cdot { 1 over 4 } } right ) { 1 over 2 } } right ) :315 } 
  // { x left ( { 315 - x ^ 2 left ( { 105 - x ^ 2 left ( { 42 - x ^ 2 } right ) cdot { 1 over 8 } } right ) { 1 over 2 } } right ) :315 } 
    constexpr fixed_internal _42{ fixed_internal{42}<<prec_};
    constexpr fixed_internal _105{ fixed_internal{105}<<(prec_+prec_+3)};
    constexpr fixed_internal _315{ fixed_internal{315}<<prec_};
//     fixed_internal result{ mul_<prec_>(x,( _315 - mul_<prec_+1>(x2,( _105 - mul_<prec_+3>(x2,(_42-x2))))))/315 };
    fixed_internal result{ mul_<prec_>(x,( _315 - mul_<prec_+1+prec_+3>(x2,( _105 - x2*(_42-x2)))))/315 };
#endif
    return as_fixed(result);
    }

  //------------------------------------------------------------------------------------------------------
  ///\returns cosine of value in radians
  [[ nodiscard, gnu::const ]]
  constexpr fixed_t cos( fixed_t rad ) noexcept
    {
    constexpr fixed_t phi2 { fixpidiv2 };
    //more effective to use sine than calculate maclurin series for cosine
    //as maclurin series give precise results for -pi/2 .. pi/2
    return sin( phi2 + rad );
    }

  //------------------------------------------------------------------------------------------------------
  // tan
  // Bernoulli number B 2*n
  // 1 1/6
  // 2 -1/30
  // 3 1/42
  // 4 -1/30
  // 5 5/66
  // 6 -691/2730
  // 7 7/6
  // 8 -3617/510
  // 9 43867/798
  namespace detail
    {
    // { { 1 over 6 } { { left ( - 4 right ) ^ 1 left ( 1 - 4 ^ 1 right ) } over fact left ( 2 right ) } x + { - 1 over 30 } { { left ( - 4 right ) ^ 2 left ( 1 - 4 ^ 2 right ) } over fact left ( 2 cdot 2 right ) } x ^ left ( 2 cdot 2 - 1 right ) + { 1 over 42 } { { left ( - 4 right ) ^ 3 left ( 1 - 4 ^ 3 right ) } over fact left ( 2 cdot 3 right ) } x ^ left ( 2 cdot 3 - 1 right ) + { - 1 over 30 } cdot { { left ( - 4 right ) ^ 4 left ( 1 - 4 ^ 4 right ) } over fact left ( 2 cdot 4 right ) } x ^ left ( { 2 cdot 4 - 1 } right ) + { 5 over 66 } cdot { { left ( - 4 right ) ^ 5 left ( 1 - 4 ^ 5 right ) } over fact left ( 2 cdot 5 right ) } x ^ left ( { 2 cdot 5 - 1 } right ) + { - 691 over 2730 } cdot { { left ( - 4 right ) ^ 6 left ( 1 - 4 ^ 6 right ) } over fact left ( 2 cdot 6 right ) } x ^ left ( { 2 cdot 6 - 1 } right ) + { 7 over 6 } { { left ( - 4 right ) ^ 7 left ( 1 - 4 ^ 7 right ) } over fact left ( 2 cdot 7 right ) } x ^ left ( { 2 cdot 7 - 1 } right ) + { - 3617 over 510 } { { left ( - 4 right ) ^ 8 left ( 1 - 4 ^ 8 right ) } over fact left ( 2 cdot 8 right ) } x ^ left ( { 2 cdot 8 - 1 } right ) } 
    
    // { x + { 1 over 3 } x ^ 3 + { 2 over 15 } x ^ 5 + { 17 over 315 } x ^ 7 + { 62 over 2835 } x ^ 9 + { 1382 over 155925 } x ^ 11 + { 21844 over 6081075 } x ^ 13 + { 929569 over 638512875 } x ^ 15 } 
    // { x left ( { 1 + { 1 over 3 } x ^ 2 + { 2 over 15 } x ^ 4 + { 17 over 315 } x ^ 6 + { 62 over 2835 } x ^ 8 + { 1382 over 155925 } x ^ 10 + { 21844 over 6081075 } x ^ 12 + { 929569 over 638512875 } x ^ 14 } right ) } 
    // { x left ( { 1 + { 1 over 3 } x ^ 2 left ( { 1 + { 2 over 5 } x ^ 2 + { 17 over 105 } x ^ 4 + { 62 over 945 } x ^ 6 + { 1382 over 51975 } x ^ 8 + { 21844 over 2027025 } x ^ 10 + { 929569 over 212837625 } x ^ 12 } right ) } right ) } 
    // { x left ( { 1 + { 1 over 3 } x ^ 2 left ( { 1 + { 1 over 5 } x ^ 2 left ( { 2 + { 17 over 21 } x ^ 2 + { 62 over 189 } x ^ 4 + { 1382 over 10395 } x ^ 6 + { 21844 over 405405 } x ^ 8 + { 929569 over 42567525 } x ^ 10 } right ) } right ) } right ) } 
    // { x left ( { 1 + { 1 over 3 } x ^ 2 left ( { 1 + { 1 over 5 } x ^ 2 left ( { 2 + { 1 over 21 } x ^ 2 left ( { 17 + { 62 over 9 } x ^ 2 + { 1382 over 495 } x ^ 4 + { 21844 over 19305 } x ^ 6 + { 929569 over 2027025 } x ^ 8 } right ) } right ) } right ) } right ) } 
    // { x left ( { 1 + { 1 over 3 } x ^ 2 left ( { 1 + { 1 over 5 } x ^ 2 left ( { 2 + { 1 over 21 } x ^ 2 left ( { 17 + { 1 over 9 } x ^ 2 left ( { 62 + { 1382 over 55 } x ^ 2 + { 21844 over 2145 } x ^ 4 + { 929569 over 225225 } x ^ 6 } right ) } right ) } right ) } right ) } right ) } 
    // { x left ( { 1 + { 1 over 3 } x ^ 2 left ( { 1 + { 1 over 5 } x ^ 2 left ( { 2 + { 1 over 21 } x ^ 2 left ( { 17 + { 1 over 9 } x ^ 2 left ( { 62 + { 1 over 55 } x ^ 2 left ( { 1382 + { 21844 over 39 } x ^ 2 + { 929569 over 4095 } x ^ 4 } right ) } right ) } right ) } right ) } right ) } right ) }
    // { x left ( { 1 + { 1 over 3 } x ^ 2 left ( { 1 + { 1 over 5 } x ^ 2 left ( { 2 + { 1 over 21 } x ^ 2 left ( { 17 + { 1 over 9 } x ^ 2 left ( { 62 + { 1 over 55 } x ^ 2 left ( { 1382 + { 1 over 39 } x ^ 2 left ( { 21844 + { 929569 over 105 } x ^ 4 } right ) } right ) } right ) } right ) } right ) } right ) } right ) } 
    // { x left ( { 1 + x ^ 2 left ( { 1 + x ^ 2 left ( { 2 + x ^ 2 left ( { 17 + x ^ 2 left ( { 62 + x ^ 2 left ( { 1382 + x ^ 2 left ( { 21844 + { 929569 over 105 } x ^ 4 } right ) :39 } right ) :55 } right ) :9 } right ) :21 } right ) :5 } right ) :3 } right ) } 
    template<int prec_>
    [[ nodiscard, gnu::const, gnu::always_inline]]
    constexpr fixed_internal tan_( fixed_internal x ) noexcept
      {
      fixed_internal x2{ mul_<prec_>(x,x) };

      fixed_internal y0_{ fix_<prec_>(21844) + 929569 * x2 / 105 };
      fixed_internal y1_{ fix_<prec_>(1382) + mul_<prec_>(x2,y0_)/ 39 };
      fixed_internal y2_{ fix_<prec_>(62) + mul_<prec_>(x2,y1_) / 55 };
      fixed_internal y3_{ fix_<prec_>(17) + mul_<prec_>(x2,y2_)/ 9 };
      fixed_internal y4_{ fix_<prec_>(2) + mul_<prec_>(x2,y3_)/ 21 };
      fixed_internal y5_{ fix_<prec_>(1) + mul_<prec_>(x2,y4_)/ 5 };
      fixed_internal y6_{ fix_<prec_>(1) + mul_<prec_>(x2,y5_)/ 3 };
      fixed_internal res{ mul_<prec_>(x,y6_) };
      return res;
      }
      
    template<int prec_,fixed_internal a, fixed_internal tan_a >
    [[ nodiscard,gnu::const]]
    constexpr fixed_internal tan2_( fixed_internal b )
      {
      constexpr fixed_internal one_{fix_<prec_>(1) };
      b = b - a;
      fixed_internal tan_b { tan_<prec_>(b) };
      return div_<prec_>( tan_a + tan_b, one_ - mul_<prec_>(tan_a, tan_b));
      }
      
    [[ nodiscard,gnu::const, gnu::always_inline ]]
    constexpr fixed_internal tan_range( fixed_internal x )
      {
      constexpr fixed_t phi2 { phi/2 };
      
      //maximum performance for values in range thus fixed_unlikely
      if( fixed_unlikely(x > phi2.v) )
        x = x % phi.v;

      return x;
      }
    }
    
  [[ nodiscard, gnu::const]]
  constexpr fixed_t tan( fixed_t rad ) noexcept
    {
    using detail::div_;
    using detail::tan_;
    
    constexpr int prec_ = 16;
    constexpr int prec_inc = 4;
    constexpr fixed_internal one_{ detail::fix_<prec_>(1) };
    //tan(a+b) = (tan(a) + tan(b)) / (1 - tan(a) tan(b))
    fixed_internal x { rad.v };
    bool sign_ {};
    if( x < 0 )
      {
      x = -x;
      sign_ = true;
      }
    //normalize the range to phi/2
    x = detail::tan_range(x);
    
    if( fixed_likely( x != fixpidiv2.v ) )
      {
      fixed_internal res_tan {};
      if( x <= fixpidiv4.v )
        res_tan = tan_<prec_+prec_inc>(x<<prec_inc)>>prec_inc;
      else
        res_tan = div_<prec_>( one_, tan_<prec_+prec_inc>( (fixpidiv2.v<<prec_inc) - (x<<prec_inc) )>>prec_inc );
      if( sign_ )
        res_tan = -res_tan;
      return as_fixed(res_tan);
       }
    else
      return quiet_NaN_result();
    }
    
  //------------------------------------------------------------------------------------------------------
  // atan
  // Y = X - X^3/3 + X^5/5 - X^7/7 + X^9/9 -X^11/11
  //  { x - { x ^ 3 over 3 } + { x ^ 5 over 5 } - { x ^ 7 over 7 } + { x ^ 9 over 9 } - { x ^ 11 over 11 } }
  // { { 1 over 11 } x left ( { 11 + x ^ 2 left ( { - { 11 over 3 } + x ^ 2 left ( { { 11 over 5 } + x ^ 2 left ( { - { 11 over 7 } + x ^ 2 left ( { { 11 over 9 } - x ^ 2 } right ) } right ) } right ) } right ) } right ) }
  namespace detail
    {
#if 0
    template<int prec_>
    [[ nodiscard,gnu::const, gnu::always_inline ]]
    constexpr fixed_internal atan( fixed_internal x ) noexcept
      {
      //this has less error
      fixed_internal x2 { mul_<prec_>(x, x) };
      fixed_internal x3 { mul_<prec_>(x2, x) };
      fixed_internal x5 { mul_<prec_>(x3, x2) };
      fixed_internal x7 { mul_<prec_>(x5, x2) };
      fixed_internal x9 { mul_<prec_>(x7, x2) };
      fixed_internal x11 { mul_<prec_>(x9, x2) };
      
      return x - x3/3 + x5/5 - x7/7 + x9/9 - x11/11;
      }
#else
    //t=x*x
    //1/11*x(11+t(-11/3+t(11/5+t(-11/7+t(11/9-t)))))
    template<int prec_>
    constexpr fixed_internal atan( fixed_internal x )
      {
      fixed_internal const t { mul_<prec_>(x,x)};
      constexpr fixed_internal _11o9{ fix_<prec_>(11)/9 };
      constexpr fixed_internal _11o7{ fix_<prec_>(11)/7 };
      constexpr fixed_internal _11o5{ fix_<prec_>(11)/5 };
      constexpr fixed_internal _11o3{ fix_<prec_>(11)/3 };
      constexpr fixed_internal _11{ fix_<prec_>(11) };
      
      fixed_internal y{ _11o9 - t };
      y = -_11o7 + mul_<prec_>(t, y);
      y =  _11o5 + mul_<prec_>(t, y);
      y = -_11o3 + mul_<prec_>(t, y);
      y =  _11 + mul_<prec_>(t, y);
      return mul_<prec_>(x, y) / 11;
      }
#endif

    //arctan (x) = arctan(c) + arctan((x - c) / (1 + x*c))
    template<int prec_, fixed_internal atanc, fixed_internal c>
    constexpr fixed_internal atan_sum( fixed_internal x )
      {
      constexpr fixed_internal one_{fix_<prec_>(1) };
      return atanc + atan<prec_>( div_<prec_>(x - c, one_ + mul_<prec_>(x,c)) );
      }
    } 
    
  [[ nodiscard, gnu::const ]]
  constexpr fixed_t atan( fixed_t value ) noexcept
    {
    using detail::atan;
    using detail::atan_sum;
    //     arctan (-x) = -arctan(x)
    //     arctan (1/x) = 0.5 * pi - arctan(x) [x > 0]
    //     arctan (x) = arctan(c) + arctan((x - c) / (1 + x*c))
    //     arctan(x)' = 1/ (1+x^2)
    constexpr int prec_ = 16;
    
    constexpr fixed_internal _7o16{ 28672 }; // 7/16
    constexpr fixed_internal atan_7o16 { 27028 }; // 27027,7307005264

    constexpr fixed_internal _11o16 { 45056 }; // 11/16
    constexpr fixed_internal atan_11o16 { 39472 }; //39471,503516301
    
    constexpr fixed_internal _19o16 { 77824 }; // 19/16
    constexpr fixed_internal atan_19o16 { 57076 }; //57075,52896291
    
    constexpr fixed_internal _39o16 { 159744 }; // 19/16
    constexpr fixed_internal atan_39o16 { 77429 }; //77429,4473907736

    fixed_internal x { value.v };
    bool sign_ {};
    if( x < 0 )
      {
      x = -x;
      sign_ = true;
      }
    fixed_internal result{};
    if( x < _7o16 ) 
      result = atan<prec_>( x );
    else if( x < _11o16 )
      result = atan_sum<prec_, atan_7o16, _7o16>( x );
    else if( x < _19o16 )
      result = atan_sum<prec_, atan_11o16, _11o16>( x );
    else if( x < _39o16 )
      result = atan_sum<prec_, atan_19o16, _19o16>( x );
    else
      result = atan_sum<prec_, atan_39o16, _39o16>( x );
    
    if( !sign_)
      return as_fixed(result);
    return as_fixed(-result);
    }
    
  [[ nodiscard, gnu::const ]]
  constexpr fixed_t atan2( fixed_t y, fixed_t x ) noexcept
    {
    if( x > 0_fix )
      return atan(y/x);
    else if( x < 0_fix )
      {
      if( y >= 0_fix )
        return atan(y/x) + phi;
      else // y < 0
        return atan(y/x) - phi;
      }
    else // x ==0 
      {
      if( y > 0_fix )
        return fixpidiv2;
      else if( y < 0_fix )
        return -fixpidiv2;
      else
        return quiet_NaN_result();
      }
    }

  namespace detail
    {
    // { x + { 1 over 6 } x ^ 3 + { 3 over 40 } x ^ 5 + { 5 over 112 } x ^ 7 + { 35 over 1152 } x ^ 9 + { 63 over 2816 } x ^ 11 } 
    // { x left ( { 1 + { 1 over 6 } x ^ 2 + { 3 over 40 } x ^ 4 + { 5 over 112 } x ^ 6 + { 35 over 1152 } x ^ 8 + { 63 over 2816 } x ^ 10 } right ) } 
    // { x left ( { 1 + { 1 over 6 } x ^ 2 + { 3 over 40 } x ^ 4 + { 5 over 112 } x ^ 6 + { 7 over 128 } x ^ 8 left ( { { 5 over 9 } + { 9 over 22 } x ^ 2 } right ) } right ) } 
    // { x left ( { 1 + { 1 over 6 } x ^ 2 + { 3 over 40 } x ^ 4 + { 5 over 112 } x ^ 6 + { 7 over 99 } { 1 over 256 } x ^ 8 left ( { 110 + 81 x ^ 2 } right ) } right ) } 
    // { x left ( { 1 + { 1 over 6 } x ^ 2 + { 3 over 40 } x ^ 4 + { 1 over { 112 cdot 99 } } x ^ 6 left ( { 495 + 49 { 1 over 16 } x ^ 2 left ( { 110 + 81 x ^ 2 } right ) } right ) } right ) } 
    // { x left ( { 1 + { 1 over 6 } x ^ 2 + { 1 over { 5 cdot 693 } } { 1 over 8 } x ^ 4 left ( { 693 cdot 3 + { 5 over 2 } x ^ 2 left ( { 495 + 49 { 1 over 16 } x ^ 2 left ( { 110 + 81 x ^ 2 } right ) } right ) } right ) } right ) } 
    // { { 1 over 10395 } x left ( { 10395 + { 1 over 2 } x ^ 2 left ( { 3465 + { 3 over 4 } x ^ 2 left ( { 2079 + { 5 over 2 } x ^ 2 left ( { 495 + 49 { 1 over 16 } x ^ 2 left ( { 110 + 81 x ^ 2 } right ) } right ) } right ) } right ) } right ) } 
#if 1
    template<int prec_>
    constexpr fixed_internal asin( fixed_internal x )
      {
      fixed_internal x2{ mul_<prec_>(x,x) };
        
      constexpr fixed_internal _35o9{ div_<prec_>(35,9) + 1 };
      constexpr fixed_internal _5o7{ div_<prec_>(5,7) + 1 };
      constexpr fixed_internal _3o5{ div_<prec_>(3,5) + 1 };
      constexpr fixed_internal _1o3{ div_<prec_>(1,3) };
      constexpr fixed_internal _1{ fix_<prec_>(1) };
      constexpr fixed_internal _63o11{ div_<prec_>(63,11) + 1 };
      

      fixed_internal y6{ _35o9 + mul_<prec_+1>(x2,_63o11) };
      fixed_internal y7{ _5o7 +  mul_<prec_+3>(x2,y6)};
      fixed_internal y8{ _3o5 +  mul_<prec_+1>(x2,y7)};
      fixed_internal y9{ _1o3 +  mul_<prec_+2>(x2,y8)};
      fixed_internal y10{ _1 +  mul_<prec_+1>(x2,y9)};
      
      return mul_<prec_>(x,y10);
      }
#else
    template<int prec_>
    constexpr fixed_internal asin( fixed_internal x )
      {
      fixed_internal x2{ mul_<prec_>(x,x) };
      constexpr fixed_internal _110{ fix_<prec_>(110) };
      constexpr fixed_internal _495{ fix_<prec_>(495) };
      constexpr fixed_internal _2079{ fix_<prec_>(2079) };
      constexpr fixed_internal _3465{ fix_<prec_>(3465) };
      constexpr fixed_internal _10395{ fix_<prec_>(10395) };
      
      fixed_internal t0{ _110 + 81*x2 }; //(110 + 81x^2)
      fixed_internal t1{ _495 + mul_<prec_+4>(49*x2, t0) }; // 495 + 49x^2*t0/16
      fixed_internal t2{ _2079 + mul_<prec_+1>(5*x2, t1) }; // 2079 + 6*x2*t1/2
      fixed_internal t3{ _3465 + mul_<prec_+2>(3*x2, t2) }; // 3465+ 3x^2*t2/4
      fixed_internal t4{ _10395 + mul_<prec_+1>(x2, t3) };
      return mul_<prec_>(x,t4) / 10395;
      }
#endif
    }
  //------------------------------------------------------------------------------------------------------
  // asin |X| <= 1
  [[ nodiscard, gnu::const ]]
  constexpr fixed_t asin( fixed_t x ) noexcept
    {
    using detail::set_sign;
    using detail::asin;
    
    fixed_internal x_{x.v};
    bool sign_ {};
    if( x_ < 0 )
      {
      x_ = -x_;
      sign_ = true;
      }
    constexpr fixed_internal _1 { (1_fix).v };
    if( fixed_likely( x_ <= _1 ) )
      {
      constexpr int ext_prec = 4;
      constexpr int prec = 16+ext_prec;

      if( x_ <= (0.60_fix).v )
        {
        fixed_internal result{ asin<prec>(x_<<ext_prec)>>ext_prec };
        return set_sign( sign_, result );
        }
      else 
        {
        // asin(x) = pi/2-2*asin(sqrt((1-x)/2))
        fixed_internal sqr { sqrt( as_fixed((_1 - x_)>>1)).v };
        fixed_internal result{ fixpidiv2.v - (asin<prec>(sqr <<ext_prec)>>(ext_prec-1)) };
        return set_sign( sign_, result );
        }
      }
    else
      return quiet_NaN_result();
    }
  //------------------------------------------------------------------------------------------------------
  // acos |X| <= 1
  [[ nodiscard, gnu::const ]]
  constexpr fixed_t acos( fixed_t x ) noexcept
    {
    constexpr fixed_t phi2 { phi/2 };
    if( fixed_likely( x >= -1_fix && x <= 1_fix ) )
      return as_fixed( phi2.v - asin(x).v );
    else
      return quiet_NaN_result();
    }
    
  //------------------------------------------------------------------------------------------------------
  template<typename supported_type>
  constexpr fixed_t sin_angle( supported_type angle ) noexcept
    {
    return sin( angle * phi / 180 );
    }
  //------------------------------------------------------------------------------------------------------
  template<typename supported_type>
  constexpr fixed_t cos_angle( supported_type angle ) noexcept
    {
    return cos( angle * phi / 180 );
    }
  //------------------------------------------------------------------------------------------------------
  template<typename supported_type>
  constexpr fixed_t tan_angle( supported_type angle ) noexcept
    {
    return tan( angle * phi / 180 );
    }
    
  //------------------------------------------------------------------------------------------------------
  // compat with old lib function
  fixed_t sin_angle_tab( uint16_t degrees ) noexcept;
  
  [[deprecated,FIXEDMATH_PUBLIC]]
  inline fixed_t sin_angle_aprox(int32_t angle) noexcept
    {
    if(fixed_unlikely(angle < 0 || angle > 360) )
      angle = angle % 360;
    return sin_angle_tab(angle);
    }

  //------------------------------------------------------------------------------------------------------
  // compat with old lib function
  fixed_t cos_angle_tab( uint16_t degrees ) noexcept;
  
  [[deprecated,FIXEDMATH_PUBLIC]]
  inline fixed_t cos_angle_aprox(int32_t angle) noexcept
    {
    if( fixed_unlikely( angle < 0 || angle > 360) )
      angle = angle % 360;
    return cos_angle_tab(angle);
    }
    
  //------------------------------------------------------------------------------------------------------
  // compat with old lib function
  fixed_t tan_tab( uint8_t index ) noexcept;
  
  [[nodiscard,FIXEDMATH_PUBLIC]]
  fixed_t atan_index_aprox( fixed_t value ) noexcept;
  
  [[deprecated]]
  inline fixed_t atan_aprox( fixed_t value ) noexcept  { return atan_index_aprox( value ) * fixtorad_r; }
  
  
  
  

}
