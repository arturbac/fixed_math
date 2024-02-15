#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
[[nodiscard]]
constexpr bool misc_functions_unit_tests() noexcept
  {
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
  static_assert( floor( -1_fix + limits_::epsilon()) == -1_fix ); //
  static_assert( floor( -1_fix - limits_::epsilon()) == -2_fix ); //
  static_assert( floor(-0.25_fix) == -1_fix );
  static_assert( floor(0.25_fix) == 0_fix );
  static_assert( floor(0.95_fix) == 0_fix );
  static_assert( floor(1.25_fix) == 1_fix );
  static_assert( floor(-1.25_fix) == -2_fix );
  
  //------------------------------------------------------------------------------------------------------
  //
  // angle_to_radians
  //
  static_assert( angle_to_radians(0) == 0_fix );
  static_assert( angle_to_radians(180) == 3.1415926536_fix );
  static_assert( angle_to_radians(180) == phi );
  static_assert( angle_to_radians(90) == phi/2 );
  static_assert( angle_to_radians(45) == phi/4 );
  
  return true;
  }
  
  static_assert(misc_functions_unit_tests());
}
