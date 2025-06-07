// #include <stdio.h>
// #include "core/bytecode.h"
// #include "debug/debug_bytecode.h"
// #include "utils/token_utils.h"

// void debug_print_bytecode(const Bytecode *bc)
// {
//     printf("--- Bytecode ---\n");
//     for (int i = 0; i < bc->count; i++)
//     {
//         Instruction inst = bc->instructions[i];
//         switch (inst.op)
//         {
//         case OP_SAY:
//             printf("[%d] OP_SAY %s (%s)\n", i, inst.operand, token_type_to_str(inst.token_type));
//             break;
//         case OP_KEEP:
//             printf("[%d] OP_KEEP %s = %s (%s)\n", i, inst.name, inst.operand, token_type_to_str(inst.token_type));
//             break;
//         case OP_END:
//             printf("[%d] OP_END\n", i);
//             break;
//         }
//     }
//     printf("\n");
// }