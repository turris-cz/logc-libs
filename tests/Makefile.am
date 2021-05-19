TESTS =
check_PROGRAMS =

if CZMQ
TESTS += %reldir%/czmq-unittests
check_PROGRAMS += %reldir%/czmq-unittests

%canon_reldir%_czmq_unittests_SOURCES = \
	%reldir%/unittests.c \
	%reldir%/czmq.c
%canon_reldir%_czmq_unittests_CFLAGS = \
	-isystem '$(srcdir)/include' \
	${logc_CFLAGS} \
	${libczmq_CFLAGS} \
	$(check_FLAGS)
%canon_reldir%_czmq_unittests_LDADD = \
	$(builddir)/libczmq_logc.la \
	${logc_LIBS} \
	${libczmq_LIBS} \
	$(check_LIBS)

linted_files += $(%canon_reldir%_unittests_SOURCES)
endif

if EVENT
TESTS += %reldir%/event-unittests
check_PROGRAMS += %reldir%/event-unittests

%canon_reldir%_event_unittests_SOURCES = \
	%reldir%/unittests.c \
	%reldir%/event.c
%canon_reldir%_event_unittests_CFLAGS = \
	-isystem '$(srcdir)/include' \
	${logc_CFLAGS} \
	${libevent_CFLAGS} \
	${check_FLAGS}
%canon_reldir%_event_unittests_LDADD = \
	$(builddir)/libevent_logc.la \
	${logc_LIBS} \
	${libevent_LIBS} \
	${check_LIBS}

linted_files += $(%canon_reldir%_unittests_SOURCES)
endif



LOG_DRIVER = \
	env AM_TAP_AWK='$(AWK)' TEST_OUTPUT_TAP="/dev/stdout" \
	'$(SHELL)' '$(srcdir)/.aux/tap-driver.sh'

## Valgrind
VALGRIND_memcheck_FLAGS = \
	--leak-check=full \
	--show-leak-kinds=definite,indirect,possible \
	--track-fds=yes \
	--track-origins=yes \
	--trace-children=yes \
	--child-silent-after-fork=no
@VALGRIND_CHECK_RULES@

# Rules generated for valgrind are for some reason called *-am. This is just an alias
check-valgrind: check-valgrind-am
define check_valgrind_rule
check-valgrind-$(1): check-valgrind-$(1)-am
endef
$(foreach tool,$(valgrind_tools),$(eval $(call check_valgrind_rule,$(tool))))

## Coverage
CODE_COVERAGE_LCOV_OPTIONS := --no-external
CODE_COVERAGE_GENHTML_OPTIONS := --prefix $(dir $(abs_top_builddir))

include $(srcdir)/aminclude_static.am

clean-local: code-coverage-clean
distclean-local: code-coverage-dist-clean
