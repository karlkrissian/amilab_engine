
INCLUDE(${AMILabEngine_SOURCE_DIR}/../CMAKE/CHECK_WRAPPED_FILES.cmake)

#-------------------------------------------------------------------------------
#
# needs 
#  GENERATED_DIR
#  LIBNAME
#
MACRO(WRAP_INIT mess)
  # reset log file
  IF(DEFINED GENERATED_DIR)
    FILE(WRITE ${GENERATED_DIR}/Wrapping.log "" )
  ENDIF(DEFINED GENERATED_DIR)
  WRAP_MESSAGE("***************************")
  WRAP_MESSAGE(" ${mess}")
  IF(DEFINED LIBNAME)
    WRAP_MESSAGE(" Configuring wrapping for library ${LIBNAME}")
  ENDIF(DEFINED LIBNAME)
  WRAP_MESSAGE("***************************")
  MESSAGE("Details in '${GENERATED_DIR}/Wrapping.log'")
ENDMACRO(WRAP_INIT)

#-------------------------------------------------------------------------------
#
# needs GENERATED_DIR
#
MACRO(WRAP_MESSAGE mess)
  SET(MAXLENGTH 50)
  STRING(LENGTH "${mess}" mess_length)
  IF (${mess_length} GREATER ${MAXLENGTH})
    # troncate message
    string(SUBSTRING "${mess}" 0 ${MAXLENGTH} mess_troncated)
    MESSAGE("${mess_troncated}[...]")
  ELSE (${mess_length} GREATER ${MAXLENGTH})
    MESSAGE("${mess}")
  ENDIF (${mess_length} GREATER ${MAXLENGTH})
  # APPEND TO LOG FILE
  IF(DEFINED GENERATED_DIR)
    FILE(APPEND ${GENERATED_DIR}/Wrapping.log ${mess} )
    FILE(APPEND ${GENERATED_DIR}/Wrapping.log "\n" )
  ENDIF(DEFINED GENERATED_DIR)
ENDMACRO(WRAP_MESSAGE mess)

#-------------------------------------------------------------------------------
#
# Running gccxml command for amilab wrapping
#
MACRO( RUN_GCCXML XML_INPUT XML_OUTPUT)

  WRAP_MESSAGE("Try to generate XML file ${XML_OUTPUT}")

#   SET(GCCXML_CMD ${GCCXML}   )
   SET(GCCXML_CMD castxml -x c++ --castxml-gccxml -v -std=c++98 -fopenmp=libomp )
#-I/usr/include/c++/5.3.1/ -I/usr/include/c++/5.3.1/x86_64-redhat-linux )

  # remove duplicates
  LIST(REMOVE_DUPLICATES GCCXML_INCLUDES)
  IF(GCCXML_DEFS)
    LIST(REMOVE_DUPLICATES GCCXML_DEFS)
  ENDIF(GCCXML_DEFS)


  # Adding the GCCXML includes and flags required
  SET(GCCXML_CMD ${GCCXML_CMD} "${GCCXML_INCLUDES}")
  IF(GCCXML_DEFS)
    SET(GCCXML_CMD ${GCCXML_CMD} "${GCCXML_DEFS}")
  ENDIF(GCCXML_DEFS)
  IF(GCCXML_INCLUDEFILES)
    SET(GCCXML_CMD ${GCCXML_CMD} "${GCCXML_INCLUDEFILES}")
  ENDIF(GCCXML_INCLUDEFILES)
  
  SET(GCCXML_CMD ${GCCXML_CMD} ${XML_INPUT})
  
  IF(WIN32)
    IF(CMAKE_CL_64)
      # this requires to comment line 81 in gccxml-0.9\Vc9\PlatformSDK\WinNT.h
      SET(GCCXML_CMD ${GCCXML_CMD} -D_WIN64 -D_AMD64_)
    ENDIF(CMAKE_CL_64)
  ENDIF(WIN32)

  # Write the command to the standard output for information
  FOREACH( C ${GCCXML_CMD})
    SET( GCCXML_CMD_TXT "${GCCXML_CMD_TXT} '${C}'")
  ENDFOREACH( C ${GCCXML_CMD})
  WRAP_MESSAGE("COMMAND: ${GCCXML_CMD_TXT}")

  WRAP_MESSAGE("Running macros")
  # Execute the command to get a file of all the macros
  EXECUTE_PROCESS(
    COMMAND ${GCCXML_CMD} -E -dM
    OUTPUT_VARIABLE GCCXML_MACROS
  )
  FILE(WRITE "${XML_OUTPUT}.macros" ${GCCXML_MACROS} )
  
  WRAP_MESSAGE("Running gccxml")
  # Execute the command
  EXECUTE_PROCESS(
    COMMAND ${GCCXML_CMD}  -o ${XML_OUTPUT}
    RESULT_VARIABLE GCCXML_CMD_RESULT
    OUTPUT_VARIABLE GCCXML_CMD_OUTPUT
    ERROR_VARIABLE  GCCXML_CMD_ERROR
  )

  WRAP_MESSAGE("GCCXML done")

  IF(GCCXML_CMD_RESULT)
    MESSAGE(SEND_ERROR "Failed the generation of XML: ${GCCXML_CMD_ERROR} - ${GCCXML_CMD_RESULT}")
  ENDIF(GCCXML_CMD_RESULT)
  WRAP_MESSAGE("GCCXML output: ${GCCXML_CMD_OUTPUT}")
  WRAP_MESSAGE("GCCXML error:  ${GCCXML_CMD_ERROR}")

ENDMACRO( RUN_GCCXML )

#-------------------------------------------------------------------------------
#
# Read the list of classes
#
# input:  filename containing the list of classes to wrap
# output: classes_txt classes_list HAS_CLASSES
#
MACRO( READ_CLASSES filename)
  #MESSAGE("READ_CLASSES *")
  # Read list of classes to wrap
  IF(EXISTS ${filename})
    #MESSAGE("READ_CLASSES *")
    FILE(READ "${filename}" classes_txt)
    # skip comments
    STRING(REGEX REPLACE "#[^\n]*\n" "\n"  classes_list_cleaned 
                          ${classes_txt} )
    STRING(REGEX REPLACE "#[^\n]*$"  ""    classes_list_cleaned 
                          ${classes_list_cleaned} )
    STRING(REGEX REPLACE "[\r\n]" ";" classes_list ${classes_list_cleaned} )
    SET(HAS_CLASSES "1")
  ENDIF(EXISTS ${filename})
ENDMACRO( READ_CLASSES )

#-------------------------------------------------------------------------------
#
# Read the list of classes including a common list for all versions of the 
# library
#
# input:  filename containing the list of classes to wrap
# output: classes_txt classes_list HAS_CLASSES
#
MACRO( READ_CLASSES2 filename_common filename)
  # Read list of classes to wrap
  IF(EXISTS ${filename_common})
    FILE(READ "${filename_common}" classes_common_txt)
    # skip comments
    STRING(REGEX REPLACE "#[^\n]*\n" "\n"  classes_common_list_cleaned 
                          ${classes_common_txt} )
    STRING(REGEX REPLACE "#[^\n]*$"  ""    classes_common_list_cleaned 
                          ${classes_common_list_cleaned} )
    STRING(REGEX REPLACE "[\r\n]" ";" classes_common_list 
                          ${classes_common_list_cleaned} )
    SET(HAS_CLASSES "1")
  ENDIF(EXISTS ${filename_common})
  READ_CLASSES(${filename})
  SET( classes_list ${classes_common_list} ${classes_list})
  #MESSAGE("classes_list = ${classes_list}")
ENDMACRO( READ_CLASSES2 )

#-------------------------------------------------------------------------------
#
# Read the list of functions
#
# input:  filename containing the list of functions to wrap
# output: functions_txt functions_list HAS_FUNCTIONS
#
MACRO( READ_FUNCTIONS filename)
MESSAGE("READ_FUNCTIONS ${filename}")
  # Read list of functions to wrap
  IF(EXISTS ${filename})
  MESSAGE("filename exists")
    FILE(READ "${filename}" functions_txt)
    # skip comments
    STRING(REGEX REPLACE "#[^\n]*\n" "\n"  functions_list_cleaned ${functions_txt} )
    STRING(REGEX REPLACE "#[^\n]*$"  ""    functions_list_cleaned ${functions_list_cleaned} )
    #STRING(REGEX REPLACE "\n#[^\n]*\n" "\n" functions_list_cleaned ${functions_list_cleaned} )
    STRING(REGEX REPLACE "[\r\n]" ";" functions_list ${functions_list_cleaned} )
    WRAP_MESSAGE("functions_list = ${functions_list}")
  MESSAGE("found = ${functions_list}")
    SET(HAS_FUNCTIONS "1")
  ENDIF(EXISTS ${filename})
ENDMACRO( READ_FUNCTIONS )


#-------------------------------------------------------------------------------
#
# Create ancestors file
#
# needs:
#   GENERATED_DIR
#   AMILabEngine_SOURCE_DIR
#   PYTHON_EXECUTABLE
#   XML_OUTPUT
#   LIBNAME
#   AVAILABLE_EXTERNAL_CLASSES (optional)
#   AVAILABLE_EXTERNAL_CLASSES2 (optional)
#   GENERATE_HTML_HELP
#   CLASSES_URL_LIST
#   HTML_DIR
#
# outputs:
#   ANCESTORS_CMD_RESULT
#   ANCESTORS_CMD_ERROR
#
MACRO( CREATE_ANCESTORS )
  SET(ANCESTORS_FILE "${GENERATED_DIR}/ancestors.txt")
  SET(AMI_WRAPPER "${AMILabEngine_SOURCE_DIR}/../PythonWrap/parse_xml/parse_xml2.py")

  SET(ANCESTORS_CMD ${PYTHON_EXECUTABLE})                          #Command
  SET(ANCESTORS_CMD ${ANCESTORS_CMD} ${AMI_WRAPPER})                 #Wrapper
  SET(ANCESTORS_CMD ${ANCESTORS_CMD} ${XML_OUTPUT})                  #Input
  SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--libname" "${LIBNAME}")       
  SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--ancestors" ${classes_list})  #Options
  SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--ancestors-file" ${ANCESTORS_FILE} "-q")
  SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--templates" )
  SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--templatefile_dir" ${AMILabEngine_SOURCE_DIR}/../PythonWrap/)

  IF(DEFINED AVAILABLE_EXTERNAL_CLASSES)
    WRAP_MESSAGE("***** available external classes *****")
    SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--available_external_classes" ${AVAILABLE_EXTERNAL_CLASSES} )
  ENDIF(DEFINED AVAILABLE_EXTERNAL_CLASSES)

  IF(DEFINED AVAILABLE_EXTERNAL_CLASSES2)
    WRAP_MESSAGE("***** available external classes 2 *****")
    SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--available_external_classes2" ${AVAILABLE_EXTERNAL_CLASSES2} )
  ENDIF(DEFINED AVAILABLE_EXTERNAL_CLASSES2)
  
  IF(GENERATE_HTML_HELP AND CLASSES_URL_LIST AND HTML_DIR)
    # flag to generate html help
    SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--generate-html")
    # base URL html help
    SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--url" "${CLASSES_URL_LIST}")
    #HTML directory
    SET(ANCESTORS_CMD ${ANCESTORS_CMD} "--outputhtmldir" ${HTML_DIR})
  ENDIF(GENERATE_HTML_HELP AND CLASSES_URL_LIST AND HTML_DIR)

  SET( ANCESTORS_CMD_TXT "")
  FOREACH( C ${ANCESTORS_CMD})  
    SET( ANCESTORS_CMD_TXT "${ANCESTORS_CMD_TXT} ${C}")
  ENDFOREACH( C ${ANCESTORS_CMD})
  WRAP_MESSAGE("ANCESTORS_CMD: ${ANCESTORS_CMD_TXT}")

#  ADD_CUSTOM_COMMAND(
#    OUTPUT ${ANCESTORS_FILE}
  EXECUTE_PROCESS(
    COMMAND ${ANCESTORS_CMD}
    RESULT_VARIABLE ANCESTORS_CMD_RESULT
    ERROR_VARIABLE  ANCESTORS_CMD_ERROR
    OUTPUT_VARIABLE ancestors_result
  )

  IF(ANCESTORS_CMD_RESULT)
    MESSAGE(SEND_ERROR "Failed the generation of ANCESTORS file: ${ANCESTORS_CMD_ERROR} - ${ANCESTORS_CMD_RESULT}")
  ENDIF(ANCESTORS_CMD_RESULT)

ENDMACRO( CREATE_ANCESTORS )

#-------------------------------------------------------------------------------
# Create classes dependencies as the file including the class given by
# gccxml result
# it creates a "map" between the classname and the dependency file
#
MACRO( CREATE_ANCESTORS_DEPS )
  SET(ANCESTORS_DEPFILE "${GENERATED_DIR}/ancestors_depfile.txt")
  IF(EXISTS ${ANCESTORS_DEPFILE})
    FILE(READ "${ANCESTORS_DEPFILE}" ancestors_depfile)
    STRING(REGEX REPLACE "[\r\n]" ";" ancestors_depfile_list 
            ${ancestors_depfile})
    # now create map for each class dependency
    FOREACH( dep ${ancestors_depfile_list})
      STRING(FIND ${dep} "|" SPLIT_POS)
      MATH(EXPR LEN "${SPLIT_POS}-1")
      STRING(SUBSTRING ${dep} 0 ${LEN} CLASSNAME)
      MATH(EXPR BEG "${SPLIT_POS}+2")
      STRING(SUBSTRING ${dep} ${BEG} -1 DEPFILE)
      #MESSAGE("${CLASSNAME} --> ${DEPFILE}")
      # create the simulated map structure
      ClassUsedName( CLASSNAME m_class )
      SET(CLASSDEP_${m_class} ${DEPFILE})
    ENDFOREACH( dep ${ancestors_depfile_list})
  ENDIF(EXISTS ${ANCESTORS_DEPFILE})
ENDMACRO( CREATE_ANCESTORS_DEPS )

#-------------------------------------------------------------------------------
# list of classes dependencies
#
MACRO( CREATE_ANCESTORS_DEPLIST )
  SET(ANCESTORS_DEPFILE "${GENERATED_DIR}/ancestors_depfile.txt")
  SET(ANCESTORS_DEPLIST "")
  IF(EXISTS ${ANCESTORS_DEPFILE})
    FILE(READ "${ANCESTORS_DEPFILE}" ancestors_depfile)
    STRING(REGEX REPLACE "[\r\n]" ";" ancestors_depfile_list 
            ${ancestors_depfile})
    # now create map for each class dependency
    FOREACH( dep ${ancestors_depfile_list})
      STRING(FIND ${dep} "|" SPLIT_POS)
      MATH(EXPR BEG "${SPLIT_POS}+2")
      STRING(SUBSTRING ${dep} ${BEG} -1 DEPFILE)
      SET(ANCESTORS_DEPLIST ${ANCESTORS_DEPLIST} ${DEPFILE})
    ENDFOREACH( dep ${ancestors_depfile_list})
  ENDIF(EXISTS ${ANCESTORS_DEPFILE})
ENDMACRO( CREATE_ANCESTORS_DEPLIST )

#-------------------------------------------------------------------------------
# Create the files MISSING_CLASSES.txt, MISSING_FUNCTIONS.txt
# and MISSING_METHODPOINTERS.txt
#
MACRO( CREATE_DEPENDENCIES_COMMAND )
  SET(  DEP_CMD ${CMAKE_COMMAND})
  SET(  DEP_CMD   ${DEP_CMD} 
                  "-D" "AMILabEngine_SOURCE_DIR:PATH=${AMILabEngine_SOURCE_DIR}")
  SET(  DEP_CMD   ${DEP_CMD} 
                  "-D" "GENERATED_DIR:PATH=${GENERATED_DIR}")
  SET(  DEP_CMD   ${DEP_CMD} 
                  "-D" "WRAPPING_DIR:PATH=${WRAPPING_DIR}")
  SET(  DEP_CMD   ${DEP_CMD} 
                  "-P" 
                  ${AMILabEngine_SOURCE_DIR}/../CMAKE/RUN_DEPENDENCIES.cmake)

  MESSAGE("WRAPPING DEPENDENCIES")
  SET(DEP_CMD_TXT "")
  FOREACH( C ${DEP_CMD})
    SET( DEP_CMD_TXT "${DEP_CMD_TXT} ${C}")
  ENDFOREACH( C ${WRAP_CMD})
  WRAP_MESSAGE("DEP_CMD: ${DEP_CMD_TXT}")
#   ADD_CUSTOM_COMMAND(
#     OUTPUT
#       ${GENERATED_DIR}/MISSING_CLASSES.txt
#     COMMAND
#       ${DEP_CMD}
      #CHECK_WRAPPED_FILES("${ancestors_list}"       "MISSING_CLASSES")
#     DEPENDS
#       ${CLASSES_FILES}
#       ${MISSING_CLASSES}
#     VERBATIM
#   )
ENDMACRO( CREATE_DEPENDENCIES_COMMAND )


#-------------------------------------------------------------------------------
#
# Wrap the classes and functions
#
# needed:
#   GENERATED_DIR
#   LIBNAME
#   LIBFILTER (optional)
#   LIBCONSTRUCTOR (optional)
#   PYTHON_EXECUTABLE
#   AMI_WRAPPER
#   ancestors_list
#   functions_list
#   OUTPUT_LIST
#   methodpointers_list (optional)
#   AVAILABLE_EXTERNAL_CLASSES (optional)
#   EXTERNAL_DLLNAME (optional)
#   AVAILABLE_EXTERNAL_CLASSES2 (optional)
#   EXTERNAL_DLLNAME2 (optional)
#   GENERATE_HTML_HELP
#   CLASSES_URL_LIST (if GENERATE_HTML_HELP)
#   HTML_DIR (if GENERATE_HTML_HELP)
#
# output:
#  command to wrap all the classes, functions, etc ...
#
MACRO( WRAP_CODE )

  CREATE_DEPENDENCIES_COMMAND()

  CREATE_ANCESTORS_DEPLIST()


  WRAP_MESSAGE("Try to generate wrapping...")
  WRAP_MESSAGE("PYTHON_EXECUTABLE = ${PYTHON_EXECUTABLE}")

  # to avoid too long command, write available classes and functions to a file in disk
  SET(available_classes_list ${ancestors_list} ${methodpointers_list})

  SAVE_LIST(  "${available_classes_list}"
              ${GENERATED_DIR}/available_classes.txt)

  SAVE_LIST(  "${functions_list}"
              ${GENERATED_DIR}/available_functions.txt)


  SET(  WRAP_CMD ${PYTHON_EXECUTABLE})
  SET(  WRAP_CMD ${WRAP_CMD} ${AMI_WRAPPER})
  SET(  WRAP_CMD ${WRAP_CMD} ${XML_OUTPUT})
  SET(  WRAP_CMD ${WRAP_CMD} "--libname" "${LIBNAME}")
  IF(DEFINED LIBFILTER)
    SET(WRAP_CMD ${WRAP_CMD} "--filter" "\"${LIBFILTER}\"")
  ENDIF(DEFINED LIBFILTER)
  IF(DEFINED LIBCONSTRUCTOR)
    SET(WRAP_CMD ${WRAP_CMD} "--constructor" "${LIBCONSTRUCTOR}")
  ENDIF(DEFINED LIBCONSTRUCTOR)
  IF(DEFINED DLLNAME)
    SET(WRAP_CMD ${WRAP_CMD} "--dllname" ${DLLNAME})
  ENDIF(DEFINED DLLNAME)
  SET(WRAP_CMD ${WRAP_CMD}  "--classes_file" 
                            "${GENERATED_DIR}/MISSING_CLASSES.txt")
  SET(WRAP_CMD ${WRAP_CMD}  "--methodpointers_file" 
                            "${GENERATED_DIR}/MISSING_METHODS.txt")
  SET(WRAP_CMD ${WRAP_CMD}  "--available_classes_file" 
                            "${GENERATED_DIR}/available_classes.txt")
  SET(  WRAP_CMD ${WRAP_CMD}    "--functions_file" 
                                "${GENERATED_DIR}/MISSING_FUNCTIONS.txt")

  IF(DEFINED AVAILABLE_EXTERNAL_CLASSES)
    WRAP_MESSAGE("***** available external classes *****")
    SET(WRAP_CMD ${WRAP_CMD} "--available_external_classes" 
          "${AVAILABLE_EXTERNAL_CLASSES}")
    IF(DEFINED EXTERNAL_DLLNAME)
      SET(WRAP_CMD ${WRAP_CMD} "--external_dllname" ${EXTERNAL_DLLNAME} )
    ENDIF(DEFINED EXTERNAL_DLLNAME)
  ENDIF(DEFINED AVAILABLE_EXTERNAL_CLASSES)

  IF(DEFINED AVAILABLE_EXTERNAL_CLASSES2)
    WRAP_MESSAGE("***** available external classes 2 *****")
    SET(WRAP_CMD ${WRAP_CMD} "--available_external_classes2" 
          "${AVAILABLE_EXTERNAL_CLASSES2}")
    IF(DEFINED EXTERNAL_DLLNAME2)
      SET(WRAP_CMD ${WRAP_CMD} "--external_dllname2" ${EXTERNAL_DLLNAME2} )
    ENDIF(DEFINED EXTERNAL_DLLNAME2)
  ENDIF(DEFINED AVAILABLE_EXTERNAL_CLASSES2)

  IF(DEFINED HAS_FUNCTIONS)
    #SET(WRAP_CMD ${WRAP_CMD} "--functions" "${MISSING_FUNCTIONS}")
    SET(WRAP_CMD ${WRAP_CMD} "--available_functions_file" "${GENERATED_DIR}/available_functions.txt")
  ENDIF(DEFINED HAS_FUNCTIONS)
  #SET(WRAP_CMD ${WRAP_CMD} "--wrap_includes" ${WrapWxWidgetsDir})
  SET(  WRAP_CMD ${WRAP_CMD} "--outputdir" ${GENERATED_DIR})
  SET(  WRAP_CMD ${WRAP_CMD} "--profile")
  SET(  WRAP_CMD ${WRAP_CMD} "--templates")
  SET(  WRAP_CMD ${WRAP_CMD} "--templatefile_dir" 
          ${AMILabEngine_SOURCE_DIR}/../PythonWrap/)
  IF(GENERATE_HTML_HELP)
    # flag to generate html help
    SET(WRAP_CMD ${WRAP_CMD} "--generate-html")
    # base URL html help
    SET(WRAP_CMD ${WRAP_CMD} "--url" "${CLASSES_URL_LIST}")
    #HTML directory
    IF (HTML_DIR)
      SET(WRAP_CMD ${WRAP_CMD} "--outputhtmldir" ${HTML_DIR})
    ENDIF (HTML_DIR)
  ENDIF(GENERATE_HTML_HELP)

  IF(DEFINED NO_METHOD_HELP)
  SET(  WRAP_CMD ${WRAP_CMD} "-light")
  ENDIF(DEFINED NO_METHOD_HELP)

  SET(  WRAP_CMD ${WRAP_CMD} "-q")

  IF(EXISTS ${WRAPPING_DIR}/classes_includes.py)
    SET(WRAP_CMD ${WRAP_CMD} "--classes_includes" 
          ${WRAPPING_DIR}/classes_includes.py)
  ENDIF(EXISTS ${WRAPPING_DIR}/classes_includes.py)
  IF(EXISTS ${WRAPPING_DIR}/members_blacklist.py)
    SET(WRAP_CMD ${WRAP_CMD} "--members_blacklist" 
          ${WRAPPING_DIR}/members_blacklist.py)
  ENDIF(EXISTS ${WRAPPING_DIR}/members_blacklist.py)
  IF(EXISTS ${WRAPPING_DIR}/enum_filter.py)
    SET(WRAP_CMD ${WRAP_CMD} "--enum_filter" 
          ${WRAPPING_DIR}/enum_filter.py)
  ENDIF(EXISTS ${WRAPPING_DIR}/enum_filter.py)


  # Write the command to the standard output for information
  SET(WRAP_CMD_TXT "")
  FOREACH( C ${WRAP_CMD})
    SET( WRAP_CMD_TXT "${WRAP_CMD_TXT} ${C}")
  ENDFOREACH( C ${WRAP_CMD})
  WRAP_MESSAGE("WRAP_CMD: ${WRAP_CMD_TXT}")

  IF(EXISTS  ${GENERATED_DIR}/../classes.txt)
    SET( CLASSES_FILES ${GENERATED_DIR}/../classes.txt)
  ENDIF(EXISTS  ${GENERATED_DIR}/../classes.txt)
  IF(EXISTS  ${GENERATED_DIR}/../../classes_common.txt)
    SET( CLASSES_FILES ${CLASSES_FILES} 
            ${GENERATED_DIR}/../../classes_common.txt)
  ENDIF(EXISTS  ${GENERATED_DIR}/../../classes_common.txt)

  ADD_CUSTOM_COMMAND(
    OUTPUT
      ${GENERATED_DIR}/MISSING_CLASSES.txt
      ${GENERATED_DIR}/MISSING_FUNCTIONS.txt
      ${GENERATED_DIR}/MISSING_METHODS.txt
    COMMAND
      ${DEP_CMD}
    DEPENDS
      # add function file, method pointers file + python files ?
      ${CLASSES_FILES}
      ${ANCESTORS_DEPLIST}
  )

  # put it separate for dependency problem with all the generated files
  # need to add this rule to allow cmake to configure
  ADD_CUSTOM_COMMAND(
    OUTPUT
      ${OUTPUT_LIST} 
    COMMAND
      # regenerate files 
      ${DEP_CMD}
    COMMAND
      # to work well, this command should delete MISSING_XXX.txt
      # if they contained elts to wrap, so that they
      ${WRAP_CMD}
#     COMMAND
#       # regenerate files 
#       ${DEP_CMD}
#     DEPENDS
#       ${GENERATED_DIR}/MISSING_CLASSES.txt
#       ${GENERATED_DIR}/MISSING_FUNCTIONS.txt
#       ${GENERATED_DIR}/MISSING_METHODS.txt
    VERBATIM
  )

  ADD_CUSTOM_COMMAND(
    OUTPUT
      # comment ${OUTPUT_LIST} because the file there may be older
      # than one of the dependencies, but the timestep of addwrap_... files
      # if enough because they are always creating
      # however, now deleting one of the wrapped files may cause the 
      # makefile to fail ?
      # CHANGE:can't get rid of this dependency for initial cmake to work ...
      ${GENERATED_DIR}/addwrap_${LIBNAME}.h
      ${GENERATED_DIR}/addwrap_${LIBNAME}.cpp
    COMMAND
      # regenerate files 
      ${DEP_CMD}
    COMMAND
      # to work well, this command should delete MISSING_XXX.txt
      # if they contained elts to wrap, so that they
      ${WRAP_CMD} "--addwrap"
    DEPENDS
      ${GENERATED_DIR}/MISSING_CLASSES.txt
      ${GENERATED_DIR}/MISSING_FUNCTIONS.txt
      ${GENERATED_DIR}/MISSING_METHODS.txt
      ${CLASSES_FILES}
      ${ANCESTORS_DEPLIST}
      ${OUTPUT_LIST}
    VERBATIM
  )



ENDMACRO( WRAP_CODE )

