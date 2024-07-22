#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_division
  //
[[nodiscard]]
constexpr bool division_unit_tests() noexcept
  {
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
  
  return true;
  }
  
  static_assert(division_unit_tests());
}

