#ifndef BASIC_FILE_SYSTEM_BLOCK_H
#define BASIC_FILE_SYSTEM_BLOCK_H

typedef struct Block
{
    long id;
    char *content;
} Block;

void addBlockContent(Block *block, long id, char *content);

void freeBlock(Block *block);

#endif //BASIC_FILE_SYSTEM_BLOCK_H