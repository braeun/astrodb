
add_library(astrodb-qt SHARED
  qtdatabase.cpp
  qtcameratable.h qtcameratable.cpp
)
add_library(astrodb::qt ALIAS astrodb-qt)

target_sources(astrodb-qt PUBLIC
  FILE_SET HEADERS TYPE HEADERS BASE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/.." FILES
  qtdatabase.h
)

target_link_libraries(astrodb-qt PUBLIC astrodb::base Qt::Sql)

set_target_properties(astrodb-qt
    PROPERTIES
      VERSION
        ${CMAKE_PROJECT_VERSION}
      SOVERSION
        ${CMAKE_PROJECT_VERSION_MAJOR} #.${CMAKE_PROJECT_VERSION_MINOR}
      DEFINE_SYMBOL
        LIBASTRODBQT
)

install(TARGETS astrodb-qt
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

