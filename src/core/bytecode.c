#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "core/bytecode.h"
#include "core/ast.h"
#include "core/vm.h"

/**
 * Helper function to compile the `say` command
 */
static void compile_say(Bytecode *bc, const JechASTNode *node)
{
	Instruction *inst = &bc->instructions[bc->count++];
	memset(inst, 0, sizeof(Instruction));
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
	memset(inst, 0, sizeof(Instruction));
	inst->op = OP_KEEP;
	strncpy(inst->name, node->name, sizeof(inst->name));
	strncpy(inst->operand, node->value, sizeof(inst->operand));
	inst->token_type = node->token_type;
}

/**
 * Compiles a `when` block, which contains a condition and an action
 * Supports both binary conditions (x > 10) and boolean conditions (true/false/identifier)
 * Now with else branch support
 */
static void compile_when(Bytecode *bc, const JechASTNode *node)
{
	const JechASTNode *condition = node->left;

	if (condition->type == JECH_AST_BIN_OP)
	{
		// Binary condition: when (x > 10) { ... } or when (x == "hello") { ... }
		Instruction *inst = &bc->instructions[bc->count++];
		memset(inst, 0, sizeof(Instruction));
		inst->op = OP_WHEN;

		strncpy(inst->name, condition->left->value, sizeof(inst->name));
		inst->bin_op = condition->token_type; // ==, <, >
		strncpy(inst->operand, condition->right->value, sizeof(inst->operand));
		inst->cmp_operand_type = condition->right->token_type; // STRING, NUMBER, IDENTIFIER

		strncpy(inst->operand_right, node->right->value, sizeof(inst->operand_right));
		inst->token_type = node->right->token_type;

		// Handle else branch for binary conditions
		if (node->else_branch)
		{
			inst->has_else = 1;
			strncpy(inst->else_operand, node->else_branch->value, sizeof(inst->else_operand));
			inst->else_token_type = node->else_branch->token_type;
		}
	}
	else
	{
		// Boolean/identifier condition: when (name) { ... } else { ... }
		Instruction *inst = &bc->instructions[bc->count++];
		memset(inst, 0, sizeof(Instruction));
		inst->op = OP_WHEN_BOOL;

		// Store condition (variable name or literal "true"/"false")
		strncpy(inst->name, condition->value, sizeof(inst->name));
		inst->bin_op = condition->type == JECH_AST_BOOL_LITERAL ? TOKEN_BOOL : TOKEN_IDENTIFIER;

		// Store then branch (say value)
		if (node->right)
		{
			strncpy(inst->operand, node->right->value, sizeof(inst->operand));
			inst->token_type = node->right->token_type;
		}

		// Store else branch if present
		if (node->else_branch)
		{
			inst->has_else = 1;
			strncpy(inst->else_operand, node->else_branch->value, sizeof(inst->else_operand));
			inst->else_token_type = node->else_branch->token_type;
		}
	}
}

/**
 * Helper function to compile the `assign` command
 */
static void compile_assign(Bytecode *bc, const JechASTNode *node)
{
	if (node->left && node->left->type == JECH_AST_BIN_OP)
	{
		const JechASTNode *bin = node->left;

		Instruction *inst = &bc->instructions[bc->count++];
		memset(inst, 0, sizeof(Instruction));
		inst->op = OP_BIN_OP;

		strncpy(inst->name, node->name, sizeof(inst->name));

		if (bin->left->type == JECH_AST_IDENTIFIER)
		{
			strncpy(inst->operand, bin->left->name, sizeof(inst->operand));
		}
		else
		{
			strncpy(inst->operand, bin->left->value, sizeof(inst->operand));
		}

		if (bin->right->type == JECH_AST_IDENTIFIER)
		{
			strncpy(inst->operand_right, bin->right->name, sizeof(inst->operand_right));
		}
		else
		{
			strncpy(inst->operand_right, bin->right->value, sizeof(inst->operand_right));
		}

		inst->bin_op = bin->token_type;
		inst->token_type = bin->right->token_type;
	}
	else
	{
		Instruction *inst = &bc->instructions[bc->count++];
		memset(inst, 0, sizeof(Instruction));
		inst->op = OP_ASSIGN;
		strncpy(inst->name, node->name, sizeof(inst->name));
		strncpy(inst->operand, node->value, sizeof(inst->operand));
		inst->token_type = node->token_type;
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
		case JECH_AST_ASSIGN:
			compile_assign(&bc, node);
			break;
		default:
			fprintf(stderr, "Unknown AST node.\n");
			break;
		}
	}

	bc.instructions[bc.count++].op = OP_END;
	return bc;
}
