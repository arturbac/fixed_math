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
#include "../utility_cxx20.h"
#include "numbers.h"

namespace 
  {
  extern fixedmath::fixed_internal angle_cos_tbl__[];
  extern fixedmath::fixed_internal cos_tbl__[];
  extern fixedmath::fixed_internal angle_sin_tbl__[];
  extern fixedmath::fixed_internal tan_tbl__[];
  extern fixedmath::fixed_internal acos_tbl__[];
  
  using limits__ = std::numeric_limits<fixedmath::fixed_t>;
  using flimits__ = std::numeric_limits<float>;
  using dlimits__ = std::numeric_limits<double>;
  }
  
namespace fixedmath
{

  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t operator -( fixed_t l ) noexcept { return fix_carrier_t{-l.v}; }
  
  //------------------------------------------------------------------------------------------------------
  namespace 
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
  template<int digits>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_internal unsigned_shift_left_unsigned( fixed_internal value ) noexcept
    {
    using unsigned_internal = std::make_unsigned<fixed_internal>::type;
    return static_cast<fixed_internal>(
          (static_cast<unsigned_internal>( value ) << digits));
    }
  }
  
  //------------------------------------------------------------------------------------------------------
  ///\brief Converts an integral to a fixed_t
  /// \returns fixed on success or NaN if source value is out of range
  template<typename integral_type>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t integral_to_fixed(integral_type value) noexcept
    { 
    static_assert( is_integral<integral_type>::value,"Must be integral type");
    if( fixed_likely(cxx20::cmp_less(value, limits__::max_integral()) && 
                     cxx20::cmp_greater(value, limits__::min_integral()) ) ) 
      {
      if constexpr ( std::is_unsigned<integral_type>::value )
        return fix_carrier_t{unsigned_shift_left_unsigned<16>(value)};
      else
        return fix_carrier_t{unsigned_shift_left_signed<16>(value)};
      }
    return quiet_NaN_result();
    }
  
  constexpr fixed_t operator"" _fix ( unsigned long long value )
    {
    return integral_to_fixed( static_cast<int32_t>( value ));
    }
    

  //------------------------------------------------------------------------------------------------------
  /// \brief Converts a floating point value to a fixed_t
  /// \returns fixed on success or NaN if source value is out of range
  template<typename floating_point_type>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t floating_point_to_fixed (floating_point_type value) noexcept
    { 
    using ft = floating_point_type;
    static_assert( 
        std::is_floating_point<ft>::value && (!is_fixed<ft>{}), "must be floating point" );
    
    if( fixed_likely( value < double(limits__::max_integral()) &&
                      value > double(limits__::min_integral())) )
      return fix_carrier_t( static_cast<fixed_internal>(value * 65536 + (value < ft(0) ? ft(-0.5) : ft(0.5) )) );

    return quiet_NaN_result();
    }
  
  constexpr fixed_t operator"" _fix ( long double value )
    {
    return floating_point_to_fixed( static_cast<double>( value ));
    }

  //------------------------------------------------------------------------------------------------------
  ///\brief Converts an fixed_t point value to an integral.
  template<typename integral_type>
  [[ gnu::const, gnu::always_inline ]]
  constexpr integral_type fixed_to_integral ( fixed_t value ) noexcept
    { 
    static_assert( is_integral<integral_type>::value,"Must be integral type");
    fixed_internal tmp{ ( value.v >> 16 ) + (( value.v & 0x8000) >> 15) };
    using al = std::numeric_limits<integral_type>;
    if( cxx20::cmp_greater_equal( tmp, al::min() ) && cxx20::cmp_less_equal( tmp, al::max() ) )
      return static_cast<integral_type>( tmp );
    return std::numeric_limits<integral_type>::quiet_NaN();
    }

  //------------------------------------------------------------------------------------------------------
  
  template<typename floating_point_type>
  [[ gnu::const, gnu::always_inline ]]
  constexpr floating_point_type fixed_to_floating_point( fixed_t value ) noexcept
    {
    using ft = floating_point_type;
    static_assert( 
        std::is_floating_point<ft>::value && (!is_fixed<ft>{}), "must be floating point" );
    
    return ft(value.v) / ft(65536);
    }

  
  //------------------------------------------------------------------------------------------------------
  //implicit convertion to double
  [[ gnu::always_inline ]]
  constexpr fixed_t::operator double() const noexcept
    {
    return fixed_to_floating_point<double>( *this );
    }
  
  template<typename arithmethic_type>
  constexpr arithmethic_type fixed_to_arithmetic( fixed_t value ) noexcept
    {
    static_assert( is_arithemetic_and_not_fixed<arithmethic_type>{} );
    if constexpr ( std::is_integral<arithmethic_type>::value )
      return fixed_to_integral<arithmethic_type>( value );
    else
      return fixed_to_floating_point<arithmethic_type>( value );
    }
    
  template<typename arithmethic_type>
  [[ gnu::always_inline ]]
  constexpr fixed_t::operator arithmethic_type() const noexcept
    {
    return fixed_to_arithmetic<arithmethic_type>( *this );
    }
  //------------------------------------------------------------------------------------------------------
  /// \fn arithmetic_to_fixed
  template<typename arithmethic_type>
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t arithmetic_to_fixed( arithmethic_type value ) noexcept
    {
    static_assert( is_arithemetic_and_not_fixed<arithmethic_type>{} );
    if constexpr( std::is_floating_point<arithmethic_type>::value )
      return floating_point_to_fixed( value );
    else
      return integral_to_fixed(value);
    }
  //------------------------------------------------------------------------------------------------------

    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t abs( fixed_t value ) noexcept
      {
      using unsigned_fix_internal = std::make_unsigned<fixed_internal>::type;
      return as_fixed(
            static_cast<unsigned_fix_internal>(value.v) & 0x7fffffffffffffffull);
      }
    //------------------------------------------------------------------------------------------------------
    [[ gnu::const, gnu::always_inline ]]
    constexpr bool isnan( fixed_t value ) noexcept
      {
      return abs( value ) == limits__::quiet_NaN();
      }
}
namespace std
  {
    using fixedmath::abs;
    using fixedmath::isnan;
  }
namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t operator >> ( fixed_t l, int r ) noexcept
    { 
    if( fixed_likely(r >= 0 ) )
      return fix_carrier_t{l.v >> r};
    return quiet_NaN_result();
    }
    
  //------------------------------------------------------------------------------------------------------
  
  [[ gnu::const, gnu::always_inline ]]
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
  namespace
    {
    ///\brief Returns the sum of two fixed_t point values.
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_additioni(fixed_t lh, fixed_t rh ) noexcept
      {
      fixed_t result { fix_carrier_t{lh.v + rh.v} };
      if( fixed_unlikely(result >= 0_fix) ) 
        {
        if( fixed_unlikely((lh < 0_fix ) && ( rh < 0_fix)) )
          return -limits__::quiet_NaN();
        }
      else 
        {
        if( fixed_unlikely((lh > 0_fix ) && ( rh > 0_fix )) ) 
          return limits__::quiet_NaN();
        }
      return result;
      }
    
    template<typename supported_type>
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promote_to_double( supported_type  value )
      {
      if constexpr( is_double<supported_type>::value )
        return value;
      else
        return fixed_to_floating_point<double>( value );
      }
      
    template<typename supported_type>
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promote_to_fixed( supported_type  value )
      {
      if constexpr( is_fixed<supported_type>{} )
        return value;
      else
        return arithmetic_to_fixed( value );
      }
      
    template<typename supported_type1, typename supported_type2>
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promoted_double_addition( supported_type1 lh, supported_type2 rh ) noexcept
      {
      static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
      return promote_to_double(lh) + promote_to_double( rh );
      }
      
    template<typename supported_type1, typename supported_type2>
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promoted_fixed_addition( supported_type1 lh, supported_type2 rh ) noexcept
      {
      static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
      return fixed_additioni(promote_to_fixed(lh), promote_to_fixed( rh ) );
      }
    }
  
  ///\brief returns result of addition of to arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  template<typename supported_type1, typename supported_type2>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto fixed_addition( supported_type1 lh, supported_type2 rh) noexcept
    {
    static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
    if constexpr( is_double<supported_type1>::value || is_double<supported_type2>::value )
      return promoted_double_addition( rh, lh );
    else
      return promoted_fixed_addition( lh, rh );
    }
    
  template<typename supported_type>
  [[ gnu::always_inline ]]
  inline fixed_t & operator += ( fixed_t & l, supported_type r ) noexcept { l = fixed_addition(l,r); return l; }

  ///\brief returns result of addition of to arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  template<typename supported_type1, typename supported_type2>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto operator + ( supported_type1 l, supported_type2 r ) noexcept { return fixed_addition(l,r); }

  //------------------------------------------------------------------------------------------------------
  namespace
    {
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_substracti(fixed_t lh, fixed_t rh) noexcept
      {
      fixed_t result { fix_carrier_t{lh.v - rh.v}};

      if(fixed_unlikely(result >= 0_fix)) 
        {
        if( fixed_unlikely((lh < 0_fix) && (rh > 0_fix)) ) 
          return -limits__::quiet_NaN();
        }
      else 
        {
        if( fixed_unlikely((lh > 0_fix) && (rh < 0_fix)) )
          return limits__::quiet_NaN();
        }

      return result;
      }
      
    template<typename supported_type1, typename supported_type2>
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promoted_double_substract( supported_type1 lh, supported_type2 rh ) noexcept
      {
      static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
      return promote_to_double(lh) - promote_to_double( rh );
      }
      
    template<typename supported_type1, typename supported_type2>
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promoted_fixed_substract( supported_type1 lh, supported_type2 rh ) noexcept
      {
      static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
      return fixed_substracti(promote_to_fixed(lh), promote_to_fixed( rh ) );
      }
    }
  ///\brief returns result of addition of to arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  template<typename supported_type1, typename supported_type2>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto fixed_substract( supported_type1 lh, supported_type2 rh) noexcept
    {
    static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
    if constexpr( is_double<supported_type1>::value || is_double<supported_type2>::value )
      return promoted_double_substract( rh, lh );
    else
      return promoted_fixed_substract( lh, rh );
    }
  template<typename supported_type>
  [[ gnu::always_inline ]]
  inline fixed_t & operator -= ( fixed_t & lh, supported_type rh ) noexcept { lh.v -= rh.v; return lh; } 
  
  template<typename supported_type1, typename supported_type2>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto operator - ( supported_type1 lh, supported_type2 rh ) noexcept { return fixed_substract(lh,rh); }

  //------------------------------------------------------------------------------------------------------
  /// \brief Returns the product of two fixed_t point values.
  namespace
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
      
      return limits__::quiet_NaN();
      }
    //double will promote fixed
    template<typename supported_type1, typename supported_type2>
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promoted_double_multiply( supported_type1 lh, supported_type2 rh ) noexcept
      {
      static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
      return promote_to_double(lh) * promote_to_double( rh );
      }
      
    //floats will be promoted
    template<typename supported_type1, typename supported_type2>
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promoted_fixed_multiply( supported_type1 lh, supported_type2 rh ) noexcept
      {
      static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
      return fixed_multiplyi(promote_to_fixed(lh), promote_to_fixed( rh ) );
      }
      
    template<typename integral_type>
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_multiply_scalar (fixed_t lh, integral_type rh) noexcept
      {
      static_assert( is_integral<integral_type>::value,"Must be integral type");
      fixed_t result { fix_carrier_t{ lh.v * rh }};

      if( fixed_likely( check_multiply_result(result)) )
        return result;
      return limits__::quiet_NaN();
      }
    }
    
  ///\brief returns result of addition of to arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  template<typename supported_type1, typename supported_type2>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto fixed_multiply( supported_type1 lh, supported_type2 rh) noexcept
    {
    static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
    if constexpr( is_double<supported_type1>::value || is_double<supported_type2>::value )
      return promoted_double_multiply( lh, rh );
    else if constexpr( is_integral<supported_type1>::value || is_integral<supported_type2>::value )
      return fixed_multiply_scalar( lh, rh);
    else
      return promoted_fixed_multiply( lh, rh );
    }
    
  template<typename supported_type>
  [[ gnu::always_inline ]]
  inline fixed_t & operator *= ( fixed_t & lh, supported_type rh ) noexcept
    {
    lh = fixed_multiply(lh,rh);
    return lh;
    }
  
  template<typename supported_type1, typename supported_type2>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto operator * ( supported_type1 lh, supported_type2 rh ) noexcept
    { 
    return fixed_multiply(lh,rh);
    }

  //------------------------------------------------------------------------------------------------------
  namespace
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
        if( fixed_likely( check_division_result(result)) )
          return result;
        }
      return limits__::quiet_NaN(); //abort ?
      }

    //floats will be promoted
    template<typename supported_type1, typename supported_type2>
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t promoted_fixed_division( supported_type1 lh, supported_type2 rh ) noexcept
      {
      //promote only one of arguments, doesnt allow using this function for ppromothing twu not fixed types
      static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
      return fixed_divisionf(promote_to_fixed(lh), promote_to_fixed( rh ) );
      }
      
    //double will promote fixed
    template<typename supported_type1, typename supported_type2>
    [[ gnu::const, gnu::always_inline ]]
    constexpr double promoted_double_division( supported_type1 lh, supported_type2 rh ) noexcept
      {
      //promote only one of arguments, doesnt allow using this function for ppromothing twu not fixed types
      static_assert( is_arithemetic<supported_type1>{}
                  && is_arithemetic<supported_type2>{}
                  && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                              ,"Arguments must be supported arithmetic types");
      return promote_to_double(lh) / promote_to_double( rh );
      }
      
    template<typename supported_type>
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_division_by_scalar(fixed_t lh, supported_type rh ) noexcept
      {
      static_assert( is_integral<supported_type>::value );
      if( fixed_likely(rh != 0) )
        {
        fixed_t const result = as_fixed( lh.v / rh );
        if( fixed_likely( check_division_result(result)) )
          return result;
        }
      return limits__::quiet_NaN(); //abort ?
      }
    }
    
  template<typename supported_type1, typename supported_type2>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto fixed_division(supported_type1 lh, supported_type2 rh ) noexcept
    {
    static_assert( is_arithemetic<supported_type1>{}
                && is_arithemetic<supported_type2>{}
                && ( is_fixed<supported_type1>{} || is_fixed<supported_type2>{} )
                            ,"Arguments must be supported arithmetic types");
    if constexpr( is_integral<supported_type2>::value )
      return fixed_division_by_scalar( lh, rh );
    else if constexpr ( is_double<supported_type1>::value || is_double<supported_type2>{} )
      return promoted_double_division( lh, rh );
    else
      return promoted_fixed_division( lh, rh );
    }

  template<typename supported_type>
  [[ gnu::always_inline ]]
  inline fixed_t & operator /= ( fixed_t & lh, supported_type rh ) noexcept
    { return fixed_division(lh,rh); } 

  template<typename supported_type1, typename supported_type2>
  [[ gnu::const, gnu::always_inline ]]
  constexpr auto operator / ( supported_type1 lh, supported_type2 rh ) noexcept
    { 
    return fixed_division(lh,rh);
    }

  //------------------------------------------------------------------------------------------------------
  
  //------------------------------------------------------------------------------------------------------

  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t ceil( fixed_t value ) noexcept
    {
    value = value + as_fixed( 0xffff );

    if( value < as_fixed( 0x800000000000ll ) ) 
      return value;
    return limits__::quiet_NaN();
    }
    
  [[deprecated]]
  constexpr int32_t fceil( fixed_t value ) noexcept
    {
    return fixed_to_integral<int32_t>(ceil( value ));
    }
  
}
namespace std
{
  using fixedmath::ceil;
}
namespace fixedmath
{

  //------------------------------------------------------------------------------------------------------
  
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t floor( fixed_t value ) noexcept
    {
    value = as_fixed( value.v & 0xffffffffffff0000llu );
    return value;
    }
    
}
namespace std
{
  using fixedmath::ceil;
}

namespace fixedmath
{

  [[deprecated]]
  constexpr int32_t ffloor( fixed_t value ) noexcept
    {
    return fixed_to_integral<int32_t>(floor( value ));
    }
    
  //------------------------------------------------------------------------------------------------------
  ///\brief converts angle 0 - 360 to radians.
  [[ gnu::const, gnu::always_inline ]]
  constexpr fixed_t angle_to_radians( int angle ) noexcept
    {
    if( angle >= 0 && angle <= 360 )
      return integral_to_fixed(angle) * fixedmath::phi / 180;
    return limits__::quiet_NaN(); 
    }

  
  //------------------------------------------------------------------------------------------------------
  uint16_t square_root_tab( uint8_t index ) noexcept;
  
  [[nodiscard,FIXEDMATH_PUBLIC]]
  fixed_t sqrt(fixed_t value) noexcept;
  
  [[nodiscard,FIXEDMATH_PUBLIC]]
  fixed_t hypot (fixed_t lh, fixed_t rh ) noexcept;
  //------------------------------------------------------------------------------------------------------
  fixed_t tan_tab( uint8_t index ) noexcept;
  
  [[nodiscard,FIXEDMATH_PUBLIC]]
  fixed_t atan( fixed_t value ) noexcept;
  
}
namespace std
{
  using fixedmath::sqrt;
  using fixedmath::atan;
}

namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  fixed_t sin_angle_tab( uint16_t degrees ) noexcept;
  
  inline fixed_t sin_angle(int32_t angle) noexcept
    {
    if(fixed_unlikely(angle < 0 || angle > 360) )
      angle = angle % 360;
    return sin_angle_tab(angle);
    }

  //------------------------------------------------------------------------------------------------------
  fixed_t cos_angle_tab( uint16_t degrees ) noexcept;
  
  inline fixed_t cos_angle(int32_t angle) noexcept
    {
    if( fixed_unlikely( angle < 0 || angle > 360) )
      angle = angle % 360;
    return sin_angle_tab(angle);
    }
    

  
  
  

}
