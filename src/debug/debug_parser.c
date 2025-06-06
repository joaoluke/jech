#include <stdio.h>
#include "core/parser.h"
#include "debug/debug_parser.h"
#include "utils/token_utils.h"

void debug_print_ast(const ASTList *ast)
{
    printf("--- AST ---\n");
    for (int i = 0; i < ast->count; i++)
    {
        ASTNode node = ast->nodes[i];
        switch (node.type)
        {
        case AST_SAY:
            printf("Node %d: SAY → \"%s\" (%s)\n", i, node.value, token_type_to_str(node.token_type));
            break;
        case AST_KEEP:
            printf("Node %d: KEEP → %s = \"%s\" (%s)\n", i, node.name, node.value, token_type_to_str(node.token_type));
            break;
        }
    }
    printf("\n");
}