#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "block.h"
#include "../miscelaneous/error.h"

void addBlockContent(Block *block, long id, char *content)
{
    block->id = id;
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
    if (block->content)
    {
        free(block->content);
    }
}
