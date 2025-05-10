add_executable(brief-usage EXCLUDE_FROM_ALL)
target_sources(brief-usage PRIVATE brief-usage.cc)
target_link_libraries(brief-usage PRIVATE fixed_math )

add_executable(iostream EXCLUDE_FROM_ALL)
target_sources(iostream PRIVATE iostream.cc)
target_link_libraries(iostream PRIVATE fixed_math )

add_executable(string_conversion EXCLUDE_FROM_ALL)
target_sources(string_conversion PRIVATE string_conversion.cc)
target_link_libraries(string_conversion PRIVATE fixed_math )

