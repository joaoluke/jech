#ifndef BYTECODE_DEBUG_H
#define BYTECODE_DEBUG_H

#include "core/bytecode.h"

/**
 * Prints all compiled bytecode instructions for inspection.
 */
void debug_print_bytecode(const Bytecode *bc);

#endif