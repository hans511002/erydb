
include_directories( ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(erydbSupport_SRCS erydbSupport.cpp)

add_executable(erydbSupport ${erydbSupport_SRCS})

target_link_libraries(erydbSupport ${ENGINE_LDFLAGS} readline ncurses  ${ENGINE_EXEC_LIBS})

install(TARGETS erydbSupport DESTINATION ${ENGINE_BINDIR} COMPONENT platform)

install(PROGRAMS alarmReport.sh bulklogReport.sh configReport.sh hadoopReport.sh 
    hardwareReport.sh logReport.sh resourceReport.sh softwareReport.sh 
    DESTINATION ${ENGINE_BINDIR} COMPONENT platform)
              
