#ifndef JECH_BYTECODE_H
#define JECH_BYTECODE_H
#include "ast.h"

/**
 * Enum for bytecode operation types
 */
typedef enum
{
	OP_SAY,
	OP_KEEP,
	OP_ASSIGN,
	OP_BIN_OP,
	OP_WHEN,
	OP_END
} OpCode;

/**
 * Instruction structure used in bytecode
 */
typedef struct
{
	OpCode op;						// operation type: OP_SAY, OP_ASSIGN, etc.
	char name[MAX_STRING];			// target variable name (for assign)
	char operand[MAX_STRING];		// left operand or single value
	char operand_right[MAX_STRING]; // right operand (for BIN_OP)
	JechTokenType bin_op;			// BIN_OP operator (+, -, etc.)
	JechTokenType token_type;		// right value type
	int line;
	int column;
} Instruction;

/**
 * Bytecode structure containing an array of instructions
 */
typedef struct
{
	Instruction instructions[128];
	int count;
} Bytecode;

/**
 * Compiles the AST into bytecode
 */
Bytecode _JechBytecode_CompileAll(JechASTNode **roots, int count);

#endif