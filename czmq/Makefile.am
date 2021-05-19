lib_LTLIBRARIES += libczmq_logc.la
pkgconfig_DATA += %reldir%/libczmq_logc.pc
EXTRA_DIST += %reldir%/libczmq_logc.version

include_HEADERS += include/czmq_logc.h
libczmq_logc_la_SOURCES = \
	%reldir%/log.c
libczmq_logc_la_CFLAGS = \
	-isystem '$(srcdir)/include' \
	${logc_CFLAGS} \
	${libczmq_CFLAGS} \
	${CODE_COVERAGE_CFLAGS}
libczmq_logc_la_LIBADD = \
	${logc_LIBS} \
	${libczmq_LIBS} \
	${CODE_COVERAGE_LIBS}
libczmq_logc_la_LDFLAGS = \
	--version-script='$(srcdir)/%reldir%/libczmq_logc.version' \
	-version-info 0:0:0


linted_files += $(libczmq_logc_la_SOURCES)
