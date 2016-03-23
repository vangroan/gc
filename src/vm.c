

#include "vm.h"

void assert(bool condition, const char* message) {
    if (!condition) { 
        fprintf(stderr, message);
        exit(1);
    }
}


VM* newVM() {
    VM* vm = (VM*)malloc(sizeof(VM));

    vm->stackPos = 0;

    vm->numObjects = 0;

    vm->maxObjects = INITIAL_MAX_OBJECTS;

    vm->firstObject = NULL;

    return vm;
}


void freeVM(VM* vm) {
    free(vm);
}


void dumpVMState(VM* vm) {
    printf("Num Objects: %d\n", vm->numObjects);
    printf("Max Objects: %d\n", vm->maxObjects);

    for (int s = 0; s < vm->stackPos; s++) {
        printf("[0x%02x] %s\n", s, objToString(vm->stack[s]));
    }
}


const char* objToString(Object* obj) {
    switch(obj->type) {
        case ObjInt:
            return "Int";
        case ObjPair:
            return "Pair";
        default: 
            return "Unknown";
    }
}


void pushStack(VM* vm, Object* obj) {
    assert(vm->stackPos < MAX_STACK_SIZE, "Stack overflow");

    vm->stack[vm->stackPos++] = obj;
}


Object* popStack(VM* vm) {
    assert(vm->stackPos > 0, "Stack underflow");

    return vm->stack[--vm->stackPos];
}


Object* newObject(VM* vm, ObjectType type) {
    Object* obj = (Object*)malloc(sizeof(Object));
    
    obj->type = type;

    obj->marked = 0;

    if (vm->firstObject == NULL) {
        vm->firstObject = obj;
    } else {
        obj->nextObject = vm->firstObject;
        vm->firstObject = obj;
    }

    vm->numObjects++;

    return obj;
}


void pushInt(VM* vm, int value) {
    Object* obj = newObject(vm, ObjInt);
    obj->value = value;
    pushStack(vm, obj);
}


void pushPair(VM* vm) {
    Object* obj = newObject(vm, ObjPair);
    obj->head = popStack(vm);
    obj->tail = popStack(vm);
}


void mark(VM* vm, Object* obj) {
    if (obj->marked) { return; }

    obj->marked = 1;

    if (obj->type == ObjPair) {
        mark(vm, obj->head);
        mark(vm, obj->tail);
    }
}

void markAll(VM* vm) {
    for (int i = 0; i < vm->stackPos; i++) {
        mark(vm, vm->stack[i]);
    }
}


void sweep(VM* vm) {
    // TODO
}

void gc(VM* vm) {
    markAll(vm);
    sweep(vm);
}
