#include "test_framework.h"
#include "core/pipeline.h"
#include "core/vm.h"
#include <stdio.h>
#include <stdlib.h>

static char *capture_pipeline_output(const char *source)
{
    FILE *original_stdout = stdout;
    char *buffer = malloc(2048);
    FILE *stream = fmemopen(buffer, 2048, "w");
    stdout = stream;
    
    run_pipeline(source);
    
    fflush(stream);
    fclose(stream);
    stdout = original_stdout;
    
    return buffer;
}

TEST(test_integration_hello_world)
{
    _JechVM_ClearState();
    const char *source = "say(\"Hello, World!\");";
    char *output = capture_pipeline_output(source);
    ASSERT_STR_EQ(output, "Hello, World!\n", "Should output 'Hello, World!'");
    free(output);
}

TEST(test_integration_variables_flow)
{
    _JechVM_ClearState();
    const char *source = "keep x = 10; keep y = 20; say(x); say(y);";
    char *output = capture_pipeline_output(source);
    ASSERT_STR_EQ(output, "10\n20\n", "Should output both variables");
    free(output);
}

TEST(test_integration_array_operations)
{
    _JechVM_ClearState();
    const char *source = "keep arr = [100, 200, 300]; say(arr[0]); say(arr[1]); say(arr[2]);";
    char *output = capture_pipeline_output(source);
    ASSERT_STR_EQ(output, "100\n200\n300\n", "Should output all array elements");
    free(output);
}

TEST(test_integration_mixed_types_array)
{
    _JechVM_ClearState();
    const char *source = "keep mixed = [42, \"text\", true]; say(mixed[0]); say(mixed[1]); say(mixed[2]);";
    char *output = capture_pipeline_output(source);
    ASSERT_STR_EQ(output, "42\ntext\ntrue\n", "Should handle mixed types");
    free(output);
}

TEST(test_integration_empty_array)
{
    _JechVM_ClearState();
    const char *source = "keep empty = []; keep single = [999]; say(single[0]);";
    char *output = capture_pipeline_output(source);
    ASSERT_STR_EQ(output, "999\n", "Should handle empty and single-element arrays");
    free(output);
}

TEST(test_integration_variable_and_array_together)
{
    _JechVM_ClearState();
    const char *source = "keep x = 5; keep arr = [10, 20]; say(x); say(arr[0]); say(arr[1]);";
    char *output = capture_pipeline_output(source);
    ASSERT_STR_EQ(output, "5\n10\n20\n", "Should handle variables and arrays together");
    free(output);
}

TEST(test_integration_reassignment)
{
    _JechVM_ClearState();
    const char *source = "keep x = 1; say(x); x = 2; say(x); x = 3; say(x);";
    char *output = capture_pipeline_output(source);
    ASSERT_STR_EQ(output, "1\n2\n3\n", "Should handle multiple reassignments");
    free(output);
}

int run_integration_tests()
{
    TEST_SUITE_BEGIN("Integration Tests (End-to-End)");
    
    RUN_TEST(test_integration_hello_world);
    RUN_TEST(test_integration_variables_flow);
    RUN_TEST(test_integration_array_operations);
    RUN_TEST(test_integration_mixed_types_array);
    RUN_TEST(test_integration_empty_array);
    RUN_TEST(test_integration_variable_and_array_together);
    RUN_TEST(test_integration_reassignment);
    
    TEST_SUITE_END();
}
