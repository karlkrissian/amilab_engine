# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found.  Any number of sources could be listed here.


# Make sure the compiler can find include files from our Hello library.
include_directories (
  ${AMILABENGINE_SOURCE_DIR}/CommonBase
  ${AMILABENGINE_SOURCE_DIR}/Common/include
  ${AMILABENGINE_SOURCE_DIR}/AMILab
  ${AMILABENGINE_SOURCE_DIR}/LanguageBase
  ${AMILABENGINE_SOURCE_DIR}/Language
  ${AMILABENGINE_SOURCE_DIR}
  ${PTHREADS_INCLUDE_DIR}
  ${AMILABENGINE_SOURCE_DIR}/Wrapping/include
)


SET(AMILab_SRCS
    amilab_global_export.cpp
)

SET (AMILab_HDRS
    amilab_global_import.h
    myscan.h
    token_list.h
)

IF(WIN32)
  set_source_files_properties(${AMILab_SRCS} PROPERTIES COMPILE_FLAGS "-DAMILab_EXPORTS")
ENDIF(WIN32)

SET (AMILab_SRCS
     ${AMILab_SRCS}
     ${AMILab_HDRS}
)

my_add_library ( AMILab)

target_link_libraries(AMILab
  Common
)
