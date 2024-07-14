AC_PREREQ([2.71])
AC_INIT([extlib], [1.0.0], [axtlos@disroot.org])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AC_CONFIG_MACRO_DIRS([m4])

AC_PROG_CC
AM_PROG_AR

LT_INIT

AC_CHECK_HEADERS([strings.h
		  ctype.h
		  unistd.h
		  stdint.h
		  errno.h])

AC_TYPE_SIZE_T

AC_FUNC_MALLOC

AC_CHECK_FUNC([memset_s], [AC_DEFINE([HAVE_MEMSET_S], [1],
			   [Define if memset_s exists])])

AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
  Makefile
  src/Makefile
  extlib.pc
])
AC_OUTPUT
