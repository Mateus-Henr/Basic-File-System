#ifndef BASIC_FILE_SYSTEM_MEMORY_H
#define BASIC_FILE_SYSTEM_MEMORY_H

#include "block.h"
#include "linkedlist/linked_list_block.h"

typedef struct Memory
{
    Block *blocks;
    long blockCount;
    long maxBlocks;
    long blockSize;
    LinkedListBlock freeBlocks;
} Memory;

void initializeMemory(Memory *memory, long maxBlocks, long blockSize);

long getAvailableBlockIdInMemory(Memory *memory);

void addFileContent(Memory *memory, long blockId, char *content);

bool removeBlockFromMemory(Memory *memory, long blockId);

#endif //BASIC_FILE_SYSTEM_MEMORY_H