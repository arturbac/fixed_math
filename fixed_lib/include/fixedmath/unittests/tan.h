#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
  //------------------------------------------------------------------------------------------------------
  //
  // tan
  //
  constexpr bool test_tan( fixed_t x, double expected )
    {
    return ut_abs(tan( x ) - expected ) < 0.0001 && ut_abs(tan( -x ) - -expected ) < 0.0001;
    }
[[nodiscard]]
constexpr bool tan_unit_tests() noexcept
  {
  static_assert(test_tan( phi /2 + phi /32 , -10.155854941143394 ));
  static_assert(test_tan( phi /3, 1.7320423410947752 ));
  static_assert(test_tan( phi /4, 0.9999739372166156 ));
  static_assert(test_tan( phi /5, 0.7265312623733221 ));
  static_assert(test_tan( phi /8, 0.4141969903665098 ));
  static_assert(test_tan( phi /16, 0.1988970837416414 ));
  static_assert(test_tan( 0_fix , 0.));
  
  return true;
  }
  
  static_assert(tan_unit_tests());
}
