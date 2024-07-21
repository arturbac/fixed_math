// MIT License
//
// Copyright (c) 2020-2021 Artur Bac
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include "detail/type_traits.h"

#define FIXEDMATH_VERSION_MAJOR 2
#define FIXEDMATH_VERSION_MINOR 0
#define FIXEDMATH_VERSION_PATCH 0
#define FIXEDMATH_VERSION_STRING "2.0.0"

namespace fixedmath::inline v2
  {
// the idea behind carrier is to use it as carier of internal int64 value in format of fixed to distinguish it from
// int64 integral type.
struct fix_carrier_t
  {
  fixed_internal v{};

  constexpr fix_carrier_t() noexcept = default;

  template<std::same_as<fixed_internal> input_type>
  explicit constexpr fix_carrier_t(input_type const & value) noexcept : v{value}
    {
    }
  };

///\brief hermetization of fixed value to avoid implicit conversions from int64, long long
struct fixed_t
  {
  fixed_internal v{};

  template<concepts::arithmetic_and_not_fixed arithmethic_type>
  explicit constexpr operator arithmethic_type() const noexcept;

  constexpr fixed_t() noexcept = default;

  constexpr fixed_t(fix_carrier_t value) noexcept : v{value.v} {}

  template<concepts::arithmetic_and_not_fixed arithmethic_type>
  explicit constexpr fixed_t(arithmethic_type value) noexcept;
  };

struct as_fixed_t
  {
  constexpr auto operator()(fixed_internal carried) const noexcept -> fixed_t { return fix_carrier_t{carried}; }
  };

///\brief constructs fixed from raw value in internal format
inline constexpr as_fixed_t as_fixed;

[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto operator==(fixed_t l, fixed_t r) noexcept -> bool
  {
  return l.v != r.v;
  }

[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto operator<=>(fixed_t l, fixed_t r) noexcept
  {
  return l.v <=> r.v;
  }

  }  // namespace fixedmath

