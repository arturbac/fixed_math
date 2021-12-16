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
/*
#if defined(_MSC_VER)
static_assert(false, "dont expect constexpr will work on this broken compiler. Expect cl crash and internal compiler error");
#endif*/
//1>D:\projects\fixed_math\fixed_lib\include\fixedmath\unittests\addition.h(19,43): fatal error C1001: Wewnêtrzny b³¹d kompilatora.
//1 > (plik kompilatora „d : \A01\_work\2\s\src\vctools\Compiler\CxxFE\sl\p1\c\constexpr\constexpr.cpp”, wiersz 6887)

#include "type_traits.h"
#include "integral_type_convertions.h"
#include "floating_point_type_convertions.h"
#include "fixed_construction.h"
#include "addition.h"
#include "substraction.h"
#include "multiplication.h"
#include "division.h"
#if defined(FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO)
#include "sqrt.h"
#endif
#include "misc_functions.h"
#include "sin.h"
#include "tan.h"
#include "atan.h"
