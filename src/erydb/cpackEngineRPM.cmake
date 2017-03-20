IF(RPM)

SET(CMAKE_INSTALL_PREFIX ${INSTALL_ENGINE})

SET(CPACK_GENERATOR "RPM")
SET(CPACK_RPM_PACKAGE_DEBUG 1)
SET(CPACK_PACKAGING_INSTALL_PREFIX ${INSTALL_ENGINE})
CMAKE_MINIMUM_REQUIRED(VERSION 2.8.7)

SET(CPACK_RPM_COMPONENT_INSTALL ON)

SET(CPACK_COMPONENTS_ALL platform libs storage-engine)

SET(CPACK_PACKAGE_NAME "erydb")
SET(ENGINE_ARCH "x86_64")

IF (NOT CPACK_RPM_PACKAGE_VERSION)
SET (CPACK_RPM_PACKAGE_VERSION ${PACKAGE_VERSION})
ENDIF()
IF (NOT CPACK_RPM_PACKAGE_RELEASE)
SET (CPACK_RPM_PACKAGE_RELEASE ${PACKAGE_RELEASE})
ENDIF()

SET(CPACK_RPM_PACKAGE_NAME ${CPACK_PACKAGE_NAME})
SET(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_RPM_PACKAGE_VERSION}-${CPACK_RPM_PACKAGE_RELEASE}-${ENGINE_ARCH}-${RPM}")

SET(CPACK_PACKAGE_DESCRIPTION_SUMMARY "erydb: a very fast and robust SQL database server")
SET(CPACK_PACKAGE_URL "http://mariadb.org")

SET(CPACK_PACKAGE_SUMMARY "Erydb software")
SET(CPACK_PACKAGE_VENDOR "MariaDB Corporation Ab")
SET(CPACK_PACKAGE_LICENSE "Copyright (c) 2016 MariaDB Corporation Ab., all rights reserved; redistributable under the terms of the GPL, see the file COPYING for details.")


SET(CPACK_RPM_PACKAGE_LICENSE "GPLv2")
SET(CPACK_RPM_PACKAGE_RELOCATABLE FALSE)
SET(CPACK_PACKAGE_RELOCATABLE FALSE)
SET(CPACK_RPM_PACKAGE_GROUP "Applications/Databases")
SET(CPACK_RPM_PACKAGE_URL ${CPACK_PACKAGE_URL})
SET(CPACK_RPM_PACKAGE_SUMMARY ${CPACK_PACKAGE_SUMMARY})
SET(CPACK_RPM_PACKAGE_VENDOR ${CPACK_PACKAGE_VENDOR})
SET(CPACK_RPM_PACKAGE_LICENSE ${CPACK_PACKAGE_LICENSE})

SET(CPACK_RPM_PACKAGE_DESCRIPTION "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}

It is GPL v2 licensed, which means you can use the it free of charge under the
conditions of the GNU General Public License Version 2 (http://www.gnu.org/licenses/).

MariaDB documentation can be found at https://mariadb.com/kb
MariaDB bug reports should be submitted through https://jira.mariadb.org 

")

SET(CPACK_RPM_platform_PACKAGE_DESCRIPTION "Erydb binary files")
SET(CPACK_RPM_platform_PACKAGE_SUMMARY "Erydb software binaries")
SET(CPACK_RPM_platform_PACKAGE_GROUP "Applications")

SET(CPACK_RPM_libs_PACKAGE_DESCRIPTION "Erydb libraries")
SET(CPACK_RPM_libs_PACKAGE_SUMMARY "Erydb software libraries")

SET(CPACK_RPM_storage-engine_PACKAGE_DESCRIPTION "erydb connector binary files")
SET(CPACK_RPM_storage-engine_PACKAGE_SUMMARY "Erydb software MariaDB connector")
SET(CPACK_RPM_storage-engine_PACKAGE_GROUP "Applications")

# "set/append array" - append a set of strings, separated by a space
MACRO(SETA var)
  FOREACH(v ${ARGN})
    SET(${var} "${${var}} ${v}")
  ENDFOREACH()
ENDMACRO(SETA)

SETA(CPACK_RPM_libs_PACKAGE_PROVIDES "erydb-libs")
SETA(CPACK_RPM_platform_PACKAGE_PROVIDES "erydb-platform")
SETA(CPACK_RPM_storage-engine_PACKAGE_PROVIDES "erydb-storage-engine")

# Boost is a source build in CentOS 6 so don't require it as a package
SET(REDHAT_VERSION_NUMBER OFF)
SET(SUSE_VERSION_NUMBER OFF)
IF (EXISTS "/etc/redhat-release")
    file (READ "/etc/redhat-release" REDHAT_VERSION)
    string(REGEX MATCH "release ([0-9]+)" CENTOS "${REDHAT_VERSION}")
    set(REDHAT_VERSION_NUMBER "${CMAKE_MATCH_1}")
ENDIF ()
IF (EXISTS "/etc/SuSE-release")
    file (READ "/etc/SuSE-release" SUSE_VERSION)
    string(REGEX MATCH "VERSION = ([0-9]+)" SUSE "${SUSE_VERSION}")
    set(SUSE_VERSION_NUMBER "${CMAKE_MATCH_1}")
ENDIF ()
if (${REDHAT_VERSION_NUMBER} EQUAL 6)
    SETA(CPACK_RPM_platform_PACKAGE_REQUIRES "expect" "erydb-libs")
    # Disable auto require as this will also try to pull Boost via RPM
    SET(CPACK_RPM_PACKAGE_AUTOREQPROV " no")
elseif (${SUSE_VERSION_NUMBER} EQUAL 12)
   SETA(CPACK_RPM_platform_PACKAGE_REQUIRES "expect" "boost-devel >= 1.54.0" "erydb-libs")
else ()
   SETA(CPACK_RPM_platform_PACKAGE_REQUIRES "expect" "boost >= 1.53.0" "erydb-libs")
endif()

SETA(CPACK_RPM_storage-engine_PACKAGE_REQUIRES "erydb-libs")

SET(CPACK_RPM_platform_POST_INSTALL_SCRIPT_FILE ${CMAKE_SOURCE_DIR}/build/postInstall_platform.sh)
SET(CPACK_RPM_libs_POST_INSTALL_SCRIPT_FILE ${CMAKE_SOURCE_DIR}/build/postInstall_libs.sh)
SET(CPACK_RPM_storage-engine_POST_INSTALL_SCRIPT_FILE ${CMAKE_SOURCE_DIR}/build/postInstall_storage_engine.sh)

SET(CPACK_RPM_platform_PRE_UNINSTALL_SCRIPT_FILE ${CMAKE_SOURCE_DIR}/build/preUn_platform.sh)
SET(CPACK_RPM_libs_PRE_UNINSTALL_SCRIPT_FILE ${CMAKE_SOURCE_DIR}/build/preUn_libs.sh)
SET(CPACK_RPM_storage-engine_PRE_UNINSTALL_SCRIPT_FILE ${CMAKE_SOURCE_DIR}/build/preUn_storage_engine.sh)

SET(CPACK_RPM_SPEC_MORE_DEFINE "${CPACK_RPM_SPEC_MORE_DEFINE}
%define ignore \#
")

SET(ignored
    "%ignore /usr"
    "%ignore /usr/local"
)

#SET(CPACK_RPM_SPEC_MORE_DEFINE "
#%define _prefix ${CMAKE_INSTALL_PREFIX}
#")

SET(CPACK_RPM_platform_USER_FILELIST
"/usr/local/erydb/bin/DDLProc"
"/usr/local/erydb/bin/ExeMgr"
"/usr/local/erydb/bin/ProcMgr"
"/usr/local/erydb/bin/ProcMon"
"/usr/local/erydb/bin/DMLProc"
"/usr/local/erydb/bin/WriteEngineServer"
"/usr/local/erydb/bin/cpimport"
"/usr/local/erydb/bin/post-install"
"/usr/local/erydb/bin/post-mysql-install"
"/usr/local/erydb/bin/post-mysqld-install"
"/usr/local/erydb/bin/pre-uninstall"
"/usr/local/erydb/bin/PrimProc"
"/usr/local/erydb/bin/DecomSvr"
"/usr/local/erydb/bin/upgrade-erydb.sh"
"/usr/local/erydb/bin/run.sh"
"/usr/local/erydb/bin/erydb"
"/usr/local/erydb/bin/erydbSyslog"
"/usr/local/erydb/bin/erydbSyslog7"
"/usr/local/erydb/bin/erydbSyslog-ng" 
"/usr/local/erydb/bin/syslogSetup.sh"
"/usr/local/erydb/bin/cplogger"
"/usr/local/erydb/bin/erydb.def"
"/usr/local/erydb/bin/dbbuilder"
"/usr/local/erydb/bin/cpimport.bin"
"/usr/local/erydb/bin/load_brm"
"/usr/local/erydb/bin/save_brm"
"/usr/local/erydb/bin/dbrmctl"
"/usr/local/erydb/bin/controllernode"
"/usr/local/erydb/bin/reset_locks"
"/usr/local/erydb/bin/workernode"
"/usr/local/erydb/bin/colxml"
"/usr/local/erydb/bin/clearShm"
"/usr/local/erydb/bin/viewtablelock"
"/usr/local/erydb/bin/cleartablelock"
"/usr/local/erydb/bin/eryadmin"
"/usr/local/erydb/bin/remote_command.sh"
"/usr/local/erydb/bin/postConfigure"
"/usr/local/erydb/bin/erydbLogRotate"
"/usr/local/erydb/bin/transactionLog"
"/usr/local/erydb/bin/erydbDBWrite"
"/usr/local/erydb/bin/transactionLogArchiver.sh"
"/usr/local/erydb/bin/installer"
"/usr/local/erydb/bin/module_installer.sh"
"/usr/local/erydb/bin/user_installer.sh"
"/usr/local/erydb/bin/performance_installer.sh"
"/usr/local/erydb/bin/startupTests.sh"
"/usr/local/erydb/bin/os_check.sh"
"/usr/local/erydb/bin/remote_scp_put.sh"
"/usr/local/erydb/bin/remotessh.exp"
"/usr/local/erydb/bin/ServerMonitor"
"/usr/local/erydb/bin/master-rep-erydb.sh" 
"/usr/local/erydb/bin/slave-rep-erydb.sh"
"/usr/local/erydb/bin/rsync.sh"
"/usr/local/erydb/bin/erydbSupport"
"/usr/local/erydb/bin/hardwareReport.sh"
"/usr/local/erydb/bin/softwareReport.sh"
"/usr/local/erydb/bin/configReport.sh"
"/usr/local/erydb/bin/logReport.sh"
"/usr/local/erydb/bin/bulklogReport.sh"
"/usr/local/erydb/bin/resourceReport.sh"
"/usr/local/erydb/bin/hadoopReport.sh"
"/usr/local/erydb/bin/alarmReport.sh"
"/usr/local/erydb/bin/amazonInstaller"
"/usr/local/erydb/bin/remote_command_verify.sh"
"/usr/local/erydb/bin/disable-rep-erydb.sh"
"/usr/local/erydb/bin/erydb.service"
"/usr/local/erydb/etc/MessageFile.txt"
"/usr/local/erydb/etc/ErrorMessage.txt"
"/usr/local/erydb/local/module"
"/usr/local/erydb/releasenum"
"/usr/local/erydb/bin/rollback"
"/usr/local/erydb/bin/editem"
"/usr/local/erydb/bin/getConfig"
"/usr/local/erydb/bin/setConfig"
"/usr/local/erydb/bin/setenv-hdfs-12"
"/usr/local/erydb/bin/setenv-hdfs-20"
"/usr/local/erydb/bin/configxml.sh"
"/usr/local/erydb/bin/remote_scp_get.sh"
"/usr/local/erydb/bin/erydbAlias"
"/usr/local/erydb/bin/autoConfigure"
"/usr/local/erydb/bin/ddlcleanup"
"/usr/local/erydb/bin/erydbmeminfo"
"/usr/local/erydb/bin/MCSInstanceCmds.sh"
"/usr/local/erydb/bin/MCSVolumeCmds.sh"
"/usr/local/erydb/bin/binary_installer.sh" 
"/usr/local/erydb/bin/myCnf-include-args.text" 
"/usr/local/erydb/bin/myCnf-exclude-args.text"
"/usr/local/erydb/bin/mycnfUpgrade"
"/usr/local/erydb/bin/getMySQLpw"
"/usr/local/erydb/bin/erydb.conf"
"/usr/local/erydb/post/functions"
"/usr/local/erydb/post/test-001.sh"
"/usr/local/erydb/post/test-002.sh"
"/usr/local/erydb/post/test-003.sh"
"/usr/local/erydb/post/test-004.sh"
${ignored})

SET(CPACK_RPM_libs_USER_FILELIST 
"/usr/local/erydb/lib/libconfigcpp.so.1.0.0"
"/usr/local/erydb/lib/libconfigcpp.so.1"
"/usr/local/erydb/lib/libconfigcpp.so"
"/usr/local/erydb/lib/libddlpackageproc.so.1.0.0"
"/usr/local/erydb/lib/libddlpackageproc.so.1"
"/usr/local/erydb/lib/libddlpackageproc.so"
"/usr/local/erydb/lib/libddlpackage.so.1.0.0"
"/usr/local/erydb/lib/libddlpackage.so.1"
"/usr/local/erydb/lib/libddlpackage.so"
"/usr/local/erydb/lib/libdmlpackageproc.so.1.0.0"
"/usr/local/erydb/lib/libdmlpackageproc.so.1"
"/usr/local/erydb/lib/libdmlpackageproc.so"
"/usr/local/erydb/lib/libdmlpackage.so.1.0.0"
"/usr/local/erydb/lib/libdmlpackage.so.1"
"/usr/local/erydb/lib/libdmlpackage.so"
"/usr/local/erydb/lib/libexecplan.so.1.0.0"
"/usr/local/erydb/lib/libexecplan.so.1"
"/usr/local/erydb/lib/libexecplan.so"
"/usr/local/erydb/lib/libfuncexp.so.1.0.0"
"/usr/local/erydb/lib/libfuncexp.so.1"
"/usr/local/erydb/lib/libfuncexp.so"
"/usr/local/erydb/lib/libudfsdk.so.1.0.0"
"/usr/local/erydb/lib/libudfsdk.so.1"
"/usr/local/erydb/lib/libudfsdk.so"
"/usr/local/erydb/lib/libjoblist.so.1.0.0"
"/usr/local/erydb/lib/libjoblist.so.1"
"/usr/local/erydb/lib/libjoblist.so"
"/usr/local/erydb/lib/libjoiner.so.1.0.0"
"/usr/local/erydb/lib/libjoiner.so.1"
"/usr/local/erydb/lib/libjoiner.so"
"/usr/local/erydb/lib/libloggingcpp.so.1.0.0"
"/usr/local/erydb/lib/libloggingcpp.so.1"
"/usr/local/erydb/lib/libloggingcpp.so"
"/usr/local/erydb/lib/libmessageqcpp.so.1.0.0"
"/usr/local/erydb/lib/libmessageqcpp.so.1"
"/usr/local/erydb/lib/libmessageqcpp.so"
"/usr/local/erydb/lib/liboamcpp.so.1.0.0"
"/usr/local/erydb/lib/liboamcpp.so.1"
"/usr/local/erydb/lib/liboamcpp.so"
"/usr/local/erydb/lib/libalarmmanager.so.1.0.0"
"/usr/local/erydb/lib/libalarmmanager.so.1"
"/usr/local/erydb/lib/libalarmmanager.so"
"/usr/local/erydb/lib/libthreadpool.so.1.0.0"
"/usr/local/erydb/lib/libthreadpool.so.1"
"/usr/local/erydb/lib/libthreadpool.so"
"/usr/local/erydb/lib/libwindowfunction.so.1.0.0"
"/usr/local/erydb/lib/libwindowfunction.so.1"
"/usr/local/erydb/lib/libwindowfunction.so"
"/usr/local/erydb/lib/libwriteengine.so.1.0.0"
"/usr/local/erydb/lib/libwriteengine.so.1"
"/usr/local/erydb/lib/libwriteengine.so"
"/usr/local/erydb/lib/libwriteengineclient.so.1.0.0"
"/usr/local/erydb/lib/libwriteengineclient.so.1"
"/usr/local/erydb/lib/libwriteengineclient.so"
"/usr/local/erydb/lib/libbrm.so.1.0.0"
"/usr/local/erydb/lib/libbrm.so.1"
"/usr/local/erydb/lib/libbrm.so"
"/usr/local/erydb/lib/librwlock.so.1.0.0"
"/usr/local/erydb/lib/librwlock.so.1"
"/usr/local/erydb/lib/librwlock.so"
"/usr/local/erydb/lib/libdataconvert.so.1.0.0"
"/usr/local/erydb/lib/libdataconvert.so.1"
"/usr/local/erydb/lib/libdataconvert.so"
"/usr/local/erydb/lib/librowgroup.so.1.0.0"
"/usr/local/erydb/lib/librowgroup.so.1"
"/usr/local/erydb/lib/librowgroup.so"
"/usr/local/erydb/lib/libcacheutils.so.1.0.0"
"/usr/local/erydb/lib/libcacheutils.so.1"
"/usr/local/erydb/lib/libcacheutils.so"
"/usr/local/erydb/lib/libcommon.so.1.0.0"
"/usr/local/erydb/lib/libcommon.so.1"
"/usr/local/erydb/lib/libcommon.so"
"/usr/local/erydb/lib/libcompress.so.1.0.0"
"/usr/local/erydb/lib/libcompress.so.1"
"/usr/local/erydb/lib/libcompress.so"
"/usr/local/erydb/lib/libddlcleanuputil.so.1.0.0"
"/usr/local/erydb/lib/libddlcleanuputil.so.1"
"/usr/local/erydb/lib/libddlcleanuputil.so"
"/usr/local/erydb/lib/libbatchloader.so.1.0.0"
"/usr/local/erydb/lib/libbatchloader.so.1"
"/usr/local/erydb/lib/libbatchloader.so"
"/usr/local/erydb/lib/libmysqlcl_erydb.so.1.0.0"
"/usr/local/erydb/lib/libmysqlcl_erydb.so.1"
"/usr/local/erydb/lib/libmysqlcl_erydb.so"
"/usr/local/erydb/lib/libquerystats.so.1.0.0"
"/usr/local/erydb/lib/libquerystats.so.1"
"/usr/local/erydb/lib/libquerystats.so"
"/usr/local/erydb/lib/libwriteengineredistribute.so.1.0.0"
"/usr/local/erydb/lib/libwriteengineredistribute.so.1"
"/usr/local/erydb/lib/libwriteengineredistribute.so"
"/usr/local/erydb/lib/liberydbdatafile.so.1.0.0"
"/usr/local/erydb/lib/liberydbdatafile.so.1"
"/usr/local/erydb/lib/liberydbdatafile.so"
"/usr/local/erydb/lib/libthrift.so.1.0.0"
"/usr/local/erydb/lib/libthrift.so.1"
"/usr/local/erydb/lib/libthrift.so"
"/usr/local/erydb/lib/libquerytele.so.1.0.0"
"/usr/local/erydb/lib/libquerytele.so.1"
"/usr/local/erydb/lib/libquerytele.so"
${ignored})

SET(CPACK_RPM_storage-engine_USER_FILELIST
"/usr/local/erydb/lib/liberymysql.so.1.0.0"
"/usr/local/erydb/lib/liberymysql.so.1"
"/usr/local/erydb/lib/liberymysql.so"
"/usr/local/erydb/lib/libudf_mysql.so.1.0.0"
"/usr/local/erydb/lib/libudf_mysql.so.1"
"/usr/local/erydb/lib/libudf_mysql.so"
"/usr/local/erydb/lib/is_erydb_columns.so"
"/usr/local/erydb/lib/is_erydb_columns.so.1"
"/usr/local/erydb/lib/is_erydb_columns.so.1.0.0"
"/usr/local/erydb/lib/is_erydb_extents.so"
"/usr/local/erydb/lib/is_erydb_extents.so.1"
"/usr/local/erydb/lib/is_erydb_extents.so.1.0.0"
"/usr/local/erydb/lib/is_erydb_tables.so"
"/usr/local/erydb/lib/is_erydb_tables.so.1"
"/usr/local/erydb/lib/is_erydb_tables.so.1.0.0"
"/usr/local/erydb/lib/is_erydb_files.so"
"/usr/local/erydb/lib/is_erydb_files.so.1"
"/usr/local/erydb/lib/is_erydb_files.so.1.0.0"
"/usr/local/erydb/mysql/mysql-erydb"
"/usr/local/erydb/mysql/install_erydb_mysql.sh"
"/usr/local/erydb/mysql/syscatalog_mysql.sql"
"/usr/local/erydb/mysql/dumpcat_mysql.sql"
"/usr/local/erydb/mysql/dumpcat.pl"
"/usr/local/erydb/mysql/calsetuserpriority.sql"
"/usr/local/erydb/mysql/calremoveuserpriority.sql"
"/usr/local/erydb/mysql/calshowprocesslist.sql"
"/usr/local/erydb/mysql/erydb_info.sql"
${ignored})


INCLUDE (CPack)

ENDIF()
