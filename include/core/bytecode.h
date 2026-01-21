#ifndef JECH_BYTECODE_H
#define JECH_BYTECODE_H
#include "ast.h"

/**
 * Enum for bytecode operation types
 */
typedef enum
{
	OP_SAY,
	OP_SAY_INDEX,
	OP_ARRAY_NEW,
	OP_ARRAY_PUSH,
	OP_KEEP,
	OP_ASSIGN,
	OP_INDEX_GET,
	OP_BIN_OP,
	OP_WHEN,
	OP_WHEN_BOOL, // for boolean/identifier conditions with else support
	OP_MAP,
	OP_FUNCTION_DECL,
	OP_FUNCTION_CALL,
	OP_END
} OpCode;

/**
 * Instruction structure used in bytecode
 */
typedef struct
{
	OpCode op;						// operation type: OP_SAY, OP_ASSIGN, etc.
	char name[MAX_STRING];			// target variable name (for assign) or condition var
	char operand[MAX_STRING];		// left operand or single value (then branch)
	char operand_right[MAX_STRING]; // right operand (for BIN_OP) or say value in when
	char else_operand[MAX_STRING];  // else branch value (for WHEN_BOOL)
	JechTokenType bin_op;			// BIN_OP operator (+, -, ==, <, >)
	JechTokenType token_type;		// then value type (say)
	JechTokenType cmp_operand_type; // comparison operand type (STRING, NUMBER, IDENTIFIER)
	JechTokenType else_token_type;  // else value type
	int has_else;                   // flag for else branch
	char params[8][MAX_STRING];     // function parameters (for FUNCTION_DECL)
	int param_count;                // number of parameters
	char args[8][MAX_STRING];       // function arguments (for FUNCTION_CALL)
	JechTokenType arg_types[8];     // argument types
	int arg_count;                  // number of arguments
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