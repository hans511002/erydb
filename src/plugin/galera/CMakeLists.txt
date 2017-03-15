
# Build mysql_fix_privilege_tables.sql (concatenate 3 sql scripts)
IF(NOT WIN32 OR CMAKE_CROSSCOMPILING)
  FIND_PROGRAM(CAT_EXECUTABLE cat DOC "path to the executable")
  MARK_AS_ADVANCED(CAT_EXECUTABLE)
ENDIF()
 

SET(HOSTNAME "hostname")
SET(MYSQLD_USER "mysql")

# Required for mysqlbug until autotools are deprecated, once done remove these
# and expand default cmake variables
SET(CC ${CMAKE_C_COMPILER})
SET(CXX ${CMAKE_CXX_COMPILER})
SET(SAVE_CC ${CMAKE_C_COMPILER})
SET(SAVE_CXX ${CMAKE_CXX_COMPILER})
SET(SAVE_CFLAGS ${CFLAGS})
SET(SAVE_CXXFLAGS ${CXXFLAGS})
# XXX no cmake equivalent for this, just make one up
SET(CONFIGURE_LINE "Built using CMake")

 
# Really ugly, one script, "mysql_install_db", needs prefix set to ".",
# i.e. makes access relative the current directory. This matches
# the documentation, so better not change this.

IF(INSTALL_LAYOUT MATCHES "STANDALONE")
  SET(prefix ".")
  SET(bindir ${prefix}/${INSTALL_BINDIR})
  SET(sbindir ${prefix}/${INSTALL_SBINDIR})
  SET(scriptdir ${prefix}/${INSTALL_BINDIR})
  SET(libexecdir ${prefix}/${INSTALL_SBINDIR})
  SET(pkgdatadir ${prefix}/${INSTALL_MYSQLSHAREDIR})
  SET(localstatedir ${prefix}/data)
ELSE()
  SET(prefix "${CMAKE_INSTALL_PREFIX}")
  SET(bindir ${INSTALL_BINDIRABS})
  SET(sbindir ${INSTALL_SBINDIRABS})
  SET(scriptdir ${INSTALL_BINDIRABS})
  SET(libexecdir ${INSTALL_SBINDIRABS})
  SET(pkgdatadir ${INSTALL_MYSQLSHAREDIRABS})
  SET(localstatedir ${MYSQL_DATADIR})
ENDIF()

SET(prefix "${CMAKE_INSTALL_PREFIX}")
IF(INSTALL_SYSCONFDIR)
  SET(sysconfdir ${DEFAULT_SYSCONFDIR})
ELSE()
  SET(sysconfdir "/etc")
ENDIF()
SET(bindir ${INSTALL_BINDIRABS})
SET(libexecdir ${INSTALL_SBINDIRABS})
SET(scriptdir ${INSTALL_BINDIRABS})
SET(datadir ${INSTALL_MYSQLSHAREDIRABS})
SET(pkgdatadir ${INSTALL_MYSQLSHAREDIRABS})
SET(libsubdir  ${INSTALL_LIBDIR})
SET(pkgincludedir ${INSTALL_INCLUDEDIRABS})
SET(pkglibdir ${INSTALL_LIBDIRABS})
SET(pkgplugindir ${INSTALL_PLUGINDIRABS})
SET(localstatedir ${MYSQL_DATADIR})

 
# some scripts use  @TARGET_LINUX@
IF(CMAKE_SYSTEM_NAME MATCHES "Linux")
  SET(TARGET_LINUX "true")
ELSE()
  SET(TARGET_LINUX "false")
ENDIF()
 

IF(UNIX)
  # On Unix, most of the files end up in the bin directory
  SET(BIN_SCRIPTS
    garb.service
    garbd
    garb-systemd
    libgalera_smm.so
  )
  FOREACH(file ${BIN_SCRIPTS})
    IF(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${file})
      CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/${file}
         ${CMAKE_CURRENT_BINARY_DIR}/${file} COPYONLY)
    ELSE()
      MESSAGE(FATAL_ERROR "Can not find  ${file} in "
        "${CMAKE_CURRENT_SOURCE_DIR}" )
    ENDIF()
    EXECUTE_PROCESS(COMMAND chmod +x ${CMAKE_CURRENT_BINARY_DIR}/${file})
    IF(NOT ${file}_COMPONENT)
      SET(${file}_COMPONENT Server)
    ENDIF()
    INSTALL_SCRIPT(
      ${CMAKE_CURRENT_BINARY_DIR}/${file} 
      DESTINATION ${INSTALL_BINDIR}
      COMPONENT ${${file}_COMPONENT}
     )
  ENDFOREACH()
ENDIF()
 
