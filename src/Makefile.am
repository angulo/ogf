LIBRARY_VERSION = 0:1:0

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(OGF_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

lib_LTLIBRARIES = libogf-0.1.la

libogf_0_1_la_SOURCES = OGF/Scene.cpp 
libogf_0_1_la_LDFLAGS = -version-info $(LIBRARY_VERSION)
libogf_0_1_la_LIBADD = $(OGF_LIBS)

library_includedir = $(includedir)/OGF/
library_include_HEADERS = OGF.h OGF/Scene.h
