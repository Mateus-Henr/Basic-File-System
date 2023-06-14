#ifndef BASIC_FILE_SYSTEM_LINKED_LIST_H
#define BASIC_FILE_SYSTEM_LINKED_LIST_H

#include <stdbool.h>

typedef struct Node
{
    long iNodeId;
    char *entryName;
    struct Node *nextNode;
} Node;

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    long nodeCount;
} LinkedList;

void initializeLinkedList(LinkedList *linkedList);

bool insertNode(LinkedList *linkedList, long iNodeId, char *entryName);

long getINodeNumber(LinkedList *linkedList, char *entryName);

bool changeNodeName(LinkedList *linkedList, char *entryName, char *newEntryName);

bool removeNode(LinkedList *linkedList, char *entryName);

void displayLinkedList(LinkedList *linkedList);

#endif //BASIC_FILE_SYSTEM_LINKED_LIST_H
