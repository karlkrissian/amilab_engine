

MESSAGE("***** executing RUN_DEPENDCIES.cmake *****")

# need as parameters
#   AMILAB_SOURCE_DIR
#   ...

#MESSAGE("AMILAB_SOURCE_DIR=${AMILAB_SOURCE_DIR}")

INCLUDE(${AMILabEngine_SOURCE_DIR}/../CMAKE/amilabengine_macros.cmake)
INCLUDE(${AMILabEngine_SOURCE_DIR}/../CMAKE/amiWrapping.cmake)
INCLUDE(${AMILabEngine_SOURCE_DIR}/../CMAKE/CHECK_WRAPPED_FILES.cmake)

#MESSAGE("AMILAB_SOURCE_DIR=${AMILAB_SOURCE_DIR}")

# reads ancestors_list
IF(EXISTS "${GENERATED_DIR}/ancestors.txt")
  SET(ANCESTORS_FILE "${GENERATED_DIR}/ancestors.txt")
  FILE(READ "${ANCESTORS_FILE}" ancestors_txt)
  STRING(REGEX REPLACE "[\r\n]" ";" ancestors_list ${ancestors_txt} )
ENDIF(EXISTS "${GENERATED_DIR}/ancestors.txt")

# Check for dependencies
CREATE_ANCESTORS_DEPS()

CHECK_WRAPPED_FILES( "${ancestors_list}"       "MISSING_CLASSES")


IF(EXISTS "${WRAPPING_DIR}/functions.txt")
  # Read list of functions to wrap
  READ_FUNCTIONS("${WRAPPING_DIR}/functions.txt")
ENDIF(EXISTS "${WRAPPING_DIR}/functions.txt")
CHECK_WRAPPED_FILES( "${functions_list}"       "MISSING_FUNCTIONS")


IF(EXISTS "${WRAPPING_DIR}/methodpointers.txt")
  # Read list of method pointers to wrap
  FILE(READ "${WRAPPING_DIR}/methodpointers.txt" methodpointers_txt)
  IF(methodpointers_txt)
    STRING(REGEX REPLACE "[\r\n]" ";" methodpointers_list 
            ${methodpointers_txt} )
  ENDIF(methodpointers_txt)
ELSE(EXISTS "${WRAPPING_DIR}/methodpointers.txt")
  SET(methodpointers_list "")
ENDIF(EXISTS "${WRAPPING_DIR}/methodpointers.txt")
CHECK_WRAPPED_FILES( "${methodpointers_list}"  "MISSING_METHODS")

