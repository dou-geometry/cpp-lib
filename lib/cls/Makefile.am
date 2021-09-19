AM_CPPFLAGS = -I$(top_srcdir)/include

lib_LIBRARIES = libinstcoord.a libinstoricoord.a libinstmatrix.a libinstmono.a libinstorimono.a libinstlinear.a libinstkarabinerhaken.a libinstline.a libinstfield.a libinstcov.a libinstring.a libinstsuu.a

libinstcoord_a_SOURCES = coord.cc
libinstoricoord_a_SOURCES = oricoord.cc
libinstmatrix_a_SOURCES = matrix.cc
libinstmono_a_SOURCES = mono.cc
libinstorimono_a_LIBADD = ./libinstoricoord.a
libinstorimono_a_SOURCES = orimono.cc
libinstlinear_a_SOURCES = linear.cc
libinstkarabinerhaken_a_SOURCES = Karabinerhaken.cc
libinstline_a_SOURCES = line.cc
libinstfield_a_SOURCES = field.cc
libinstcov_a_SOURCES = cov.cc
libinstring_a_SOURCES = ring.cc
libinstsuu_a_SOURCES = suu.cc
