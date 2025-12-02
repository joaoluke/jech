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
             (t[4].type == TOKEN_NUMBER || t[4].type == TOKEN_STRING || t[4].type == TOKEN_IDENTIFIER) &&
             t[5].type == TOKEN_RPAREN)
    {
        JechASTNode *bin = _JechAST_CreateNode(JECH_AST_BIN_OP, NULL, NULL, t[3].type);
        bin->left = _JechAST_CreateNode(JECH_AST_IDENTIFIER, t[2].value, NULL, t[2].type);

        // Create right node based on token type
        JechASTType right_type;
        if (t[4].type == TOKEN_NUMBER)
            right_type = JECH_AST_NUMBER_LITERAL;
        else if (t[4].type == TOKEN_STRING)
            right_type = JECH_AST_STRING_LITERAL;
        else
            right_type = JECH_AST_IDENTIFIER;

        bin->right = _JechAST_CreateNode(right_type, t[4].value, NULL, t[4].type);

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

    // Check for optional else block: else { say(...); }
    int else_start = base + 7; // position after '}'
    if (remaining_tokens > else_start && t[else_start].type == TOKEN_ELSE)
    {
        if (t[else_start + 1].type != TOKEN_LBRACE)
        {
            report_syntax_error("Expected '{' after 'else'", t[else_start + 1].line, t[else_start + 1].column);
            return NULL;
        }

        if (t[else_start + 2].type != TOKEN_SAY)
        {
            report_syntax_error("Expected 'say' statement inside 'else' block", t[else_start + 2].line, t[else_start + 2].column);
            return NULL;
        }

        if (t[else_start + 3].type != TOKEN_LPAREN)
        {
            report_syntax_error("Expected '(' after 'say' in else", t[else_start + 3].line, t[else_start + 3].column);
            return NULL;
        }

        if (t[else_start + 4].type != TOKEN_STRING &&
            t[else_start + 4].type != TOKEN_IDENTIFIER &&
            t[else_start + 4].type != TOKEN_NUMBER)
        {
            report_syntax_error("Invalid value inside 'say' in else", t[else_start + 4].line, t[else_start + 4].column);
            return NULL;
        }

        if (t[else_start + 5].type != TOKEN_RPAREN)
        {
            report_syntax_error("Expected ')' after value in 'say' in else", t[else_start + 5].line, t[else_start + 5].column);
            return NULL;
        }

        if (t[else_start + 6].type != TOKEN_SEMICOLON)
        {
            report_syntax_error("Missing semicolon after 'say' in else", t[else_start + 6].line, t[else_start + 6].column);
            return NULL;
        }

        if (t[else_start + 7].type != TOKEN_RBRACE)
        {
            report_syntax_error("Expected '}' to close 'else' block", t[else_start + 7].line, t[else_start + 7].column);
            return NULL;
        }

        JechASTNode *else_say = _JechAST_CreateNode(JECH_AST_SAY, t[else_start + 4].value, NULL, t[else_start + 4].type);
        when->else_branch = else_say;
    }

    return when;
}