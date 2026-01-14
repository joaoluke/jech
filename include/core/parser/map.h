#ifndef JECH_PARSER_MAP_H
#define JECH_PARSER_MAP_H

#include "core/ast.h"
#include "core/tokenizer.h"

/**
 * Parses array.map() syntax
 * Example: keep doubled = numbers.map(* 2);
 */
JechASTNode *parse_map(const JechToken *t, int remaining_tokens, int *out_consumed);

#endif
