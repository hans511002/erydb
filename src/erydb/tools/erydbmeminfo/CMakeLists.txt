
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(erydbmeminfo_SRCS erydbmeminfo.cpp)

add_executable(erydbmeminfo ${erydbmeminfo_SRCS})

target_link_libraries(erydbmeminfo ${ENGINE_LDFLAGS})

install(TARGETS erydbmeminfo DESTINATION ${ENGINE_BINDIR} COMPONENT platform)

