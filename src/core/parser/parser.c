#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core/ast.h"
#include "core/parser/parser.h"
#include "core/parser/keep.h"
#include "core/parser/say.h"
#include "core/parser/when.h"
#include "core/parser/assign.h"
#include "errors/error.h"

#define MAX_AST_ROOTS 128

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
			int consumed = 0;
			JechASTNode *node = parse_say(&t[i], remaining, &consumed);
			if (node)
			{
				roots[count++] = node;
				i += consumed;
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
			int consumed = 0;
			JechASTNode *node = parse_keep(&t[i], remaining, &consumed);
			if (node)
			{
				roots[count++] = node;
				i += consumed;
				continue;
			}
			else
			{
				break;
			}
		}

		// when(condition) { say(...) } else { say(...) }
		if (t[i].type == TOKEN_WHEN)
		{
			int remaining = tokens->count - i;
			JechASTNode *node = parse_when(&t[i], remaining);

			if (node)
			{
				roots[count++] = node;

				// Calculate offset based on condition type
				int offset = 0;
				if (node->left->type == JECH_AST_BIN_OP)
				{
					offset = 5; // when ( id op num )
				}
				else
				{
					offset = 3; // when ( bool/id )
				}

				// Base: offset + { say(...); } = offset + 8
				i += offset + 8;

				// If there's an else block, add 8 more tokens: else { say(...); }
				if (node->else_branch != NULL)
				{
					i += 8;
				}

				continue;
			}
			else
			{
				break;
			}
		}

		// 🔄 assignment: name = value;
		if ((i + 1) < tokens->count && t[i].type == TOKEN_IDENTIFIER && t[i + 1].type == TOKEN_EQUAL)
		{
			int remaining = tokens->count - i;
			int consumed = 0;
			JechASTNode *node = parse_assign(&t[i], remaining, &consumed);
			if (node)
			{
				roots[count++] = node;
				i += consumed;
				continue;
			}
			else
				break;
		}

		// Handle EOF token
		if (t[i].type == TOKEN_EOF)
		{
			break;
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