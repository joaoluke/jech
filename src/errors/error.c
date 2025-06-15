#include "errors/error.h"

void print_error_header(JechErrorType type)
{
    switch (type)
    {
    case SYNTAX_ERROR:
        fprintf(stderr, "\x1b[1;31m[SyntaxError]\x1b[0m ");
        break;
    case ERROR_PARSER:
        fprintf(stderr, "\x1b[1;35m[Parser Error]\x1b[0m ");
        break;
    case ERROR_RUNTIME:
        fprintf(stderr, "\x1b[1;33m[Runtime Error]\x1b[0m ");
        break;
    }
}

void report_error(JechErrorType type, const char *message, int line, int col)
{
    print_error_header(type);
    fprintf(stderr, "at line %d, col %d: %s\n", line, col, message);
}

void report_parser_error(const char *message, int line, int column)
{
    print_error_header(SYNTAX_ERROR);
    fprintf(stderr, "at line %d, col %d: %s\n", line, column, message);
}
