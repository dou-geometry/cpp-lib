#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([Dou-geometry-Cpp-Library], [0], [fudepia@outlook.jp])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])

AC_CONFIG_MACRO_DIRS([m4])

# Checks for programs.
AC_LANG([C++])
AX_CHECK_COMPILE_FLAG([-std=c++20], [
		       CXXFLAGS="$CXXFLAGS -std=c++20"])
AM_CXXFLAGS=-std=c++20
AC_PROG_CXX

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_CHECK_HEADER_STDBOOL

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([floor pow sqrt])

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 include/cls/Makefile
                 include/conn/Makefile
                 include/func/Makefile
                 lib/Makefile
                 lib/conn/Makefile
                 src/Makefile])
AC_OUTPUT
