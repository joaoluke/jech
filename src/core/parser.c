#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core/parser.h"
#include "core/ast.h"

#define MAX_AST_ROOTS 128

/**
 * Creates an AST node for a `say(...)` command
 */
static JechASTNode *create_say_node(const JechToken *value_token)
{
	return _JechAST_CreateNode(JECH_AST_SAY, value_token->value, NULL, value_token->type);
}

/**
 * Creates an AST node for a `keep name = value;` command
 */
static JechASTNode *create_keep_node(const JechToken *name_token, const JechToken *value_token)
{
	return _JechAST_CreateNode(JECH_AST_KEEP, value_token->value, name_token->value, value_token->type);
}

/**
 * Main function: transforms list of tokens into an AST tree
 */
JechASTNode **_JechParser_ParseAll(const JechTokenList *tokens, int *out_count)
{
	static JechASTNode *roots[MAX_AST_ROOTS];
	int count = 0;
	int i = 0;
	const JechToken *t = tokens->tokens;

	while (i + 4 < tokens->count)
	{
		if (count >= MAX_AST_ROOTS)
		{
			fprintf(stderr, "Parser error: AST root limit reached\n");
			exit(1);
		}

		if (t[i].type == TOKEN_SAY &&
			t[i + 1].type == TOKEN_LPAREN &&
			(t[i + 2].type == TOKEN_STRING || t[i + 2].type == TOKEN_NUMBER ||
			 t[i + 2].type == TOKEN_BOOL || t[i + 2].type == TOKEN_IDENTIFIER) &&
			t[i + 3].type == TOKEN_RPAREN &&
			t[i + 4].type == TOKEN_SEMICOLON)
		{
			roots[count++] = create_say_node(&t[i + 2]);
			i += 5;
		}
		else if (t[i].type == TOKEN_KEEP &&
				 t[i + 1].type == TOKEN_IDENTIFIER &&
				 t[i + 2].type == TOKEN_EQUAL &&
				 (t[i + 3].type == TOKEN_STRING || t[i + 3].type == TOKEN_NUMBER || t[i + 3].type == TOKEN_BOOL) &&
				 t[i + 4].type == TOKEN_SEMICOLON)
		{
			roots[count++] = create_keep_node(&t[i + 1], &t[i + 3]);
			i += 5;
		}
		else
		{
			fprintf(stderr, "Parser error: unexpected token near '%s'\n", t[i].value);
			break;
		}
	}

	*out_count = count;
	return roots;
}