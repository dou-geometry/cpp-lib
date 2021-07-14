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
AX_CHECK_COMPILE_FLAG([-std=gnu++20], [
		       CXXFLAGS="$CXXFLAGS -std=gnu++20"])
AM_CXXFLAGS=-std=gnu++20
AC_PROG_CXX
AC_PROG_RANLIB
AM_PROG_AR

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor pow sqrt])

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 include/boxCounting/Makefile
                 include/cls/Makefile
                 include/conn/Makefile
                 include/conn/bash/Makefile
                 include/conn/sage/Makefile
                 include/numerical/Makefile
                 lib/Makefile
                 lib/boxCounting/Makefile
                 lib/conn/Makefile
                 lib/conn/bash/Makefile
                 lib/conn/sage/Makefile
                 lib/dyn/Makefile
                 lib/numerical/Makefile
                 src/Makefile])
AC_OUTPUT
