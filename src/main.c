
#include <stdio.h>
#include "vm.h"


void demo(VM* vm) {
    pushInt(vm, 3);
    pushInt(vm, 5);
}


int main() {
    VM* vm = newVM();

    demo(vm);

    freeVM(vm);
    return 0;
}
