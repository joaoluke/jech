#ifndef JECH_ERRORS_H
#define JECH_ERRORS_H

#include "core/lexer.h"

void check_lexical_errors(const TokenList *tokens, const char *source);

#endif
