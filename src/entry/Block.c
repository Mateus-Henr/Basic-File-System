#include <stdio.h>
#include <stdlib.h>

#include "Block.h"


Block *initializeBlock(char *content, long size)
{
    Block *block = (Block *) malloc(sizeof(Block));

    if (!block)
    {
        printf("ERROR: Couldn't allocate memory for Block.");
        return NULL;
    }

    block->size = size;
    block->content = (char *) malloc(size);

    if (!block->content)
    {
        printf("ERROR: Couldn't allocate memory for Block's content.");
        return NULL;
    }

    return block;
}

void freeBlock(Block *block)
{
    if (block)
    {
        if (block->content)
        {
            free(block->content);
        }

        free(block);
    }
}
