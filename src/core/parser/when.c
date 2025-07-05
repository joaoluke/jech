#include "core/ast.h"
#include "core/parser/when.h"
#include "errors/error.h"

JechASTNode *parse_when(const JechToken *t, int remaining_tokens)
{
    if (remaining_tokens < 7)
    {
        report_syntax_error("Incomplete 'when' statement", t[0].line, t[0].column);
        return NULL;
    }

    if (t[1].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after 'when'", t[1].line, t[1].column);
        return NULL;
    }

    JechASTNode *condition = NULL;
    int offset = 0;

    if ((t[2].type == TOKEN_BOOL || t[2].type == TOKEN_IDENTIFIER) && t[3].type == TOKEN_RPAREN)
    {
        if (t[2].type == TOKEN_BOOL)
        {
            condition = _JechAST_CreateNode(JECH_AST_BOOL_LITERAL, t[2].value, NULL, t[2].type);
        }
        else
        {
            condition = _JechAST_CreateNode(JECH_AST_IDENTIFIER, t[2].value, NULL, t[2].type);
        }
        offset = 3;
    }
    else if (t[2].type == TOKEN_IDENTIFIER &&
             (t[3].type == TOKEN_GT || t[3].type == TOKEN_LT || t[3].type == TOKEN_EQEQ) &&
             t[4].type == TOKEN_NUMBER &&
             t[5].type == TOKEN_RPAREN)
    {

        JechASTNode *bin = _JechAST_CreateNode(JECH_AST_BIN_OP, NULL, NULL, t[3].type);
        bin->left = _JechAST_CreateNode(JECH_AST_IDENTIFIER, t[2].value, NULL, t[2].type);
        bin->right = _JechAST_CreateNode(JECH_AST_NUMBER_LITERAL, t[4].value, NULL, t[4].type);

        condition = bin;
        offset = 5;
    }
    else
    {
        report_syntax_error("Invalid condition in 'when' statement", t[2].line, t[2].column);
        return NULL;
    }
    int base = offset + 1;

    if (t[base].type != TOKEN_LBRACE)
    {
        report_syntax_error("Expected '{' to start block", t[base].line, t[base].column);
        return NULL;
    }

    if (t[base + 1].type != TOKEN_SAY)
    {
        report_syntax_error("Expected 'say' statement inside 'when' block", t[base + 1].line, t[base + 1].column);
        return NULL;
    }

    if (t[base + 2].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after 'say'", t[base + 2].line, t[base + 2].column);
        return NULL;
    }

    if (t[base + 3].type != TOKEN_STRING &&
        t[base + 3].type != TOKEN_IDENTIFIER &&
        t[base + 3].type != TOKEN_NUMBER)
    {
        report_syntax_error("Invalid value inside 'say'", t[base + 3].line, t[base + 3].column);
        return NULL;
    }

    if (t[base + 4].type != TOKEN_RPAREN)
    {
        report_syntax_error("Expected ')' after value in 'say'", t[base + 4].line, t[base + 4].column);
        return NULL;
    }

    if (t[base + 5].type != TOKEN_SEMICOLON)
    {
        report_syntax_error("Missing semicolon after 'say' in 'when'", t[base + 5].line, t[base + 5].column);
        return NULL;
    }

    if (t[base + 6].type != TOKEN_RBRACE)
    {
        report_syntax_error("Expected '}' to close 'when' block", t[base + 6].line, t[base + 6].column);
        return NULL;
    }

    JechASTNode *say = _JechAST_CreateNode(JECH_AST_SAY, t[base + 3].value, NULL, t[base + 3].type);

    JechASTNode *when = _JechAST_CreateNode(JECH_AST_WHEN, NULL, NULL, t[0].type);
    when->left = condition;
    when->right = say;

    return when;
}