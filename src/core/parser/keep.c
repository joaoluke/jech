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

    if (remaining_tokens >= 6 && t[3].type == TOKEN_LBRACKET)
    {
        int i = 4;

        if (i >= remaining_tokens)
        {
            report_syntax_error("Incomplete array literal in 'keep' statement", t[3].line, t[3].column);
            return NULL;
        }

        JechASTNode *array = _JechAST_CreateNode(JECH_AST_ARRAY_LITERAL, NULL, NULL, TOKEN_LBRACKET);

        JechASTNode *head = NULL;
        JechASTNode *tail = NULL;

        if (t[i].type != TOKEN_RBRACKET)
        {
            while (1)
            {
                if (t[i].type != TOKEN_STRING &&
                    t[i].type != TOKEN_NUMBER &&
                    t[i].type != TOKEN_BOOL)
                {
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

                JechASTNode *elem = _JechAST_CreateNode(elem_type, t[i].value, NULL, t[i].type);

                if (!head)
                {
                    head = elem;
                    tail = elem;
                }
                else
                {
                    tail->right = elem;
                    tail = elem;
                }

                i++;
                if (i >= remaining_tokens)
                {
                    report_syntax_error("Incomplete array literal in 'keep' statement", t[0].line, t[0].column);
                    _JechAST_Free(array);
                    return NULL;
                }

                if (t[i].type == TOKEN_COMMA)
                {
                    i++;
                    if (i >= remaining_tokens)
                    {
                        report_syntax_error("Incomplete array literal in 'keep' statement", t[0].line, t[0].column);
                        _JechAST_Free(array);
                        return NULL;
                    }
                    continue;
                }

                if (t[i].type == TOKEN_RBRACKET)
                {
                    break;
                }

                report_syntax_error("Expected ',' or ']' in array literal", t[i].line, t[i].column);
                _JechAST_Free(array);
                return NULL;
            }
        }

        if (t[i].type != TOKEN_RBRACKET)
        {
            report_syntax_error("Expected ']' to close array literal", t[i].line, t[i].column);
            _JechAST_Free(array);
            return NULL;
        }
        i++;

        if (i >= remaining_tokens || t[i].type != TOKEN_SEMICOLON)
        {
            report_syntax_error("Missing semicolon after 'keep' statement", t[i].line, t[i].column);
            _JechAST_Free(array);
            return NULL;
        }

        array->left = head;

        JechASTNode *keep = _JechAST_CreateNode(JECH_AST_KEEP, NULL, t[1].value, TOKEN_LBRACKET);
        keep->left = array;
        return keep;
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
