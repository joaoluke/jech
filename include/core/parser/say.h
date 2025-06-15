#pragma once
#include "core/ast.h"
#include "core/tokenizer.h"

JechASTNode *parse_say(const JechToken *t, int remaining_tokens);
