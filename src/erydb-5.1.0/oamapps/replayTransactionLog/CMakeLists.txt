
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(ReplayTransactionLog_SRCS replaytransactionlog.cpp )

add_executable(ReplayTransactionLog ${ReplayTransactionLog_SRCS})

add_dependencies(ReplayTransactionLog libnetsnmpmibs)

target_link_libraries(ReplayTransactionLog ${ENGINE_LDFLAGS} readline ncurses ${ENGINE_EXEC_LIBS})

install(TARGETS ReplayTransactionLog DESTINATION ${ENGINE_BINDIR})

