
add_library(astrodb-guiqt
  databasedialog.cpp databasedialog.ui
  dbinfodialog.cpp dbinfodialog.ui
)

target_sources(astrodb-guiqt PUBLIC
  FILE_SET HEADERS TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.." FILES
  databasedialog.h
  dbinfodialog.h
)

target_compile_definitions(astrodb-guiqt PRIVATE ${ASTRODB_QT6_DEF})

target_link_libraries(astrodb-guiqt
  Qt::Widgets
  astrodb::astrodb-base
)

set_target_properties(astrodb-guiqt
    PROPERTIES
      VERSION
        ${CMAKE_PROJECT_VERSION}
      SOVERSION
        ${CMAKE_PROJECT_VERSION_MAJOR} #.${CMAKE_PROJECT_VERSION_MINOR}
      DEFINE_SYMBOL
        LIBASTRODB
)


install(TARGETS astrodb-guiqt
  EXPORT astrodb-guiqt
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# pkg-config file
if (UNIX)
  list(JOIN DEPENDENT_LIST " " DEPENDENT_LIBS)
  configure_file(libastrodb-guiqt.pc.in ${CMAKE_CURRENT_BINARY_DIR}/libastrodb-guiqt.pc @ONLY)
  install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/libastrodb-guiqt.pc
    DESTINATION
      ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    COMPONENT
      pkgconfig
  )
endif (UNIX)

# cmake config files
set(config_targets_file "astrodb-guiqtConfigTargets.cmake")
set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/astrodb-guiqtConfigVersion.cmake")
set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/astrodb-guiqt")
set(project_config_in "${CMAKE_CURRENT_LIST_DIR}/astrodb-guiqtConfig.cmake.in")
set(project_config_out "${CMAKE_CURRENT_BINARY_DIR}/astrodb-guiqtConfig.cmake")
export(TARGETS astrodb-guiqt NAMESPACE astrodb::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${config_targets_file}")
install(EXPORT astrodb DESTINATION ${export_dest_dir} NAMESPACE astrodb:: FILE ${config_targets_file})
include(CMakePackageConfigHelpers)
configure_package_config_file("${project_config_in}" "${project_config_out}" INSTALL_DESTINATION ${export_dest_dir})
write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
install(FILES "${project_config_out}" "${version_config_file}" DESTINATION "${export_dest_dir}")


