#pragma once
#include <cstdint>
#include <type_traits>
#include <limits>
#include <cmath>
#include "utility_cxx20.h"

namespace fixedmath
  {
  using fixed_internal = int64_t;
  using fixed_internal_unsigned = uint64_t;
  
  struct fix_carrier_t;
  struct fixed_t;
  
  }
namespace fixedmath::detail
  {
  template<int size>
  struct signed_type_by_size {};
  
  template<>
  struct signed_type_by_size<1> { using type = int8_t; };
  
  template<>
  struct signed_type_by_size<2> { using type = int16_t; };
  
  template<>
  struct signed_type_by_size<4> { using type = int32_t; };
  
  template<>
  struct signed_type_by_size<8> { using type = int64_t; };
  
  template<>
  struct signed_type_by_size<16> { using type = int64_t; };
  
  // concepts
  template<typename arithmetic_type>
  inline constexpr bool is_signed_v = std::numeric_limits<arithmetic_type>::is_signed;
  
  template<typename arithmetic_type>
  inline constexpr bool is_unsigned_v = !std::numeric_limits<arithmetic_type>::is_signed;
  
  template<typename supported_type>
  inline constexpr bool is_fixed_v = std::is_same_v<supported_type,fixed_t>;
  
  template<typename supported_type>
  inline constexpr bool is_double_v = std::is_same_v<supported_type,double>;
  
  template<typename supported_type>
  inline constexpr bool is_integral_v = std::is_integral_v<supported_type>;
  
  template<typename supported_type>
  inline constexpr bool is_floating_point_v = std::is_floating_point_v<supported_type> 
                                           || is_fixed_v<supported_type>;
  
  template<typename supported_type>
  inline constexpr bool is_arithmetic_v = 
                                is_integral_v<supported_type> 
                             || is_floating_point_v<supported_type>;

  template<typename supported_type>
  inline constexpr bool is_arithmetic_and_not_fixed_v = 
                  is_arithmetic_v<supported_type> && (!is_fixed_v<supported_type>);
                  
  template<typename supported_type>
  inline constexpr bool is_floating_point_and_not_fixed_v = 
                  is_floating_point_v<supported_type> && (!is_fixed_v<supported_type>);
                  
  template<typename supported_type1, typename supported_type2>
  inline constexpr bool arithmetic_and_one_is_fixed_v = 
                  is_arithmetic_v<supported_type1> && 
                  is_arithmetic_v<supported_type2> && 
                  ( is_fixed_v<supported_type1> || is_fixed_v<supported_type2> );
                  
  template<typename supported_type1, typename supported_type2>
  inline constexpr bool one_of_is_double_v = is_double_v<supported_type1> || is_double_v<supported_type2>;
  
  using limits_ = std::numeric_limits<fixedmath::fixed_t>;
  using flimits_ = std::numeric_limits<float>;
  using dlimits_ = std::numeric_limits<double>;
  }
