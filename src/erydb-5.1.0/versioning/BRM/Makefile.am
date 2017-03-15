# Copyright (C) 2014 EryDB, Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; version 2 of
# the License.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.

# $Id: Makefile.am 864 2009-04-02 19:22:49Z rdempsey $
## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(erydb_common_includes) $(erydb_cppflags)
AM_CFLAGS = $(erydb_cflags)
AM_CXXFLAGS = $(erydb_cxxflags)
AM_LDFLAGS = $(erydb_ldflags)
lib_LTLIBRARIES = libbrm.la
libbrm_la_SOURCES = autoincrementmanager.cpp \
blockresolutionmanager.cpp \
brmshmimpl.cpp \
brmtypes.cpp \
copylocks.cpp \
dbrm.cpp \
extentmap.cpp \
lbidresourcegraph.cpp \
logicalpartition.cpp \
mastersegmenttable.cpp \
oidserver.cpp \
resourcenode.cpp \
rgnode.cpp \
rwlockmonitor.cpp \
sessionmanagerserver.cpp \
shmkeys.cpp \
slavedbrmnode.cpp \
slavecomm.cpp \
tablelockserver.cpp \
tracer.cpp \
transactionnode.cpp \
undoable.cpp \
vbbm.cpp \
vss.cpp
libbrm_la_LDFLAGS = -version-info 1:0:0 $(AM_LDFLAGS)
libbrm_la_CXXFLAGS = $(march_flags) $(AM_CXXFLAGS)
include_HEADERS = blockresolutionmanager.h \
brm.h \
brmshmimpl.h \
brmtypes.h \
copylocks.h \
dbrm.h \
extentmap.h \
logicalpartition.h \
mastersegmenttable.h \
sessionmanagerserver.h \
shmkeys.h \
slavecomm.h \
slavedbrmnode.h \
tracer.h \
undoable.h \
vbbm.h \
vss.h

bin_PROGRAMS = controllernode workernode dbrmctl reset_locks rollback save_brm load_brm

controllernode_SOURCES = masternode.cpp masterdbrmnode.cpp
controllernode_LDFLAGS = $(erydb_common_ldflags) $(erydb_oam_libs) $(erydb_exec_libs) $(netsnmp_libs) $(AM_LDFLAGS)
controllernode_LDADD = libbrm.la

workernode_SOURCES = slavenode.cpp
workernode_LDFLAGS = $(erydb_common_ldflags) $(erydb_oam_libs) $(erydb_exec_libs) $(netsnmp_libs) $(AM_LDFLAGS)
workernode_LDADD = libbrm.la

dbrmctl_SOURCES = dbrmctl.cpp
dbrmctl_LDFLAGS = $(erydb_common_ldflags) $(erydb_oam_libs) $(erydb_exec_libs) $(netsnmp_libs) $(AM_LDFLAGS)
dbrmctl_LDADD = libbrm.la

reset_locks_SOURCES = reset_locks.cpp
reset_locks_LDFLAGS = $(erydb_common_ldflags) $(erydb_oam_libs) $(erydb_exec_libs) $(netsnmp_libs) $(AM_LDFLAGS)
reset_locks_LDADD = libbrm.la

rollback_SOURCES = rollback.cpp
rollback_LDFLAGS = $(erydb_common_ldflags) $(erydb_oam_libs) $(erydb_exec_libs) $(netsnmp_libs) $(AM_LDFLAGS)
rollback_LDADD = libbrm.la

save_brm_SOURCES = save_brm.cpp
save_brm_LDFLAGS = $(erydb_common_ldflags) $(erydb_oam_libs) $(erydb_exec_libs) $(netsnmp_libs) $(AM_LDFLAGS)
save_brm_LDADD = libbrm.la

load_brm_SOURCES = load_brm.cpp
load_brm_LDFLAGS = $(erydb_common_ldflags) $(erydb_oam_libs) $(erydb_exec_libs) $(netsnmp_libs) $(AM_LDFLAGS)
load_brm_LDADD = libbrm.la

.PHONY: dbrm
.PRECIOUS: dbrm
dbrm: controllernode workernode dbrmctl 

tools: reset_locks rollback save_brm load_brm

install_dbrm:

install_tools:

test-dbrm:

test:

coverage:

leakcheck:

docs:

bootstrap: install-data-am

