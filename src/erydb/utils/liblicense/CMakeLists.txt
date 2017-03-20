
include_directories( ${ENGINE_COMMON_INCLUDES} )
 

########### next target ###############

set(lic_LIB_SRCS
   Decoding.cpp  Encoding.cpp  Functions.cpp license.cpp  String.cpp)

add_library(lic SHARED ${lic_LIB_SRCS})

add_dependencies(lic genMsgAndErrId)

set_target_properties(lic PROPERTIES VERSION 1.0.0 SOVERSION 1)

install(TARGETS lic DESTINATION ${ENGINE_LIBDIR})

