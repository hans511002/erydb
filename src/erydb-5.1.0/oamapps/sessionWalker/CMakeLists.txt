
include_directories( ${ENGINE_COMMON_INCLUDES} )

 

########### next target ###############

set(sessionWalker_SRCS sessionwalker.cpp )

add_executable(sessionWalker ${sessionWalker_SRCS})

add_dependencies(sessionWalker libnetsnmpmibs)

target_link_libraries(sessionWalker ${ENGINE_LDFLAGS} readline ncurses ${ENGINE_EXEC_LIBS})

install(TARGETS sessionWalker DESTINATION ${ENGINE_BINDIR})


 

