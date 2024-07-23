add_executable(brief-usage EXCLUDE_FROM_ALL)
target_sources(brief-usage PRIVATE brief-usage.cc)
target_link_libraries(brief-usage PRIVATE fixed_math )

