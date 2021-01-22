#pragma once

#include "unit_test_common.h"

namespace fixedmath
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
}
