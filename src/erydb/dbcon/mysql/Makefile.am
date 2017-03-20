#  Copyright (C) 2014 EryDB, Inc.
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; version 2 of
#  the License.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
#  MA 02110-1301, USA.
AM_CPPFLAGS = $(erydb_common_includes) $(erydb_cppflags)
AM_CFLAGS = $(erydb_cflags)
AM_CXXFLAGS = $(erydb_cxxflags)
AM_LDFLAGS = $(erydb_ldflags)
lib_LTLIBRARIES = liberymysql.la
liberymysql_la_SOURCES = ha_erydb.cpp ha_erydb_impl.cpp ha_erydb_dml.cpp ha_erydb_ddl.cpp ha_erydb_execplan.cpp ha_scalar_sub.cpp ha_in_sub.cpp ha_exists_sub.cpp ha_from_sub.cpp ha_select_sub.cpp ha_view.cpp sm.cpp ha_window_function.cpp ha_erydb_partition.cpp ha_pseudocolumn.cpp
liberymysql_la_LDFLAGS = -version-info 1:0:0 $(erydb_common_ldflags) $(erydb_common_libs) $(erydb_write_libs) $(AM_LDFLAGS)
liberymysql_la_CPPFLAGS = -I/usr/include/libxml2 -I../../../mysql/include -I../../../mysql/sql -I../../../mysql/regex -DMYSQL_DYNAMIC_PLUGIN $(AM_CPPFLAGS)
include_HEADERS = erydb_mysql.h

dist_mysql_DATA = syscatalog_mysql.sql dumpcat_mysql.sql calsetuserpriority.sql calremoveuserpriority.sql calshowprocesslist.sql my.cnf
dist_mysql_SCRIPTS = install_erydb_mysql.sh mysql-erydb dumpcat.pl

test:

coverage:

leakcheck:

docs:

bootstrap: install-data-am

liberymysql_la-ha_erydb.lo: ha_erydb.cpp
	if $(LIBTOOL) --tag=CXX --mode=compile $(CXX) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(liberymysql_la_CPPFLAGS) $(CPPFLAGS) $(AM_CXXFLAGS) $(CXXFLAGS) -fno-rtti -fno-implicit-templates -MT liberymysql_la-ha_erydb.lo -MD -MP -MF "$(DEPDIR)/libcalmysql_la-ha_erydb.Tpo" -c -o libcalmysql_la-ha_erydb.lo `test -f 'ha_erydb.cpp' || echo '$(srcdir)/'`ha_erydb.cpp; \
	then mv -f "$(DEPDIR)/liberymysql_la-ha_erydb.Tpo" "$(DEPDIR)/liberymysql_la-ha_erydb.Plo"; else rm -f "$(DEPDIR)/libcalmysql_la-ha_erydb.Tpo"; exit 1; fi

