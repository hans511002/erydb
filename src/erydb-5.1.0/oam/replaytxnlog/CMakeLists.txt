include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(replaytxnlog_LIB_SRCS replaytxnlog.cpp)

add_library(replaytxnlog SHARED ${replaytxnlog_LIB_SRCS})

add_dependencies(replaytxnlog libnetsnmpmibs)

set_target_properties(replaytxnlog PROPERTIES VERSION 1.0.0 SOVERSION 1)

install(TARGETS replaytxnlog DESTINATION ${ENGINE_LIBDIR})
 

