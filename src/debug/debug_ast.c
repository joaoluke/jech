#include <stdio.h>
#include "core/ast.h"
#include "debug/debug_ast.h"

void debug_print_ast(JechASTNode **roots, int count)
{
    printf("\n--- AST Tree ---\n");
    for (int i = 0; i < count; i++)
    {
        _JechAST_Print(roots[i], 0);
    }
    printf("\n");
}
