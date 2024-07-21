cmake_minimum_required(VERSION 3.21 FATAL_ERROR )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

include(get_fixed_math_version)
include(cmake/CPM.cmake)

project(fixed_math
        LANGUAGES CXX
        VERSION "${fixed_math_VERSION_MAJOR}.${fixed_math_VERSION_MINOR}.${fixed_math_VERSION_PATCH}" )

message(STATUS "fixed_math VERSION: ${fixed_math_VERSION}")
set(fixed_math_HOMEPAGE_URL "https://github.com/arturbac/fixed_math")
set(fixed_math_DESCRIPTION  "fixed point math library in C++20")

include(FeatureSummary)

# Set a default build type if none was specified
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to 'Release' as none was specified.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

#-----------------------------------------------------------------------------
# options
#-----------------------------------------------------------------------------
if(PROJECT_IS_TOP_LEVEL)
  option(FIXEDMATH_ENABLE_UNIT_TESTS "unit tests available from CTest" ON )
  add_feature_info("FIXEDMATH_ENABLE_UNIT_TESTS" FIXEDMATH_ENABLE_UNIT_TESTS "unit test available from CTest")

  option(FIXEDMATH_ENABLE_DEVEL_CODE "enable internaly used for development code" OFF )
  add_feature_info("ENABLE_DEVEL_CODE" ENABLE_DEVEL_CODE "enable internaly used for development code")
endif()
# CMAKE_CXX_STANDARD used for compilation of fixedmath will not affect CMAKE_CXX_STANDARD avaialble when importing library
if(NOT DEFINED CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD LESS 20 )
  message(STATUS "Assuming by default c++17 standard")
  set( CMAKE_CXX_STANDARD 20 )
endif()
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF)

#-----------------------------------------------------------------------------
# project
#-----------------------------------------------------------------------------

add_subdirectory( fixed_lib )

if(FIXEDMATH_ENABLE_DEVEL_CODE)
  add_subdirectory(table_gen)
  add_subdirectory(perf_test_suite)
endif()

if( PROJECT_IS_TOP_LEVEL)
  if( FIXEDMATH_ENABLE_UNIT_TESTS )
      enable_testing( TRUE )
      add_subdirectory(unit_tests)
  endif()
endif()
#-----------------------------------------------------------------------------
# Add clean-all target
#-----------------------------------------------------------------------------
add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND rm -rf ${CMAKE_BINARY_DIR}/
)

if( PROJECT_IS_TOP_LEVEL)
  feature_summary(WHAT ALL)
endif()


#--------
#[[
add_executable(fixed_math_test main.cc)
target_compile_definitions( fixed_math_test PRIVATE -DFIXEDMATH_ENABLE_SQRT_ABACUS_ALGO=1)

target_link_libraries( fixed_math_test 
   fixed_math
   agg_fixed )]]
