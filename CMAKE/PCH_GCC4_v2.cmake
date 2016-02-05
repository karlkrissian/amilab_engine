
# (ADD_PCH_RULE  _header_filename _src_list)
# Version 7/26/2010 4:55pm
#
# use this macro before "add_executable"
#
# _header_filename
#	header to make a .gch
#
# _src_list 
#   the variable name (do not use ${..}) which contains a
#     a list of sources (a.cpp b.cpp c.cpp ...)
#  This macro will append a header file to it, then this src_list can be used in
#	"add_executable..."
#
#
# Now a .gch file should be generated and gcc should use it. 
#       	(add -Winvalid-pch to the cpp flags to verify)
#
# make clean should delete the pch file
#
# example : ADD_PCH_RULE(headers.h myprog_SRCS)
MACRO (ADD_PCH_RULE  _header_filename _src_list)
  MESSAGE(" === ADD_PCH_RULE ${_header_filename} ${_src_list} ===")
	SET(_gch_filename "${_header_filename}.gch")
	LIST(APPEND ${_src_list} ${_gch_filename})
  MESSAGE("CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
  MESSAGE("CMAKE_CXX_FLAGS_RELEASE = ${CMAKE_CXX_FLAGS_RELEASE}")
  MESSAGE("CMAKE_CXX_FLAGS_Release = ${CMAKE_CXX_FLAGS_Release}")
  IF ( NOT (${CMAKE_BUILD_TYPE} STREQUAL ""))
    string(TOUPPER  ${CMAKE_BUILD_TYPE} buildtype)
    MESSAGE("CMAKE_CXX_FLAGS_${buildtype} = ${CMAKE_CXX_FLAGS_${buildtype}}")
    SET (_args "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_${buildtype}}")
  ELSE( NOT (${CMAKE_BUILD_TYPE} STREQUAL ""))
    SET (_args "${CMAKE_CXX_FLAGS} ")
  ENDIF( NOT (${CMAKE_BUILD_TYPE} STREQUAL ""))
 #-Winvalid-pch

	LIST(APPEND _args -fpch-preprocess -c ${_header_filename} -o ${_gch_filename})
  GET_DIRECTORY_PROPERTY(DIRINC INCLUDE_DIRECTORIES)
  GET_DIRECTORY_PROPERTY(DIRFLAGS COMPILE_DEFINITIONS)
  foreach (_inc ${DIRFLAGS})
    LIST(APPEND _args "-D" ${_inc})
  endforeach(_inc ${DIRFLAGS})
	foreach (_inc ${DIRINC})
		LIST(APPEND _args "-I" ${_inc})
	endforeach(_inc ${DIRINC})
	SEPARATE_ARGUMENTS(_args)
  MESSAGE("Compilation of precompiled header: ${CMAKE_CXX_COMPILER}  ${CMAKE_CXX_COMPILER_ARG1} ${_args}")
	add_custom_command(OUTPUT ${_gch_filename}
		   COMMAND rm -f ${_gch_filename}
		   COMMAND ${CMAKE_CXX_COMPILER}  ${CMAKE_CXX_COMPILER_ARG1} ${_args}
			    DEPENDS ${_header_filename})
ENDMACRO(ADD_PCH_RULE _header_filename _src_list)


