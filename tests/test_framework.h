#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RED "\033[0;31m"
#define COLOR_YELLOW "\033[0;33m"
#define COLOR_RESET "\033[0m"

typedef struct {
    int total;
    int passed;
    int failed;
} TestStats;

static TestStats test_stats = {0, 0, 0};

#define TEST(name) \
    void name(); \
    void name()

#define ASSERT(condition, message) \
    do { \
        test_stats.total++; \
        if (!(condition)) { \
            printf(COLOR_RED "  ✗ FAIL: %s\n" COLOR_RESET, message); \
            printf("    at %s:%d\n", __FILE__, __LINE__); \
            test_stats.failed++; \
            return; \
        } else { \
            test_stats.passed++; \
        } \
    } while(0)

#define ASSERT_EQ(actual, expected, message) \
    ASSERT((actual) == (expected), message)

#define ASSERT_STR_EQ(actual, expected, message) \
    ASSERT(strcmp(actual, expected) == 0, message)

#define RUN_TEST(test_func) \
    do { \
        printf(COLOR_YELLOW "Running: %s" COLOR_RESET "\n", #test_func); \
        test_func(); \
        if (test_stats.failed == 0) { \
            printf(COLOR_GREEN "  ✓ PASS\n" COLOR_RESET); \
        } \
    } while(0)

#define TEST_SUITE_BEGIN(suite_name) \
    printf("\n" COLOR_YELLOW "═══════════════════════════════════════\n"); \
    printf("  Test Suite: %s\n", suite_name); \
    printf("═══════════════════════════════════════\n" COLOR_RESET); \
    test_stats.total = 0; \
    test_stats.passed = 0; \
    test_stats.failed = 0;

#define TEST_SUITE_END() \
    printf("\n" COLOR_YELLOW "───────────────────────────────────────\n"); \
    printf("  Results: %d/%d passed", test_stats.passed, test_stats.total); \
    if (test_stats.failed > 0) { \
        printf(COLOR_RED " (%d failed)" COLOR_RESET, test_stats.failed); \
    } else { \
        printf(COLOR_GREEN " (all passed!)" COLOR_RESET); \
    } \
    printf("\n" COLOR_YELLOW "───────────────────────────────────────\n" COLOR_RESET); \
    return test_stats.failed;

#endif
