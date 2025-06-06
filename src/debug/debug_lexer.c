#include <stdio.h>
#include "core/lexer.h"
#include "debug/debug_lexer.h"
#include "utils/token_utils.h"

void debug_print_tokens(const TokenList *list)
{
    printf("\n--- Tokens ---\n");
    for (int i = 0; i < list->count; i++)
    {
        printf("Token: Type=%s, Value=\"%s\"\n", token_type_to_str(list->tokens[i].type), list->tokens[i].value);
    }
    printf("\n");
}