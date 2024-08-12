#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
int main()
  {
  test_result result;
  using F = fixedmath::fixed_internal;

  
  "arithmetic_to_fixed integrals"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(arithmetic_to_fixed(0), 0_fix);
      expect_eq(arithmetic_to_fixed(1), limits_::one());
      expect_eq(arithmetic_to_fixed(-1), -limits_::one());
      expect_neq(arithmetic_to_fixed(-1), limits_::one());
      expect_neq(arithmetic_to_fixed(-1), 0_fix);
      expect_neq(arithmetic_to_fixed(1), 0_fix);
      expect_neq(arithmetic_to_fixed(1), arithmetic_to_fixed(-1));
      expect_eq(arithmetic_to_fixed(1), arithmetic_to_fixed(1));

      expect_eq(0_fix, fixed_t{});
      expect_eq(1_fix, limits_::one());
      expect_eq(-1_fix, -limits_::one());
      expect_eq(as_fixed(F(0x80000000LL)), 32768_fix);
      expect_eq(as_fixed(F(0)), 0_fix);
      expect_eq(as_fixed(F(1ll << 32)), 65536_fix);

      //
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };

  "arithmetic_to_fixed floating point"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(arithmetic_to_fixed(0.f), 0_fix);
      expect_eq(arithmetic_to_fixed(-1.f), -limits_::one());
      expect_neq(arithmetic_to_fixed(-1.f), limits_::one());
      expect_neq(arithmetic_to_fixed(-1.f), 0_fix);
      expect_neq(arithmetic_to_fixed(1.f), 0_fix);
      expect_neq(arithmetic_to_fixed(1.f), arithmetic_to_fixed(-1));
      expect_eq(arithmetic_to_fixed(1.f), arithmetic_to_fixed(1));
      expect_eq(arithmetic_to_fixed(0.f), 0_fix);
      expect_eq(arithmetic_to_fixed(float(limits_::max_integral())), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(flimits_::max()), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(float(limits_::max_integral() + 1ll)), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(float(limits_::min_integral())), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(float(limits_::min_integral() - 1ll)), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(flimits_::lowest()), limits_::quiet_NaN());
      expect_neq(arithmetic_to_fixed(flimits_::min()), limits_::quiet_NaN());

      expect_eq(arithmetic_to_fixed(-1.), -limits_::one());
      expect_neq(arithmetic_to_fixed(-1.), limits_::one());
      expect_neq(arithmetic_to_fixed(-1.), 0_fix);
      expect_neq(arithmetic_to_fixed(1.), 0_fix);
      expect_neq(arithmetic_to_fixed(1.), arithmetic_to_fixed(-1));
      expect_eq(arithmetic_to_fixed(1.), arithmetic_to_fixed(1));
      expect_eq(arithmetic_to_fixed(double(limits_::max_integral())), limits_::quiet_NaN());
      expect_neq(arithmetic_to_fixed(double(limits_::max_integral() - 1ll)), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(double(limits_::max_integral() + 1ll)), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(double(limits_::min_integral())), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(double(limits_::min_integral() - 1ll)), limits_::quiet_NaN());
      expect_neq(arithmetic_to_fixed(double(limits_::min_integral() + 1ll)), limits_::quiet_NaN());
      expect_eq(arithmetic_to_fixed(dlimits_::lowest()), limits_::quiet_NaN());
      expect_neq(arithmetic_to_fixed(dlimits_::min()), limits_::quiet_NaN());
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };

  "fixed_to_arithmetic integrals"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(fixed_to_arithmetic<int>(0.25_fix), 0);
      expect_eq(fixed_to_arithmetic<int>(1.25_fix), 1);
      expect_eq(fixed_to_arithmetic<int>(100.25_fix), 100);
      expect_eq(fixed_to_arithmetic<int>(100.55_fix), 100);
      expect_eq(fixed_to_arithmetic<unsigned>(100.55_fix), 100u);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
#if !defined(_MSC_VER) || defined(__clang__)
    // skip msvc toolset undebugable nonsense consteval errors for completely valid code
    result |= run_consteval_test(fn_tmpl);
#endif
  };
  "fixed_to_arithmetic floating point"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      {
      static constexpr auto approx{std::numeric_limits<float>::epsilon()};

      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(0.f)), 0.f, approx);
      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(1.f)), 1.f, approx);
      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(0.25f)), 0.25f, approx);
      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(0.5f)), 0.5f, approx);
      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(0.75f)), 0.75f, approx);
      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(-1.f)), -1.f, approx);
      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(-0.25f)), -0.25f, approx);
      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(-0.5f)), -0.5f, approx);
      expect_approx(fixed_to_arithmetic<float>(arithmetic_to_fixed(-0.75f)), -0.75f, approx);
      }
      {
      static constexpr auto approx{std::numeric_limits<double>::epsilon()};
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(0.f)), 0., approx);
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(1.f)), 1., approx);
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(0.25f)), 0.25, approx);
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(0.5f)), 0.5, approx);
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(0.75f)), 0.75, approx);
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(-1.f)), -1., approx);
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(-0.25f)), -0.25, approx);
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(-0.5f)), -0.5, approx);
      expect_approx(fixed_to_arithmetic<double>(arithmetic_to_fixed(-0.75f)), -0.75, approx);
      }
    return {};
    };
    result |= run_runtime_test(fn_tmpl);
#if !defined(_MSC_VER) || defined(__clang__)
    // skip msvc toolset undebugable nonsense consteval errors for completely valid code
    result |= run_consteval_test(fn_tmpl);
#endif
  };
  }
