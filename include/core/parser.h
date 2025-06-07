#ifndef PARSER_H
#define PARSER_H

#include "ast.h"

/**
 * Convert token list into an Abstract Syntax Tree (AST).
 */
JechASTNode **_JechParser_ParseAll(const JechTokenList *tokens, int *out_count);

#endif
