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

#include "limits.h"
#include "math.h"

namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  //
  // type traits
  //
  static_assert( is_fixed_t<fixed_t>::value ); static_assert( is_fixed_t<fixed_t const &>::value );
  static_assert( is_double_t<double>::value ); static_assert( is_double_t<double const &>::value );
  static_assert( is_integral_t<int32_t>::value );
  static_assert( is_integral_t<uint32_t>::value ); static_assert( is_integral_t<uint32_t const &>::value );
  static_assert( is_integral_t<int16_t>::value ); static_assert( is_integral_t<int16_t const & >::value );
  static_assert( is_integral_t<int64_t>::value );
  static_assert( std::is_signed<fixed_t>::value );
  static_assert( std::is_arithmetic<fixed_t>::value );
  //------------------------------------------------------------------------------------------------------
  //
  // integral_to_fixed unit tests
  //
  static_assert( integral_to_fixed(0) == 0_fix );
  static_assert( integral_to_fixed(1) == limits__::one() );
  static_assert( integral_to_fixed(-1) == -limits__::one() );
  static_assert( integral_to_fixed(-1) != limits__::one() );
  static_assert( integral_to_fixed(-1) != 0_fix );
  static_assert( integral_to_fixed(1) != 0_fix );
  static_assert( integral_to_fixed(1) != integral_to_fixed(-1) );
  static_assert( integral_to_fixed(1) == integral_to_fixed(1) );

  static_assert( 0_fix == fixed_t{});
  static_assert( 1_fix == limits__::one());
  static_assert( -1_fix == -limits__::one());
  static_assert( as_fixed(0x80000000LL) == 32768_fix);
  static_assert( as_fixed(0) == 0_fix);
  static_assert( as_fixed(1l<<32) == 65536_fix );
  //------------------------------------------------------------------------------------------------------
  //
  // floating_point_to_fixed unit tests
  //
  static_assert( floating_point_to_fixed(0.f) == 0_fix );
  static_assert( floating_point_to_fixed(-1.f) == -limits__::one() );
  static_assert( floating_point_to_fixed(-1.f) != limits__::one() );
  static_assert( floating_point_to_fixed(-1.f) != 0_fix );
  static_assert( floating_point_to_fixed(1.f) != 0_fix );
  static_assert( floating_point_to_fixed(1.f) != integral_to_fixed(-1) );
  static_assert( floating_point_to_fixed(1.f) == integral_to_fixed(1) );
  static_assert( floating_point_to_fixed(0.f) == 0_fix );
  static_assert( floating_point_to_fixed(float(limits__::max_integral())) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(flimits__::max()) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(float(limits__::max_integral()+1ll)) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(float(limits__::min_integral())) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(float(limits__::min_integral()-1ll)) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(flimits__::lowest()) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(flimits__::min()) != limits__::quiet_NaN() );
  
  static_assert( floating_point_to_fixed(-1.) == -limits__::one() );
  static_assert( floating_point_to_fixed(-1.) != limits__::one() );
  static_assert( floating_point_to_fixed(-1.) != 0_fix );
  static_assert( floating_point_to_fixed(1.) != 0_fix );
  static_assert( floating_point_to_fixed(1.) != integral_to_fixed(-1) );
  static_assert( floating_point_to_fixed(1.) == integral_to_fixed(1) );
  static_assert( floating_point_to_fixed(double(limits__::max_integral())) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(double(limits__::max_integral()-1ll)) != limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(double(limits__::max_integral()+1ll)) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(double(limits__::min_integral())) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(double(limits__::min_integral()-1ll)) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(double(limits__::min_integral()+1ll)) != limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(dlimits__::lowest()) == limits__::quiet_NaN() );
  static_assert( floating_point_to_fixed(dlimits__::min()) != limits__::quiet_NaN() );
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_to_integral
  //
  static_assert( fixed_to_integral<int>(0.25_fix) == 0 );
  static_assert( fixed_to_integral<int>(1.25_fix) == 1 );
  static_assert( fixed_to_integral<int>(100.25_fix) == 100 );
  static_assert( fixed_to_integral<int>(-100.25_fix) == -100 );
  static_assert( fixed_to_integral<int>(limits__::max()) == (0x7FFFFFFFll>>16)+1 );
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_to_floating_point
  //
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(0.f)) == 0.f );
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(1.f)) == 1.f );
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(0.25f)) == 0.25f );
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(0.5f)) == 0.5f );
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(0.75f)) == 0.75f );
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(-1.f)) == -1.f );
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(-0.25f)) == -0.25f );
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(-0.5f)) == -0.5f );
  static_assert( fixed_to_floating_point<float>(floating_point_to_fixed(-0.75f)) == -0.75f );
  
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(0.f)) == 0. );
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(1.f)) == 1. );
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(0.25f)) == 0.25 );
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(0.5f)) == 0.5 );
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(0.75f)) == 0.75 );
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(-1.f)) == -1. );
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(-0.25f)) == -0.25 );
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(-0.5f)) == -0.5 );
  static_assert( fixed_to_floating_point<double>(floating_point_to_fixed(-0.75f)) == -0.75 );
  
  //------------------------------------------------------------------------------------------------------
  // fixed explicit arithemtic type constructor
  //
  static_assert( fixed_t{1}  == 1_fix );
  static_assert( fixed_t{1u}  == 1_fix );
  static_assert( fixed_t{1lu}  == 1_fix );
  static_assert( fixed_t{1llu}  == 1_fix );
  static_assert( fixed_t{-1}  == -1_fix );
  static_assert( fixed_t{1.f}  == 1_fix );
  static_assert( fixed_t{-1.f}  == -1_fix );
  static_assert( fixed_t{2}  == 2_fix );
  static_assert( fixed_t{-2}  == -2_fix );
  static_assert( fixed_t{2.f}  == 2_fix );
  static_assert( fixed_t{-2.f}  == -2_fix );
  static_assert( fixed_t{4.f}  == 4_fix );
  static_assert( fixed_t{-4.f}  == -4_fix );
  
  static_assert( fixed_t{ 4096ll }  == 4096_fix );
  static_assert( fixed_t{ -4096ll }  == -4096_fix );
  static_assert( fixed_t{ 4096llu } == 4096_fix );
  
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_addition
  //
  static_assert( fixed_addition( 0_fix, 1_fix ) == 1_fix );
  static_assert( fixed_addition( 1_fix, 1_fix ) == 2_fix );
  static_assert( fixed_addition( 10_fix, 1_fix ) == 11_fix );
  static_assert( fixed_addition( -10_fix, 1_fix ) == -9_fix );
  
  static_assert( 0_fix + 1_fix  == 1_fix );
  static_assert( 1_fix + 1_fix  == 2_fix );
  static_assert( 10.4_fix + 1_fix == 11.4_fix );
  static_assert( -10_fix+ 1_fix == -9_fix );

  static_assert( 0_fix + 1  == 1_fix );
  static_assert( 1 + 1_fix  == 2_fix );
  static_assert( 10.4 + 1_fix == 11.4 );
  static_assert( 10.5_fix + 10.2 == 20.7 );
  static_assert( -10_fix+ 1 == -9_fix );
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_substract
  //
  static_assert( 0.2_fix - 1.2_fix  == -1_fix );
  static_assert( 3.2_fix - 1.2_fix  == 2_fix );
  static_assert( -4.2_fix - 1.2_fix  == -5.4_fix );
  static_assert( 1_fix - 1.  ==  1. - 1. );
  
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_multiply
  //
  static_assert( 1_fix * 1_fix  == 1_fix );
  static_assert( 10_fix * 0.5_fix  == 5_fix );
  static_assert( std::abs(0.8_fix * 0.2_fix)  - 0.16_fix <= limits__::epsilon() );
  static_assert( std::abs(0.8_fix * -0.2_fix)  > 0_fix );
  
  
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_division
  //
  static_assert( 1_fix / 1_fix  == 1_fix );
  static_assert( -1_fix / 1_fix  == -1_fix );
  static_assert( 1_fix / -1_fix  == -1_fix );
  static_assert( -1_fix / -1_fix  == 1_fix );
  static_assert( 1_fix / 1  == 1_fix );
  static_assert( 100_fix / 10_fix  == 10_fix );
  static_assert( 100_fix / 10  == 10_fix );
  static_assert( -10_fix / 1  == -10_fix );
  static_assert( -10_fix / 1_fix  == -10_fix );
  static_assert( 1_fix / 2_fix  == 0.5_fix );
  static_assert( 1_fix / 4_fix  == 0.25_fix );
  static_assert( 1 / 4_fix  == 0.25_fix );
  
  //------------------------------------------------------------------------------------------------------
  //
  // ceil
  //
  static_assert( fixed_to_integral<int>(ceil(0.25_fix)) == 1 );
  static_assert( fixed_to_integral<int>(ceil(5.25_fix)) == 6 );
  
  //------------------------------------------------------------------------------------------------------
  //
  // floor
  //
  static_assert( fixed_to_integral<int>(floor(0.25_fix)) == 0 );
  static_assert( floor(0.25_fix) == 0_fix );
  static_assert_equal( (floor(1.25_fix)).v , (1_fix).v );
  static_assert_equal( (floor(-1.25_fix)).v , (-2_fix).v );
  
  //------------------------------------------------------------------------------------------------------
  //
  // angle_to_radians
  //
  static_assert_equal( (angle_to_radians(0)).v , (0_fix).v );
  static_assert_equal( (angle_to_radians(180)).v , (3.1415926536_fix).v );
}
