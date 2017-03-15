
include_directories( ${ENGINE_COMMON_INCLUDES} )

 

########### next target ###############

set(resourceMonitor_SRCS resourceMonitor.cpp )

add_executable(resourceMonitor ${resourceMonitor_SRCS})

add_dependencies(resourceMonitor libnetsnmpmibs)

target_link_libraries(resourceMonitor ${ENGINE_LDFLAGS} readline ncurses ${ENGINE_EXEC_LIBS})

install(TARGETS resourceMonitor DESTINATION ${ENGINE_BINDIR})

