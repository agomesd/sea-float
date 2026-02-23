#ifndef SF_TEST_SUITE_H
#define SF_TEST_SUITE_H


typedef int (*test_func_t)(void);

typedef struct TestCase {
    char *name;
    int failed;
    test_func_t test_func;
} test_case_t;

typedef struct TestSuite {
    char *name;
    test_case_t *test_cases;
    size_t count;
    size_t capacity;
    size_t total_passed;
    size_t total_failed;
} test_suite_t;

int test_suite_init(test_suite_t *suite, char *name);
int register_test(test_suite_t *suite, test_func_t func, const char *test_name);
void run_all_tests(test_suite_t *suite);
void test_suite_destroy(test_suite_t *suite);

#endif
