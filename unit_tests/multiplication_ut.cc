#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
using namespace fixedmath::func;

int main()
  {
  test_result result;
  using F = fixedmath::fixed_internal;
  "multiplication"_test = [&result]
  {
    auto fn_tmpl = [] -> metatests::test_result
    {
      expect_eq(1_fix * 1_fix, 1_fix);
      expect_eq(10_fix * 0.5_fix, 5_fix);

      expect_approx(0.8_fix * 0.2_fix, 0.16000_fix, 0.0001_fix);
      expect_approx(0.8_fix * -0.2_fix, -0.16000_fix, 0.0001_fix);

      expect_eq(-1.25_fix * int8_t(4), -5_fix);
      expect_eq(-1.25_fix * int16_t(4), -5_fix);
      expect_eq(-1.25_fix * int32_t(4), -5_fix);
      expect_eq(-1.25_fix * int64_t(4), -5_fix);

      expect_eq(-1.25_fix * uint8_t(4), -5_fix);
      expect_eq(-1.25_fix * uint16_t(4), -5_fix);
      expect_eq(-1.25_fix * uint32_t(4), -5_fix);
      expect_eq(-1.25_fix * uint64_t(4), -5_fix);

      expect_eq(int8_t(4) * -1.25_fix, -5_fix);
      expect_eq(int16_t(4) * -1.25_fix, -5_fix);
      expect_eq(int32_t(4) * -1.25_fix, -5_fix);
      expect_eq(int64_t(4) * -1.25_fix, -5_fix);

      expect_eq(uint8_t(4) * -1.25_fix, -5_fix);
      expect_eq(uint16_t(4) * -1.25_fix, -5_fix);
      expect_eq(uint32_t(4) * -1.25_fix, -5_fix);
      expect_eq(uint64_t(4) * -1.25_fix, -5_fix);

      expect(test_resulting_type<fixed_t>(int64_t(1) * 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix * int64_t(1)));
      expect(test_resulting_type<fixed_t>(uint64_t(1) * 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix * uint64_t(1)));
      expect(test_resulting_type<fixed_t>(1_fix * 1_fix));
      expect(test_resulting_type<fixed_t>(1 * 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix * 1));
      expect(test_resulting_type<fixed_t>(int16_t(1) * 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix * int16_t(1)));
      expect(test_resulting_type<fixed_t>(uint16_t(1) * 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix * uint16_t(1)));
      expect(test_resulting_type<fixed_t>(int8_t(1) * 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix * int8_t(1)));
      expect(test_resulting_type<fixed_t>(uint8_t(1) * 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix * uint8_t(1)));
      expect(test_resulting_type<fixed_t>(1.f * 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix * 1.f));
      expect(test_resulting_type<double>(1. * 1_fix));
      expect(test_resulting_type<double>(1_fix * 1.));
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }
