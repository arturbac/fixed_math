#pragma once

#include "../types.h"
#include <type_traits>

#define FIXEDMATH_PUBLIC gnu::visibility("default")

namespace fixedmath::inline v2::detail
  {

template<int digits>
[[gnu::const, gnu::always_inline]]
constexpr auto unsigned_shift_left_signed(fixed_internal value) noexcept -> fixed_internal
  {
  using unsigned_internal = std::make_unsigned_t<fixed_internal>;
  return static_cast<fixed_internal>(
    (static_cast<unsigned_internal>(value) << digits)
    | (static_cast<unsigned_internal>(value) & (unsigned_internal(1) << 63u))
  );
  }

template<typename value_type>
[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto promote_type_to_signed(value_type value) noexcept
  {
  if constexpr(std::is_signed_v<value_type>)
    return value;
  else
    {
    using signed_type = typetraits::promote_to_signed_t<value_type>;
    return static_cast<signed_type>(value);
    }
  }

template<int digits>
[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto unsigned_shift_left_unsigned(fixed_internal value) noexcept -> fixed_internal
  {
  using unsigned_internal = std::make_unsigned_t<fixed_internal>;
  return static_cast<fixed_internal>(static_cast<unsigned_internal>(value) << digits);
  }

[[nodiscard, gnu::const, gnu::always_inline]]
///\returns the highest power of 4 that is less than or equal to \ref value
constexpr auto highest_pwr4_clz(fixed_internal_unsigned value) noexcept -> fixed_internal
  {
  if(value != 0) [[likely]]
    {
    int clz{std::countl_zero(value)};

    clz = (64 - clz);
    if((clz & 1) == 0)
      clz -= 1;

    return fixed_internal(1ll << (clz - 1));
    }
  return 0;
  }

[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto highest_pwr4(fixed_internal_unsigned value) noexcept -> fixed_internal
  {
  // one starts at the highest power of four <= than the argument.
  fixed_internal_unsigned pwr4{1ll << 62};  // second-to-top bit set

  while(pwr4 > value)
    pwr4 >>= 2;
  return fixed_internal(pwr4);
  }

template<int precision>
[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto mul_(fixed_internal x, fixed_internal y) noexcept -> fixed_internal
  {
  return (x * y) >> precision;
  }

template<int precision>
[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto div_(fixed_internal x, fixed_internal y) noexcept -> fixed_internal
  {
  return (x << precision) / y;
  }

template<int precision>
[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto fix_(fixed_internal x) noexcept -> fixed_internal
  {
  return (x << precision);
  }

[[nodiscard, gnu::const, gnu::always_inline]]
constexpr auto set_sign(bool sign_, fixed_internal result) -> fixed_t
  {
  if(!sign_)
    return as_fixed(result);
  return as_fixed(-result);
  }

template<concepts::arithmetic T>
constexpr void swap(T & a, T & b) noexcept
  {
  T temp = a;
  a = b;
  b = temp;
  }
  }  // namespace fixedmath::detail

