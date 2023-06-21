#ifndef BASIC_FILE_SYSTEM_LINKED_LIST_H
#define BASIC_FILE_SYSTEM_LINKED_LIST_H

#include <stdbool.h>
#include "../../entry_header.h"

typedef struct Node
{
    EntryHeader *entryHeader;
    struct Node *nextNode;
} Node;

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    long nodeCount;
} LinkedList;

void initializeLinkedList(LinkedList *linkedList);

bool insertNode(LinkedList *linkedList, EntryHeader *entryHeader);

bool removeNode(LinkedList *linkedList, char *entryName);

long getINodeNumber(LinkedList *linkedList, char *entryName);

void displayLinkedList(LinkedList *linkedList);

#endif //BASIC_FILE_SYSTEM_LINKED_LIST_H
