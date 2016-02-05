# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found.  Any number of sources could be listed here.


# Make sure the compiler can find include files from our Hello library.
include_directories (
  ${AMILABENGINE_SOURCE_DIR}/Wrapping/include
  ${AMILABENGINE_SOURCE_DIR}/CommonBase
  ${AMILABENGINE_SOURCE_DIR}/Common/include
  ${AMILABENGINE_SOURCE_DIR}/LanguageBase
  #${AMILABENGINE_SOURCE_DIR}/Language
  ${Boost_INCLUDE_DIR}
  )

#INCLUDE( ${wxWidgets_USE_FILE})

#add_subdirectory ( WrapImports        )
add_subdirectory ( WrapCommon         )
#add_subdirectory ( WrapBasicTypes     )
#add_subdirectory ( WrapSystem         )
#add_subdirectory ( WrapIO             )
#add_subdirectory ( WrapLanguage       )

