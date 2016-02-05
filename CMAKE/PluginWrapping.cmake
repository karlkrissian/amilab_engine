#===============================================================================
# Plugin
#
# Description: Specifies since it is wrapped of the class Example.
#
# Author: xXx <xXX>, (C) 2010
#
# Copyright: See COPYING file that comes with this distribution
#===============================================================================

#MESSAGE("Find GCCXML...")

FIND_PACKAGE( GCCXML REQUIRED)

#MESSAGE("GCCXML found")
#MESSAGE("Begin wrapping...")

INCLUDE(${AMILabEngine_SOURCE_DIR}/../CMAKE/amiWrapping.cmake)
INCLUDE(${AMILabEngine_SOURCE_DIR}/../CMAKE/CHECK_WRAPPED_FILES.cmake)

# Setting WRAP_DIR
IF(EXISTS ${${KIT}_SOURCE_DIR}/src/Wrapping)
  SET(WRAP_DIR ${${KIT}_SOURCE_DIR}/src/Wrapping)
ELSE(EXISTS ${${KIT}_SOURCE_DIR}/src/Wrapping)
  IF(EXISTS ${${KIT}_SOURCE_DIR}/Wrapping)
    SET(WRAP_DIR ${${KIT}_SOURCE_DIR}/Wrapping)
  ELSE(EXISTS ${${KIT}_SOURCE_DIR}/Wrapping)
    IF(EXISTS ${PROJECT_SOURCE_DIR}/Wrapping)
      SET(WRAP_DIR ${PROJECT_SOURCE_DIR}/Wrapping)
    ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/Wrapping)

    IF(EXISTS ${PROJECT_SOURCE_DIR}/src/Wrapping)
      SET(WRAP_DIR ${PROJECT_SOURCE_DIR}/src/Wrapping)
    ENDIF(EXISTS ${PROJECT_SOURCE_DIR}/src/Wrapping)
  ENDIF(EXISTS ${${KIT}_SOURCE_DIR}/Wrapping)
ENDIF(EXISTS ${${KIT}_SOURCE_DIR}/src/Wrapping)

SET(GENERATED_DIR ${${KIT}_BINARY_DIR}/Wrapping/Generated)
IF( NOT EXISTS ${GENERATED_DIR})
  FILE(MAKE_DIRECTORY ${GENERATED_DIR})
ENDIF( NOT EXISTS ${GENERATED_DIR})

WRAP_INIT("Wrapping ${KIT}")

#-------------------------------------------------------------------------------
#  Generating XML file
#-------------------------------------------------------------------------------

SET(XML_OUTPUT "${GENERATED_DIR}/${KIT}_includes.xml")
SET(XML_INPUT  "${WRAP_DIR}/${KIT}_includes.h")

IF(${KIT}_NEED_VTK_WRAPPING)
  INCLUDE(${AMILab_SOURCE_DIR}/../CMAKE/amiWrapVTK.cmake)
  GCCXML_USE_VTK()
ENDIF(${KIT}_NEED_VTK_WRAPPING)

IF(${KIT}_NEED_WX_WRAPPING)
  INCLUDE(${AMILab_SOURCE_DIR}/../CMAKE/amiWrapWxWidgets.cmake)
  GCCXML_USE_WXWIDGETS()
ENDIF(${KIT}_NEED_WX_WRAPPING)

IF(${KIT}_NEED_ITK_WRAPPING)
  INCLUDE(${AMILab_SOURCE_DIR}/../CMAKE/amiWrapITK.cmake)
  GCCXML_USE_ITK()
ENDIF(${KIT}_NEED_ITK_WRAPPING)

# Adding KIT includes
IF(KIT)
  IF(${KIT}_INCLUDE_PATHS)
    WRAP_MESSAGE("************ ${KIT}_INCLUDE_PATHS = ${${KIT}_INCLUDE_PATHS}")
    FOREACH(path ${${KIT}_INCLUDE_PATHS})
      SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${path}")
    ENDFOREACH(path ${${KIT}_INCLUDE_PATHS})
  ENDIF(${KIT}_INCLUDE_PATHS)

  IF(${KIT}_INCLUDEFILES)
    WRAP_MESSAGE("************ ${KIT}_INCLUDEFILES = ${${KIT}_INCLUDEFILES}")
    FOREACH(file ${${KIT}_INCLUDEFILES})
      SET(GCCXML_INCLUDEFILES ${GCCXML_INCLUDEFILES} "-include" "${file}")
    ENDFOREACH(file ${${KIT}_INCLUDEFILES})
  ENDIF(${KIT}_INCLUDEFILES)

ENDIF(KIT)

SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILab_SOURCE_DIR}/Wrapping/include")
SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILab_SOURCE_DIR}/Common/include")
SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILab_SOURCE_DIR}/CommonBase")
SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILab_SOURCE_DIR}/LanguageBase")
SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILab_BINARY_DIR}")
SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${PROJECT_SOURCE_DIR}")
SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${Boost_INCLUDE_DIR}")

RUN_GCCXML(${XML_INPUT} ${XML_OUTPUT})

#-------------------------------------------------------------------------------
# Create Ancestors
#-------------------------------------------------------------------------------

# Need python interpreter
FIND_PACKAGE( PythonInterp REQUIRED)

# Read list of classes to wrap
READ_CLASSES(  "${WRAP_DIR}/classes.txt")
# Read list of functions to wrap
READ_FUNCTIONS("${WRAP_DIR}/functions.txt")

SET(WRAPPING_DIR ${WRAP_DIR})

SET(LIBNAME "${KIT}")
SET(GENERATE_HTML_HELP ${${KIT}_GENERATE_HTML_HELP})
CREATE_ANCESTORS()

IF(EXISTS ${ANCESTORS_FILE})
  FILE(READ "${ANCESTORS_FILE}" ancestors_txt)
  STRING(REGEX REPLACE "[\r\n]" ";" ancestors_list ${ancestors_txt} )
ELSE(EXISTS ${ANCESTORS_FILE})
  SET(ancestors_list "")
ENDIF(EXISTS ${ANCESTORS_FILE})

#-------------------------------------------------------------------------------
# Checking for existing and missing files
#-------------------------------------------------------------------------------

MESSAGE("functions_list = ${functions_list}")

UPDATE_OUTPUT_LIST( "${ancestors_list}"     )
UPDATE_FUNCTION_OUTPUT_LIST( "${functions_list}"     )
UPDATE_FUNCTION_OUTPUT_LIST( "${methodpointers_list}")

FOREACH( MP ${methodpointers_list})
  SET( methodpointers_files ${methodpointers_files} ${GENERATED_DIR}/wrap_${MP}.h ${GENERATED_DIR}/wrap_${MP}.cpp )
ENDFOREACH( MP ${methodpointers_list})

#-------------------------------------------------------------------------------
# Create the rule that wraps the code
#-------------------------------------------------------------------------------

IF(${KIT}_GENERATE_HTML_HELP)
  SET(GENERATE_HTML_HELP ${KIT}_GENERATE_HTML_HELP)
ENDIF(${KIT}_GENERATE_HTML_HELP)

WRAP_CODE()


#     SET(MYCOMMAND_3 ${PYTHON_EXECUTABLE})
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} ${AMI_WRAPPER})
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} ${XML_OUTPUT})
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "--libname" "${KIT}")
#     #SET(MYCOMMAND_3 ${MYCOMMAND_3} "--filter" "\"wx*\"")
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "--classes" ${MISSING_CLASSES})
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "--available_classes" ${ancestors_list})
#     IF(DEFINED AVAILABLE_EXTERNAL_CLASSES)
#       WRAP_MESSAGE("***** available external classes *****")
#       SET(MYCOMMAND_3 ${MYCOMMAND_3} "--available_external_classes" ${AVAILABLE_EXTERNAL_CLASSES})
#     ENDIF(DEFINED AVAILABLE_EXTERNAL_CLASSES)
#     IF(DEFINED HAS_FUNCTIONS)
#       SET(MYCOMMAND_3 ${MYCOMMAND_3} "--functions" ${MISSING_FUNCTIONS})
#       SET(MYCOMMAND_3 ${MYCOMMAND_3} "--available_functions" ${functions_list})
#     ENDIF(DEFINED HAS_FUNCTIONS)
#     IF(EXISTS ${WRAP_DIR}/classes_includes.py)
#       SET(MYCOMMAND_3 ${MYCOMMAND_3} "--classes_includes" ${WRAP_DIR}/classes_includes.py)
#     ENDIF(EXISTS ${WRAP_DIR}/classes_includes.py)
#     IF(EXISTS ${WRAP_DIR}/members_blacklist.py)
#       SET(MYCOMMAND_3 ${MYCOMMAND_3} "--members_blacklist" ${WRAP_DIR}/members_blacklist.py)
#     ENDIF(EXISTS ${WRAP_DIR}/members_blacklist.py)
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "--outputdir" ${GENERATED_DIR})
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "--profile")
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "--templates")
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "--templatefile_dir" ${AMILab_SOURCE_DIR}/../PythonWrap/)
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "--addwrap")
#     SET(MYCOMMAND_3 ${MYCOMMAND_3} "-q")
#     IF(${KIT}_GENERATE_HTML_HELP)
#       # flag to generate html help
#       SET(MYCOMMAND_3 ${MYCOMMAND_3} "--generate-html")
#       IF(CLASSES_URL_LIST)
#         # base URL html help
#         SET(MYCOMMAND_3 ${MYCOMMAND_3} "--url" "${CLASSES_URL_LIST}")
#       ENDIF(CLASSES_URL_LIST)
#         IF(HTML_DIR)
#         #HTML directory
#       SET(MYCOMMAND_3 ${MYCOMMAND_3} "--outputhtmldir" ${HTML_DIR})
#       ENDIF(HTML_DIR)
#     ENDIF(${KIT}_GENERATE_HTML_HELP)
# 
#     WRAP_MESSAGE("COMMAND 3: ${MYCOMMAND_3}")
#     ADD_CUSTOM_COMMAND(
#       OUTPUT
#         ${OUTPUT_LIST} ${methodpointers_list} 
#         ${GENERATED_DIR}/addwrap_${KIT}.h
#         ${GENERATED_DIR}/addwrap_${KIT}.cpp
#       COMMAND
#         ${MYCOMMAND_3}
#       DEPENDS
#         ${WRAP_DIR}/classes.txt
#       VERBATIM
#     )


#-------------------------------------------------------------------------------

  FOREACH( class ${ancestors_list} ${functions_list} )
    ClassUsedName( class m_class )
    SET( ${KIT}_HDRS 
          ${GENERATED_DIR}/wrap_${m_class}.h ${${KIT}_HDRS})
    SET( ${KIT}_SRCS 
          ${GENERATED_DIR}/wrap_${m_class}.cpp ${${KIT}_SRCS})
  ENDFOREACH( class ${ancestors_list} )

  SET( ${KIT}_HDRS 
      ${GENERATED_DIR}/addwrap_${KIT}.h
      ${${KIT}_HDRS})

  SET( ${KIT}_SRCS 
      ${GENERATED_DIR}/addwrap_${KIT}.cpp 
      ${${KIT}_SRCS})

#MESSAGE("${KIT}_HDR = ${${KIT}_HDR}")
#   ENDIF(MYCOMMAND_2_RESULT)

WRAP_MESSAGE("End wrapping")
