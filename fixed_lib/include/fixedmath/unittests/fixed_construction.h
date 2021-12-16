#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
[[nodiscard]]
constexpr bool fixed_construction_unit_tests() noexcept
  {
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
  
  return true;
  }
  
  static_assert(fixed_construction_unit_tests());
}
