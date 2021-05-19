AC_INIT([logc-libs], [0.1.0], [cynerd@email.cz])
AC_CONFIG_MACRO_DIRS([.m4])
AC_CONFIG_AUX_DIR([.aux])

AM_INIT_AUTOMAKE([
  foreign silent-rules subdir-objects
  -Wall -Wno-portability
  dist-zip dist-xz
])
AM_SILENT_RULES([yes])

AC_PROG_CC
AC_GNU_SOURCE
AM_PROG_AR
LT_INIT
PKG_INSTALLDIR

AX_CHECK_COMPILE_FLAG([-std=c11], , AC_MSG_ERROR([Compiler with C11 standard support is required]))
AX_APPEND_FLAG([-std=c11])

PKG_CHECK_MODULES([logc], [logc])


dnl --- czmq ---
AC_ARG_WITH([czmq],
  [AS_HELP_STRING([--with-czmq], [build czmq integration library @<:@default=check@:>@])],
  [], [with_czmq=check]
)
AS_IF([test "x$with_czmq" != xno],
  [PKG_CHECK_MODULES([libczmq], [libczmq],
    [with_czmq=yes],
    [AS_IF([test "x$with_czmq" != xcheck], [AC_MSG_FAILURE([Unable to find libczmq])])]
  )]
)
AM_CONDITIONAL(CZMQ, [test "x$with_czmq" = "xyes"])

dnl --- event ---
AC_ARG_WITH([event],
  [AS_HELP_STRING([--with-event], [build event integration library @<:@default=check@:>@])],
  [], [with_event=check]
)
AS_IF([test "x$with_event" != xno],
  [PKG_CHECK_MODULES([libevent], [libevent >= 2.0],
    [with_event=yes],
    [AS_IF([test "x$with_event" != xcheck], [AC_MSG_FAILURE([Unable to find libevent])])]
  )]
)
AM_CONDITIONAL(EVENT, [test "x$with_event" = "xyes"])


dnl Tests
AC_ARG_ENABLE([tests], AC_HELP_STRING([--enable-tests], [Whether to enable unit tests]))
AM_CONDITIONAL([ENABLE_TESTS], [test "x$enable_tests" = "xyes"])
AS_IF([test "x$enable_tests" = "xyes"], [
  PKG_CHECK_MODULES([check], [check >= 0.11])
  AC_REQUIRE_AUX_FILE([tap-driver.sh])
])
AX_VALGRIND_CHECK

dnl Linters
AC_ARG_ENABLE([linters], AC_HELP_STRING([--enable-linters], [Whether to enable code linting support (cppcheck)]))
AM_CONDITIONAL([ENABLE_LINTERS], [test "x$enable_linters" = "xyes"])
AS_IF([test "x$enable_linters" = "xyes"], [
  AC_PATH_PROG([CPPCHECK], [cppcheck])
  AS_IF([test -z "$CPPCHECK" ], AC_MSG_ERROR([Missing linter cppcheck]))
])

dnl Coverage
AX_CODE_COVERAGE


AC_CONFIG_FILES([Makefile])
AS_IF([test "x$with_czmq" == "xyes"], AC_CONFIG_FILES([czmq/libczmq_logc.pc]))
AS_IF([test "x$with_event" == "xyes"], AC_CONFIG_FILES([event/libevent_logc.pc]))

AC_OUTPUT
