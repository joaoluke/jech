#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils/main_helpers.h"
#include "utils/read_file.h"
#include "core/tokenizer.h"
#include "core/parser.h"
#include "core/bytecode.h"
#include "core/vm.h"
#include "core/ast.h"
#include "errors.h"
#include "config.h"

// Debug
// #include "debug/debug_lexer.h"
// #include "debug/debug_parser.h"
// #include "debug/debug_bytecode.h"
// #include "debug/debug_vm.h"

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
    JechTokenList tokens = _JechTokenizer_Lex(source);
    check_lexical_errors(&tokens, source);

    int ast_count = 0;
    JechASTNode **roots = _JechParser_ParseAll(&tokens, &ast_count);

    // if (JECH_DEBUG)
    // {
    //     debug_print_tokens(&tokens);
    //     for (int i = 0; i < ast_count; i++)
    //     {
    //         printf("AST %d:\n", i);
    //         _JechAST_Print(roots[i], 0);
    //     }
    // }

    if (ast_count == 0)
    {
        printf("Parser error: No valid instructions found\n");
        return;
    }

    Bytecode bytecode = _JechBytecode_CompileAll(roots, ast_count);

    // if (JECH_DEBUG)
    // {
    //     debug_print_bytecode(&bytecode);
    // }

    _JechVM_Execute(&bytecode);

    // if (JECH_DEBUG)
    // {
    //     debug_print_variables();
    // }

    for (int i = 0; i < ast_count; i++)
    {
        _JechAST_Free(roots[i]);
    }
}
