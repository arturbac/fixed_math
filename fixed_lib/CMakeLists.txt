

add_library( fixed_math )

target_include_directories( fixed_math 
  PUBLIC 
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}/fixed_math>"
  )
target_sources( fixed_math PRIVATE src/fixed_math.cc )

file(GLOB_RECURSE fixed_math_include_files ${CMAKE_CURRENT_SOURCE_DIR}/include/fixed_math/*.h )

install(TARGETS fixed_math
        EXPORT fixed_math_targets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${fixed_math_include_files}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/fixed_math 
        )

install(EXPORT fixed_math_targets
        FILE fixed_mathTargets.cmake
        NAMESPACE fixed_math::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fixed_math
  )

include(CMakePackageConfigHelpers)
  write_basic_package_version_file(
      "${CMAKE_CURRENT_BINARY_DIR}/fixed_mathConfigVersion.cmake"
      VERSION ${fixed_math_VERSION}
      COMPATIBILITY SameMajorVersion
      )
      
set(ConfigPackageLocation ${CMAKE_INSTALL_LIBDIR}/cmake/fixed_math)

install(FILES
    fixed_mathConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/fixed_mathConfigVersion.cmake"
    DESTINATION ${ConfigPackageLocation}
    )
    
install(FILES
    fixed_mathConfig.cmake
    "${CMAKE_CURRENT_BINARY_DIR}/fixed_mathConfigVersion.cmake"
    DESTINATION ${ConfigPackageLocation}
    )
    
if(FIXEDMATH_ENABLE_DEVEL_CODE)
  add_subdirectory( mca_analisis )
endif()
