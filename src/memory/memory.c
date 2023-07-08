#include <stdlib.h>
#include <string.h>
#include <math.h>
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
        initializeBlock(&memory->blocks[i], blockSize);
        insertNodeBlock(&memory->freeBlocks, i);
    }
}

bool addFileContent(Memory *memory, File *file, char *content)
{
    long stringLength = (long) strlen(content);
    long numberOfBlocks = ceil((double) stringLength / (double) memory->blockSize);

    for (int i = 0; i < numberOfBlocks; i++)
    {
        long id = popNodeBlock(&memory->freeBlocks);

        if (id == -1)
        {
            printf(FULL_MEMORY);
            return false;
        }

        char extractedString[memory->blockSize];

        strncpy(extractedString, content, memory->blockSize * i);
        addBlockContent(&memory->blocks[id], extractedString);

        file->directBlocks[i] = &memory->blocks[id];
    }

    return true;
}