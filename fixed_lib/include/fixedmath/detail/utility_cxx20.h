// SPDX-FileCopyrightText: 2020-2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0
// SPDX-PackageHomePage: https://github.com/arturbac/fixed_math

#pragma once

#if !defined(SMALL_VECTORS_CXX_UTILITY)
#define SMALL_VECTORS_CXX_UTILITY 1

#include <type_traits>
#include <cstdint>
#include <limits>
#include <memory>
#include <utility>
#include <bit>
#include <concepts>

namespace cxx20
  {

using std::assume_aligned;
using std::bit_cast;
using std::byteswap;
using std::countl_zero;
using std::countr_zero;
  }  // namespace cxx20

namespace cxx23
  {
#if defined(__cpp_lib_to_underlying)
using std::to_underlying;
#else
template<class T>
constexpr std::underlying_type_t<T> to_underlying(T value) noexcept
  {
  return static_cast<std::underlying_type_t<T>>(value);
  }
#endif
  }  // namespace cxx23
#endif  // SMALL_VECTORS_CXX_UTILITY

