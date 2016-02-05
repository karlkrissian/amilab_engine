

#-------------------------------------------------------------------------------
MACRO( InitPrintSources)
#-------------------------------------------------------------------------------
    FILE(WRITE ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/source_list.txt "")
ENDMACRO( InitPrintSources)
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
MACRO( PrintSources var)
#-------------------------------------------------------------------------------
  FILE(APPEND ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/source_list.txt "\n")
  FOREACH(sourcefile ${${var}_SRCS} )
    IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${sourcefile})
      FILE(RELATIVE_PATH filename ${${CMAKE_PROJECT_NAME}_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/${sourcefile})
    ELSE( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${sourcefile})
      # sourcefile already contains the full path
      FILE(RELATIVE_PATH filename ${${CMAKE_PROJECT_NAME}_SOURCE_DIR} ${sourcefile})
    ENDIF( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${sourcefile})
    FILE(APPEND ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/source_list.txt "src/${filename}\n")
    # look for a header file
  ENDFOREACH( sourcefile)

  FILE(GLOB ${var}_INC RELATIVE ${${CMAKE_PROJECT_NAME}_SOURCE_DIR} *.h *.hpp *.hxx *.ypp *.lpp *.tpp CMakeLists.txt)
  FOREACH(sourcefile ${${var}_INC} )
    FILE(APPEND ${${CMAKE_PROJECT_NAME}_SOURCE_DIR}/source_list.txt "src/${sourcefile}\n")
    # look for a header file
  ENDFOREACH( sourcefile)
ENDMACRO(PrintSources)
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
MACRO( my_add_library var)
#-------------------------------------------------------------------------------
  add_library (${var}   ${${var}_SRCS})
  PrintSources(${var})
ENDMACRO(my_add_library)
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
MACRO( my_add_shared_library var)
#-------------------------------------------------------------------------------
  ADD_LIBRARY (${var} SHARED  ${${var}_SRCS})
  PrintSources(${var})
ENDMACRO(my_add_shared_library)
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
# Specifies the number of sources that will be packed in a file. By default, 10
# files are packaged.
#-------------------------------------------------------------------------------
SET(NUMBER_SOURCES_TO_PACKAGE 1 CACHE STRING "Indicates the number of sources to package")
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Creates a directory. If the directory exists, it does not do anything.
#-------------------------------------------------------------------------------
MACRO( CreateDirectory path)
#-------------------------------------------------------------------------------
  IF( NOT EXISTS ${path})
    #MESSAGE("Directory ${path}: Exists")
  #ELSE(EXISTS ${path})
    #MESSAGE("Directory ${path}: Create")
    FILE(MAKE_DIRECTORY ${path})
  ENDIF( NOT EXISTS ${path})
ENDMACRO(CreateDirectory)
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
# Determines if a file exists. If not, it creates a certain content.
#-------------------------------------------------------------------------------
MACRO( FileExists file result body)
#-----------------------------------------------------------------------------
  IF(EXISTS ${file})
    SET(${result} TRUE)
  ELSE(EXISTS ${file})
    FILE(WRITE ${file} ${body})
    SET(${result} FALSE)
  ENDIF(EXISTS ${file})
ENDMACRO(FileExists)
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
MACRO( GenerateSourcesWrapping new_code_list path code_list )
#-------------------------------------------------------------------------------
  SET(source_code_list ${${code_list}})
  SET(source_code_path ${${path}})
  #MESSAGE("source code: ${source_code_list}\n\npath: ${source_code_path}")

  #-----------------------------------------------------------------------------
  # 1. Verify if there exists the output_dir_path directory. If the directory
  #    does not exist, it creates it.
  #-----------------------------------------------------------------------------
  SET(output_dir_path "${source_code_path}/Generated")
  CreateDirectory(${output_dir_path})

  #-----------------------------------------------------------------------------
  # 2. Verify if there exists the wrap_source_list.txt file. If the file does
  #    not exist, it creates it with the content of the source_code_list
  #    variable.
  #-----------------------------------------------------------------------------
  SET(wrap_source_filename "${output_dir_path}/wrap_source_list.txt")
  SET(result FALSE)
  LIST(SORT source_code_list)
  FileExists(${wrap_source_filename} result ${source_code_list} )
  #MESSAGE("FileExists(${wrap_source_filename}): ${result}")

  #-------------------------------------------------------------------------------
  # 3. Check if it begins the process. Reads the content of the file
  #    wrap_source_filename and compares it with the content of the variable
  #    source_code_list. If they are equal, the process does not begin.
  #-------------------------------------------------------------------------------
  IF(result) #There has been a previous generation of files wrap_x.cpp
    FILE(READ ${wrap_source_filename} wrap_source_list)
    #message("wrap_source_list: ${wrap_source_list} \n source_code_list: ${source_code_list}")
    FILE(WRITE "${wrap_source_filename}.new" ${source_code_list})
    FILE(READ "${wrap_source_filename}.new" wrap_source_list_new)
    IF(wrap_source_list STREQUAL wrap_source_list_new)
      SET(build_flag FALSE)
    ELSE(wrap_source_list STREQUAL wrap_source_list_new)
      SET(build_flag TRUE)
    ENDIF(wrap_source_list STREQUAL wrap_source_list_new)
  ELSE(result)
    SET(build_flag TRUE)
  ENDIF(result)
  MESSAGE("build_flag: ${build_flag}")
  #-----------------------------------------------------------------------------
  # 4. Checks if the process begins.
  #-----------------------------------------------------------------------------
  IF(build_flag)

    MESSAGE("Begin process..")
    #---------------------------------------------------------------------------
    # 4.1. Preprocess the source file list.
    #---------------------------------------------------------------------------
    SET(output_src "")
    FOREACH(loop_var ${source_code_list})
      SET(include_header "#include \"${loop_var}\"")
      SET(output_src ${output_src} ${include_header})
    ENDFOREACH(loop_var)

    #---------------------------------------------------------------------------
    # 4.2. Process the list.
    #---------------------------------------------------------------------------
    SET(counter_files 0)
    LIST(LENGTH output_src output_src_length)
    SET(new_source_list "")
    SET(iterations ${NUMBER_SOURCES_TO_PACKAGE})
    MATH(EXPR iterations "${iterations}-1")
    MESSAGE("size: ${output_src_length} - iterations: ${iterations}")
    WHILE(output_src_length)

      #-------------------------------------------------------------------------
      # 4.2.1. Generate packages of iterations files.
      #-------------------------------------------------------------------------
      SET(include_list "")
      FOREACH(counter RANGE ${iterations})

        IF(output_src_length)
          LIST(GET output_src -1 element_src)
          SET(include_list "${include_list} ${element_src}\n")
          LIST(REMOVE_AT output_src -1)
          LIST(LENGTH output_src output_src_length)
        ENDIF(output_src_length)

      ENDFOREACH(counter)

      #-------------------------------------------------------------------------
      # 4.2.2. Generate the wrap files.
      #-------------------------------------------------------------------------
      SET(name_output "wrap_${counter_files}.cpp")
      MATH(EXPR counter_files "${counter_files}+1")

      FILE(WRITE "${output_dir_path}/${name_output}" ${include_list})
      SET(new_source_list ${new_source_list} "${output_dir_path}/${name_output}")

    ENDWHILE(output_src_length)

    #---------------------------------------------------------------------------
    # 4.3. Obtain the necessary to compile source code listing and file with the
    #      original source code.
    #---------------------------------------------------------------------------
    SET(${new_code_list} ${new_source_list})
    IF(result)#There has been a previous generation of files wrap_x.cpp
      FILE(RENAME "${wrap_source_filename}.new"  ${wrap_source_filename})
    ENDIF(result)

    #MESSAGE("new_source_list = ${new_source_list}")
    # remove other files
    FILE(GLOB cpp_files "${output_dir_path}/wrap*cpp")
    FOREACH( file ${cpp_files})
      #MESSAGE("file ${file}")
      LIST(FIND new_source_list ${file} file_found)
      IF ( file_found EQUAL -1 ) 
        FILE(REMOVE ${file})
        #MESSAGE("Removing file ${file}")
      ENDIF( file_found EQUAL -1 )
    ENDFOREACH( file ${cpp_files})
    

  ELSE(build_flag)
    MESSAGE("NOT PROCESS")
    FILE(GLOB wx_SRCS_list  "${output_dir_path}/*.cpp")
    SET(${new_code_list} ${wx_SRCS_list})
  ENDIF(build_flag)

ENDMACRO( GenerateSourcesWrapping)
#-------------------------------------------------------------------------------

#-------------------------------------------------------------------------------
MACRO( ClassUsedName input_name output_name )
#-------------------------------------------------------------------------------

  STRING(REGEX REPLACE "<" "_L_"                ${output_name} ${${input_name}} )
  STRING(REGEX REPLACE ">" "_G_"                ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "," "_"                  ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "::" "_"                 ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "\\*" "_ptr"             ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "&" "_ref"               ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "unsigned char"  "UC"    ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "unsigned short" "US"    ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "unsigned int"   "UI"    ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "unsigned long"  "UL"    ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "short int"      "short" ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE " " ""                   ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "itk_"           ""      ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "\\("            "_"     ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "\\)"            "_"     ${output_name} ${${output_name}} )

ENDMACRO( ClassUsedName)
#-------------------------------------------------------------------------------


#-------------------------------------------------------------------------------
MACRO( FunctionUsedName input_name output_name )
#-------------------------------------------------------------------------------

  STRING(REGEX REPLACE "<" "_L_"                ${output_name} ${${input_name}} )
  STRING(REGEX REPLACE ">" "_G_"                ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "," "_"                  ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "::" "_"                 ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "\\*" "_ptr"             ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "&" "_ref"               ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "unsigned char"  "UC"    ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "unsigned short" "US"    ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "unsigned int"   "UI"    ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "unsigned long"  "UL"    ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "short int"      "short" ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE " " ""                   ${output_name} ${${output_name}} )
  STRING(REGEX REPLACE "itk_"           ""      ${output_name} ${${output_name}} )
  # get rid of function parameters in case of a function
  STRING(REGEX REPLACE "\\(.*\\)"         ""      ${output_name} ${${output_name}} )
  

ENDMACRO( FunctionUsedName)


#-------------------------------------------------------------------------------
# save a list to a file
MACRO( SAVE_LIST VAR_LIST VAR_FILENAME)
  # only way found to convert back the string to a list ...
  SET( REALLIST ${VAR_LIST})
  IF(DEFINED VAR_LIST )
    LIST(SORT               REALLIST)
    LIST(REMOVE_DUPLICATES  REALLIST)
  ENDIF(DEFINED VAR_LIST)
  FILE(WRITE ${VAR_FILENAME} "${REALLIST}")
ENDMACRO( SAVE_LIST VAR_LIST VAR_FILENAME)
#-------------------------------------------------------------------------------


