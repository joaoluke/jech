#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"
#include "constants.h"

/**
 * AST node types
 */
typedef enum
{
	AST_SAY,
	AST_KEEP,
	AST_UNKNOWN
} ASTType;

/**
 * Abstract Syntax Tree node
 */
typedef struct
{
	ASTType type;
	char value[MAX_STRING];
	char name[MAX_STRING];
	TokenType token_type;
} ASTNode;

/**
 * List of AST nodes
 */
typedef struct
{
	ASTNode nodes[128];
	int count;
} ASTList;

/**
 * Parses tokens into an AST
 */
ASTList parse_all(TokenList *tokens);

#endif
