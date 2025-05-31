#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Represents a type of command
typedef enum
{
	AST_SAY
} ASTType;

typedef struct
{
	ASTType type;
	char value[256];
} ASTNode;

typedef struct
{
	ASTNode nodes[128];
	int count;
} ASTList;

ASTList parse_all(TokenList *tokens);

#endif
