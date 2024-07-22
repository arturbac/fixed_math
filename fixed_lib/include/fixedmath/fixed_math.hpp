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

#if defined(_MSC_VER)
__pragma( warning (push) )
__pragma( warning(disable : 5030) ) //unknown attribute
__pragma( warning(disable : 4554) ) //false positive about order of execution >>

#endif
#include "types.h"
#include "limits.h"
#include "math.h"

#if defined(_MSC_VER)
__pragma( warning (pop) )
#endif

namespace fixedmath::inline v2
{
  //representative fractions in fixed and any of sum of them
  // 1      1<<0   0.0000152587890625
  // 2      1<<1   0.0000305175781250
  // 4      1<<2   0.0000610351562500
  // 8      1<<3   0.0001220703125000
  // 16     1<<4   0.0002441406250000
  // 32     1<<5   0.0004882812500000
  // 64     1<<6   0.0009765625000000
  // 128    1<<7   0.0019531250000000
  // 256    1<<8   0.0039062500000000
  // 512    1<<9   0.0078125000000000
  // 1024   1<<10  0.0156250000000000
  // 2048   1<<11  0.0312500000000000
  // 4096   1<<12  0.0625000000000000
  // 8192   1<<13  0.1250000000000000
  // 16384  1<<14  0.2500000000000000
  // 32768  1<<15  0.5000000000000000
  
}
