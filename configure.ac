#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([jon], [0.0.1], [2182619@qq.com])
AM_INIT_AUTOMAKE([check-news -Wall 1.9 dist-bzip2])

AC_CONFIG_SRCDIR([src/jon.c])
AC_CONFIG_HEADERS([src/config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h memory.h stddef.h stdlib.h string.h strings.h unistd.h utime.h utmp.h utmpx.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
