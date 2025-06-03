#include <stdio.h>
#include <string.h>
#include "parser.h"

ASTList parse_all(TokenList *tokens)
{
	ASTList ast;
	ast.count = 0;

	int i = 0;
	while (i + 4 < tokens->count)
	{
		if (tokens->tokens[i].type == TOKEN_SAY &&
			tokens->tokens[i + 1].type == TOKEN_LPAREN &&
			(tokens->tokens[i + 2].type == TOKEN_STRING ||
			 tokens->tokens[i + 2].type == TOKEN_NUMBER ||
			 tokens->tokens[i + 2].type == TOKEN_BOOL) &&
			tokens->tokens[i + 3].type == TOKEN_RPAREN &&
			tokens->tokens[i + 4].type == TOKEN_SEMICOLON)
		{
			ASTNode node;
			node.type = AST_SAY;
			strncpy(node.value, tokens->tokens[i + 2].value, sizeof(node.value));
			node.token_type = tokens->tokens[i + 2].type;

			ast.nodes[ast.count++] = node;
			i += 5;
		}
		else
		{
			break;
		}
	}

	return ast;
}
