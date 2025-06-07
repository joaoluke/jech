// #include <stdio.h>
// #include "core/ast.h"
// #include "debug/debug_parser.h"
// #include "utils/token_utils.h"

// void debug_print_ast(const JechASTList *ast)
// {
//     printf("--- AST ---\n");
//     for (int i = 0; i < ast->count; i++)
//     {
//         JechASTNode node = ast->nodes[i];
//         switch (node.type)
//         {
//         case JECH_AST_SAY:
//             printf("Node %d: SAY → \"%s\" (%s)\n", i, node.value, token_type_to_str(node.token_type));
//             break;
//         case JECH_AST_KEEP:
//             printf("Node %d: KEEP → %s = \"%s\" (%s)\n", i, node.name, node.value, token_type_to_str(node.token_type));
//             break;
//         }
//     }
//     printf("\n");
// }