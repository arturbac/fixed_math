include(CheckSourceCompiles)
#----------------------------------------------------------------
# boost-ext/ut
#----------------------------------------------------------------
CPMAddPackage(
  ut
  GITHUB_REPOSITORY arturbac/ut-ext
  GIT_TAG        v2.0.1_5
)
find_package(ut-ext REQUIRED)

add_library( fixedmath_ut_core INTERFACE )

target_link_libraries( fixedmath_ut_core
  INTERFACE
    fixed_math
    Boost::ut
    )
target_include_directories( fixedmath_ut_core INTERFACE include )

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
  target_compile_options(fixedmath_ut_core
    INTERFACE
      -Wno-disabled-macro-expansion
      -Wno-used-but-marked-unused
      -Wno-global-constructors
      -Wno-exit-time-destructors
      -Wno-ctad-maybe-unsupported
      -Wno-weak-vtables
      -fconstexpr-backtrace-limit=0
      -Wno-misleading-indentation
      )
endif()
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(fixedmath_ut_core
    INTERFACE
      -Wno-misleading-indentation
      -Wno-attributes
      -Wno-unused-parameter
      )
endif()
add_custom_target( unit_tests )

function( add_fixedmath_ut name )
  add_executable(${name})
  target_sources(${name} PRIVATE ${name}.cc)
  target_link_libraries( ${name} PRIVATE fixedmath_ut_core )

  add_dependencies(unit_tests ${name} )
  add_test( NAME ${name}_test COMMAND ${name} )
endfunction()

add_fixedmath_ut( fixed_construction_ut )
add_fixedmath_ut( type_convertions_ut )
add_fixedmath_ut( addition_ut )
add_fixedmath_ut( subtraction_ut )
add_fixedmath_ut( sqrt_ut )
add_fixedmath_ut( multiplication_ut )
add_fixedmath_ut( division_ut )
add_fixedmath_ut( misc_functions_ut )
add_fixedmath_ut( sin_cos_ut )
# add_compile_test( tan )
# add_compile_test( atan )

