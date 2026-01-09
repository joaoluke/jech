#include "test_framework.h"
#include "core/tokenizer.h"

TEST(test_tokenizer_say_string)
{
    const char *source = "say(\"Hello\");";
    JechTokenList list = _JechTokenizer_Lex(source);

    ASSERT_EQ(list.count, 6, "Token count should be 6");
    ASSERT_EQ(list.tokens[0].type, TOKEN_SAY, "First token should be SAY");
    ASSERT_EQ(list.tokens[1].type, TOKEN_LPAREN, "Second token should be LPAREN");
    ASSERT_EQ(list.tokens[2].type, TOKEN_STRING, "Third token should be STRING");
    ASSERT_STR_EQ(list.tokens[2].value, "Hello", "String value should be 'Hello'");
    ASSERT_EQ(list.tokens[3].type, TOKEN_RPAREN, "Fourth token should be RPAREN");
    ASSERT_EQ(list.tokens[4].type, TOKEN_SEMICOLON, "Fifth token should be SEMICOLON");
}

TEST(test_tokenizer_keep_number)
{
    const char *source = "keep x = 42;";
    JechTokenList list = _JechTokenizer_Lex(source);

    ASSERT_EQ(list.count, 6, "Token count should be 6");
    ASSERT_EQ(list.tokens[0].type, TOKEN_KEEP, "First token should be KEEP");
    ASSERT_EQ(list.tokens[1].type, TOKEN_IDENTIFIER, "Second token should be IDENTIFIER");
    ASSERT_STR_EQ(list.tokens[1].value, "x", "Identifier should be 'x'");
    ASSERT_EQ(list.tokens[2].type, TOKEN_EQUAL, "Third token should be EQUAL");
    ASSERT_EQ(list.tokens[3].type, TOKEN_NUMBER, "Fourth token should be NUMBER");
    ASSERT_STR_EQ(list.tokens[3].value, "42", "Number should be '42'");
}

TEST(test_tokenizer_array_literal)
{
    const char *source = "[1, 2, 3]";
    JechTokenList list = _JechTokenizer_Lex(source);

    ASSERT_EQ(list.tokens[0].type, TOKEN_LBRACKET, "First token should be LBRACKET");
    ASSERT_EQ(list.tokens[1].type, TOKEN_NUMBER, "Second token should be NUMBER");
    ASSERT_EQ(list.tokens[2].type, TOKEN_COMMA, "Third token should be COMMA");
    ASSERT_EQ(list.tokens[3].type, TOKEN_NUMBER, "Fourth token should be NUMBER");
    ASSERT_EQ(list.tokens[4].type, TOKEN_COMMA, "Fifth token should be COMMA");
    ASSERT_EQ(list.tokens[5].type, TOKEN_NUMBER, "Sixth token should be NUMBER");
    ASSERT_EQ(list.tokens[6].type, TOKEN_RBRACKET, "Seventh token should be RBRACKET");
}

TEST(test_tokenizer_array_indexing)
{
    const char *source = "arr[0]";
    JechTokenList list = _JechTokenizer_Lex(source);

    ASSERT_EQ(list.tokens[0].type, TOKEN_IDENTIFIER, "First token should be IDENTIFIER");
    ASSERT_STR_EQ(list.tokens[0].value, "arr", "Identifier should be 'arr'");
    ASSERT_EQ(list.tokens[1].type, TOKEN_LBRACKET, "Second token should be LBRACKET");
    ASSERT_EQ(list.tokens[2].type, TOKEN_NUMBER, "Third token should be NUMBER");
    ASSERT_STR_EQ(list.tokens[2].value, "0", "Index should be '0'");
    ASSERT_EQ(list.tokens[3].type, TOKEN_RBRACKET, "Fourth token should be RBRACKET");
}

TEST(test_tokenizer_when_condition)
{
    const char *source = "when (x > 10) { say(x); }";
    JechTokenList list = _JechTokenizer_Lex(source);

    ASSERT_EQ(list.tokens[0].type, TOKEN_WHEN, "First token should be WHEN");
    ASSERT_EQ(list.tokens[1].type, TOKEN_LPAREN, "Second token should be LPAREN");
    ASSERT_EQ(list.tokens[2].type, TOKEN_IDENTIFIER, "Third token should be IDENTIFIER");
    ASSERT_EQ(list.tokens[3].type, TOKEN_GT, "Fourth token should be GT");
    ASSERT_EQ(list.tokens[4].type, TOKEN_NUMBER, "Fifth token should be NUMBER");
}

int run_tokenizer_tests()
{
    TEST_SUITE_BEGIN("Tokenizer Tests");
    
    RUN_TEST(test_tokenizer_say_string);
    RUN_TEST(test_tokenizer_keep_number);
    RUN_TEST(test_tokenizer_array_literal);
    RUN_TEST(test_tokenizer_array_indexing);
    RUN_TEST(test_tokenizer_when_condition);
    
    TEST_SUITE_END();
}
