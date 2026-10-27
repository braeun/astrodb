
add_library(astrodb-base SHARED
  cameratable.cpp
  database.cpp
  infosnippettable.cpp
  libastrodb-base.pc.in
  objecttable.cpp
  observertable.cpp
  plugin.cpp
  telescopetable.cpp
  data/camera.cpp
  data/infosnippet.cpp
  data/object.cpp
  data/observer.cpp
  data/telescope.cpp
  memory/jsondatabase.cpp
  memory/json.hpp
  memory/json_fwd.hpp
  memory/memorycameratable.h memory/memorycameratable.cpp
  memory/memoryinfosnippettable.h memory/memoryinfosnippettable.cpp
  memory/memoryobjecttable.h memory/memoryobjecttable.cpp
  memory/memoryobservertable.h memory/memoryobservertable.cpp
  memory/memorytelescopetable.h memory/memorytelescopetable.cpp
)

add_library(astrodb::astrodb-base ALIAS astrodb-base)

target_sources(astrodb-base PUBLIC
  FILE_SET HEADERS TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.." FILES
  cameratable.h
  database.h
  infosnippettable.h
  objecttable.h
  observertable.h
  plugin.h
  telescopetable.h
  data/camera.h
  data/infosnippet.h
  data/object.h
  data/observer.h
  data/telescope.h
  memory/jsondatabase.h
)

target_link_libraries(astrodb-base
)

# if (BUILD_SQLITE3_DB)
#   target_sources(astrodb-base PRIVATE
#     sqlite3/sqlite3database.cpp
#   )
#   target_sources(astrodb-base PUBLIC
#     FILE_SET HEADERS TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.." FILES
#     sqlite3/sqlite3database.h
#   )
#   target_link_libraries(astrodb-base PUBLIC SQLite3::SQLite3)
# endif()

set_target_properties(astrodb-base
    PROPERTIES
      VERSION
        ${CMAKE_PROJECT_VERSION}
      SOVERSION
        ${CMAKE_PROJECT_VERSION_MAJOR} #.${CMAKE_PROJECT_VERSION_MINOR}
      DEFINE_SYMBOL
        LIBASTRODB
)


install(TARGETS astrodb-base
  EXPORT astrodb
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# pkg-config file
if (UNIX)
  list(JOIN DEPENDENT_LIST " " DEPENDENT_LIBS)
  configure_file(libastrodb-base.pc.in ${CMAKE_CURRENT_BINARY_DIR}/libastrodb-base.pc @ONLY)
  install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/libastrodb-base.pc
    DESTINATION
      ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    COMPONENT
      pkgconfig
  )
endif (UNIX)

# cmake config files
set(config_targets_file "astrodbConfigTargets.cmake")
set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/astrodbConfigVersion.cmake")
set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/astrodb")
set(project_config_in "${CMAKE_CURRENT_LIST_DIR}/astrodbConfig.cmake.in")
set(project_config_out "${CMAKE_CURRENT_BINARY_DIR}/astrodbConfig.cmake")
export(TARGETS astrodb-base NAMESPACE astrodb::
       FILE "${CMAKE_CURRENT_BINARY_DIR}/${config_targets_file}")
install(EXPORT astrodb DESTINATION ${export_dest_dir} NAMESPACE astrodb:: FILE ${config_targets_file})
include(CMakePackageConfigHelpers)
configure_package_config_file("${project_config_in}" "${project_config_out}" INSTALL_DESTINATION ${export_dest_dir})
write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
install(FILES "${project_config_out}" "${version_config_file}" DESTINATION "${export_dest_dir}")


