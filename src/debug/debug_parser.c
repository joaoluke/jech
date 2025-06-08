#include <stdio.h>
#include "debug/debug_parser.h"
#include "core/ast.h"

void debug_print_parser(JechASTNode **roots, int count)
{
    printf("\n--- Parser Output (AST Roots) ---\n");

    for (int i = 0; i < count; i++)
    {
        JechASTNode *node = roots[i];

        const char *kind = (node->type == JECH_AST_SAY) ? "say" : (node->type == JECH_AST_KEEP) ? "keep"
                                                                                                : "unknown";

        if (node->type == JECH_AST_SAY)
        {
            printf("Instruction: %s(\"%s\")\n", kind, node->value);
        }
        else if (node->type == JECH_AST_KEEP)
        {
            printf("Instruction: %s %s = \"%s\"\n", kind, node->name, node->value);
        }
        else
        {
            printf("Instruction: unknown → name=%s, value=%s\n", node->name, node->value);
        }
    }

    printf("\n");
}
