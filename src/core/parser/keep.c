#include <stddef.h>
#include "core/ast.h"
#include "core/parser/keep.h"
#include "core/parser/map.h"
#include "errors/error.h"

JechASTNode * parse_keep(const JechToken * t, int remaining_tokens, int * out_consumed) {
    if (remaining_tokens < 5) {
        report_syntax_error("Incomplete 'keep' statement", t[0].line, t[0].column);
        * out_consumed = 0;
        return NULL;
    }

    if (t[1].type != TOKEN_IDENTIFIER) {
        report_syntax_error("Expected variable name after 'keep'", t[1].line, t[1].column);
        * out_consumed = 0;
        return NULL;
    }

    if (t[2].type != TOKEN_EQUAL) {
        report_syntax_error("Expected '=' after variable name", t[2].line, t[2].column);
        * out_consumed = 0;
        return NULL;
    }

    // Check for array.map() syntax: keep result = array.map(op value);
    if (remaining_tokens >= 11 &&
        t[3].type == TOKEN_IDENTIFIER &&
        t[4].type == TOKEN_DOT &&
        t[5].type == TOKEN_MAP) {
        int map_consumed = 0;
        JechASTNode * map_node = parse_map( & t[3], remaining_tokens - 3, & map_consumed);

        if (!map_node) {
            * out_consumed = 0;
            return NULL;
        }

        // Create KEEP node with map as child
        JechASTNode * keep = _JechAST_CreateNode(JECH_AST_KEEP, NULL, t[1].value, TOKEN_IDENTIFIER);
        keep -> left = map_node;

        * out_consumed = 3 + map_consumed; // keep + varname + = + map_consumed
        return keep;
    }

    if (remaining_tokens >= 6 && t[3].type == TOKEN_LBRACKET) {
        int i = 4;

        if (i >= remaining_tokens) {
            report_syntax_error("Incomplete array literal in 'keep' statement", t[3].line, t[3].column);
            return NULL;
        }

        JechASTNode * array = _JechAST_CreateNode(JECH_AST_ARRAY_LITERAL, NULL, NULL, TOKEN_LBRACKET);

        JechASTNode * head = NULL;
        JechASTNode * tail = NULL;

        if (t[i].type != TOKEN_RBRACKET) {
            while (1) {
                if (t[i].type != TOKEN_STRING &&
                    t[i].type != TOKEN_NUMBER &&
                    t[i].type != TOKEN_BOOL) {
                    report_syntax_error("Invalid array element in 'keep' statement", t[i].line, t[i].column);
                    _JechAST_Free(array);
                    return NULL;
                }

                JechASTType elem_type = JECH_AST_UNKNOWN;
                if (t[i].type == TOKEN_STRING)
                    elem_type = JECH_AST_STRING_LITERAL;
                else if (t[i].type == TOKEN_NUMBER)
                    elem_type = JECH_AST_NUMBER_LITERAL;
                else
                    elem_type = JECH_AST_BOOL_LITERAL;

                JechASTNode * elem = _JechAST_CreateNode(elem_type, t[i].value, NULL, t[i].type);

                if (!head) {
                    head = elem;
                    tail = elem;
                } else {
                    tail -> right = elem;
                    tail = elem;
                }

                i++;
                if (i >= remaining_tokens) {
                    report_syntax_error("Incomplete array literal in 'keep' statement", t[0].line, t[0].column);
                    _JechAST_Free(array);
                    return NULL;
                }

                if (t[i].type == TOKEN_COMMA) {
                    i++;
                    if (i >= remaining_tokens) {
                        report_syntax_error("Incomplete array literal in 'keep' statement", t[0].line, t[0].column);
                        _JechAST_Free(array);
                        return NULL;
                    }
                    continue;
                }

                if (t[i].type == TOKEN_RBRACKET) {
                    break;
                }

                report_syntax_error("Expected ',' or ']' in array literal", t[i].line, t[i].column);
                _JechAST_Free(array);
                return NULL;
            }
        }

        if (t[i].type != TOKEN_RBRACKET) {
            report_syntax_error("Expected ']' to close array literal", t[i].line, t[i].column);
            _JechAST_Free(array);
            return NULL;
        }
        i++;

        if (i >= remaining_tokens || t[i].type != TOKEN_SEMICOLON) {
            report_syntax_error("Missing semicolon after 'keep' statement", t[i].line, t[i].column);
            _JechAST_Free(array);
            return NULL;
        }

        array -> left = head;

        JechASTNode * keep = _JechAST_CreateNode(JECH_AST_KEEP, NULL, t[1].value, TOKEN_LBRACKET);
        keep -> left = array;
        * out_consumed = i + 1;
        return keep;
    }

    // Check for binary operation: keep x = a + b;
    if (remaining_tokens >= 7 &&
        (t[3].type == TOKEN_IDENTIFIER || t[3].type == TOKEN_NUMBER || t[3].type == TOKEN_STRING) &&
        (t[4].type == TOKEN_PLUS || t[4].type == TOKEN_MINUS || t[4].type == TOKEN_STAR || t[4].type == TOKEN_SLASH) &&
        (t[5].type == TOKEN_IDENTIFIER || t[5].type == TOKEN_NUMBER || t[5].type == TOKEN_STRING) &&
        t[6].type == TOKEN_SEMICOLON) {
        JechASTNode * left = _JechAST_CreateNode(
            t[3].type == TOKEN_IDENTIFIER ? JECH_AST_ASSIGN : JECH_AST_KEEP,
            t[3].value, t[3].type == TOKEN_IDENTIFIER ? t[3].value : NULL, t[3].type);

        JechASTNode * right = _JechAST_CreateNode(
            t[5].type == TOKEN_IDENTIFIER ? JECH_AST_ASSIGN : JECH_AST_KEEP,
            t[5].value, t[5].type == TOKEN_IDENTIFIER ? t[5].value : NULL, t[5].type);

        JechASTNode * binop = _JechAST_CreateNode(JECH_AST_BIN_OP, NULL, NULL, t[4].type);
        binop -> left = left;
        binop -> right = right;
        binop -> op = t[4].type;

        JechASTNode * keep = _JechAST_CreateNode(JECH_AST_KEEP, NULL, t[1].value, TOKEN_IDENTIFIER);
        keep -> left = binop;
        * out_consumed = 7;
        return keep;
    }

    if (t[3].type != TOKEN_STRING &&
        t[3].type != TOKEN_NUMBER &&
        t[3].type != TOKEN_BOOL) {
        report_syntax_error("Invalid value type in 'keep' statement", t[3].line, t[3].column);
        * out_consumed = 0;
        return NULL;
    }

    if (t[4].type != TOKEN_SEMICOLON) {
        report_syntax_error("Missing semicolon after 'keep' statement", t[4].line, t[4].column);
        * out_consumed = 0;
        return NULL;
    }

    * out_consumed = 5;
    return _JechAST_CreateNode(JECH_AST_KEEP, t[3].value, t[1].value, t[3].type);
}