

add_library( fixed_math )
target_include_directories( fixed_math PUBLIC include )
target_sources( fixed_math PRIVATE src/fixed_math.cc )

add_subdirectory( mca_analisis )
