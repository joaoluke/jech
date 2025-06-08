#ifndef DEBUG_PARSER_H
#define DEBUG_PARSER_H

#include "core/ast.h"

/** * Prints the parser output in a human-readable format.
 * This function iterates through the AST roots and prints each instruction
 * with its type, name, and value.
 *
 * @param roots Array of root nodes of the AST.
 * @param count Number of root nodes in the AST.
 */
void debug_print_parser(JechASTNode **roots, int count);

#endif
