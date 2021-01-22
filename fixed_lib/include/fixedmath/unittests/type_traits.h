#pragma once

#include "unit_test_common.h"

namespace fixedmath
{

using detail::limits__;
using detail::flimits__;
using detail::dlimits__;

//------------------------------------------------------------------------------------------------------
//
// type traits
//
using detail::is_fixed_v;

static_assert( is_fixed_v<fixed_t> );
static_assert( is_fixed_v<fixed_t const &> );
static_assert( is_fixed_v<fixed_t> ); static_assert( is_fixed_v<fixed_t const &> );
static_assert( !is_fixed_v<double> );
static_assert( !is_fixed_v<int64_t> );

using detail::is_double_v;
static_assert( is_double_v<double> ); static_assert( is_double_v<double const &> );
static_assert( !is_double_v<fixed_t> );
static_assert( !is_double_v<int64_t> );

using detail::is_integral_v;
static_assert( is_integral_v<int32_t> );
static_assert( is_integral_v<uint32_t> ); static_assert( is_integral_v<uint32_t const &> );
static_assert( is_integral_v<int16_t> ); static_assert( is_integral_v<int16_t const & > );
static_assert( is_integral_v<int64_t> );
static_assert( !is_integral_v<double> );
static_assert( !is_integral_v<fixed_t> );
static_assert( std::is_signed<fixed_t>::value );
static_assert( std::is_arithmetic<fixed_t>::value );

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

}

