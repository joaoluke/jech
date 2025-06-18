#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "core/bytecode.h"
#include "core/ast.h"

/**
 * Helper function to compile the `say` command
 */
static void compile_say(Bytecode *bc, const JechASTNode *node)
{
	Instruction *inst = &bc->instructions[bc->count++];
	inst->op = OP_SAY;
	strncpy(inst->operand, node->value, sizeof(inst->operand));
	inst->token_type = node->token_type;
}

/**
 * Helper function to compile the `keep` command
 */
static void compile_keep(Bytecode *bc, const JechASTNode *node)
{
	Instruction *inst = &bc->instructions[bc->count++];
	inst->op = OP_KEEP;
	strncpy(inst->name, node->name, sizeof(inst->name));
	strncpy(inst->operand, node->value, sizeof(inst->operand));
	inst->token_type = node->token_type;
}

/**
 * Compiles a `when` block, which contains a condition and an action
 * Currently only supports `say` actions for the true condition
 */
static void compile_when(Bytecode *bc, const JechASTNode *node)
{
	bool is_true = false;

	const JechASTNode *condition = node->left;

	switch (condition->token_type)
	{
	case TOKEN_BOOL:
		is_true = (strcmp(condition->value, "true") == 0);
		break;

	case TOKEN_IDENTIFIER:
		for (int i = 0; i < bc->count; i++)
		{
			Instruction inst = bc->instructions[i];
			if (inst.op == OP_KEEP && strcmp(inst.name, condition->value) == 0)
			{
				is_true = (strcmp(inst.operand, "true") == 0);
				break;
			}
		}
		break;

	default:
		fprintf(stderr, "Bytecode warning: unsupported when condition type: %d\n", condition->token_type);
		break;
	}

	if (is_true && node->right != NULL)
	{
		switch (node->right->type)
		{
		case JECH_AST_SAY:
			compile_say(bc, node->right);
			break;

		case JECH_AST_KEEP:
			compile_keep(bc, node->right);
			break;

		default:
			fprintf(stderr, "Bytecode warning: unsupported when block content.\n");
			break;
		}
	}
}

/**
 * Main compilation function: convert AST to bytecode
 */
Bytecode _JechBytecode_CompileAll(JechASTNode **roots, int count)
{
	Bytecode bc;
	bc.count = 0;

	for (int i = 0; i < count; i++)
	{
		if (bc.count >= 128)
		{
			fprintf(stderr, "Bytecode overflow: too many instructions.\n");
			break;
		}

		JechASTNode *node = roots[i];
		switch (node->type)
		{
		case JECH_AST_SAY:
			compile_say(&bc, node);
			break;
		case JECH_AST_KEEP:
			compile_keep(&bc, node);
			break;
		case JECH_AST_WHEN:
			compile_when(&bc, node);
			break;
		default:
			fprintf(stderr, "Unknown AST node.\n");
			break;
		}
	}

	bc.instructions[bc.count++].op = OP_END;
	return bc;
}
