#include <stdio.h>
#include "core/vm.h"
#include "debug/debug_vm.h"

extern void _debug_vm_dump_vars();

void debug_print_variables()
{
    printf("\n--- VM Variables ---\n");
    _debug_vm_dump_vars();
    printf("\n");
}
