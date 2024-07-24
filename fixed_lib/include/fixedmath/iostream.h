// SPDX-FileCopyrightText: 2020-2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0
// SPDX-PackageHomePage: https://github.com/arturbac/fixed_math

#pragma once
#include "math.h"

#include <iostream>
#include <iomanip>

namespace fixedmath
  {
inline std::ostream & operator<<(std::ostream & outstr, fixed_t src)
  {
  if(src != std::numeric_limits<fixed_t>::quiet_NaN())
    outstr << std::fixed << std::setprecision(16) << static_cast<double>(src);
  else
    outstr << "NaN";
  return outstr;
  }
  }  // namespace fixedmath
