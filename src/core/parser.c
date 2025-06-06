#include <stdio.h>
#include <string.h>
#include "core/parser.h"

/**
 * Creates an AST node for a `say(...)` command
 */
static ASTNode create_say_node(const Token *value_token)
{
	ASTNode node;
	node.type = AST_SAY;

	strncpy(node.value, value_token->value, sizeof(node.value));
	node.token_type = value_token->type;

	return node;
}

/**
 * Creates an AST node for a `keep name = value;` command
 */
static ASTNode create_keep_node(const Token *name_token, const Token *value_token)
{
	ASTNode node;
	node.type = AST_KEEP;

	strncpy(node.name, name_token->value, sizeof(node.name));
	strncpy(node.value, value_token->value, sizeof(node.value));
	node.token_type = value_token->type;

	return node;
}

/**
 * Main function: transforms list of tokens into an AST tree
 */
ASTList parse_all(TokenList *tokens)
{
	ASTList ast;
	ast.count = 0;

	int i = 0;

	// Loop through tokens as far as possible to form complete instructions
	while (i + 4 < tokens->count)
	{
		Token *t = tokens->tokens; // alias for easier reading

		// Default: say(<value>);
		if (t[i].type == TOKEN_SAY &&
			t[i + 1].type == TOKEN_LPAREN &&
			(t[i + 2].type == TOKEN_STRING ||
			 t[i + 2].type == TOKEN_NUMBER ||
			 t[i + 2].type == TOKEN_BOOL ||
			 t[i + 2].type == TOKEN_IDENTIFIER) &&
			t[i + 3].type == TOKEN_RPAREN &&
			t[i + 4].type == TOKEN_SEMICOLON)
		{
			ast.nodes[ast.count++] = create_say_node(&t[i + 2]);
			i += 5;
		}

		// Default: keep name = value;
		else if (t[i].type == TOKEN_KEEP &&
				 t[i + 1].type == TOKEN_IDENTIFIER &&
				 t[i + 2].type == TOKEN_EQUAL &&
				 (t[i + 3].type == TOKEN_STRING ||
				  t[i + 3].type == TOKEN_NUMBER ||
				  t[i + 3].type == TOKEN_BOOL) &&
				 t[i + 4].type == TOKEN_SEMICOLON)
		{
			ast.nodes[ast.count++] = create_keep_node(&t[i + 1], &t[i + 3]);
			i += 5;
		}

		// Any other pattern is considered invalid and ends parsing.
		else
		{
			break;
		}
	}

	return ast;
}
