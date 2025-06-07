#ifndef MAIN_HELPERS_H
#define MAIN_HELPERS_H

#include "core/tokenizer.h"
#include "core/parser.h"
#include "core/bytecode.h"

/**
 * Check if the file name has a .jc extension
 */
int is_valid_extension(const char *filename);

/**
 * Handles file read error and displays appropriate message
 */
char *load_source_file(const char *filename);

/**
 * Executes the complete JECH language pipeline
 */
void run_pipeline(const char *source);

#endif
