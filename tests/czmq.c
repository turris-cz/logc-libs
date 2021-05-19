#include <check.h>
#include <czmq_logc.h>
#include <stdio.h>
#include <errno.h>

void unittests_add_suite(Suite*);

FILE* orig_stderr;
char *stderr_data;
size_t stderr_len;

void f_setup() {
	errno = 0;
	orig_stderr = stderr;
	stderr = open_memstream(&stderr_data, &stderr_len);
	logc_czmq_init();
	log_set_level(log_czmq, LL_DEBUG);
}
void f_teardown() {
	ck_assert_int_eq(errno, 0);
	logc_czmq_cleanup();
	fclose(stderr);
	stderr = orig_stderr;
}


START_TEST(zmq_error) {
	zsys_error("test message: %s", "foo");
	fflush(stderr);
	ck_assert_str_eq(stderr_data, "ERROR:czmq: ZMQ: test message: foo\n");
}
END_TEST

START_TEST(zmq_warning) {
	zsys_warning("test message: %s", "foo");
	fflush(stderr);
	ck_assert_str_eq(stderr_data, "WARNING:czmq: ZMQ: test message: foo\n");
}
END_TEST

START_TEST(zmq_notice) {
	zsys_notice("test message: %s", "foo");
	fflush(stderr);
	ck_assert_str_eq(stderr_data, "NOTICE:czmq: ZMQ: test message: foo\n");
}
END_TEST

START_TEST(zmq_info) {
	zsys_info("test message: %s", "foo");
	fflush(stderr);
	ck_assert_str_eq(stderr_data, "INFO:czmq: ZMQ: test message: foo\n");
}
END_TEST

START_TEST(zmq_debug) {
	zsys_debug("test message: %s", "foo");
	fflush(stderr);
	ck_assert_str_eq(stderr_data, "DEBUG:czmq: ZMQ: test message: foo\n");
}
END_TEST


__attribute__((constructor))
static void suite() {
	Suite *suite = suite_create("log");

	TCase *zmq_case = tcase_create("zmq");
	tcase_add_checked_fixture(zmq_case, f_setup, f_teardown);
	tcase_add_test(zmq_case, zmq_error);
	tcase_add_test(zmq_case, zmq_warning);
	tcase_add_test(zmq_case, zmq_notice);
	tcase_add_test(zmq_case, zmq_info);
	tcase_add_test(zmq_case, zmq_debug);
	suite_add_tcase(suite, zmq_case);

	unittests_add_suite(suite);
}
