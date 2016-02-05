# - Find the OpticFlow library
# defined OPTICFLOW_INCLUDE_DIRS
#
#

# typical root dirs of installations, exactly one of them is used
SET (OPTICFLOW_POSSIBLE_ROOT_DIRS
  "$ENV{ProgramFiles}/libAMIOpticalFlow"
  "$ENV{HOME}/usr/local"
  /usr/local
  /usr
  )

#
#
FIND_PATH(OPTICFLOW_ROOT_DIR
  NAMES
  include/OpticalFlow/optic_flow.h 
  PATHS ${OPTICFLOW_POSSIBLE_ROOT_DIRS})


MESSAGE("OPTICFLOW_ROOT_DIR=${OPTICFLOW_ROOT_DIR}")

  # header include dir suffixes appended to AMIFLUID_ROOT_DIR
SET(OPTICFLOW_INCDIR_SUFFIXES
  include
  include/OpticalFlow
  libAMIOpticalFlow/include/OpticalFlow
  )

#
# Find the header file
#
FIND_PATH(OPTICFLOW_INCLUDE_DIR OpticalFlow/optic_flow.h
	PATHS ${OPTICFLOW_ROOT_DIR}
	PATH_SUFFIXES ${OPTICFLOW_INCDIR_SUFFIXES} )

#
# Find the library
#


INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(OpticFlow DEFAULT_MSG
     AMIFLUID_INCLUDE_DIR)

IF(OPTICFLOW_INCLUDE_DIR )
    SET(OPTICFLOW_INCLUDE_DIRS ${OPTICFLOW_INCLUDE_DIR})
ENDIF(OPTICFLOW_INCLUDE_DIR)

#MARK_AS_ADVANCED(AMIFLUID_INCLUDE_DIR)
#MARK_AS_ADVANCED(AMIFLUID_LIBRARY)
