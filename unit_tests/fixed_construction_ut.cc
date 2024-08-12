#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using F = fixedmath::fixed_internal;
using namespace fixedmath;

using concepts::fixed_point;

static_assert(fixed_point<fixed_t>);
static_assert(!fixed_point<double>);
static_assert(!fixed_point<int64_t>);

using typetraits::is_integral_v;
static_assert(is_integral_v<int32_t>);
static_assert(is_integral_v<uint32_t>);
static_assert(is_integral_v<int16_t>);
static_assert(is_integral_v<int64_t>);
static_assert(!is_integral_v<double>);
static_assert(!is_integral_v<fixed_t>);

using typetraits::is_signed_v;
static_assert(is_signed_v<double>);
static_assert(is_signed_v<float>);
static_assert(is_signed_v<int64_t>);
static_assert(is_signed_v<int32_t>);
static_assert(is_signed_v<int16_t>);
static_assert(is_signed_v<int8_t>);
static_assert(!is_signed_v<uint64_t>);
static_assert(!is_signed_v<uint32_t>);
static_assert(!is_signed_v<uint16_t>);
static_assert(!is_signed_v<uint8_t>);
static_assert(is_signed_v<fixed_t>);

using typetraits::is_unsigned_v;
static_assert(!is_unsigned_v<double>);
static_assert(!is_unsigned_v<float>);
static_assert(!is_unsigned_v<int64_t>);
static_assert(!is_unsigned_v<int32_t>);
static_assert(!is_unsigned_v<int16_t>);
static_assert(!is_unsigned_v<int8_t>);
static_assert(is_unsigned_v<uint64_t>);
static_assert(is_unsigned_v<uint32_t>);
static_assert(is_unsigned_v<uint16_t>);
static_assert(is_unsigned_v<uint8_t>);
static_assert(!is_unsigned_v<fixed_t>);

using concepts::arithmetic;
static_assert(arithmetic<double>);
static_assert(arithmetic<float>);
static_assert(arithmetic<int64_t>);
static_assert(arithmetic<int32_t>);
static_assert(arithmetic<int16_t>);
static_assert(arithmetic<int8_t>);
static_assert(arithmetic<uint64_t>);
static_assert(arithmetic<uint32_t>);
static_assert(arithmetic<uint16_t>);
static_assert(arithmetic<uint8_t>);
static_assert(arithmetic<fixed_t>);

using typetraits::is_floating_point_v;

using typetraits::is_arithmetic_and_not_fixed_v;
static_assert(!is_arithmetic_and_not_fixed_v<fixed_t>);
static_assert(is_arithmetic_and_not_fixed_v<uint8_t>);
static_assert(is_arithmetic_and_not_fixed_v<uint16_t>);
static_assert(is_arithmetic_and_not_fixed_v<uint32_t>);
static_assert(is_arithmetic_and_not_fixed_v<uint64_t>);
static_assert(is_arithmetic_and_not_fixed_v<int8_t>);
static_assert(is_arithmetic_and_not_fixed_v<int16_t>);
static_assert(is_arithmetic_and_not_fixed_v<int32_t>);
static_assert(is_arithmetic_and_not_fixed_v<int64_t>);
static_assert(is_arithmetic_and_not_fixed_v<float>);
static_assert(is_arithmetic_and_not_fixed_v<double>);

using typetraits::is_arithmetic_and_one_is_fixed_v;
static_assert(is_arithmetic_and_one_is_fixed_v<float, fixed_t>);
static_assert(is_arithmetic_and_one_is_fixed_v<fixed_t, fixed_t>);
static_assert(is_arithmetic_and_one_is_fixed_v<double, fixed_t>);
static_assert(is_arithmetic_and_one_is_fixed_v<int64_t, fixed_t>);
static_assert(is_arithmetic_and_one_is_fixed_v<fixed_t, float>);
static_assert(is_arithmetic_and_one_is_fixed_v<fixed_t, double>);
static_assert(is_arithmetic_and_one_is_fixed_v<fixed_t, int64_t>);
static_assert(!is_arithmetic_and_one_is_fixed_v<int64_t, int64_t>);
static_assert(!is_arithmetic_and_one_is_fixed_v<float, double>);

using typetraits::one_of_is_double_v;
static_assert(!one_of_is_double_v<float, fixed_t>);
static_assert(!one_of_is_double_v<fixed_t, fixed_t>);
static_assert(one_of_is_double_v<double, fixed_t>);
static_assert(!one_of_is_double_v<int64_t, fixed_t>);
static_assert(!one_of_is_double_v<fixed_t, float>);
static_assert(one_of_is_double_v<fixed_t, double>);
static_assert(!one_of_is_double_v<fixed_t, int64_t>);
static_assert(!one_of_is_double_v<int64_t, int64_t>);
static_assert(one_of_is_double_v<float, double>);

int main()
  {
  test_result result;
  "fixed construction"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(fixed_t{1}, 1_fix);
      expect_eq(fixed_t{1u}, 1_fix);
      expect_eq(fixed_t{1lu}, 1_fix);
      expect_eq(fixed_t{1llu}, 1_fix);
      expect_eq(fixed_t{-1}, -1_fix);
      expect_eq(fixed_t{1.f}, 1_fix);
      expect_eq(fixed_t{-1.f}, -1_fix);
      expect_eq(fixed_t{2}, 2_fix);
      expect_eq(fixed_t{-2}, -2_fix);
      expect_eq(fixed_t{2.f}, 2_fix);
      expect_eq(fixed_t{-2.f}, -2_fix);
      expect_eq(fixed_t{4.f}, 4_fix);
      expect_eq(fixed_t{-4.f}, -4_fix);

      expect_eq(fixed_t{4096ll}, 4096_fix);
      expect_eq(fixed_t{-4096ll}, -4096_fix);
      expect_eq(fixed_t{4096llu}, 4096_fix);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }
