
#include <stdio.h>
#include "vm.h"


void demo(VM* vm) {
    printf("\n");
    printf("Pushing two integers onto the stack.\n");
    pushInt(vm, 3);
    pushInt(vm, 5);

    dumpVMState(vm);

    printf("\n");
    printf("Pushing a pair onto the stack.\n");
    pushPair(vm);

    dumpVMState(vm);
}


int main() {
    VM* vm = newVM();

    demo(vm);

    freeVM(vm);
    return 0;
}
