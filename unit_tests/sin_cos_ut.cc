#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
using namespace fixedmath::func;

constexpr void
  test_sin(fixed_t x, fixed_t expected, fixed_t aprox, source_location const location = source_location::current())
  {
  expect_approx(sin(x), expected, aprox, location);
  expect_approx(sin(x + 2 * phi), expected, aprox, location);
  expect_approx(sin(x - 2 * phi), expected, aprox, location);
  expect_approx(sin(x + 4 * phi), expected, aprox, location);
  }

constexpr void
  test_cos(fixed_t x, fixed_t expected, fixed_t aprox, source_location const location = source_location::current())
  {
  expect_approx(cos(x), expected, aprox, location);
  expect_approx(cos(x + 2 * phi), expected, aprox, location);
  expect_approx(cos(x - 2 * phi), expected, aprox, location);
  expect_approx(cos(x + 4 * phi), expected, aprox, location);
  }

int main()
  {
  test_result result;
  "sin"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      test_sin(phi + phi / 2, -0.99986_fix, 0.0001_fix);
      test_sin(phi + phi / 4, -0.7071_fix, 0.0001_fix);
      test_sin(phi, 0_fix, 0.0001_fix);
      test_sin(0_fix, 0_fix, 0.0001_fix);
      test_sin(phi / 2 + phi / 4, 0.7071_fix, 0.0001_fix);

      test_sin(phi / 2_fix, 0.99984_fix, 0.0001_fix);
      test_sin(phi / 4_fix, 0.70709_fix, 0.0001_fix);
      test_sin(phi / 5_fix, 0.58778_fix, 0.0001_fix);
      test_sin(phi / 8_fix, 0.38265_fix, 0.0001_fix);
      test_sin(phi / 16_fix, 0.19506_fix, 0.0001_fix);
      test_sin(-phi / 16_fix, -0.19508_fix, 0.0001_fix);
      test_sin(phi / -8_fix, -0.38267_fix, 0.0001_fix);
      test_sin(phi / -5_fix, -0.58779_fix, 0.0001_fix);
      test_sin(phi / -4_fix, -0.7071_fix, 0.0001_fix);
      test_sin(phi / -2_fix, -0.99986_fix, 0.0001_fix);

      test_sin(phi + phi + phi / 2, 0.99984_fix, 0.0001_fix);
      test_sin(phi + phi + phi / 4, 0.70709_fix, 0.0001_fix);
      test_sin(phi + phi, 0_fix, 0.0001_fix);
      test_sin(phi + phi / 2 + phi / 4, -0.70712_fix, 0.0001_fix);
      test_sin(2 * phi + phi + phi / 2, -0.99986_fix, 0.0001_fix);
      test_sin(2 * phi + phi + phi / 4, -0.7071_fix, 0.0001_fix);
      test_sin(2 * phi + phi, 0_fix, 0.0001_fix);
      test_sin(2 * phi + phi / 2 + phi / 4, 0.7071_fix, 0.0001_fix);

      test_sin(-phi - phi / 16, 0.19506_fix, 0.0001_fix);
      test_sin(-phi - phi / 8, 0.38265_fix, 0.0001_fix);
      test_sin(-phi - phi / 5, 0.58778_fix, 0.0001_fix);
      test_sin(-phi - phi / 4, 0.70709_fix, 0.0001_fix);
      test_sin(-phi - phi / 2, 0.99984_fix, 0.0001_fix);

      test_sin(-6 * phi + -95 * phi / 180, -0.99612_fix, 0.0001_fix);
      test_sin(-4 * phi + -95 * phi / 180, -0.99612_fix, 0.0001_fix);
      test_sin(-2 * phi + -95 * phi / 180, -0.99612_fix, 0.0001_fix);
      test_sin(-95 * phi / 180, -0.99612_fix, 0.0001_fix);
      test_sin(-90 * phi / 180, -0.99986_fix, 0.0001_fix);
      test_sin(-85 * phi / 180, -0.99610_fix, 0.0001_fix);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
#if !defined(_MSC_VER) || defined(__clang__)
    // skip msvc toolset undebugable nonsense consteval errors for completely valid code
    result |= run_consteval_test(fn_tmpl);
#endif
  };

  "cos"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      test_cos(2 * phi, 0.9998_fix, 0.0001_fix);
      test_cos(phi, -0.9998_fix, 0.0001_fix);
      test_cos(phi / 2 + phi / 4, -0.7071_fix, 0.0001_fix);
      test_cos(phi / 2, 0_fix, 0.0001_fix);
      test_cos(phi / 3, 0.49998_fix, 0.0001_fix);
      test_cos(phi / 4, 0.7071_fix, 0.0001_fix);
      test_cos(phi / 16, 0.98072_fix, 0.0001_fix);
      test_cos(0_fix, 0.99984_fix, 0.0001_fix);
      test_cos(-phi / 16, 0.98074_fix, 0.0001_fix);
      test_cos(-phi / 4, 0.7071_fix, 0.0001_fix);
      test_cos(-phi / 3, 0.5_fix, 0.0001_fix);
      test_cos(-phi / 2, 0.0001_fix, 0.00014_fix);
      test_cos(-phi / 2 + -phi / 4, -0.70709_fix, 0.0001_fix);
      test_cos(-phi, -0.99986_fix, 0.0001_fix);
      test_cos(2 * -phi, 0.99984_fix, 0.0001_fix);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
#if !defined(_MSC_VER) || defined(__clang__)
    // skip msvc toolset undebugable nonsense consteval errors for completely valid code
    result |= run_consteval_test(fn_tmpl);
#endif
  };
  }

//
