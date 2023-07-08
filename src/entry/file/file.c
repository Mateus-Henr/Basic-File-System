#include <stdio.h>
#include <stdlib.h>
#include "../../miscelaneous/colour.h"
#include "../../miscelaneous/error.h"

#include "file.h"

#define FILE_CONTENT "../files/content.txt"


void initializeFile(File *file, Memory *memory)
{
    /// TODO: Divide content into blocks.
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

    addFileContent(memory, file, fileContents);

    fclose(realFile);
    free(fileContents);
}

void displayFileContent(File *file)
{
    /// TODO: Display content into blocks.
    printf("%s\nFILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "FILE CONTENT"
           "\n%s", ORANGE, RESET);


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