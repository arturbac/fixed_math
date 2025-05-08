#include <unit_test_core.h>
#include <unit_test_common.h>
#include <fixedmath/std_formatter.h>
#include <print>
using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
using namespace fixedmath::func;

int main()
  {
  test_result result;

  static_assert(fixedmath::fobj::fmod(-21_fix, 6.125_fix).v == (-2.625_fix).v);
  static_assert((int64_t(-21) % 6.125_fix).v== (-2.625_fix).v);

  "modulo"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(1_fix % 1_fix, 0_fix);
      expect_eq(-1_fix % 1_fix, 0_fix);
      expect_eq(1_fix % -1_fix, 0_fix);
      expect_eq(-1_fix % -1_fix, 0_fix);
      expect_eq(3_fix % 2_fix, 1_fix);
      expect_eq(3_fix % 4_fix, 3_fix);
      expect_eq(13_fix % 5.5_fix, 2_fix);
      expect_eq(21_fix % 6.125_fix, 2.625_fix);
      
      expect_eq(-21_fix % 6.125_fix, -2.625_fix);
      expect_eq(uint8_t(21) % 6.125_fix, 2.625_fix);
      expect_eq(uint16_t(21) % 6.125_fix, 2.625_fix);
      expect_eq(uint64_t(21) % 6.125_fix, 2.625_fix);
      expect_eq(int64_t(-21) % 6.125_fix, -2.625_fix);
      expect_eq(int32_t(-21) % 6.125_fix, -2.625_fix);
      expect_eq(int16_t(-21) % 6.125_fix, -2.625_fix);
      expect_eq(int8_t(-21) % 6.125_fix, -2.625_fix);
      
      expect_eq(21_fix % -6.125_fix, 2.625_fix);
      expect_eq(-21_fix % -6.125_fix, -2.625_fix);
      
      expect_eq(-21.625_fix % -6_fix, -3.625_fix);
      expect_eq(-21.625_fix % int32_t(-6), -3.625_fix);
      expect_eq(-21.625_fix % int16_t(-6), -3.625_fix);
      expect_eq(-21.625_fix % int8_t(-6), -3.625_fix);
      
      expect_eq(-21.625_fix % 6_fix, -3.625_fix);
      expect_eq(-21.625_fix % int32_t(6), -3.625_fix);
      expect_eq(-21.625_fix % int16_t(6), -3.625_fix);
      expect_eq(-21.625_fix % int8_t(6), -3.625_fix);

      expect_eq(21.625_fix % -6_fix, 3.625_fix);
      expect_eq(21.625_fix % int32_t(-6), 3.625_fix);
      expect_eq(21.625_fix % int16_t(-6), 3.625_fix);
      expect_eq(21.625_fix % int8_t(-6), 3.625_fix);
      
      expect_eq(0.625_fix % -6_fix, 0.625_fix);
      expect_eq(0.625_fix % int32_t(-6), 0.625_fix);
      expect_eq(0.625_fix % int16_t(-6), 0.625_fix);
      expect_eq(0.625_fix % int8_t(-6), 0.625_fix);
      
      expect_eq(0.505_fix % 0.125_fix, 0.005_fix);
      expect_eq(0.505_fix % -0.125_fix, 0.005_fix);
      expect_eq(-0.505_fix % -0.125_fix, -0.005_fix);
      
      expect(test_resulting_type<fixed_t>(int64_t(1) % 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix % int64_t(1)));
      expect(test_resulting_type<fixed_t>(uint64_t(1) % 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix % uint64_t(1)));
      expect(test_resulting_type<fixed_t>(1_fix % 1_fix));
      expect(test_resulting_type<fixed_t>(1 % 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix % 1));
      expect(test_resulting_type<fixed_t>(int16_t(1) % 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix % int16_t(1)));
      expect(test_resulting_type<fixed_t>(uint16_t(1) % 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix % uint16_t(1)));
      expect(test_resulting_type<fixed_t>(int8_t(1) % 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix % int8_t(1)));
      expect(test_resulting_type<fixed_t>(uint8_t(1) % 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix % uint8_t(1)));
      expect(test_resulting_type<fixed_t>(1.f % 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix % 1.f));

      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }
