AUTOMAKE_OPTIONS = subdir-objects foreign

lib_LTLIBRARIES = JROFI/libdouIvSR.la

JROFI_libdouIvSR_la_SOURCES = JROFI/IvSR.cc
#JROFI_libdouIvSR_la_LDFLAGS = -Wl,--unresolved-symbols=ignore-all
include_HEADERS = JROFI/IvSR.hh

SUBDIRS = test

bin_PROGRAMS = $(top_builddir)/bin/main \
			   $(top_builddir)/bin/JROFI/JROFI \
			   $(top_builddir)/bin/test/refraction \
			   $(top_builddir)/bin/CMF \
			   $(top_builddir)/bin/JROFI/OelWasser \
			   $(top_builddir)/bin/JROFI/SRv-I \
			   $(top_builddir)/bin/JROFI/SRvelAdd \
			   $(top_builddir)/bin/JROFI/NGrav-I
__top_builddir__bin_main_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_main_SOURCES = main.cc

__top_builddir__bin_JROFI_JROFI_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_JROFI_JROFI_SOURCES = JROFI/main.cc
__top_builddir__bin_JROFI_OelWasser_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_JROFI_OelWasser_SOURCES = JROFI/OelWasser.cc
__top_builddir__bin_JROFI_SRv_I_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/conn/signal/libsignalhandle.la ../lib/numerical/libnumintegration.a ../lib/numerical/libnumrk4.la JROFI/libdouIvSR.la
__top_builddir__bin_JROFI_SRv_I_SOURCES = JROFI/SRv=I.cc
__top_builddir__bin_JROFI_SRvelAdd_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/conn/signal/libsignalhandle.la ../lib/numerical/libnumintegration.a ../lib/numerical/libnumrk4.la JROFI/libdouIvSR.la
__top_builddir__bin_JROFI_SRvelAdd_SOURCES = JROFI/SRvelAdd.cc
__top_builddir__bin_JROFI_NGrav_I_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/conn/signal/libsignalhandle.la ../lib/numerical/libnumintegration.a ../lib/numerical/libnumrk4.la JROFI/libdouIvSR.la
__top_builddir__bin_JROFI_NGrav_I_SOURCES = JROFI/NGrav=I.cc

__top_builddir__bin_test_refraction_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/conn/signal/libsignalhandle.la ../lib/numerical/libnumintegration.a ../lib/numerical/libnumrk4.la
__top_builddir__bin_test_refraction_SOURCES = JROFI/test/refraction.cc

__top_builddir__bin_CMF_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_CMF_SOURCES = CMF/main.cc
