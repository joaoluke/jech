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
	OP_END
} OpCode;

/**
 * Instruction structure used in bytecode
 */
typedef struct
{
	OpCode op;
	char operand[MAX_STRING];
	char name[MAX_STRING];
	JechTokenType token_type;
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