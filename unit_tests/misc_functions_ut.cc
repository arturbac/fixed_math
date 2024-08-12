#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
using namespace fixedmath::func;

int main()
  {
  test_result result;

  "ceil"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(ceil(-0.25_fix), 0_fix);
      expect_eq(ceil(-1.25_fix), -1_fix);
      expect_eq(ceil(-10.25_fix), -10_fix);
      expect_eq(ceil(-10.95_fix), -10_fix);
      expect_eq(ceil(0.25_fix), 1_fix);
      expect_eq(ceil(0.75_fix), 1_fix);
      expect_eq(ceil(as_fixed(fixed_internal(1ul))), 1_fix);
      expect_eq(ceil(5.25_fix), 6_fix);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };

  "floor"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(fixed_to_arithmetic<int>(floor(0.25_fix)), 0);
      expect_eq(floor(-1_fix + limits_::epsilon()), -1_fix);  //
      expect_eq(floor(-1_fix - limits_::epsilon()), -2_fix);  //
      expect_eq(floor(-0.25_fix), -1_fix);
      expect_eq(floor(0.25_fix), 0_fix);
      expect_eq(floor(0.95_fix), 0_fix);
      expect_eq(floor(1.25_fix), 1_fix);
      expect_eq(floor(-1.25_fix), -2_fix);

      return {};
    };
    result |= run_runtime_test(fn_tmpl);
#if !defined(_MSC_VER) || defined(__clang__)
    // skip msvc toolset undebugable nonsense consteval errors for completely valid code
    result |= run_consteval_test(fn_tmpl);
#endif
  };

  "angle_to_radians"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(angle_to_radians(0), 0_fix);
      expect_eq(angle_to_radians(180), 3.1415926536_fix);
      expect_eq(angle_to_radians(180), phi);
      expect_eq(angle_to_radians(90), phi / 2);
      expect_eq(angle_to_radians(45), phi / 4);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }
