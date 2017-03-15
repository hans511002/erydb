# $Id: Makefile.am 333 2009-04-03 20:35:04Z rdempsey $
## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(erydb_cppflags)
AM_CFLAGS = $(erydb_cflags)
AM_CXXFLAGS = $(erydb_cxxflags)
AM_LDFLAGS = $(erydb_ldflags)
bin_PROGRAMS = evalidx
evalidx_SOURCES = evalidx.cpp
evalidx_CPPFLAGS = @erydb_common_includes@ $(AM_CPPFLAGS)
evalidx_LDFLAGS = @erydb_common_ldflags@ -ldmlpackageproc -lexecplan -ljoblist -lrowgroup -lwriteengine -lbrm \
-ldataconvert -lcacheutils -ldmlpackage -lmessageqcpp -lloggingcpp -lconfigcpp -lrwlock -l@boost_thread_lib@ -lxml2 \
-ljoiner -loamcpp -lsnmpmanager -l@boost_filesystem_lib@ -l@boost_date_time_lib@ @netsnmp_libs@ -lmulticast -lfuncexp \
$(AM_LDFLAGS)

test:

coverage:

leakcheck:

docs:

bootstrap: install-data-am

