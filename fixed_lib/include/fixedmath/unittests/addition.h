#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
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
}
