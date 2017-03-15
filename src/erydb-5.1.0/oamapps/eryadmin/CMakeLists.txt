
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(eryadmin_SRCS eryadmin.cpp)

add_executable(eryadmin ${eryadmin_SRCS})

add_dependencies(eryadmin libnetsnmpmibs)

target_link_libraries(eryadmin ${ENGINE_LDFLAGS} readline ncurses ${ENGINE_EXEC_LIBS})

install(TARGETS eryadmin DESTINATION ${ENGINE_BINDIR})

