#include <stdio.h>
#include "core/vm.h"
#include "debug/debug_vm.h"

void debug_print_variables()
{
    extern Variable variables[];
    extern int var_count;

    printf("\n--- Variables ---\n");
    for (int i = 0; i < var_count; i++)
    {
        printf("%s = %s\n", variables[i].name, variables[i].value);
    }
    printf("\n");
}