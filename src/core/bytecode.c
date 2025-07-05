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
 * Currently only supports `say` actions for the true condition
 */
static void compile_when(Bytecode *bc, const JechASTNode *node)
{
	bool is_true = false;

	const JechASTNode *condition = node->left;

	printf("[DEBUG] compile_when: condition type = %d\n", condition->type);

	switch (condition->type)
	{
	case JECH_AST_BOOL_LITERAL:
		is_true = (strcmp(condition->value, "true") == 0);
		break;

	case JECH_AST_IDENTIFIER:
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

	case JECH_AST_BIN_OP:
	{
		const char *var_name = condition->left->value;
		const char *rhs = condition->right->value;

		int var_value = 0;
		int found = 0;

		for (int i = 0; i < bc->count; i++)
		{
			Instruction inst = bc->instructions[i];
			if (inst.op == OP_KEEP && strcmp(inst.name, var_name) == 0)
			{
				var_value = atoi(inst.operand);
				found = 1;
				break;
			}
		}

		if (!found)
		{
			fprintf(stderr, "Bytecode Error: Variable '%s' not found for 'when'\n", var_name);
			exit(1);
		}

		int rhs_value = atoi(rhs);

		switch (condition->token_type)
		{
		case TOKEN_GT:
			is_true = (var_value > rhs_value);
			break;
		case TOKEN_LT:
			is_true = (var_value < rhs_value);
			break;
		case TOKEN_EQEQ:
			is_true = (var_value == rhs_value);
			break;
		default:
			fprintf(stderr, "Bytecode warning: unsupported binary operator in when condition.\n");
			break;
		}
		break;
	}

	default:
		fprintf(stderr, "Bytecode warning: unsupported when condition type: %d\n", condition->type);
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
