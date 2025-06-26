#include <stdio.h>
#include "tests/tokenizer_tests.h"

int main()
{
    printf("Running JECH internal tests...\n");

    test_tokenizer_say_string();

    printf("All tests passed!\n");
    return 0;
}
