#ifndef BASIC_FILE_SYSTEM_BLOCK_H
#define BASIC_FILE_SYSTEM_BLOCK_H

typedef struct Block
{
    char *content;
} Block;

void addBlockContent(Block *block, char *content);

void freeBlock(Block *block);

#endif //BASIC_FILE_SYSTEM_BLOCK_H