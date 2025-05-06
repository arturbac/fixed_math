// SPDX-FileCopyrightText: 2020-2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0
// SPDX-PackageHomePage: https://github.com/arturbac/fixed_math

#pragma once
#include "math.h"
#include "fixed_string.h"
#include <format>

// TODO add precision handling
template<>
struct std::formatter<fixedmath::fixed_t>
  {
  template<typename ParseContext>
  constexpr auto parse(ParseContext & ctx) -> decltype(ctx.begin())
    {
    return ctx.begin();
    }

  template<typename FormatContext>
  auto format(fixedmath::fixed_t const & value, FormatContext & ctx) const -> decltype(ctx.out())
    {
    return format_to(ctx.out(), "{}", fixedmath::func::to_string(value));
    }
  };
