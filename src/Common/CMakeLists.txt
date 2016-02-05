# Create a library called "Hello" which includes the source file "hello.cxx".
# The extension is already found.  Any number of sources could be listed here.

# Make sure the compiler can find include files from our Hello library.
include_directories (
  ${AMILabEngine_SOURCE_DIR}/CommonBase
  ${AMILabEngine_SOURCE_DIR}/Common/include
)

SET(Common_SRCS
  common_global_export.cpp
  Erreurs.cpp 
  ficparam.cpp
  message_dialog.cpp
  PluginManager.cpp
)

SET(Common_HDRS
	include/CallBackBase.h
  include/common_global_import.h
  include/DefineClass.hpp
  include/Erreurs.hpp
  include/Erreurs.Main.hpp

  # from ami_itk IO
  include/wrapConversion.h
  include/wrapConversion.tpp

  include/DynamicLibrary.h
  include/PluginBase.h
  include/PluginInterface.h
  include/PluginManager.h
)

IF(WIN32)
  set_source_files_properties(${Common_SRCS} PROPERTIES COMPILE_FLAGS "-DCOMMON_EXPORTS")
ENDIF(WIN32)

SET (Common_SRCS
     ${Common_SRCS}
     ${Common_HDRS}
)



# own macro to add the library and print the source files
# using xxx_SRCS variable
#my_add_shared_library (Common)
my_add_library (Common)

IF( NOT DEFINED ITK_LIBRARIES )
  SET(ITK_LIBRARIES 
    ITKIO
    ITKAlgorithms
    itkvnl
    itkvnl_algo
  )
ENDIF( NOT DEFINED ITK_LIBRARIES )

target_link_libraries(Common 
  ${Boost_LIBRARIES}
)


IF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
  SET_TARGET_PROPERTIES(Common PROPERTIES COMPILE_FLAGS -fPIC)
ENDIF(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_COMPILER_IS_GNUCC)
