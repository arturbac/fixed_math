// #define FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO 1
#include <fixedmath/unittests/unit_test_common.h>
#include <fixedmath/iostream.h>
#include <cassert>

namespace fixedmath
{

static fixed_t nhypot(fixed_t lh, fixed_t rh ) noexcept
    {
    constexpr int prec_ = 16;
    //sqrt(X^2+Y^2) = sqrt( (X/D)^2+(Y/D)^2) * D
    //D = 2^n
    if( lh < 0_fix )
      lh = -lh;
    if( rh < 0_fix )
      rh = -rh;
    uint64_t uhi { static_cast<uint64_t>(lh.v)};
    uint64_t ulo { static_cast<uint64_t>(rh.v)};
    
    //reorder hi/lo
    if( uhi < ulo )
      {
      uhi = ulo;
      ulo = static_cast<uint64_t>(lh.v);
      }
    int lbits{ cxx20::countl_zero( uhi ) };
    int rbits{ cxx20::countr_zero( uhi ) };
    int llbits{ cxx20::countl_zero( ulo ) };
    int lrbits{ cxx20::countr_zero( ulo ) };
    
    if( uhi == 0 )
      return 0_fix;
    //check hi for overflow and shift right with d
    else if( uhi >= (1ull<<30) )
      {
      int rshbits{ std::min(cxx20::countr_zero( uhi ),cxx20::countr_zero( ulo )) };
      uhi >>= rshbits;
      ulo >>= rshbits;
      return as_fixed(sqrt( as_fixed( fixed_internal((uhi*uhi+ulo*ulo)>>prec_) ) ).v << rshbits)  ;
      }
    //else check lo for underflow and shift left with d
    else if( ulo < (1<<16) )
      {
      int lshbits{ std::max(cxx20::countl_zero( uhi ) - 30,0) >> 1 };
//       fixed_t ln{ lh*(1<<lshbits)};
//       fixed_t rn{ rh*(1<<lshbits)};
//       
//       //sqrt(X^2+Y^2) = sqrt( (X/D)^2+(Y/D)^2) * D
//       std::cout << sqrt( ln*ln+rn*rn) /(1<<lshbits) << std::endl; 
    
      uhi <<= lshbits;
      ulo <<= lshbits;

      return as_fixed( fixedmath::sqrt( as_fixed( fixed_internal((uhi*uhi+ulo*ulo)>>prec_)) ).v  >> lshbits);
      }
    else
      return sqrt( as_fixed( fixed_internal((uhi*uhi+ulo*ulo)>>prec_) ) );
    }
inline void test_hypot( fixed_t x, fixed_t y, fixed_t expected )
    {
//     static constexpr fixed_t tolerance = 0.00001_fix;
    fixed_t res1{ abs( nhypot( x, y ) ) };
    double exp { std::hypot(static_cast<double>(x), static_cast<double>(y)) };
    std::cout << " d" << exp << " h" << res1 << " ex" << expected << std::endl;
    }

}
using FX = fixedmath::fixed_internal;
int main( int argc, char ** argv ) 
{
  using namespace fixedmath;
//   double exp { std::hypot(-14.991608,-0.837158) };
//   fixed_t sq_res { sqrt(-14.991608_fix*-14.991608_fix + -0.837158_fix * -0.837158_fix) };
//   fixed_t h_res { nhypot(-14.991608_fix,-0.837158_fix) };
//   std::cout << " d" << exp << " s" << sq_res<< " h" << h_res << std::endl;
//   hypot(-14.991608,-0.837158) -> 1.203796 (15.014969) 
//   
  ( test_hypot(14.9916076660156250_fix,0_fix, 14.9916076660156250_fix));
  ( test_hypot(0_fix, 14.9916076660156250_fix, 14.9916076660156250_fix));
   
  ( test_hypot(-14.991608_fix,-0.837158_fix, 15.0149536132812500_fix));
  ( test_hypot(-0.774933_fix,-4.295090_fix, 4.3644377251651436_fix)); 
   test_hypot(-20.245346_fix,-0.909424_fix, 20.265762_fix);
//     d20.2657614997891855 h20.2657470703125000 ex20.2657623291015625
  ( test_hypot(as_fixed(FX(1ul<<32)),as_fixed(FX(1ul<<31)), 73270_fix));
  ( test_hypot(as_fixed(1ul<<30),as_fixed(1<<0ul), 16384_fix) );
  ( test_hypot(as_fixed(1ul<<33),as_fixed(1ul<<31), 135104_fix) );
  ( test_hypot(as_fixed(1ul<<31),as_fixed(1ul<<31), 46340_fix));
  ( test_hypot(as_fixed(1ul<<32),as_fixed(1ul), 65536_fix));
  ( test_hypot(as_fixed(1ul<<30),as_fixed(1<<30ul), 23170_fix));
  ( test_hypot(as_fixed((1ul<<30)-1), as_fixed((1ul<<30)-1), 23170.4749755859375_fix) );

  ( test_hypot(as_fixed(1),as_fixed(1), 0.0000152587890625_fix));
  ( test_hypot(as_fixed(2),as_fixed(2), 0.0000305175781250_fix));
  ( test_hypot(as_fixed(1),as_fixed(3), 0.0000457763671875_fix));
  ( test_hypot(as_fixed(2),as_fixed(3), 0.0000457763671875_fix));
  ( test_hypot(0.0125_fix,0.125_fix, 0.1256103515625000_fix));
  ( test_hypot(1_fix,1_fix, 1.4141998291015625_fix));
  ( test_hypot(0.5_fix,0.25_fix, 0.5590057373046875_fix));

}
