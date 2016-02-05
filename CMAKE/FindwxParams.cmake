# - Find the wxParams library
# This module searches for the wxParams library .
#
# This module defines these variables:
#
#  wxParams_FOUND
#      True if the wxParams library was found
#  wxParams_LIBRARY
#      The location of the wxParams library
#  wxParams_INCLUDE_DIR
#      The include directory of the wxParams library
#
#



#
# Find the library
#

SET(names wxParams)
    
FIND_LIBRARY(wxParams_LIBRARY ${names}
    DOC "wxParams library")

FIND_PATH(wxParams_INCLUDE wxParams/wxParamTypes.hpp)
SET(wxParams_INCLUDE_DIR ${wxParams_INCLUDE})

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(wxParams DEFAULT_MSG
    wxParams_LIBRARY wxParams_INCLUDE_DIR)

IF(wxParams_INCLUDE_DIR AND wxParams_LIBRARY)
    SET(wxParams_INCLUDE_DIRS ${wxParams_INCLUDE_DIR}/wxParams)
    SET(wxParams_LIBRARIES    ${wxParams_LIBRARY})
ENDIF(wxParams_INCLUDE_DIR AND wxParams_LIBRARY)

#MARK_AS_ADVANCED(wxParams_INCLUDE_DIR)
#MARK_AS_ADVANCED(wxParams_LIBRARY)
