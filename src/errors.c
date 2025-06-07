#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "errors.h"

void check_lexical_errors(const JechTokenList *tokens, const char *source)
{
    for (int i = 0; i < tokens->count; i++)
    {
        if (tokens->tokens[i].type == TOKEN_UNKNOWN)
        {
            printf("Aborting due to unknown token: \"%s\"\n", tokens->tokens[i].value);
            free((void *)source); 
            exit(1);
        }
    }
}
