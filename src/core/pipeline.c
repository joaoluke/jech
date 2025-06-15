#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/read_file.h"
#include "core/tokenizer.h"
#include "core/pipeline.h"
#include "core/parser/parser.h"
#include "core/bytecode.h"
#include "core/vm.h"
#include "core/ast.h"
#include "config.h"

// Debug
#include "debug/debug_tokenizer.h"
#include "debug/debug_parser.h"
#include "debug/debug_ast.h"
#include "debug/debug_bytecode.h"
#include "debug/debug_vm.h"

/**
 * Checks if the file has a valid .jc extension
 * Returns 1 if valid, 0 otherwise
 */
int is_valid_extension(const char *filename)
{
    int len = strlen(filename);
    return len >= 4 && strcmp(&filename[len - 3], ".jc") == 0;
}

/**
 * Reads the source file content into a string
 * Returns NULL if the file cannot be read
 */
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

/**
 * Runs the entire pipeline: lexing, parsing, bytecode compilation, and execution
 * Prints debug information if JECH_DEBUG is enabled
 */
void run_pipeline(const char *source)
{
    JechTokenList tokens = _JechTokenizer_Lex(source);

    int ast_count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &ast_count);

    if (JECH_DEBUG)
    {
        debug_print_tokens(&tokens);
        debug_print_parser(roots, ast_count);
        debug_print_ast(roots, ast_count);
    }

    Bytecode bytecode = _JechBytecode_CompileAll(roots, ast_count);

    if (JECH_DEBUG)
    {
        debug_print_bytecode(&bytecode);
    }

    _JechVM_Execute(&bytecode);

    if (JECH_DEBUG)
    {
        debug_print_variables();
    }

    for (int i = 0; i < ast_count; i++)
    {
        _JechAST_Free(roots[i]);
    }
}