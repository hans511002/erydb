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

# $Id: Makefile.am 696 2011-03-07 21:54:16Z rdempsey $
## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(erydb_common_includes) $(erydb_cppflags)
AM_CFLAGS = $(erydb_cflags)
AM_CXXFLAGS = $(erydb_cxxflags)
AM_LDFLAGS = $(erydb_ldflags)
bin_PROGRAMS = cpimport
cpimport_SOURCES = we_splitterapp.cpp \
we_cmdargs.cpp \
we_sdhandler.cpp \
we_respreadthread.cpp \
we_filereadthread.cpp \
we_splclient.cpp \
we_brmupdater.cpp \
we_tablelockgrabber.cpp \
we_xmlgetter.cpp
cpimport_LDFLAGS = $(erydb_common_ldflags) $(erydb_exec_libs) $(erydb_write_libs) ${abs_top_builddir}/utils/batchloader/libbatchloader.la ${abs_top_builddir}/utils/threadpool/libthreadpool.la $(AM_LDFLAGS)

install_splitter: install

test:

coverage:

leakcheck:

docs:

bootstrap: install-data-am

