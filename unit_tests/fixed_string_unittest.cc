// SPDX-FileCopyrightText: 2024 Artur Bać
// SPDX-License-Identifier: BSL-1.0
// SPDX-PackageHomePage: https://github.com/arturbac/fixed_math

//#include <fixedmath/fixed_math.hpp>
//#include <fixedmath/iostream.h>
#include "../../fixed_math/fixed_lib/include/fixedmath/fixed_math.hpp"
#include "../../fixed_math/fixed_lib/include/fixedmath/iostream.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>

using fixedmath::fixed_t;
using fixedmath::from_string;
using fixedmath::to_string;
using fixedmath::quiet_NaN_result;

bool fixed_close_enough(fixed_t a, fixed_t b, fixed_t epsilon = fixed_t{0.0001}) {
    return fixedmath::func::abs(a - b) < epsilon;
}

void test_from_string() {
    // Typical cases
    auto v1 = from_string("3.141592654  ");
    assert(v1 && fixed_close_enough(*v1, fixed_t{3.14159}));
    auto v2 = from_string("-42.5");
    assert(v2 && fixed_close_enough(*v2, fixed_t{-42.5}));
    auto v3 = from_string("0");
    assert(v3 && *v3 == fixed_t{0});
    auto v4 = from_string("+123.456");
    assert(v4 && fixed_close_enough(*v4, fixed_t{123.456}));
    auto v5 = from_string("NaN");
    assert(v5 && fixedmath::fobj::isnan(*v5));
    auto v6 = from_string("nan");
    assert(v6 && fixedmath::fobj::isnan(*v6));
    // Edge/invalid cases
    assert(!from_string("abc").has_value());
    assert(!from_string("").has_value());
    assert(!from_string("123.45.67").has_value());
    assert(!from_string("123abc").has_value());
    std::cout << "test_from_string passed\n";
}

void test_to_string() {
    fixed_t pi{3.14159};
    std::string s1 = to_string(pi, 5);
    assert(s1.substr(0, 2) == "3.");
    fixed_t neg{-42.5};
    std::string s2 = to_string(neg, 2);
    assert(s2.find("-42.5") == 0);
    fixed_t zero{0};
    std::string s3 = to_string(zero);
    assert(s3 == "0" || s3 == "0.0");
    fixed_t nan = quiet_NaN_result();
    std::string s4 = to_string(nan);
    assert(s4 == "NaN");
    std::cout << "test_to_string passed\n";
}

void test_stream_io() {
    // Output
    fixed_t val{1.2345};
    std::ostringstream oss;
    oss << val;
    std::string out = oss.str();
    assert(out.find("1.234") == 0);
    // Input
    std::istringstream iss("-99.99");
    fixed_t in;
    iss >> in;
    assert(fixed_close_enough(in, fixed_t{-99.99}));
    // NaN input
    std::istringstream iss2("NaN");
    fixed_t in2;
    iss2 >> in2;
    assert(fixedmath::fobj::isnan(in2));
    std::cout << "test_stream_io passed\n";
}

int main() {
    test_from_string();
    test_to_string();
    test_stream_io();
    std::cout << "All fixed_string unit tests passed!\n";
    return 0;
} 