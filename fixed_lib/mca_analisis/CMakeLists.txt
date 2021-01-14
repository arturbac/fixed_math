#clang -target aarch64-unknown-linux-gnu -march=armv8a -std=c++17 -O3 -ffast-math -S sin.cc -o - | llvm-mca --iterations=1 --bottleneck-analysis -march=aarch64 -mcpu=cortex-a72 > sin.txt
set( CLANG_ARGS -target aarch64-unknown-linux-gnu -march=armv8a -std=c++17 -O3 -ffast-math -S )
set( MCA_ARGS --iterations=1 --bottleneck-analysis -march=aarch64 -mcpu=cortex-a72 )

macro( mca_target SOURCE_FILE )
  get_filename_component(source_file_no_ext ${SOURCE_FILE} NAME_WE)
add_custom_target(
  maca_${source_file_no_ext}
  COMMAND clang ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE} ${CLANG_ARGS} -o ${CMAKE_CURRENT_SOURCE_DIR}/${source_file_no_ext}.s
  COMMAND llvm-mca ${MCA_ARGS} -o=${CMAKE_CURRENT_SOURCE_DIR}/${source_file_no_ext}.txt  ${CMAKE_CURRENT_SOURCE_DIR}/${source_file_no_ext}.s 
  VERBATIM
)
endmacro()

mca_target( sin.cc )
mca_target( tan.cc )
mca_target( asin.cc )
mca_target( atan.cc )
mca_target( sqrt.cc )
