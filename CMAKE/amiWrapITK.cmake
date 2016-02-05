
# Prepare GCCXML to compile with VTK
# by updating the variables GCCXML_INCLUDES and GCCXML_DEFS
MACRO( GCCXML_USE_ITK )

  IF   (ITK_FOUND)
    IF   (ITK_INCLUDE_DIRS)
      WRAP_MESSAGE("ITK_INCLUDE_DIRS = ${ITK_INCLUDE_DIRS}")
      FOREACH( inc ${ITK_INCLUDE_DIRS})
        SET( GCCXML_ITK_INCLUDES  -I${inc}  ${GCCXML_ITK_INCLUDES} )
        SET( GCCXML_ITK_INCLUDES  -I${inc}/vnl  ${GCCXML_ITK_INCLUDES} )
        IF (inc MATCHES ".*Utilities$")
          SET(ITK_UTILITIES_PATH ${inc})
        ENDIF(inc MATCHES ".*Utilities$")
      ENDFOREACH(inc ${ITK_INCLUDE_DIRS})
      WRAP_MESSAGE("ITK_UTILITIES_PATH = ${ITK_UTILITIES_PATH}")
      # for unknown reasons I had to add those two directories
      SET( GCCXML_ITK_INCLUDES ${GCCXML_ITK_INCLUDES} -I${ITK_UTILITIES_PATH}/vxl/vcl/iso/)
      SET( GCCXML_ITK_INCLUDES ${GCCXML_ITK_INCLUDES} -I${ITK_UTILITIES_PATH}/vxl/core/vnl/)
      SET( GCCXML_ITK_INCLUDES ${GCCXML_ITK_INCLUDES} -I${ITK_UTILITIES_PATH}/vxl/core/generic/)
      #SET( GCCXML_ITK_INCLUDES -I/home/karl/projects/Install/amilab/InsightToolkit-3.20.0/Utilities/vxl/vcl/generic/ ${GCCXML_ITK_INCLUDES} )
      #SET( GCCXML_ITK_INCLUDES -I/home/karl/projects/Install/amilab/InsightToolkit-3.20.0/Utilities/vxl/core/vnl/ ${GCCXML_ITK_INCLUDES} )
    ENDIF(ITK_INCLUDE_DIRS)
     IF   (ITK_REQUIRED_CXX_FLAGS)
       FOREACH( def ${ITK_REQUIRED_CXX_FLAGS})
         SET( GCCXML_ITK_DEFS  ${def}  ${GCCXML_ITK_DEFS} )
       ENDFOREACH(def ${ITK_REQUIRED_CXX_FLAGS})       
     ENDIF(ITK_REQUIRED_CXX_FLAGS)

     # Add Cable configuration for gccxml compilation ?
     SET(GCCXML_ITK_DEFS ${GCCXML_ITK_DEFS} -DCABLE_CONFIGURATION  )
     SET(GCCXML_ITK_DEFS ""  )

     WRAP_MESSAGE("GCCXML_ITK_DEFS=${GCCXML_ITK_DEFS}")
  ENDIF ( ITK_FOUND)

  # Update GCCXML variables
  SET( GCCXML_INCLUDES ${GCCXML_INCLUDES}  ${GCCXML_ITK_INCLUDES})
  SET( GCCXML_DEFS     ${GCCXML_DEFS}      ${GCCXML_ITK_DEFS}    )

ENDMACRO( GCCXML_USE_ITK )

