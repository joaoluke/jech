#include "utils/token_utils.h"

const char *token_type_to_str(JechTokenType type)
{
    switch (type)
    {
    case TOKEN_STRING:
        return "STRING";
    case TOKEN_NUMBER:
        return "NUMBER";
    case TOKEN_BOOL:
        return "BOOL";
    case TOKEN_IDENTIFIER:
        return "IDENTIFIER";
    case TOKEN_KEEP:
        return "KEEP";
    case TOKEN_SAY:
        return "SAY";
    case TOKEN_LPAREN:
        return "LPAREN";
    case TOKEN_RPAREN:
        return "RPAREN";
    case TOKEN_EQUAL:
        return "EQUAL";
    case TOKEN_SEMICOLON:
        return "SEMICOLON";
    case TOKEN_WHEN:
        return "WHEN";
    case TOKEN_LBRACE:
        return "LBRACE";
    case TOKEN_RBRACE:
        return "RBRACE";
    case TOKEN_EOF:
        return "EOF";
    default:
        return "UNKNOWN";
    }
}
