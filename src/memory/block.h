#ifndef BASIC_FILE_SYSTEM_BLOCK_H
#define BASIC_FILE_SYSTEM_BLOCK_H

typedef struct Block
{
    char *content;
    long size;
} Block;

void initializeBlock(Block *block, long size);

void addBlockContent(Block *block, char *content);

void freeBlock(Block *block);

#endif //BASIC_FILE_SYSTEM_BLOCK_H