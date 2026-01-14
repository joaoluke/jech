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
 * Helper function to compile say with array indexing: say(arr[0]);
 */
static void compile_say_index(Bytecode *bc, const JechASTNode *node)
{
	Instruction *inst = &bc->instructions[bc->count++];
	memset(inst, 0, sizeof(Instruction));
	inst->op = OP_SAY_INDEX;
	strncpy(inst->name, node->value, sizeof(inst->name));
	if (node->left)
	{
		strncpy(inst->operand, node->left->value, sizeof(inst->operand));
	}
}

/**
 * Helper function to compile map operation
 */
static void compile_map(Bytecode *bc, const JechASTNode *node, const char *result_name)
{
	Instruction *inst = &bc->instructions[bc->count++];
	memset(inst, 0, sizeof(Instruction));
	inst->op = OP_MAP;
	
	// name = result array name
	strncpy(inst->name, result_name, sizeof(inst->name));
	
	// operand = source array name
	strncpy(inst->operand, node->value, sizeof(inst->operand));
	
	// operand_right = operation value
	if (node->left)
	{
		strncpy(inst->operand_right, node->left->value, sizeof(inst->operand_right));
		inst->bin_op = node->left->op; // operator type (*, +, -, /)
	}
}

/**
 * Helper function to compile the `keep` command
 */
static void compile_keep(Bytecode *bc, const JechASTNode *node)
{
	if (node->left && node->left->type == JECH_AST_MAP)
	{
		// Map operation: keep doubled = numbers.map(* 2);
		compile_map(bc, node->left, node->name);
	}
	else if (node->token_type == TOKEN_LBRACKET && node->left && node->left->type == JECH_AST_ARRAY_LITERAL)
	{
		// Array literal: keep arr = [1, 2, 3];
		Instruction *inst = &bc->instructions[bc->count++];
		memset(inst, 0, sizeof(Instruction));
		inst->op = OP_ARRAY_NEW;
		strncpy(inst->name, node->name, sizeof(inst->name));

		// Iterate through array elements and push them
		JechASTNode *elem = node->left->left;
		while (elem)
		{
			Instruction *push_inst = &bc->instructions[bc->count++];
			memset(push_inst, 0, sizeof(Instruction));
			push_inst->op = OP_ARRAY_PUSH;
			strncpy(push_inst->name, node->name, sizeof(push_inst->name));
			strncpy(push_inst->operand, elem->value, sizeof(push_inst->operand));
			push_inst->token_type = elem->token_type;
			elem = elem->right;
		}
	}
	else
	{
		// Scalar keep
		Instruction *inst = &bc->instructions[bc->count++];
		memset(inst, 0, sizeof(Instruction));
		inst->op = OP_KEEP;
		strncpy(inst->name, node->name, sizeof(inst->name));
		strncpy(inst->operand, node->value, sizeof(inst->operand));
		inst->token_type = node->token_type;
	}
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
		case JECH_AST_SAY_INDEX:
			compile_say_index(&bc, node);
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
		case JECH_AST_MAP:
			// Standalone map: modify array in-place
			compile_map(&bc, node, node->value);
			break;
		default:
			fprintf(stderr, "Unknown AST node.\n");
			break;
		}
	}

	bc.instructions[bc.count++].op = OP_END;
	return bc;
}
