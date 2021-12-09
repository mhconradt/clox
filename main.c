#include "common.h"
#include "chunk.h"
#include "debug.h"
#include "vm.h"

int main() {
    initVM();
    Chunk chunk;
    initChunk(&chunk);

    int constant = addConstant(&chunk, 1.2);
    writeChunk(&chunk, OP_CONSTANT, 42);
    writeChunk(&chunk, constant, 42);

    constant = addConstant(&chunk, 3.4);
    writeChunk(&chunk, OP_CONSTANT, 42);
    writeChunk(&chunk, constant, 42);

    writeChunk(&chunk, OP_ADD, 42);

    constant = addConstant(&chunk, 5.6);
    writeChunk(&chunk, OP_CONSTANT, 42);
    writeChunk(&chunk, constant, 42);

    writeChunk(&chunk, OP_DIVIDE, 42);
    writeChunk(&chunk, OP_NEGATE, 42);
    writeChunk(&chunk, OP_RETURN, 42);
    disassembleChunk(&chunk, "test chunk");
    interpret(&chunk);
    freeVM();
    freeChunk(&chunk);
    return 0;
}