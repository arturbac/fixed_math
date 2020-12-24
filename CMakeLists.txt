cmake_minimum_required(VERSION 3.0)

project(fixed_math)

add_executable(fixed_math main.cpp)

install(TARGETS fixed_math RUNTIME DESTINATION bin)
