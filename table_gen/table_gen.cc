// MIT License
// 
// Copyright (c) 2020 EBASoft Artur Bac
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
#include <fixedmath/iostream.h>
#include <functional>
#include <fstream>
#include <string>
#include <cmath>

using namespace fixedmath;

using limits__ = std::numeric_limits<fixedmath::fixed_t>;
using flimits__ = std::numeric_limits<float>;
using dlimits__ = std::numeric_limits<double>;

using std::endl;

static fixed_t conv( double value )
  {
  return fix_carrier_t( static_cast<fixed_internal>(value * 65536 + (1./16) ) );
  }
  
static void head( std::ostream & out )
  {
  out <<"#pragma once"<< endl;
  out <<"// generated on " << __DATE__ << " " << __TIME__ << endl;
  out <<"#include <fixedmath/types.h>"<< endl << endl;
  out <<"#include <cstdio>"<< endl;
  out <<"#include <array>"<< endl;
  out <<"#include <cstdint>"<< endl;
  out <<"#include <cassert>"<< endl << endl;
  out <<"namespace fixedmath {"<< endl;
  out << endl;
  }
  
static void foot( std::ostream & out )
  {
  out <<"}"<< endl;
  out << endl;
  }
  
static void gen_sqrt_tab()
  {
  std::string filename = OUTPUT_FILE_PATH "/square_root_table.h";
  std::fstream out(filename, out.binary | out.trunc | out.out);
  
  head( out );
  out <<"// square root precalculated values"<< endl;
  out << "static std::array<uint16_t, 256> square_root_table__ {"<< endl;

  out << std::hex << std::showbase << endl;
  for( int16_t i{0}; i != 256 ; i+=1 )
    {
    double fract { static_cast<double>(i) / 256 + 1./(2*8192) + 1./(4*8192) + 1./(8*8192)+ 1./(16*8192) + 1./(32*8192)  };
    fixed_t ftab { conv( sqrt( fract )) };
    uint16_t tabvalue{ static_cast<uint16_t>(ftab.v) };
    out << "  " << tabvalue << " /* sqrt("<< fract<<") ~=" << ftab << "*/";
    if( i != 255 )
      out << ", ";
    if( i != 0 && (i+1) % 2 == 0 )
      out << endl;
    }
  out <<"};"<< endl;
  out << endl;
  out <<"uint16_t square_root_tab( uint8_t index ) noexcept"<< endl;
  out <<"  {" << endl;
  out <<"  return square_root_table__[index];"<< endl;
  out <<"  }"<< endl;
  foot(out);
  }
  
static void gen_tan_tab()
  {
  std::string filename = OUTPUT_FILE_PATH "/tan_table.h";
  std::fstream out(filename, out.binary | out.trunc | out.out);
  
  head( out );
  
  
  out <<"// tangets of half of circle 0 .. 127 precalculated values 0 .. phi/2"<< endl;
  out << "static std::array<fixed_internal, 256> tan_table__ {"<< endl;

  out << std::dec << endl;
  for( int16_t i{0}; i != 256 ; i+=1 )
    {
    double fract { static_cast<double>(i) / 128 * (phi/2)  };
    fixed_t ftab { floating_point_to_fixed( std::tan( fract ) ) };
    fixed_internal tabvalue{ ftab.v };
    out << "  " << tabvalue << "ll /* tan("<< fract<<") ~=" << ftab << "*/";
    if( i != 255 )
      out << ", ";
    if( i != 0 && (i+1) % 2 == 0 )
      out << endl;
    }
  out <<"};"<< endl;
  out << endl;
  out <<"fixed_t tan_tab( uint8_t index ) noexcept"<< endl;
  out <<"  {" << endl;
  out <<"  return as_fixed(tan_table__[index]);"<< endl;
  out <<"  }"<< endl;
  foot(out);
  }
  
static void gen_cos_angle_tab()
  {
  std::string filename = OUTPUT_FILE_PATH "/cos_angle_table.h";
  std::fstream out(filename, out.binary | out.trunc | out.out);
  
  head( out );
  
  
  out <<"// cosine of full circle for input in degrees"<< endl;
  out << "static std::array<fixed_internal, 361> cos_angle_table__ {"<< endl;

  out << std::dec << endl;
  for( int16_t i{0}; i != 361 ; i++ )
    {
    double rad { static_cast<double>(i) * phi / 180.  };
    fixed_t ftab { floating_point_to_fixed( std::cos( rad ) ) };
    fixed_internal tabvalue{ ftab.v };
    out << "  " << tabvalue << "ll /* cos("<< rad <<") ~=" << ftab << "*/";
    if( i != 360 )
      out << ", ";
    if( i != 0 && (i+1) % 2 == 0 )
      out << endl;
    }
  out <<"};"<< endl;
  out << endl;
  out <<"fixed_t cos_angle_tab( uint16_t index ) noexcept"<< endl;
  out <<"  {" << endl;
  out <<"  return as_fixed(cos_angle_table__[index]);"<< endl;
  out <<"  }"<< endl;
  foot(out);
  }
static void gen_sin_angle_tab()
  {
  std::string filename = OUTPUT_FILE_PATH "/sin_angle_table.h";
  std::fstream out(filename, out.binary | out.trunc | out.out);
  
  head( out );
  
  
  out <<"// sine of full circle for input in degrees"<< endl;
  out << "static std::array<fixed_internal, 361> sin_angle_table__ {"<< endl;

  out << std::dec << endl;
  for( int16_t i{0}; i != 361 ; i++ )
    {
    double rad { static_cast<double>(i) * phi / 180.  };
    fixed_t ftab { floating_point_to_fixed( std::sin( rad ) ) };
    fixed_internal tabvalue{ ftab.v };
    out << "  " << tabvalue << "ll /* sin("<< rad <<") ~=" << ftab << "*/";
    if( i != 360 )
      out << ", ";
    if( i != 0 && (i+1) % 2 == 0 )
      out << endl;
    }
  out <<"};"<< endl;
  out << endl;
  out <<"fixed_t sin_angle_tab( uint16_t index ) noexcept"<< endl;
  out <<"  {" << endl;
  out <<"  return as_fixed(sin_angle_table__[index]);"<< endl;
  out <<"  }"<< endl;
  foot(out);
  }
int main(int argc, char **argv) 
{
  gen_sqrt_tab();
  gen_tan_tab();
  gen_cos_angle_tab();
  gen_sin_angle_tab();
}
