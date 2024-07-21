include(CheckSourceCompiles)

#----------------------------------------------------------------
# small_vectors
#----------------------------------------------------------------
CPMAddPackage(
  small_vectors
  GITHUB_REPOSITORY arturbac/small_vectors
  GIT_TAG        v3.1.0
  )
find_package(small_vectors REQUIRED)
#----------------------------------------------------------------
# stralgo
#----------------------------------------------------------------
CPMAddPackage(
  stralgo
  GITHUB_REPOSITORY arturbac/stralgo
  GIT_TAG        v1.2.0
  OPTIONS "STRALGO_ENABLE_UNIT_TESTS=OFF"
  )
find_package(stralgo REQUIRED)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set( CMAKE_REQUIRED_FLAGS -std=c++23)
  check_source_compiles(CXX "int main(void){return 0;}" SUPPORTS_CXX23)
else()
  set(SUPPORTS_CXX23 FALSE)
endif()

set( TEST_DEFINITIONS -DFIXEDMATH_ENABLE_SQRT_ABACUS_ALGO )
function(add_compile_test HEADER_FILE_NAME )
  get_filename_component(TEST_NAME ${HEADER_FILE_NAME} NAME_WE)
  set( SOURCE_FILE_NAME test_${TEST_NAME}.cc )
  
  set( FIXED_MATH_INCLUDES ${PROJECT_SOURCE_DIR}/fixed_lib/include )
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME} "#include <fixedmath/unittests/${HEADER_FILE_NAME}.h>\nint main( int argc, char ** argv ) {return fixedmath::${HEADER_FILE_NAME}_unit_tests() ? EXIT_SUCCESS : EXIT_FAILURE; }\n" )

  # using FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO is not required for sqrt with c++20 standard
  add_test(NAME ${TEST_NAME}_cxx20 
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 -I${FIXED_MATH_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME} -o ${CMAKE_CURRENT_BINARY_DIR}/test_${TEST_NAME}_cxx20.o )

  if( SUPPORTS_CXX20 )
    add_test(NAME ${TEST_NAME}_cxx23 
      COMMAND ${CMAKE_CXX_COMPILER} -std=c++23 -I${FIXED_MATH_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME} -o ${CMAKE_CURRENT_BINARY_DIR}/test_${TEST_NAME}_cxx2b.o )
  endif()
  if(FIXEDMATH_ENABLE_DEVEL_CODE)
    add_executable( ${TEST_NAME}_DEVEL ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME})
    target_link_libraries( ${TEST_NAME}_DEVEL PRIVATE fixed_math )
  endif()
endfunction()

add_compile_test( type_traits )
add_compile_test( integral_type_convertions )
add_compile_test( floating_point_type_convertions )
add_compile_test( fixed_construction )
# add_compile_test( addition )
# add_compile_test( substraction )
# add_compile_test( multiplication )
# add_compile_test( division )
# add_compile_test( sqrt )
# add_compile_test( misc_functions )
# add_compile_test( sin )
# add_compile_test( tan )
# add_compile_test( atan )

add_executable( hypot_not_abacus hypot_not_abacus.cc )
target_link_libraries( hypot_not_abacus fixed_math )

add_executable( tests tests.cc )
target_link_libraries( tests fixed_math stralgo::stralgo )
