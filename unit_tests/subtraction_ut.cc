#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;

int main()
  {
  test_result result;
  "addition"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(0.2_fix - 1.2_fix, -1_fix);
      expect_eq(3.2_fix - 1.2_fix, 2_fix);
      expect_eq(-4.2_fix - 1.2_fix, -5.4_fix);
      expect_eq(-4.2_fix + 1.2_fix, -3_fix);
      
      static constexpr auto approx{std::numeric_limits<double>::epsilon()};
      expect_approx(1_fix - 1., 1. - 1., approx);
      expect_approx(2_fix - 1., 2. - 1., approx);
      expect_approx(-2_fix - 1., -2. - 1., approx);
      expect_approx(-2_fix + 1., -2. + 1., approx);
      
      expect_eq(-10.5_fix - uint8_t(10), -20.5_fix);
      expect_eq(-10.5_fix - uint16_t(10), -20.5_fix);
      expect_eq(-10.5_fix - uint32_t(10), -20.5_fix);
      expect_eq(-10.5_fix - uint64_t(10), -20.5_fix);
      expect_eq(uint8_t(10) - 10.5_fix, -.5_fix);
      expect_eq(uint16_t(10) - 10.5_fix, -.5_fix);
      expect_eq(uint32_t(10) - 10.5_fix, -.5_fix);
      expect_eq(uint64_t(10) - 10.5_fix, -.5_fix);
      expect_neq(limits_::max() - 1, limits_::quiet_NaN());

      expect(test_resulting_type<fixed_t>(int64_t(1) - 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix - int64_t(1)));
      expect(test_resulting_type<fixed_t>(uint64_t(1) - 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix - uint64_t(1)));
      expect(test_resulting_type<fixed_t>(1_fix - 1_fix));
      expect(test_resulting_type<fixed_t>(1 - 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix - 1));
      expect(test_resulting_type<fixed_t>(int16_t(1) - 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix - int16_t(1)));
      expect(test_resulting_type<fixed_t>(uint16_t(1) - 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix - uint16_t(1)));
      expect(test_resulting_type<fixed_t>(int8_t(1) - 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix - int8_t(1)));
      expect(test_resulting_type<fixed_t>(uint8_t(1) - 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix - uint8_t(1)));
      expect(test_resulting_type<fixed_t>(1.f - 1_fix));
      expect(test_resulting_type<fixed_t>(1_fix - 1.f));
      expect(test_resulting_type<double>(1. - 1_fix));
      expect(test_resulting_type<double>(1_fix - 1.));
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }
