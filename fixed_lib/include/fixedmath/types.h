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
#include "../utility_cxx20.h"

// #include <numbers>
#define FIXEDMATH_PUBLIC gnu::visibility("default")
namespace fixedmath
{
  using fixed_internal = int64_t;
  
  #define fixed_likely(x)    __builtin_expect(static_cast<bool>(x), 1)
  #define fixed_unlikely(x)  __builtin_expect(static_cast<bool>(x), 0)

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
  constexpr fixed_t integral_to_fixed(integral_type value) noexcept;
  
  template<typename arithmethic_type>
  constexpr fixed_t arithmetic_to_fixed( arithmethic_type value ) noexcept;
  
  template<typename integral_type>
  constexpr integral_type fixed_to_integral ( fixed_t value ) noexcept;
  
  ///\brief hermetization of fixed value to avoid implicit conversions from int64, long long 
  struct [[FIXEDMATH_PUBLIC]] fixed_t
    {
    fixed_internal v;
    
    //making double implicit causes invalid comparisions with implicit double convertion
    explicit constexpr operator double() const noexcept;
    
    template<typename floating_or_integral_type>
    explicit constexpr operator floating_or_integral_type() const noexcept;
    
    constexpr fixed_t() : v{}{}
    
    constexpr fixed_t( fixed_t const & ) = default;
    
    constexpr fixed_t & operator=( fixed_t const & ) = default;
    
    constexpr fixed_t( fix_carrier_t value) : v{ value.v }{}
    
    template<typename arithemtic_type>
    explicit constexpr fixed_t( arithemtic_type const & value );
    };

  template<typename supported_type>
  struct is_fixed_t : 
      public std::integral_constant<bool,std::is_same<cxx20::remove_cvref_t<supported_type>,fixed_t>::value>
    {};
  
  template<typename supported_type>
  struct is_double_t : 
      public std::integral_constant<bool,std::is_same<cxx20::remove_cvref_t<supported_type>,double>::value>
    {};
    
  template<typename supported_type>
  struct is_integral_t : 
      public std::integral_constant<bool,std::is_integral<cxx20::remove_cvref_t<supported_type>>::value>
    {};
  
  template<typename supported_type>
  using is_fixed = typename is_fixed_t<supported_type>::type;
  
  template<typename supported_type>
  using is_double = typename is_double_t<supported_type>::type;
  
  template<typename supported_type>
  using is_integral = typename is_integral_t<supported_type>::type;
  
  template<typename supported_type>
  using is_floating_point = std::is_floating_point<supported_type>;
  
  static_assert( is_fixed<fixed_t>{} );
  static_assert( is_fixed<fixed_t const &>{} );
  
  template<typename supported_type>
  struct is_arithemetic_t
    : public std::integral_constant<bool,
                  (std::is_integral<supported_type>::value) 
                  || (std::is_floating_point<supported_type>::value)
                  || is_fixed<supported_type>{}
                    >::type
    {};
    
  template<typename supported_type>
  using is_arithemetic = typename is_arithemetic_t<supported_type>::type;
  
  template<typename supported_type>
  struct is_arithemetic_and_not_fixed_t
    : public std::integral_constant<bool,
                  is_arithemetic_t<supported_type>::value && (!is_fixed<supported_type>{}) >::type
    {};
  
  template<typename supported_type>
  using is_arithemetic_and_not_fixed = typename is_arithemetic_and_not_fixed_t<supported_type>::type;
  
  ///\brief constructs fixed from raw value in internal format
  constexpr fixed_t as_fixed( fixed_internal carried ) { return fix_carrier_t{carried}; }
  
  template<typename arithmethic_type>
  constexpr fixed_t::fixed_t( arithmethic_type const & value )
    : v{ arithmetic_to_fixed(value).v }
    {
    static_assert( is_arithemetic_and_not_fixed<arithmethic_type>{} );
    }
    
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
#define make_const_value(x) const_val<decltype(x), x>
#define static_assert_equal(x, y) static_assert( assert_equal_t< make_const_value( x ), make_const_value( y ) >::eq() )

template<typename T, T val>
struct const_val {
    static constexpr T value { val };
    constexpr const_val() = default;
    constexpr const_val(T) {}
};


template<typename T, typename U>
struct assert_equal_t 
  {
  static constexpr bool eq()
    { return assert_equal_t<decltype(T::value), decltype(U::value)>::eq( T::value, U::value ); }
    
  static constexpr bool eq( T lh, U rh )
    {
//       static_assert( lh == rh );
    return lh == rh;
    }
  static constexpr bool value { T::value == U::value };
  };

