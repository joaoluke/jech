#include <stddef.h>
#include "core/ast.h"
#include "core/parser/keep.h"
#include "errors/error.h"

JechASTNode *parse_keep(const JechToken *t, int remaining_tokens)
{
    if (remaining_tokens < 5)
    {
        report_syntax_error("Incomplete 'keep' statement", t[0].line, t[0].column);
        return NULL;
    }

    if (t[1].type != TOKEN_IDENTIFIER)
    {
        report_syntax_error("Expected variable name after 'keep'", t[1].line, t[1].column);
        return NULL;
    }

    if (t[2].type != TOKEN_EQUAL)
    {
        report_syntax_error("Expected '=' after variable name", t[2].line, t[2].column);
        return NULL;
    }

    if (t[3].type != TOKEN_STRING &&
        t[3].type != TOKEN_NUMBER &&
        t[3].type != TOKEN_BOOL)
    {
        report_syntax_error("Invalid value type in 'keep' statement", t[3].line, t[3].column);
        return NULL;
    }

    if (t[4].type != TOKEN_SEMICOLON)
    {
        report_syntax_error("Missing semicolon after 'keep' statement", t[4].line, t[4].column);
        return NULL;
    }

    return _JechAST_CreateNode(JECH_AST_KEEP, t[3].value, t[1].value, t[3].type);
}
