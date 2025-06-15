#ifndef PARSER_WHEN_H
#define PARSER_WHEN_H

#include "core/ast.h"
#include "core/tokenizer.h"

JechASTNode *parse_when(const JechToken *t, int remaining_tokens);

#endif
