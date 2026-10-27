
find_package(Qt6 COMPONENTS Sql REQUIRED)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

if (Qt6_FOUND)

  set(ASTRODB_QT6_DEF)
  list(APPEND ASTRODB_QT6_DEF -DVERSION_MAJOR=${PROJECT_VERSION_MAJOR})
  list(APPEND ASTRODB_QT6_DEF -DVERSION_MINOR=${PROJECT_VERSION_MINOR})
  list(APPEND ASTRODB_QT6_DEF -DVERSION_PATCH=${PROJECT_VERSION_PATCH})

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



endif()
