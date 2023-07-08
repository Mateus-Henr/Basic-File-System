#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "../../miscelaneous/colour.h"
#include "../../miscelaneous/error.h"

#include "file.h"

#define FILE_CONTENT "../files/content.txt"


void initializeFile(File *file, Memory *memory)
{
    FILE *realFile = fopen(FILE_CONTENT, "r");

    if (!realFile)
    {
        printf("Failed to open the file.\n");
        return;
    }

    fseek(realFile, 0, SEEK_END);
    long fileSize = ftell(realFile);
    fseek(realFile, 0, SEEK_SET);

    char *fileContents = (char *) malloc(fileSize + 1);

    if (!fileContents)
    {
        printf(ALLOCATION_ERROR, "File contents");
        fclose(realFile);
        return;
    }

    fread(fileContents, fileSize, 1, realFile);
    fileContents[fileSize] = '\0';

    file->numberOfBlocks = ceil((double) fileSize / (double) memory->blockSize);

    if (file->numberOfBlocks > 12)
    {
        file->indirectBlock = (Block **) malloc(file->numberOfBlocks * sizeof(Block *));
    }

    for (int i = 0; i < file->numberOfBlocks; i++)
    {
        long id = getAvailableBlock(memory);

        if (id == -1)
        {
            printf(FULL_MEMORY);
            return;
        }

        char extractedString[memory->blockSize + 1];
        strncpy(extractedString, (i * memory->blockSize) + fileContents, memory->blockSize);
        extractedString[memory->blockSize] = '\0';
        addFileContent(memory, id, extractedString);

        if (file->numberOfBlocks <= 12)
        {
            file->directBlocks[i] = &memory->blocks[id];
        }
        else
        {
            file->indirectBlock[i] = &memory->blocks[id];
        }
    }

    fclose(realFile);
    free(fileContents);
}

void displayFileContent(File *file)
{
    for (int i = 0; i < file->numberOfBlocks; i++)
    {
        if (file->numberOfBlocks <= 12)
        {
            printf("%s", file->directBlocks[i]->content);
        }
        else
        {
            printf("%s", file->indirectBlock[i]->content);
        }
    }
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
    }
}