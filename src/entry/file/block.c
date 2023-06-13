#include <stdio.h>
#include <stdlib.h>

#include "block.h"
#include "../../miscelaneous/error.h"


Block *initializeBlock(char *content, long size)
{
    Block *block = (Block *) malloc(sizeof(Block));

    if (!block)
    {
        printf(ALLOCATION_ERROR, "Block");
        exit(EXIT_FAILURE);
    }

    block->size = size;
    block->content = (char *) malloc(size);

    if (!block->content)
    {
        printf(ALLOCATION_ERROR, "Block's Content.");
        free(block);
        exit(EXIT_FAILURE);
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
