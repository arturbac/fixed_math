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

#if !defined(SMALL_VECTORS_CXX_UTILITY)
#define SMALL_VECTORS_CXX_UTILITY 1

#include <type_traits>
#include <cstdint>
#include <limits>
#include <memory>
#include <utility>
#if __cplusplus > 201703L
#include <bit>
#include <concepts>
#endif

// on linux depending on system build c++ standard libc++ version has various test macros undefined even for pure constexpr inline functions ..
#if defined(_LIBCPP_STD_VER) && _LIBCPP_STD_VER >= 20
  #if !defined(__cpp_lib_bitops)
    #define cpp_lib_bitops 201907L
  #endif
#endif
namespace cxx20
{
#if defined(__cpp_lib_integer_comparison_functions)
  using std::cmp_equal;
  using std::cmp_not_equal;
  using std::cmp_less;
  using std::cmp_greater;
  using std::cmp_less_equal;
  using std::cmp_greater_equal;
#else
#if !defined(integer_comparison_functions_defiend)
#define integer_comparison_functions_defiend

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
#endif // integer_comparison_functions_defiend
#endif // __cpp_lib_integer_comparison_functions

#if defined(__cpp_lib_bitops) || defined(cpp_lib_bitops)
  using std::countr_zero;
  using std::countl_zero;
#else
  template<typename T>
  constexpr int countl_zero(T value ) noexcept
    {
    static_assert(std::is_unsigned_v<T>);
    static_assert(std::is_integral<T>::value && sizeof(T) <= 8);
#if defined(_MSC_VER)
      //msvc c++17 naive loop implementation
      return std::_Countl_zero_fallback(value);
#else
    constexpr auto number_digits { std::numeric_limits<T>::digits };

    if (value == 0)
      return number_digits;
    else
      {
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
    static_assert(std::is_integral<T>::value && sizeof(T) <= 8);
#if defined(_MSC_VER)
    return std::_Countr_zero(value);
#else
    static_assert(std::is_integral<T>::value && sizeof(T)<=8);
    
    constexpr auto number_digits { std::numeric_limits<T>::digits };

    if (value == 0)
      return number_digits;
    else
      {
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
      }
#endif
    }
#endif //__cpp_lib_bitops

#if defined(__cpp_lib_bit_cast)
    using std::bit_cast;
#else //defined(__cpp_lib_bit_cast)
#if __has_builtin(__builtin_bit_cast)
    
  template <class To, class From>
#if __cplusplus > 201703L
  requires requires(To, From)
      {
      sizeof(To) == sizeof(From);
      requires std::is_trivially_copyable_v<From>;
      requires std::is_trivially_copyable_v<To>;
      }
#endif
  constexpr To bit_cast( From const & src) noexcept
    {
#if __cplusplus <= 201703L
    static_assert(std::is_trivially_copyable_v<From>);
    static_assert(std::is_trivially_copyable_v<To>);
#endif
    return __builtin_bit_cast(To,src);
    }
#endif //__has_builtin(__builtin_bit_cast)
#endif //defined(__cpp_lib_bit_cast)

#if defined(__cpp_lib_assume_aligned)
  using std::assume_aligned;
#else
  template< std::size_t N, class T >
  [[nodiscard]]
  constexpr T* assume_aligned(T* ptr)
  {
  #if __has_builtin(__builtin_assume_aligned)
  #if __cplusplus > 201703L
  if( !std::is_constant_evaluated())
  #endif
    return reinterpret_cast<T *>(__builtin_assume_aligned(ptr,N));
  #if __cplusplus > 201703L
  else
    return ptr;
  #endif
  #else
    return ptr;
  #endif
  }
#endif
  }

namespace cxx23
{
#if defined(__cpp_lib_to_underlying)
  using std::to_underlying;
#else
  template <class T>
  constexpr std::underlying_type_t<T> to_underlying( T value ) noexcept
    { return static_cast<std::underlying_type_t<T>>(value); }
#endif

#if defined(__cpp_lib_byteswap)
  using std::byteswap;
#else
  // -O3 -std=c++20
  //x86_64
  // byteswap(unsigned long):                # @byteswap(unsigned long)
  //         mov     rax, rdi
  //         bswap   rax
  //         ret
  // byteswap(double):                       # @byteswap(double)
  //         movq    rax, xmm0
  //         bswap   rax
  //         movq    xmm0, rax
  //         ret
  //aarch64
  // byteswap(unsigned long):
  //         fmov    d0, x0
  //         rev64   v0.8b, v0.8b
  //         umov    x0, v0.d[0]
  //         ret
  // byteswap(double):
  //         fmov    x0, d0
  //         rev     x0, x0
  //         fmov    d0, x0
  //         ret
  //
  namespace detail
    {
     template<std::size_t sz, int32_t ix>
     struct swap_bytes_impl_t
        {
        [[gnu::always_inline]]
        static inline constexpr void swap( std::byte (&l)[sz] ) noexcept
           {
           swap_bytes_impl_t<sz,ix-1>::swap( l );
           std::swap( l[ix], l[sz-1-ix]);
           }
        };
     template<std::size_t sz>
     struct swap_bytes_impl_t<sz,0>
        {
        [[gnu::always_inline]]
        static inline constexpr void swap( std::byte (&l)[sz] ) noexcept
           {
           std::swap( l[0], l[sz-1]);
           }
        };

    template<std::size_t sz>
    [[gnu::always_inline]]
    inline constexpr void swap_bytes(std::byte (&l)[sz]) noexcept
      {
      swap_bytes_impl_t<sz,sz/2-1>::swap(l);
      }
    
#if __cplusplus > 201703L
      template<typename T>
      concept trivially_copyable = std::is_trivially_copyable_v<T>;
      
      template<typename T>
      concept even_value_size = (sizeof(T) & 1) == 0;

      template<typename value_type>
      concept byte_swap_constraints =
       requires( value_type )
        {
        requires detail::trivially_copyable<value_type>;
        requires detail::even_value_size<value_type>;
        };
#endif
    }

#if __cplusplus > 201703L
  template<detail::byte_swap_constraints value_type>
#else
  template<typename value_type>
#endif
  [[gnu::always_inline,gnu::const]]
  constexpr value_type byteswap( value_type big_or_le ) noexcept
    {
#if __cplusplus <= 201703L
    static_assert(std::is_trivially_copyable_v<value_type>);
    static_assert((sizeof(value_type) & 1) == 0);
#endif
    struct store_type
      {
      alignas(alignof(value_type))
      std::byte data[sizeof(value_type)];
      };

    store_type raw { cxx20::bit_cast<store_type>(big_or_le) };
    detail::swap_bytes(raw.data);
    return cxx20::bit_cast<value_type>(raw);
    }
#endif
}
#endif //SMALL_VECTORS_CXX_UTILITY

