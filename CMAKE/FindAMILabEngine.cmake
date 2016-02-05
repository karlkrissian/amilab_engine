#==============================================================================
# AMILabEngine configuration
#
# Author: xXx <xXX>, (C) 2010
#
# Copyright: See COPYING file that comes with this distribution
#==============================================================================


# Assume not found.
#SET(AMILabEngine_FOUND 0)
# Construct consitent error messages for use below.
SET(AMILabEngine_DIR_DESCRIPTION "directory containing AMILabEngineConfig.cmake.  This is either the root of the build tree, or PREFIX/lib/AMILabEngine for an installation.")
SET(AMILabEngine_DIR_MESSAGE "AMILabEngine not found.  Set the AMILabEngine_DIR cmake cache entry to the ${AMILabEngine_DIR_DESCRIPTION}")
FIND_PACKAGE(AMILabEngine QUIET NO_MODULE)

MESSAGE("AMILabEngine_FOUND=${AMILabEngine_FOUND}")
IF(AMILabEngine_FOUND)
  
  INCLUDE(${AMILabEngine_DIR}/AMILabEngineConfig.cmake)

  MESSAGE("AMILabEngine_SOURCE_DIR = ${AMILabEngine_SOURCE_DIR}")

  SET(AMILabEngine_PATHS
      ${AMILabEngine_SOURCE_DIR}/LanguageBase
      ${AMILabEngine_SOURCE_DIR}/Language
      ${AMILabEngine_SOURCE_DIR}/Common/include
      ${AMILabEngine_SOURCE_DIR}/CommonBase
      ${AMILabEngine_SOURCE_DIR}/Wrapping/include
      ${AMILabEngine_SOURCE_DIR}
      ${AMILabEngine_BINARY_DIR}
  )


  IF (${KIT}_NEED_VTK_WRAPPING)
    SET(AMILabEngine_PATHS
      ${AMILabEngine_BINARY_DIR}/Wrapping/WrapVTK/${AMI_VTK_VERSION}/Generated
      ${AMILabEngine_PATHS}
      )
    MESSAGE(" VTK wrapping path is ${AMILabEngine_BINARY_DIR}/Wrapping/WrapVTK/${AMI_VTK_VERSION}/Generated")
  ENDIF(${KIT}_NEED_VTK_WRAPPING)

  IF (${KIT}_NEED_ITK_WRAPPING)
    SET(AMILabEngine_PATHS
      ${AMILabEngine_BINARY_DIR}/Wrapping/WrapITK/${AMI_ITK_VERSION}/Generated
      ${AMILabEngine_PATHS}
      )
    MESSAGE(" ITK wrapping path is ${AMILabEngine_BINARY_DIR}/Wrapping/WrapITK/${AMI_ITK_VERSION}/Generated")
  ENDIF(${KIT}_NEED_ITK_WRAPPING)

  IF (${KIT}_NEED_WX_WRAPPING)
    SET(AMILabEngine_PATHS
      ${AMILabEngine_BINARY_DIR}/Wrapping/WrapWxWidgets/${AMI_WXWIDGETS_VERSION}/Generated
      ${AMILabEngine_PATHS}
      )
    MESSAGE(" WxWidgets wrapping path is ${AMILabEngine_BINARY_DIR}/Wrapping/WrapVTK/${AMI_WXWIDGETS_VERSION}/Generated")
  ENDIF(${KIT}_NEED_WX_WRAPPING)

  MESSAGE("AMILabEngine_PATHS = ${AMILabEngine_PATHS}")

  FIND_LIBRARY(CommonBase CommonBase
      DOC "AMILabEngine CommonBase library"
      PATHS ${AMILabEngine_BINARY_DIR}
      PATH_SUFFIXES 
        Bin/Debug
        Bin/Release
        CommonBase
        CommonBase/Debug
        CommonBase/Release
  )

  FIND_LIBRARY(Common Common
      DOC "AMILabEngine Common library"
      PATHS ${AMILabEngine_BINARY_DIR}
      PATH_SUFFIXES 
        Bin/Debug
        Bin/Release
        Common Common/Debug 
        Common/Release)

  FIND_LIBRARY(LanguageBase LanguageBase
      DOC "AMILabEngine LanguageBase library"
      PATHS ${AMILabEngine_BINARY_DIR}
      PATH_SUFFIXES 
        Bin/Debug
        Bin/Release
        LanguageBase LanguageBase/Debug LanguageBase/Release)

  FIND_LIBRARY(Language Language
      DOC "AMILabEngine Language library"
      PATHS ${AMILabEngine_BINARY_DIR}
      PATH_SUFFIXES 
        Bin/Debug
        Bin/Release
        Language Language/Debug Language/Release)

  FIND_LIBRARY(WrapCommon WrapCommon
      DOC "AMILabEngine WrapCommon library"
      PATHS ${AMILabEngine_BINARY_DIR}
      PATH_SUFFIXES 
        Bin/Debug
        Bin/Release
        Wrapping/WrapCommon 
        Wrapping/WrapCommon/Debug 
        Wrapping/WrapCommon/Release)

#   FIND_LIBRARY(WrapLanguage WrapLanguage
#       DOC "AMILabEngine WrapLanguage library"
#       PATHS ${AMILabEngine_BINARY_DIR}
#       PATH_SUFFIXES 
#         Bin/Debug
#         Bin/Release
#         Wrapping/WrapLanguage 
#         Wrapping/WrapLanguage/Debug 
#         Wrapping/WrapLanguage/Release)
# 
#   FIND_LIBRARY(Algorithms Algorithms
#       DOC "AMILabEngine Algorithms library"
#       PATHS ${AMILabEngine_BINARY_DIR}
#       PATH_SUFFIXES 
#         Bin/Debug
#         Bin/Release
#         Algorithms 
#         Algorithms/Debug 
#         Algorithms/Release)
# 
#   FIND_LIBRARY(Graphic Graphic
#       DOC "AMILabEngine Graphic library"
#       PATHS ${AMILabEngine_BINARY_DIR}
#       PATH_SUFFIXES 
#         Bin/Debug
#         Bin/Release
#         Graphic 
#         Graphic/Debug 
#         Graphic/Release)
# 
#   FIND_LIBRARY(AMILabEngine AMILabEngine
#       DOC "AMILabEngine AMILabEngine library"
#       PATHS ${AMILabEngine_BINARY_DIR}
#       PATH_SUFFIXES 
#         Bin/Debug
#         Bin/Release
#         AMILabEngine 
#         AMILabEngine/Debug 
#         AMILabEngine/Release)
# 
#   FIND_LIBRARY(wxParams wxParams
#       DOC "AMILabEngine wxParams library"
#       PATHS ${AMILabEngine_BINARY_DIR}
#       PATH_SUFFIXES 
#         binary_dir
#         binary_dir/Debug
#         binary_dir/Release
#       )

  IF (${KIT}_NEED_WX_WRAPPING)
    FIND_LIBRARY(WrapWxWidgets WrapWxWidgets
        DOC "AMILabEngine WrapWxWidgets library"
        PATHS ${AMILabEngine_BINARY_DIR}
        PATH_SUFFIXES 
          Bin/Debug
          Bin/Release
          Wrapping/WrapWxWidgets/
          Wrapping/WrapWxWidgets/Debug
          Wrapping/WrapWxWidgets/Release)
  ENDIF (${KIT}_NEED_WX_WRAPPING)

  IF (${KIT}_NEED_VTK_WRAPPING)
    FIND_LIBRARY(WrapVTK WrapVTK
        DOC "AMILabEngine WrapVTK library"
        PATHS ${AMILabEngine_BINARY_DIR}
        PATH_SUFFIXES 
          Bin/Debug
          Bin/Release
          Wrapping/WrapVTK
          Wrapping/WrapVTK/Debug
          Wrapping/WrapVTK/Release)
  ENDIF (${KIT}_NEED_VTK_WRAPPING)

#   FIND_LIBRARY(WrapInterface WrapInterface
#       DOC "AMILabEngine WrapInterface library"
#       PATHS ${AMILabEngine_BINARY_DIR}
#       PATH_SUFFIXES 
#         Bin/Debug
#         Bin/Release
#         Wrapping/WrapInterface
#         Wrapping/WrapInterface/Debug
#         Wrapping/WrapInterface/Release)
# 
#   FIND_LIBRARY(WrapImports WrapImports
#       DOC "AMILabEngine WrapImports library"
#       PATHS ${AMILabEngine_BINARY_DIR}
#       PATH_SUFFIXES 
#         Bin/Debug
#         Bin/Release
#         Wrapping/WrapImports
#         Wrapping/WrapImports/Debug
#         Wrapping/WrapImports/Release)
# 
#   FIND_LIBRARY(myVTK4 myVTK4
#       DOC "AMILabEngine myVTK4 library"
#       PATHS ${AMILabEngine_BINARY_DIR}
#       PATH_SUFFIXES 
#         Bin/Debug
#         Bin/Release
#         Algorithms/myVTK4
#         Algorithms/myVTK4/Debug
#         Algorithms/myVTK4/Release)

ENDIF(AMILabEngine_FOUND)
