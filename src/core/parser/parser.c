#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "core/ast.h"
#include "core/parser/parser.h"
#include "core/parser/keep.h"
#include "core/parser/say.h"
#include "core/parser/when.h"
#include "core/parser/assign.h"
#include "core/parser/map.h"
#include "core/parser/function.h"
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

		// array.map() standalone expression
		if ((i + 2) < tokens->count && 
		    t[i].type == TOKEN_IDENTIFIER && 
		    t[i + 1].type == TOKEN_DOT && 
		    t[i + 2].type == TOKEN_MAP)
		{
			int remaining = tokens->count - i;
			int consumed = 0;
			JechASTNode *node = parse_map(&t[i], remaining, &consumed);
			if (node)
			{
				roots[count++] = node;
				i += consumed;
				continue;
			}
			else
				break;
		}

		// do greet(name) { ... }
		if (t[i].type == TOKEN_DO)
		{
			int remaining = tokens->count - i;
			int consumed = 0;
			JechASTNode *node = parse_function_decl(&t[i], remaining, &consumed);
			if (node)
			{
				roots[count++] = node;
				i += consumed;
				continue;
			}
			else
				break;
		}

		// return value; or return;
		if (t[i].type == TOKEN_RETURN)
		{
			if ((i + 1) < tokens->count && t[i + 1].type == TOKEN_SEMICOLON)
			{
				// return; (no value)
				JechASTNode *node = _JechAST_CreateNode(JECH_AST_RETURN, "", NULL, TOKEN_UNKNOWN);
				roots[count++] = node;
				i += 2;
				continue;
			}
			else if ((i + 2) < tokens->count && t[i + 2].type == TOKEN_SEMICOLON)
			{
				// return value;
				JechASTNode *node = _JechAST_CreateNode(JECH_AST_RETURN, t[i + 1].value, NULL, t[i + 1].type);
				roots[count++] = node;
				i += 3;
				continue;
			}
			else if ((i + 4) < tokens->count &&
				(t[i + 2].type == TOKEN_PLUS || t[i + 2].type == TOKEN_MINUS ||
				 t[i + 2].type == TOKEN_STAR || t[i + 2].type == TOKEN_SLASH) &&
				t[i + 4].type == TOKEN_SEMICOLON)
			{
				// return a + b;
				JechASTNode *left = _JechAST_CreateNode(
					t[i + 1].type == TOKEN_IDENTIFIER ? JECH_AST_IDENTIFIER : JECH_AST_NUMBER_LITERAL,
					t[i + 1].value, NULL, t[i + 1].type);
				JechASTNode *right = _JechAST_CreateNode(
					t[i + 3].type == TOKEN_IDENTIFIER ? JECH_AST_IDENTIFIER : JECH_AST_NUMBER_LITERAL,
					t[i + 3].value, NULL, t[i + 3].type);
				JechASTNode *binop = _JechAST_CreateNode(JECH_AST_BIN_OP, NULL, NULL, t[i + 2].type);
				binop->left = left;
				binop->right = right;
				binop->op = t[i + 2].type;

				JechASTNode *node = _JechAST_CreateNode(JECH_AST_RETURN, NULL, NULL, TOKEN_UNKNOWN);
				node->left = binop;
				roots[count++] = node;
				i += 5;
				continue;
			}
			else
			{
				report_error(ERROR_PARSER, "Invalid return statement", t[i].line, t[i].column);
				break;
			}
		}

		// function call: greet("World");
		if ((i + 1) < tokens->count && t[i].type == TOKEN_IDENTIFIER && t[i + 1].type == TOKEN_LPAREN)
		{
			int remaining = tokens->count - i;
			int consumed = 0;
			JechASTNode *node = parse_function_call(&t[i], remaining, &consumed);
			if (node)
			{
				roots[count++] = node;
				i += consumed;
				continue;
			}
			else
				break;
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
			if (t[i].type == TOKEN_IDENTIFIER)
			{
				char msg[128];
				snprintf(msg, sizeof(msg), "Unknown expression or statement: '%s'. Did you mean to call it as a function or assign a value?", t[i].value);
				report_error(ERROR_PARSER, msg, t[i].line, t[i].column);
			}
			else
			{
				report_error(ERROR_PARSER, "Unexpected token or invalid statement", t[i].line, t[i].column);
			}
			break;
		}
	}

	*out_count = count;
	return roots;
}