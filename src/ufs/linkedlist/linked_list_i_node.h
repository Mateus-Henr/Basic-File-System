#ifndef BASIC_FILE_SYSTEM_LINKED_LIST_I_NODE_H
#define BASIC_FILE_SYSTEM_LINKED_LIST_I_NODE_H

#include <stdbool.h>

typedef struct NodeINode
{
    long id;
    struct NodeINode *nextNode;
} NodeINode;

typedef struct LinkedListINode
{
    NodeINode *head;
    NodeINode *tail;
    long nodeCount;
} LinkedListINode;

void initializeLinkedListINode(LinkedListINode *linkedList);

bool insertNodeINode(LinkedListINode *linkedList, long id);

bool removeNodeINode(LinkedListINode *linkedList, long id);

#endif //BASIC_FILE_SYSTEM_LINKED_LIST_I_NODE_H