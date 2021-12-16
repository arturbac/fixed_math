#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
  constexpr bool test_sin( fixed_t x, fixed_t expected )
    {
    return abs(sin( x ) - expected ) < 0.0001_fix &&
      abs(sin( x + 2*phi ) - expected ) < 0.0001_fix &&
      abs(sin( x - 2*phi ) - expected ) < 0.0001_fix &&
      abs(sin( x + 4*phi ) - expected ) < 0.0001_fix;
    }
    
  constexpr bool test_cos( fixed_t x, fixed_t expected )
    {
    return abs(cos( x ) - expected ) < 0.0001_fix &&
      abs(cos( x + 2*phi ) - expected ) < 0.0001_fix &&
      abs(cos( x - 2*phi ) - expected ) < 0.0001_fix &&
      abs(cos( x + 4*phi ) - expected ) < 0.0001_fix;
    }
[[nodiscard]]
constexpr bool sin_unit_tests() noexcept
  {
  //------------------------------------------------------------------------------------------------------
  //
  // sin
  //

  static_assert( test_sin( phi + phi/2 ,  -0.9998626708984375_fix ));
  static_assert( test_sin( phi + phi/4 ,  -0.7071075439453125_fix ));
  static_assert( test_sin( phi,            0_fix ));
  static_assert( test_sin( 0_fix       ,   0_fix ));
  static_assert( test_sin( phi /2 + phi/4, 0.7071075439453125_fix ));

  static_assert( test_sin( phi/2_fix,      0.9998474121093750_fix ));
  static_assert( test_sin( phi/4_fix,      0.7070922851562500_fix ));
  static_assert( test_sin( phi/5_fix,      0.5877838134765625_fix ));
  static_assert( test_sin( phi/8_fix,      0.3826599121093750_fix ));
  static_assert( test_sin( phi/16_fix,     0.1950683593750000_fix ));
  static_assert( test_sin(-phi/16_fix,    -0.1950836181640625_fix ));
  static_assert( test_sin( phi/-8_fix,    -0.3826751708984375_fix ));
  static_assert( test_sin( phi/-5_fix,    -0.5877990722656250_fix ));
  static_assert( test_sin( phi/-4_fix,    -0.7071075439453125_fix ));
  static_assert( test_sin( phi/-2_fix,    -0.9998626708984375_fix ));

  static_assert( test_sin( phi + phi + phi/2,        0.9998474121093750_fix));
  static_assert( test_sin( phi + phi + phi/4,        0.7070922851562500_fix));
  static_assert( test_sin( phi + phi,                0_fix));
  static_assert( test_sin( phi + phi /2 + phi/4,    -0.7071228027343750_fix));
  static_assert( test_sin( 2*phi + phi + phi/2,     -0.9998626708984375_fix));
  static_assert( test_sin( 2*phi + phi + phi/4,     -0.7071075439453125_fix));
  static_assert( test_sin( 2*phi + phi,              0_fix));
  static_assert( test_sin( 2*phi + phi /2 + phi/4,   0.7071075439453125_fix));

  static_assert( test_sin( -phi-phi /16,  0.1950683593750000_fix ));
  static_assert( test_sin( -phi-phi /8,   0.3826599121093750_fix ));
  static_assert( test_sin( -phi-phi /5,   0.5877838134765625_fix ));
  static_assert( test_sin( -phi-phi /4,   0.7070922851562500_fix ));
  static_assert( test_sin( -phi-phi /2,   0.9998474121093750_fix ));
  
  static_assert( test_sin( -6*phi + -95* phi / 180, -0.9961242675781250_fix ));
  static_assert( test_sin( -4*phi + -95* phi / 180, -0.9961242675781250_fix ));
  static_assert( test_sin( -2*phi + -95* phi / 180, -0.9961242675781250_fix ));
  static_assert( test_sin( -95* phi / 180,          -0.9961242675781250_fix ));
  static_assert( test_sin( -90* phi / 180,          -0.9998626708984375_fix ));
  static_assert( test_sin( -85* phi / 180,          -0.9961090087890625_fix ));

  //------------------------------------------------------------------------------------------------------
  //
  // cos
  //

  static_assert( test_cos( 2 * phi,           0.9998474121093750_fix ));
  static_assert( test_cos( phi,              -0.9998626708984375_fix ));
  static_assert( test_cos( phi /2 + phi/4,   -0.7071075439453125_fix ));
  static_assert( test_cos( phi /2,            0_fix ));
  static_assert( test_cos( phi /3,            0.4999847412109375_fix ));
  static_assert( test_cos( phi /4,            0.7071075439453125_fix ));
  static_assert( test_cos( phi /16,           0.9807281494140625_fix ));
  static_assert( test_cos( 0_fix,             0.9998474121093750_fix ));
  static_assert( test_cos( -phi /16,          0.9807434082031250_fix ));
  static_assert( test_cos( -phi /4,           0.7071075439453125_fix ));
  static_assert( test_cos( -phi /3,           0.5000000000000000_fix ));
  static_assert( test_cos( -phi /2,           0.0001_fix ));
  static_assert( test_cos( -phi /2 + -phi/4, -0.7070922851562500_fix ));
  static_assert( test_cos( -phi,             -0.9998626708984375_fix ));
  static_assert( test_cos( 2 * -phi,         0.9998474121093750_fix ));
  
  return true;
  }
  
  static_assert(sin_unit_tests());
}
