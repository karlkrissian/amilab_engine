
# Prepare GCCXML to compile with wxwidgets
# by updating the variables GCCXML_INCLUDES and GCCXML_DEFS
MACRO( GCCXML_USE_WXWIDGETS )

  # wxwidgets compilation flags
  IF   (wxWidgets_FOUND)
    IF   (wxWidgets_INCLUDE_DIRS)
      FOREACH( inc ${wxWidgets_INCLUDE_DIRS})
        SET( GCCXML_WX_INCLUDES  -I${inc}  ${GCCXML_WX_INCLUDES} )
      ENDFOREACH(inc ${wxWidgets_INCLUDE_DIRS})
    ENDIF(wxWidgets_INCLUDE_DIRS)
    MESSAGE("GCCXML_WX_INCLUDES=${GCCXML_WX_INCLUDES}")

    IF   (wxWidgets_DEFINITIONS)
      FOREACH( def ${wxWidgets_DEFINITIONS})
        SET( GCCXML_WX_DEFS  -D${def}  ${GCCXML_WX_DEFS} )
      ENDFOREACH(def ${wxWidgets_DEFINITIONS})
      MESSAGE("wxWidgets_DEFINITIONS=${wxWidgets_DEFINITIONS}")
    ENDIF(wxWidgets_DEFINITIONS)

    IF   (wxWidgets_DEFINITIONS_DEBUG)
      FOREACH( def ${wxWidgets_DEFINITIONS_DEBUG})
        SET( GCCXML_WX_DEFS  -D${def} ${GCCXML_WX_DEFS} )
      ENDFOREACH(def ${wxWidgets_DEFINITIONS_DEBUG})
      MESSAGE("wxWidgets_DEFINITIONS_DEBUG=${wxWidgets_DEFINITIONS_DEBUG}")
    ENDIF(wxWidgets_DEFINITIONS_DEBUG)

    IF   (wxWidgets_CXX_FLAGS)
      SET(GCCXML_WX_FLAGS "${CMAKE_CXX_FLAGS} ${wxWidgets_CXX_FLAGS}")
      MESSAGE("GCCXML_WX_FLAGS=${GCCXML_WX_FLAGS}")
    ENDIF(wxWidgets_CXX_FLAGS)

    IF(WIN32)
      # fix a problem with wxWidgets 2.9.4 and unichar ...
      SET(GCCXML_DEFS ${GCCXML_DEFS} -D_NATIVE_WCHAR_T_DEFINED)
      SET(GCCXML_DEFS ${GCCXML_DEFS} -D__multiple_inheritance=)
    ENDIF(WIN32)

    # Update GCCXML variables
    SET( GCCXML_INCLUDES ${GCCXML_INCLUDES}  ${GCCXML_WX_INCLUDES})
    SET( GCCXML_DEFS     ${GCCXML_DEFS}      ${GCCXML_WX_DEFS}    )

  ENDIF (wxWidgets_FOUND)

ENDMACRO( GCCXML_USE_WXWIDGETS )

