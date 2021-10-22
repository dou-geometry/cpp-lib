AM_CPPFLAGS = -I$(top_srcdir)/include

lib_LIBRARIES = libnumintegration.a libnumfunc.a
lib_LTLIBRARIES = libnumrk4.la
libnumintegration_a_SOURCES = integration.cc
libnumfunc_a_SOURCES = func.cc
libnumrk4_la_SOURCES = rk4.cc
libnumrk4_la_LIBADD = ../conn/signal/libsignalhandle.la
