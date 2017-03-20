
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(erydbdatafile_LIB_SRCS
    BufferedFile.cpp
    ERYDBDataFile.cpp
    ERYDBFactory.cpp
    ERYDBFileSystem.cpp
    ERYDBLogger.cpp
    ERYDBPolicy.cpp
    PosixFileSystem.cpp
    UnbufferedFile.cpp)

add_library(erydbdatafile SHARED ${erydbdatafile_LIB_SRCS})

target_link_libraries(erydbdatafile ${NETSNMP_LIBRARIES})

set_target_properties(erydbdatafile PROPERTIES VERSION 1.0.0 SOVERSION 1)

install(TARGETS erydbdatafile DESTINATION ${ENGINE_LIBDIR} COMPONENT libs)
