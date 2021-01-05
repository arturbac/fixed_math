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
#ifndef PRAGMAS_H
#define PRAGMAS_H
//
// Macros with compiler name [gcc,msvc] are recognised on specified compiler only
// For gcc compatiblity read explanation at bottom of file
//
// ATTRIBUTE_GCC(a)
// ATTRIBUTE_ALIGN(a)
// ATTRIBUTE_GCC_ALIGN(a)
// ATTRIBUTE_MSC_ALIGN(a)
// ATTRIBUTE_EXPORT, DLL_EXPORT ,DLL_IMPORT
//
// Please note that aligment should be declared as below:
// struct ATTRIBUTE_ALIGN( n ) struct_name {};
//
// PRAGMA_GCC_PACK_PUSH( n )
// PRAGMA_GCC_PACK_POP
// PRAGMA_MSC_PACK_PUSH( n )
// PRAGMA_MSC_PACK_POP
// PRAGMA_PACK_PUSH( n )
// PRAGMA_PACK_POP
//
// PRAGMA_GCC_WARNING_PUSH - gcc 4.6+
// PRAGMA_GCC_WARNING_POP  - gcc 4.6+
// PRAGMA_GCC_WARNING_OFF(-Wwarning_name) - gcc 4.2+
// PRAGMA_GCC_WARNING_ON(-Wwarning_name) - gcc 4.2+
// PRAGMA_GCC_WARNING_PUSH_OFF - gcc 4.6+ (works as PUSH + OFF needs POP)
// PRAGMA_MSC_WARNING_PUSH
// PRAGMA_MSC_WARNING_POP
// PRAGMA_MSC_WARNING_OFF( id )
// PRAGMA_MSC_WARNING_SUPPRESS( id )
// PRAGMA_MSC_WARNING_DEFAULT( id )
//
// TODO(x) - msvc, gcc 4.4+
// MESSAGE(x) - msvc, gcc 4.4+
// WARNING(x) - msvc, gcc 4.4+
//
// PRAGMA_WARNING_PUSH - msvc, gcc 4.6+
// PRAGMA_WARNING_POP  - msvc, gcc 4.6+
//
// PUSH_MACRO(macro_name) - msvc, gcc 4.4+ macro_name as string "" to avoid substituting by preprocessor definitions
// POP_MACRO(macro_name) - msvc, gcc 4.4+ macro_name as string "" to avoid substituting by preprocessor definitions
// HAVE_PUSH_POP_MACRO 1/0 - can be used to proper handle lack of PUSH/POP_MACRO
//
// exmample code

/*
#ifdef new
	#if HAVE_PUSH_POP_MACRO
			PUSH_MACRO("new")
			#undef new
	#else
			#error "Macro new is defined and wiil cause syntax errors with placment new here, this file must be build with new undefined"
	#endif
	#define NEED_POP_MACRO_NEW 1
#else
	#define NEED_POP_MACRO_NEW 0
#endif

//Code with placment new
node = new(tmp_) tree_node_type( null,null, alphabet.front() );

#if NEED_POP_MACRO_NEW
			POP_MACRO("new")
#endif
#undef NEED_POP_MACRO_NEW
*/
#if !defined(DEPRECATED)
#if __cplusplus >= 201400L
  #define DEPRECATED(msg) [[deprecated(msg)]]
#else
  #if defined(__GNUC__)
    #define DEPRECATED(a) __attribute__((__deprecated__))
  #elif defined(_MSC_VER)
    #define DEPRECATED(a) __declspec( deprecated(a))
  #else
    #define DEPRECATED(msg)
  #endif
#endif
#endif

#if defined _WIN32 || defined __CYGWIN__

    #ifdef __GNUC__
      #define ATTRIBUTE_EXPORT __attribute__ ((dllexport))
      #define DLL_IMPORT __attribute__ ((dllimport))
    #else
      #define ATTRIBUTE_EXPORT __declspec(dllexport)
      #define DLL_IMPORT __declspec(dllimport)
    #endif
    #define DLL_LOCAL_DEF
#else
    #define ATTRIBUTE_EXPORT __attribute__ ((visibility ("default")))
    #define DLL_IMPORT __attribute__ ((visibility ("default")))
    #define DLL_LOCAL_DEF  __attribute__ ((visibility ("hidden")))
#endif
#define DLL_EXPORT ATTRIBUTE_EXPORT

#ifndef AQURAT_EQUOTEME
  #define AQURAT_QUOTEME(x) #x
  #define AQURAT_EQUOTEME(x) AQURAT_QUOTEME(x)
#endif

#if defined(_MSC_VER)

	// http://msdn.microsoft.com/en-us/library/aa273913(v=VS.60).aspx
	#define PRAGMA_MSC_PACK_PUSH( n ) __pragma( pack ( push, n ) )
	#define PRAGMA_MSC_PACK_POP __pragma( pack ( pop ) )
	#define PRAGMA_PACK_PUSH( n ) PRAGMA_MSC_PACK_PUSH( n )
	#define PRAGMA_PACK_POP PRAGMA_MSC_PACK_POP
	#define ATTRIBUTE_MSC_ALIGN(a) __declspec(align(a))
	#define ATTRIBUTE_ALIGN(a) ATTRIBUTE_MSC_ALIGN(a)
	
	#define PRAGMA_MSC_WARNING_PUSH __pragma( warning (push) )
	#define PRAGMA_MSC_WARNING_POP __pragma( warning (pop) )
	#define PRAGMA_MSC_WARNING_OFF( id ) __pragma( warning(disable : id) ) 
	#define PRAGMA_MSC_WARNING_DEFAULT( id ) __pragma( warning(default : id) )
	#define PRAGMA_MSC_WARNING_SUPPRESS( id ) __pragma( warning (suppress : id) )
	#define PRAGMA_WARNING_PUSH PRAGMA_MSC_WARNING_PUSH
	#define PRAGMA_WARNING_POP PRAGMA_MSC_WARNING_POP

  #if !defined(DISABLE_TODO)
		#define TODO(x) __pragma(message (__FILE__ "(" AQURAT_EQUOTEME(__LINE__)") : TODO: " x))
	#else
		#define TODO(x)
	#endif
	#define WARNING(x) __pragma(message (__FILE__ "(" AQURAT_EQUOTEME(__LINE__) ") : WARNING: " x))
	#if !defined(DISABLE_MESSAGES)
		#define MESSAGE(x) __pragma(message("INFO: " x))
	#else
		#define MESSAGE(x) 
	#endif
	
  #if _MSC_VER >= 1400
		#define PUSH_MACRO(x) __pragma( push_macro (x) )
		#define POP_MACRO(x) __pragma( pop_macro (x) )
		#define HAVE_PUSH_POP_MACRO 1
	#else
		#define PUSH_MACRO(x) 
		#define POP_MACRO(x) 
		#define HAVE_PUSH_POP_MACRO 0
	#endif

#else

  #define PRAGMA_MSC_PACK_PUSH( n )
	#define PRAGMA_MSC_PACK_POP
	#define PRAGMA_MSC_WARNING_PUSH
	#define PRAGMA_MSC_WARNING_POP
	#define PRAGMA_MSC_WARNING_OFF( id )
	#define PRAGMA_MSC_WARNING_SUPPRESS( id )
	#define ATTRIBUTE_MSC_ALIGN(a)

#endif

//
// GCC support pragmas as follow
// 4.0 ---
// 4.2 diagnostic[ warning error ignored]
// 4.3 diagnostic[ warning error ignored]
// 4.4 diagnostic[ warning error ignored]          push_macro(X) pop_macro(X) message
// 4.5 diagnostic[ warning error ignored]          push_macro(X) pop_macro(X) message
// 4.6 diagnostic[ warning error ignored push pop] push_macro(X) pop_macro(X) message

// On different platforms there are used different versions of gcc

// Android NDK, Revision 1 gcc-4.2.1
// Android NDK, Revision 2 
// Android NDK, Revision 3 gcc-4.4.0 
// Android NDK, Revision 4b 
// Android NDK, Revision 5 gcc-4.4.3
// Android NDK, Revision 5b
// Android NDK, Revision 6 gcc-4.4.3
// Android NDK, Revision 7 
// Bada 1.0 gcc-4.4.1
// Bada 1.2 gcc-4.4.1
// Bada 2.0 gcc-4.5.3

// Bada supports allways a diagnostic[ warning error ignored] push_macro(X) pop_macro(X) message
// Android supports allways only diagnostic[ warning error ignored]

// With gcc 4.0 up to gcc 4.1 definitions will issue an error.
// With gcc 4.2 up to gcc 4.3 definitions will issue an warning about lack 
// of macro push_macro(X) pop_macro(X) and diagnostic push pop.
// With gcc 4.4 up to gcc 4.5 definitions will issue an warning about lack of diagnostic push pop.
// With -DPRAGMA_GCC_WARNING_ON_DISABLE will remove any use of PRAGMA_GCC_WARNING_ON(name) statments from preprocessed code
// With -DPRAGMA_GCC_WARNING_OFF_DISABLE will remove any use of PRAGMA_GCC_WARNING_OFF(name) statments from preprocessed code
// With -DPRAGMA_GCC_WARNING_AS_ERROR_DISABLE will remove any use of PRAGMA_GCC_WARNING_AS_ERROR(name) statments from preprocessed code
//
// Belows macros were tested on kubuntu linux and freebsd9 with gcc 4.2, 4.4, 4.5, 4.6 

// Bear in mind that not all pragmas can be switched to errors or controled.
// From manual:
// Modifies the disposition of a diagnostic. Note that not all diagnostics are modifiable; 
// at the moment only warnings (normally controlled by `-W...') can be controlled, and not all of them.
// gcc42 requires also to put all macro definitions of diagnostics outside functions.
#if defined(__clang__)
  #pragma clang diagnostic ignored "-Wunused-parameter"
  
  #define CLANG_DO_PRAGMA(x) _Pragma (#x)
  #define GCC_DO_PRAGMA(x) _Pragma (#x)
  #define PRAGMA_CLANG_WARNING_OFF(name)    CLANG_DO_PRAGMA(clang diagnostic ignored #name)
  #define PRAGMA_CLANG_WARNING_ON(name)     CLANG_DO_PRAGMA(clang diagnostic warning #name)
  #if !defined(DISABLE_TODO)
    #define TODO(x) CLANG_DO_PRAGMA( message ( "TODO: " x) )
  #else
    #define TODO(x)
  #endif
  #define WARNING(x) CLANG_DO_PRAGMA( message ( "WARNING - "  x) )
  #if !defined(DISABLE_MESSAGES)
    #define MESSAGE(x) CLANG_DO_PRAGMA( message ( "INFO: " x) )
  #else
    #define MESSAGE(x)
  #endif
  #define PUSH_MACRO(x) CLANG_DO_PRAGMA( push_macro ( #x ) )
  #define POP_MACRO(x) CLANG_DO_PRAGMA( pop_macro ( #x ) )
  #define HAVE_PUSH_POP_MACRO 1  
  #define PRAGMA_CLANG_WARNING_PUSH CLANG_DO_PRAGMA(clang diagnostic push)
  #define PRAGMA_CLANG_WARNING_POP CLANG_DO_PRAGMA(clang diagnostic pop)
  #define PRAGMA_CLANG_WARNING_PUSH_OFF(name) PRAGMA_CLANG_WARNING_PUSH PRAGMA_CLANG_WARNING_OFF(name)
  #define PRAGMA_WARNING_PUSH PRAGMA_CLANG_WARNING_PUSH
  #define PRAGMA_WARNING_POP PRAGMA_CLANG_WARNING_POP
  #define PRAGMA_WARNING_PUSH_OFF(name) PRAGMA_CLANG_WARNING_PUSH_OFF(name)
  #define ATTRIBUTE_GCC(...) __attribute__((__VA_ARGS__))
  #define restrict __restrict__ 
  #define attribute_gcc __attribute__
  #define ATTRIBUTE_CLANG_ALIGN(a) __attribute__((aligned(a)))
  #define ATTRIBUTE_GCC_ALIGN(a) ATTRIBUTE_CLANG_ALIGN(a)
  #define ATTRIBUTE_ALIGN(a) ATTRIBUTE_GCC_ALIGN(a)
  #define PRAGMA_CLANG_PACK_PUSH( n ) CLANG_DO_PRAGMA( pack ( push, n ) )
  #define PRAGMA_CLANG_PACK_POP CLANG_DO_PRAGMA( pack ( pop ) )

  #define PRAGMA_PACK_PUSH( n ) PRAGMA_CLANG_PACK_PUSH( n )
  #define PRAGMA_PACK_POP PRAGMA_CLANG_PACK_POP
  #if __cplusplus >= 201103L && defined(__has_warning)
  #  if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
  #    define ATTRIBUTE_FALLTHROUGH [[clang::fallthrough]]
  #  endif
  #endif
  #if !defined(ATTRIBUTE_FALLTHROUGH)
   #define ATTRIBUTE_FALLTHROUGH
  #endif
#else
  #define PRAGMA_CLANG_WARNING_PUSH 
  #define PRAGMA_CLANG_WARNING_POP
  #define PRAGMA_CLANG_WARNING_ON(name)
  #define PRAGMA_CLANG_WARNING_OFF(name)
  #define PRAGMA_CLANG_WARNING_PUSH_OFF(name)
#endif

#if defined(__GNUC__) && !defined(__clang__)
	#define GCC_DO_PRAGMA(x) _Pragma (#x)
	
	#define ATTRIBUTE_GCC(...) __attribute__((__VA_ARGS__))
  #define restrict __restrict__ 
  #define attribute_gcc __attribute__
  
	//http://gcc.gnu.org/onlinedocs/gcc-4.2.4/gcc/Structure_002dPacking-Pragmas.html#Structure_002dPacking-Pragmas

	#define PRAGMA_GCC_PACK_PUSH( n ) GCC_DO_PRAGMA( pack ( push, n ) )
	#define PRAGMA_GCC_PACK_POP GCC_DO_PRAGMA( pack ( pop ) )

	#define PRAGMA_PACK_PUSH( n ) PRAGMA_GCC_PACK_PUSH( n )
	#define PRAGMA_PACK_POP PRAGMA_GCC_PACK_POP

	#define ATTRIBUTE_GCC_ALIGN(a) __attribute__((aligned(a)))
	#define ATTRIBUTE_ALIGN(a) ATTRIBUTE_GCC_ALIGN(a)
	
	#if __GNUC__ >= 5 || __GNUC__ >= 4 && __GNUC_MINOR__ >= 2 
	
		//diagnostic[ warning error ignored]	
		#define PRAGMA_GCC_WARNING_OFF(name) 		GCC_DO_PRAGMA(GCC diagnostic ignored #name)
		#define PRAGMA_GCC_WARNING_ON(name) 		GCC_DO_PRAGMA(GCC diagnostic warning #name)

		#if __GNUC__ >= 5 || __GNUC_MINOR__ >= 4 
			#if !defined(DISABLE_TODO)
				#define TODO(x) GCC_DO_PRAGMA( message ( "TODO: " x) )
			#else
				#define TODO(x)
			#endif
			#define WARNING(x) GCC_DO_PRAGMA( message ( "WARNING: " x) )
			#if !defined(DISABLE_MESSAGES)
				#define MESSAGE(x) GCC_DO_PRAGMA( message ( "INFO: " x) )
			#else
				#define MESSAGE(x)
			#endif
			#define PUSH_MACRO(x) GCC_DO_PRAGMA( push_macro (x) )
			#define POP_MACRO(x) GCC_DO_PRAGMA( pop_macro (x) )
			#define HAVE_PUSH_POP_MACRO 1

			#if __GNUC__ >= 5 || __GNUC_MINOR__ >= 6 || __clang__
				#define PRAGMA_GCC_WARNING_PUSH GCC_DO_PRAGMA(GCC diagnostic push)
				#define PRAGMA_GCC_WARNING_POP GCC_DO_PRAGMA(GCC diagnostic pop)
			#endif
		#elif !defined(__clang__)
			// 4 > __GNUC_MINOR__ >= 2
			#define TODO(x)
			#define WARNING(x)
			#define MESSAGE(x)
			
			#define PUSH_MACRO(name) GCC_DO_PRAGMA( message ( "PUSH_MACRO is not implemented in your gcc" ) )
			#define POP_MACRO(name) GCC_DO_PRAGMA( message ( "POP_MACRO is not implemented in your gcc" ) )
			#define HAVE_PUSH_POP_MACRO 0
		#endif

		#if __GNUC_MINOR__ < 6 && __GNUC__ < 5 && !defined( __clang__)
      #define PRAGMA_GCC_WARNING_PUSH GCC_DO_PRAGMA( message ( "PRAGMA_WARNING_PUSH is not implemented in your gcc" ) )
      #define PRAGMA_GCC_WARNING_POP GCC_DO_PRAGMA( message ( "PRAGMA_WARNING_POP is not implemented in your gcc" ) )
		#endif
					
		#if defined( PRAGMA_GCC_WARNING_ON_DISABLE )
			#undef PRAGMA_GCC_WARNING_ON
			#define PRAGMA_GCC_WARNING_ON(name)
		#endif
		#if defined( PRAGMA_GCC_WARNING_OFF_DISABLE )
			#undef PRAGMA_GCC_WARNING_OFF
			#define PRAGMA_GCC_WARNING_OFF(name)
		#endif

  #else
		#error "Your Toolchain is too old, pragmas will not work at all"	
	#endif

	#define PRAGMA_GCC_WARNING_PUSH_OFF(name) PRAGMA_GCC_WARNING_PUSH PRAGMA_GCC_WARNING_OFF(name)
	#define PRAGMA_WARNING_PUSH PRAGMA_GCC_WARNING_PUSH
	#define PRAGMA_WARNING_POP PRAGMA_GCC_WARNING_POP						
  #define ATTRIBUTE_FALLTHROUGH __attribute__ ((fallthrough))

#else
  #if !defined(__clang__)
    #define ATTRIBUTE_GCC(...)
    #define restrict
    #define attribute_gcc(...)
    #define ATTRIBUTE_GCC_ALIGN(a)
    #define PRAGMA_GCC_PACK_PUSH( n ) 
    #define PRAGMA_GCC_PACK_POP
    #define ATTRIBUTE_FALLTHROUGH
  #endif
	#define PRAGMA_GCC_WARNING_PUSH
	#define PRAGMA_GCC_WARNING_POP
	#define PRAGMA_GCC_WARNING_ON(name)
	#define PRAGMA_GCC_WARNING_OFF(name)
	#define PRAGMA_GCC_WARNING_PUSH_OFF(name)
#endif

// Emample code
/*
#include <cstdio>
#warning "starting test"
#pragma message "starting test"

PRAGMA_GCC_WARNING_PUSH
PRAGMA_GCC_WARNING_ON(-Wunknown-pragmas)
#pragma region o---unknown pragma---o

PRAGMA_GCC_WARNING_POP
PRAGMA_GCC_WARNING_OFF(-Wunknown-pragmas)
#pragma region o---unknown pragma---o

PRAGMA_GCC_WARNING_ON(-Wunused-variable)
PRAGMA_GCC_WARNING_ON(-Wuninitialized)
void other2 ()
{
	int a, b;
	b = 10;
	printf("%d", a);	
}

#if __GNUC_MINOR__ < 6
PRAGMA_GCC_WARNING_OFF(-Wunused-variable)
#else
PRAGMA_GCC_WARNING_OFF(-Wunused-but-set-variable)
#endif
PRAGMA_GCC_WARNING_OFF(-Wuninitialized)

int main(int argc, char ** argv)
{
	int a, b;
	b=10;
	printf("%d", a);
	return 0;
}
#if __GNUC_MINOR__ < 6
PRAGMA_GCC_WARNING_ON(-Wunused-variable)
#else
PRAGMA_GCC_WARNING_ON(-Wunused-but-set-variable)
#endif
PRAGMA_GCC_WARNING_ON(-Wuninitialized)
void other ()
{
	int a, b;
	b = 10;
	printf("%d", a);	
}
*/

#endif // PRAGMAS_H
