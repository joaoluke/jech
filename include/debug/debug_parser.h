#ifndef PARSER_DEBUG_H
#define PARSER_DEBUG_H

#include "core/parser.h"

/**
 * Prints all nodes of the parsed abstract syntax tree.
 */
void debug_print_ast(const ASTList *ast);

#endif