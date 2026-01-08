#include "core/ast.h"
#include "core/parser/say.h"
#include "errors/error.h"

JechASTNode *parse_say(const JechToken *t, int remaining_tokens, int *out_consumed)
{
    if (remaining_tokens < 5)
    {
        report_syntax_error("Incomplete 'say' statement", t[0].line, t[0].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[1].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after 'say'", t[1].line, t[1].column);
        *out_consumed = 0;
        return NULL;
    }

    if (!(t[2].type == TOKEN_STRING || t[2].type == TOKEN_NUMBER ||
          t[2].type == TOKEN_BOOL || t[2].type == TOKEN_IDENTIFIER))
    {
        report_syntax_error("Invalid value in 'say' statement", t[2].line, t[2].column);
        *out_consumed = 0;
        return NULL;
    }

    if (remaining_tokens >= 8 &&
        t[2].type == TOKEN_IDENTIFIER &&
        t[3].type == TOKEN_LBRACKET &&
        t[4].type == TOKEN_NUMBER &&
        t[5].type == TOKEN_RBRACKET &&
        t[6].type == TOKEN_RPAREN &&
        t[7].type == TOKEN_SEMICOLON)
    {
        JechASTNode *say = _JechAST_CreateNode(JECH_AST_SAY_INDEX, t[2].value, NULL, TOKEN_IDENTIFIER);
        say->left = _JechAST_CreateNode(JECH_AST_NUMBER_LITERAL, t[4].value, NULL, TOKEN_NUMBER);
        *out_consumed = 8;
        return say;
    }

    if (t[3].type != TOKEN_RPAREN)
    {
        report_syntax_error("Expected ')' after value", t[3].line, t[3].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[4].type != TOKEN_SEMICOLON)
    {
        report_syntax_error("Missing semicolon after 'say' statement", t[4].line, t[4].column);
        *out_consumed = 0;
        return NULL;
    }

    *out_consumed = 5;
    return _JechAST_CreateNode(JECH_AST_SAY, t[2].value, NULL, t[2].type);
}
