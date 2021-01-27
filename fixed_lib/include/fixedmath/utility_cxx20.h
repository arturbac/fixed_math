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
#include <type_traits>
#include <cstdint>

namespace cxx20
{

  ///\brief Compare the values. negative signed integers always compare less than (and not equal to) unsigned integers: the comparison is safe against lossy integer conversion.
  template< class T, class U >
  constexpr bool cmp_equal( T t, U u ) noexcept
    {
    using UT = typename std::make_unsigned<T>::type;
    using UU = typename std::make_unsigned<U>::type;
    if constexpr (std::is_signed<T>::value == std::is_signed<U>::value)
        return t == u;
    else if constexpr (std::is_signed<T>::value)
        return t < 0 ? false : static_cast<UT>(t) == u;
    else
        return u < 0 ? false : t == static_cast<UU>(u);
    }
  
  ///\brief Compare the values. negative signed integers always compare less than (and not equal to) unsigned integers: the comparison is safe against lossy integer conversion.  
  template< class T, class U >
  constexpr bool cmp_not_equal( T t, U u ) noexcept { return !cmp_equal(t, u); }

  ///\brief Compare the values. negative signed integers always compare less than (and not equal to) unsigned integers: the comparison is safe against lossy integer conversion.
  template< class T, class U >
  constexpr bool cmp_less( T t, U u ) noexcept
    {
    using UT = typename std::make_unsigned<T>::type;
    using UU = typename std::make_unsigned<U>::type;
    if constexpr (std::is_signed<T>::value == std::is_signed<U>::value )
        return t < u;
    else if constexpr (std::is_signed<T>::value)
        return t < 0 ? true : static_cast<UT>(t) < u;
    else
        return u < 0 ? false : t < static_cast<UU>(u);
    }
    
  ///\brief Compare the values. negative signed integers always compare less than (and not equal to) unsigned integers: the comparison is safe against lossy integer conversion.
  template< class T, class U >
  constexpr bool cmp_greater( T t, U u ) noexcept { return cmp_less(u, t); }

  ///\brief Compare the values. negative signed integers always compare less than (and not equal to) unsigned integers: the comparison is safe against lossy integer conversion.
  template< class T, class U >
  constexpr bool cmp_less_equal( T t, U u ) noexcept { return !cmp_greater(t, u); }

  ///\brief Compare the values. negative signed integers always compare less than (and not equal to) unsigned integers: the comparison is safe against lossy integer conversion.
  template< class T, class U >
  constexpr bool cmp_greater_equal( T t, U u ) noexcept { return !cmp_less(t, u); }
  
  template<typename _Tp>
  using remove_cvref_t = typename std::remove_cv<typename std::remove_reference<_Tp>::type>::type;
  
  template<typename _Tp>
  struct remove_cvref { using type = remove_cvref_t<_Tp>; };


  template<typename T>
  constexpr int countl_zero(T value ) noexcept
    {
    static_assert(std::is_unsigned_v<T>);
    static_assert(std::is_integral<T>::value && sizeof(T) <= 8);
#if defined(_MSC_VER)
  #if _HAS_CXX20
      return std::countl_zero(value);
  #else
      //msvc c++17 naive loop implementation
      return std::_Countl_zero_fallback(value);
  #endif
#else
    if constexpr (sizeof(T) < 4)
      {
      int lz{ __builtin_clz(value) };
      return lz - 8 * (sizeof(int) - sizeof(T));
      }
    else if constexpr (sizeof(T) == 4)
      return __builtin_clz(value);
    else if constexpr (sizeof(T) == 8)
      {
      if constexpr (sizeof(long) == 4)
        return __builtin_clzll(value);
      else
        return __builtin_clzl(value);
      }
#endif
    }

  static_assert( countl_zero(uint8_t(1)) == 8 - 1 );
  static_assert( countl_zero(uint16_t(1)) == 16 - 1 );
  static_assert(countl_zero(uint32_t{ 1 }) == 32 - 1);
  static_assert( countl_zero(uint32_t{ 2 }) == 32 - 2 );
  static_assert( countl_zero(uint32_t{ 4 }) == 32 - 3 );
  static_assert( countl_zero(uint64_t(4)) == 64 - 3 );

  template<typename T>
  constexpr int countr_zero(T value ) noexcept
    {
    static_assert(std::is_unsigned_v<T>);
#if defined(_MSC_VER)
#if _HAS_CXX20
    return std::countr_zero(value);
#else
    return std::_Countr_zero(value);
#endif
#else
    
    static_assert(std::is_integral<T>::value && sizeof(T)<=8);
    if constexpr( sizeof(T) < 4 )
      {
      int lz{ __builtin_ctz( value ) };
      return lz - 8 * (sizeof(int) - sizeof(T));
      }
    else if constexpr( sizeof(T) == 4 )
      return __builtin_ctz( value );
    else if constexpr( sizeof(T) == 8 )
      {
      if constexpr( sizeof(long) == 4 )
        return __builtin_ctz( value );
      else
        return __builtin_ctz( value );
      }
#endif
    }
  }
