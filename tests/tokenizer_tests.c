#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "core/tokenizer.h"

void test_tokenizer_say_string()
{
    const char *source = "say(\"Hello\");";
    JechTokenList list = _JechTokenizer_Lex(source);

    assert(list.count == 6);

    assert(list.tokens[0].type == TOKEN_SAY);
    assert(list.tokens[1].type == TOKEN_LPAREN);
    assert(list.tokens[2].type == TOKEN_STRING);
    assert(strcmp(list.tokens[2].value, "Hello") == 0);
    assert(list.tokens[3].type == TOKEN_RPAREN);
    assert(list.tokens[4].type == TOKEN_SEMICOLON);
    assert(list.tokens[5].type == TOKEN_EOF);
}
