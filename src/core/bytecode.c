#include <string.h>
#include <stdio.h>
#include "core/bytecode.h"

// Helper function to compile the `say` command
void compile_say(Bytecode *bc, ASTNode node)
{
	Instruction *inst = &bc->instructions[bc->count++];
	inst->op = OP_SAY;
	strncpy(inst->operand, node.value, sizeof(inst->operand));
	inst->token_type = node.token_type;
}

// Helper function to compile the `keep` command
void compile_keep(Bytecode *bc, ASTNode node)
{
	Instruction *inst = &bc->instructions[bc->count++];
	inst->op = OP_KEEP;
	strncpy(inst->name, node.name, sizeof(inst->name));
	strncpy(inst->operand, node.value, sizeof(inst->operand));
	inst->token_type = node.token_type;
}

// Main compilation function: convert AST to bytecode
Bytecode compile_all(ASTList ast)
{
	Bytecode bc;
	bc.count = 0;

	for (int i = 0; i < ast.count; i++)
	{
		if (bc.count >= 128)
		{
			fprintf(stderr, "Bytecode overflow: too many instructions.\n");
			break;
		}

		ASTNode node = ast.nodes[i];

		switch (node.type)
		{
		case AST_SAY:
			compile_say(&bc, node);
			break;
		case AST_KEEP:
			compile_keep(&bc, node);
			break;
		default:
			fprintf(stderr, "Unknown AST node.\n");
			break;
		}
	}

	// Final instruction indicating the end of the bytecode
	bc.instructions[bc.count].op = OP_END;
	bc.count++;

	return bc;
}
