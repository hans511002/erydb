
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(buildLic_SRCS licenseBuild.cpp)
 
add_executable(buildLic ${buildLic_SRCS})

add_dependencies(buildLic libnetsnmpmibs)

target_link_libraries(buildLic ${ENGINE_LDFLAGS} readline ncurses ${ENGINE_EXEC_LIBS})

install(TARGETS buildLic DESTINATION ${ENGINE_BINDIR})

set(licenseInfo_SRCS licenseInfo.cpp)
 
add_executable(licenseInfo ${licenseInfo_SRCS})

add_dependencies(licenseInfo libnetsnmpmibs)

target_link_libraries(licenseInfo ${ENGINE_LDFLAGS} readline ncurses ${ENGINE_EXEC_LIBS})

install(TARGETS licenseInfo DESTINATION ${ENGINE_BINDIR})

