#==============================================================================
# BoostFileSystem
#
# Description: BoostFileSystem module
#
# Author: xXx <xXX>, (C) 2010
#
# Copyright: See COPYING file that comes with this distribution
#==============================================================================


SET(KIT BoostFileSystem)

SET(CMAKE_MODULE_PATH  ${PROJECT_SOURCE_DIR}/../../../CMAKE  ${CMAKE_MODULE_PATH} ${CMAKE_ROOT}/Modules   )

MESSAGE( "CMAKE_PROJECT_NAME = ${CMAKE_PROJECT_NAME} ")

SET( ${KIT}_ENABLE_WRAPPING      ON )

SET(${KIT}_INCLUDE_PATHS
    ${AMILabEngine_SOURCE_DIR}/LanguageBase
    ${AMILabEngine_SOURCE_DIR}/Language
    ${AMILabEngine_SOURCE_DIR}/Common/include
    ${AMILabEngine_SOURCE_DIR}/CommonBase
    ${AMILabEngine_SOURCE_DIR}/Wrapping/include
    ${AMILabEngine_SOURCE_DIR}
    ${AMILabEngine_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)


INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/Wrapping
    ${CMAKE_BINARY_DIR}/Wrapping/Generated
    ${${KIT}_INCLUDE_PATHS}
    ${Boost_INCLUDE_DIR}
 )


MESSAGE("${KIT}_ENABLE_WRAPPING=${${KIT}_ENABLE_WRAPPING}")
IF(${KIT}_ENABLE_WRAPPING)
  #
  INCLUDE(${CMAKE_CURRENT_SOURCE_DIR}/../../../CMAKE/PluginWrapping.cmake)
  #
ENDIF(${KIT}_ENABLE_WRAPPING)

SET(${KIT}_HDRS
  ${${KIT}_HDRS}
  ${KIT}Plugin.h
  TestClass.h
)

SET(${KIT}_SRCS
  ${${KIT}_SRCS}
  ${KIT}Plugin.cpp
  TestClass.cpp
)

SET(${KIT}_scriptsdir
  ../scripts
)

IF(WIN32)
  set_source_files_properties(${${KIT}_SRCS} PROPERTIES COMPILE_FLAGS "-D${KIT}_EXPORTS")
ENDIF(WIN32)

SET(${KIT}_SRCS
    ${${KIT}_SRCS}
    ${${KIT}_HDRS}
    ${${KIT}_scriptsdir}
)


SET( ${KIT}_LIBRARY_OUTPUT_DIRECTORY  ${AMILabEngine_BINARY_DIR}/lib/amilabengine-${AMILABENGINE_VERSION}/plugin/)


SET(amilabengine_ownlibs
  ${LanguageBase}
  ${Common}
  ${CommonBase}
  ${WrapCommon}
)


ADD_LIBRARY(${KIT} MODULE ${${KIT}_SRCS} )

SET_TARGET_PROPERTIES( ${KIT}
  PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY ${${KIT}_LIBRARY_OUTPUT_DIRECTORY}
)
  
IF(WIN32 OR APPLE)
  TARGET_LINK_LIBRARIES( ${KIT}
    ${amilabengine_ownlibs}
    ${Boost_LIBRARIES}
    )
  TARGET_LINK_LIBRARIES( ${KIT} ${ZLIB_LIBRARIES})
  TARGET_LINK_LIBRARIES( ${KIT} ${BZIP2_LIBRARIES})
ELSE(WIN32 OR APPLE)
  ADD_DEPENDENCIES ( ${KIT} ${amilabengine_ownlibs})
ENDIF(WIN32 OR APPLE)

# Install library 
INSTALL(TARGETS BoostFileSystem
      RUNTIME DESTINATION bin
      ARCHIVE DESTINATION lib/amilabengine-${AMILABENGINE_VERSION}/plugin/
      LIBRARY DESTINATION lib/amilabengine-${AMILABENGINE_VERSION}/plugin/
)

#get_target_property(Subpixel_location BoostFileSystem LOCATION target)
#MESSAGE("Subpixel_location=${Subpixel_location}")

# Install the scripts
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/../../BoostFileSystem
        DESTINATION share/amilabengine-${AMILABENGINE_VERSION}/Modules
        # COMPONENT scripts
        FILES_MATCHING 
          PATTERN "*.amil"
          PATTERN "*.sh"
          PATTERN "*.py"
          PATTERN "*.png"         
          PATTERN "*.txt"
          PATTERN "*.sh"
          PATTERN "*.html"
          # ----  Exclude
          PATTERN "CMakeLists.txt" EXCLUDE
          PATTERN "src"            EXCLUDE
          PATTERN ".svn"           EXCLUDE
          PATTERN "*.in"           EXCLUDE
        PERMISSIONS 
          OWNER_EXECUTE
          OWNER_WRITE
          OWNER_READ
          GROUP_EXECUTE
          GROUP_READ
        )

MESSAGE("TARGET: ${KIT}")
