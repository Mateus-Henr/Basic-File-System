#ifndef BASIC_FILE_SYSTEM_MEMORY_H
#define BASIC_FILE_SYSTEM_MEMORY_H

#include "block.h"
#include "linkedlist/linked_list_block.h"
#include "../entry/file/file.h"

typedef struct Memory
{
    Block *blocks;
    long blockCount;
    long maxBlocks;
    long blockSize;
    LinkedListBlock freeBlocks;
} Memory;

void initializeMemory(Memory *memory, long maxBlocks, long blockSize);

bool addFileContent(Memory *memory, File *file, char *content);

#endif //BASIC_FILE_SYSTEM_MEMORY_H