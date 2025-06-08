#ifndef DEBUG_AST_H
#define DEBUG_AST_H

#include "core/ast.h"

/**
 * Prints the abstract syntax tree (AST) in a human-readable format.
 * This function traverses the AST and prints each node with its type and value.
 *
 * @param roots Array of root nodes of the AST.
 * @param count Number of root nodes in the AST.
 */
void debug_print_ast(JechASTNode **roots, int count);

#endif
