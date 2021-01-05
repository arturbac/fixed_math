add_executable(table_gen table_gen.cc)

install(TARGETS table_gen RUNTIME DESTINATION bin)

#target_link_libraries( table_gen 
   #fixed_math )
target_include_directories( table_gen PRIVATE
  $<TARGET_PROPERTY:fixed_math,INCLUDE_DIRECTORIES> 
  )

target_compile_definitions( table_gen PRIVATE -DOUTPUT_FILE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/../fixed_lib/src" )
