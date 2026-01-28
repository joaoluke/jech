#include "core/ast.h"
#include "core/parser/assign.h"
#include "errors/error.h"

/**
 * Parses an assignment statement from the token list.
 */
JechASTNode * parse_assign(const JechToken * t, int remaining_tokens, int * out_consumed) {
    if (remaining_tokens < 5) {
        report_syntax_error("Incomplete assignment", t[0].line, t[0].column);
        * out_consumed = 0;
        return NULL;
    }

    if (t[1].type != TOKEN_EQUAL) {
        report_syntax_error("Expected '=' in assignment", t[1].line, t[1].column);
        * out_consumed = 0;
        return NULL;
    }

    if (remaining_tokens >= 6 &&
        (t[2].type == TOKEN_IDENTIFIER || t[2].type == TOKEN_NUMBER || t[2].type == TOKEN_STRING) &&
        (t[3].type == TOKEN_PLUS || t[3].type == TOKEN_MINUS || t[3].type == TOKEN_STAR || t[3].type == TOKEN_SLASH) &&
        (t[4].type == TOKEN_IDENTIFIER || t[4].type == TOKEN_NUMBER || t[4].type == TOKEN_STRING) &&
        t[5].type == TOKEN_SEMICOLON) {
        JechASTNode * left = _JechAST_CreateNode(
            t[2].type == TOKEN_IDENTIFIER ? JECH_AST_ASSIGN : JECH_AST_KEEP,
            t[2].value, NULL, t[2].type);

        JechASTNode * right = _JechAST_CreateNode(
            t[4].type == TOKEN_IDENTIFIER ? JECH_AST_ASSIGN : JECH_AST_KEEP,
            t[4].value, NULL, t[4].type);

        JechASTNode * binop = _JechAST_CreateNode(JECH_AST_BIN_OP, NULL, NULL, t[3].type);
        binop -> left = left;
        binop -> right = right;
        binop -> op = t[3].type;

        JechASTNode * assign = _JechAST_CreateNode(JECH_AST_ASSIGN, NULL, t[0].value, TOKEN_IDENTIFIER);
        assign -> left = binop;
        * out_consumed = 6;
        return assign;
    }

    if ((t[2].type == TOKEN_STRING || t[2].type == TOKEN_NUMBER || t[2].type == TOKEN_BOOL || t[2].type == TOKEN_IDENTIFIER) && t[3].type == TOKEN_SEMICOLON) {
        * out_consumed = 4;
        return _JechAST_CreateNode(JECH_AST_ASSIGN, t[2].value, t[0].value, t[2].type);
    }

    report_syntax_error("Invalid value type in assignment", t[2].line, t[2].column);
    * out_consumed = 0;
    return NULL;
}