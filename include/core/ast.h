#ifndef JECH_AST_H
#define JECH_AST_H

#include "constants.h"
#include "tokenizer.h"

/**
 * AST node types
 */
typedef enum
{
    JECH_AST_SAY,
    JECH_AST_KEEP,
    JECH_AST_WHEN,
    JECH_AST_BOOL_LITERAL,
    JECH_AST_ASSIGN,
    JECH_AST_UNKNOWN
} JechASTType;

/**
 * Abstract Syntax Tree node (binary structure)
 */
typedef struct JechASTNode
{
    JechASTType type;
    char value[MAX_STRING];
    char name[MAX_STRING];
    JechTokenType token_type;
    struct JechASTNode *left;
    struct JechASTNode *right;
} JechASTNode;

/**
 * AST helper functions
 */
JechASTNode *_JechAST_CreateNode(JechASTType type, const char *value, const char *name, JechTokenType token_type);
void _JechAST_Free(JechASTNode *node);
void _JechAST_Print(const JechASTNode *node, int depth);

#endif
