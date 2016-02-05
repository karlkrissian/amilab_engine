

INCLUDE(${AMILabEngine_SOURCE_DIR}/../CMAKE/amilabengine_macros.cmake)


#
# Check existence of files to create
# if missing, add them to OUTPUT_LIST
# and to the list of missing elements
#
# needs:
#   GENERATED_DIR
#   ClassUsedName
#
# creates
#   ${MISSING_VAR} as list
#   NB_${MISSING_VAR}
#
MACRO( CHECK_WRAPPED_FILES ELTS_LIST MISSING_VAR)
  MESSAGE("MISSING_VAR=${MISSING_VAR}  ${ELTS_LIST}")
  FOREACH( elt  ${ELTS_LIST})
    ClassUsedName( elt m_elt )
    #MESSAGE("CHECK_WRAPPED_FILES for ${m_elt}")
    SET(SRC ${GENERATED_DIR}/wrap_${m_elt}.cpp)
    SET(HDR ${GENERATED_DIR}/wrap_${m_elt}.h)
    IF( DEFINED CLASSDEP_${m_elt})
      SET(DEPFILE ${CLASSDEP_${m_elt}})
      IF( (${DEPFILE} IS_NEWER_THAN ${HDR}) OR
          (${DEPFILE} IS_NEWER_THAN ${SRC}) )
        # NOT NEEDED --- rename file to force new creation
        #FILE(RENAME ${HDR} "${HDR}.old")
        #FILE(RENAME ${SRC} "${SRC}.old")
        SET(${MISSING_VAR} ${elt} ${${MISSING_VAR}})
      ENDIF( (${DEPFILE} IS_NEWER_THAN ${HDR}) OR
             (${DEPFILE} IS_NEWER_THAN ${SRC}) )
    ELSE( DEFINED CLASSDEP_${m_elt})
      IF( (NOT EXISTS ${HDR}) OR (NOT EXISTS ${SRC}))
        SET(${MISSING_VAR} ${elt} ${${MISSING_VAR}})
      ENDIF( (NOT EXISTS ${HDR}) OR (NOT EXISTS ${SRC}))
    ENDIF(DEFINED CLASSDEP_${m_elt})

  ENDFOREACH( elt ${ELTS_LIST}) 
  LIST(LENGTH  ${MISSING_VAR} NB_${MISSING_VAR})
  WRAP_MESSAGE("NB_${MISSING_VAR}=${NB_${MISSING_VAR}} '${${MISSING_VAR}}'")
  # save to file
  #MESSAGE("******************* saving list ${MISSING_VAR}.txt *******************")
  SAVE_LIST( "${${MISSING_VAR}}" ${GENERATED_DIR}/${MISSING_VAR}.txt)
ENDMACRO( CHECK_WRAPPED_FILES ELTS_LIST MISSING_VAR)


#-------------------------------------------------------------------------------
MACRO( UPDATE_OUTPUT_LIST ELTS_LIST)
  FOREACH( elt  ${ELTS_LIST})
    ClassUsedName( elt m_elt )
    SET(OUTPUT_LIST ${GENERATED_DIR}/wrap_${m_elt}.cpp ${OUTPUT_LIST})
    SET(OUTPUT_LIST ${GENERATED_DIR}/wrap_${m_elt}.h ${OUTPUT_LIST})
  ENDFOREACH( elt ${ELTS_LIST}) 
ENDMACRO( UPDATE_OUTPUT_LIST ELTS_LIST)

#-------------------------------------------------------------------------------
MACRO( UPDATE_FUNCTION_OUTPUT_LIST ELTS_LIST)
  FOREACH( elt  ${ELTS_LIST})
    FunctionUsedName( elt m_elt )
    SET(OUTPUT_LIST ${GENERATED_DIR}/wrap_${m_elt}.cpp ${OUTPUT_LIST})
    SET(OUTPUT_LIST ${GENERATED_DIR}/wrap_${m_elt}.h ${OUTPUT_LIST})
  ENDFOREACH( elt ${ELTS_LIST}) 
ENDMACRO( UPDATE_FUNCTION_OUTPUT_LIST ELTS_LIST)

