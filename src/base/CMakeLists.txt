
add_library(astrodb-base SHARED
  cameratable.cpp
  database.cpp
  libastrodb-base.pc.in
  objecttable.cpp
  observertable.cpp
  telescopetable.cpp
  data/camera.cpp
  data/object.cpp
  data/observer.cpp
  data/telescope.cpp
  json/jsoncameratable.h json/jsoncameratable.cpp
  json/jsondatabase.cpp
  json/json.hpp
  json/json_fwd.hpp
  json/jsonobjecttable.h json/jsonobjecttable.cpp
  json/jsonobservertable.h json/jsonobservertable.cpp
  json/jsontelescopetable.h json/jsontelescopetable.cpp
)

add_library(astrodb::base ALIAS astrodb-base)

target_sources(astrodb-base PUBLIC
  FILE_SET HEADERS TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.." FILES
  cameratable.h
  database.h
  objecttable.h
  observertable.h
  telescopetable.h
  data/camera.h
  data/object.h
  data/observer.h
  data/telescope.h
  json/jsondatabase.h
)

if (BUILD_SQLITE3_DB)
  target_sources(astrodb-base PRIVATE
    sqlite3/sqlite3cameratable.h sqlite3/sqlite3cameratable.cpp
    sqlite3/sqlite3database.cpp
  )
  target_sources(astrodb-base PUBLIC
    FILE_SET HEADERS TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.." FILES
    sqlite3/sqlite3database.h
  )
  target_link_libraries(astrodb-base PUBLIC SQLite3::SQLite3)
endif()

set_target_properties(astrodb-base
    PROPERTIES
      VERSION
        ${CMAKE_PROJECT_VERSION}
      SOVERSION
        ${CMAKE_PROJECT_VERSION_MAJOR} #.${CMAKE_PROJECT_VERSION_MINOR}
      DEFINE_SYMBOL
        LIBIMCACORE
)


install(TARGETS astrodb-base
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


