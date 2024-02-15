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
  using detail::is_fixed_v;

  static_assert( is_fixed_v<fixed_t> );
  static_assert( !is_fixed_v<double> );
  static_assert( !is_fixed_v<int64_t> );

  using detail::is_double_v;
  static_assert( is_double_v<double> );
  static_assert( !is_double_v<fixed_t> );
  static_assert( !is_double_v<int64_t> );

  using detail::is_integral_v;
  static_assert( is_integral_v<int32_t> );
  static_assert( is_integral_v<uint32_t> );
  static_assert( is_integral_v<int16_t> );
  static_assert( is_integral_v<int64_t> );
  static_assert( !is_integral_v<double> );
  static_assert( !is_integral_v<fixed_t> );
  
  using detail::is_signed_v;
  static_assert( is_signed_v<double> );
  static_assert( is_signed_v<float> );
  static_assert( is_signed_v<int64_t> );
  static_assert( is_signed_v<int32_t> );
  static_assert( is_signed_v<int16_t> );
  static_assert( is_signed_v<int8_t> );
  static_assert( !is_signed_v<uint64_t> );
  static_assert( !is_signed_v<uint32_t> );
  static_assert( !is_signed_v<uint16_t> );
  static_assert( !is_signed_v<uint8_t> );
  static_assert( is_signed_v<fixed_t> );
  
  using detail::is_unsigned_v;
  static_assert( !is_unsigned_v<double> );
  static_assert( !is_unsigned_v<float> );
  static_assert( !is_unsigned_v<int64_t> );
  static_assert( !is_unsigned_v<int32_t> );
  static_assert( !is_unsigned_v<int16_t> );
  static_assert( !is_unsigned_v<int8_t> );
  static_assert( is_unsigned_v<uint64_t> );
  static_assert( is_unsigned_v<uint32_t> );
  static_assert( is_unsigned_v<uint16_t> );
  static_assert( is_unsigned_v<uint8_t> );
  static_assert( !is_unsigned_v<fixed_t> );
  
  using detail::is_arithmetic_v;
  static_assert( detail::is_arithmetic_v<double> );
  static_assert( detail::is_arithmetic_v<float> );
  static_assert( detail::is_arithmetic_v<int64_t> );
  static_assert( detail::is_arithmetic_v<int32_t> );
  static_assert( detail::is_arithmetic_v<int16_t> );
  static_assert( detail::is_arithmetic_v<int8_t> );
  static_assert( detail::is_arithmetic_v<uint64_t> );
  static_assert( detail::is_arithmetic_v<uint32_t> );
  static_assert( detail::is_arithmetic_v<uint16_t> );
  static_assert( detail::is_arithmetic_v<uint8_t> );
  static_assert( detail::is_arithmetic_v<fixed_t> );

  using detail::is_floating_point_v;
  
  using detail::is_arithmetic_and_not_fixed_v;
  static_assert( !is_arithmetic_and_not_fixed_v<fixed_t> );
  static_assert( is_arithmetic_and_not_fixed_v<uint8_t> );
  static_assert( is_arithmetic_and_not_fixed_v<uint16_t> );
  static_assert( is_arithmetic_and_not_fixed_v<uint32_t> );
  static_assert( is_arithmetic_and_not_fixed_v<uint64_t> );
  static_assert( is_arithmetic_and_not_fixed_v<int8_t> );
  static_assert( is_arithmetic_and_not_fixed_v<int16_t> );
  static_assert( is_arithmetic_and_not_fixed_v<int32_t> );
  static_assert( is_arithmetic_and_not_fixed_v<int64_t> );
  static_assert( is_arithmetic_and_not_fixed_v<float> );
  static_assert( is_arithmetic_and_not_fixed_v<double> );

  using detail::arithmetic_and_one_is_fixed_v;
  static_assert( arithmetic_and_one_is_fixed_v<float,fixed_t> );
  static_assert( arithmetic_and_one_is_fixed_v<fixed_t,fixed_t> );
  static_assert( arithmetic_and_one_is_fixed_v<double,fixed_t> );
  static_assert( arithmetic_and_one_is_fixed_v<int64_t,fixed_t> );
  static_assert( arithmetic_and_one_is_fixed_v<fixed_t,float> );
  static_assert( arithmetic_and_one_is_fixed_v<fixed_t,double> );
  static_assert( arithmetic_and_one_is_fixed_v<fixed_t,int64_t> );
  static_assert( !arithmetic_and_one_is_fixed_v<int64_t,int64_t> );
  static_assert( !arithmetic_and_one_is_fixed_v<float,double> );
  
  using detail::one_of_is_double_v;
  static_assert( !one_of_is_double_v<float,fixed_t> );
  static_assert( !one_of_is_double_v<fixed_t,fixed_t> );
  static_assert( one_of_is_double_v<double,fixed_t> );
  static_assert( !one_of_is_double_v<int64_t,fixed_t> );
  static_assert( !one_of_is_double_v<fixed_t,float> );
  static_assert( one_of_is_double_v<fixed_t,double> );
  static_assert( !one_of_is_double_v<fixed_t,int64_t> );
  static_assert( !one_of_is_double_v<int64_t,int64_t> );
  static_assert( one_of_is_double_v<float,double> );

  return true;
  }
  
  static_assert(type_traits_unit_tests());
}

