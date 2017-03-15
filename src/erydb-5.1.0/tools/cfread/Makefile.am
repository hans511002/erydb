# $Id: Makefile.am 333 2009-04-03 20:35:04Z rdempsey $
## Process this file with automake to produce Makefile.in

AM_CPPFLAGS = $(erydb_cppflags)
AM_CFLAGS = $(erydb_cflags)
AM_CXXFLAGS = $(erydb_cxxflags)
AM_LDFLAGS = $(erydb_ldflags)
bin_PROGRAMS = cfread mtread
cfread_SOURCES = cfread.cpp
cfread_CPPFLAGS = @erydb_common_includes@ $(AM_CPPFLAGS)
cfread_LDFLAGS = @erydb_common_ldflags@ -lpthread -lwriteengine -lbrm -lrwlock -lmessageqcpp -ldl -lconfigcpp -lxml2 -lloggingcpp -lcacheutils -lboost_erydb -lpthread -lrt $(AM_LDFLAGS)
mtread_SOURCES = mtread.cpp
mtread_CPPFLAGS = @erydb_common_includes@ $(AM_CPPFLAGS)
mtread_LDFLAGS = @erydb_common_ldflags@ -lpthread -lwriteengine -lbrm -lrwlock -lmessageqcpp -ldl -lconfigcpp -lxml2 -lloggingcpp -lcacheutils -lboost_erydb -lpthread -lrt $(AM_LDFLAGS)

test:

coverage:

leakcheck:

docs:

bootstrap: install-data-am

