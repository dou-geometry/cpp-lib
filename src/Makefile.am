AUTOMAKE_OPTIONS = subdir-objects foreign

SUBDIRS = test

bin_PROGRAMS = $(top_builddir)/bin/main \
			   $(top_builddir)/bin/JROFI \
			   $(top_builddir)/bin/test/refraction \
			   $(top_builddir)/bin/CMF
__top_builddir__bin_main_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_main_SOURCES = main.cc

__top_builddir__bin_JROFI_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_JROFI_SOURCES = JROFI/main.cc

__top_builddir__bin_test_refraction_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_test_refraction_SOURCES = JROFI/test/refraction.cc

__top_builddir__bin_CMF_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_CMF_SOURCES = CMF/main.cc
