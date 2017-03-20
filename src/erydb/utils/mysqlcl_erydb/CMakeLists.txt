
include_directories( /usr/include/libxml2 ${ENGINE_COMMON_INCLUDES} )


########### next target ###############

set(mysqlcl_erydb_LIB_SRCS
    column.cc
    command.cc
    conn.cc
    conn_uds.cc
    drizzle.cc
    field.cc
    handshake.cc
    pack.cc
    query.cc
    result.cc
    row.cc
    sha1.cc
    state.cc)

add_library(mysqlcl_erydb SHARED ${mysqlcl_erydb_LIB_SRCS})

set_target_properties(mysqlcl_erydb PROPERTIES VERSION 1.0.0 SOVERSION 1)

install(TARGETS mysqlcl_erydb DESTINATION ${ENGINE_LIBDIR} COMPONENT libs)

