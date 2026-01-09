#include "test_framework.h"
#include "core/tokenizer.h"
#include "core/parser/parser.h"
#include "core/bytecode.h"
#include "core/vm.h"
#include "core/ast.h"
#include <stdio.h>
#include <stdlib.h>

static char *capture_output(void (*func)(const Bytecode*), const Bytecode *bc)
{
    FILE *original_stdout = stdout;
    char *buffer = malloc(1024);
    FILE *stream = fmemopen(buffer, 1024, "w");
    stdout = stream;
    
    func(bc);
    
    fflush(stream);
    fclose(stream);
    stdout = original_stdout;
    
    return buffer;
}

TEST(test_vm_variable_keep_and_say)
{
    _JechVM_ClearState();
    
    const char *source = "keep x = 42; say(x);";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    Bytecode bc = _JechBytecode_CompileAll(roots, count);
    
    char *output = capture_output(_JechVM_Execute, &bc);
    ASSERT_STR_EQ(output, "42\n", "Should output '42'");
    
    free(output);
    for (int i = 0; i < count; i++) _JechAST_Free(roots[i]);
}

TEST(test_vm_variable_assignment)
{
    _JechVM_ClearState();
    
    const char *source = "keep x = 10; x = 20; say(x);";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    Bytecode bc = _JechBytecode_CompileAll(roots, count);
    
    char *output = capture_output(_JechVM_Execute, &bc);
    ASSERT_STR_EQ(output, "20\n", "Should output '20' after reassignment");
    
    free(output);
    for (int i = 0; i < count; i++) _JechAST_Free(roots[i]);
}

TEST(test_vm_array_creation_and_access)
{
    _JechVM_ClearState();
    
    const char *source = "keep arr = [1, 2, 3]; say(arr[0]); say(arr[2]);";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    Bytecode bc = _JechBytecode_CompileAll(roots, count);
    
    char *output = capture_output(_JechVM_Execute, &bc);
    ASSERT_STR_EQ(output, "1\n3\n", "Should output '1' and '3'");
    
    free(output);
    for (int i = 0; i < count; i++) _JechAST_Free(roots[i]);
}

TEST(test_vm_array_with_strings)
{
    _JechVM_ClearState();
    
    const char *source = "keep names = [\"Alice\", \"Bob\"]; say(names[0]);";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    Bytecode bc = _JechBytecode_CompileAll(roots, count);
    
    char *output = capture_output(_JechVM_Execute, &bc);
    ASSERT_STR_EQ(output, "Alice\n", "Should output 'Alice'");
    
    free(output);
    for (int i = 0; i < count; i++) _JechAST_Free(roots[i]);
}

TEST(test_vm_clear_state)
{
    _JechVM_ClearState();
    
    _JechVM_SetVariable("test", "value");
    ASSERT(_JechVM_GetVariable("test") != NULL, "Variable should exist");
    
    _JechVM_ClearState();
    ASSERT(_JechVM_GetVariable("test") == NULL, "Variable should be cleared");
}

int run_vm_tests()
{
    TEST_SUITE_BEGIN("VM Tests");
    
    RUN_TEST(test_vm_variable_keep_and_say);
    RUN_TEST(test_vm_variable_assignment);
    RUN_TEST(test_vm_array_creation_and_access);
    RUN_TEST(test_vm_array_with_strings);
    RUN_TEST(test_vm_clear_state);
    
    TEST_SUITE_END();
}
