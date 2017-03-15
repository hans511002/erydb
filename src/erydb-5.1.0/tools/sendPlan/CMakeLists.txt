
include_directories(${KDE4_INCLUDES} ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} )


########### next target ###############

set(sendPlan_SRCS sendplan.cpp)

kde4_add_executable(sendPlan ${sendPlan_SRCS})

target_link_libraries(sendPlan ${KDE4_KDECORE_LIBS})

install(TARGETS sendPlan ${INSTALL_TARGETS_DEFAULT_ARGS})


########### install files ###############




#original Makefile.am contents follow:

## $Id: Makefile.am 333 2009-04-03 20:35:04Z rdempsey $
### Process this file with automake to produce Makefile.in
#
#AM_CPPFLAGS = $(erydb_cppflags)
#AM_CFLAGS = $(erydb_cflags)
#AM_CXXFLAGS = $(erydb_cxxflags)
#AM_LDFLAGS = $(erydb_ldflags)
#bin_PROGRAMS = sendPlan
#sendPlan_SOURCES = sendplan.cpp
#sendPlan_CPPFLAGS = @erydb_common_includes@ $(AM_CPPFLAGS)
#sendPlan_LDFLAGS = @erydb_common_ldflags@ @erydb_exec_libs@ $(AM_LDFLAGS)
#
#test:
#
#coverage:
#
#leakcheck:
#
#docs:
#
#bootstrap: install-data-am
#
