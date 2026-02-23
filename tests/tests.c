#include <assert.h>
#include <stdlib.h>
#include "../src/test-suite/test-suite.h"

int add(int a, int b);
int sub(int a, int b);
int test_add(void);
int test_sub(void);

void test_test_suite(void) {
    test_suite_t *test_suite = malloc(sizeof(test_suite_t));
    char *name = "test_suite";
    
    int initialised = test_suite_init(test_suite, name);
    assert(initialised == 0);
    assert(test_suite->count == 0);
    assert(test_suite->capacity == 8);
    assert(test_suite->total_passed == 0);
    assert(test_suite->total_failed == 0);

    register_test(test_suite, test_add, "Test add");
    register_test(test_suite, test_sub, "Test sub");

    assert(test_suite->count == 2);

    run_all_tests(test_suite);

    test_suite_destroy(test_suite);
    free(test_suite);
}

int test_add(void) {
    int sum = add(3, 7);
    return (sum == 10) ? 0 : 1;
}

int test_sub(void) {
    int diff = sub(3, 2);
    return (diff == 1) ? 0 : 1;
}

int add(int a, int b) { return a + b; }
int sub(int a, int b) { return a - b; }
