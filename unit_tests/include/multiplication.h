#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
[[nodiscard]]
constexpr bool multiplication_unit_tests() noexcept
  {
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_multiply
  //
  static_assert( 1_fix * 1_fix  == 1_fix );
  static_assert( 10_fix * 0.5_fix  == 5_fix );
  static_assert( abs(0.8_fix * 0.2_fix)  - 0.16_fix <= limits_::epsilon() );
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
  
  return true;
  }
  
  static_assert(multiplication_unit_tests());
}
