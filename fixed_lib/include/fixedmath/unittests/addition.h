#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  //
  // fixed_addition
  //
[[nodiscard]]
constexpr bool addition_unit_tests() noexcept
  {
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
  static_assert( limits_::max() < limits_::quiet_NaN() );
  static_assert( limits_::lowest() +1 != limits_::quiet_NaN() );
  
  static_assert( as_fixed(limits_::max().v- 65536) + 1_fix != limits_::quiet_NaN() );
  
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
  
  constexpr auto i1 = 1_fix;
  constexpr auto i2 = 10_fix;
  auto const & i1r { i1 };
  auto const & i2r { i2 };
  if( i1r + i2r != 11_fix )
    return false;
  
  return true;
  }
  
  static_assert(addition_unit_tests());
}
