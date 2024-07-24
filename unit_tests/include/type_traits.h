#pragma once

#include "unit_test_common.h"

namespace fixedmath
{

using detail::limits_;
using detail::flimits_;
using detail::dlimits_;
[[nodiscard]]
constexpr bool type_traits_unit_tests() noexcept
  {
  //------------------------------------------------------------------------------------------------------
  //
  // type traits
  //


  return true;
  }
  
  static_assert(type_traits_unit_tests());
}

