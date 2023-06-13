#ifndef BASIC_FILE_SYSTEM_BLOCK_H
#define BASIC_FILE_SYSTEM_BLOCK_H

typedef struct Block
{
    char *content;
    long size;
} Block;

Block *initializeBlock(char *content, long size);

void freeBlock(Block *block);

#endif //BASIC_FILE_SYSTEM_BLOCK_H
