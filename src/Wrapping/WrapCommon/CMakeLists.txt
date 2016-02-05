# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found.  Any number of sources could be listed here.

SET(CURRENT_LIB WrapCommon)
#SET(WrapCommon_TYPE SHARED) 
SET(WrapCommon_TYPE STATIC) 

CONFIGURE_FILE(
    ${CMAKE_SOURCE_DIR}/libConfigure.h.in
    ${CMAKE_BINARY_DIR}/${CURRENT_LIB}Configure.h)

# Make sure the compiler can find include files from our Hello library.
include_directories (
  ${AMILABENGINE_SOURCE_DIR}/CommonBase
  ${AMILABENGINE_SOURCE_DIR}/Common/include
  ${AMILABENGINE_SOURCE_DIR}/LanguageBase
  ${Boost_INCLUDE_DIR}
  ${CMAKE_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}/Generated
)


IF(AMI_ENABLE_WRAPPING)
  #-----------------------------------------------------------------------------
  # Initialization
  #-----------------------------------------------------------------------------
  INCLUDE(${AMILABENGINE_SOURCE_DIR}/../CMAKE/amiWrapping.cmake)
  SET(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/Generated)
  SET(WRAPPING_DIR ${CMAKE_CURRENT_SOURCE_DIR})
  CreateDirectory( ${GENERATED_DIR})
  SET(LIBNAME "common")
  WRAP_INIT(" Common")

  #-----------------------------------------------------------------------------
  # Creating XML file
  #-----------------------------------------------------------------------------
  SET(GCCXML_FLAGS "")
  IF(WIN32)
    SET(GCCXML_FLAGS ${GCCXML_FLAGS} -D_WIN32 -DWIN32 -D_MSC_VER)
  ENDIF(WIN32)
  
  # Add Frameworks information
  IF(APPLE)
    SET(GCCXML_FLAGS ${GCCXML_FLAGS} -F /System/Library/Frameworks )
  ENDIF(APPLE)
  MESSAGE("GCCXML_FLAGS='${GCCXML_FLAGS}'")

  SET(XML_OUTPUT "${GENERATED_DIR}/common_includes.xml")
  SET(XML_INPUT  "${CMAKE_CURRENT_SOURCE_DIR}/common_includes.h")

  # Adding needed includes for wrapping ???
  SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILABENGINE_SOURCE_DIR}/Wrapping/include")
  SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILABENGINE_SOURCE_DIR}/Common/include")
  SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILABENGINE_SOURCE_DIR}/CommonBase")
  SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILABENGINE_SOURCE_DIR}/LanguageBase")
  SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${AMILABENGINE_SOURCE_DIR}/Language")
  SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${CMAKE_BINARY_DIR}")
  SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${PROJECT_SOURCE_DIR}")
  SET(GCCXML_INCLUDES ${GCCXML_INCLUDES} "-I${Boost_INCLUDE_DIR}")

  RUN_GCCXML( ${XML_INPUT} ${XML_OUTPUT})

  #-----------------------------------------------------------------------------
  # Setting up the Documentation information
  #-----------------------------------------------------------------------------
  IF(GENERATE_HTML_HELP)
    SET(CLASSES_URL_LIST "http://www.ctm.ulpgc.es/amilab_doxygen/3.2.0/html/")
    SET(HTML_DIR "${GENERATED_DIR}/html")
    CreateDirectory( ${HTML_DIR} )
  ENDIF(GENERATE_HTML_HELP)

  #-----------------------------------------------------------------------------
  # Generating the classes, functions, etc...  lists
  #-----------------------------------------------------------------------------
  READ_CLASSES(  "${CMAKE_CURRENT_SOURCE_DIR}/classes.txt"  ) 
  READ_FUNCTIONS("${CMAKE_CURRENT_SOURCE_DIR}/functions.txt")

  #-----------------------------------------------------------------------------
  # Generating and reading ancestors
  #-----------------------------------------------------------------------------
  CREATE_ANCESTORS()
  FILE(READ "${ANCESTORS_FILE}" ancestors_txt)
  STRING(REGEX REPLACE "[\r\n]" ";" ancestors_list ${ancestors_txt} )

  #-----------------------------------------------------------------------------
  # Checking for existing and missing files
  #-----------------------------------------------------------------------------
  # Wrap all missing classes at once since it is now fast
  #CHECK_WRAPPED_FILES( "${ancestors_list}"       "MISSING_CLASSES")
  UPDATE_OUTPUT_LIST( "${ancestors_list}"  )
  UPDATE_OUTPUT_LIST( "${functions_list}"  )

  #-----------------------------------------------------------------------------
  # Create the rule that wraps the code
  #-----------------------------------------------------------------------------
  WRAP_CODE()

ENDIF(AMI_ENABLE_WRAPPING)

FOREACH( class ${ancestors_list} ${functions_list}) 
  ClassUsedName( class m_class )
  SET( WrapCommon_HDRS ${GENERATED_DIR}/wrap_${m_class}.h ${WrapCommon_HDRS})
  SET( WrapCommon_SRCS ${GENERATED_DIR}/wrap_${m_class}.cpp ${WrapCommon_SRCS})
ENDFOREACH( class ${ancestors_list} ${functions_list}) 
SET( WrapCommon_HDRS ${GENERATED_DIR}/addwrap_common.h   ${WrapCommon_HDRS})
SET( WrapCommon_SRCS ${GENERATED_DIR}/addwrap_common.cpp ${WrapCommon_SRCS})

SET(  WrapCommon_SRCS
  ${WrapCommon_SRCS}
  wrapfunctions.cpp
  #  wrapfunctions_draw.cpp
  wrapfunction_class.cpp
)

SET(WrapCommon_HDRS
  ${WrapCommon_SRCS}
  #	wrapfunctions_draw.h
  ${CMAKE_BINARY_DIR}/${CURRENT_LIB}Configure.h
  ../include/wrapfunctions.hpp
  ../include/wrapfunctions.tpp
  ../include/wrapfunction_class.h
)

SET(WrapCommon_SRCS
     ${WrapCommon_SRCS}
     ${WrapCommon_HDRS}
     common_includes.h
     classes.txt
)

ADD_LIBRARY(${CURRENT_LIB} ${${CURRENT_LIB}_TYPE}  ${${CURRENT_LIB}_SRCS})

IF(CMAKE_COMPILER_IS_GNUCC)
  # TODO: set link for windows too
  TARGET_LINK_LIBRARIES( ${CURRENT_LIB}
    dl
  )
ENDIF(CMAKE_COMPILER_IS_GNUCC)

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
  SET_TARGET_PROPERTIES(${CURRENT_LIB} PROPERTIES COMPILE_FLAGS -fPIC)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
