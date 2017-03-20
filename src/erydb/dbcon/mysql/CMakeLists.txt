
include_directories( ${ENGINE_COMMON_INCLUDES}
                     /usr/include/libxml2 )


SET ( liberymysql_SRCS
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
    ha_pseudocolumn.cpp)

add_definitions(-DMYSQL_DYNAMIC_PLUGIN)

set_source_files_properties(ha_erydb.cpp PROPERTIES COMPILE_FLAGS "-fno-rtti -fno-implicit-templates")

add_library(erymysql SHARED ${liberymysql_SRCS})

target_link_libraries(erymysql ${ENGINE_LDFLAGS} ${ENGINE_WRITE_LIBS} ${NETSNMP_LIBRARIES} threadpool)

set_target_properties(erymysql PROPERTIES VERSION 1.0.0 SOVERSION 1)

SET ( is_erydb_tables_SRCS
    is_erydb_tables.cpp
    )
add_library(is_erydb_tables SHARED ${is_erydb_tables_SRCS})

target_link_libraries(is_erydb_tables ${ENGINE_LDFLAGS} ${ENGINE_WRITE_LIBS} threadpool)

# Don't prepend .so file with 'lib'
set_target_properties(is_erydb_tables PROPERTIES PREFIX "")
set_target_properties(is_erydb_tables PROPERTIES VERSION 1.0.0 SOVERSION 1)

SET ( is_erydb_columns_SRCS
    is_erydb_columns.cpp
    )
add_library(is_erydb_columns SHARED ${is_erydb_columns_SRCS})

target_link_libraries(is_erydb_columns ${ENGINE_LDFLAGS} ${ENGINE_WRITE_LIBS} threadpool)

# Don't prepend .so file with 'lib'
set_target_properties(is_erydb_columns PROPERTIES PREFIX "")
set_target_properties(is_erydb_columns PROPERTIES VERSION 1.0.0 SOVERSION 1)

SET ( is_erydb_extents_SRCS
    is_erydb_extents.cpp
    )
add_library(is_erydb_extents SHARED ${is_erydb_extents_SRCS})

target_link_libraries(is_erydb_extents ${ENGINE_LDFLAGS} ${ENGINE_WRITE_LIBS} threadpool)

# Don't prepend .so file with 'lib'
set_target_properties(is_erydb_extents PROPERTIES PREFIX "")
set_target_properties(is_erydb_extents PROPERTIES VERSION 1.0.0 SOVERSION 1)

SET ( is_erydb_files_SRCS
    is_erydb_files.cpp
    )
add_library(is_erydb_files SHARED ${is_erydb_files_SRCS})

target_link_libraries(is_erydb_files ${ENGINE_LDFLAGS} ${ENGINE_WRITE_LIBS} threadpool)

# Don't prepend .so file with 'lib'
set_target_properties(is_erydb_files PROPERTIES PREFIX "")
set_target_properties(is_erydb_files PROPERTIES VERSION 1.0.0 SOVERSION 1)


install(TARGETS erymysql is_erydb_tables is_erydb_columns is_erydb_extents is_erydb_files DESTINATION ${ENGINE_LIBDIR} COMPONENT storage-engine)
install(FILES syscatalog_mysql.sql 
              dumpcat_mysql.sql 
              calsetuserpriority.sql 
              calremoveuserpriority.sql 
              calshowprocesslist.sql 
              erydb_info.sql
              my.cnf
              DESTINATION ${ENGINE_MYSQLDIR} COMPONENT storage-engine)
install(PROGRAMS install_erydb_mysql.sh mysql-erydb dumpcat.pl
              DESTINATION ${ENGINE_MYSQLDIR} COMPONENT storage-engine)


#AM_CPPFLAGS = $(erydb_common_includes) $(erydb_cppflags)
#AM_CFLAGS = $(erydb_cflags)
#AM_CXXFLAGS = $(erydb_cxxflags)
#AM_LDFLAGS = $(erydb_ldflags)
#lib_LTLIBRARIES = liberymysql.la
#liberymysql_la_SOURCES = ha_erydb.cpp ha_erydb_impl.cpp ha_erydb_dml.cpp ha_erydb_ddl.cpp ha_erydb_execplan.cpp ha_scalar_sub.cpp ha_in_sub.cpp ha_exists_sub.cpp ha_from_sub.cpp ha_select_sub.cpp ha_view.cpp sm.cpp ha_window_function.cpp ha_erydb_partition.cpp ha_pseudocolumn.cpp
#liberymysql_la_LDFLAGS = -version-info 1:0:0 $(erydb_common_ldflags) $(erydb_common_libs) $(erydb_write_libs) $(AM_LDFLAGS)
#liberymysql_la_CPPFLAGS = -I/usr/include/libxml2 -I../../../mysql/include -I../../../mysql/sql -I../../../mysql/regex -DMYSQL_DYNAMIC_PLUGIN $(AM_CPPFLAGS)
#include_HEADERS = erydb_mysql.h
#
#dist_mysql_DATA = syscatalog_mysql.sql dumpcat_mysql.sql calsetuserpriority.sql calremoveuserpriority.sql calshowprocesslist.sql my.cnf
#dist_mysql_SCRIPTS = install_erydb_mysql.sh mysql-erydb dumpcat.pl
#
#liberymysql_la-ha_erydb.lo: ha_erydb.cpp
#    if $(LIBTOOL) --tag=CXX --mode=compile $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(liberymysql_la_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) -fno-rtti -fno-implicit-templates -MT liberymysql_la-ha_erydb.lo -MD -MP -MF "$(DEPDIR)/libcalmysql_la-ha_erydb.Tpo" -c -o libcalmysql_la-ha_erydb.lo `test -f 'ha_erydb.cpp' || echo '$(srcdir)/'`ha_erydb.cpp; \
#    then mv -f "$(DEPDIR)/liberymysql_la-ha_erydb.Tpo" "$(DEPDIR)/liberymysql_la-ha_erydb.Plo"; else rm -f "$(DEPDIR)/libcalmysql_la-ha_erydb.Tpo"; exit 1; fi

