cmake_minimum_required(VERSION 3.23) # Version 3.10 is required for string(JSON ...)

# Read the content of types.h into a variable
file(READ fixed_lib/include/fixedmath/types.h types_h_content)

# Extract the version string
string(REGEX MATCH "FIXEDMATH_VERSION_STRING \"([0-9]+\\.[0-9]+\\.[0-9]+)\"" _ ${types_h_content})
set(fixedmath_version_string ${CMAKE_MATCH_1})

# Split the version string into major, minor, and patch components
string(REPLACE "." ";" fixedmath_version_list ${fixedmath_version_string})
list(GET fixedmath_version_list 0 fixed_math_VERSION_MAJOR)
list(GET fixedmath_version_list 1 fixed_math_VERSION_MINOR)
list(GET fixedmath_version_list 2 fixed_math_VERSION_PATCH)
