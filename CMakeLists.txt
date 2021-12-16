cmake_minimum_required(VERSION 3.0)

project(fixed_math LANGUAGES CXX )

include(FeatureSummary)

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF)

option(ENABLE_UNIT_TESTS "Enable unit tests available from CTest" ON )

add_feature_info("ENABLE_UNIT_TESTS" ENABLE_UNIT_TESTS "Enable unit test available from CTest")

add_subdirectory( fixed_lib )
#add_subdirectory(table_gen)
add_subdirectory(perf_test_suite)

if( ENABLE_UNIT_TESTS )
  enable_testing( TRUE )
  add_subdirectory(unit_tests)
endif()

feature_summary(WHAT ALL)

