//
// Created by Maxwell Conradt on 12/5/21.
//

#include <stdlib.h>

#include "memory.h"
#include "object.h"
#include "vm.h"

void *reallocate(void *pointer, size_t oldSize, size_t newSize) {
    if (newSize == 0) {
        free(pointer);
        return NULL;
    }

    void *result = realloc(pointer, newSize);
    if (result == NULL) exit(1);
    return result;
}

static void freeObject(Obj *object) {
    switch (object->type) {
        case OBJ_CLOSURE: {
            FREE(ObjClosure, object);
            ObjClosure *closure = (ObjClosure *) object;
            FREE_ARRAY(ObjUpvalue*, closure->upvalues, closure->upvalueCount);
            break;
        }
        case OBJ_FUNCTION: {
            ObjFunction *function = (ObjFunction *) object;
            freeChunk(&function->chunk);
            FREE(ObjFunction, object);
            break;
        }
        case OBJ_NATIVE:
            FREE(ObjNative, object);
            break;
        case OBJ_STRING: {
            ObjString *string = (ObjString *) object;
            FREE_ARRAY(char, string->chars, string->length + 1);
            FREE(ObjString, object);
            break;
        }
        case OBJ_UPVALUE:
            FREE(ObjUpvalue, object);
            break;
    }
}

void freeObjects() {
    Obj *object = vm.objects;
    while (object != NULL) {
        Obj *next = object->next; // can't access next after freeing
        freeObjects(object);
        object = next;
    }
}