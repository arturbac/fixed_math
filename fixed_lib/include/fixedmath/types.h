// MIT License
// 
// Copyright (c) 2020-2021 Artur Bac
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once
#include <cstdint>
#include <type_traits>
#include <limits>
#include <cmath>
#include "utility_cxx20.h"



#define FIXEDMATH_VERSION_MAJOR 0
#define FIXEDMATH_VERSION_MINOR 9
#define FIXEDMATH_VERSION_PATCH 5
#define FIXEDMATH_VERSION_STRING "fixedmath 0.9.5 beta"

namespace fixedmath
{
  using fixed_internal = int64_t;
  using fixed_internal_unsigned = uint64_t;

  //the idea behind carrier is to use it as carier of internal int64 value in format of fixed to distinguish it from int64 integral type.
  struct fix_carrier_t 
    { 
    fixed_internal v;
    
    constexpr fix_carrier_t() : v{}{}
    constexpr fix_carrier_t( fix_carrier_t const & ) = default;
    constexpr fix_carrier_t & operator=( fix_carrier_t const & ) = default;
  
    template<typename input_type>
    explicit constexpr fix_carrier_t( input_type const & value) : v{value}
      {
      static_assert( std::is_same<fixed_internal, input_type>::value, "cast allowed only for internal type" );
      }
    };
  
  struct fixed_t;
  
  template<typename integral_type>
  constexpr integral_type fixed_to_integral ( fixed_t value ) noexcept;
  
  ///\brief hermetization of fixed value to avoid implicit conversions from int64, long long 
  struct fixed_t
    {
    fixed_internal v;
    
    template<typename floating_or_integral_type>
    explicit constexpr operator floating_or_integral_type() const noexcept;
    
    constexpr fixed_t() : v{}{}
    
    constexpr fixed_t( fixed_t const & ) = default;
    
    constexpr fixed_t & operator=( fixed_t const & ) = default;
    
    constexpr fixed_t( fix_carrier_t value) : v{ value.v }{}
    
    template<typename arithemtic_type>
    explicit constexpr fixed_t( arithemtic_type const & value );
    };

  
  ///\brief constructs fixed from raw value in internal format
  constexpr fixed_t as_fixed( fixed_internal carried ) { return fix_carrier_t{carried}; }
    
  [[ gnu::const, gnu::always_inline ]]
  inline bool constexpr
  operator != ( fixed_t l, fixed_t r ) noexcept { return l.v != r.v; }
  
  [[ gnu::const, gnu::always_inline ]]
  inline bool constexpr
  operator == ( fixed_t l, fixed_t r ) noexcept { return l.v == r.v; }
  
  [[ gnu::const, gnu::always_inline ]]
  inline bool constexpr
  operator > ( fixed_t l, fixed_t r ) noexcept { return l.v > r.v; }
  
  [[ gnu::const, gnu::always_inline ]]
  inline bool constexpr
  operator >= ( fixed_t l, fixed_t r ) noexcept { return l.v >= r.v; }
  
  [[ gnu::const, gnu::always_inline ]]
  inline bool constexpr
  operator < ( fixed_t l, fixed_t r ) noexcept { return l.v < r.v; }
  
  [[ gnu::const, gnu::always_inline ]]
  inline bool constexpr
  operator <= ( fixed_t l, fixed_t r ) noexcept { return l.v <= r.v; }

  
}

