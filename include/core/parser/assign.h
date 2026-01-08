#ifndef JECH_PARSER_ASSIGN_H
#define JECH_PARSER_ASSIGN_H

#include "core/tokenizer.h"
#include "core/ast.h"

JechASTNode *parse_assign(const JechToken *t, int remaining_tokens, int *out_consumed);

#endif
