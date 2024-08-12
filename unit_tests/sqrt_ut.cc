#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
using namespace fixedmath::func;

constexpr void test_hypot(
  fixed_t x, fixed_t y, fixed_t expected, fixed_t aprox, source_location const location = source_location::current()
)
  {
  expect_approx(hypot(x, y), expected, aprox, location);
  expect_approx(hypot(-x, y), expected, aprox, location);
  expect_approx(hypot(x, -y), expected, aprox, location);
  expect_approx(hypot(-x, -y), expected, aprox, location);
  }

template<std::unsigned_integral T>
constexpr auto asfix(T const v)
  {
  return as_fixed(fixedmath::fixed_internal(v));
  }

int main()
  {
  test_result result;
  "sqrt"_test = [&result]
  {
    auto fn_tmpl = [] -> metatests::test_result
    {
      expect_approx(sqrt(1.4111175537109375_fix), 1.1878_fix, 0.001_fix);
      expect_approx(sqrt(2.0000000000000000_fix), 1.4141_fix, 0.001_fix);
      expect_approx(sqrt(2.0124969482421875_fix), 1.4186_fix, 0.001_fix);
      expect_approx(sqrt(3.3333282470703125_fix), 1.8257_fix, 0.001_fix);
      expect_approx(sqrt(4.0000000000000000_fix), 2_fix, 0.001_fix);
      expect_approx(sqrt(3331.0000000000000000_fix), 57.7148_fix, 0.001_fix);
      expect_approx(sqrt(33331.0000000000000000_fix), 182.5677_fix, 0.001_fix);
      expect_approx(sqrt(333331.1000061035156250_fix), 577.3483_fix, 0.001_fix);
      expect_approx(sqrt(3333331.0215148925781250_fix), 1825.7412_fix, 0.001_fix);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };

  "hypot"_test = [&result]
  {
    auto fn_tmpl = [] -> metatests::test_result
    {
      test_hypot(-14.991608_fix, -0.837158_fix, 15.01495_fix, 0.0001_fix);
      test_hypot(-14.991608_fix, -0.837158_fix, 15.01495_fix, 0.0001_fix);
      test_hypot(-0.774933_fix, -4.295090_fix, 4.364425_fix, 0.0001_fix);
      test_hypot(-20.245346_fix, -0.909424_fix, 20.26574_fix, 0.0001_fix);
      test_hypot(14.9916076660156250_fix, 0_fix, 14.99160_fix, 0.0001_fix);
      test_hypot(0_fix, 14.9916076660156250_fix, 14.99160_fix, 0.0001_fix);

      test_hypot(asfix(1ull << 30), asfix(1u << 0), 16384_fix, 0.0001_fix);
      test_hypot(asfix(1ull << 33), asfix(1ul << 31), 135104_fix, 0.0001_fix);
      test_hypot(asfix(1ull << 32), asfix(1ul << 31), 73271_fix, 1.1_fix);
      test_hypot(asfix(1ull << 31), asfix(1ul << 31), 46340_fix, 1.1_fix);
      test_hypot(asfix(1ull << 32), asfix(1ul), 65536_fix, 0.0001_fix);
      test_hypot(asfix(1ull << 30), asfix(1u << 30), 23170_fix, 1_fix);
      test_hypot(asfix((1ull << 30) - 1), asfix((1ul << 30) - 1), 23170.47497_fix, 0.0001_fix);

      test_hypot(asfix(1u), asfix(1u), 0.000015_fix, 0.00001_fix);
      test_hypot(asfix(2u), asfix(2u), 0.000030_fix, 0.00001_fix);
      test_hypot(asfix(1u), asfix(3u), 0.000045_fix, 0.00001_fix);
      test_hypot(asfix(2u), asfix(3u), 0.000045_fix, 0.00001_fix);
      test_hypot(0.0125_fix, 0.125_fix, 0.125610_fix, 0.00001_fix);
      test_hypot(1_fix, 1_fix, 1.41419_fix, 0.0001_fix);
      test_hypot(0.5_fix, 0.25_fix, 0.559005_fix, 0.0001_fix);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }
