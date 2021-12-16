#pragma once

#include "unit_test_common.h"

namespace fixedmath
{
  constexpr bool test_hypot( fixed_t x, fixed_t y, fixed_t expected )
    {
    return abs( hypot( x, y ) - expected ) < 0.00001_fix &&
           abs( hypot( -x, y ) - expected ) < 0.00001_fix &&
           abs( hypot( x, -y ) - expected ) < 0.00001_fix &&
           abs( hypot( -x, -y ) - expected ) < 0.00001_fix;
    }
    
[[nodiscard]]
constexpr bool sqrt_unit_tests() noexcept
  {
  //------------------------------------------------------------------------------------------------------
  //
  // sqrt
  //
  static_assert( sqrt(1.4111175537109375_fix) == 1.1878967285156250_fix);
  static_assert( sqrt(2.0000000000000000_fix) == 1.4141998291015625_fix);
  static_assert( sqrt(2.0124969482421875_fix) == 1.4186248779296875_fix);
  static_assert( sqrt(3.3333282470703125_fix) == 1.8257293701171875_fix);
  static_assert( sqrt(4.0000000000000000_fix) == 2.0000000000000000_fix);
  static_assert( sqrt(3331.0000000000000000_fix) == 57.7148132324218750_fix);
  static_assert( sqrt(33331.0000000000000000_fix) == 182.5677947998046875_fix);
  static_assert( sqrt(333331.1000061035156250_fix) == 577.3483276367187500_fix);
  static_assert( sqrt(3333331.0215148925781250_fix) == 1825.7412109375000000_fix);
  //------------------------------------------------------------------------------------------------------
  //
  // hypot
  //

  static_assert( test_hypot(-14.991608_fix,-0.837158_fix, 15.0149536132812500_fix));
  static_assert( test_hypot(-14.991608_fix,-0.837158_fix, 15.0149536132812500_fix));
  static_assert( test_hypot(-0.774933_fix,-4.295090_fix, 4.3644256591796875_fix));
  static_assert( test_hypot(-20.245346_fix,-0.909424_fix, 20.2657470703125_fix));
  static_assert( test_hypot(14.9916076660156250_fix,0_fix, 14.9916076660156250_fix));
  static_assert( test_hypot(0_fix, 14.9916076660156250_fix, 14.9916076660156250_fix));
  
  static_assert( test_hypot(as_fixed(1ul<<30),as_fixed(1<<0ul), 16384_fix) );
  static_assert( test_hypot(as_fixed(1ul<<33),as_fixed(1ul<<31), 135104_fix) );
  static_assert( test_hypot(as_fixed(1ul<<32),as_fixed(1ul<<31), 73270_fix));
  static_assert( test_hypot(as_fixed(1ul<<31),as_fixed(1ul<<31), 46340_fix));
  static_assert( test_hypot(as_fixed(1ul<<32),as_fixed(1ul), 65536_fix));
  static_assert( test_hypot(as_fixed(1ul<<30),as_fixed(1<<30ul), 23170_fix));
  static_assert( test_hypot(as_fixed((1ul<<30)-1), as_fixed((1ul<<30)-1), 23170.4749755859375_fix) );

  static_assert( test_hypot(as_fixed(1),as_fixed(1), 0.0000152587890625_fix));
  static_assert( test_hypot(as_fixed(2),as_fixed(2), 0.0000305175781250_fix));
  static_assert( test_hypot(as_fixed(1),as_fixed(3), 0.0000457763671875_fix));
  static_assert( test_hypot(as_fixed(2),as_fixed(3), 0.0000457763671875_fix));
  static_assert( test_hypot(0.0125_fix,0.125_fix, 0.1256103515625000_fix));
  static_assert( test_hypot(1_fix,1_fix, 1.4141998291015625_fix));
  static_assert( test_hypot(0.5_fix,0.25_fix, 0.5590057373046875_fix));
  
  return true;
  }
  
  static_assert(sqrt_unit_tests());
}
