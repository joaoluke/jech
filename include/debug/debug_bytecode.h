#ifndef DEBUG_BYTECODE_H
#define DEBUG_BYTECODE_H

#include "core/bytecode.h"

/**
 * Prints the bytecode instructions in a human-readable format.
 * This function iterates through the bytecode and prints each instruction
 * with its operation, operand, and token type.
 *
 * @param bc Pointer to the Bytecode structure containing the instructions.
 */
void debug_print_bytecode(const Bytecode *bc);

#endif
