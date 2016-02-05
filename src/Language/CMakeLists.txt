# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found.  Any number of sources could be listed here.



# Make sure the compiler can find include files from our Hello library.
include_directories (
  ${AMILABENGINE_SOURCE_DIR}/CommonBase
  ${AMILABENGINE_SOURCE_DIR}/Common/include
  ${AMILABENGINE_SOURCE_DIR}/Wrapping/include
  ${AMILab_BINARY_DIR}/Wrapping/WrapCommon/Generated
  ${AMILABENGINE_SOURCE_DIR}/Language/GeneratedFlexBison
  ${AMILABENGINE_SOURCE_DIR}/LanguageBase
  ${AMILABENGINE_SOURCE_DIR}/Language
  ${AMILABENGINE_SOURCE_DIR}/AMILab
  ${AMILABENGINE_SOURCE_DIR}/
  ${FLEX_INCLUDE_DIR}
  )


SET(Language_SRCS
    driver.cc
    language_global_export.cpp
)

SET(Language_HDRS
    LanguageConfigure.h
    language_global_import.h
    driver.h
    scanner.h
    VariableStack.h
)

SET(Language_BISONFLEX_SRCS
  amiengine_bison.y
  amiengine_flex.l
)


IF(AMI_USE_FLEXBISON)


  SET(bison_options "-dv")
  IF(AMI_BISON_DEBUG)
    SET(bison_options "-t ${bison_options}")
  ENDIF(AMI_BISON_DEBUG)

  BISON_TARGET_option_extraopts(${bison_options})
#BISON_${Name}_COMPILE_FLAGS

  BISON_TARGET(amienginebison
    ${AMILABENGINE_SOURCE_DIR}/Language/amiengine_bison.y
    ${AMILABENGINE_SOURCE_DIR}/Language/GeneratedFlexBison/amiengine_bison.tab.cpp
    COMPILE_FLAGS ${bison_options}
 )
 
  FLEX_TARGET(amiengineflex
  ${AMILABENGINE_SOURCE_DIR}/Language/amiengine_flex.l
  ${AMILABENGINE_SOURCE_DIR}/Language/GeneratedFlexBison/amiengine_flex.cpp)

  ADD_FLEX_BISON_DEPENDENCY(amiengineflex amienginebison)

  
  #MESSAGE("******************** Language_SRCS = ${Language_SRCS} *****************************")
  IF(WIN32)
    set_source_files_properties(${Language_SRCS} PROPERTIES COMPILE_FLAGS "-DLanguage_EXPORTS")
    set_source_files_properties(${AMILABENGINE_SOURCE_DIR}/Language/GeneratedFlexBison/amiengine_flex.cpp PROPERTIES COMPILE_FLAGS "-DLanguage_EXPORTS")
    set_source_files_properties(${AMILABENGINE_SOURCE_DIR}/Language/GeneratedFlexBison/amiengine_bison.tab.cpp PROPERTIES COMPILE_FLAGS "-DLanguage_EXPORTS")
  ENDIF(WIN32)

  SET(Language_SRCS
    ${BISON_amienginebison_OUTPUTS}
    ${FLEX_amiengineflex_OUTPUTS}
    ${Language_SRCS}
    ${Language_BISONFLEX_SRCS}
    ${Language_HDRS}
  )

  IF(MSVC)
    # too slow compilation in release mode ...
    SET_SOURCE_FILES_PROPERTIES (
        ${BISON_amienginebison_OUTPUTS} PROPERTIES CMAKE_CXX_FLAGS_RELEASE
            "/MD /O1 /Ob1 /D NDEBUG")
  ENDIF(MSVC)

  IF(AMI_BISON_DEBUG)
    SET_SOURCE_FILES_PROPERTIES( ${Language_SRCS}
    PROPERTIES COMPILE_FLAGS -DYYDEBUG=1)
  ENDIF(AMI_BISON_DEBUG)
  
ELSE(AMI_USE_FLEXBISON)
 
  # find FlexLexer.h
  include_directories(${AMILABENGINE_SOURCE_DIR}/Language/FlexInclude)

   SET( FLEXBISON_OUTPUTS
    ${AMILABENGINE_SOURCE_DIR}/Language/GeneratedFlexBison/amiengine_bison.tab.cpp
    ${AMILABENGINE_SOURCE_DIR}/Language/GeneratedFlexBison/amiengine_flex.cpp
  )
 
  SET(Language_SRCS
     ${FLEXBISON_OUTPUTS}
     ${Language_SRCS}
  )
  
  IF(WIN32)
    set_source_files_properties(${Language_SRCS} PROPERTIES COMPILE_FLAGS "-DLanguage_EXPORTS")
  ENDIF(WIN32)

   SET(Language_SRCS
     ${Language_SRCS}
     ${Language_HDRS}
   )
 

ENDIF(AMI_USE_FLEXBISON)


#ADD_PCH_RULE( ${AMILABENGINE_SOURCE_DIR}/Language/Variable.hpp Language_SRCS)
#ADD_PCH_RULE( ${AMILABENGINE_SOURCE_DIR}/Common/include/amilab_messages.h Language_SRCS)
#ADD_PCH_RULE( ${AMILABENGINE_SOURCE_DIR}/Common/include/DefineClass.hpp Language_SRCS)

my_add_library ( Language)

target_link_libraries(Language 
  AMILab
  Common
  ${Boost_LIBRARIES}
)


add_dependencies ( Language 
  WrapCommon 
)
