#include <stdlib.h>
#include "../miscelaneous/error.h"

#include "memory.h"


void initializeMemory(Memory *memory, long maxBlocks, long blockSize)
{
    memory->maxBlocks = maxBlocks;
    memory->blockCount = 0;
    memory->blockSize = blockSize;
    initializeLinkedListBlock(&memory->freeBlocks);

    memory->blocks = (Block *) malloc(maxBlocks * sizeof(Block));

    if (!memory->blocks)
    {
        printf(ALLOCATION_ERROR, "Memory's blocks");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < maxBlocks; i++)
    {
        insertNodeBlock(&memory->freeBlocks, i);
    }
}

long getAvailableBlock(Memory *memory)
{
    return popNodeBlock(&memory->freeBlocks);
}

void addFileContent(Memory *memory, long blockId, char *content)
{
    addBlockContent(&memory->blocks[blockId], content);
}