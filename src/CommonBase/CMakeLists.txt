# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found.  Any number of sources could be listed here.

# Make sure the compiler can find include files from our Hello library.
include_directories (
  ${AMILAB_SOURCE_DIR}/CommonBase/include
)

#INCLUDE( ${wxWidgets_USE_FILE})

SET(CommonBase_SRCS
  ami_format.cpp
  AmiMessage.cpp
  amilab_messages.cpp
  StringUtils.cpp
  Timing.cpp 
)

SET(CommonBase_HDRS
  AmiMessage.h
  amilab_boost.h
  amilab_messages.h
  ami_format.h
  CommonBaseConfigure.h
  std_common.h
  StringUtils.hpp
  Timing.hpp
)

IF(WIN32)
  set_source_files_properties(${CommonBase_SRCS} PROPERTIES COMPILE_FLAGS "-DCommonBase_EXPORTS")
ENDIF(WIN32)

SET (CommonBase_SRCS
     ${CommonBase_SRCS}
     ${CommonBase_HDRS}
)



# own macro to add the library and print the source files
# using xxx_SRCS variable
#my_add_shared_library (Common)
my_add_library (CommonBase)


target_link_libraries(CommonBase
  ${Boost_LIBRARIES}
)

IF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
  SET_TARGET_PROPERTIES(CommonBase PROPERTIES COMPILE_FLAGS -fPIC)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
