

#ifndef VM_H
#define VM_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_STACK_SIZE 254

#define INITIAL_MAX_OBJECTS 1024

typedef enum {
    ObjInt,
    ObjPair
} ObjectType;

typedef struct sObject {
    ObjectType type;

    bool marked;

    struct sObject* nextObject;

    union {
        int value;

        struct {
            struct sObject* head;
            struct sObject* tail;
        };
    };
} Object;

typedef struct {

    Object* stack[MAX_STACK_SIZE];

    int stackPos;

    int numObjects;

    int maxObjects;

    Object* firstObject;

} VM;

void assert(bool condition, const char* message);

VM* newVM();

void freeVM(VM* vm);

void dumpVMState(VM* vm);

// Returns a string representation of an object. 
const char* objToString(Object* obj);

void pushStack(VM* vm, Object* obj);

Object* popStack(VM* vm);

Object* newObject(VM* vm, ObjectType type);

void pushInt(VM* vm, int value);

void pushPair(VM* vm);

void mark(VM* vm, Object* obj);

void markAll(VM* vm);

void sweep(VM* vm);

void gc(VM* vm);

#endif
