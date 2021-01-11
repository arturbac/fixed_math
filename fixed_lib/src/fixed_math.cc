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

#include <fixed_math.hpp>
#include "square_root_table.h"
#include "tan_table.h"
#include <algorithm>
#include <fixedmath/iostream.h>

namespace fixedmath 
{
  
  struct fix_rbit_scan_loop
    {
    constexpr int operator()( uint32_t value ) const
      {
      int cx = 0;             // if no bit set: default %clz = 2n = 0 
      for (int i = 0; i < 32; i++) 
        {
        auto r1 = value << i;
        auto r2 = ( r1 & 0x80000000 );
        if( 0 != r2 )
          {
          cx = 32 - i;
          break;
          }
        }
      return cx;
      }
    };
    
  struct fix_rbit_scan_clz
    {
    constexpr int operator()( uint32_t value ) const
      {
      if( value != 0 )
        {
        int lb { cxx20::countl_zero(value) };
        return 32 - lb;
        }
      return 0;
      }
    };
    
  fixed_t sqrt(fixed_t value) noexcept
    {
    if( fixed_unlikely(value <= 0_fix) ) 
      {
      if( fixed_unlikely(value < 0_fix) )
        return std::numeric_limits<fixed_t>::quiet_NaN();
      return 0_fix;
      }

    int cl = fix_rbit_scan_clz()( static_cast<uint32_t>( value.v >> 6 ) ) & 0xfe; // make result even -->  %cl = 2n
    int index = value.v >> cl;                // shift value to fall into range 1..127
    value = as_fixed( square_root_tab(index) );
    cl >>= 1;
    value.v = value.v << cl;
    return as_fixed(value.v >> 4);
    }

  fixed_t hypot (fixed_t lh, fixed_t rh ) noexcept
    {
    uint64_t u_l = lh.v; 
    uint64_t u_r = rh.v;

    uint64_t sum = u_l * u_l + u_r * u_r;

    if( sum > 0x3fffffffffffull)
      return std::numeric_limits<fixed_t>::quiet_NaN();

    uint32_t hi_sum = static_cast<uint32_t>( sum >> 32 );
    uint32_t lo_sum = static_cast<uint32_t>( sum & 0xffffffffu );

    int clz = fix_rbit_scan_clz()( hi_sum );
    if( clz != 0 )
      {
      clz = (clz + 2) & 0xfe;
      sum = sum >> clz;
      uint32_t lo_index = (sum >> 24) & 0xff;
      lh = as_fixed( square_root_tab(lo_index));

      clz = clz >> 1;
      lh.v = lh.v << clz;
      }
    else 
      {
      lo_sum = lo_sum >> 16;
     
      clz = fix_rbit_scan_clz()( lo_sum >> 6 ) & 0xfe;
      uint32_t lo_index = lo_sum >> clz;
      lh = as_fixed( square_root_tab(lo_index));

      clz = clz >> 1;
      lh.v = lh.v << clz;
      lh.v = lh.v >> 4;
      }

    return lh;
    }
    
  //binary search closest value in tan table
  fixed_t atan( fixed_t value ) noexcept
    {
#if 1
    if( value >= 0_fix )
      {
      auto it { std::lower_bound( std::begin(tan_table__), std::next(std::begin(tan_table__),128), value.v ) };

      fixed_internal index{ std::distance( std::begin(tan_table__), it ) };
      if( index !=0 && (tan_tab(index)-value) >  ( value - tan_tab(index-1) ) )
        index = index -1;
      return as_fixed( fixed_internal(index) << 15);
      }
    else
      {
      auto it { std::lower_bound( std::next(std::begin(tan_table__),128), std::next(std::begin(tan_table__),256), value.v ) };
      fixed_internal index{ std::distance( std::begin(tan_table__), it ) };
      if( index !=0 && (tan_tab(index)-value) >  ( value - tan_tab(index-1) ) )
        index = index -1;
      return -128_fix + as_fixed( fixed_internal(index) << 15);
      }
#else
    uint8_t low_bound, up_bound;

    if( value >= 0_fix )
      {
      low_bound = 0; up_bound = 127;
      }
    else
      {
      low_bound = 128; up_bound = 255;
      }

    uint8_t index;
    fixed_t diff;
    do 
      {
      index = (low_bound + up_bound) >> 1;
      diff = value - as_fixed( tan_tab(index) );

      if (diff > 0_fix)
        low_bound = index + 1;
      else if (diff < 0_fix)
        up_bound = index - 1;
      } 
    while ((low_bound <= up_bound) && (diff != 0_fix));
    std::cout << '[' << int(index) <<  ']' << '(' << as_fixed( tan_tab(index) ) << ')';
    fixed_t const result { as_fixed( fixed_internal(index) << 15) };
    if (value >= 0_fix)
      return result;

    return -128_fix + result;
#endif
    }
}
