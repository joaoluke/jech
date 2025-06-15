#ifndef PARSER_KEEP_H
#define PARSER_KEEP_H

#include "tokenizer.h"
#include "ast.h"

JechASTNode *parse_keep(const JechToken *t, int remaining_tokens);

#endif
