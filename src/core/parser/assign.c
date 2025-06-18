#include "core/ast.h"
#include "core/parser/assign.h"
#include "errors/error.h"

/**
 * Parses an assignment statement from the token list.
 */
JechASTNode *parse_assign(const JechToken *t, int remaining_tokens)
{
    if (remaining_tokens < 4)
    {
        report_syntax_error("Incomplete assignment", t[0].line, t[0].column);
        return NULL;
    }

    if (t[0].type != TOKEN_IDENTIFIER)
    {
        report_syntax_error("Expected variable name", t[0].line, t[0].column);
        return NULL;
    }

    if (t[1].type != TOKEN_EQUAL)
    {
        report_syntax_error("Expected '=' after variable name", t[1].line, t[1].column);
        return NULL;
    }

    if (t[2].type != TOKEN_STRING &&
        t[2].type != TOKEN_NUMBER &&
        t[2].type != TOKEN_BOOL)
    {
        report_syntax_error("Invalid value type in assignment", t[2].line, t[2].column);
        return NULL;
    }

    if (t[3].type != TOKEN_SEMICOLON)
    {
        report_syntax_error("Missing semicolon after assignment", t[2].line, t[2].column);
        return NULL;
    }

    return _JechAST_CreateNode(JECH_AST_ASSIGN, t[2].value, t[0].value, t[2].type);
}
