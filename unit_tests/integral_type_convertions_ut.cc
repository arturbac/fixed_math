#pragma once

#include <unit_test_core.h>
#include <unit_test_common.h>

using boost::ut::operator""_test;
using namespace metatests;

// namespace fixedmath
// {
// [[nodiscard]]
// constexpr bool integral_type_convertions_unit_tests() noexcept
//   {
//   //------------------------------------------------------------------------------------------------------
//   //
//   // arithmetic_to_fixed unit tests
//   //
//   expect_eq( arithmetic_to_fixed(0) == 0_fix );

//   
//   //------------------------------------------------------------------------------------------------------
//   //
//   // fixed_to_integral
//   //

//   return true;
//   }
//   expect_eq(integral_type_convertions_unit_tests());
// }
int main()
  {
    test_result result;
    using F = fixedmath::fixed_internal;
    
    using namespace fixedmath;
    "arithmetic_to_fixed integrals"_test = [&result]
    {
      auto fn_tmpl = [] -> metatests::test_result
        {
        expect_eq( arithmetic_to_fixed(0), 0_fix );
        expect_eq( arithmetic_to_fixed(1), limits_::one() );
        expect_eq( arithmetic_to_fixed(-1), -limits_::one() );
        expect_neq( arithmetic_to_fixed(-1), limits_::one() );
        expect_neq( arithmetic_to_fixed(-1), 0_fix );
        expect_neq( arithmetic_to_fixed(1), 0_fix );
        expect_neq( arithmetic_to_fixed(1), arithmetic_to_fixed(-1) );
        expect_eq( arithmetic_to_fixed(1), arithmetic_to_fixed(1) );

        expect_eq( 0_fix, fixed_t{});
        expect_eq( 1_fix, limits_::one());
        expect_eq( -1_fix, -limits_::one());
        expect_eq( as_fixed(F(0x80000000LL)), 32768_fix);
        expect_eq( as_fixed(F(0)), 0_fix);
        expect_eq( as_fixed(F(1ll<<32)), 65536_fix );
        
        // 
        return {};
        };
      result |=run_constexpr_test(fn_tmpl);
      result |=run_consteval_test(fn_tmpl);
    };
    
    "arithmetic_to_fixed floating point"_test = [&result]
    {
      auto fn_tmpl = [] -> metatests::test_result
        {
        expect_eq( arithmetic_to_fixed(0.f), 0_fix );
        expect_eq( arithmetic_to_fixed(-1.f), -limits_::one() );
        expect_neq( arithmetic_to_fixed(-1.f),  limits_::one() );
        expect_neq( arithmetic_to_fixed(-1.f),  0_fix );
        expect_neq( arithmetic_to_fixed(1.f),  0_fix );
        expect_neq( arithmetic_to_fixed(1.f),  arithmetic_to_fixed(-1) );
        expect_eq( arithmetic_to_fixed(1.f), arithmetic_to_fixed(1) );
        expect_eq( arithmetic_to_fixed(0.f), 0_fix );
        expect_eq( arithmetic_to_fixed(float(limits_::max_integral())), limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(flimits_::max()), limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(float(limits_::max_integral()+1ll)), limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(float(limits_::min_integral())), limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(float(limits_::min_integral()-1ll)), limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(flimits_::lowest()), limits_::quiet_NaN() );
        expect_neq( arithmetic_to_fixed(flimits_::min()),  limits_::quiet_NaN() );
        
        expect_eq( arithmetic_to_fixed(-1.), -limits_::one() );
        expect_neq( arithmetic_to_fixed(-1.),  limits_::one() );
        expect_neq( arithmetic_to_fixed(-1.),  0_fix );
        expect_neq( arithmetic_to_fixed(1.),  0_fix );
        expect_neq( arithmetic_to_fixed(1.),  arithmetic_to_fixed(-1) );
        expect_eq( arithmetic_to_fixed(1.), arithmetic_to_fixed(1) );
        expect_eq( arithmetic_to_fixed(double(limits_::max_integral())), limits_::quiet_NaN() );
        expect_neq( arithmetic_to_fixed(double(limits_::max_integral()-1ll)),  limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(double(limits_::max_integral()+1ll)), limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(double(limits_::min_integral())), limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(double(limits_::min_integral()-1ll)), limits_::quiet_NaN() );
        expect_neq( arithmetic_to_fixed(double(limits_::min_integral()+1ll)),  limits_::quiet_NaN() );
        expect_eq( arithmetic_to_fixed(dlimits_::lowest()), limits_::quiet_NaN() );
        expect_neq( arithmetic_to_fixed(dlimits_::min()),  limits_::quiet_NaN() );
        return {};
        };
      result |=run_constexpr_test(fn_tmpl);
      result |=run_consteval_test(fn_tmpl);
    };
    
    "fixed_to_arithmetic integrals"_test = [&result]
    {
      auto fn_tmpl = [] -> metatests::test_result
        {
        expect_eq( fixed_to_arithmetic<int>(0.25_fix), 0 );
        expect_eq( fixed_to_arithmetic<int>(1.25_fix), 1 );
        expect_eq( fixed_to_arithmetic<int>(100.25_fix), 100 );
        expect_eq( fixed_to_arithmetic<int>(100.55_fix), 100 );
        expect_eq( fixed_to_arithmetic<unsigned>(100.55_fix), 100u );
        return {};
        };
      result |=run_constexpr_test(fn_tmpl);
      result |=run_consteval_test(fn_tmpl);
    };
    "fixed_to_arithmetic integrals"_test = [&result]
    {
      auto fn_tmpl = [] -> metatests::test_result
        {
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(0.f)),  0.f );
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(1.f)),  1.f );
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(0.25f)),  0.25f );
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(0.5f)),  0.5f );
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(0.75f)),  0.75f );
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(-1.f)),  -1.f );
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(-0.25f)),  -0.25f );
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(-0.5f)),  -0.5f );
      expect_eq( fixed_to_arithmetic<float>(arithmetic_to_fixed(-0.75f)),  -0.75f );
      
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(0.f)),  0. );
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(1.f)),  1. );
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(0.25f)),  0.25 );
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(0.5f)),  0.5 );
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(0.75f)),  0.75 );
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(-1.f)),  -1. );
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(-0.25f)),  -0.25 );
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(-0.5f)),  -0.5 );
      expect_eq( fixed_to_arithmetic<double>(arithmetic_to_fixed(-0.75f)),  -0.75 );
        return {};
        };
      result |=run_constexpr_test(fn_tmpl);
      result |=run_consteval_test(fn_tmpl);
    };
  }
