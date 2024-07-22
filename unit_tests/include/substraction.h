#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_substract
  //
[[nodiscard]]
constexpr bool substraction_unit_tests() noexcept
  {
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
  static_assert( limits_::max() -1 != limits_::quiet_NaN() );
  
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
  
  return true;
  }
  static_assert(substraction_unit_tests());
}
