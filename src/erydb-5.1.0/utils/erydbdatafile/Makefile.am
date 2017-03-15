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

# $Id$
## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(erydb_common_includes) $(erydb_cppflags)
AM_CFLAGS = $(erydb_cflags)
AM_CXXFLAGS = $(erydb_cxxflags)
AM_LDFLAGS = -version-info 1:0:0 $(erydb_ldflags)
lib_LTLIBRARIES = liberydbdatafile.la

liberydbdatafile_la_SOURCES = \
BufferedFile.cpp \
ERYDBDataFile.cpp \
ERYDBFactory.cpp \
ERYDBFileSystem.cpp \
ERYDBLogger.cpp \
ERYDBPolicy.cpp \
PosixFileSystem.cpp \
UnbufferedFile.cpp

include_HEADERS = \
BufferedFile.h \
FileFactoryBase.h \
ERYDBDataFile.h \
ERYDBFactory.h \
ERYDBFileSystem.h \
ERYDBLogger.h \
ERYDBPolicy.h \
largefile64.h \
utility.h

test:

coverage:

leakcheck:

docs:

bootstrap: install-data-am

