#include "core/ast.h"
#include "core/parser/function.h"
#include "errors/error.h"
#include <string.h>

/**
 * Parses a function declaration from the token list.
 * Syntax: do greet(name) { say("Hello " + name); }
 * 
 * Token sequence:
 * [0] TOKEN_DO
 * [1] TOKEN_IDENTIFIER (function name)
 * [2] TOKEN_LPAREN
 * [3] TOKEN_IDENTIFIER (param1)
 * [4] TOKEN_COMMA (optional, if more params)
 * [5] TOKEN_IDENTIFIER (param2)
 * ...
 * [n] TOKEN_RPAREN
 * [n+1] TOKEN_LBRACE
 * [n+2...] function body statements
 * [last] TOKEN_RBRACE
 */
JechASTNode *parse_function_decl(const JechToken *t, int remaining_tokens, int *out_consumed)
{
    if (remaining_tokens < 7)
    {
        report_syntax_error("Incomplete function declaration", t[0].line, t[0].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[0].type != TOKEN_DO)
    {
        report_syntax_error("Expected 'do' keyword", t[0].line, t[0].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[1].type != TOKEN_IDENTIFIER)
    {
        report_syntax_error("Expected function name after 'do'", t[1].line, t[1].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[2].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after function name", t[2].line, t[2].column);
        *out_consumed = 0;
        return NULL;
    }

    int i = 3;
    JechASTNode *param_list = _JechAST_CreateNode(JECH_AST_PARAM_LIST, NULL, NULL, TOKEN_IDENTIFIER);
    JechASTNode *param_head = NULL;
    JechASTNode *param_tail = NULL;

    if (t[i].type != TOKEN_RPAREN)
    {
        while (i < remaining_tokens)
        {
            if (t[i].type != TOKEN_IDENTIFIER)
            {
                report_syntax_error("Expected parameter name", t[i].line, t[i].column);
                _JechAST_Free(param_list);
                *out_consumed = 0;
                return NULL;
            }

            JechASTNode *param = _JechAST_CreateNode(JECH_AST_IDENTIFIER, t[i].value, NULL, TOKEN_IDENTIFIER);
            
            if (!param_head)
            {
                param_head = param;
                param_tail = param;
            }
            else
            {
                param_tail->right = param;
                param_tail = param;
            }

            i++;

            if (i >= remaining_tokens)
            {
                report_syntax_error("Incomplete parameter list", t[0].line, t[0].column);
                _JechAST_Free(param_list);
                *out_consumed = 0;
                return NULL;
            }

            if (t[i].type == TOKEN_COMMA)
            {
                i++;
                continue;
            }
            else if (t[i].type == TOKEN_RPAREN)
            {
                break;
            }
            else
            {
                report_syntax_error("Expected ',' or ')' in parameter list", t[i].line, t[i].column);
                _JechAST_Free(param_list);
                *out_consumed = 0;
                return NULL;
            }
        }
    }

    if (t[i].type != TOKEN_RPAREN)
    {
        report_syntax_error("Expected ')' after parameters", t[i].line, t[i].column);
        _JechAST_Free(param_list);
        *out_consumed = 0;
        return NULL;
    }
    i++;

    if (i >= remaining_tokens || t[i].type != TOKEN_LBRACE)
    {
        report_syntax_error("Expected '{' to start function body", t[i].line, t[i].column);
        _JechAST_Free(param_list);
        *out_consumed = 0;
        return NULL;
    }
    i++;

    int brace_count = 1;
    while (i < remaining_tokens && brace_count > 0)
    {
        if (t[i].type == TOKEN_LBRACE)
            brace_count++;
        else if (t[i].type == TOKEN_RBRACE)
            brace_count--;
        i++;
    }

    if (brace_count != 0)
    {
        report_syntax_error("Unmatched braces in function body", t[0].line, t[0].column);
        _JechAST_Free(param_list);
        *out_consumed = 0;
        return NULL;
    }

    param_list->left = param_head;

    JechASTNode *func_decl = _JechAST_CreateNode(JECH_AST_FUNCTION_DECL, NULL, t[1].value, TOKEN_IDENTIFIER);
    func_decl->left = param_list;

    *out_consumed = i;
    return func_decl;
}

/**
 * Parses a function call from the token list.
 * Syntax: greet("World")
 * 
 * Token sequence:
 * [0] TOKEN_IDENTIFIER (function name)
 * [1] TOKEN_LPAREN
 * [2] TOKEN_STRING/NUMBER/IDENTIFIER (arg1)
 * [3] TOKEN_COMMA (optional, if more args)
 * [4] TOKEN_STRING/NUMBER/IDENTIFIER (arg2)
 * ...
 * [n] TOKEN_RPAREN
 * [n+1] TOKEN_SEMICOLON
 */
JechASTNode *parse_function_call(const JechToken *t, int remaining_tokens, int *out_consumed)
{
    if (remaining_tokens < 4)
    {
        report_syntax_error("Incomplete function call", t[0].line, t[0].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[0].type != TOKEN_IDENTIFIER)
    {
        report_syntax_error("Expected function name", t[0].line, t[0].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[1].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after function name", t[1].line, t[1].column);
        *out_consumed = 0;
        return NULL;
    }

    int i = 2;
    JechASTNode *arg_list = _JechAST_CreateNode(JECH_AST_PARAM_LIST, NULL, NULL, TOKEN_IDENTIFIER);
    JechASTNode *arg_head = NULL;
    JechASTNode *arg_tail = NULL;

    if (t[i].type != TOKEN_RPAREN)
    {
        while (i < remaining_tokens)
        {
            if (t[i].type != TOKEN_STRING && t[i].type != TOKEN_NUMBER && 
                t[i].type != TOKEN_IDENTIFIER && t[i].type != TOKEN_BOOL)
            {
                report_syntax_error("Invalid argument in function call", t[i].line, t[i].column);
                _JechAST_Free(arg_list);
                *out_consumed = 0;
                return NULL;
            }

            JechASTType arg_type = JECH_AST_IDENTIFIER;
            if (t[i].type == TOKEN_STRING)
                arg_type = JECH_AST_STRING_LITERAL;
            else if (t[i].type == TOKEN_NUMBER)
                arg_type = JECH_AST_NUMBER_LITERAL;
            else if (t[i].type == TOKEN_BOOL)
                arg_type = JECH_AST_BOOL_LITERAL;

            JechASTNode *arg = _JechAST_CreateNode(arg_type, t[i].value, NULL, t[i].type);
            
            if (!arg_head)
            {
                arg_head = arg;
                arg_tail = arg;
            }
            else
            {
                arg_tail->right = arg;
                arg_tail = arg;
            }

            i++;

            if (i >= remaining_tokens)
            {
                report_syntax_error("Incomplete argument list", t[0].line, t[0].column);
                _JechAST_Free(arg_list);
                *out_consumed = 0;
                return NULL;
            }

            if (t[i].type == TOKEN_COMMA)
            {
                i++;
                continue;
            }
            else if (t[i].type == TOKEN_RPAREN)
            {
                break;
            }
            else
            {
                report_syntax_error("Expected ',' or ')' in argument list", t[i].line, t[i].column);
                _JechAST_Free(arg_list);
                *out_consumed = 0;
                return NULL;
            }
        }
    }

    if (t[i].type != TOKEN_RPAREN)
    {
        report_syntax_error("Expected ')' after arguments", t[i].line, t[i].column);
        _JechAST_Free(arg_list);
        *out_consumed = 0;
        return NULL;
    }
    i++;

    if (i >= remaining_tokens || t[i].type != TOKEN_SEMICOLON)
    {
        report_syntax_error("Expected ';' after function call", t[i].line, t[i].column);
        _JechAST_Free(arg_list);
        *out_consumed = 0;
        return NULL;
    }
    i++;

    arg_list->left = arg_head;

    JechASTNode *func_call = _JechAST_CreateNode(JECH_AST_FUNCTION_CALL, NULL, t[0].value, TOKEN_IDENTIFIER);
    func_call->left = arg_list;

    *out_consumed = i;
    return func_call;
}
