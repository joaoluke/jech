#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "core/ast.h"

/**
 * Creates a new AST node with the given data.
 * Initializes `left` and `right` to NULL.
 */
JechASTNode *_JechAST_CreateNode(JechASTType type, const char *value, const char *name, JechTokenType token_type)
{
    JechASTNode *node = malloc(sizeof(JechASTNode));
    if (!node)
    {
        fprintf(stderr, "AST error: malloc failed\n");
        exit(1);
    }

    node->type = type;
    strncpy(node->value, value ? value : "", MAX_STRING);
    strncpy(node->name, name ? name : "", MAX_STRING);
    node->value[MAX_STRING - 1] = '\0';
    node->name[MAX_STRING - 1] = '\0';
    node->token_type = token_type;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/**
 * Recursively frees all nodes of an AST tree.
 */
void _JechAST_Free(JechASTNode *node)
{
    if (!node)
        return;
    _JechAST_Free(node->left);
    _JechAST_Free(node->right);
    free(node);
}

/**
 * Prints the AST in tree form, indented according to depth.
 * Useful for visual debugging.
 */
void _JechAST_Print(const JechASTNode *node, int depth)
{
    if (!node)
        return;

    for (int i = 0; i < depth; i++)
        printf("  ");
    printf("• %d (%s%s%s)\n", node->type,
           node->name[0] ? node->name : "",
           (node->name[0] && node->value[0]) ? " = " : "",
           node->value[0] ? node->value : "");

    _JechAST_Print(node->left, depth + 1);
    _JechAST_Print(node->right, depth + 1);
}
