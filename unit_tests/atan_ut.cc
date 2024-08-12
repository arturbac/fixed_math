#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;
using namespace fixedmath::func;

constexpr void
  test_atan(fixed_t x, fixed_t expected, fixed_t aprox, source_location const location = source_location::current())
  {
  // constexpr double expected_precision = ; //0.000025
  expect_approx(atan(x), expected, aprox, location);
  expect_approx(atan(-x), -expected, aprox, location);
  }

constexpr void test_atan2(
  fixed_t y, fixed_t x, fixed_t expected, fixed_t aprox, source_location const location = source_location::current()
)
  {
  // constexpr double expected_precision = 0.00005; //0.000025
  expect_approx(atan2(y, x), expected, aprox, location);
  }

int main()
  {
  test_result result;
  "atan"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      test_atan(1_fix / 16, 0.062418_fix, 0.000025_fix);
      test_atan(3_fix / 16, 0.185347_fix, 0.000025_fix);
      test_atan(5_fix / 16, 0.302884_fix, 0.000025_fix);
      test_atan(7_fix / 16, 0.412410_fix, 0.000025_fix);
      test_atan(8_fix / 16, 0.463647_fix, 0.000025_fix);
      test_atan(9_fix / 16, 0.512389_fix, 0.000025_fix);
      test_atan(11_fix / 16, 0.602287_fix, 0.000025_fix);
      test_atan(13_fix / 16, 0.682316_fix, 0.000025_fix);
      test_atan(15_fix / 16, 0.753151_fix, 0.000025_fix);
      test_atan(17_fix / 16, 0.815691_fix, 0.000025_fix);
      test_atan(19_fix / 16, 0.870903_fix, 0.000025_fix);
      test_atan(21_fix / 16, 0.919719_fix, 0.000025_fix);
      test_atan(25_fix / 16, 1.001483_fix, 0.000025_fix);
      test_atan(37_fix / 16, 1.162647_fix, 0.000025_fix);
      test_atan(39_fix / 16, 1.181479_fix, 0.000025_fix);
      test_atan(40_fix / 16, 1.190289_fix, 0.00005_fix);
      test_atan(45_fix / 16, 1.229180_fix, 0.00005_fix);

      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };

  "atan2"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      test_atan2(-1 / 2_fix, -1 / 2_fix, -2.3561944901923448_fix, 0.00005_fix);

      // Thise are generated according to representation of fractions in fixed_t then
      // std::atan2(static_cast<double(fixed y),static_cast<double(fixed x)) atan2(+-1/1_fix, +-1/1_fix)
      test_atan2(1 / -1_fix, 1 / -1_fix, -2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / -1_fix, 1 / 1_fix, -0.785398163397_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / -1_fix, 2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / 1_fix, 0.785398163397_fix, 0.00005_fix);
      // atan2(+-1/1_fix, +-1/2_fix)
      test_atan2(1 / -1_fix, 1 / -2_fix, -2.034443935796_fix, 0.00005_fix);
      test_atan2(1 / -1_fix, 1 / 2_fix, -1.107148717794_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / -2_fix, 2.034443935796_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / 2_fix, 1.107148717794_fix, 0.00005_fix);
      // atan2(+-1/1_fix, +-1/3_fix)
      test_atan2(1 / -1_fix, 1 / -3_fix, -1.892542303548_fix, 0.00005_fix);
      test_atan2(1 / -1_fix, 1 / 3_fix, -1.249050350042_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / -3_fix, 1.892542303548_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / 3_fix, 1.249050350042_fix, 0.00005_fix);
      // atan2(+-1/1_fix, +-1/5_fix)
      test_atan2(1 / -1_fix, 1 / -5_fix, -1.768188952261_fix, 0.00005_fix);
      test_atan2(1 / -1_fix, 1 / 5_fix, -1.373403701329_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / -5_fix, 1.768188952261_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / 5_fix, 1.373403701329_fix, 0.00005_fix);
      // atan2(+-1/1_fix, +-1/7_fix)
      test_atan2(1 / -1_fix, 1 / -7_fix, -1.712689108936_fix, 0.00005_fix);
      test_atan2(1 / -1_fix, 1 / 7_fix, -1.428903544654_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / -7_fix, 1.712689108936_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / 7_fix, 1.428903544654_fix, 0.00005_fix);
      // atan2(+-1/1_fix, +-1/9_fix)
      test_atan2(1 / -1_fix, 1 / -9_fix, -1.681441824738_fix, 0.00005_fix);
      test_atan2(1 / -1_fix, 1 / 9_fix, -1.460150828852_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / -9_fix, 1.681441824738_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / 9_fix, 1.460150828852_fix, 0.00005_fix);
      // atan2(+-1/1_fix, +-1/13_fix)
      test_atan2(1 / -1_fix, 1 / -13_fix, -1.647564717518_fix, 0.00005_fix);
      test_atan2(1 / -1_fix, 1 / 13_fix, -1.494027936072_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / -13_fix, 1.647564717518_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / 13_fix, 1.494027936072_fix, 0.00005_fix);
      // atan2(+-1/1_fix, +-1/17_fix)
      test_atan2(1 / -1_fix, 1 / -17_fix, -1.629551255030_fix, 0.00005_fix);
      test_atan2(1 / -1_fix, 1 / 17_fix, -1.512041398560_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / -17_fix, 1.629551255030_fix, 0.00005_fix);
      test_atan2(1 / 1_fix, 1 / 17_fix, 1.512041398560_fix, 0.00005_fix);
      // atan2(+-1/2_fix, +-1/1_fix)
      test_atan2(1 / -2_fix, 1 / -1_fix, -2.677945044589_fix, 0.00005_fix);
      test_atan2(1 / -2_fix, 1 / 1_fix, -0.463647609001_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / -1_fix, 2.677945044589_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / 1_fix, 0.463647609001_fix, 0.00005_fix);
      // atan2(+-1/2_fix, +-1/2_fix)
      test_atan2(1 / -2_fix, 1 / -2_fix, -2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / -2_fix, 1 / 2_fix, -0.785398163397_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / -2_fix, 2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / 2_fix, 0.785398163397_fix, 0.00005_fix);
      // atan2(+-1/2_fix, +-1/3_fix)
      test_atan2(1 / -2_fix, 1 / -3_fix, -2.158791887791_fix, 0.00005_fix);
      test_atan2(1 / -2_fix, 1 / 3_fix, -0.982800765798_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / -3_fix, 2.158791887791_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / 3_fix, 0.982800765798_fix, 0.00005_fix);
      // atan2(+-1/2_fix, +-1/5_fix)
      test_atan2(1 / -2_fix, 1 / -5_fix, -1.951297442245_fix, 0.00005_fix);
      test_atan2(1 / -2_fix, 1 / 5_fix, -1.190295211345_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / -5_fix, 1.951297442245_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / 5_fix, 1.190295211345_fix, 0.00005_fix);
      // atan2(+-1/2_fix, +-1/7_fix)
      test_atan2(1 / -2_fix, 1 / -7_fix, -1.849087924534_fix, 0.00005_fix);
      test_atan2(1 / -2_fix, 1 / 7_fix, -1.292504729055_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / -7_fix, 1.849087924534_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / 7_fix, 1.292504729055_fix, 0.00005_fix);
      // atan2(+-1/2_fix, +-1/9_fix)
      test_atan2(1 / -2_fix, 1 / -9_fix, -1.789442653644_fix, 0.00005_fix);
      test_atan2(1 / -2_fix, 1 / 9_fix, -1.352149999945_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / -9_fix, 1.789442653644_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / 9_fix, 1.352149999945_fix, 0.00005_fix);
      // atan2(+-1/2_fix, +-1/13_fix)
      test_atan2(1 / -2_fix, 1 / -13_fix, -1.723438775498_fix, 0.00005_fix);
      test_atan2(1 / -2_fix, 1 / 13_fix, -1.418153878092_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / -13_fix, 1.723438775498_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / 13_fix, 1.418153878092_fix, 0.00005_fix);
      // atan2(+-1/2_fix, +-1/17_fix)
      test_atan2(1 / -2_fix, 1 / -17_fix, -1.687903300717_fix, 0.00005_fix);
      test_atan2(1 / -2_fix, 1 / 17_fix, -1.453689352873_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / -17_fix, 1.687903300717_fix, 0.00005_fix);
      test_atan2(1 / 2_fix, 1 / 17_fix, 1.453689352873_fix, 0.00005_fix);
      // atan2(+-1/3_fix, +-1/1_fix)
      test_atan2(1 / -3_fix, 1 / -1_fix, -2.819846676837_fix, 0.00005_fix);
      test_atan2(1 / -3_fix, 1 / 1_fix, -0.321745976753_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / -1_fix, 2.819846676837_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / 1_fix, 0.321745976753_fix, 0.00005_fix);
      // atan2(+-1/3_fix, +-1/2_fix)
      test_atan2(1 / -3_fix, 1 / -2_fix, -2.553597092593_fix, 0.00005_fix);
      test_atan2(1 / -3_fix, 1 / 2_fix, -0.587995560996_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / -2_fix, 2.553597092593_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / 2_fix, 0.587995560996_fix, 0.00005_fix);
      // atan2(+-1/3_fix, +-1/3_fix)
      test_atan2(1 / -3_fix, 1 / -3_fix, -2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / -3_fix, 1 / 3_fix, -0.785398163397_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / -3_fix, 2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / 3_fix, 0.785398163397_fix, 0.00005_fix);
      // atan2(+-1/3_fix, +-1/5_fix)
      test_atan2(1 / -3_fix, 1 / -5_fix, -2.111215827065_fix, 0.00005_fix);
      test_atan2(1 / -3_fix, 1 / 5_fix, -1.030376826524_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / -5_fix, 2.111215827065_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / 5_fix, 1.030376826524_fix, 0.00005_fix);
      // atan2(+-1/3_fix, +-1/7_fix)
      test_atan2(1 / -3_fix, 1 / -7_fix, -1.975682588249_fix, 0.00005_fix);
      test_atan2(1 / -3_fix, 1 / 7_fix, -1.165910065341_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / -7_fix, 1.975682588249_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / 7_fix, 1.165910065341_fix, 0.00005_fix);
      // atan2(+-1/3_fix, +-1/9_fix)
      test_atan2(1 / -3_fix, 1 / -9_fix, -1.892519414701_fix, 0.00005_fix);
      test_atan2(1 / -3_fix, 1 / 9_fix, -1.249073238889_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / -9_fix, 1.892519414701_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / 9_fix, 1.249073238889_fix, 0.00005_fix);
      // atan2(+-1/3_fix, +-1/13_fix)
      test_atan2(1 / -3_fix, 1 / -13_fix, -1.797588488301_fix, 0.00005_fix);
      test_atan2(1 / -3_fix, 1 / 13_fix, -1.344004165289_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / -13_fix, 1.797588488301_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / 13_fix, 1.344004165289_fix, 0.00005_fix);
      // atan2(+-1/3_fix, +-1/17_fix)
      test_atan2(1 / -3_fix, 1 / -17_fix, -1.745468525803_fix, 0.00005_fix);
      test_atan2(1 / -3_fix, 1 / 17_fix, -1.396124127787_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / -17_fix, 1.745468525803_fix, 0.00005_fix);
      test_atan2(1 / 3_fix, 1 / 17_fix, 1.396124127787_fix, 0.00005_fix);
      // atan2(+-1/5_fix, +-1/1_fix)
      test_atan2(1 / -5_fix, 1 / -1_fix, -2.944200028124_fix, 0.00005_fix);
      test_atan2(1 / -5_fix, 1 / 1_fix, -0.197392625466_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / -1_fix, 2.944200028124_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / 1_fix, 0.197392625466_fix, 0.00005_fix);
      // atan2(+-1/5_fix, +-1/2_fix)
      test_atan2(1 / -5_fix, 1 / -2_fix, -2.761091538140_fix, 0.00005_fix);
      test_atan2(1 / -5_fix, 1 / 2_fix, -0.380501115450_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / -2_fix, 2.761091538140_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / 2_fix, 0.380501115450_fix, 0.00005_fix);
      // atan2(+-1/5_fix, +-1/3_fix)
      test_atan2(1 / -5_fix, 1 / -3_fix, -2.601173153319_fix, 0.00005_fix);
      test_atan2(1 / -5_fix, 1 / 3_fix, -0.540419500271_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / -3_fix, 2.601173153319_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / 3_fix, 0.540419500271_fix, 0.00005_fix);
      // atan2(+-1/5_fix, +-1/5_fix)
      test_atan2(1 / -5_fix, 1 / -5_fix, -2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / -5_fix, 1 / 5_fix, -0.785398163397_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / -5_fix, 2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / 5_fix, 0.785398163397_fix, 0.00005_fix);
      // atan2(+-1/5_fix, +-1/7_fix)
      test_atan2(1 / -5_fix, 1 / -7_fix, -2.191038595636_fix, 0.00005_fix);
      test_atan2(1 / -5_fix, 1 / 7_fix, -0.950554057954_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / -7_fix, 2.191038595636_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / 7_fix, 0.950554057954_fix, 0.00005_fix);
      // atan2(+-1/5_fix, +-1/9_fix)
      test_atan2(1 / -5_fix, 1 / -9_fix, -2.077855963028_fix, 0.00005_fix);
      test_atan2(1 / -5_fix, 1 / 9_fix, -1.063736690562_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / -9_fix, 2.077855963028_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / 9_fix, 1.063736690562_fix, 0.00005_fix);
      // atan2(+-1/5_fix, +-1/13_fix)
      test_atan2(1 / -5_fix, 1 / -13_fix, -1.937959935455_fix, 0.00005_fix);
      test_atan2(1 / -5_fix, 1 / 13_fix, -1.203632718135_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / -13_fix, 1.937959935455_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / 13_fix, 1.203632718135_fix, 0.00005_fix);
      // atan2(+-1/5_fix, +-1/17_fix)
      test_atan2(1 / -5_fix, 1 / -17_fix, -1.856847768512_fix, 0.00005_fix);
      test_atan2(1 / -5_fix, 1 / 17_fix, -1.284744885078_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / -17_fix, 1.856847768512_fix, 0.00005_fix);
      test_atan2(1 / 5_fix, 1 / 17_fix, 1.284744885078_fix, 0.00005_fix);
      // atan2(+-1/7_fix, +-1/1_fix)
      test_atan2(1 / -7_fix, 1 / -1_fix, -2.999699871449_fix, 0.00005_fix);
      test_atan2(1 / -7_fix, 1 / 1_fix, -0.141892782141_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / -1_fix, 2.999699871449_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / 1_fix, 0.141892782141_fix, 0.00005_fix);
      // atan2(+-1/7_fix, +-1/2_fix)
      test_atan2(1 / -7_fix, 1 / -2_fix, -2.863301055850_fix, 0.00005_fix);
      test_atan2(1 / -7_fix, 1 / 2_fix, -0.278291597739_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / -2_fix, 2.863301055850_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / 2_fix, 0.278291597739_fix, 0.00005_fix);
      // atan2(+-1/7_fix, +-1/3_fix)
      test_atan2(1 / -7_fix, 1 / -3_fix, -2.736706392136_fix, 0.00005_fix);
      test_atan2(1 / -7_fix, 1 / 3_fix, -0.404886261454_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / -3_fix, 2.736706392136_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / 3_fix, 0.404886261454_fix, 0.00005_fix);
      // atan2(+-1/7_fix, +-1/5_fix)
      test_atan2(1 / -7_fix, 1 / -5_fix, -2.521350384749_fix, 0.00005_fix);
      test_atan2(1 / -7_fix, 1 / 5_fix, -0.620242268841_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / -5_fix, 2.521350384749_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / 5_fix, 0.620242268841_fix, 0.00005_fix);
      // atan2(+-1/7_fix, +-1/7_fix)
      test_atan2(1 / -7_fix, 1 / -7_fix, -2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / -7_fix, 1 / 7_fix, -0.785398163397_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / -7_fix, 2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / 7_fix, 0.785398163397_fix, 0.00005_fix);
      // atan2(+-1/7_fix, +-1/9_fix)
      test_atan2(1 / -7_fix, 1 / -9_fix, -2.231802520234_fix, 0.00005_fix);
      test_atan2(1 / -7_fix, 1 / 9_fix, -0.909790133356_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / -9_fix, 2.231802520234_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / 9_fix, 0.909790133356_fix, 0.00005_fix);
      // atan2(+-1/7_fix, +-1/13_fix)
      test_atan2(1 / -7_fix, 1 / -13_fix, -2.064731326004_fix, 0.00005_fix);
      test_atan2(1 / -7_fix, 1 / 13_fix, -1.076861327586_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / -13_fix, 2.064731326004_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / 13_fix, 1.076861327586_fix, 0.00005_fix);
      // atan2(+-1/7_fix, +-1/17_fix)
      test_atan2(1 / -7_fix, 1 / -17_fix, -1.961408742822_fix, 0.00005_fix);
      test_atan2(1 / -7_fix, 1 / 17_fix, -1.180183910768_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / -17_fix, 1.961408742822_fix, 0.00005_fix);
      test_atan2(1 / 7_fix, 1 / 17_fix, 1.180183910768_fix, 0.00005_fix);
      // atan2(+-1/9_fix, +-1/1_fix)
      test_atan2(1 / -9_fix, 1 / -1_fix, -3.030947155647_fix, 0.00005_fix);
      test_atan2(1 / -9_fix, 1 / 1_fix, -0.110645497943_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / -1_fix, 3.030947155647_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / 1_fix, 0.110645497943_fix, 0.00005_fix);
      // atan2(+-1/9_fix, +-1/2_fix)
      test_atan2(1 / -9_fix, 1 / -2_fix, -2.922946326740_fix, 0.00005_fix);
      test_atan2(1 / -9_fix, 1 / 2_fix, -0.218646326849_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / -2_fix, 2.922946326740_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / 2_fix, 0.218646326849_fix, 0.00005_fix);
      // atan2(+-1/9_fix, +-1/3_fix)
      test_atan2(1 / -9_fix, 1 / -3_fix, -2.819869565684_fix, 0.00005_fix);
      test_atan2(1 / -9_fix, 1 / 3_fix, -0.321723087906_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / -3_fix, 2.819869565684_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / 3_fix, 0.321723087906_fix, 0.00005_fix);
      // atan2(+-1/9_fix, +-1/5_fix)
      test_atan2(1 / -9_fix, 1 / -5_fix, -2.634533017357_fix, 0.00005_fix);
      test_atan2(1 / -9_fix, 1 / 5_fix, -0.507059636233_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / -5_fix, 2.634533017357_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / 5_fix, 0.507059636233_fix, 0.00005_fix);
      // atan2(+-1/9_fix, +-1/7_fix)
      test_atan2(1 / -9_fix, 1 / -7_fix, -2.480586460150_fix, 0.00005_fix);
      test_atan2(1 / -9_fix, 1 / 7_fix, -0.661006193439_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / -7_fix, 2.480586460150_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / 7_fix, 0.661006193439_fix, 0.00005_fix);
      // atan2(+-1/9_fix, +-1/9_fix)
      test_atan2(1 / -9_fix, 1 / -9_fix, -2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / -9_fix, 1 / 9_fix, -0.785398163397_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / -9_fix, 2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / 9_fix, 0.785398163397_fix, 0.00005_fix);
      // atan2(+-1/9_fix, +-1/13_fix)
      test_atan2(1 / -9_fix, 1 / -13_fix, -2.176369557339_fix, 0.00005_fix);
      test_atan2(1 / -9_fix, 1 / 13_fix, -0.965223096250_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / -13_fix, 2.176369557339_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / 13_fix, 0.965223096250_fix, 0.00005_fix);
      // atan2(+-1/9_fix, +-1/17_fix)
      test_atan2(1 / -9_fix, 1 / -17_fix, -2.057733420184_fix, 0.00005_fix);
      test_atan2(1 / -9_fix, 1 / 17_fix, -1.083859233406_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / -17_fix, 2.057733420184_fix, 0.00005_fix);
      test_atan2(1 / 9_fix, 1 / 17_fix, 1.083859233406_fix, 0.00005_fix);
      // atan2(+-1/13_fix, +-1/1_fix)
      test_atan2(1 / -13_fix, 1 / -1_fix, -3.064824262867_fix, 0.00005_fix);
      test_atan2(1 / -13_fix, 1 / 1_fix, -0.076768390723_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / -1_fix, 3.064824262867_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / 1_fix, 0.076768390723_fix, 0.00005_fix);
      // atan2(+-1/13_fix, +-1/2_fix)
      test_atan2(1 / -13_fix, 1 / -2_fix, -2.988950204887_fix, 0.00005_fix);
      test_atan2(1 / -13_fix, 1 / 2_fix, -0.152642448703_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / -2_fix, 2.988950204887_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / 2_fix, 0.152642448703_fix, 0.00005_fix);
      // atan2(+-1/13_fix, +-1/3_fix)
      test_atan2(1 / -13_fix, 1 / -3_fix, -2.914800492084_fix, 0.00005_fix);
      test_atan2(1 / -13_fix, 1 / 3_fix, -0.226792161506_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / -3_fix, 2.914800492084_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / 3_fix, 0.226792161506_fix, 0.00005_fix);
      // atan2(+-1/13_fix, +-1/5_fix)
      test_atan2(1 / -13_fix, 1 / -5_fix, -2.774429044930_fix, 0.00005_fix);
      test_atan2(1 / -13_fix, 1 / 5_fix, -0.367163608660_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / -5_fix, 2.774429044930_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / 5_fix, 0.367163608660_fix, 0.00005_fix);
      // atan2(+-1/13_fix, +-1/7_fix)
      test_atan2(1 / -13_fix, 1 / -7_fix, -2.647657654381_fix, 0.00005_fix);
      test_atan2(1 / -13_fix, 1 / 7_fix, -0.493934999209_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / -7_fix, 2.647657654381_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / 7_fix, 0.493934999209_fix, 0.00005_fix);
      // atan2(+-1/13_fix, +-1/9_fix)
      test_atan2(1 / -13_fix, 1 / -9_fix, -2.536019423045_fix, 0.00005_fix);
      test_atan2(1 / -13_fix, 1 / 9_fix, -0.605573230544_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / -9_fix, 2.536019423045_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / 9_fix, 0.605573230544_fix, 0.00005_fix);
      // atan2(+-1/13_fix, +-1/13_fix)
      test_atan2(1 / -13_fix, 1 / -13_fix, -2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / -13_fix, 1 / 13_fix, -0.785398163397_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / -13_fix, 2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / 13_fix, 0.785398163397_fix, 0.00005_fix);
      // atan2(+-1/13_fix, +-1/17_fix)
      test_atan2(1 / -13_fix, 1 / -17_fix, -2.223657684135_fix, 0.00005_fix);
      test_atan2(1 / -13_fix, 1 / 17_fix, -0.917934969455_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / -17_fix, 2.223657684135_fix, 0.00005_fix);
      test_atan2(1 / 13_fix, 1 / 17_fix, 0.917934969455_fix, 0.00005_fix);
      // atan2(+-1/17_fix, +-1/1_fix)
      test_atan2(1 / -17_fix, 1 / -1_fix, -3.082837725355_fix, 0.00005_fix);
      test_atan2(1 / -17_fix, 1 / 1_fix, -0.058754928235_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / -1_fix, 3.082837725355_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / 1_fix, 0.058754928235_fix, 0.00005_fix);
      // atan2(+-1/17_fix, +-1/2_fix)
      test_atan2(1 / -17_fix, 1 / -2_fix, -3.024485679668_fix, 0.00005_fix);
      test_atan2(1 / -17_fix, 1 / 2_fix, -0.117106973922_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / -2_fix, 3.024485679668_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / 2_fix, 0.117106973922_fix, 0.00005_fix);
      // atan2(+-1/17_fix, +-1/3_fix)
      test_atan2(1 / -17_fix, 1 / -3_fix, -2.966920454582_fix, 0.00005_fix);
      test_atan2(1 / -17_fix, 1 / 3_fix, -0.174672199008_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / -3_fix, 2.966920454582_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / 3_fix, 0.174672199008_fix, 0.00005_fix);
      // atan2(+-1/17_fix, +-1/5_fix)
      test_atan2(1 / -17_fix, 1 / -5_fix, -2.855541211872_fix, 0.00005_fix);
      test_atan2(1 / -17_fix, 1 / 5_fix, -0.286051441717_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / -5_fix, 2.855541211872_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / 5_fix, 0.286051441717_fix, 0.00005_fix);
      // atan2(+-1/17_fix, +-1/7_fix)
      test_atan2(1 / -17_fix, 1 / -7_fix, -2.750980237563_fix, 0.00005_fix);
      test_atan2(1 / -17_fix, 1 / 7_fix, -0.390612416027_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / -7_fix, 2.750980237563_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / 7_fix, 0.390612416027_fix, 0.00005_fix);
      // atan2(+-1/17_fix, +-1/9_fix)
      test_atan2(1 / -17_fix, 1 / -9_fix, -2.654655560200_fix, 0.00005_fix);
      test_atan2(1 / -17_fix, 1 / 9_fix, -0.486937093389_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / -9_fix, 2.654655560200_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / 9_fix, 0.486937093389_fix, 0.00005_fix);
      // atan2(+-1/17_fix, +-1/13_fix)
      test_atan2(1 / -17_fix, 1 / -13_fix, -2.488731296250_fix, 0.00005_fix);
      test_atan2(1 / -17_fix, 1 / 13_fix, -0.652861357340_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / -13_fix, 2.488731296250_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / 13_fix, 0.652861357340_fix, 0.00005_fix);
      // atan2(+-1/17_fix, +-1/17_fix)
      test_atan2(1 / -17_fix, 1 / -17_fix, -2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / -17_fix, 1 / 17_fix, -0.785398163397_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / -17_fix, 2.356194490192_fix, 0.00005_fix);
      test_atan2(1 / 17_fix, 1 / 17_fix, 0.785398163397_fix, 0.00005_fix);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }

// 0.00005
