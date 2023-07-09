#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "../../miscelaneous/colour.h"
#include "../../miscelaneous/error.h"

#include "file.h"

#define FILE_CONTENT "../files/content.txt"
#define FILE1 "../files/shrek1.txt"
#define FILE2 "../files/shrek2.txt"
#define FILE3 "../files/shrek3.txt"
#define FILE4 "../files/marquin.txt"
#define FILE5 "../files/pistonCup.txt"



void initializeFile(File *file, Memory *memory)
{
    const char* files[] = {FILE_CONTENT, FILE1, FILE2, FILE3, FILE4, FILE5};
    int numFiles = sizeof(files)/sizeof(files[0]);
    int randomIndex = rand()% numFiles;
    const char* randomFILE = files[randomIndex];

    FILE *realFile = fopen(randomFILE, "r");

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
        file->indirectBlocks = (Block **) malloc(file->numberOfBlocks * sizeof(Block *));
    }
    else
    {
        file->indirectBlocks = NULL;
    }

    for (int i = 0; i < file->numberOfBlocks; i++)
    {
        long id = getAvailableBlockIdInMemory(memory);

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
            file->indirectBlocks[i] = &memory->blocks[id];
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
            printf("%s", file->indirectBlocks[i]->content);
        }
    }
}

void freeFile(File *file, Memory *memory)
{
    for (int i = 0; i < file->numberOfBlocks; i++)
    {
        if (!file->indirectBlocks)
        {
            removeBlockFromMemory(memory, file->directBlocks[i]->id);
        }
        else
        {
            removeBlockFromMemory(memory, file->indirectBlocks[i]->id);
        }
    }
}