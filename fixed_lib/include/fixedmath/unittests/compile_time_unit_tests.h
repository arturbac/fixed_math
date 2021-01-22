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

#include "../limits.h"
#include "../math.h"

namespace fixedmath::unittests
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

  //------------------------------------------------------------------------------------------------------
  //
  // type traits
  //
  using detail::is_fixed_v;
  
  static_assert( is_fixed_v<fixed_t> );
  static_assert( is_fixed_v<fixed_t const &> );
  static_assert( is_fixed_v<fixed_t> ); static_assert( is_fixed_v<fixed_t const &> );
  static_assert( !is_fixed_v<double> );
  static_assert( !is_fixed_v<int64_t> );
  
  using detail::is_double_v;
  static_assert( is_double_v<double> ); static_assert( is_double_v<double const &> );
  static_assert( !is_double_v<fixed_t> );
  static_assert( !is_double_v<int64_t> );
  
  using detail::is_integral_v;
  static_assert( is_integral_v<int32_t> );
  static_assert( is_integral_v<uint32_t> ); static_assert( is_integral_v<uint32_t const &> );
  static_assert( is_integral_v<int16_t> ); static_assert( is_integral_v<int16_t const & > );
  static_assert( is_integral_v<int64_t> );
  static_assert( !is_integral_v<double> );
  static_assert( !is_integral_v<fixed_t> );
  static_assert( std::is_signed<fixed_t>::value );
  static_assert( std::is_arithmetic<fixed_t>::value );
  
  using detail::is_arithmetic_and_not_fixed_v;
  static_assert( !is_arithmetic_and_not_fixed_v<fixed_t> );
  static_assert( is_arithmetic_and_not_fixed_v<uint8_t> );
  static_assert( is_arithmetic_and_not_fixed_v<uint16_t> );
  static_assert( is_arithmetic_and_not_fixed_v<uint32_t> );
  static_assert( is_arithmetic_and_not_fixed_v<uint64_t> );
  static_assert( is_arithmetic_and_not_fixed_v<int8_t> );
  static_assert( is_arithmetic_and_not_fixed_v<int16_t> );
  static_assert( is_arithmetic_and_not_fixed_v<int32_t> );
  static_assert( is_arithmetic_and_not_fixed_v<int64_t> );
  static_assert( is_arithmetic_and_not_fixed_v<float> );
  static_assert( is_arithmetic_and_not_fixed_v<double> );
  
  using detail::arithmetic_and_one_is_fixed_v;
  static_assert( arithmetic_and_one_is_fixed_v<float,fixed_t> );
  static_assert( arithmetic_and_one_is_fixed_v<fixed_t,fixed_t> );
  static_assert( arithmetic_and_one_is_fixed_v<double,fixed_t> );
  static_assert( arithmetic_and_one_is_fixed_v<int64_t,fixed_t> );
  static_assert( arithmetic_and_one_is_fixed_v<fixed_t,float> );
  static_assert( arithmetic_and_one_is_fixed_v<fixed_t,double> );
  static_assert( arithmetic_and_one_is_fixed_v<fixed_t,int64_t> );
  static_assert( !arithmetic_and_one_is_fixed_v<int64_t,int64_t> );
  static_assert( !arithmetic_and_one_is_fixed_v<float,double> );
  
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
  
  template<typename expected, typename input>
  constexpr bool test_resulting_type( input ) { return std::is_same<expected,input>::value; }
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
  static_assert( -10.5_fix + uint8_t(10) == -0.5_fix );
  static_assert( -10.5_fix + uint16_t(10) == -0.5_fix );
  static_assert( -10.5_fix + uint32_t(10) == -0.5_fix );
  static_assert( -10.5_fix + uint64_t(10) == -0.5_fix );
  static_assert( uint8_t(10) + -10.5_fix == -.5_fix );
  static_assert( uint16_t(10) + -10.5_fix == -.5_fix );
  static_assert( uint32_t(10) + -10.5_fix == -.5_fix );
  static_assert( uint64_t(10) + -10.5_fix == -.5_fix );
  static_assert( -10_fix+ 1 == -9_fix );
  static_assert( 10.5_fix + -10. == .5 );
  static_assert( 10.5_fix + -10.f == .5_fix );
  static_assert( limits__::max() < limits__::quiet_NaN() );
  static_assert( limits__::lowest() +1 != limits__::quiet_NaN() );
  
  static_assert( test_resulting_type<fixed_t>( int64_t(1) + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  + int64_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint64_t(1) + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  + uint64_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1 + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix + 1 ) );
  static_assert( test_resulting_type<fixed_t>( int16_t(1) + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  + int16_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint16_t(1) + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  + uint16_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( int8_t(1) + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  + int8_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint8_t(1) + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  + uint8_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( 1.f + 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  + 1.f ) );
  static_assert( test_resulting_type<double>( 1. + 1_fix ) );
  static_assert( test_resulting_type<double>( 1_fix  + 1. ) );
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_substract
  //
  static_assert( 0.2_fix - 1.2_fix  == -1_fix );
  static_assert( 3.2_fix - 1.2_fix  == 2_fix );
  static_assert( -4.2_fix - 1.2_fix  == -5.4_fix );
  static_assert( -4.2_fix + 1.2_fix  == -3_fix );
  static_assert( 1_fix - 1.  ==  1. - 1. );
  static_assert( 2_fix - 1.  ==  2. - 1. );
  static_assert( -2_fix - 1.  ==  -2. - 1. );
  static_assert( -2_fix + 1.  ==  -2. + 1. );
  static_assert( -10.5_fix - uint8_t(10) == -20.5_fix );
  static_assert( -10.5_fix - uint16_t(10) == -20.5_fix );
  static_assert( -10.5_fix - uint32_t(10) == -20.5_fix );
  static_assert( -10.5_fix - uint64_t(10) == -20.5_fix );
  static_assert( uint8_t(10) -10.5_fix == -.5_fix );
  static_assert( uint16_t(10) -10.5_fix == -.5_fix );
  static_assert( uint32_t(10) -10.5_fix == -.5_fix );
  static_assert( uint64_t(10) -10.5_fix == -.5_fix );
  static_assert( limits__::max() -1 != limits__::quiet_NaN() );
  
  static_assert( test_resulting_type<fixed_t>( int64_t(1) - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  - int64_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint64_t(1) - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  - uint64_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1 - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix - 1 ) );
  static_assert( test_resulting_type<fixed_t>( int16_t(1) - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  - int16_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint16_t(1) - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  - uint16_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( int8_t(1) - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  - int8_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint8_t(1) - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix - uint8_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( 1.f - 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix - 1.f ) );
  static_assert( test_resulting_type<double>( 1. - 1_fix ) );
  static_assert( test_resulting_type<double>( 1_fix  - 1. ) );
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_multiply
  //
  static_assert( 1_fix * 1_fix  == 1_fix );
  static_assert( 10_fix * 0.5_fix  == 5_fix );
  static_assert( abs(0.8_fix * 0.2_fix)  - 0.16_fix <= limits__::epsilon() );
  static_assert( abs(0.8_fix * -0.2_fix)  > 0_fix );

  static_assert( -1.25_fix * int8_t(4)  == -5_fix );
  static_assert( -1.25_fix * int16_t(4)  == -5_fix );
  static_assert( -1.25_fix * int32_t(4)  == -5_fix );
  static_assert( -1.25_fix * int64_t(4)  == -5_fix );
  
  static_assert( -1.25_fix * uint8_t(4)  == -5_fix );
  static_assert( -1.25_fix * uint16_t(4)  == -5_fix );
  static_assert( -1.25_fix * uint32_t(4)  == -5_fix );
  static_assert( -1.25_fix * uint64_t(4)  == -5_fix );
  
  static_assert( int8_t(4) * -1.25_fix == -5_fix );
  static_assert( int16_t(4) * -1.25_fix  == -5_fix );
  static_assert( int32_t(4) * -1.25_fix == -5_fix );
  static_assert( int64_t(4) * -1.25_fix == -5_fix );

  static_assert( uint8_t(4) * -1.25_fix == -5_fix );
  static_assert( uint16_t(4) * -1.25_fix  == -5_fix );
  static_assert( uint32_t(4) * -1.25_fix == -5_fix );
  static_assert( uint64_t(4) * -1.25_fix == -5_fix );
  
  static_assert( test_resulting_type<fixed_t>( int64_t(1) * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  * int64_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint64_t(1) * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  * uint64_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1 * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix * 1 ) );
  static_assert( test_resulting_type<fixed_t>( int16_t(1) * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  * int16_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint16_t(1) * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  * uint16_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( int8_t(1) * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  * int8_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint8_t(1) * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix * uint8_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( 1.f * 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix * 1.f ) );
  static_assert( test_resulting_type<double>( 1. * 1_fix ) );
  static_assert( test_resulting_type<double>( 1_fix * 1. ) );
  
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
  static_assert( -1_fix / 4  == -0.25_fix );
  
  static_assert( int8_t{1} / -4_fix  == -0.25_fix );
  static_assert( int16_t{1} / -4_fix  == -0.25_fix );
  static_assert( int32_t{1} / -4_fix  == -0.25_fix );
  static_assert( int64_t{1} / -4_fix  == -0.25_fix );
  static_assert( float{1} / -4_fix  == -0.25_fix );
  static_assert( double{1} / -4_fix  == -0.25 );
  
  static_assert( uint8_t{1} / -4_fix  == -0.25_fix );
  static_assert( uint16_t{1} / -4_fix  == -0.25_fix );
  static_assert( uint32_t{1} / -4_fix  == -0.25_fix );
  static_assert( uint64_t{1} / -4_fix  == -0.25_fix );
  
  static_assert( -1_fix / uint8_t(4)  == -0.25_fix );
  static_assert( -1_fix / uint16_t(4)  == -0.25_fix );
  static_assert( -1_fix / uint32_t(4)  == -0.25_fix );
  static_assert( -1_fix / uint64_t(4)  == -0.25_fix );
  
  static_assert( -1_fix / int8_t(4)  == -0.25_fix );
  static_assert( -1_fix / int16_t(4)  == -0.25_fix );
  static_assert( -1_fix / int32_t(4)  == -0.25_fix );
  static_assert( -1_fix / int64_t(4)  == -0.25_fix );

  
  static_assert( 1 / 4_fix  == 0.25_fix );
  static_assert( test_resulting_type<fixed_t>( int64_t(1) / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  / int64_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint64_t(1) / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  / uint64_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1 / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix / 1 ) );
  static_assert( test_resulting_type<fixed_t>( int16_t(1) / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  / int16_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint16_t(1) / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  / uint16_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( int8_t(1) / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix  / int8_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( uint8_t(1) / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix / uint8_t(1) ) );
  static_assert( test_resulting_type<fixed_t>( 1.f / 1_fix ) );
  static_assert( test_resulting_type<fixed_t>( 1_fix / 1.f ) );
  static_assert( test_resulting_type<double>( 1. / 1_fix ) );
  static_assert( test_resulting_type<double>( 1_fix / 1. ) );
  
#if defined(FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO)
  //------------------------------------------------------------------------------------------------------
  //
  // sqrt
  //
  static_assert( sqrt(1.4111175537109375_fix) == 1.1878967285156250_fix);
  static_assert( sqrt(2.0000000000000000_fix) == 1.4141998291015625_fix);
  static_assert( sqrt(2.0124969482421875_fix) == 1.4186248779296875_fix);
  static_assert( sqrt(3.3333282470703125_fix) == 1.8257293701171875_fix);
  static_assert( sqrt(4.0000000000000000_fix) == 2.0000000000000000_fix);
  static_assert( sqrt(3331.0000000000000000_fix) == 57.7148132324218750_fix);
  static_assert( sqrt(33331.0000000000000000_fix) == 182.5677947998046875_fix);
  static_assert( sqrt(333331.1000061035156250_fix) == 577.3483276367187500_fix);
  static_assert( sqrt(3333331.0215148925781250_fix) == 1825.7412109375000000_fix);
  //------------------------------------------------------------------------------------------------------
  //
  // hypot
  //
  constexpr bool test_hypot( fixed_t x, fixed_t y, fixed_t expected )
    {
    return abs( hypot( x, y ) - expected ) < 0.00001_fix &&
           abs( hypot( -x, y ) - expected ) < 0.00001_fix &&
           abs( hypot( x, -y ) - expected ) < 0.00001_fix &&
           abs( hypot( -x, -y ) - expected ) < 0.00001_fix;
    }
  static_assert( test_hypot(as_fixed(1ul<<30),as_fixed(1<<0ul), 16384_fix) );
  static_assert( test_hypot(as_fixed(1ul<<33),as_fixed(1ul<<31), 135104_fix) );
  static_assert( test_hypot(as_fixed(1ul<<32),as_fixed(1ul<<31), 73270_fix));
  static_assert( test_hypot(as_fixed(1ul<<31),as_fixed(1ul<<31), 46340_fix));
  static_assert( test_hypot(as_fixed(1ul<<32),as_fixed(1ul), 65536_fix));
  static_assert( test_hypot(as_fixed(1ul<<30),as_fixed(1<<30ul), 23170_fix));
  static_assert( test_hypot(as_fixed((1ul<<30)-1), as_fixed((1ul<<30)-1), 23170.4749755859375_fix) );

  static_assert( test_hypot(as_fixed(1),as_fixed(1), 0.0000152587890625_fix));
  static_assert( test_hypot(as_fixed(2),as_fixed(2), 0.0000305175781250_fix));
  static_assert( test_hypot(as_fixed(1),as_fixed(3), 0.0000457763671875_fix));
  static_assert( test_hypot(as_fixed(2),as_fixed(3), 0.0000457763671875_fix));
  static_assert( test_hypot(0.0125_fix,0.125_fix, 0.1256103515625000_fix));
  static_assert( test_hypot(1_fix,1_fix, 1.4141998291015625_fix));
  static_assert( test_hypot(0.5_fix,0.25_fix, 0.5590057373046875_fix));
#endif
  //------------------------------------------------------------------------------------------------------
  //
  // ceil
  //
  static_assert( ceil(-0.25_fix) == 0_fix );
  static_assert( ceil(-1.25_fix) == -1_fix );
  static_assert( ceil(-10.25_fix) == -10_fix );
  static_assert( ceil(-10.95_fix) == -10_fix );
  static_assert( ceil(0.25_fix) == 1_fix );
  static_assert( ceil(0.75_fix) == 1_fix );
  static_assert( ceil(as_fixed(1)) == 1_fix );
  static_assert( ceil(5.25_fix) == 6_fix );

  //------------------------------------------------------------------------------------------------------
  //
  // floor
  //
  static_assert( fixed_to_integral<int>(floor(0.25_fix)) == 0 );
  static_assert( floor( -1_fix + limits__::epsilon()) == -1_fix ); //
  static_assert( floor( -1_fix - limits__::epsilon()) == -2_fix ); //
  static_assert( floor(-0.25_fix) == -1_fix );
  static_assert( floor(0.25_fix) == 0_fix );
  static_assert( floor(0.95_fix) == 0_fix );
  static_assert_equal( (floor(1.25_fix)).v , (1_fix).v );
  static_assert_equal( (floor(-1.25_fix)).v , (-2_fix).v );
  
  //------------------------------------------------------------------------------------------------------
  //
  // angle_to_radians
  //
  static_assert_equal( (angle_to_radians(0)).v , (0_fix).v );
  static_assert_equal( (angle_to_radians(180)).v , (3.1415926536_fix).v );
  static_assert_equal( (angle_to_radians(180)).v , phi.v );
  static_assert_equal( (angle_to_radians(90)).v , (phi/2).v );
  static_assert_equal( (angle_to_radians(45)).v , (phi/4).v );
  //------------------------------------------------------------------------------------------------------
  //
  // sin
  //
  constexpr bool test_sin( fixed_t x, fixed_t expected )
    {
    return abs(sin( x ) - expected ) < 0.000025_fix &&
      abs(sin( x + 2*phi ) - expected ) < 0.000025_fix &&
      abs(sin( x - 2*phi ) - expected ) < 0.000025_fix &&
      abs(sin( x + 4*phi ) - expected ) < 0.000025_fix;
    }
    
  static_assert( test_sin( phi + phi/2 ,  -0.9998626708984375_fix ));
  static_assert( test_sin( phi + phi/4 ,  -0.7071075439453125_fix ));
  static_assert( test_sin( phi,            0_fix ));
  static_assert( test_sin( 0_fix       ,   0_fix ));
  static_assert( test_sin( phi /2 + phi/4, 0.7071075439453125_fix ));

  static_assert( test_sin( phi/2_fix,      0.9998474121093750_fix ));
  static_assert( test_sin( phi/4_fix,      0.7070922851562500_fix ));
  static_assert( test_sin( phi/5_fix,      0.5877838134765625_fix ));
  static_assert( test_sin( phi/8_fix,      0.3826599121093750_fix ));
  static_assert( test_sin( phi/16_fix,     0.1950683593750000_fix ));
  static_assert( test_sin(-phi/16_fix,    -0.1950836181640625_fix ));
  static_assert( test_sin( phi/-8_fix,    -0.3826751708984375_fix ));
  static_assert( test_sin( phi/-5_fix,    -0.5877990722656250_fix ));
  static_assert( test_sin( phi/-4_fix,    -0.7071075439453125_fix ));
  static_assert( test_sin( phi/-2_fix,    -0.9998626708984375_fix ));

  static_assert( test_sin( phi + phi + phi/2,        0.9998474121093750_fix));
  static_assert( test_sin( phi + phi + phi/4,        0.7070922851562500_fix));
  static_assert( test_sin( phi + phi,                0_fix));
  static_assert( test_sin( phi + phi /2 + phi/4,    -0.7071228027343750_fix));
  static_assert( test_sin( 2*phi + phi + phi/2,     -0.9998626708984375_fix));
  static_assert( test_sin( 2*phi + phi + phi/4,     -0.7071075439453125_fix));
  static_assert( test_sin( 2*phi + phi,              0_fix));
  static_assert( test_sin( 2*phi + phi /2 + phi/4,   0.7071075439453125_fix));

  static_assert( test_sin( -phi-phi /16,  0.1950683593750000_fix ));
  static_assert( test_sin( -phi-phi /8,   0.3826599121093750_fix ));
  static_assert( test_sin( -phi-phi /5,   0.5877838134765625_fix ));
  static_assert( test_sin( -phi-phi /4,   0.7070922851562500_fix ));
  static_assert( test_sin( -phi-phi /2,   0.9998474121093750_fix ));
  
  static_assert( test_sin( -6*phi + -95* phi / 180, -0.9961242675781250_fix ));
  static_assert( test_sin( -4*phi + -95* phi / 180, -0.9961242675781250_fix ));
  static_assert( test_sin( -2*phi + -95* phi / 180, -0.9961242675781250_fix ));
  static_assert( test_sin( -95* phi / 180,          -0.9961242675781250_fix ));
  static_assert( test_sin( -90* phi / 180,          -0.9998626708984375_fix ));
  static_assert( test_sin( -85* phi / 180,          -0.9961090087890625_fix ));

  //------------------------------------------------------------------------------------------------------
  //
  // cos
  //
  static_assert( cos( 2 * phi )           ==  0.9998474121093750_fix );
  static_assert( cos( phi  )              == -0.9998626708984375_fix );
  static_assert( cos( phi /2 + phi/4 )    == -0.7071075439453125_fix );
  static_assert( cos( phi /2 )            ==  0_fix );
  static_assert( cos( phi /3 )            ==  0.4999847412109375_fix );
  static_assert( cos( phi /4 )            ==  0.7071075439453125_fix );
  static_assert( cos( phi /16 )           ==  0.9807281494140625_fix );
  static_assert( cos( 0_fix )             ==  0.9998474121093750_fix );
  static_assert( cos( -phi /16 )          ==  0.9807434082031250_fix );
  static_assert( cos( -phi /4 )           ==  0.7071075439453125_fix );
  static_assert( cos( -phi /3 )           ==  0.5000000000000000_fix );
  static_assert( cos( -phi /2 )           <   0.0001_fix );
  static_assert( cos( -phi /2 + -phi/4  ) == -0.7070922851562500_fix );
  static_assert( cos( -phi  )             == -0.9998626708984375_fix );
  static_assert( cos( 2 * -phi  )         ==  0.9998474121093750_fix );
  
  //------------------------------------------------------------------------------------------------------
  //
  // tan
  //
  constexpr bool test_tan( fixed_t x, double expected )
    {
    return std::abs(tan( x ) - expected ) < 0.0001 && std::abs(tan( -x ) - -expected ) < 0.0001;
    }
    
  static_assert(test_tan( phi /2 + phi /32 , -10.155854941143394 ));
  static_assert(test_tan( phi /3, 1.7320423410947752 ));
  static_assert(test_tan( phi /4, 0.9999739372166156 ));
  static_assert(test_tan( phi /5, 0.7265312623733221 ));
  static_assert(test_tan( phi /8, 0.4141969903665098 ));
  static_assert(test_tan( phi /16, 0.1988970837416414 ));
  static_assert(test_tan( 0_fix , 0.));

  //------------------------------------------------------------------------------------------------------
  //
  // atan
  //
  constexpr bool test_atan( fixed_t x, double expected )
    {
    return std::abs(atan( x ) - expected ) < 0.000025 && std::abs(atan( -x ) - -expected ) < 0.000025;
    }
  static_assert( test_atan( 1_fix/16,0.062418809995957));
  static_assert( test_atan( 3_fix/16,0.185347949995695));
  static_assert( test_atan( 5_fix/16,0.302884868374971));
  static_assert( test_atan( 7_fix/16,0.412410441597387));
  static_assert( test_atan( 8_fix/16,0.463647609000806));
  static_assert( test_atan( 9_fix/16,0.512389460310738));
  static_assert( test_atan( 11_fix/16,0.602287346134964));
  static_assert( test_atan( 13_fix/16,0.682316554874748));
  static_assert( test_atan( 15_fix/16,0.753151280962194));
  static_assert( test_atan( 17_fix/16,0.815691923316223));
  static_assert( test_atan( 19_fix/16,0.870903457075653));
  static_assert( test_atan( 21_fix/16,0.919719605350417));
  static_assert( test_atan( 25_fix/16,1.00148313569423));
  static_assert( test_atan( 37_fix/16,1.16264722303981));
  static_assert( test_atan( 39_fix/16,1.18147960496176));
  static_assert( test_atan( 40_fix/16,1.19028994968253));
  static_assert( test_atan( 45_fix/16,1.22918083614709));
  
  constexpr bool test_atan2( fixed_t y, fixed_t x, double expected )
    {
    return std::abs(atan2( y,x ) - expected ) < 0.0000253;
    }
  static_assert( test_atan2(-1/2_fix,-1/2_fix, -2.3561944901923448 ));
  
  //Thise are generated according to representation of fractions in fixed_t then std::atan2(static_cast<double(fixed y),static_cast<double(fixed x))
  //atan2(+-1/1_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -1_fix,-2.356194490192));
  static_assert(test_atan2(1/ -1_fix, 1/  1_fix,-0.785398163397));
  static_assert(test_atan2(1/  1_fix, 1/ -1_fix,2.356194490192));
  static_assert(test_atan2(1/  1_fix, 1/  1_fix,0.785398163397));
  //atan2(+-1/1_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -2_fix,-2.034443935796));
  static_assert(test_atan2(1/ -1_fix, 1/  2_fix,-1.107148717794));
  static_assert(test_atan2(1/  1_fix, 1/ -2_fix,2.034443935796));
  static_assert(test_atan2(1/  1_fix, 1/  2_fix,1.107148717794));
  //atan2(+-1/1_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -3_fix,-1.892542303548));
  static_assert(test_atan2(1/ -1_fix, 1/  3_fix,-1.249050350042));
  static_assert(test_atan2(1/  1_fix, 1/ -3_fix,1.892542303548));
  static_assert(test_atan2(1/  1_fix, 1/  3_fix,1.249050350042));
  //atan2(+-1/1_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -5_fix,-1.768188952261));
  static_assert(test_atan2(1/ -1_fix, 1/  5_fix,-1.373403701329));
  static_assert(test_atan2(1/  1_fix, 1/ -5_fix,1.768188952261));
  static_assert(test_atan2(1/  1_fix, 1/  5_fix,1.373403701329));
  //atan2(+-1/1_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -7_fix,-1.712689108936));
  static_assert(test_atan2(1/ -1_fix, 1/  7_fix,-1.428903544654));
  static_assert(test_atan2(1/  1_fix, 1/ -7_fix,1.712689108936));
  static_assert(test_atan2(1/  1_fix, 1/  7_fix,1.428903544654));
  //atan2(+-1/1_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -9_fix,-1.681441824738));
  static_assert(test_atan2(1/ -1_fix, 1/  9_fix,-1.460150828852));
  static_assert(test_atan2(1/  1_fix, 1/ -9_fix,1.681441824738));
  static_assert(test_atan2(1/  1_fix, 1/  9_fix,1.460150828852));
  //atan2(+-1/1_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -1_fix, 1/-13_fix,-1.647564717518));
  static_assert(test_atan2(1/ -1_fix, 1/ 13_fix,-1.494027936072));
  static_assert(test_atan2(1/  1_fix, 1/-13_fix,1.647564717518));
  static_assert(test_atan2(1/  1_fix, 1/ 13_fix,1.494027936072));
  //atan2(+-1/1_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -1_fix, 1/-17_fix,-1.629551255030));
  static_assert(test_atan2(1/ -1_fix, 1/ 17_fix,-1.512041398560));
  static_assert(test_atan2(1/  1_fix, 1/-17_fix,1.629551255030));
  static_assert(test_atan2(1/  1_fix, 1/ 17_fix,1.512041398560));
  //atan2(+-1/2_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -1_fix,-2.677945044589));
  static_assert(test_atan2(1/ -2_fix, 1/  1_fix,-0.463647609001));
  static_assert(test_atan2(1/  2_fix, 1/ -1_fix,2.677945044589));
  static_assert(test_atan2(1/  2_fix, 1/  1_fix,0.463647609001));
  //atan2(+-1/2_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -2_fix,-2.356194490192));
  static_assert(test_atan2(1/ -2_fix, 1/  2_fix,-0.785398163397));
  static_assert(test_atan2(1/  2_fix, 1/ -2_fix,2.356194490192));
  static_assert(test_atan2(1/  2_fix, 1/  2_fix,0.785398163397));
  //atan2(+-1/2_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -3_fix,-2.158791887791));
  static_assert(test_atan2(1/ -2_fix, 1/  3_fix,-0.982800765798));
  static_assert(test_atan2(1/  2_fix, 1/ -3_fix,2.158791887791));
  static_assert(test_atan2(1/  2_fix, 1/  3_fix,0.982800765798));
  //atan2(+-1/2_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -5_fix,-1.951297442245));
  static_assert(test_atan2(1/ -2_fix, 1/  5_fix,-1.190295211345));
  static_assert(test_atan2(1/  2_fix, 1/ -5_fix,1.951297442245));
  static_assert(test_atan2(1/  2_fix, 1/  5_fix,1.190295211345));
  //atan2(+-1/2_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -7_fix,-1.849087924534));
  static_assert(test_atan2(1/ -2_fix, 1/  7_fix,-1.292504729055));
  static_assert(test_atan2(1/  2_fix, 1/ -7_fix,1.849087924534));
  static_assert(test_atan2(1/  2_fix, 1/  7_fix,1.292504729055));
  //atan2(+-1/2_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -9_fix,-1.789442653644));
  static_assert(test_atan2(1/ -2_fix, 1/  9_fix,-1.352149999945));
  static_assert(test_atan2(1/  2_fix, 1/ -9_fix,1.789442653644));
  static_assert(test_atan2(1/  2_fix, 1/  9_fix,1.352149999945));
  //atan2(+-1/2_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -2_fix, 1/-13_fix,-1.723438775498));
  static_assert(test_atan2(1/ -2_fix, 1/ 13_fix,-1.418153878092));
  static_assert(test_atan2(1/  2_fix, 1/-13_fix,1.723438775498));
  static_assert(test_atan2(1/  2_fix, 1/ 13_fix,1.418153878092));
  //atan2(+-1/2_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -2_fix, 1/-17_fix,-1.687903300717));
  static_assert(test_atan2(1/ -2_fix, 1/ 17_fix,-1.453689352873));
  static_assert(test_atan2(1/  2_fix, 1/-17_fix,1.687903300717));
  static_assert(test_atan2(1/  2_fix, 1/ 17_fix,1.453689352873));
  //atan2(+-1/3_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -1_fix,-2.819846676837));
  static_assert(test_atan2(1/ -3_fix, 1/  1_fix,-0.321745976753));
  static_assert(test_atan2(1/  3_fix, 1/ -1_fix,2.819846676837));
  static_assert(test_atan2(1/  3_fix, 1/  1_fix,0.321745976753));
  //atan2(+-1/3_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -2_fix,-2.553597092593));
  static_assert(test_atan2(1/ -3_fix, 1/  2_fix,-0.587995560996));
  static_assert(test_atan2(1/  3_fix, 1/ -2_fix,2.553597092593));
  static_assert(test_atan2(1/  3_fix, 1/  2_fix,0.587995560996));
  //atan2(+-1/3_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -3_fix,-2.356194490192));
  static_assert(test_atan2(1/ -3_fix, 1/  3_fix,-0.785398163397));
  static_assert(test_atan2(1/  3_fix, 1/ -3_fix,2.356194490192));
  static_assert(test_atan2(1/  3_fix, 1/  3_fix,0.785398163397));
  //atan2(+-1/3_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -5_fix,-2.111215827065));
  static_assert(test_atan2(1/ -3_fix, 1/  5_fix,-1.030376826524));
  static_assert(test_atan2(1/  3_fix, 1/ -5_fix,2.111215827065));
  static_assert(test_atan2(1/  3_fix, 1/  5_fix,1.030376826524));
  //atan2(+-1/3_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -7_fix,-1.975682588249));
  static_assert(test_atan2(1/ -3_fix, 1/  7_fix,-1.165910065341));
  static_assert(test_atan2(1/  3_fix, 1/ -7_fix,1.975682588249));
  static_assert(test_atan2(1/  3_fix, 1/  7_fix,1.165910065341));
  //atan2(+-1/3_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -9_fix,-1.892519414701));
  static_assert(test_atan2(1/ -3_fix, 1/  9_fix,-1.249073238889));
  static_assert(test_atan2(1/  3_fix, 1/ -9_fix,1.892519414701));
  static_assert(test_atan2(1/  3_fix, 1/  9_fix,1.249073238889));
  //atan2(+-1/3_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -3_fix, 1/-13_fix,-1.797588488301));
  static_assert(test_atan2(1/ -3_fix, 1/ 13_fix,-1.344004165289));
  static_assert(test_atan2(1/  3_fix, 1/-13_fix,1.797588488301));
  static_assert(test_atan2(1/  3_fix, 1/ 13_fix,1.344004165289));
  //atan2(+-1/3_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -3_fix, 1/-17_fix,-1.745468525803));
  static_assert(test_atan2(1/ -3_fix, 1/ 17_fix,-1.396124127787));
  static_assert(test_atan2(1/  3_fix, 1/-17_fix,1.745468525803));
  static_assert(test_atan2(1/  3_fix, 1/ 17_fix,1.396124127787));
  //atan2(+-1/5_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -1_fix,-2.944200028124));
  static_assert(test_atan2(1/ -5_fix, 1/  1_fix,-0.197392625466));
  static_assert(test_atan2(1/  5_fix, 1/ -1_fix,2.944200028124));
  static_assert(test_atan2(1/  5_fix, 1/  1_fix,0.197392625466));
  //atan2(+-1/5_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -2_fix,-2.761091538140));
  static_assert(test_atan2(1/ -5_fix, 1/  2_fix,-0.380501115450));
  static_assert(test_atan2(1/  5_fix, 1/ -2_fix,2.761091538140));
  static_assert(test_atan2(1/  5_fix, 1/  2_fix,0.380501115450));
  //atan2(+-1/5_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -3_fix,-2.601173153319));
  static_assert(test_atan2(1/ -5_fix, 1/  3_fix,-0.540419500271));
  static_assert(test_atan2(1/  5_fix, 1/ -3_fix,2.601173153319));
  static_assert(test_atan2(1/  5_fix, 1/  3_fix,0.540419500271));
  //atan2(+-1/5_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -5_fix,-2.356194490192));
  static_assert(test_atan2(1/ -5_fix, 1/  5_fix,-0.785398163397));
  static_assert(test_atan2(1/  5_fix, 1/ -5_fix,2.356194490192));
  static_assert(test_atan2(1/  5_fix, 1/  5_fix,0.785398163397));
  //atan2(+-1/5_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -7_fix,-2.191038595636));
  static_assert(test_atan2(1/ -5_fix, 1/  7_fix,-0.950554057954));
  static_assert(test_atan2(1/  5_fix, 1/ -7_fix,2.191038595636));
  static_assert(test_atan2(1/  5_fix, 1/  7_fix,0.950554057954));
  //atan2(+-1/5_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -9_fix,-2.077855963028));
  static_assert(test_atan2(1/ -5_fix, 1/  9_fix,-1.063736690562));
  static_assert(test_atan2(1/  5_fix, 1/ -9_fix,2.077855963028));
  static_assert(test_atan2(1/  5_fix, 1/  9_fix,1.063736690562));
  //atan2(+-1/5_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -5_fix, 1/-13_fix,-1.937959935455));
  static_assert(test_atan2(1/ -5_fix, 1/ 13_fix,-1.203632718135));
  static_assert(test_atan2(1/  5_fix, 1/-13_fix,1.937959935455));
  static_assert(test_atan2(1/  5_fix, 1/ 13_fix,1.203632718135));
  //atan2(+-1/5_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -5_fix, 1/-17_fix,-1.856847768512));
  static_assert(test_atan2(1/ -5_fix, 1/ 17_fix,-1.284744885078));
  static_assert(test_atan2(1/  5_fix, 1/-17_fix,1.856847768512));
  static_assert(test_atan2(1/  5_fix, 1/ 17_fix,1.284744885078));
  //atan2(+-1/7_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -1_fix,-2.999699871449));
  static_assert(test_atan2(1/ -7_fix, 1/  1_fix,-0.141892782141));
  static_assert(test_atan2(1/  7_fix, 1/ -1_fix,2.999699871449));
  static_assert(test_atan2(1/  7_fix, 1/  1_fix,0.141892782141));
  //atan2(+-1/7_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -2_fix,-2.863301055850));
  static_assert(test_atan2(1/ -7_fix, 1/  2_fix,-0.278291597739));
  static_assert(test_atan2(1/  7_fix, 1/ -2_fix,2.863301055850));
  static_assert(test_atan2(1/  7_fix, 1/  2_fix,0.278291597739));
  //atan2(+-1/7_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -3_fix,-2.736706392136));
  static_assert(test_atan2(1/ -7_fix, 1/  3_fix,-0.404886261454));
  static_assert(test_atan2(1/  7_fix, 1/ -3_fix,2.736706392136));
  static_assert(test_atan2(1/  7_fix, 1/  3_fix,0.404886261454));
  //atan2(+-1/7_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -5_fix,-2.521350384749));
  static_assert(test_atan2(1/ -7_fix, 1/  5_fix,-0.620242268841));
  static_assert(test_atan2(1/  7_fix, 1/ -5_fix,2.521350384749));
  static_assert(test_atan2(1/  7_fix, 1/  5_fix,0.620242268841));
  //atan2(+-1/7_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -7_fix,-2.356194490192));
  static_assert(test_atan2(1/ -7_fix, 1/  7_fix,-0.785398163397));
  static_assert(test_atan2(1/  7_fix, 1/ -7_fix,2.356194490192));
  static_assert(test_atan2(1/  7_fix, 1/  7_fix,0.785398163397));
  //atan2(+-1/7_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -9_fix,-2.231802520234));
  static_assert(test_atan2(1/ -7_fix, 1/  9_fix,-0.909790133356));
  static_assert(test_atan2(1/  7_fix, 1/ -9_fix,2.231802520234));
  static_assert(test_atan2(1/  7_fix, 1/  9_fix,0.909790133356));
  //atan2(+-1/7_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -7_fix, 1/-13_fix,-2.064731326004));
  static_assert(test_atan2(1/ -7_fix, 1/ 13_fix,-1.076861327586));
  static_assert(test_atan2(1/  7_fix, 1/-13_fix,2.064731326004));
  static_assert(test_atan2(1/  7_fix, 1/ 13_fix,1.076861327586));
  //atan2(+-1/7_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -7_fix, 1/-17_fix,-1.961408742822));
  static_assert(test_atan2(1/ -7_fix, 1/ 17_fix,-1.180183910768));
  static_assert(test_atan2(1/  7_fix, 1/-17_fix,1.961408742822));
  static_assert(test_atan2(1/  7_fix, 1/ 17_fix,1.180183910768));
  //atan2(+-1/9_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -1_fix,-3.030947155647));
  static_assert(test_atan2(1/ -9_fix, 1/  1_fix,-0.110645497943));
  static_assert(test_atan2(1/  9_fix, 1/ -1_fix,3.030947155647));
  static_assert(test_atan2(1/  9_fix, 1/  1_fix,0.110645497943));
  //atan2(+-1/9_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -2_fix,-2.922946326740));
  static_assert(test_atan2(1/ -9_fix, 1/  2_fix,-0.218646326849));
  static_assert(test_atan2(1/  9_fix, 1/ -2_fix,2.922946326740));
  static_assert(test_atan2(1/  9_fix, 1/  2_fix,0.218646326849));
  //atan2(+-1/9_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -3_fix,-2.819869565684));
  static_assert(test_atan2(1/ -9_fix, 1/  3_fix,-0.321723087906));
  static_assert(test_atan2(1/  9_fix, 1/ -3_fix,2.819869565684));
  static_assert(test_atan2(1/  9_fix, 1/  3_fix,0.321723087906));
  //atan2(+-1/9_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -5_fix,-2.634533017357));
  static_assert(test_atan2(1/ -9_fix, 1/  5_fix,-0.507059636233));
  static_assert(test_atan2(1/  9_fix, 1/ -5_fix,2.634533017357));
  static_assert(test_atan2(1/  9_fix, 1/  5_fix,0.507059636233));
  //atan2(+-1/9_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -7_fix,-2.480586460150));
  static_assert(test_atan2(1/ -9_fix, 1/  7_fix,-0.661006193439));
  static_assert(test_atan2(1/  9_fix, 1/ -7_fix,2.480586460150));
  static_assert(test_atan2(1/  9_fix, 1/  7_fix,0.661006193439));
  //atan2(+-1/9_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -9_fix,-2.356194490192));
  static_assert(test_atan2(1/ -9_fix, 1/  9_fix,-0.785398163397));
  static_assert(test_atan2(1/  9_fix, 1/ -9_fix,2.356194490192));
  static_assert(test_atan2(1/  9_fix, 1/  9_fix,0.785398163397));
  //atan2(+-1/9_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -9_fix, 1/-13_fix,-2.176369557339));
  static_assert(test_atan2(1/ -9_fix, 1/ 13_fix,-0.965223096250));
  static_assert(test_atan2(1/  9_fix, 1/-13_fix,2.176369557339));
  static_assert(test_atan2(1/  9_fix, 1/ 13_fix,0.965223096250));
  //atan2(+-1/9_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -9_fix, 1/-17_fix,-2.057733420184));
  static_assert(test_atan2(1/ -9_fix, 1/ 17_fix,-1.083859233406));
  static_assert(test_atan2(1/  9_fix, 1/-17_fix,2.057733420184));
  static_assert(test_atan2(1/  9_fix, 1/ 17_fix,1.083859233406));
  //atan2(+-1/13_fix, +-1/1_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -1_fix,-3.064824262867));
  static_assert(test_atan2(1/-13_fix, 1/  1_fix,-0.076768390723));
  static_assert(test_atan2(1/ 13_fix, 1/ -1_fix,3.064824262867));
  static_assert(test_atan2(1/ 13_fix, 1/  1_fix,0.076768390723));
  //atan2(+-1/13_fix, +-1/2_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -2_fix,-2.988950204887));
  static_assert(test_atan2(1/-13_fix, 1/  2_fix,-0.152642448703));
  static_assert(test_atan2(1/ 13_fix, 1/ -2_fix,2.988950204887));
  static_assert(test_atan2(1/ 13_fix, 1/  2_fix,0.152642448703));
  //atan2(+-1/13_fix, +-1/3_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -3_fix,-2.914800492084));
  static_assert(test_atan2(1/-13_fix, 1/  3_fix,-0.226792161506));
  static_assert(test_atan2(1/ 13_fix, 1/ -3_fix,2.914800492084));
  static_assert(test_atan2(1/ 13_fix, 1/  3_fix,0.226792161506));
  //atan2(+-1/13_fix, +-1/5_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -5_fix,-2.774429044930));
  static_assert(test_atan2(1/-13_fix, 1/  5_fix,-0.367163608660));
  static_assert(test_atan2(1/ 13_fix, 1/ -5_fix,2.774429044930));
  static_assert(test_atan2(1/ 13_fix, 1/  5_fix,0.367163608660));
  //atan2(+-1/13_fix, +-1/7_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -7_fix,-2.647657654381));
  static_assert(test_atan2(1/-13_fix, 1/  7_fix,-0.493934999209));
  static_assert(test_atan2(1/ 13_fix, 1/ -7_fix,2.647657654381));
  static_assert(test_atan2(1/ 13_fix, 1/  7_fix,0.493934999209));
  //atan2(+-1/13_fix, +-1/9_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -9_fix,-2.536019423045));
  static_assert(test_atan2(1/-13_fix, 1/  9_fix,-0.605573230544));
  static_assert(test_atan2(1/ 13_fix, 1/ -9_fix,2.536019423045));
  static_assert(test_atan2(1/ 13_fix, 1/  9_fix,0.605573230544));
  //atan2(+-1/13_fix, +-1/13_fix)
  static_assert(test_atan2(1/-13_fix, 1/-13_fix,-2.356194490192));
  static_assert(test_atan2(1/-13_fix, 1/ 13_fix,-0.785398163397));
  static_assert(test_atan2(1/ 13_fix, 1/-13_fix,2.356194490192));
  static_assert(test_atan2(1/ 13_fix, 1/ 13_fix,0.785398163397));
  //atan2(+-1/13_fix, +-1/17_fix)
  static_assert(test_atan2(1/-13_fix, 1/-17_fix,-2.223657684135));
  static_assert(test_atan2(1/-13_fix, 1/ 17_fix,-0.917934969455));
  static_assert(test_atan2(1/ 13_fix, 1/-17_fix,2.223657684135));
  static_assert(test_atan2(1/ 13_fix, 1/ 17_fix,0.917934969455));
  //atan2(+-1/17_fix, +-1/1_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -1_fix,-3.082837725355));
  static_assert(test_atan2(1/-17_fix, 1/  1_fix,-0.058754928235));
  static_assert(test_atan2(1/ 17_fix, 1/ -1_fix,3.082837725355));
  static_assert(test_atan2(1/ 17_fix, 1/  1_fix,0.058754928235));
  //atan2(+-1/17_fix, +-1/2_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -2_fix,-3.024485679668));
  static_assert(test_atan2(1/-17_fix, 1/  2_fix,-0.117106973922));
  static_assert(test_atan2(1/ 17_fix, 1/ -2_fix,3.024485679668));
  static_assert(test_atan2(1/ 17_fix, 1/  2_fix,0.117106973922));
  //atan2(+-1/17_fix, +-1/3_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -3_fix,-2.966920454582));
  static_assert(test_atan2(1/-17_fix, 1/  3_fix,-0.174672199008));
  static_assert(test_atan2(1/ 17_fix, 1/ -3_fix,2.966920454582));
  static_assert(test_atan2(1/ 17_fix, 1/  3_fix,0.174672199008));
  //atan2(+-1/17_fix, +-1/5_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -5_fix,-2.855541211872));
  static_assert(test_atan2(1/-17_fix, 1/  5_fix,-0.286051441717));
  static_assert(test_atan2(1/ 17_fix, 1/ -5_fix,2.855541211872));
  static_assert(test_atan2(1/ 17_fix, 1/  5_fix,0.286051441717));
  //atan2(+-1/17_fix, +-1/7_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -7_fix,-2.750980237563));
  static_assert(test_atan2(1/-17_fix, 1/  7_fix,-0.390612416027));
  static_assert(test_atan2(1/ 17_fix, 1/ -7_fix,2.750980237563));
  static_assert(test_atan2(1/ 17_fix, 1/  7_fix,0.390612416027));
  //atan2(+-1/17_fix, +-1/9_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -9_fix,-2.654655560200));
  static_assert(test_atan2(1/-17_fix, 1/  9_fix,-0.486937093389));
  static_assert(test_atan2(1/ 17_fix, 1/ -9_fix,2.654655560200));
  static_assert(test_atan2(1/ 17_fix, 1/  9_fix,0.486937093389));
  //atan2(+-1/17_fix, +-1/13_fix)
  static_assert(test_atan2(1/-17_fix, 1/-13_fix,-2.488731296250));
  static_assert(test_atan2(1/-17_fix, 1/ 13_fix,-0.652861357340));
  static_assert(test_atan2(1/ 17_fix, 1/-13_fix,2.488731296250));
  static_assert(test_atan2(1/ 17_fix, 1/ 13_fix,0.652861357340));
  //atan2(+-1/17_fix, +-1/17_fix)
  static_assert(test_atan2(1/-17_fix, 1/-17_fix,-2.356194490192));
  static_assert(test_atan2(1/-17_fix, 1/ 17_fix,-0.785398163397));
  static_assert(test_atan2(1/ 17_fix, 1/-17_fix,2.356194490192));
  static_assert(test_atan2(1/ 17_fix, 1/ 17_fix,0.785398163397));
}
