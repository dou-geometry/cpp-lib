include_HEADERS = integration.hh rk4.hh func.hh
EXTRA_DIST = integration.tt rk4.tt func.tt
lib_LIBRARIES = libnumintegration.a libnumfunc.a
lib_LTLIBRARIES = libnumrk4.la
libnumintegration_a_SOURCES = integration.cc
libnumfunc_a_SOURCES = func.cc
libnumrk4_la_SOURCES = rk4.cc
libnumrk4_la_LIBADD = ../signal/libsignalhandle.la
