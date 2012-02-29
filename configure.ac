AC_PREREQ(2.59)
AC_COPYRIGHT([Copyright (c) 2011 Varnish Software AS])
AC_INIT([libvmod-example], [trunk])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_SRCDIR(src/vmod_example.vcc)
AM_CONFIG_HEADER(config.h)

AC_CANONICAL_SYSTEM
AC_LANG(C)

AM_INIT_AUTOMAKE([foreign])

AC_GNU_SOURCE
AC_PROG_CC
AC_PROG_CC_STDC
if test "x$ac_cv_prog_cc_c99" = xno; then
	AC_MSG_ERROR([Could not find a C99 compatible compiler])
fi
AC_PROG_CPP

AC_PROG_INSTALL
AC_PROG_LIBTOOL
AC_PROG_MAKE_SET

# Check for rst utilities
AC_CHECK_PROGS(RST2MAN, [rst2man rst2man.py], "no")
if test "x$RST2MAN" = "xno"; then
	AC_MSG_WARN([rst2man not found - not building man pages])
fi
AM_CONDITIONAL(HAVE_RST2MAN, [test "x$RST2MAN" != "xno"])

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([sys/stdlib.h])

# Check for python
AC_CHECK_PROGS(PYTHON, [python3 python3.1 python3.2 python2.7 python2.6 python2.5 python2 python], [AC_MSG_ERROR([Python is needed to build this vmod, please install python.])])

# Check for pkg-config
PKG_PROG_PKG_CONFIG
PKG_CHECK_EXISTS(varnishapi,
	[],
	[AC_MSG_ERROR([Can't find pkg-config data for 'varnishapi'])]
)

# Read Varnish pkg-config variables
VAPI_VERSION=`$PKG_CONFIG --variable=Version varnishapi`
VARNISH_BIN=`$PKG_CONFIG --variable=bindir varnishapi`
VARNISH_SBIN=`$PKG_CONFIG --variable=sbindir varnishapi`
VARNISH_PKGINCLUDE=`$PKG_CONFIG --variable=pkgincludedir varnishapi`
VARNISH_PKGDATA=`$PKG_CONFIG --variable=pkgdatadir varnishapi`
VARNISH_PKGDATAINCLUDE=`$PKG_CONFIG --variable=pkgdataincludedir varnishapi`
VARNISH_BUILD=`$PKG_CONFIG --variable=builddir varnishapi`
VARNISH_SRC=`$PKG_CONFIG --variable=srcdir varnishapi`
VMOD_DIR=`$PKG_CONFIG --variable=vmoddir varnishapi`

AC_MSG_CHECKING([for Varnish source/build tree])
if test "x$VARNISH_BUILD" != x; then
	# Configuring against a varnish build directory
	AC_MSG_RESULT([$VARNISH_BUILD])
	AC_CHECK_FILE([$VARNISH_SRC/bin/varnishd/cache/cache.h],
		[],
		[AC_MSG_FAILURE([Varnish vmod headers not found])]
	)
	AC_CHECK_FILE([$VARNISH_BUILD/include/vmod_abi.h],
		[],
		[AC_MSG_FAILURE([vmod_abi.h not found, source tree built?])]
	)
	VMOD_TOOL="$VARNISH_SRC/lib/libvcl/vmodtool.py"
	VMOD_INCLUDES="-I$VARNISH_SRC/include -I$VARNISH_SRC/bin/varnishd"
	if test "x$VARNISH_BUILD" != "x$VARNISHSRC"; then
		VMOD_INCLUDES="$VMOD_INCLUDES -I$VARNISH_BUILD/include"
	fi
	VARNISHD="$VARNISH_BUILD/bin/varnishd/varnishd"
	VARNISHTEST="$VARNISH_BUILD/bin/varnishtest/varnishtest"
else
	AC_MSG_RESULT([no])
	AC_CHECK_FILES(
		[
			$VARNISH_PKGDATAINCLUDE/cache/cache.h
			$VARNISH_PKGDATAINCLUDE/vmod_abi.h
		],
		[],
		[AC_MSG_FAILURE([Varnish vmod headers not found])]
	)
	VMOD_TOOL="$VARNISH_PKGDATA/vmodtool.py"
	VMOD_INCLUDES="-I$VARNISH_PKGINCLUDE -I$VARNISH_PKGDATAINCLUDE"
	VARNISHD="$VARNISH_SBIN/varnishd"
	VARNISHTEST="$VARNISH_BIN/varnishtest"
	VARNISHTEST_ARGS=""
fi

AC_CHECK_FILE([$VMOD_TOOL], [], [AC_MSG_FAILURE(["$VMOD_TOOL" does not exist])])
AC_CHECK_FILE([$VARNISHD], [], [AC_MSG_FAILURE(["$VARNISHD" does not exist])])
AC_CHECK_FILE([$VARNISHTEST], [],
	[AC_MSG_FAILURE(["$VARNISHTEST" does not exist])])

AC_SUBST(VMOD_TOOL)
AC_SUBST(VMOD_INCLUDES)
AC_SUBST(VARNISHD)
AC_SUBST(VARNISHTEST)
AC_SUBST(VMOD_DIR)

AC_CONFIG_FILES([
	Makefile
	src/Makefile
])
AC_OUTPUT
