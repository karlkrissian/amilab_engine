# The name of our project is "HELLO".  CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
project (AMILabEngine)


MESSAGE( "CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME} ")

cmake_minimum_required(VERSION 2.8.5)

if(POLICY CMP0017) 
  cmake_policy(SET CMP0017 NEW)
endif(POLICY CMP0017)

SET(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/../CMAKE ${CMAKE_MODULE_PATH} ${CMAKE_ROOT}/Modules   )

 
#-------------------------------------------------------------
#  CONFIGURE OUTPUT DIRECTORIES FOR WINDOWS BECAUSE OF DLL
#-------------------------------------------------------------

IF (WIN32)
  # ---------- Setup output Directories -------------------------
  SET (CMAKE_LIBRARY_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/Bin
    CACHE PATH
    "Single Directory for all Libraries"
  )

  # --------- Setup the Executable output Directory -------------
  SET (CMAKE_ARCHIVE_OUTPUT_DIRECTORY
    ${PROJECT_BINARY_DIR}/Bin
    CACHE PATH
    "Single Directory for all static libraries."
  )
ENDIF(WIN32)

# --------- Setup the Executable output Directory -------------
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${PROJECT_BINARY_DIR}
  CACHE PATH
  "Single Directory for all Executables."
)

#-----------------------------------------------------
# VERSION information
#-----------------------------------------------------

SET(AMILABENGINE_VERSION_MAJOR "1")
SET(AMILABENGINE_VERSION_MINOR "0")
SET(AMILABENGINE_VERSION_PATCH "0")
SET(AMILABENGINE_VERSION "${AMILABENGINE_VERSION_MAJOR}.${AMILABENGINE_VERSION_MINOR}.${AMILABENGINE_VERSION_PATCH}")


#-----------------------------------------------------
# set packaging information
#-----------------------------------------------------
INCLUDE(InstallRequiredSystemLibraries)


#
# Common package configuration
#
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "AMILabEngine scripting language with C++ wrapping system")
SET(CPACK_PACKAGE_VENDOR "Karl Krissian, Montpellier 2014")
SET(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_CURRENT_SOURCE_DIR}/ReadMe.txt")
SET(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/Copyright.txt")
SET(CPACK_PACKAGE_VERSION ${AMILABENGINE_VERSION})
SET(CPACK_PACKAGE_VERSION_MAJOR ${AMILABENGINE_VERSION_MAJOR} )
SET(CPACK_PACKAGE_VERSION_MINOR ${AMILABENGINE_VERSION_MINOR} )
SET(CPACK_PACKAGE_VERSION_PATCH ${AMILABENGINE_VERSION_PATCH} )
SET(CPACK_PACKAGE_INSTALL_DIRECTORY "CMake ${CMake_VERSION_MAJOR}.${CMake_VERSION_MINOR}")
SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "AMILabEngine scripting language with C++ wrapping system")

SET(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}.${CMAKE_SYSTEM_PROCESSOR}")
SET(CPACK_TOPLEVEL_TAG ${CPACK_SYSTEM_NAME})

SET(CPACK_INSTALL_PREFIX "${CPACK_INSTALL_PREFIX}")
SET(CPACK_PACKAGE_RELOCATABLE "true")
#SET(CPACK_SET_DESTDIR "ON")
SET(CPACK_SET_DESTDIR "OFF")

#
# RPM configuration
#
SET(CPACK_RPM_PACKAGE_SUMMARY "AMILabEngine  scripting language with C++ wrapping system")
SET(CPACK_RPM_PACKAGE_NAME "amilab")
SET(CPACK_RPM_PACKAGE_VERSION ${AMILABENGINE_VERSION})
SET(CPACK_RPM_PACKAGE_RELEASE "1")
SET(CPACK_RPM_PACKAGE_LICENSE "LGPL")
SET(CPACK_RPM_PACKAGE_GROUP "Applications/Engineering")
SET(CPACK_RPM_PACKAGE_VENDOR "Karl Krissian, ULPGC")
SET(CPACK_RPM_PACKAGE_DESCRIPTION "AMILabEngine scripting language with C++ wrapping system.")
SET(CPACK_RPM_PACKAGE_REQUIRES "glibc ")
SET(CPACK_RPM_PACKAGE_ARCHITECTURE ${CMAKE_SYSTEM_PROCESSOR})

# this will make the package relocatable !!cd
SET(CPACK_RPM_SPEC_MORE_DEFINE "Prefix: /usr")

# package architecture
# does this work??
MESSAGE("CMAKE_SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}")
MESSAGE("CMAKE_SIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P}")
MESSAGE("CMAKE_GENERATOR=${CMAKE_GENERATOR}")
MESSAGE("CMAKE_CL_64=${CMAKE_CL_64}")
IF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")
  SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE amd64)
  SET(CPACK_RPM_PACKAGE_ARCHITECTURE "x86_64")
ELSEIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "i686")
  SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE i386)
  SET(CPACK_RPM_PACKAGE_ARCHITECTURE "i386")
ENDIF(${CMAKE_SYSTEM_PROCESSOR} STREQUAL "x86_64")



# create AMILABENGINE_BIN variable
# IF(CMAKE_BUILD_TYPE)
#   string(TOLOWER AMILABENGINE_${CPACK_PACKAGE_VERSION}_${CMAKE_BUILD_TYPE} AMILABENGINE_BIN )
# ELSE(CMAKE_BUILD_TYPE)
  string(TOLOWER amilabengine_${CPACK_PACKAGE_VERSION} AMILABENGINE_BIN )
# ENDIF(CMAKE_BUILD_TYPE)
MESSAGE("AMILABENGINE_BIN=${AMILABENGINE_BIN}")
MESSAGE("CMAKE_GENERATOR = ${CMAKE_GENERATOR}")


#
# DEB configuration
#


IF(UNIX)
  #
  # DEB configuration
  #
  # no i386 in debian, should use dpkg --print-architecture ??
#  SET(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "i386" )
  SET(CPACK_DEBIAN_PACKAGE_MAINTAINER   "karl.krissian@gmail.com")
  SET(CPACK_DEBIAN_PACKAGE_SECTION      "science")
  SET(CPACK_DEBIAN_PACKAGE_PRIORITY     "extra")
  # creating dependencies ...
  MESSAGE(" ${AMILABENGINE_BIN}_release")
  if (EXISTS "${AMILABENGINE_BIN}_release")
      EXECUTE_PROCESS( 
        COMMAND ${CMAKE_SOURCE_DIR}/../Releases/Debian/list_dependencies.sh  ${AMILABENGINE_BIN}_release
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        RESULT_VARIABLE amilabengine_dep_result 
        OUTPUT_VARIABLE amilabengine_dep_output
        ERROR_VARIABLE amilabengine_dep_error
      )
    
      MESSAGE ("Dependencies = [${amilabengine_dep_result}], [${amilabengine_dep_output}] , [${amilabengine_dep_error}]")
      SET(CPACK_DEBIAN_PACKAGE_DEPENDS "${amilabengine_dep_output}")
#      SET(CPACK_DEBIAN_PACKAGE_DEPENDS "lib64expat1, libbz2-1.0, libc6, libc6-amd64, libc6-i686, libexpat1, libgcc1, libgl1-mesa-glx, libglu1-mesa, libice6, libjpeg62, libpng12-0, libsm6, libstdc++6, libtiff4, libuuid1, libvtk5.6, libwxbase2.8-0, libwxgtk2.8-0, libx11-6, libxext6, zlib1g")
#    endif(objdump_prog)
  
  ENDIF(EXISTS "${AMILABENGINE_BIN}_release")
ENDIF(UNIX)

#
# NSIS: not used at the moment
#
IF(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Makec
  # sure there is at least one set of four (4) backlasshes.
  #SET(CPACK_PACKAGE_ICON "${CMake_SOURCE_DIR}/Utilities/Release\\\\InstallIcon.bmp")
  #SET(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  SET(CPACK_NSIS_DISPLAY_NAME "${CPACK_PACKAGE_INSTALL_DIRECTORY} AMIOpticalFlow library")
  SET(CPACK_NSIS_HELP_LINK "http:\\\\\\\\http://amilab.sourceforge.net")
  #SET(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.my-personal-home-page.com")
  #SET(CPACK_NSIS_CONTACT "lalvarez@dis.ulpgc.es")
  SET(CPACK_NSIS_MODIFY_PATH ON)
ELSE(WIN32 AND NOT UNIX)
  #SET(CPACK_STRIP_FILES "bin/MyExecutable")
  #SET(CPACK_PACKAGE_INSTALL_DIRECTORY "/usr/local")
  SET(CPACK_SOURCE_STRIP_FILES "")
ENDIF(WIN32 AND NOT UNIX)
#SET(CPACK_PACKAGE_EXECUTABLES "MyExecutable" "My Executable")
#MESSAGE("CMake:Debug:  CPACK_PACKAGE_INSTALL_DIRECTORY         = ${CPACK_PACKAGE_INSTALL_DIRECTORY}")

#
# MacOS
#
# Bundle Configuration (still needs work ...),
# now compiling MacOS Package with "sudo cpack -G PackageMaker ."
#
IF (APPLE)
  SET(CPACK_GENERATOR "Bundle")
  SET( CPACK_PACKAGE_FILE_NAME      )
#  SET( CPACK_PACKAGE_ICON            "${CMAKE_SOURCE_DIR}/../Pixmaps/amilabengine_logo_new_48x48_alpha.png")
#  SET( CPACK_BUNDLE_ICON             "${CMAKE_SOURCE_DIR}/../Pixmaps/amilabengine_logo_new_48x48_alpha.png")
#  SET( CPACK_BUNDLE_STARTUP_COMMAND )


  SET(CPACK_BUNDLE_ICON              "${CMAKE_SOURCE_DIR}/../Pixmaps/amilabengine_bundleicon.icns")
  SET( CPACK_BUNDLE_NAME             "AMILabEngine_${AMILABENGINE_VERSION}_release")
  SET( CPACK_BUNDLE_PLIST            "${CMAKE_SOURCE_DIR}/../Releases/MacOS/Info.plist")
  SET(CPACK_BUNDLE_STARTUP_COMMAND   "${CMAKE_SOURCE_DIR}/../Releases/MacOS/StartupCommand")
  SET(CPACK_PACKAGE_DESCRIPTIONG     "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}")

  #Usamos el icono que hicimos para el disco
  SET(CPACK_PACKAGE_ICON    "${CMAKE_SOURCE_DIR}/../Pixmaps/amilabengine_volumeicon.icns")
  SET(CPACK_PACKAGE_NAME     "AMILabEnginePackage")
  SET(CPACK_PACKAGE_VERSION  "1.0")

ENDIF(APPLE)


#IF(APPLE)
#  SET(CMAKE_BUNDLE_NAME "AMILabEngine_${AMILABENGINE_VERSION}")
#  SET(CMAKE_BUNDLE_LOCATION "${CMAKE_INSTALL_PREFIX}")
#  # make sure CMAKE_INSTALL_PREFIX ends in /
#  STRING(LENGTH "${CMAKE_INSTALL_PREFIX}" LEN)
#  MATH(EXPR LEN "${LEN} -1" )
#  STRING(SUBSTRING "${CMAKE_INSTALL_PREFIX}" ${LEN} 1 ENDCH)
#  IF(NOT "${ENDCH}" STREQUAL "/")
#  SET(CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}/")
#  ENDIF(NOT "${ENDCH}" STREQUAL "/")
#  SET(CMAKE_INSTALL_PREFIX  "${CMAKE_INSTALL_PREFIX}${CMAKE_BUNDLE_NAME}.app/Contents")
#ENDIF(APPLE)



#SET( CPACK_COMPONENTS_ALL applications scripts doc )

IF (UNIX AND NOT APPLE)
  SET(CPACK_GENERATOR "RPM")
  #SET(CPACK_GENERATOR "RPM;STGZ;DEB")
  #SET(CPACK_SOURCE_GENERATOR "TGZ")
ENDIF(UNIX AND NOT APPLE)

INCLUDE(CPack)


#-------------------------------------------------------------------------------
#  Configuration files
#-------------------------------------------------------------------------------

#
# Configuration of Linux Desktop
#
# CONFIGURE_FILE(
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/Linux/share/applications/amilab.desktop.in
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/Linux/share/applications/amilab.desktop)
# 
# CONFIGURE_FILE(
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/Linux/share/menu/amilab.in
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/Linux/share/menu/amilab)
# 
# #
# # Configuration for MacOS
# #
# 
# CONFIGURE_FILE(
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/MacOS/Info.plist.in
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/MacOS/Info.plist)
# 
# CONFIGURE_FILE(
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/MacOS/StartupCommand.in
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/MacOS/StartupCommand)
# 
# #
# # Configuration of Windows installation script (Inno)
# #
# 
# CONFIGURE_FILE(
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/Windows/amilabengine_wininstall.iss.in
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Releases/Windows/amilabengine_wininstall.iss)
# 
# #
# # Scripts dir configuration in the build directory
# #
# 
# CONFIGURE_FILE(
#     ${CMAKE_CURRENT_SOURCE_DIR}/../Config/config.amil.in
#     ${CMAKE_CURRENT_BINARY_DIR}/config.amil)

#-------------------------------------------------------------------------------
#  End of Configuration files
#-------------------------------------------------------------------------------

OPTION(AMI_USE_STATIC_LIBS     "Look for static libraries" ON)
OPTION(AMI_USE_DOXYGEN         "Look for doxygen" OFF)
OPTION(AMI_USE_PRECOMP_HEADERS "Use precompiled headers when available" OFF)


set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "4.2")

IF( AMI_USE_STATIC_LIBS )
   SET( _ami_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES ${CMAKE_FIND_LIBRARY_SUFFIXES})
   IF(WIN32)
     SET(CMAKE_FIND_LIBRARY_SUFFIXES .lib .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
   ELSE(WIN32)
     SET(CMAKE_FIND_LIBRARY_SUFFIXES .a ${CMAKE_FIND_LIBRARY_SUFFIXES})
   ENDIF(WIN32)
ENDIF( AMI_USE_STATIC_LIBS )


OPTION(AMI_CHECK_BRANCH "Look for the name of the SVN branch" OFF)

IF(AMI_CHECK_BRANCH)
  FIND_PACKAGE(Subversion)

  IF(Subversion_FOUND)
    Subversion_WC_INFO(${CMAKE_SOURCE_DIR} SRCDIR)
    MESSAGE( " *** SUBVERSION INFO ***")
    MESSAGE( "SRCDIR_WC_URL = ${SRCDIR_WC_URL}")
    #MESSAGE( "SRCDIR_WC_ROOT = ${SRCDIR_WC_ROOT}")
    #MESSAGE( "SRCDIR_WC_REVISION = ${SRCDIR_WC_REVISION}")
  ENDIF(Subversion_FOUND)

  # Get the root dir through info XML
  EXECUTE_PROCESS(COMMAND ${Subversion_SVN_EXECUTABLE} info --xml ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE SRCDIR_WC_XML_INFO
    ERROR_VARIABLE Subversion_svn_info_error
    RESULT_VARIABLE Subversion_svn_info_result
    OUTPUT_STRIP_TRAILING_WHITESPACE)

  IF(NOT ${Subversion_svn_info_result} EQUAL 0)
    MESSAGE(SEND_ERROR "Command \"${Subversion_SVN_EXECUTABLE} info --xml ${CMAKE_SOURCE_DIR}\" failed with output:\n${Subversion_svn_info_error}")
  ELSE(NOT ${Subversion_svn_info_result} EQUAL 0)

    STRING(REGEX REPLACE ".*<root>(.*)</root>.*"
      "\\1" SRCDIR_WC_XML_ROOT "${SRCDIR_WC_XML_INFO}")
    MESSAGE( "SRCDIR_WC_XML_ROOT = ${SRCDIR_WC_XML_ROOT}")
  ENDIF(NOT ${Subversion_svn_info_result} EQUAL 0)

  
  STRING(REGEX MATCH "^(.*\n)?${SRCDIR_WC_XML_ROOT}/trunk/src.*"
    SRCDIR_WC_TRUNK  "${SRCDIR_WC_URL}")
  MESSAGE( "SRCDIR_WC_TRUNK = ${SRCDIR_WC_TRUNK}")

  IF(NOT SRCDIR_WC_TRUNK)
    IF(SRCDIR_WC_XML_ROOT AND SRCDIR_WC_URL)
      SET(PATTERN "^(.*\n)?${SRCDIR_WC_XML_ROOT}([^\n]+).*")
      MESSAGE("PATTERN = ${PATTERN}")
      STRING(REGEX REPLACE "^(.*\n)?${SRCDIR_WC_XML_ROOT}/branches/(.+)/src.*"
        "\\2" SRCDIR_WC_BRANCH "${SRCDIR_WC_URL}")
      MESSAGE( "SRCDIR_WC_BRANCH = ${SRCDIR_WC_BRANCH} ")
    ENDIF(SRCDIR_WC_XML_ROOT AND SRCDIR_WC_URL)
  ENDIF(NOT SRCDIR_WC_TRUNK)
  
ENDIF(AMI_CHECK_BRANCH)

OPTION(AMI_ENABLE_WRAPPING "Enable Automatic Wrapping: need gccxml, python, ..." ON)

IF(AMI_ENABLE_WRAPPING)
  FIND_PACKAGE( GCCXML REQUIRED)
  FIND_PACKAGE( PythonInterp REQUIRED)
ENDIF(AMI_ENABLE_WRAPPING)

# set gcc hidden visibility 
# IF(UNIX)
#     IF(CMAKE_COMPILER_IS_GNUCC)
#          SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden")
#          SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
#     ENDIF(CMAKE_COMPILER_IS_GNUCC)
# ENDIF(UNIX)

OPTION(GENERATE_HTML_HELP "Generate HTML file help")


# Separe Mac generated files
#IF(APPLE)
#  STRING(REGEX MATCH "WXMAC" ISMAC ${wxWidgets_CXX_FLAGS})
#  MESSAGE("\"${ISMAC}\"")
#  IF ( NOT ( ISMAC STREQUAL "" ) )
#    SET(AMI_WXWIDGETS_VERSION ${AMI_WXWIDGETS_VERSION}/Mac)
#  ENDIF( NOT ( ISMAC STREQUAL "" ) )
#  MESSAGE("AMI_WXWIDGETS_VERSION ${AMI_WXWIDGETS_VERSION}")
#ENDIF(APPLE)


OPTION(Boost_USE_STATIC_LIBS "Use Boost static libraries" OFF)

SET(Boost_USE_MULTITHREAD OFF)
#MESSAGE(  CMAKE_HOST_SYSTEM_NAME=${CMAKE_HOST_SYSTEM_NAME} )
#MESSAGE(  CMAKE_HOST_SYSTEM=${CMAKE_HOST_SYSTEM} )

SET(BOOST_RELEASE "1.33" CACHE STRING "specify boost version")
FIND_PACKAGE( Boost ${BOOST_RELEASE} REQUIRED COMPONENTS date_time filesystem  system iostreams  regex )
#graph)
#SET(Boost_USE_STATIC_LIBS ON)
MESSAGE( "Boost_LIBRARIES = ${Boost_LIBRARIES}")

FIND_PACKAGE(Curses)

IF(AMI_USE_OPENMP)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
ENDIF(AMI_USE_OPENMP)

FIND_PACKAGE( Pthreads)

OPTION(AMI_USE_FLEXBISON "Compile language using Flex and Bison" ON)
IF(AMI_USE_FLEXBISON)
  OPTION(AMI_BISON_DEBUG "Outputs debugging information of the parser" OFF)
ENDIF(AMI_USE_FLEXBISON)

IF(AMI_USE_OPENMP)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  SET(CMAKE_EXE_LINKER_FLAGS 
      "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
ENDIF(AMI_USE_OPENMP)


IF(AMI_USE_FLEXBISON)
  FIND_PACKAGE(BISON)
  FIND_PACKAGE(FLEX)
ENDIF(AMI_USE_FLEXBISON)


IF(AMI_USE_FASTNLMEANS)
  FIND_PACKAGE(NewNLMeans)
  MESSAGE("NewNLMeans_LIBRARY=${NewNLMeans_LIBRARY}")
ENDIF(AMI_USE_FASTNLMEANS)

OPTION(AMI_USE_OPENMP "Use OpenMP for multithreading and timing" OFF)

IF(AMI_USE_OPENMP)
  FIND_PACKAGE( OpenMP)
ENDIF(AMI_USE_OPENMP)

OPTION(AMI_USE_SSE "Use SSE CPU instructions set" OFF)

IF(AMI_USE_SSE)
  # add flag for mingw
  MESSAGE("${CMAKE_CXX_COMPILER}")
  IF(${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/i686-pc-mingw32-g++")
    MESSAGE("adding -msse for compiler")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse")
  ENDIF(${CMAKE_CXX_COMPILER} STREQUAL "/usr/bin/i686-pc-mingw32-g++")
  IF (CMAKE_COMPILER_IS_GNUCXX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -msse3")
  ENDIF(CMAKE_COMPILER_IS_GNUCXX)

ENDIF(AMI_USE_SSE)


 IF( AMI_USE_STATIC_LIBS )
   SET(CMAKE_FIND_LIBRARY_SUFFIXES ${_ami_ORIG_CMAKE_FIND_LIBRARY_SUFFIXES})
 ENDIF( AMI_USE_STATIC_LIBS )



INCLUDE (CheckIncludeFiles)
# usage: CHECK_INCLUDE_FILES (<header> <RESULT_VARIABLE> )
CHECK_INCLUDE_FILES (malloc.h HAVE_MALLOC_H)




#SET(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../CMAKE)

SET(AMI_BUILD_TYPE ${CMAKE_BUILD_TYPE})

CONFIGURE_FILE( ${CMAKE_CURRENT_SOURCE_DIR}/AMILabEngineConfig.h.in 
                ${CMAKE_CURRENT_BINARY_DIR}/AMILabEngineConfig.h
              )

include(amilabengine_macros)

include(PCH_GCC4_v2)

InitPrintSources()

IF (CMAKE_COMPILER_IS_GNUCXX)
  # expand macros with debug info
  SET(CMAKE_CXX_FLAGS_DEBUG "-g3")
  MESSAGE("CMAKE_CXX_FLAGS_DEBUG = ${CMAKE_CXX_FLAGS_DEBUG}")

  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -std=c++0x")
  # -std=gnu++11 

ENDIF (CMAKE_COMPILER_IS_GNUCXX)


#-------------------------------------------------------------------------------

#MESSAGE(wxParams_INCLUDE_DIRS=${wxParams_INCLUDE_DIRS})
MESSAGE(FLEX_INCLUDE_DIR=${FLEX_INCLUDE_DIR})


include_directories (
  ${CMAKE_CURRENT_BINARY_DIR}
)

# for compatibility with previous name
SET( AMILABENGINE_SOURCE_DIR ${AMILabEngine_SOURCE_DIR} )

add_subdirectory (CommonBase)
add_subdirectory (Common)
add_subdirectory (AMILab)


add_subdirectory (LanguageBase)
add_subdirectory (Language)

add_subdirectory (Wrapping)


#
# Automatically included plugins
#


SET(AMILABENGINE_INCLUDE_DIRS
  ${wxParams_INCLUDE_DIRS}
  ${AMILABENGINE_SOURCE_DIR}/CommonBase
  ${AMILABENGINE_SOURCE_DIR}/Common/include
  ${AMILABENGINE_SOURCE_DIR}/LanguageBase
  ${AMILABENGINE_SOURCE_DIR}/Language
  ${AMILABENGINE_SOURCE_DIR}/AMILab
  ${AMILABENGINE_SOURCE_DIR}/Wrapping/include
  ${AMILABENGINE_SOURCE_DIR}
  ${AMILabEngine_BINARY_DIR}
)


MESSAGE("AMILABENGINE_INCLUDE_DIRS=${AMILABENGINE_INCLUDE_DIRS}")
CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/../CMAKE/AMILabEngineConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/AMILabEngineConfig.cmake)

include_directories (
  ${AMILABENGINE_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIR}
  ${OPENGL_INCLUDE_DIR}
  ${OPTICFLOW_INCLUDE_DIR}
  )


SET(amilabengine_bin_SRCS 
  amilab_engine.cpp
  TTY/ncstream.cpp
#  MainFrame.cpp
)

SET(amilabengine_bin_HDRS
  TTY/ncstream.hpp
#  guicon.h
#  MainFrame.h
)

SET(amilabengine_scripts_dir ../scripts/Common)

SET(amilabengine_bin_SRCS
  ${amilabengine_bin_SRCS}
  ${amilabengine_bin_HDRS}
  ${amilabengine_scripts_dir}
)

if (WIN32)
SET(amilabengine_bin_SRCS
  ${amilabengine_bin_SRCS}
  guicon.cpp
)
endif (WIN32)


include_directories (
  ${AMILABENGINE_SOURCE_DIR}/LanguageBase
  ${AMILABENGINE_SOURCE_DIR}/Language
)


add_executable (${AMILABENGINE_BIN} WIN32
  # MACOSX_BUNDLE
  ${amilabengine_bin_SRCS}
)


SET(amilabengine_ownlibs
#   WrapLanguage
#   WrapBasicTypes
#   WrapIO
  WrapCommon
  LanguageBase
  Language
  AMILab
  Common
  CommonBase
)


# Test template class
IF(AMI_WRAP_EXAMPLES)
  SET(amilabengine_ownlibs WrapExamples ${amilabengine_ownlibs})
ENDIF(AMI_WRAP_EXAMPLES)

MESSAGE( "Boost_LIBRARIES=${Boost_LIBRARIES}" )


TARGET_LINK_LIBRARIES( ${AMILABENGINE_BIN}
  ${amilabengine_ownlibs}
  ${PTHREADS_LIBRARY}
  ${Boost_LIBRARIES}
  ${CURSES_LIBRARY}
  -lpanel
)


if (WIN32)
TARGET_LINK_LIBRARIES( ${AMILABENGINE_BIN}
  ole32
  oleaut32
  uuid
  winmm
)
endif (WIN32)


SET(CMAKE_DEBUG_POSTFIX  _debug)
SET(CMAKE_RELEASE_POSTFIX _release)
SET(CMAKE_MINSIZEREL_POSTFIX _minsizerel)
SET(CMAKE_RELWITHDEBINFO_POSTFIX _relwithdebinfo)
  
SET_TARGET_PROPERTIES( ${AMILABENGINE_BIN}
    PROPERTIES 
      DEBUG_POSTFIX           _debug
      RELEASE_POSTFIX         _release
      MINSIZEREL_POSTFIX      _minsizerel
      RELWITHDEBINFO_POSTFIX  _relwithdebinfo

      COMPILE_DEFINITIONS_DEBUG           "_CMAKEBUILDTYPE_DEBUG_"
      COMPILE_DEFINITIONS_RELEASE         "_CMAKEBUILDTYPE_RELEASE_"
      COMPILE_DEFINITIONS_MINSIZEREL      "_CMAKEBUILDTYPE_MINSIZEREL_"
      COMPILE_DEFINITIONS_RELWITHDEBINFO  "_CMAKEBUILDTYPE_RELWITHDEBINFO_"
)

IF(MSVC)
  # NEED TO SPECIFY FOR EACH POSSIBLE CONFIGURATION
  # SET INCREMENTAL LINKING: much faster ...
  set_target_properties( ${AMILABENGINE_BIN} 
    PROPERTIES LINK_FLAGS_RELEASE "/NODEFAULTLIB:LIBCMT /NODEFAULTLIB:LIBCMTD /NODEFAULTLIB:MSVCRTD /INCREMENTAL:YES")

  set_target_properties( ${AMILABENGINE_BIN} 
    PROPERTIES LINK_FLAGS_DEBUG "/NODEFAULTLIB:LIBCMT /NODEFAULTLIB:LIBCMTD /INCREMENTAL:NO")

ENDIF(MSVC)


# -------------------------------------
#   Find library in MacOS package
# -------------------------------------
IF(APPLE)
    SET(CMAKE_INSTALL_NAME_DIR @executable_path/../lib/amilab-${AMILABENGINE_VERSION} CACHE STRING "Executable Path for MacOS X" FORCE)
    MARK_AS_ADVANCED(CMAKE_INSTALL_NAME_DIR)
ENDIF(APPLE)



INSTALL(TARGETS ${AMILABENGINE_BIN}
  RUNTIME DESTINATION bin
  #  COMPONENT applications
  #  BUNDLE DESTINATION 
  #${CMAKE_INSTALL_DESTINATION_ARGS}
)


# Install the scripts
install(DIRECTORY ${AMILABENGINE_SOURCE_DIR}/../scripts
        DESTINATION share/amilab-${AMILABENGINE_VERSION}
#        COMPONENT scripts
        FILES_MATCHING 
          PATTERN "*.amil"
          PATTERN "*.sh"
          PATTERN "*.py"
          PATTERN "*.png"         
          PATTERN "*.txt"
          PATTERN "*.sh"
          PATTERN "*.html"
          # exclude
          PATTERN ".svn" EXCLUDE
          PATTERN "*.in"  EXCLUDE
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                    GROUP_EXECUTE GROUP_READ
                    WORLD_READ
        )

install(FILES ${AMILABENGINE_SOURCE_DIR}/../Modules/Add2Menu.amil
        DESTINATION share/amilab-${AMILABENGINE_VERSION}/Modules/
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                    GROUP_EXECUTE GROUP_READ
                    WORLD_READ
        )

# Install the Matlab utilities
install(DIRECTORY ${AMILABENGINE_SOURCE_DIR}/../MatlabUtils
        DESTINATION share/amilab-${AMILABENGINE_VERSION}
        FILES_MATCHING PATTERN "*.m" PATTERN "*.amil"
          PATTERN "*.sh"
          PATTERN "*.py"
          PATTERN "*.png"         
          PATTERN "*.txt"
          PATTERN "*.sh"
          PATTERN "*.html"
          # exclude
          PATTERN ".svn" EXCLUDE
          PATTERN "*.in"  EXCLUDE
        PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                    GROUP_EXECUTE GROUP_READ
                    WORLD_READ
        )


# Install the documentation
install(DIRECTORY ${AMILABENGINE_SOURCE_DIR}/../doc
        DESTINATION share/amilab-${AMILABENGINE_VERSION}
#        COMPONENT doc
        FILES_MATCHING
          PATTERN "*.html"
          PATTERN "*.amih"
          PATTERN "*.gif"
          PATTERN "*.css"
          PATTERN "*.txt"
          # exclude
          PATTERN ".svn" EXCLUDE
          PATTERN "*.in"  EXCLUDE
        PERMISSIONS 
          OWNER_WRITE 
          OWNER_READ
          GROUP_READ
          WORLD_READ
        )

if (UNIX)
  # Install the documentation
  install(DIRECTORY ${AMILABENGINE_SOURCE_DIR}/../Releases/Linux/share
          DESTINATION .
          FILES_MATCHING
            PATTERN "*"
            # exclude
            PATTERN "*.in"  EXCLUDE
            PATTERN ".svn" EXCLUDE
            PATTERN "*~"   EXCLUDE
          PERMISSIONS OWNER_READ GROUP_READ WORLD_READ
          )
endif(UNIX)



#Test for amilab engine
#INCLUDE(${PROJECT_SOURCE_DIR}/../CTEST/amilabengine_tests.cmake)


if (GENERATE_HTML_HELP)
  # check if doxygen is even installed
  find_package(Doxygen)
  if (DOXYGEN_FOUND STREQUAL "NO")
    message(FATAL_ERROR "Doxygen not found. Please get a copy http://www.doxygen.org")
  endif (DOXYGEN_FOUND STREQUAL "NO")

  # prepare doxygen configuration file
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../Doxygen/doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

  # add doxygen as target
  add_custom_target(doxygen ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

  # cleanup $build/api-doc on "make clean"
  set_property(DIRECTORY APPEND PROPERTY
       ADDITIONAL_MAKE_CLEAN_FILES api-doc)

  # add doxygen as dependency to doc-target
  get_target_property(DOC_TARGET doc TYPE)
  if(NOT DOC_TARGET)
    add_custom_target(doc)
  endif()
  add_dependencies(doc doxygen)

  # install HTML API documentation and manual pages
  set(DOC_PATH "share/amilabengine-${AMILABENGINE_VERSION}")

  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/html
           DESTINATION ${DOC_PATH}
         )

  # install man pages into packages, scope is now project root..
  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/api-doc/man/man3
         DESTINATION share/man/man3/
       )
endif (GENERATE_HTML_HELP)

PrintSources(${AMILABENGINE_BIN})
