# - Find the NewNLMeans library
# This module searches for the NewNLMeans library .
#
# This module defines these variables:
#
#  NewNLMeans_FOUND
#      True if the NewNLMeans library was found
#  NewNLMeans_LIBRARIES
#      The location of the NewNLMeans libraries
#  NewNLMeans_INCLUDE_DIRS
#      The include directories of the NewNLMeans library
#
#

MACRO(DBG_MSG _MSG)
  #  MESSAGE(STATUS "${CMAKE_CURRENT_LIST_FILE}(${CMAKE_CURRENT_LIST_LINE}):\n${_MSG}")
ENDMACRO(DBG_MSG)

#
# Find the header file
#
#FIND_PATH(NewNLMeans_INCLUDE_DIR ami.h)

#
# Find the library
#



# typical root dirs of installations, exactly one of them is used
SET (NewNLMeans_POSSIBLE_ROOT_DIRS
  "$ENV{ProgramFiles}/NewNLMeans"
  /usr/local
  /usr
  )


#
#
FIND_PATH(NewNLMeans_ROOT_DIR
  NAMES
  include/NewNLmeans.h     # windows
  include/NewNLMeans/NewNLmeans.h # linux /opt/net
  NewNLMeans/include/NewNLmeans.h # linux /opt/net
  PATHS ${NewNLMeans_POSSIBLE_ROOT_DIRS})

DBG_MSG( " NewNLMeans_ROOT_DIR=${NewNLMeans_ROOT_DIR}")

# header include dir suffixes appended to OpenCV_ROOT_DIR
SET(NewNLMeans_INCDIR_SUFFIXES
  include
  include/NewNLMeans
  NewNLMeans/include/NewNLMeans
  )

FIND_PATH(NewNLMeans_INCLUDE_DIR
  NAMES NewNLmeans.h
  PATHS ${NewNLMeans_ROOT_DIR}
  PATH_SUFFIXES ${NewNLMeans_INCDIR_SUFFIXES} )

DBG_MSG( " NewNLMeans_INCLUDE_DIR ${NewNLMeans_INCLUDE_DIR}")

# library linkdir suffixes appended to OpenCV_ROOT_DIR
SET(NewNLMeans_LIBDIR_SUFFIXES
  lib
  NewNLMeans/lib
  lib/NewNLMeans
  NewNLMeans/lib/NewNLMeans
  )

set(libnewnlmeans NewNLMeans_${CMAKE_BUILD_TYPE})

SET(names ${libnewnlmeans})

FIND_LIBRARY(NewNLMeans_LIBRARY ${names}
    DOC "NewNLMeans library"
    PATHS ${NewNLMeans_ROOT_DIR}
    PATH_SUFFIXES ${NewNLMeans_LIBDIR_SUFFIXES} )

DBG_MSG( "CMAKE_SYSTEM_INCLUDE_PATH=${CMAKE_SYSTEM_INCLUDE_PATH}")


INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(NewNLMeans DEFAULT_MSG
    NewNLMeans_LIBRARY NewNLMeans_INCLUDE_DIR)

IF(NewNLMeans_INCLUDE_DIR AND NewNLMeans_LIBRARY)
    SET(NewNLMeans_INCLUDE_DIRS ${NewNLMeans_INCLUDE_DIR})
    SET(NewNLMeans_LIBRARIES    ${NewNLMeans_LIBRARY})
ENDIF(NewNLMeans_INCLUDE_DIR AND NewNLMeans_LIBRARY)

