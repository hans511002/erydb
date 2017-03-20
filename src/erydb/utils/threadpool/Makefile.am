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

# $Id: Makefile.am 3194 2012-07-24 13:15:08Z rdempsey $
## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(erydb_common_includes) $(erydb_cppflags)
AM_CFLAGS = $(erydb_cflags)
AM_CXXFLAGS = $(erydb_cxxflags)
AM_LDFLAGS = -version-info 1:0:0 $(erydb_ldflags)
lib_LTLIBRARIES = libthreadpool.la
libthreadpool_la_SOURCES = weightedthreadpool.cpp threadpool.cpp prioritythreadpool.cpp
include_HEADERS = weightedthreadpool.h threadpool.h prioritythreadpool.h

test:

coverage:

leakcheck:

docs:

bootstrap: install-data-am

