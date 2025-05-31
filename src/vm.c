#include <stdio.h>
#include "vm.h"

void execute(Bytecode bc)
{
    for (int i = 0; i < bc.count; i++)
    {
        Instruction inst = bc.instructions[i];

        switch (inst.op)
        {
        case OP_SAY:
            printf("%s\n", inst.operand);
            break;
        case OP_END:
            return;
        default:
            printf("Unknown instruction\n");
            return;
        }
    }
}
