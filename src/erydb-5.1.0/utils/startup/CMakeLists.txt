
include_directories( ${ENGINE_COMMON_INCLUDES} )

ADD_DEFINITIONS(-fPIC -DPIC)

add_library(erydbboot STATIC installdir.cpp)

INSTALL(TARGETS erydbboot DESTINATION ${ENGINE_LIBDIR})


