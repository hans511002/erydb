
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(hardwareMonitor_SRCS hardwareMonitor.cpp )

add_executable(hardwareMonitor ${hardwareMonitor_SRCS})

add_dependencies(hardwareMonitor libnetsnmpmibs)

target_link_libraries(hardwareMonitor ${ENGINE_LDFLAGS} readline ncurses ${ENGINE_EXEC_LIBS})

install(TARGETS hardwareMonitor DESTINATION ${ENGINE_BINDIR})
