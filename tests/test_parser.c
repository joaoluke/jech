#include "test_framework.h"
#include "core/tokenizer.h"
#include "core/parser/parser.h"
#include "core/ast.h"

TEST(test_parser_say_statement)
{
    const char *source = "say(\"Hello\");";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    
    ASSERT_EQ(count, 1, "Should parse 1 statement");
    ASSERT_EQ(roots[0]->type, JECH_AST_SAY, "Should be SAY node");
    ASSERT_STR_EQ(roots[0]->value, "Hello", "Value should be 'Hello'");
    
    _JechAST_Free(roots[0]);
}

TEST(test_parser_keep_statement)
{
    const char *source = "keep x = 42;";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    
    ASSERT_EQ(count, 1, "Should parse 1 statement");
    ASSERT_EQ(roots[0]->type, JECH_AST_KEEP, "Should be KEEP node");
    ASSERT_STR_EQ(roots[0]->name, "x", "Variable name should be 'x'");
    ASSERT_STR_EQ(roots[0]->value, "42", "Value should be '42'");
    
    _JechAST_Free(roots[0]);
}

TEST(test_parser_array_literal)
{
    const char *source = "keep arr = [1, 2, 3];";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    
    ASSERT_EQ(count, 1, "Should parse 1 statement");
    ASSERT_EQ(roots[0]->type, JECH_AST_KEEP, "Should be KEEP node");
    ASSERT_STR_EQ(roots[0]->name, "arr", "Variable name should be 'arr'");
    ASSERT(roots[0]->left != NULL, "Should have array literal child");
    ASSERT_EQ(roots[0]->left->type, JECH_AST_ARRAY_LITERAL, "Child should be ARRAY_LITERAL");
    
    _JechAST_Free(roots[0]);
}

TEST(test_parser_array_indexing)
{
    const char *source = "say(arr[0]);";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    
    ASSERT_EQ(count, 1, "Should parse 1 statement");
    ASSERT_EQ(roots[0]->type, JECH_AST_SAY_INDEX, "Should be SAY_INDEX node");
    ASSERT_STR_EQ(roots[0]->value, "arr", "Array name should be 'arr'");
    ASSERT(roots[0]->left != NULL, "Should have index child");
    ASSERT_STR_EQ(roots[0]->left->value, "0", "Index should be '0'");
    
    _JechAST_Free(roots[0]);
}

TEST(test_parser_assignment)
{
    const char *source = "x = 100;";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    
    ASSERT_EQ(count, 1, "Should parse 1 statement");
    ASSERT_EQ(roots[0]->type, JECH_AST_ASSIGN, "Should be ASSIGN node");
    ASSERT_STR_EQ(roots[0]->name, "x", "Variable name should be 'x'");
    ASSERT_STR_EQ(roots[0]->value, "100", "Value should be '100'");
    
    _JechAST_Free(roots[0]);
}

TEST(test_parser_multiple_statements)
{
    const char *source = "keep x = 10; say(x); x = 20;";
    JechTokenList tokens = _JechTokenizer_Lex(source);
    
    int count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &count);
    
    ASSERT_EQ(count, 3, "Should parse 3 statements");
    ASSERT_EQ(roots[0]->type, JECH_AST_KEEP, "First should be KEEP");
    ASSERT_EQ(roots[1]->type, JECH_AST_SAY, "Second should be SAY");
    ASSERT_EQ(roots[2]->type, JECH_AST_ASSIGN, "Third should be ASSIGN");
    
    for (int i = 0; i < count; i++) {
        _JechAST_Free(roots[i]);
    }
}

int run_parser_tests()
{
    TEST_SUITE_BEGIN("Parser Tests");
    
    RUN_TEST(test_parser_say_statement);
    RUN_TEST(test_parser_keep_statement);
    RUN_TEST(test_parser_array_literal);
    RUN_TEST(test_parser_array_indexing);
    RUN_TEST(test_parser_assignment);
    RUN_TEST(test_parser_multiple_statements);
    
    TEST_SUITE_END();
}
