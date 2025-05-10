// SPDX-FileCopyrightText: 2025 Artur Bać
// SPDX-License-Identifier: BSL-1.0
// SPDX-PackageHomePage: https://github.com/arturbac/fixed_math
#include <unit_test_core.h>
#include <unit_test_common.h>
#include <fixedmath/fixed_string.h>
#include <fixedmath/iostream.h>
#include <fixedmath/std_formatter.h>

#include <iostream>
#include <sstream>
#include <string>

using namespace std::string_view_literals;
using boost::ut::operator""_test;
using namespace metatests;
using namespace fixedmath;

int main()
  {
  test_result result;
  static constexpr fixed_t epsilon = fixed_t{0.0001};

  "from_string"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      // Typical cases
      {
      auto v1 = from_string("3.141592654  ");
      expect(v1.has_value());
      if(v1)
        expect_approx(*v1, 3.14159_fix, epsilon);
      }
      {
      auto v2 = from_string("-42.5");
      expect(v2.has_value());
      if(v2)
        expect_approx(*v2, -42.5_fix, epsilon);
      }
      {
      auto v3 = from_string("0");
      expect(v3.has_value());
      if(v3)
        expect_eq(*v3, 0_fix);
      }
      {
      auto v4 = from_string("+123.456");
      expect(v4.has_value());
      if(v4)
        expect_approx(*v4, 123.456_fix, epsilon);
      }
      {
      auto v5 = from_string("NaN");
      expect(v5.has_value());
      if(v5)
        expect(fixedmath::fobj::isnan(*v5));
      }
      {
      auto v6 = from_string("nan");
      expect(v6.has_value());
      if(v6)
        expect(fixedmath::fobj::isnan(*v6));
      }
      {
      auto v = from_string("0.125");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.125_fix);
      }
      {
      auto v = from_string("0.0000152587890625");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0000152587890625_fix);
      }
      {
      auto v = from_string("0.0000305175781250");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0000305175781250_fix);
      }
      {
      auto v = from_string("0.0000610351562500");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0000610351562500_fix);
      }
      {
      auto v = from_string("0.0001220703125000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0001220703125000_fix);
      }
      {
      auto v = from_string("0.0002441406250000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0002441406250000_fix);
      }
      {
      auto v = from_string("0.0004882812500000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0004882812500000_fix);
      }
      {
      auto v = from_string("0.0009765625000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0009765625000000_fix);
      }
      {
      auto v = from_string("0.0019531250000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0019531250000000_fix);
      }
      {
      auto v = from_string("0.0039062500000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0039062500000000_fix);
      }
      {
      auto v = from_string("0.0078125000000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0078125000000000_fix);
      }
      {
      auto v = from_string("0.0156250000000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0156250000000000_fix);
      }
      {
      auto v = from_string("0.0312500000000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0312500000000000_fix);
      }
      {
      auto v = from_string("0.0625000000000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.0625000000000000_fix);
      }
      {
      auto v = from_string("0.1250000000000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.1250000000000000_fix);
      }
      {
      auto v = from_string("0.2500000000000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.2500000000000000_fix);
      }
      {
      auto v = from_string("0.5000000000000000");
      expect(v.has_value());
      if(v)
        expect_eq(*v, 0.5000000000000000_fix);
      }
    // Edge/invalid cases
    expect(not from_string("abc").has_value());
    expect(not from_string("").has_value());
    expect(not from_string("123.45.67").has_value());
    expect(not from_string("123abc").has_value());
    return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };

  static_assert(expect(to_string(fixed_t{3.14159}, 5).substr(0, 2) == "3."sv));

  "to_string"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      {
      auto pi{3.14159_fix};
      std::string s1 = to_string(pi, 5);
      expect(s1.substr(0, 2) == "3.");
      }
      {
      fixed_t neg{-42.5};
      std::string s2 = to_string(neg, 2);
      expect_eq(s2, "-42.5"sv);
      }
      {
      fixed_t zero{0};
      std::string s3 = to_string(zero);
      expect(s3 == "0" || s3 == "0.0");
      }
      {
      fixed_t nan = quiet_NaN_result();
      std::string s4 = to_string(nan);
      expect(s4 == "NaN");
      }
      {
      auto v{0.0000152587890625_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.0000152587890625"sv);
      }
      {
      auto v{0.000030517578125_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.000030517578125"sv);
      }
      {
      auto v{0.00006103515625_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.00006103515625"sv);
      }
      {
      auto v{0.0001220703125_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.0001220703125"sv);
      }
      {
      auto v{0.000244140625_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.000244140625"sv);
      }
      {
      auto v{0.00048828125_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.00048828125"sv);
      }
      {
      auto v{0.0009765625_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.0009765625"sv);
      }
      {
      auto v{0.001953125_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.001953125"sv);
      }
      {
      auto v{0.00390625_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.00390625"sv);
      }
      {
      auto v{0.0078125_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.0078125"sv);
      }
      {
      auto v{0.015625_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.015625"sv);
      }
      {
      auto v{0.03125_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.03125"sv);
      }
      {
      auto v{0.0625_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.0625"sv);
      }
      {
      auto v{0.125_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.125"sv);
      }
      {
      auto v{0.25_fix};
      std::string s1 = to_string(v, 16);
      expect_eq(s1,"0.25"sv);
      }
    return {};
    };
    result |= run_runtime_test(fn_tmpl);
    result |= run_consteval_test(fn_tmpl);
  };
  "stream_io"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      // Output
      fixed_t val{1.2345};
      std::ostringstream oss;
      oss << val;
      std::string out = oss.str();
      expect_eq(out.substr(0, 5), "1.234"sv);
      // Input
      std::istringstream iss("-99.99");
      fixed_t in;
      iss >> in;
      expect(expect_approx(in, fixed_t{-99.99}, epsilon));
      // NaN input
      std::istringstream iss2("NaN");
      fixed_t in2;
      iss2 >> in2;
      expect(fixedmath::fobj::isnan(in2));
      std::cout << "test_stream_io passed\n";
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
  };

  "format"_test = [&result]
  {
    auto fn_tmpl = []() -> metatests::test_result
    {
      fixed_t val{1.2345};
      std::string out{std::format("{}", val)};
      expect_eq(out.substr(0, 5), "1.234"sv);
      return {};
    };
    result |= run_runtime_test(fn_tmpl);
  };
  }
