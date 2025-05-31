#include <string.h>
#include "bytecode.h"

Bytecode compile_all(ASTList ast)
{
    Bytecode bc;
    bc.count = 0;

    for (int i = 0; i < ast.count; i++)
    {
        ASTNode node = ast.nodes[i];
        if (node.type == AST_SAY)
        {
            bc.instructions[bc.count].op = OP_SAY;
            strncpy(bc.instructions[bc.count].operand, node.value, sizeof(bc.instructions[bc.count].operand));
            bc.count++;
        }
    }

    bc.instructions[bc.count].op = OP_END;
    bc.count++;

    return bc;
}
