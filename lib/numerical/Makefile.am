include_HEADERS = integration.hh rk4.hh func.hh
EXTRA_DIST = integration.tt rk4.tt func.tt
lib_LTLIBRARIES = libnumintegration.la libnumfunc.la libnumrk4.la
libnumintegration_la_SOURCES = integration.cc
libnumfunc_la_SOURCES = func.cc
libnumrk4_la_SOURCES = rk4.cc
libnumrk4_la_LIBADD = ../signal/libsignalhandle.la
