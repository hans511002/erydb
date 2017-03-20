
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(eryadmin_SRCS eryadmin.cpp)

add_executable(eryadmin ${eryadmin_SRCS})

target_link_libraries(eryadmin ${ENGINE_LDFLAGS} readline ncurses  ${ENGINE_EXEC_LIBS} ${ENGINE_WRITE_LIBS})

install(TARGETS eryadmin DESTINATION ${ENGINE_BINDIR} COMPONENT platform)

