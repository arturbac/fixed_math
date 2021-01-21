cmake_minimum_required(VERSION 3.0)

project(fixed_math)

set( CMAKE_CXX_STANDARD 17 )

add_subdirectory( fixed_lib )
add_subdirectory(perf_test_suite)
