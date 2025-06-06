#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/main_helpers.h"
#include "utils/read_file.h"
#include "core/lexer.h"
#include "core/parser.h"
#include "core/bytecode.h"
#include "core/vm.h"
#include "errors.h"
#include "config.h"

// Debug
#include "debug/debug_lexer.h"
#include "debug/debug_parser.h"
#include "debug/debug_bytecode.h"
#include "debug/debug_vm.h"

int is_valid_extension(const char *filename)
{
    int len = strlen(filename);
    return len >= 4 && strcmp(&filename[len - 3], ".jc") == 0;
}

char *load_source_file(const char *filename)
{
    char *source = read_file_content(filename);
    if (!source)
    {
        printf("Could not read file: %s\n", filename);
        exit(1);
    }
    return source;
}

void run_pipeline(const char *source)
{
    TokenList tokens = lex(source);
    check_lexical_errors(&tokens, source);

    ASTList ast = parse_all(&tokens);

    if (JECH_DEBUG)
    {
        debug_print_tokens(&tokens);
        debug_print_ast(&ast);
    }

    if (ast.count == 0)
    {
        printf("Parser error: No valid instructions found\n");
        return;
    }

    Bytecode bytecode = compile_all(ast);

    if (JECH_DEBUG)
    {
        debug_print_bytecode(&bytecode);
    }

    execute(bytecode);

    if (JECH_DEBUG)
    {
        debug_print_variables();
    }
}
