
#include <stdio.h>
#include "vm.h"


void demo(VM* vm) {
    printf("\n");
    printf("Pushing two integers onto the stack\n");
    pushInt(vm, 3);
    pushInt(vm, 5);

    dumpVMState(vm);

    printf("\n");
    printf("Pushing a pair onto the stack\n");
    pushPair(vm);

    dumpVMState(vm);

    printf("\n");
    printf("Collect garbage\n");
    gc(vm);

    dumpVMState(vm);

    printf("\n");
    printf("Popping the pair off the stack, and collection garbage again\n");
    popStack(vm);
    gc(vm);

    dumpVMState(vm);
}


int main() {
    VM* vm = newVM();

    demo(vm);

    freeVM(vm);
    return 0;
}
