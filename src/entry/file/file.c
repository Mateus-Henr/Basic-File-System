#include <stdio.h>
#include <stdlib.h>
#include "file.h"
#include "../../miscelaneous/colour.h"

#define FILE_CONTENT "../files/content.txt"

void initializeFile(File *file, char *content, long blockSize)
{
    /// TODO: Divide content into blocks.
}

void displayFileContent(File *file)
{
    /// TODO: Display content into blocks.
    printf("%s\nFILE CONTENT\n%s", ORANGE, RESET);
}

void freeFile(File *file)
{
    for (int i = 0; i < SIZE_DIRECT_BLOCKS; i++)
    {
        freeBlock(file->directBlocks[i]);

        if (file->indirectBlock)
        {
            free(file->indirectBlock);
        }

        if (file->doubleIndirectBlock)
        {
            free(file->doubleIndirectBlock);
        }

        if (file->tripleIndirectBlock)
        {
            free(file->tripleIndirectBlock);
        }
    }
}