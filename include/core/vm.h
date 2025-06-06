#ifndef VM_H
#define VM_H

#include "bytecode.h"

#define MAX_STRING 256
#define MAX_VARS 100

/**
 * Variable representation in memory
 */
typedef struct
{
    char name[MAX_STRING];
    char value[MAX_STRING];
} Variable;

/**
 * Global variable storage
 */
extern Variable variables[MAX_VARS];
extern int var_count;

/**
 * Runs the bytecode using the JECH virtual machine
 */
void execute(Bytecode bc);

/**
 * Gets the value of a variable by name
 */
const char *get_variable(const char *name);

/**
 * Sets or updates a variable's value
 */
void set_variable(const char *name, const char *value);

#endif
