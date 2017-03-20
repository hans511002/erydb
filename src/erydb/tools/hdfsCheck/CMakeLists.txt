
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(hdfsCheck_SRCS hdfsCheck.cpp)

add_executable(hdfsCheck ${hdfsCheck_SRCS})

target_link_libraries(hdfsCheck ${ENGINE_LDFLAGS} ${ENGINE_EXEC_LIBS})

install(TARGETS hdfsCheck DESTINATION ${ENGINE_BINDIR} COMPONENT platform)

