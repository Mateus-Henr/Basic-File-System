#ifndef BASIC_FILE_SYSTEM_FILE_H
#define BASIC_FILE_SYSTEM_FILE_H

#include "Block.h"

#define SIZE_DIRECT_BLOCKS 12

typedef struct File
{
    Block *directBlocks[SIZE_DIRECT_BLOCKS];
    Block *indirectBlock;
    Block *doubleIndirectBlock;
    Block *tripleIndirectBlock;
} File;

void initializeFile(File *file, char *content, long blockSize);

void freeFile(File *file);

#endif //BASIC_FILE_SYSTEM_FILE_H
