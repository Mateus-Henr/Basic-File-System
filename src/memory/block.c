#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "../miscelaneous/error.h"


void initializeBlock(Block *block, long size)
{
    block->size = size;
}

void addBlockContent(Block *block, char *content)
{
    block->content = strdup(content);

    if (!block->content)
    {
        printf(ALLOCATION_ERROR, "Block's Content");
        free(block);
        exit(EXIT_FAILURE);
    }
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
