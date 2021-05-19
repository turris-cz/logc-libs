lib_LTLIBRARIES += libevent_logc.la
pkgconfig_DATA += %reldir%/libevent_logc.pc
EXTRA_DIST += %reldir%/libevent_logc.version

event2dir = $(includedir)/event2
event2_HEADERS = include/event2/logc.h
libevent_logc_la_SOURCES = \
	%reldir%/log.c
libevent_logc_la_CFLAGS = \
	-isystem '$(srcdir)/include' \
	${logc_CFLAGS} \
	${libevent_CFLAGS} \
	${CODE_COVERAGE_CFLAGS}
libevent_logc_la_LIBADD = \
	${logc_LIBS} \
	${libevent_LIBS} \
	${CODE_COVERAGE_LIBS}
libevent_logc_la_LDFLAGS = \
	--version-script='$(srcdir)/%reldir%/libevent_logc.version' \
	-version-info 0:0:0


linted_files += $(libevent_logc_la_SOURCES)
