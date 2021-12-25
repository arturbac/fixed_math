include(CheckSourceCompiles)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set( CMAKE_REQUIRED_FLAGS -std=c++20)
  check_source_compiles(CXX "int main(void){return 0;}" SUPPORTS_CXX20)
else()
  set(SUPPORTS_CXX20 FALSE)
endif()

set( TEST_DEFINITIONS -DFIXEDMATH_ENABLE_SQRT_ABACUS_ALGO )
function(add_compile_test HEADER_FILE_NAME )
  get_filename_component(TEST_NAME ${HEADER_FILE_NAME} NAME_WE)
  set( SOURCE_FILE_NAME test_${TEST_NAME}.cc )
  
  set( FIXED_MATH_INCLUDES ${PROJECT_SOURCE_DIR}/fixed_lib/include )
  file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME} "#include <fixedmath/unittests/${HEADER_FILE_NAME}.h>\nint main( int argc, char ** argv ) {return fixedmath::${HEADER_FILE_NAME}_unit_tests() ? EXIT_SUCCESS : EXIT_FAILURE; }\n" )
  add_test(NAME ${TEST_NAME}_cxx17 
    COMMAND ${CMAKE_CXX_COMPILER} -std=c++17 ${TEST_DEFINITIONS} -I${FIXED_MATH_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME} -o ${CMAKE_CURRENT_BINARY_DIR}/test_${TEST_NAME}_cxx17.o )
  if( SUPPORTS_CXX20 )
    # using FIXEDMATH_ENABLE_SQRT_ABACUS_ALGO is not required for sqrt with c++20 standard
    add_test(NAME ${TEST_NAME}_cxx20 
      COMMAND ${CMAKE_CXX_COMPILER} -std=c++20 -I${FIXED_MATH_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR}/${SOURCE_FILE_NAME} -o ${CMAKE_CURRENT_BINARY_DIR}/test_${TEST_NAME}_cxx20.o )
  endif()
endfunction()

add_compile_test( type_traits )
add_compile_test( integral_type_convertions )
add_compile_test( floating_point_type_convertions )
add_compile_test( fixed_construction )
add_compile_test( addition )
add_compile_test( substraction )
add_compile_test( multiplication )
add_compile_test( division )
add_compile_test( sqrt )
add_compile_test( misc_functions )
add_compile_test( sin )
add_compile_test( tan )
add_compile_test( atan )

add_executable( hypot_not_abacus hypot_not_abacus.cc )
target_link_libraries( hypot_not_abacus fixed_math )
