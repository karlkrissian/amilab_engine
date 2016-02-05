# - Find the Amifluid library
# This module searches for the Amifluid library .
#
# This module defines these variables:
#
#  AMIFLUID_FOUND
#      True if the Amifluid library was found
#  AMIFLUID_LIBRARY
#      The location of the Amifluid library
#  AMIFLUID_INCLUDE_DIR
#      The include directory of the Amifluid library
#
#

MESSAGE( " FindAMIFluid.cmake")

# typical root dirs of installations, exactly one of them is used
SET (AMIFLUID_POSSIBLE_ROOT_DIRS
  "$ENV{ProgramFiles}/libAMIFluid"
  "$ENV{HOME}/usr/local"
  /usr/local
  /usr
  )

#
#
FIND_PATH(AMIFLUID_ROOT_DIR
  NAMES
  include/AMIFluid/ami.h # linux /opt/net
  AMIFluid/include/ami.h # linux /opt/net
  PATHS ${AMIFLUID_POSSIBLE_ROOT_DIRS})


# header include dir suffixes appended to AMIFLUID_ROOT_DIR
SET(AMIFLUID_INCDIR_SUFFIXES
  include
  include/AMIFluid
  libAMIFluid/include/AMIFluid
  )

FIND_PATH(AMIFLUID_INCLUDE_DIR
  NAMES ami.h
  PATHS ${AMIFLUID_ROOT_DIR}
  PATH_SUFFIXES ${AMIFLUID_INCDIR_SUFFIXES} )

MESSAGE( " AMIFLUID_INCLUDE_DIR=${AMIFLUID_INCLUDE_DIR}")

# library linkdir suffixes appended to AMIFLUID_ROOT_DIR
SET(AMIFLUID_LIBDIR_SUFFIXES
  lib
  AMIFluid/lib
  lib/AMIFluid
  libAMIFluid/lib/AMIFluid
  )


SET(names AMIFluid)

FIND_LIBRARY(AMIFLUID_LIBRARY ${names}
    DOC "AMIFluid library"
    PATHS ${AMIFLUID_ROOT_DIR}
    PATH_SUFFIXES ${AMIFLUID_LIBDIR_SUFFIXES} )

MESSAGE( "CMAKE_SYSTEM_INCLUDE_PATH=${CMAKE_SYSTEM_INCLUDE_PATH}")


INCLUDE(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(AMIFLUID DEFAULT_MSG
    AMIFLUID_LIBRARY AMIFLUID_INCLUDE_DIR)

IF(AMIFLUID_INCLUDE_DIR AND AMIFLUID_LIBRARY)
    SET(AMIFLUID_INCLUDE_DIRS ${AMIFLUID_INCLUDE_DIR})
    SET(AMIFLUID_LIBRARIES    ${AMIFLUID_LIBRARY})
ENDIF(AMIFLUID_INCLUDE_DIR AND AMIFLUID_LIBRARY)


