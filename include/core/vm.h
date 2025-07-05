#ifndef JECH_VM_H
#define JECH_VM_H

#include "bytecode.h"

/**
 * Sets or updates a variable in the VM runtime environment.
 * If the variable already exists, its value will be overwritten.
 */
void _JechVM_SetVariable(const char *name, const char *value);

/**
 * Retrieves the value of a variable from the VM runtime environment.
 * Returns NULL if the variable does not exist.
 */
const char *_JechVM_GetVariable(const char *name);

/**
 * Executes the bytecode instructions
 */
void _JechVM_Execute(const Bytecode *bc);

#endif
