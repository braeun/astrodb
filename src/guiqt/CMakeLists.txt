
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

