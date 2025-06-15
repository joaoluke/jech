#include "core/ast.h"
#include "core/parser/say.h"
#include "errors/error.h"

JechASTNode *parse_say(const JechToken *t, int remaining_tokens)
{
    if (remaining_tokens < 5)
    {
        report_syntax_error("Incomplete 'say' statement", t[0].line, t[0].column);
        return NULL;
    }

    if (t[1].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after 'say'", t[1].line, t[1].column);
        return NULL;
    }

    if (!(t[2].type == TOKEN_STRING || t[2].type == TOKEN_NUMBER ||
          t[2].type == TOKEN_BOOL || t[2].type == TOKEN_IDENTIFIER))
    {
        report_syntax_error("Invalid value in 'say' statement", t[2].line, t[2].column);
        return NULL;
    }

    if (t[3].type != TOKEN_RPAREN)
    {
        report_syntax_error("Expected ')' after value", t[3].line, t[3].column);
        return NULL;
    }

    if (t[4].type != TOKEN_SEMICOLON)
    {
        report_syntax_error("Missing semicolon after 'say' statement", t[4].line, t[4].column);
        return NULL;
    }

    return _JechAST_CreateNode(JECH_AST_SAY, t[2].value, NULL, t[2].type);
}
