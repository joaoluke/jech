#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core/ast.h"
#include "core/parser/parser.h"
#include "core/parser/keep.h"
#include "core/parser/say.h"
#include "core/parser/when.h"
#include "errors/error.h"

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
 * Creates an AST node for a `when(condition) { say(...) }` command
 */
static JechASTNode *create_when_node(const JechToken *condition_token, const JechToken *say_token)
{
	JechASTNode *condition = _JechAST_CreateNode(JECH_AST_BOOL_LITERAL, condition_token->value, NULL, condition_token->type);
	JechASTNode *say = _JechAST_CreateNode(JECH_AST_SAY, say_token->value, NULL, say_token->type);
	JechASTNode *when = _JechAST_CreateNode(JECH_AST_WHEN, NULL, NULL, TOKEN_WHEN);
	when->left = condition;
	when->right = say;
	return when;
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

	while (i < tokens->count)
	{
		if (count >= MAX_AST_ROOTS)
		{
			report_error(ERROR_PARSER, "Too many instructions", t[i].line, t[i].column);
			break;
		}

		// say("Hello, World!");
		if (t[i].type == TOKEN_SAY)
		{
			int remaining = tokens->count - i;
			JechASTNode *node = parse_say(&t[i], remaining);
			if (node)
			{
				roots[count++] = node;
				i += 5;
				continue;
			}
			else
			{
				break;
			}
		}

		// keep name = value;
		if (t[i].type == TOKEN_KEEP)
		{
			int remaining = tokens->count - i;
			JechASTNode *node = parse_keep(&t[i], remaining);
			if (node)
			{
				roots[count++] = node;
				i += 5;
				continue;
			}
			else
			{
				break;
			}
		}

		// when(condition) { say(...) }
		if (t[i].type == TOKEN_WHEN)
		{
			int remaining = tokens->count - i;
			JechASTNode *node = parse_when(&t[i], remaining);
			if (node)
			{
				roots[count++] = node;
				i += 11;
			}
			else
			{
				break;
			}
		}

		// Handle other tokens
		else
		{
			report_error(ERROR_PARSER, "Unexpected token or invalid statement", t[i].line, t[i].column);
			break;
		}
	}

	*out_count = count;
	return roots;
}