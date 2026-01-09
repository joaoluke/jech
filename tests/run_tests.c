#include <stdio.h>
#include "test_framework.h"

int run_tokenizer_tests();
int run_parser_tests();
int run_vm_tests();
int run_integration_tests();

int main(int argc, char *argv[])
{
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                                                        ║\n");
    printf("║           JECH Language Test Suite v1.0               ║\n");
    printf("║                                                        ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");

    int total_failures = 0;

    total_failures += run_tokenizer_tests();
    total_failures += run_parser_tests();
    total_failures += run_vm_tests();
    total_failures += run_integration_tests();

    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║                   FINAL RESULTS                        ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");

    if (total_failures == 0) {
        printf(COLOR_GREEN "✓ All test suites passed!\n" COLOR_RESET);
        printf("\n");
        return 0;
    } else {
        printf(COLOR_RED "✗ %d test suite(s) had failures\n" COLOR_RESET, total_failures);
        printf("\n");
        return 1;
    }
}
