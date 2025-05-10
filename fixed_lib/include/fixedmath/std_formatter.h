// SPDX-FileCopyrightText: 2020-2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0
// SPDX-PackageHomePage: https://github.com/arturbac/fixed_math

#pragma once
#include "math.h"
#include "fixed_string.h"
#include <format>
#include <algorithm>
#include <charconv>

template<>
struct std::formatter<fixedmath::fixed_t>
  {
  int precision = fixedmath::func::from_string_default_precision;

  template<typename ParseContext>
  constexpr auto parse(ParseContext & ctx) -> decltype(ctx.begin())
    {
    auto it = ctx.begin();
#ifdef __cpp_lib_to_chars
    if(it != ctx.end() && *it != '}')
      {
      if(auto parse_res{std::from_chars(it, ctx.end(), precision)}; parse_res.ec == std::errc{})
        it = parse_res.ptr;
      else
        throw std::format_error("Invalid fixed_t precision format");
      }
#endif
    return it;
    }

  template<typename FormatContext>
  auto format(fixedmath::fixed_t const & value, FormatContext & ctx) const -> decltype(ctx.out())
    {
    auto const formatted{fixedmath::func::to_string(value, precision)};
    return std::copy(formatted.begin(), formatted.end(), ctx.out());
    }
  };
