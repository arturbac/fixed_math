#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
  
  constexpr bool test_atan( fixed_t x, double expected )
    {
    constexpr double expected_precision = 0.00005; //0.000025
    return ut_abs(atan( x ) - expected ) < expected_precision && ut_abs(atan( -x ) - -expected ) < expected_precision;
    }
    
  constexpr bool test_atan2( fixed_t y, fixed_t x, double expected )
    {
    constexpr double expected_precision = 0.00005; //0.000025
    return ut_abs(atan2( y,x ) - expected ) < expected_precision;
    }
    
[[nodiscard]]
constexpr bool atan_unit_tests() noexcept
  {
  //------------------------------------------------------------------------------------------------------
  //
  // atan
  //
  static_assert( test_atan( 1_fix/16,0.062418809995957));
  static_assert( test_atan( 3_fix/16,0.185347949995695));
  static_assert( test_atan( 5_fix/16,0.302884868374971));
  static_assert( test_atan( 7_fix/16,0.412410441597387));
  static_assert( test_atan( 8_fix/16,0.463647609000806));
  static_assert( test_atan( 9_fix/16,0.512389460310738));
  static_assert( test_atan( 11_fix/16,0.602287346134964));
  static_assert( test_atan( 13_fix/16,0.682316554874748));
  static_assert( test_atan( 15_fix/16,0.753151280962194));
  static_assert( test_atan( 17_fix/16,0.815691923316223));
  static_assert( test_atan( 19_fix/16,0.870903457075653));
  static_assert( test_atan( 21_fix/16,0.919719605350417));
  static_assert( test_atan( 25_fix/16,1.00148313569423));
  static_assert( test_atan( 37_fix/16,1.16264722303981));
  static_assert( test_atan( 39_fix/16,1.18147960496176));
  static_assert( test_atan( 40_fix/16,1.19028994968253));
  static_assert( test_atan( 45_fix/16,1.22918083614709));
  

  static_assert( test_atan2(-1/2_fix,-1/2_fix, -2.3561944901923448 ));
  
  //Thise are generated according to representation of fractions in fixed_t then std::atan2(static_cast<double(fixed y),static_cast<double(fixed x))
  //atan2(+-1/1_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -1_fix,-2.356194490192));
  static_assert(test_atan2(1/ -1_fix, 1/  1_fix,-0.785398163397));
  static_assert(test_atan2(1/  1_fix, 1/ -1_fix,2.356194490192));
  static_assert(test_atan2(1/  1_fix, 1/  1_fix,0.785398163397));
  //atan2(+-1/1_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -2_fix,-2.034443935796));
  static_assert(test_atan2(1/ -1_fix, 1/  2_fix,-1.107148717794));
  static_assert(test_atan2(1/  1_fix, 1/ -2_fix,2.034443935796));
  static_assert(test_atan2(1/  1_fix, 1/  2_fix,1.107148717794));
  //atan2(+-1/1_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -3_fix,-1.892542303548));
  static_assert(test_atan2(1/ -1_fix, 1/  3_fix,-1.249050350042));
  static_assert(test_atan2(1/  1_fix, 1/ -3_fix,1.892542303548));
  static_assert(test_atan2(1/  1_fix, 1/  3_fix,1.249050350042));
  //atan2(+-1/1_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -5_fix,-1.768188952261));
  static_assert(test_atan2(1/ -1_fix, 1/  5_fix,-1.373403701329));
  static_assert(test_atan2(1/  1_fix, 1/ -5_fix,1.768188952261));
  static_assert(test_atan2(1/  1_fix, 1/  5_fix,1.373403701329));
  //atan2(+-1/1_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -7_fix,-1.712689108936));
  static_assert(test_atan2(1/ -1_fix, 1/  7_fix,-1.428903544654));
  static_assert(test_atan2(1/  1_fix, 1/ -7_fix,1.712689108936));
  static_assert(test_atan2(1/  1_fix, 1/  7_fix,1.428903544654));
  //atan2(+-1/1_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -1_fix, 1/ -9_fix,-1.681441824738));
  static_assert(test_atan2(1/ -1_fix, 1/  9_fix,-1.460150828852));
  static_assert(test_atan2(1/  1_fix, 1/ -9_fix,1.681441824738));
  static_assert(test_atan2(1/  1_fix, 1/  9_fix,1.460150828852));
  //atan2(+-1/1_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -1_fix, 1/-13_fix,-1.647564717518));
  static_assert(test_atan2(1/ -1_fix, 1/ 13_fix,-1.494027936072));
  static_assert(test_atan2(1/  1_fix, 1/-13_fix,1.647564717518));
  static_assert(test_atan2(1/  1_fix, 1/ 13_fix,1.494027936072));
  //atan2(+-1/1_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -1_fix, 1/-17_fix,-1.629551255030));
  static_assert(test_atan2(1/ -1_fix, 1/ 17_fix,-1.512041398560));
  static_assert(test_atan2(1/  1_fix, 1/-17_fix,1.629551255030));
  static_assert(test_atan2(1/  1_fix, 1/ 17_fix,1.512041398560));
  //atan2(+-1/2_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -1_fix,-2.677945044589));
  static_assert(test_atan2(1/ -2_fix, 1/  1_fix,-0.463647609001));
  static_assert(test_atan2(1/  2_fix, 1/ -1_fix,2.677945044589));
  static_assert(test_atan2(1/  2_fix, 1/  1_fix,0.463647609001));
  //atan2(+-1/2_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -2_fix,-2.356194490192));
  static_assert(test_atan2(1/ -2_fix, 1/  2_fix,-0.785398163397));
  static_assert(test_atan2(1/  2_fix, 1/ -2_fix,2.356194490192));
  static_assert(test_atan2(1/  2_fix, 1/  2_fix,0.785398163397));
  //atan2(+-1/2_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -3_fix,-2.158791887791));
  static_assert(test_atan2(1/ -2_fix, 1/  3_fix,-0.982800765798));
  static_assert(test_atan2(1/  2_fix, 1/ -3_fix,2.158791887791));
  static_assert(test_atan2(1/  2_fix, 1/  3_fix,0.982800765798));
  //atan2(+-1/2_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -5_fix,-1.951297442245));
  static_assert(test_atan2(1/ -2_fix, 1/  5_fix,-1.190295211345));
  static_assert(test_atan2(1/  2_fix, 1/ -5_fix,1.951297442245));
  static_assert(test_atan2(1/  2_fix, 1/  5_fix,1.190295211345));
  //atan2(+-1/2_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -7_fix,-1.849087924534));
  static_assert(test_atan2(1/ -2_fix, 1/  7_fix,-1.292504729055));
  static_assert(test_atan2(1/  2_fix, 1/ -7_fix,1.849087924534));
  static_assert(test_atan2(1/  2_fix, 1/  7_fix,1.292504729055));
  //atan2(+-1/2_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -2_fix, 1/ -9_fix,-1.789442653644));
  static_assert(test_atan2(1/ -2_fix, 1/  9_fix,-1.352149999945));
  static_assert(test_atan2(1/  2_fix, 1/ -9_fix,1.789442653644));
  static_assert(test_atan2(1/  2_fix, 1/  9_fix,1.352149999945));
  //atan2(+-1/2_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -2_fix, 1/-13_fix,-1.723438775498));
  static_assert(test_atan2(1/ -2_fix, 1/ 13_fix,-1.418153878092));
  static_assert(test_atan2(1/  2_fix, 1/-13_fix,1.723438775498));
  static_assert(test_atan2(1/  2_fix, 1/ 13_fix,1.418153878092));
  //atan2(+-1/2_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -2_fix, 1/-17_fix,-1.687903300717));
  static_assert(test_atan2(1/ -2_fix, 1/ 17_fix,-1.453689352873));
  static_assert(test_atan2(1/  2_fix, 1/-17_fix,1.687903300717));
  static_assert(test_atan2(1/  2_fix, 1/ 17_fix,1.453689352873));
  //atan2(+-1/3_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -1_fix,-2.819846676837));
  static_assert(test_atan2(1/ -3_fix, 1/  1_fix,-0.321745976753));
  static_assert(test_atan2(1/  3_fix, 1/ -1_fix,2.819846676837));
  static_assert(test_atan2(1/  3_fix, 1/  1_fix,0.321745976753));
  //atan2(+-1/3_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -2_fix,-2.553597092593));
  static_assert(test_atan2(1/ -3_fix, 1/  2_fix,-0.587995560996));
  static_assert(test_atan2(1/  3_fix, 1/ -2_fix,2.553597092593));
  static_assert(test_atan2(1/  3_fix, 1/  2_fix,0.587995560996));
  //atan2(+-1/3_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -3_fix,-2.356194490192));
  static_assert(test_atan2(1/ -3_fix, 1/  3_fix,-0.785398163397));
  static_assert(test_atan2(1/  3_fix, 1/ -3_fix,2.356194490192));
  static_assert(test_atan2(1/  3_fix, 1/  3_fix,0.785398163397));
  //atan2(+-1/3_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -5_fix,-2.111215827065));
  static_assert(test_atan2(1/ -3_fix, 1/  5_fix,-1.030376826524));
  static_assert(test_atan2(1/  3_fix, 1/ -5_fix,2.111215827065));
  static_assert(test_atan2(1/  3_fix, 1/  5_fix,1.030376826524));
  //atan2(+-1/3_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -7_fix,-1.975682588249));
  static_assert(test_atan2(1/ -3_fix, 1/  7_fix,-1.165910065341));
  static_assert(test_atan2(1/  3_fix, 1/ -7_fix,1.975682588249));
  static_assert(test_atan2(1/  3_fix, 1/  7_fix,1.165910065341));
  //atan2(+-1/3_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -3_fix, 1/ -9_fix,-1.892519414701));
  static_assert(test_atan2(1/ -3_fix, 1/  9_fix,-1.249073238889));
  static_assert(test_atan2(1/  3_fix, 1/ -9_fix,1.892519414701));
  static_assert(test_atan2(1/  3_fix, 1/  9_fix,1.249073238889));
  //atan2(+-1/3_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -3_fix, 1/-13_fix,-1.797588488301));
  static_assert(test_atan2(1/ -3_fix, 1/ 13_fix,-1.344004165289));
  static_assert(test_atan2(1/  3_fix, 1/-13_fix,1.797588488301));
  static_assert(test_atan2(1/  3_fix, 1/ 13_fix,1.344004165289));
  //atan2(+-1/3_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -3_fix, 1/-17_fix,-1.745468525803));
  static_assert(test_atan2(1/ -3_fix, 1/ 17_fix,-1.396124127787));
  static_assert(test_atan2(1/  3_fix, 1/-17_fix,1.745468525803));
  static_assert(test_atan2(1/  3_fix, 1/ 17_fix,1.396124127787));
  //atan2(+-1/5_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -1_fix,-2.944200028124));
  static_assert(test_atan2(1/ -5_fix, 1/  1_fix,-0.197392625466));
  static_assert(test_atan2(1/  5_fix, 1/ -1_fix,2.944200028124));
  static_assert(test_atan2(1/  5_fix, 1/  1_fix,0.197392625466));
  //atan2(+-1/5_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -2_fix,-2.761091538140));
  static_assert(test_atan2(1/ -5_fix, 1/  2_fix,-0.380501115450));
  static_assert(test_atan2(1/  5_fix, 1/ -2_fix,2.761091538140));
  static_assert(test_atan2(1/  5_fix, 1/  2_fix,0.380501115450));
  //atan2(+-1/5_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -3_fix,-2.601173153319));
  static_assert(test_atan2(1/ -5_fix, 1/  3_fix,-0.540419500271));
  static_assert(test_atan2(1/  5_fix, 1/ -3_fix,2.601173153319));
  static_assert(test_atan2(1/  5_fix, 1/  3_fix,0.540419500271));
  //atan2(+-1/5_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -5_fix,-2.356194490192));
  static_assert(test_atan2(1/ -5_fix, 1/  5_fix,-0.785398163397));
  static_assert(test_atan2(1/  5_fix, 1/ -5_fix,2.356194490192));
  static_assert(test_atan2(1/  5_fix, 1/  5_fix,0.785398163397));
  //atan2(+-1/5_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -7_fix,-2.191038595636));
  static_assert(test_atan2(1/ -5_fix, 1/  7_fix,-0.950554057954));
  static_assert(test_atan2(1/  5_fix, 1/ -7_fix,2.191038595636));
  static_assert(test_atan2(1/  5_fix, 1/  7_fix,0.950554057954));
  //atan2(+-1/5_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -5_fix, 1/ -9_fix,-2.077855963028));
  static_assert(test_atan2(1/ -5_fix, 1/  9_fix,-1.063736690562));
  static_assert(test_atan2(1/  5_fix, 1/ -9_fix,2.077855963028));
  static_assert(test_atan2(1/  5_fix, 1/  9_fix,1.063736690562));
  //atan2(+-1/5_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -5_fix, 1/-13_fix,-1.937959935455));
  static_assert(test_atan2(1/ -5_fix, 1/ 13_fix,-1.203632718135));
  static_assert(test_atan2(1/  5_fix, 1/-13_fix,1.937959935455));
  static_assert(test_atan2(1/  5_fix, 1/ 13_fix,1.203632718135));
  //atan2(+-1/5_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -5_fix, 1/-17_fix,-1.856847768512));
  static_assert(test_atan2(1/ -5_fix, 1/ 17_fix,-1.284744885078));
  static_assert(test_atan2(1/  5_fix, 1/-17_fix,1.856847768512));
  static_assert(test_atan2(1/  5_fix, 1/ 17_fix,1.284744885078));
  //atan2(+-1/7_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -1_fix,-2.999699871449));
  static_assert(test_atan2(1/ -7_fix, 1/  1_fix,-0.141892782141));
  static_assert(test_atan2(1/  7_fix, 1/ -1_fix,2.999699871449));
  static_assert(test_atan2(1/  7_fix, 1/  1_fix,0.141892782141));
  //atan2(+-1/7_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -2_fix,-2.863301055850));
  static_assert(test_atan2(1/ -7_fix, 1/  2_fix,-0.278291597739));
  static_assert(test_atan2(1/  7_fix, 1/ -2_fix,2.863301055850));
  static_assert(test_atan2(1/  7_fix, 1/  2_fix,0.278291597739));
  //atan2(+-1/7_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -3_fix,-2.736706392136));
  static_assert(test_atan2(1/ -7_fix, 1/  3_fix,-0.404886261454));
  static_assert(test_atan2(1/  7_fix, 1/ -3_fix,2.736706392136));
  static_assert(test_atan2(1/  7_fix, 1/  3_fix,0.404886261454));
  //atan2(+-1/7_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -5_fix,-2.521350384749));
  static_assert(test_atan2(1/ -7_fix, 1/  5_fix,-0.620242268841));
  static_assert(test_atan2(1/  7_fix, 1/ -5_fix,2.521350384749));
  static_assert(test_atan2(1/  7_fix, 1/  5_fix,0.620242268841));
  //atan2(+-1/7_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -7_fix,-2.356194490192));
  static_assert(test_atan2(1/ -7_fix, 1/  7_fix,-0.785398163397));
  static_assert(test_atan2(1/  7_fix, 1/ -7_fix,2.356194490192));
  static_assert(test_atan2(1/  7_fix, 1/  7_fix,0.785398163397));
  //atan2(+-1/7_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -7_fix, 1/ -9_fix,-2.231802520234));
  static_assert(test_atan2(1/ -7_fix, 1/  9_fix,-0.909790133356));
  static_assert(test_atan2(1/  7_fix, 1/ -9_fix,2.231802520234));
  static_assert(test_atan2(1/  7_fix, 1/  9_fix,0.909790133356));
  //atan2(+-1/7_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -7_fix, 1/-13_fix,-2.064731326004));
  static_assert(test_atan2(1/ -7_fix, 1/ 13_fix,-1.076861327586));
  static_assert(test_atan2(1/  7_fix, 1/-13_fix,2.064731326004));
  static_assert(test_atan2(1/  7_fix, 1/ 13_fix,1.076861327586));
  //atan2(+-1/7_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -7_fix, 1/-17_fix,-1.961408742822));
  static_assert(test_atan2(1/ -7_fix, 1/ 17_fix,-1.180183910768));
  static_assert(test_atan2(1/  7_fix, 1/-17_fix,1.961408742822));
  static_assert(test_atan2(1/  7_fix, 1/ 17_fix,1.180183910768));
  //atan2(+-1/9_fix, +-1/1_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -1_fix,-3.030947155647));
  static_assert(test_atan2(1/ -9_fix, 1/  1_fix,-0.110645497943));
  static_assert(test_atan2(1/  9_fix, 1/ -1_fix,3.030947155647));
  static_assert(test_atan2(1/  9_fix, 1/  1_fix,0.110645497943));
  //atan2(+-1/9_fix, +-1/2_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -2_fix,-2.922946326740));
  static_assert(test_atan2(1/ -9_fix, 1/  2_fix,-0.218646326849));
  static_assert(test_atan2(1/  9_fix, 1/ -2_fix,2.922946326740));
  static_assert(test_atan2(1/  9_fix, 1/  2_fix,0.218646326849));
  //atan2(+-1/9_fix, +-1/3_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -3_fix,-2.819869565684));
  static_assert(test_atan2(1/ -9_fix, 1/  3_fix,-0.321723087906));
  static_assert(test_atan2(1/  9_fix, 1/ -3_fix,2.819869565684));
  static_assert(test_atan2(1/  9_fix, 1/  3_fix,0.321723087906));
  //atan2(+-1/9_fix, +-1/5_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -5_fix,-2.634533017357));
  static_assert(test_atan2(1/ -9_fix, 1/  5_fix,-0.507059636233));
  static_assert(test_atan2(1/  9_fix, 1/ -5_fix,2.634533017357));
  static_assert(test_atan2(1/  9_fix, 1/  5_fix,0.507059636233));
  //atan2(+-1/9_fix, +-1/7_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -7_fix,-2.480586460150));
  static_assert(test_atan2(1/ -9_fix, 1/  7_fix,-0.661006193439));
  static_assert(test_atan2(1/  9_fix, 1/ -7_fix,2.480586460150));
  static_assert(test_atan2(1/  9_fix, 1/  7_fix,0.661006193439));
  //atan2(+-1/9_fix, +-1/9_fix)
  static_assert(test_atan2(1/ -9_fix, 1/ -9_fix,-2.356194490192));
  static_assert(test_atan2(1/ -9_fix, 1/  9_fix,-0.785398163397));
  static_assert(test_atan2(1/  9_fix, 1/ -9_fix,2.356194490192));
  static_assert(test_atan2(1/  9_fix, 1/  9_fix,0.785398163397));
  //atan2(+-1/9_fix, +-1/13_fix)
  static_assert(test_atan2(1/ -9_fix, 1/-13_fix,-2.176369557339));
  static_assert(test_atan2(1/ -9_fix, 1/ 13_fix,-0.965223096250));
  static_assert(test_atan2(1/  9_fix, 1/-13_fix,2.176369557339));
  static_assert(test_atan2(1/  9_fix, 1/ 13_fix,0.965223096250));
  //atan2(+-1/9_fix, +-1/17_fix)
  static_assert(test_atan2(1/ -9_fix, 1/-17_fix,-2.057733420184));
  static_assert(test_atan2(1/ -9_fix, 1/ 17_fix,-1.083859233406));
  static_assert(test_atan2(1/  9_fix, 1/-17_fix,2.057733420184));
  static_assert(test_atan2(1/  9_fix, 1/ 17_fix,1.083859233406));
  //atan2(+-1/13_fix, +-1/1_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -1_fix,-3.064824262867));
  static_assert(test_atan2(1/-13_fix, 1/  1_fix,-0.076768390723));
  static_assert(test_atan2(1/ 13_fix, 1/ -1_fix,3.064824262867));
  static_assert(test_atan2(1/ 13_fix, 1/  1_fix,0.076768390723));
  //atan2(+-1/13_fix, +-1/2_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -2_fix,-2.988950204887));
  static_assert(test_atan2(1/-13_fix, 1/  2_fix,-0.152642448703));
  static_assert(test_atan2(1/ 13_fix, 1/ -2_fix,2.988950204887));
  static_assert(test_atan2(1/ 13_fix, 1/  2_fix,0.152642448703));
  //atan2(+-1/13_fix, +-1/3_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -3_fix,-2.914800492084));
  static_assert(test_atan2(1/-13_fix, 1/  3_fix,-0.226792161506));
  static_assert(test_atan2(1/ 13_fix, 1/ -3_fix,2.914800492084));
  static_assert(test_atan2(1/ 13_fix, 1/  3_fix,0.226792161506));
  //atan2(+-1/13_fix, +-1/5_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -5_fix,-2.774429044930));
  static_assert(test_atan2(1/-13_fix, 1/  5_fix,-0.367163608660));
  static_assert(test_atan2(1/ 13_fix, 1/ -5_fix,2.774429044930));
  static_assert(test_atan2(1/ 13_fix, 1/  5_fix,0.367163608660));
  //atan2(+-1/13_fix, +-1/7_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -7_fix,-2.647657654381));
  static_assert(test_atan2(1/-13_fix, 1/  7_fix,-0.493934999209));
  static_assert(test_atan2(1/ 13_fix, 1/ -7_fix,2.647657654381));
  static_assert(test_atan2(1/ 13_fix, 1/  7_fix,0.493934999209));
  //atan2(+-1/13_fix, +-1/9_fix)
  static_assert(test_atan2(1/-13_fix, 1/ -9_fix,-2.536019423045));
  static_assert(test_atan2(1/-13_fix, 1/  9_fix,-0.605573230544));
  static_assert(test_atan2(1/ 13_fix, 1/ -9_fix,2.536019423045));
  static_assert(test_atan2(1/ 13_fix, 1/  9_fix,0.605573230544));
  //atan2(+-1/13_fix, +-1/13_fix)
  static_assert(test_atan2(1/-13_fix, 1/-13_fix,-2.356194490192));
  static_assert(test_atan2(1/-13_fix, 1/ 13_fix,-0.785398163397));
  static_assert(test_atan2(1/ 13_fix, 1/-13_fix,2.356194490192));
  static_assert(test_atan2(1/ 13_fix, 1/ 13_fix,0.785398163397));
  //atan2(+-1/13_fix, +-1/17_fix)
  static_assert(test_atan2(1/-13_fix, 1/-17_fix,-2.223657684135));
  static_assert(test_atan2(1/-13_fix, 1/ 17_fix,-0.917934969455));
  static_assert(test_atan2(1/ 13_fix, 1/-17_fix,2.223657684135));
  static_assert(test_atan2(1/ 13_fix, 1/ 17_fix,0.917934969455));
  //atan2(+-1/17_fix, +-1/1_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -1_fix,-3.082837725355));
  static_assert(test_atan2(1/-17_fix, 1/  1_fix,-0.058754928235));
  static_assert(test_atan2(1/ 17_fix, 1/ -1_fix,3.082837725355));
  static_assert(test_atan2(1/ 17_fix, 1/  1_fix,0.058754928235));
  //atan2(+-1/17_fix, +-1/2_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -2_fix,-3.024485679668));
  static_assert(test_atan2(1/-17_fix, 1/  2_fix,-0.117106973922));
  static_assert(test_atan2(1/ 17_fix, 1/ -2_fix,3.024485679668));
  static_assert(test_atan2(1/ 17_fix, 1/  2_fix,0.117106973922));
  //atan2(+-1/17_fix, +-1/3_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -3_fix,-2.966920454582));
  static_assert(test_atan2(1/-17_fix, 1/  3_fix,-0.174672199008));
  static_assert(test_atan2(1/ 17_fix, 1/ -3_fix,2.966920454582));
  static_assert(test_atan2(1/ 17_fix, 1/  3_fix,0.174672199008));
  //atan2(+-1/17_fix, +-1/5_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -5_fix,-2.855541211872));
  static_assert(test_atan2(1/-17_fix, 1/  5_fix,-0.286051441717));
  static_assert(test_atan2(1/ 17_fix, 1/ -5_fix,2.855541211872));
  static_assert(test_atan2(1/ 17_fix, 1/  5_fix,0.286051441717));
  //atan2(+-1/17_fix, +-1/7_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -7_fix,-2.750980237563));
  static_assert(test_atan2(1/-17_fix, 1/  7_fix,-0.390612416027));
  static_assert(test_atan2(1/ 17_fix, 1/ -7_fix,2.750980237563));
  static_assert(test_atan2(1/ 17_fix, 1/  7_fix,0.390612416027));
  //atan2(+-1/17_fix, +-1/9_fix)
  static_assert(test_atan2(1/-17_fix, 1/ -9_fix,-2.654655560200));
  static_assert(test_atan2(1/-17_fix, 1/  9_fix,-0.486937093389));
  static_assert(test_atan2(1/ 17_fix, 1/ -9_fix,2.654655560200));
  static_assert(test_atan2(1/ 17_fix, 1/  9_fix,0.486937093389));
  //atan2(+-1/17_fix, +-1/13_fix)
  static_assert(test_atan2(1/-17_fix, 1/-13_fix,-2.488731296250));
  static_assert(test_atan2(1/-17_fix, 1/ 13_fix,-0.652861357340));
  static_assert(test_atan2(1/ 17_fix, 1/-13_fix,2.488731296250));
  static_assert(test_atan2(1/ 17_fix, 1/ 13_fix,0.652861357340));
  //atan2(+-1/17_fix, +-1/17_fix)
  static_assert(test_atan2(1/-17_fix, 1/-17_fix,-2.356194490192));
  static_assert(test_atan2(1/-17_fix, 1/ 17_fix,-0.785398163397));
  static_assert(test_atan2(1/ 17_fix, 1/-17_fix,2.356194490192));
  static_assert(test_atan2(1/ 17_fix, 1/ 17_fix,0.785398163397));
  return true;
  }
  
  static_assert(atan_unit_tests());
}
