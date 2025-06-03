#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "vm.h"

void execute(Bytecode bc)
{
	for (int i = 0; i < bc.count; i++)
	{
		Instruction inst = bc.instructions[i];

		if (inst.op == OP_SAY)
		{
			switch (inst.token_type)
			{
			case TOKEN_STRING:
				printf("%s\n", inst.operand);
				break;
			case TOKEN_NUMBER:
				printf("%d\n", atoi(inst.operand));
				break;
			case TOKEN_BOOL:
				if (strcmp(inst.operand, "true") == 0)
					printf("true\n");
				else
					printf("false\n");
				break;
			default:
				printf("Error: unknown value type for say()\n");
			}
		}
		else if (inst.op == OP_END)
		{
			break;
		}
	}
}
