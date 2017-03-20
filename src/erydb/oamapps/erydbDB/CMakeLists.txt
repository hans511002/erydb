
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(erydbDBWrite_SRCS erydbDB.cpp)

add_executable(erydbDBWrite ${erydbDBWrite_SRCS})

target_link_libraries(erydbDBWrite ${ENGINE_LDFLAGS} readline ncurses  ${ENGINE_EXEC_LIBS})

install(TARGETS erydbDBWrite DESTINATION ${ENGINE_BINDIR} COMPONENT platform)

