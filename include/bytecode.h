#ifndef BYTECODE_H
#define BYTECODE_H

#include "parser.h"

typedef enum
{
    OP_SAY,
    OP_END
} OpCode;

typedef struct
{
    OpCode op;
    char operand[256];
} Instruction;

typedef struct
{
    Instruction instructions[128];
    int count;
} Bytecode;

Bytecode compile_all(ASTList ast);

#endif
