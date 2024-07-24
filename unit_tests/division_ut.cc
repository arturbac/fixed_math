#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
using namespace fixedmath::func;

int main()
  {
  test_result result;
  
  "division"_test = [&result]
  {
    auto fn_tmpl = [] -> metatests::test_result
    {
      expect_eq(1_fix / 1_fix, 1_fix);
      expect_eq(-1_fix / 1_fix, -1_fix);
      expect_eq(1_fix / -1_fix, -1_fix);
      expect_eq(-1_fix / -1_fix, 1_fix);
      expect_eq(1_fix / 1, 1_fix);
      expect_eq(100_fix / 10_fix, 10_fix);
      expect_eq(100_fix / 10, 10_fix);
      expect_eq(-10_fix / 1, -10_fix);
      expect_eq(-10_fix / 1_fix, -10_fix);
      expect_eq(1_fix / 2_fix, 0.5_fix);
      expect_eq(1_fix / 4_fix, 0.25_fix);
      expect_eq(-1_fix / 4, -0.25_fix);

      expect_eq(int8_t{1} / -4_fix, -0.25_fix);
      expect_eq(int16_t{1} / -4_fix, -0.25_fix);
      expect_eq(int32_t{1} / -4_fix, -0.25_fix);
      expect_eq(int64_t{1} / -4_fix, -0.25_fix);
      expect_eq(float{1} / -4_fix, -0.25_fix);
      expect_approx(double{1} / -4_fix, -0.25, 0.0000000001);

      expect_eq(uint8_t{1} / -4_fix, -0.25_fix);
      expect_eq(uint16_t{1} / -4_fix, -0.25_fix);
      expect_eq(uint32_t{1} / -4_fix, -0.25_fix);
      expect_eq(uint64_t{1} / -4_fix, -0.25_fix);

      expect_eq(-1_fix / uint8_t(4), -0.25_fix);
      expect_eq(-1_fix / uint16_t(4), -0.25_fix);
      expect_eq(-1_fix / uint32_t(4), -0.25_fix);
      expect_eq(-1_fix / uint64_t(4), -0.25_fix);

      expect_eq(-1_fix / int8_t(4), -0.25_fix);
      expect_eq(-1_fix / int16_t(4), -0.25_fix);
      expect_eq(-1_fix / int32_t(4), -0.25_fix);
      expect_eq(-1_fix / int64_t(4), -0.25_fix);

      expect_eq(1 / 4_fix, 0.25_fix);
      
      expect_eq(4 / 1_fix, 4_fix);
      expect_eq(4 / 0.5_fix, 8_fix);
      
      expect_eq(1625.625_fix / 0.625_fix, 2601_fix);

      expect(test_resulting_type<fixed_t>(int64_t(1) / 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix / int64_t(1)));
      expect(test_resulting_type<fixed_t>(uint64_t(1) / 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix / uint64_t(1)));
      expect(test_resulting_type<fixed_t>(1_fix / 1_fix));
      expect(test_resulting_type<fixed_t>(1 / 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix / 1));
      expect(test_resulting_type<fixed_t>(int16_t(1) / 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix / int16_t(1)));
      expect(test_resulting_type<fixed_t>(uint16_t(1) / 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix / uint16_t(1)));
      expect(test_resulting_type<fixed_t>(int8_t(1) / 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix / int8_t(1)));
      expect(test_resulting_type<fixed_t>(uint8_t(1) / 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix / uint8_t(1)));
      expect(test_resulting_type<fixed_t>(1.f / 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix / 1.f));
      expect(test_resulting_type<double>(1. / 1_fix));
      expect(test_resulting_type<double>(1_fix / 1.));
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }
