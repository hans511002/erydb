
include_directories( ${ENGINE_COMMON_INCLUDES}
                     /usr/include/libxml2 
                     ../../../mysql/include 
                     ../../../mysql/sql 
                     ../../../mysql/regex )


SET ( libcalmysql_SRCS
    ha_erydb.cpp
    ha_erydb_impl.cpp
    ha_erydb_dml.cpp
    ha_erydb_ddl.cpp
    ha_erydb_execplan.cpp
    ha_scalar_sub.cpp
    ha_in_sub.cpp
    ha_exists_sub.cpp
    ha_from_sub.cpp
    ha_select_sub.cpp
    ha_view.cpp sm.cpp
    ha_window_function.cpp
    ha_erydb_partition.cpp
    ha_pseudocolumn.cpp )

add_definitions(-DMYSQL_DYNAMIC_PLUGIN)

set_source_files_properties(ha_erydb.cpp PROPERTIES COMPILE_FLAGS "-fno-rtti -fno-implicit-templates")

add_library(calmysql SHARED ${libcalmysql_SRCS})

add_dependencies(calmysql libnetsnmpmibs)

target_link_libraries(calmysql ${ENGINE_LDFLAGS} ${ENGINE_WRITE_LIBS} threadpool)

set_target_properties(calmysql PROPERTIES VERSION 1.0.0 SOVERSION 1)

install(TARGETS calmysql DESTINATION ${ENGINE_LIBDIR})
install(FILES syscatalog_mysql.sql 
              dumpcat_mysql.sql 
              calsetuserpriority.sql 
              calremoveuserpriority.sql 
              calshowprocesslist.sql 
              my.cnf
              DESTINATION ${ENGINE_MYSQLDIR})
install(PROGRAMS install_erydb_mysql.sh mysql-erydb dumpcat.pl
              DESTINATION ${ENGINE_MYSQLDIR})


#AM_CPPFLAGS = $(erydb_common_includes) $(erydb_cppflags)
#AM_CFLAGS = $(erydb_cflags)
#AM_CXXFLAGS = $(erydb_cxxflags)
#AM_LDFLAGS = $(erydb_ldflags)
#lib_LTLIBRARIES = libcalmysql.la
#libcalmysql_la_SOURCES = ha_erydb.cpp ha_erydb_impl.cpp ha_erydb_dml.cpp ha_erydb_ddl.cpp ha_erydb_execplan.cpp ha_scalar_sub.cpp ha_in_sub.cpp ha_exists_sub.cpp ha_from_sub.cpp ha_select_sub.cpp ha_view.cpp sm.cpp ha_window_function.cpp ha_erydb_partition.cpp ha_pseudocolumn.cpp
#libcalmysql_la_LDFLAGS = -version-info 1:0:0 $(erydb_common_ldflags) $(erydb_common_libs) $(erydb_write_libs) $(AM_LDFLAGS)
#libcalmysql_la_CPPFLAGS = -I/usr/include/libxml2 -I../../../mysql/include -I../../../mysql/sql -I../../../mysql/regex -DMYSQL_DYNAMIC_PLUGIN $(AM_CPPFLAGS)
#include_HEADERS = erydb_mysql.h
#
#dist_mysql_DATA = syscatalog_mysql.sql dumpcat_mysql.sql calsetuserpriority.sql calremoveuserpriority.sql calshowprocesslist.sql my.cnf
#dist_mysql_SCRIPTS = install_erydb_mysql.sh mysql-erydb dumpcat.pl
#
#libcalmysql_la-ha_erydb.lo: ha_erydb.cpp
#    if $(LIBTOOL) --tag=CXX --mode=compile $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(libcalmysql_la_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) -fno-rtti -fno-implicit-templates -MT libcalmysql_la-ha_erydb.lo -MD -MP -MF "$(DEPDIR)/libcalmysql_la-ha_erydb.Tpo" -c -o libcalmysql_la-ha_erydb.lo `test -f 'ha_erydb.cpp' || echo '$(srcdir)/'`ha_erydb.cpp; \
#    then mv -f "$(DEPDIR)/libcalmysql_la-ha_erydb.Tpo" "$(DEPDIR)/libcalmysql_la-ha_erydb.Plo"; else rm -f "$(DEPDIR)/libcalmysql_la-ha_erydb.Tpo"; exit 1; fi

