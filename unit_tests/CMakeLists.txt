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

# set( TEST_DEFINITIONS -DFIXEDMATH_ENABLE_SQRT_ABACUS_ALGO )
# function(add_compile_test HEADER_FILE_NAME )
#   get_filename_component(TEST_NAME ${HEADER_FILE_NAME} NAME_WE)
#   set( SOURCE_FILE_NAME test_${TEST_NAME}.cc )
#   
#   set( FIXED_MATH_INCLUDES ${PROJECT_SOURCE_DIR}/fixed_lib/include )
#   file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME} "#include <fixedmath/unittests/${HEADER_FILE_NAME}.h>\nint main( int argc, char ** argv ) {return fixedmath::${HEADER_FILE_NAME}_unit_tests() ? EXIT_SUCCESS : EXIT_FAILURE; }\n" )
# 
#     add_test(NAME ${TEST_NAME}_cxx23 
#       COMMAND ${CMAKE_CXX_COMPILER} -std=c++23 -I${FIXED_MATH_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME} -o ${CMAKE_CURRENT_BINARY_DIR}/test_${TEST_NAME}_cxx2b.o )
#   
#   if(FIXEDMATH_ENABLE_DEVEL_CODE)
#     add_executable( ${TEST_NAME}_DEVEL ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME})
#     target_link_libraries( ${TEST_NAME}_DEVEL PRIVATE fixed_math )
#   endif()
# endfunction()

# add_fixedmath_ut( type_traits )
add_fixedmath_ut( integral_type_convertions_ut )
# add_compile_test( floating_point_type_convertions )
# add_compile_test( fixed_construction )
# add_compile_test( addition )
# add_compile_test( substraction )
# add_compile_test( multiplication )
# add_compile_test( division )
# add_compile_test( sqrt )
# add_compile_test( misc_functions )
# add_compile_test( sin )
# add_compile_test( tan )
# add_compile_test( atan )

# add_executable( hypot_not_abacus hypot_not_abacus.cc )
# target_link_libraries( hypot_not_abacus fixed_math )

# add_executable( tests tests.cc )
# target_link_libraries( tests fixed_math stralgo::stralgo )
