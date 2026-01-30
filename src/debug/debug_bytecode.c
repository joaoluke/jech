#include <stdio.h>
#include "core/bytecode.h"
#include "debug/debug_bytecode.h"
#include "utils/token_utils.h"

void debug_print_bytecode(const Bytecode *bc)
{
    printf("\n--- Bytecode ---\n");
    for (int i = 0; i < bc->count; i++)
    {
        Instruction inst = bc->instructions[i];
        const char *op_name = "";
        switch (inst.op)
        {
        case OP_SAY:
            op_name = "OP_SAY";
            break;
        case OP_KEEP:
            op_name = "OP_KEEP";
            break;
        case OP_BIN_OP:
            op_name = "OP_BIN_OP";
            break;
        case OP_END:
            op_name = "OP_END";
            break;
        default:
            op_name = "OP_UNKNOWN";
            break;
        }

        printf("Instruction: %s", op_name);

        if (inst.op == OP_SAY)
        {
            printf(" \"%s\"", inst.operand);
        }
        else if (inst.op == OP_KEEP)
        {
            printf(" %s = \"%s\"", inst.name, inst.operand);
        }
        else if (inst.op == OP_BIN_OP)
        {
            printf(" %s = %s %c %s", inst.name, inst.operand, 
                   inst.bin_op == TOKEN_PLUS ? '+' : 
                   inst.bin_op == TOKEN_MINUS ? '-' : 
                   inst.bin_op == TOKEN_STAR ? '*' : '/', 
                   inst.operand_right);
        }

        printf(" [type: %s]\n", token_type_to_str(inst.token_type));
    }
    printf("\n");
}
