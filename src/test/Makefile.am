AUTOMAKE_OPTIONS = subdir-objects foreign

TESTS = $(check_PROGRAMS)

check_PROGRAMS =\
				$(top_builddir)/bin/test/pendulum \
				$(top_builddir)/bin/test/ncku \
				$(top_builddir)/bin/test/condTerRK4 \
				$(top_builddir)/bin/test/sys \
				$(top_builddir)/bin/test/signal
#				$(top_builddir)/bin/test/compareOutput

__top_builddir__bin_test_pendulum_LDADD = ../../lib/conn/bash/libbashstdout.a ../../lib/conn/sage/libsageplot.a ../../lib/numerical/libnumintegration.a ../../lib/conn/signal/libsignalhandle.la
__top_builddir__bin_test_pendulum_SOURCES = pendulum-ang.cc

__top_builddir__bin_test_ncku_LDADD = ../../lib/conn/bash/libbashstdout.a ../../lib/conn/sage/libsageplot.a ../../lib/numerical/libnumintegration.a ../../lib/conn/signal/libsignalhandle.la
__top_builddir__bin_test_ncku_SOURCES = ncku.cc

__top_builddir__bin_test_condTerRK4_LDADD = ../../lib/conn/bash/libbashstdout.a ../../lib/conn/sage/libsageplot.a ../../lib/numerical/libnumintegration.a ../../lib/conn/signal/libsignalhandle.la
__top_builddir__bin_test_condTerRK4_SOURCES = condTerRK4.cc

#__top_builddir__bin_test_compareOutput_SOURCES = compareOutput.cc

#__top_builddir__bin_test_sys_LDADD = ../../lib/dou/sys/libdoucarrier.a
__top_builddir__bin_test_sys_SOURCES = sys.cc

__top_builddir__bin_test_signal_LDADD = ../../lib/conn/signal/libsignalhandle.la
__top_builddir__bin_test_signal_SOURCES = signal.cc
