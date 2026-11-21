
find_package(SQLite3)
if (SQLite3_FOUND)
  if(NOT TARGET SQLite3::SQLite3) # CMake < 4.3
    add_library(SQLite3::SQLite3 ALIAS SQLite::SQLite3)
  endif()
  add_subdirectory(sqlite3)
endif()



if (Qt6_FOUND)
  add_subdirectory(qt)
endif()
