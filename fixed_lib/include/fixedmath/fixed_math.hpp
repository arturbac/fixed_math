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

#if defined(_MSC_VER)
__pragma( warning (push) )
__pragma( warning(disable : 5030) ) //unknown attribute
__pragma( warning(disable : 4554) ) //false positive about order of execution >>

#endif
#include "types.h"
#include "limits.h"
#include "math.h"

#if defined(_MSC_VER)
__pragma( warning (pop) )
#endif

namespace fixedmath
{
  //representated fractions in fixed and any of sum of them
  // 1      1<<0   0.0000152587890625
  // 2      1<<1   0.0000305175781250
  // 4      1<<2   0.0000610351562500
  // 8      1<<3   0.0001220703125000
  // 16     1<<4   0.0002441406250000
  // 32     1<<5   0.0004882812500000
  // 64     1<<6   0.0009765625000000
  // 128    1<<7   0.0019531250000000
  // 256    1<<8   0.0039062500000000
  // 512    1<<9   0.0078125000000000
  // 1024   1<<10  0.0156250000000000
  // 2048   1<<11  0.0312500000000000
  // 4096   1<<12  0.0625000000000000
  // 8192   1<<13  0.1250000000000000
  // 16384  1<<14  0.2500000000000000
  // 32768  1<<15  0.5000000000000000
  
  ///\brief main type used in calculations
  struct fixed_t;

  ///\brief fixed number negation
  constexpr fixed_t operator -( fixed_t l ) noexcept;
  
  ///\brief converts any floating point or integral value into fixed point
  template<typename arithmethic_type, typename>
  constexpr fixed_t arithmetic_to_fixed( arithmethic_type value ) noexcept;
  
  /// implicit convertion to double from fixed
  //constexpr fixed_t::operator double() const noexcept
  
  /// explicit convertion to integral or float
  //template<typename arithmethic_type>
  //constexpr fixed_t::operator arithmethic_type() const noexcept
  
  ///\brief converts fixed_t into any floating point or integral type
  template<typename arithmethic_type, typename>
  constexpr arithmethic_type fixed_to_arithmetic( fixed_t value ) noexcept;
  
  ///\return absolute value of fixed_t
  constexpr fixed_t abs( fixed_t value ) noexcept;
  
  ///\brief tests for NaN fixed
  ///returns true if \param value is NaN
  constexpr bool isnan( fixed_t value ) noexcept;
  
  constexpr fixed_t ceil( fixed_t value ) noexcept;
  
  constexpr fixed_t floor( fixed_t value ) noexcept;
  
  ///\brief converts angle 0 - 360 to radians.
  template<typename integral_type, typename>
  constexpr fixed_t angle_to_radians( integral_type angle ) noexcept;
  
  ///\brief shifts right value of \param l by \param r digits
  constexpr fixed_t operator >> ( fixed_t l, int r ) noexcept;
  
  ///\brief shifts left value of \param l by \param r digits
  constexpr fixed_t operator << ( fixed_t l, int r ) noexcept;
  
  ///\brief returns result of addition of two arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  ///\returns value of type fixed_t or double
  template<typename supported_type1, typename supported_type2, typename>
  constexpr auto fixed_addition( supported_type1 lh, supported_type2 rh) noexcept;
  
  ///\brief returns result of addition of two arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  ///\returns value of type fixed_t or double
  template<typename supported_type1, typename supported_type2, typename>
  constexpr auto operator + ( supported_type1 l, supported_type2 r ) noexcept;
  
  template<typename supported_type, typename>
  constexpr fixed_t & operator += ( fixed_t & l, supported_type r ) noexcept;
  
  ///\brief returns result of substraction of two arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  ///\returns value of type fixed_t or double
  template<typename supported_type1, typename supported_type2, typename>
  constexpr auto fixed_substract( supported_type1 lh, supported_type2 rh) noexcept;
  
  template<typename supported_type, typename>
  inline fixed_t & operator -= ( fixed_t & lh, supported_type rh ) noexcept;
  
  ///\brief returns result of substraction of two arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  ///\returns value of type fixed_t or double
  template<typename supported_type1, typename supported_type2, typename>
  constexpr auto operator - ( supported_type1 l, supported_type2 r ) noexcept;

  ///\brief returns result of multiplication of two arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  ///\returns value of type fixed_t or double
  template<typename supported_type1, typename supported_type2, typename>
  constexpr auto fixed_multiply( supported_type1 lh, supported_type2 rh) noexcept;
  
  template<typename supported_type, typename>
  constexpr fixed_t & operator *= ( fixed_t & lh, supported_type rh ) noexcept;
  
  ///\brief returns result of multiplication of two arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  ///\returns value of type fixed_t or double
  template<typename supported_type1, typename supported_type2, typename>
  constexpr auto operator * ( supported_type1 lh, supported_type2 rh ) noexcept;
  
  ///\brief returns result of division of two arguments
  ///\notice when one of arguments is double precission operation is promoted to double
  ///\returns value of type fixed_t or double
  template<typename supported_type1, typename supported_type2, typename>
  constexpr auto fixed_division(supported_type1 lh, supported_type2 rh ) noexcept;
  
  template<typename supported_type, typename>
  constexpr fixed_t & operator /= ( fixed_t & lh, supported_type rh ) noexcept;
  
  template<typename supported_type1, typename supported_type2, typename>
  constexpr auto operator / ( supported_type1 lh, supported_type2 rh ) noexcept;
 
  //You can check if constexpr sqrt is avaiable with, for c++20 is always avaiable
  //if constexpr(fixedmath::sqrt_constexpr_available)
  ///\returns square root
  FIXEDMATH_SQRT_CONSTEXPR fixed_t sqrt(fixed_t value) noexcept;

  FIXEDMATH_SQRT_CONSTEXPR fixed_t hypot(fixed_t lh, fixed_t rh ) noexcept;
  
  ///\returns sine of \param rad in radians
  constexpr fixed_t sin( fixed_t rad ) noexcept;
  
  ///\returns cosine of value in radians
  constexpr fixed_t cos( fixed_t rad ) noexcept;
  
  ///\returns tangent of \param rad
  constexpr fixed_t tan( fixed_t rad ) noexcept;
  
  ///\returns arcus sine
  ///\warning valid range < -1 .. 1 >
  constexpr fixed_t asin( fixed_t x ) noexcept;
  
  ///\returns arcus sine
  ///\warning valid range < -1 .. 1 >
  constexpr fixed_t acos( fixed_t x ) noexcept;
  
  ///\returns arcus tangent of \param x
  ///\warning valid range < -1 .. 1 >
  constexpr fixed_t atan( fixed_t x ) noexcept;
  
  ///\returns arcus tangent of y/x using the signs of arguments to determine the correct quadrant.
  constexpr fixed_t atan2( fixed_t y, fixed_t x ) noexcept;
  
  ///\returns arc tan in range 0..+/-127 where 127 represents phi/2
  constexpr fixed_t atan_index( fixed_t value ) noexcept;
  
  ///\returns sine of \param angle specified in degrees
  template<typename supported_type>
  constexpr fixed_t sin_angle(supported_type angle) noexcept;
  
  ///\returns cosine of \param angle specified in degrees
  template<typename supported_type>
  constexpr fixed_t cos_angle(supported_type angle) noexcept;
  
  ///\returns tangent of \param angle specified in degrees
  template<typename supported_type>
  constexpr fixed_t tan_angle(supported_type angle) noexcept;
}
