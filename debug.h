//
// Created by Maxwell Conradt on 12/5/21.
//

#ifndef CLOX_DEBUG_H
#define CLOX_DEBUG_H

#include "chunk.h"
#include "value.h"

void disassembleChunk(Chunk *chunk, const char *name);

int disassembleInstruction(Chunk *chunk, int offset);

void printValue(Value value);

#endif //CLOX_DEBUG_H
