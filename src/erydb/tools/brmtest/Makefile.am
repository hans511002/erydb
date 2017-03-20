# $Id: Makefile.am 333 2009-04-03 20:35:04Z rdempsey $
## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(erydb_cppflags)
AM_CFLAGS = $(erydb_cflags)
AM_CXXFLAGS = $(erydb_cxxflags)
AM_LDFLAGS = $(erydb_ldflags)
bin_PROGRAMS = brmtest
brmtest_SOURCES = brmtest.cpp locks.cpp
brmtest_CPPFLAGS = -I@prefix@/erydb/include -I/usr/include/libxml2 $(AM_CPPFLAGS)
brmtest_LDFLAGS = @erydb_common_ldflags@ -lexecplan -ljoblist -lrowgroup -ldataconvert -lloggingcpp -l@boost_thread_lib@ -lbrm -lmessageqcpp -lrwlock -lconfigcpp -lxml2 -ljoiner \
-loamcpp -lsnmpmanager -l@boost_filesystem_lib@ -l@boost_date_time_lib@ @netsnmp_libs@ -lmulticast -lfuncexp $(AM_LDFLAGS)

test:

coverage:

leakcheck:

docs:

bootstrap: install-data-am

