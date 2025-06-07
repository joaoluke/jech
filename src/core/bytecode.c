#include <string.h>
#include <stdio.h>
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
		default:
			fprintf(stderr, "Unknown AST node.\n");
			break;
		}
	}

	bc.instructions[bc.count++].op = OP_END;
	return bc;
}
