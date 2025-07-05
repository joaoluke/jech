#ifndef JECH_VM_H
#define JECH_VM_H

#include "bytecode.h"

const char *get_variable(const char *name);
void set_variable(const char *name, const char *value);
/**
 * Executes the bytecode instructions
 */
void _JechVM_Execute(const Bytecode *bc);

#endif
