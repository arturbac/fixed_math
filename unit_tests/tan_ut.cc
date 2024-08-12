#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
using namespace fixedmath::func;

constexpr void
  test_tan(fixed_t x, fixed_t expected, fixed_t aprox, source_location const location = source_location::current())
  {
  expect_approx(tan(x), expected, aprox, location);
  expect_approx(tan(-x), -expected, aprox, location);
  }

int main()
  {
  test_result result;
  "tan"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      test_tan(phi / 2 + phi / 32, -10.155854941143394_fix, 0.0001_fix);
      test_tan(phi / 3, 1.73204_fix, 0.0001_fix);
      test_tan(phi / 4, 0.99997_fix, 0.0001_fix);
      test_tan(phi / 5, 0.72653_fix, 0.0001_fix);
      test_tan(phi / 8, 0.41419_fix, 0.0001_fix);
      test_tan(phi / 16, 0.19889_fix, 0.0001_fix);
      test_tan(0_fix, 0_fix, 0.0001_fix);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }

// 0.0001
