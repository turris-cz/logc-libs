#include <check.h>
#include <event2/logc.h>
#include <errno.h>

void unittests_add_suite(Suite*);

START_TEST(init_cleanup) {
	logc_event_init();
	ck_assert_int_eq(errno, 0);
	logc_event_cleanup();
	ck_assert_int_eq(errno, 0);
}
END_TEST

// TODO we should implement tests that trigger callback but how?

__attribute__((constructor))
static void suite() {
	Suite *suite = suite_create("event");

	TCase *basic_case = tcase_create("basic");
	tcase_add_test(basic_case, init_cleanup);
	suite_add_tcase(suite, basic_case);

	unittests_add_suite(suite);
}
