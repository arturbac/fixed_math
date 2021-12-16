#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
[[nodiscard]]
constexpr bool floating_point_type_convertions_unit_tests() noexcept
  {
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
  return true;
  }
  
  static_assert(floating_point_type_convertions_unit_tests());
}
