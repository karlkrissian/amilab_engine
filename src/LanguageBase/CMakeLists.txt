# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found.  Any number of sources could be listed here.



# Make sure the compiler can find include files from our Hello library.
include_directories (
  ${AMILABENGINE_SOURCE_DIR}/CommonBase
  ${AMILABENGINE_SOURCE_DIR}/Common/include
  ${AMILABENGINE_SOURCE_DIR}/LanguageBase
  ${AMILABENGINE_SOURCE_DIR}/Wrapping/include
  ${AMILab_BINARY_DIR}/Wrapping/WrapCommon/Generated
)

# Difficult to avoid wxwidgets: used in Variables.cpp

SET(LanguageBase_SRCS
    ami_object.cpp
	BasicVariable.cpp
    CallBackAMIFunction.cpp
    DriverBase.cpp
    languagebase_global_export.cpp
    paramlist.cpp
    VarArray.cpp
    VarContexts.cpp
    Variable.cpp
    Variable_AMIObject.cpp
    Variable_bool.cpp
    Variable_double.cpp
    Variable_float.cpp
    Variable_short.cpp
    Variable_ushort.cpp
    Variable_int.cpp
    Variable_long.cpp
    Variable_ulong.cpp
#    Variable_string.cpp
    Variable_uchar.cpp
    Variable_WrapClassMember.cpp
    Variables.cpp
    TypeConversion.cpp

#    VarContexts.cpp
#    ImageStack.cpp
#    VarArray.cpp
#    driver.cc
#    language_global_export.cpp
)

SET(LanguageBase_HDRS
  ami_class.h
  ami_function.h
  ami_object.h
  AmiInstructionBlock.h
  BasicVariable.h
  CallBackAMIFunction.h
  DriverBase.h
  IdentifierInfo.h
  languagebase_global_import.h
  LanguageBaseConfigure.h
  paramlist.h
  VarArray.h
  VarContexts.hpp
  VarContexts.tpp
  Variable.hpp
  Variable.tpp
  Variable_AMIObject.h
  Variable_bool.h
  Variable_double.h
  Variable_float.h
  Variable_short.h
  Variable_ushort.h
  Variable_int.h
  Variable_long.h
  Variable_ulong.h
#  Variable_string.h
  Variable_uchar.h
  Variable_WrapClassMember.h
  Variables.hpp
  vartype.h
  TypeConversion.h
)

# IF(WIN32 OR APPLE)
  OPTION(LanguageBase_SHARED     "Compile LanguageBase library as shared" ON)
# ELSE(WIN32)
#   OPTION(LanguageBase_SHARED     "Compile LanguageBase library as shared" OFF)
# ENDIF(WIN32 OR APPLE)

 
IF(LanguageBase_SHARED)
  set_source_files_properties(${Language_SRCS} PROPERTIES COMPILE_FLAGS "-DLanguageBase_EXPORTS")
ENDIF(LanguageBase_SHARED)

SET(LanguageBase_SRCS
 ${LanguageBase_SRCS}
 ${LanguageBase_HDRS}
)
 

IF (LanguageBase_SHARED)
  my_add_shared_library ( LanguageBase)
  INSTALL(TARGETS LanguageBase
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    #  COMPONENT applications
    #  BUNDLE DESTINATION 
    #${CMAKE_INSTALL_DESTINATION_ARGS}
  )
  IF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
    SET_TARGET_PROPERTIES(LanguageBase PROPERTIES COMPILE_FLAGS -fPIC)
  ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
ELSE(LanguageBase_SHARED)
  my_add_library ( LanguageBase)
ENDIF(LanguageBase_SHARED)


MESSAGE("LanguageBase Boost_LIBRARIES=${Boost_LIBRARIES}")
target_link_libraries(LanguageBase 
  CommonBase
  Common
  WrapCommon
  ${Boost_LIBRARIES}
#   ${ZLIB_LIBRARIES} # need to add it for MacOS ??
)

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
  SET_TARGET_PROPERTIES(LanguageBase PROPERTIES COMPILE_FLAGS -fPIC)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)

SET(LanguageBase_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR})
MESSAGE("LanguageBase binary directory = ${CMAKE_CURRENT_BINARY_DIR}")

#MESSAGE("CMAKE_LIBRARY_ARCHITECTURE=${CMAKE_LIBRARY_ARCHITECTURE}")

MESSAGE("LIB_INSTALL_DIR=${LIB_INSTALL_DIR}")

INSTALL(TARGETS LanguageBase
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib/amilabengine-${AMILABENGINE_VERSION}
  LIBRARY DESTINATION lib/amilabengine-${AMILABENGINE_VERSION}
)


add_dependencies ( LanguageBase
  WrapCommon # dependency because of wrap_ImageExtent ...
)
