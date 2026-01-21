#ifndef JECH_PARSER_FUNCTION_H
#define JECH_PARSER_FUNCTION_H

#include "core/ast.h"
#include "core/tokenizer.h"

JechASTNode *parse_function_decl(const JechToken *t, int remaining_tokens, int *out_consumed);
JechASTNode *parse_function_call(const JechToken *t, int remaining_tokens, int *out_consumed);

#endif
