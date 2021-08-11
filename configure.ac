#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Dou-geometry-Cpp-Library], [v0-alpha], [fudepia@outlook.jp])
AM_INIT_AUTOMAKE([-Wall -Werror foreign subdir-objects])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_LANG([C++])
AX_CHECK_COMPILE_FLAG([-std=gnu++20 -lquadmath -g3], [CXXFLAGS="$CXXFLAGS -std=gnu++20 -lquadmath -g3"])
AM_CXXFLAGS="-std=gnu++20 -lquadmath -g3"
AC_PROG_CXX

AC_PROG_AWK
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET

AM_PROG_AR

LT_INIT

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor memset pow sqrt])

AC_CONFIG_FILES([Makefile
                 lib/Makefile
                 lib/boxCounting/Makefile
                 lib/cls/Makefile
                 lib/cls/compact/Makefile
                 lib/concepts/Makefile
                 lib/conn/Makefile
                 lib/conn/bash/Makefile
                 lib/conn/sage/Makefile
                 lib/dou/Makefile
                 lib/dou/geo/Makefile
                 lib/dyn/Makefile
                 lib/manip/Makefile
                 lib/numerical/Makefile
                 lib/signal/Makefile
                 src/Makefile
                 src/test/Makefile])
AC_OUTPUT
