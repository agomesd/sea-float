#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/test-suite.h"

#define INITIAL_CAPACITY 8

int test_suite_init(test_suite_t *suite, char *name) {
    suite->name = strdup(name);
    if (!suite->name) {
        fprintf(stderr, "Failed to duplicate suite name\n");
        return -1;
    }
    suite->capacity = INITIAL_CAPACITY;
    suite->count = 0;
    suite->total_passed = 0;
    suite->total_failed = 0;
    suite->test_cases = malloc(suite->capacity * sizeof(test_case_t));
    if (!suite->test_cases) {
        fprintf(stderr, "Failed to allocate memory for test cases.");
        return -1;
    }
    return 0;
}

int register_test(test_suite_t *suite, test_func_t func, const char *name) {
    if (suite->count >= suite->capacity) {
        size_t new_capacity = suite->capacity ? suite->capacity * 2 : INITIAL_CAPACITY;
        test_case_t *new_cases = realloc(suite->test_cases, new_capacity * sizeof(test_case_t));
        if (new_cases == NULL) {
            fprintf(stderr, "Failed to expand test cases array\n");
            return -1;
        }
        suite->test_cases = new_cases;
        suite->capacity = new_capacity;
    }

    suite->test_cases[suite->count].test_func = func;
    suite->test_cases[suite->count].name = strdup(name);
    if (!suite->test_cases[suite->count].name) {
        fprintf(stderr, "Failed to duplicate test name\n");
        return -1;
    }
    suite->test_cases[suite->count].failed = 0;
    suite->count++;
    return 0;
}

void run_all_tests(test_suite_t *suite) {
    for (size_t i = 0; i < suite->count; i++) {
        int result = suite->test_cases[i].test_func();

        if (result != 0) {
            printf("\x1b[31mTest: %s -> FAILED\x1b[0m\n", suite->test_cases[i].name);
            suite->test_cases[i].failed = 1;
            suite->total_failed++;
        } else {
            printf("\x1b[32mTest: %s -> PASSED\x1b[0m\n", suite->test_cases[i].name);
            suite->test_cases[i].failed = 0;
            suite->total_passed++;
        }
    }

    printf("\nTest Summary for suite: %s\n", suite->name);
    printf("Total: %zu, \x1b[32mPassed: %zu\x1b[0m, \x1b[31mFailed: %zu\x1b[0m\n", suite->count, suite->total_passed, suite->total_failed);
}

void test_suite_destroy(test_suite_t *suite) {
    for (size_t i = 0; i < suite->count; i++) {
        free(suite->test_cases[i].name);
        suite->test_cases[i].name = NULL;
    }

    free(suite->test_cases);
    suite->test_cases = NULL;
    
    free(suite->name);
    suite->name = NULL;

    suite->count = 0;
    suite->capacity = 0;
    suite->total_failed = 0;
    suite->total_passed = 0;
}
