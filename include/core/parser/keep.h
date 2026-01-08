#ifndef PARSER_KEEP_H
#define PARSER_KEEP_H

#include "core/tokenizer.h"
#include "core/ast.h"

JechASTNode *parse_keep(const JechToken *t, int remaining_tokens, int *out_consumed);

#endif
