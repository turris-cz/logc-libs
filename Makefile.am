ACLOCAL_AMFLAGS = -I .m4

lib_LTLIBRARIES =
include_HEADERS =
pkgconfig_DATA =
EXTRA_DIST =
linted_files =


if CZMQ
include $(srcdir)/czmq/Makefile.am
endif
if EVENT
include $(srcdir)/event/Makefile.am
endif


linted_files += $(include_HEADERS)
if ENABLE_LINTERS
include $(srcdir)/utils/lint.am
endif

if ENABLE_TESTS
DISTCHECK_CONFIGURE_FLAGS = --enable-tests
include $(srcdir)/tests/Makefile.am
endif
