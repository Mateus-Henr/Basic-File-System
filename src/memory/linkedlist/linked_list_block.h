#ifndef BASIC_FILE_SYSTEM_LINKED_LIST_BLOCK_H
#define BASIC_FILE_SYSTEM_LINKED_LIST_BLOCK_H

#include <stdbool.h>

typedef struct NodeBlock
{
    long id;
    struct NodeBlock *nextNode;
} NodeBlock;

typedef struct LinkedListBlock
{
    NodeBlock *head;
    NodeBlock *tail;
    long nodeCount;
} LinkedListBlock;

void initializeLinkedListBlock(LinkedListBlock *linkedList);

bool insertNodeBlock(LinkedListBlock *linkedList, long id);

long popNodeBlock(LinkedListBlock *linkedList);

#endif //BASIC_FILE_SYSTEM_LINKED_LIST_BLOCK_H