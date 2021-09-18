AM_CPPFLAGS = -I$(top_srcdir)/include

AUTOMAKE_OPTIONS = subdir-objects foreign

lib_LTLIBRARIES = JROFI/libdouIvSR.la JROFI/libdouIgN.la

JROFI_libdouIvSR_la_SOURCES = JROFI/IvSR.cc
JROFI_libdouIvSR_la_LDFLAGS = -shared
JROFI_libdouIgN_la_SOURCES = JROFI/IgN.cc
noinst_HEADERS = JROFI/IvSR.hh JROFI/IgN.hh

SUBDIRS = test

bin_PROGRAMS = $(top_builddir)/bin/main \
			   $(top_builddir)/bin/JROFI/JROFI \
			   $(top_builddir)/bin/test/refraction \
			   $(top_builddir)/bin/CMF \
			   $(top_builddir)/bin/JROFI/OelWasser \
			   $(top_builddir)/bin/JROFI/SRv-I \
			   $(top_builddir)/bin/JROFI/SRvelAdd \
			   $(top_builddir)/bin/JROFI/NGrav-I \
			   $(top_builddir)/bin/JROFI/NGravCorrect \
			   $(top_builddir)/bin/JROFI/discreteRefracLayers
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
__top_builddir__bin_JROFI_NGrav_I_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/conn/signal/libsignalhandle.la ../lib/numerical/libnumintegration.a ../lib/numerical/libnumrk4.la JROFI/libdouIgN.la
__top_builddir__bin_JROFI_NGrav_I_SOURCES = JROFI/NGrav=I.cc
__top_builddir__bin_JROFI_NGravCorrect_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/conn/signal/libsignalhandle.la ../lib/numerical/libnumintegration.a ../lib/numerical/libnumrk4.la JROFI/libdouIgN.la
__top_builddir__bin_JROFI_NGravCorrect_SOURCES = JROFI/NGravCorrect.cc
__top_builddir__bin_JROFI_discreteRefracLayers_LDADD = ../lib/cls/libinstkarabinerhaken.a ../lib/cls/libinstoricoord.a ../lib/cls/libinstorimono.a
__top_builddir__bin_JROFI_discreteRefracLayers_SOURCES = JROFI/discreteRefracLayers.cc

__top_builddir__bin_test_refraction_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/conn/signal/libsignalhandle.la ../lib/numerical/libnumintegration.a ../lib/numerical/libnumrk4.la
__top_builddir__bin_test_refraction_SOURCES = JROFI/test/refraction.cc

__top_builddir__bin_CMF_LDADD = ../lib/conn/bash/libbashstdout.a ../lib/conn/sage/libsageplot.a ../lib/numerical/libnumintegration.a
__top_builddir__bin_CMF_SOURCES = CMF/main.cc
