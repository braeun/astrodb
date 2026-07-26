cmake_minimum_required(VERSION 3.23 FATAL_ERROR)

project(astrodb VERSION 0.1.0 LANGUAGES CXX)

# Forbid in-tree building
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
      message(STATUS "Please do an out-of-tree build:")
      message(STATUS "rm -f CMakeCache.txt && mkdir build && cd build; cmake .. && make")
      message(FATAL_ERROR "In-tree-build detected!")
endif()

include(CMakeDependentOption)

#-----------------------------------------------------------------------------
# BUILD SYSTEM
#-----------------------------------------------------------------------------

set(CMAKE_VERBOSE_MAKEFILE OFF)

#set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)

include(CheckTypeSize)
check_type_size("int" SIZEOF_INT LANGUAGE CXX)
if (${SIZEOF_INT} LESS "4")
  message(FATAL_ERROR "int must be at least 32bit")
endif()

include(GNUInstallDirs)

# keep rpath to actual Qt framework in executable
#set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)

#-----------------------------------------------------------------------------
# DEPENDENCIES
#-----------------------------------------------------------------------------

# Specify search path for CMake modules to be loaded by include() and find_package()
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# CMake config files
include(CMakePackageConfigHelpers)

# load the package to obtain information from pkgconfig
# ensure that packages etc. in /usr/local are found
# do NOT use CMAKE_PREFIX_PATH as it is used by qtcreator to select the Qt version
set(ENV{PKG_CONFIG_PATH} "${PKG_CONFIG_PATH}:/usr/local/lib/pkgconfig:/usr/local/lib64/pkgconfig")
find_package(PkgConfig REQUIRED)

find_package(SQLite3)
if (SQLite3_FOUND)
  if(NOT TARGET SQLite3::SQLite3) # CMake < 4.3
    add_library(SQLite3::SQLite3 ALIAS SQLite::SQLite3)
  endif()
endif()

#-----------------------------------------------------------------------------
# OPTIONS
#-----------------------------------------------------------------------------
# build options
#-----------------------------------------------------------------------------

CMAKE_DEPENDENT_OPTION(BUILD_SQLITE3_DB "build sqlite3 based database" ON "SQLITE3_FOUND" OFF)

#-----------------------------------------------------------------------------
# COMPILE DEFINITIONS
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# BUILD ALL COMPONENTS
#-----------------------------------------------------------------------------

add_subdirectory(src/base)

#-----------------------------------------------------------------------------
# INSTALL
#-----------------------------------------------------------------------------


#-----------------------------------------------------------------------------
# PACKAGE GENERATION
#-----------------------------------------------------------------------------

# generate a self-extracting archive using the modified template in the
# projects cmake directory

# first all variables must be set
set(CPACK_GENERATOR "STGZ")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_CONTACT "Harald Braeuning")
#set(CPACK_PACKAGE_VENDOR "GSI - Beam Instrumentation")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Astro Database")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_INCLUDE_TOPLEVEL_DIRECTORY OFF)
set(CPACK_PACKAGING_INSTALL_PREFIX "")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}")
#set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}.${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)



