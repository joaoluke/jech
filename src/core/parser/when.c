#include "core/ast.h"
#include "core/parser/when.h"
#include "errors/error.h"

JechASTNode *parse_when(const JechToken *t, int remaining_tokens)
{
    if (remaining_tokens < 11)
    {
        report_syntax_error("Incomplete 'when' statement", t[0].line, t[0].column);
        return NULL;
    }

    if (t[1].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after 'when'", t[1].line, t[1].column);
        return NULL;
    }

    if (t[2].type != TOKEN_BOOL && t[2].type != TOKEN_IDENTIFIER)
    {
        report_syntax_error("Expected condition (bool or variable) after '('", t[2].line, t[2].column);
        return NULL;
    }

    if (t[3].type != TOKEN_RPAREN)
    {
        report_syntax_error("Expected ')' after condition", t[3].line, t[3].column);
        return NULL;
    }

    if (t[4].type != TOKEN_LBRACE)
    {
        report_syntax_error("Expected '{' to start block", t[4].line, t[4].column);
        return NULL;
    }

    if (t[5].type != TOKEN_SAY)
    {
        report_syntax_error("Expected 'say' statement inside 'when' block", t[5].line, t[5].column);
        return NULL;
    }

    if (t[6].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after 'say'", t[6].line, t[6].column);
        return NULL;
    }

    if (t[7].type != TOKEN_STRING &&
        t[7].type != TOKEN_IDENTIFIER &&
        t[7].type != TOKEN_NUMBER)
    {
        report_syntax_error("Invalid value inside 'say'", t[7].line, t[7].column);
        return NULL;
    }

    if (t[8].type != TOKEN_RPAREN)
    {
        report_syntax_error("Expected ')' after value in 'say'", t[8].line, t[8].column);
        return NULL;
    }

    if (t[9].type != TOKEN_SEMICOLON)
    {
        report_syntax_error("Missing semicolon after 'say' in 'when'", t[9].line, t[9].column);
        return NULL;
    }

    if (t[10].type != TOKEN_RBRACE)
    {
        report_syntax_error("Expected '}' to close 'when' block", t[10].line, t[10].column);
        return NULL;
    }

    JechASTNode *condition = _JechAST_CreateNode(JECH_AST_BOOL_LITERAL, t[2].value, NULL, t[2].type);
    JechASTNode *say = _JechAST_CreateNode(JECH_AST_SAY, t[7].value, NULL, t[7].type);
    JechASTNode *when = _JechAST_CreateNode(JECH_AST_WHEN, NULL, NULL, t[0].type);
    when->left = condition;
    when->right = say;

    return when;
}
