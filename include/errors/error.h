#ifndef JECH_ERROR_H
#define JECH_ERROR_H

#include <stdio.h>

typedef enum
{
    SYNTAX_ERROR,
    ERROR_PARSER,
    ERROR_RUNTIME
} JechErrorType;

void report_error(JechErrorType type, const char *message, int line, int col);
void print_error_header(JechErrorType type);
void report_syntax_error(const char *message, int line, int column);
void report_runtime_error(const char *message, int line, int column);

#endif
