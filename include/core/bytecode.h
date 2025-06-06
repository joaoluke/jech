#ifndef BYTECODE_H
#define BYTECODE_H

#include "parser.h"

/**
 * Enum for bytecode operation types
 */
typedef enum
{
	OP_SAY,
	OP_KEEP,
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
	TokenType token_type;
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
Bytecode compile_all(ASTList ast);

#endif
