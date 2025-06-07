#ifndef JECH_VM_H
#define JECH_VM_H

#include "bytecode.h"

/**
 * Executes the bytecode instructions
 */
void _JechVM_Execute(const Bytecode *bc);

#endif
