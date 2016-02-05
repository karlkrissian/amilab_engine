#==============================================================================
# ModuleExample
#
# Description: ModuleExample module
#
# Author: xXx <xXX>, (C) 2010
#
# Copyright: See COPYING file that comes with this distribution
#==============================================================================

project (ModuleExample)

SET(KIT ModuleExample)

set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "4.2")

IF(POLICY CMP0017) 
  CMAKE_POLICY(SET CMP0017 NEW)
ENDIF(POLICY CMP0017)

SET(CMAKE_MODULE_PATH  ${PROJECT_SOURCE_DIR}/../../CMAKE  ${CMAKE_MODULE_PATH} ${CMAKE_ROOT}/Modules   )

MESSAGE( "CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME} ")

CMAKE_MINIMUM_REQUIRED(VERSION 2.6.4)

# default boost parameters
OPTION(Boost_USE_STATIC_LIBS "Use Boost static libraries" ON)
SET(Boost_USE_MULTITHREAD OFF)
SET(BOOST_RELEASE "1.33" CACHE STRING "specify boost version")

OPTION( ${KIT}_GENERATE_HTML_HELP "Generate HTML file help" OFF)

FIND_PACKAGE(AMILabEngine REQUIRED)

INCLUDE(${AMILabEngine_BINARY_DIR}/AMILabEngineConfig.cmake)
MESSAGE("Boost_USE_STATIC_LIBS has been set to ${Boost_USE_STATIC_LIBS}")

INCLUDE(${AMILab_SOURCE_DIR}/../CMAKE/amilab_macros.cmake)


FIND_PACKAGE( Boost ${BOOST_RELEASE} COMPONENTS date_time filesystem  system iostreams  regex)
#FIND_PACKAGE( ZLIB)
#FIND_PACKAGE( BZip2)


add_subdirectory (src)


IF(${KIT}_GENERATE_HTML_HELP)
  # check if doxygen is even installed
  FIND_PACKAGE(Doxygen)
  IF (DOXYGEN_FOUND STREQUAL "NO")
    MESSAGE(FATAL_ERROR "Doxygen not found. Please get a copy http://www.doxygen.org")
  ENDIF (DOXYGEN_FOUND STREQUAL "NO")

  # prepare doxygen configuration file
  CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../../../Doxygen/doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

  # add doxygen as target
  ADD_CUSTOM_TARGET(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

  # cleanup $build/api-doc on "make clean"
  SET_PROPERTY(DIRECTORY APPEND PROPERTY
       ADDITIONAL_MAKE_CLEAN_FILES api-doc)

  # add doxygen as dependency to doc-target
  GET_TARGET_PROPERTY(DOC_TARGET doc TYPE)
  IF(NOT DOC_TARGET)
    ADD_CUSTOM_TARGET(doc)
  ENDIF(NOT DOC_TARGET)
  ADD_DEPENDENCIES(doc doxygen)

  # install HTML API documentation and manual pages
  SET(DOC_PATH "share/amilab-${AMILAB_VERSION}/${CMAKE_PROJECT_NAME}")

  INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/html
           DESTINATION ${DOC_PATH}
         )

  # install man pages into packages, scope is now project root..
  INSTALL(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/man/man3
         DESTINATION share/man/man3/
       )
ENDIF(${KIT}_GENERATE_HTML_HELP)


