#ifndef BASIC_FILE_SYSTEM_FILE_H
#define BASIC_FILE_SYSTEM_FILE_H

#include "../../memory/block.h"
#include "../../memory/memory.h"

#define SIZE_DIRECT_BLOCKS 12

typedef struct File
{
    Block *directBlocks[SIZE_DIRECT_BLOCKS];
    Block **indirectBlock;
    long numberOfBlocks;
} File;

void initializeFile(File *file, Memory *memory);

void displayFileContent(File *file);

void freeFile(File *file);

#endif //BASIC_FILE_SYSTEM_FILE_H
