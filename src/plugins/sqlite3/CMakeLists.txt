
add_library(astrodb_sqlite3 SHARED
  sqlite3cameratable.cpp sqlite3cameratable.h
  sqlite3database.cpp sqlite3database.h
  sqlite3objecttable.cpp sqlite3objecttable.h
  sqlite3observertable.cpp sqlite3observertable.h
  sqlite3telescopetable.cpp sqlite3telescopetable.h
  sqlite3plugin.h sqlite3plugin.cpp
  sqlite3infosnippettable.h sqlite3infosnippettable.cpp
)

set(ASTRODB_SQLITE3_DEF)
list(APPEND ASTRODB_SQLITE3_DEF -DVERSION_MAJOR=${PROJECT_VERSION_MAJOR})
list(APPEND ASTRODB_SQLITE3_DEF -DVERSION_MINOR=${PROJECT_VERSION_MINOR})
list(APPEND ASTRODB_SQLITE3_DEF -DVERSION_PATCH=${PROJECT_VERSION_PATCH})

target_compile_definitions(astrodb_sqlite3 PRIVATE ${ASTRODB_SQLITE3_DEF})

target_link_libraries(astrodb_sqlite3
  PUBLIC SQLite3::SQLite3
  PUBLIC astrodb::astrodb-base
)

install(TARGETS astrodb_sqlite3
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/astrodb
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

