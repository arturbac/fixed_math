#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using F = fixedmath::fixed_internal;
using namespace fixedmath;

int main()
  {
  test_result result;
  "fixed construction"_test = [&result]
  {
    auto fn_tmpl = [] -> metatests::test_result
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
    result |= run_constexpr_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }
