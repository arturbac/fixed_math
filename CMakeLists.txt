cmake_minimum_required(VERSION 3.8 FATAL_ERROR )

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

include(get_fixed_math_version)
get_fixed_math_version(${CMAKE_CURRENT_SOURCE_DIR}/fixed_lib/include/fixedmath/types.h fixed_math_VERSION_MAJOR fixed_math_VERSION_MINOR fixed_math_VERSION_PATCH)

project(fixed_math
        LANGUAGES CXX
        VERSION "${fixed_math_VERSION_MAJOR}.${fixed_math_VERSION_MINOR}.${fixed_math_VERSION_PATCH}" )

message(STATUS "fixed_math VERSION: ${fixed_math_VERSION}")
set(fixed_math_HOMEPAGE_URL "https://github.com/arturbac/fixed_math")
set(fixed_math_DESCRIPTION  "fixed point math library in C++17")

include(FeatureSummary)

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF)

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
option(FIXEDMATH_ENABLE_UNIT_TESTS "unit tests available from CTest" ON )
add_feature_info("FIXEDMATH_ENABLE_UNIT_TESTS" FIXEDMATH_ENABLE_UNIT_TESTS "unit test available from CTest")

option(FIXEDMATH_ENABLE_DEVEL_CODE "enable internaly used for development code" OFF )
add_feature_info("ENABLE_DEVEL_CODE" ENABLE_DEVEL_CODE "enable internaly used for development code")

#-----------------------------------------------------------------------------
# project
#-----------------------------------------------------------------------------

add_subdirectory( fixed_lib )

if(FIXEDMATH_ENABLE_DEVEL_CODE)
  add_subdirectory(table_gen)
  add_subdirectory(perf_test_suite)
endif()

if( FIXEDMATH_ENABLE_UNIT_TESTS )
  enable_testing( TRUE )
  add_subdirectory(unit_tests)
endif()

#-----------------------------------------------------------------------------
# Add clean-all target
#-----------------------------------------------------------------------------
add_custom_target(clean-all
   COMMAND ${CMAKE_BUILD_TOOL} clean
   COMMAND rm -rf ${CMAKE_BINARY_DIR}/
)

feature_summary(WHAT ALL)

