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

#include "types.h"
namespace fixedmath
{
  
}
namespace std
{
  template<>
  struct numeric_limits<fixedmath::fixed_t>
    {
    using value_type = fixedmath::fixed_t;
    using fixed_internal = fixedmath::fixed_internal;
    using fix_carrier_t = fixedmath::fix_carrier_t;
    
    static constexpr bool is_integer { false };
    static constexpr bool is_specialized { true };
    static constexpr bool is_signed { true };
    static constexpr bool is_exact{ true };
    static constexpr bool has_infinity{};
    static constexpr bool has_quiet_NaN{ true };
    static constexpr bool has_signaling_NaN{};
    static constexpr float_denorm_style has_denorm{denorm_absent};
    static constexpr bool has_denorm_loss{};
    static constexpr float_round_style round_style{round_toward_zero};
    static constexpr bool is_iec559{};
    static constexpr bool is_bounded{true};
    static constexpr bool is_modulo{};
    static constexpr int digits{16};
    static constexpr int digits10{4};
    static constexpr int max_digits10{6};
    static constexpr int radix{2};
    static constexpr bool traps{true};
    static constexpr bool tinyness_before{};
    
    static constexpr value_type min() noexcept{ return fix_carrier_t{fixed_internal{1}}; };
    static constexpr value_type lowest() noexcept{ return fix_carrier_t{fixed_internal{-0x7FFFFFFFFFFFFFFEll}}; };
    static constexpr value_type max() noexcept { return fix_carrier_t{fixed_internal{0x7FFFFFFFFFFFFFFEll}}; }
    static constexpr value_type one() noexcept { return fix_carrier_t{fixed_internal{65536}}; }
    static constexpr value_type epsilon() noexcept { return fix_carrier_t{fixed_internal{1}}; }
    static constexpr value_type round_error() noexcept { return fix_carrier_t{fixed_internal{1}}; }
    static constexpr value_type quiet_NaN() noexcept { return fix_carrier_t{fixed_internal{0x7FFFFFFFFFFFFFFFll}}; }
    
    static constexpr int32_t max_integral() noexcept { return 2147483647; }
    static constexpr int32_t min_integral() noexcept{ return -2147483647; };
    };

}
namespace fixedmath
{
inline constexpr fixed_t quiet_NaN_result() noexcept { return std::numeric_limits<fixed_t>::quiet_NaN(); }
}

