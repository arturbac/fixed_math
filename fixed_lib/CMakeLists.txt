

add_library( fixed_math INTERFACE )
target_compile_features( fixed_math INTERFACE cxx_std_23 )
target_include_directories( fixed_math 
  INTERFACE 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:$<INSTALL_PREFIX>/include>"
  )

file(GLOB fixed_math_include_files
  ${CMAKE_CURRENT_SOURCE_DIR}/include/fixedmath/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/fixedmath/*.hpp
  )

file(GLOB fixed_math_include_files_detail 
  ${CMAKE_CURRENT_SOURCE_DIR}/include/fixedmath/detail/*.h
  )

install(TARGETS fixed_math
        EXPORT fixed_math_targets
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${fixed_math_include_files}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fixed_math 
        )
install(FILES ${fixed_math_include_files_detail}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fixed_math/detail
        )

set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/fixed_math)

install(EXPORT fixed_math_targets
        FILE fixed_mathTargets.cmake
        NAMESPACE fixed_math::
        DESTINATION ${ConfigPackageLocation}
  )

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/fixed_mathConfigVersion.cmake"
    VERSION ${fixed_math_VERSION}
    COMPATIBILITY SameMajorVersion
    )
    
install(FILES
    fixed_mathConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/fixed_mathConfigVersion.cmake"
    DESTINATION ${ConfigPackageLocation}
    )
    
if(FIXEDMATH_ENABLE_DEVEL_CODE)
  add_subdirectory( mca_analisis )
endif()
