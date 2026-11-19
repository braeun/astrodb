
add_library(astrodb_qt SHARED
  pluginqt.h pluginqt.cpp
  databaseqt.h databaseqt.cpp
  cameratableqt.h cameratableqt.cpp
  objecttableqt.h objecttableqt.cpp
  observertableqt.h observertableqt.cpp
  telescopetableqt.h telescopetableqt.cpp
  infosnippettableqt.h infosnippettableqt.cpp
)

target_compile_definitions(astrodb_qt PRIVATE ${ASTRODB_QT6_DEF})

target_link_libraries(astrodb_qt
  Qt::Sql
  astrodb::astrodb-base
)

install(TARGETS astrodb_qt
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/astrodb
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

