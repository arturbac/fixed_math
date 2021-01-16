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
      // cmp     x0, #0                          // =0
      // cneg    x0, x0, mi
      return as_fixed(value.v > 0 ? value.v : -value.v);
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
  inline fixed_t & operator -= ( fixed_t & lh, supported_type rh ) noexcept 
    { 
    lh = fixed_substract(lh,rh);
    return lh;
    } 
  
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
    template<typename integral_type>
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t fixed_multiply_scalar (integral_type lh, fixed_t rh ) noexcept
      { return fixed_multiply_scalar(rh,lh); }
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
    {
    lh = fixed_division(lh,rh);
    return lh;
    }
    
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
  fixed_t sqrt_aprox(fixed_t value) noexcept;
  
  namespace 
    {
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
    }
    
  ///\brief Square root by abacus algorithm
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t sqrt( fixed_t value ) noexcept
    {
    if( fixed_unlikely(value.v < 0 || value.v >= (1ll<<48)) )
      return std::numeric_limits<fixed_t>::quiet_NaN();

    value.v <<= 16;
    
    fixed_internal pwr4 { highest_pwr4_clz(value.v) };
    
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
  
  [[nodiscard,FIXEDMATH_PUBLIC]]
  fixed_t hypot_aprox (fixed_t lh, fixed_t rh ) noexcept;

  constexpr fixed_t hypot(fixed_t lh, fixed_t rh ) noexcept
    {
    //TODO
    //sqrt (x^2+y^2) = sqrt ((x/d)^2+(y/d)^2) * d
    //d = 2^n
    //reorder hi/lo
    //check hi for overflow and shift right with d
    //else check lo for underflow and shift left with d
    return sqrt( lh*lh+rh*rh);
    }
}
namespace std
{
  using fixedmath::sqrt;
  using fixedmath::hypot;
}

namespace fixedmath
{
  // for trigonometric functions maclurin taylor series are used
  // https://en.wikipedia.org/wiki/Taylor_series
  //------------------------------------------------------------------------------------------------------
  namespace
    {
    [[ gnu::const, gnu::always_inline ]]
    constexpr int64_t fac( fixed_internal value )
      {
      fixed_internal result{1};
      for( fixed_internal i = 2; i <= value; ++i )
        result *= i;
      return result;
      }
    [[ gnu::const, gnu::always_inline ]]
    constexpr fixed_t inv_fac( fixed_internal value )
      {
      return 1_fix/fac(value);
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
    }
  /// 
  //------------------------------------------------------------------------------------------------------
  ///\returns \param rad normalized into range -phi/2 .. 3phi/2
  [[ nodiscard,gnu::const, gnu::always_inline ]]
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
  
  ///\returns sine of value in radians
  /// Y = X - X^3/ 3! + X^5/ 5! - ... + (-1)^(n+1) * X^(2*n-1)/(2n-1)!
  /// X - X^3/ 3! + X^5/ 5! - X^7/7! 
  /// X - X^3/6 + x^3*x^2/(6*20) - x^3*x^2*x^2/(6*20*42)
  ///
  /// let X2 = X*X
  /// X * (1 - X2*(1 - X2*(1 - X2/42)/20)/6)
  ///
  /// error is less or equal to X^9/9!
  [[ nodiscard,gnu::const, gnu::always_inline ]]
  constexpr fixed_t sin( fixed_t rad ) noexcept
    {
    constexpr fixed_t phi2 { phi/2 };
    rad = sin_range(rad);
      
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
    constexpr fixed_internal one__{ fixed_internal{1}<<prec_};
    fixed_internal x { rad.v };
    
    fixed_internal x2{ mul_<prec_>(x,x) };
    fixed_internal result{ mul_<prec_>(x,( one__ - mul_<prec_>(x2,( one__ - mul_<prec_>(x2,( one__-x2/42))/20))/6)) };
    return as_fixed(result);
    }
}
namespace std
{
  using fixedmath::sin;
}
namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  ///\returns cosine of value in radians
  [[ nodiscard, gnu::const, gnu::always_inline ]]
  constexpr fixed_t cos( fixed_t rad ) noexcept
    {
    constexpr fixed_t phi2 { fixpidiv2 };
    //more effective to use sine than calculate maclurin series for cosine
    //as maclurin series give precise results for -pi/2 .. pi/2
    return sin( phi2 + rad );
    }
}
namespace std
{
  using fixedmath::cos;
}
namespace fixedmath
{
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
  [[ nodiscard,gnu::const, gnu::always_inline ]]
  constexpr fixed_t tan( fixed_t rad ) noexcept
    {
    constexpr fixed_t phi2 { phi/2 };
    if( fixed_likely( rad > -phi2 && rad < phi2 ) )
      {
      constexpr int prec_ = 16;
      fixed_internal x{ rad.v };
      fixed_internal x2{ mul_<prec_>(x,x) };
    
      //X(1+X2(1+X2(2+X2(17+2*X2(31+X2(691+X2(21844+929569X2/105)/39)/55)/9)/21)/5)/3)
      // y0 = 21844+929569X2/105 -> X(1+X2(1+X2(2+X2(17+2*X2(31+X2(691+X2*y0/39)/55)/9)/21)/5)/3)
      // y1 = 691+X2*y0/39 -> X(1+X2(1+X2(2+X2(17+2*X2(31+X2*y1/55)/9)/21)/5)/3)
      // y2 = 31+X2*y1/55 -> X(1+X2(1+X2(2+X2(17+2*X2*y2/9)/21)/5)/3)
      // y3 = 17+2*X2*y2/9 -> X(1+X2(1+X2(2+X2*y3/21)/5)/3)
      // y4 = 2+X2*y3/21 -> X(1+X2(1+X2*y4/5)/3)
      // y5 = 1+X2*y4/5 -> X(1+X2*y5/3)
      // y6 = 1+X2*y5/3 -> X*y6
      // tan = X*y6
      fixed_internal ya_{ fix_<prec_>(929569) + 6404582 * x2 / 17 };
      fixed_internal y0_{ fix_<prec_>(21844) + mul_<prec_>(x2,ya_) / 105 };
      fixed_internal y1_{ fix_<prec_>(691) + mul_<prec_>(x2,y0_)/ 39 };
      fixed_internal y2_{ fix_<prec_>(31) + mul_<prec_>(x2,y1_) / 55 };
      fixed_internal y3_{ fix_<prec_>(17) + mul_<prec_-1>(x2,y2_)/ 9 };
      fixed_internal y4_{ fix_<prec_>(2) + mul_<prec_>(x2,y3_)/ 21 };
      fixed_internal y5_{ fix_<prec_>(1) + mul_<prec_>(x2,y4_)/ 5 };
      fixed_internal y6_{ fix_<prec_>(1) + mul_<prec_>(x2,y5_)/ 3 };
      fixed_internal res{ mul_<prec_>(x,y6_) };
      return as_fixed(res);
      }
    else
      return limits__::quiet_NaN();
    }
}
namespace std
{
  using fixedmath::tan;
}
namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  // atan
  // Y = X - X^3/3 + X^5/5 - X^7/7 + X^9/9 -X^11/11
  [[ nodiscard,gnu::const, gnu::always_inline ]]
  constexpr fixed_t atan( fixed_t x ) noexcept
    {
    //if( fixed_likely( rad >= -1_fix && rad <= 1_fix ) )
    //is optimised as fixed_likely( abs(rad) <= 1_fix )
    //   and     x8, x0, #0x7fffffffffffffff
    //   cmp     x8, #16, lsl #12                // =65536
    //   b.hi    .LBB0_2
    if( fixed_likely( x >= -1_fix && x <= 1_fix ) )
      {
      fixed_internal x2 { (x.v * x.v) >> 16 };
      fixed_internal x3 { (x2 * x.v) >> 16 };
      fixed_internal x5 { (x3 * x2) >> 16 };
      fixed_internal x7 { (x5 * x2) >> 16 };
      fixed_internal x9 { (x7 * x2) >> 16 };
      fixed_internal x11 { (x9 * x2) >> 16 };
      
      return as_fixed( x.v - x3/3 + x5/5 - x7/7 + x9/9 - x11/11);
      }
    else
      return limits__::quiet_NaN();
    }
}
namespace std
{
  using fixedmath::atan;
}
namespace fixedmath
{
  namespace 
    {
    // X + X^3/6 + 3X^5/40 + 5*X^7/112 + 35X^9/1152 + 63X^11/2816
    constexpr fixed_t asin_unchecked( fixed_t rad ) noexcept
      {
      //y0=11/21+21x2/46
      //y1=12155/19+4199x2*y0/4
      //y2=6435/17+x2*y1/2
      //y3=143/5+x2*y2/16
      //y4=231/13+x2*y3/2
      //y5=63/11+x2*y4/4
      //y6=35/9+x2*y5/2
      //y7=5/7+x2*y6/8
      //y8=3/5+x2*y7/2
      //y9=1/3+x2y8/4
      //y10=1+x2*y9
      //asin=x*y10/2
      constexpr int prec_ = 16;
      
      fixed_internal x { rad.v };
      fixed_internal x2{ mul_<prec_>(x,x) };
      
      fixed_internal y5{};
      if(rad > 0.5_fix || rad < -0.5_fix )
        {
        constexpr fixed_internal _11o21{ div_<prec_>(11,21)};
        fixed_internal y0{ _11o21 + 21*x2/46};
        
        constexpr fixed_internal _12155o19{ div_<prec_>(12155,19)+1};
        fixed_internal y1{ _12155o19 + 4199*mul_<prec_>(x2,y0)/4};
        
        constexpr fixed_internal _6435o17{ div_<prec_>(6435,17)+1 };
        fixed_internal y2{ _6435o17 +  mul_<prec_>(x2,y1)/2};
        
        constexpr fixed_internal _143o5{ div_<prec_>(143,5)+1 };
        fixed_internal y3{ _143o5 +  mul_<prec_>(x2,y2)/16};
        
        constexpr fixed_internal _231o13{ div_<prec_>(231,13)+1 };
        fixed_internal y4{ _231o13 +  mul_<prec_>(x2,y3)/2};
        
        constexpr fixed_internal _63o11{ div_<prec_>(63,11) + 1 };
        y5 = mul_<prec_>(x2, _63o11 +  mul_<prec_>(x2,y4)/4)/2;
        }
      constexpr fixed_internal _35o9{ div_<prec_>(35,9) + 1 };
      fixed_internal y6{ _35o9 + y5 };
      
      constexpr fixed_internal _5o7{ div_<prec_>(5,7) + 1 };
      fixed_internal y7{ _5o7 +  mul_<prec_>(x2,y6)/8};
      
      constexpr fixed_internal _3o5{ div_<prec_>(3,5) + 1 };
      fixed_internal y8{ _3o5 +  mul_<prec_>(x2,y7)/2};
      
      constexpr fixed_internal _1o3{ div_<prec_>(1,3) };
      fixed_internal y9{ _1o3 +  mul_<prec_>(x2,y8)/4};
      
      constexpr fixed_internal _1{ 1<<prec_ };
      fixed_internal y10{ _1 +  mul_<prec_>(x2,y9)/2};
      
      return as_fixed(mul_<prec_>(x,y10));
      }
    }
  //------------------------------------------------------------------------------------------------------
  // asin |X| <= 1
  // X + X^3/6 + 3X^5/40 + 5*X^7/112 + 35X^9/1152 + 63X^11/2816
  constexpr fixed_t asin( fixed_t x ) noexcept
    {
    if( fixed_likely( x >= -1_fix && x <= 1_fix ) )
      return asin_unchecked(x);
    else
      return limits__::quiet_NaN();
    }
  //------------------------------------------------------------------------------------------------------
  // acos |X| <= 1
  // pi/2 - X + X^3/6 + 3X^5/40 + 5*X^7/112 + 35X^9/1152 + 63X^11/2816
  constexpr fixed_t acos( fixed_t x ) noexcept
    {
    constexpr fixed_t phi2 { phi/2 };
    if( fixed_likely( x >= -1_fix && x <= 1_fix ) )
      return as_fixed( phi2.v - asin_unchecked(x).v );
    else
      return limits__::quiet_NaN();
    }
  //------------------------------------------------------------------------------------------------------
  // compat with old lib function
  constexpr fixed_t atan_index( fixed_t value ) noexcept
    {
    return atan( value ) * radtofix_r;
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
  
  inline fixed_t sin_angle_aprox(int32_t angle) noexcept
    {
    if(fixed_unlikely(angle < 0 || angle > 360) )
      angle = angle % 360;
    return sin_angle_tab(angle);
    }

  //------------------------------------------------------------------------------------------------------
  // compat with old lib function
  fixed_t cos_angle_tab( uint16_t degrees ) noexcept;
  
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
  
  inline fixed_t atan_aprox( fixed_t value ) noexcept  { return atan_index_aprox( value ) * fixtorad_r; }
  
  
  
  

}
