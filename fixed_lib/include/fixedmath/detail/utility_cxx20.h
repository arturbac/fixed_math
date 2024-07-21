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

