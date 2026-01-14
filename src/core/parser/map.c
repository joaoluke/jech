#include "core/ast.h"
#include "core/parser/map.h"
#include "errors/error.h"

/**
 * Parses array.map() syntax
 * Syntax: keep result = arrayName.map(operator value);
 * Example: keep doubled = numbers.map(* 2);
 * 
 * Token sequence:
 * [0] TOKEN_IDENTIFIER (array name)
 * [1] TOKEN_DOT
 * [2] TOKEN_MAP
 * [3] TOKEN_LPAREN
 * [4] TOKEN_PLUS/MINUS/STAR/SLASH (operator)
 * [5] TOKEN_NUMBER (value)
 * [6] TOKEN_RPAREN
 * [7] TOKEN_SEMICOLON
 */
JechASTNode *parse_map(const JechToken *t, int remaining_tokens, int *out_consumed)
{
    if (remaining_tokens < 8)
    {
        report_syntax_error("Incomplete map expression", t[0].line, t[0].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[0].type != TOKEN_IDENTIFIER)
    {
        report_syntax_error("Expected array name before .map()", t[0].line, t[0].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[1].type != TOKEN_DOT)
    {
        report_syntax_error("Expected '.' after array name", t[1].line, t[1].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[2].type != TOKEN_MAP)
    {
        report_syntax_error("Expected 'map' after '.'", t[2].line, t[2].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[3].type != TOKEN_LPAREN)
    {
        report_syntax_error("Expected '(' after 'map'", t[3].line, t[3].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[4].type != TOKEN_PLUS && t[4].type != TOKEN_MINUS && 
        t[4].type != TOKEN_STAR && t[4].type != TOKEN_SLASH)
    {
        report_syntax_error("Expected operator (+, -, *, /) in map", t[4].line, t[4].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[5].type != TOKEN_NUMBER)
    {
        report_syntax_error("Expected number after operator in map", t[5].line, t[5].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[6].type != TOKEN_RPAREN)
    {
        report_syntax_error("Expected ')' after map operation", t[6].line, t[6].column);
        *out_consumed = 0;
        return NULL;
    }

    if (t[7].type != TOKEN_SEMICOLON)
    {
        report_syntax_error("Expected ';' after map expression", t[7].line, t[7].column);
        *out_consumed = 0;
        return NULL;
    }

    // Create MAP node
    // node->value = array name
    // node->left = operator node (stores operator type and operand value)
    JechASTNode *map_node = _JechAST_CreateNode(JECH_AST_MAP, t[0].value, NULL, TOKEN_IDENTIFIER);
    
    // Create operator node to store the operation
    JechASTNode *op_node = _JechAST_CreateNode(JECH_AST_NUMBER_LITERAL, t[5].value, NULL, t[4].type);
    op_node->op = t[4].type;
    
    map_node->left = op_node;
    
    *out_consumed = 8;
    return map_node;
}
