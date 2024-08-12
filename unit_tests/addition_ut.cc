#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;

int main()
  {
  test_result result;
  "addition"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      expect_eq(fobj::add(0_fix, 1_fix), 1_fix);
      expect_eq(fobj::add(1_fix, 1_fix), 2_fix);
      expect_eq(fobj::add(10_fix, 1_fix), 11_fix);
      expect_eq(fobj::add(-10_fix, 1_fix), -9_fix);

      expect_eq(0_fix + 1_fix, 1_fix);
      expect_eq(1_fix + 1_fix, 2_fix);
      expect_eq(10.4_fix + 1_fix, 11.4_fix);
      expect_eq(-10_fix + 1_fix, -9_fix);

      expect_eq(0_fix + 1, 1_fix);
      expect_eq(1 + 1_fix, 2_fix);
      expect_eq(10.4 + 1_fix, 11.4);
      expect_eq(10.5_fix + 10.2, 20.7);
      expect_eq(-10.5_fix + uint8_t(10), -0.5_fix);
      expect_eq(-10.5_fix + uint16_t(10), -0.5_fix);
      expect_eq(-10.5_fix + uint32_t(10), -0.5_fix);
      expect_eq(-10.5_fix + uint64_t(10), -0.5_fix);
      expect_eq(uint8_t(10) + -10.5_fix, -.5_fix);
      expect_eq(uint16_t(10) + -10.5_fix, -.5_fix);
      expect_eq(uint32_t(10) + -10.5_fix, -.5_fix);
      expect_eq(uint64_t(10) + -10.5_fix, -.5_fix);
      expect_eq(-10_fix + 1, -9_fix);
      expect_eq(10.5_fix + -10., .5);
      expect_eq(10.5_fix + -10.f, .5_fix);
      expect_lt(limits_::max(), limits_::quiet_NaN());
      expect_neq(limits_::lowest() + 1, limits_::quiet_NaN());

      expect_neq(as_fixed(limits_::max().v - 65536) + 1_fix, limits_::quiet_NaN());
      
      expect( test_resulting_type<fixed_t>( int64_t(1) + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1_fix  + int64_t(1) ) );
      expect( test_resulting_type<fixed_t>( uint64_t(1) + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1_fix  + uint64_t(1) ) );
      expect( test_resulting_type<fixed_t>( 1_fix + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1 + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1_fix + 1 ) );
      expect( test_resulting_type<fixed_t>( int16_t(1) + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1_fix  + int16_t(1) ) );
      expect( test_resulting_type<fixed_t>( uint16_t(1) + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1_fix  + uint16_t(1) ) );
      expect( test_resulting_type<fixed_t>( int8_t(1) + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1_fix  + int8_t(1) ) );
      expect( test_resulting_type<fixed_t>( uint8_t(1) + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1_fix  + uint8_t(1) ) );
      expect( test_resulting_type<fixed_t>( 1.f + 1_fix ) );
      expect( test_resulting_type<fixed_t>( 1_fix  + 1.f ) );
      expect( test_resulting_type<double>( 1. + 1_fix ) );
      expect( test_resulting_type<double>( 1_fix  + 1. ) );
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  }

