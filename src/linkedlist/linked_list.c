#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

void initializeLinkedList(LinkedList *linkedList)
{
    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->nodeCount = 0;
}

bool insertNode(LinkedList linkedList, long iNodeId, char *entryName)
{
    Node *newNode = (Node *) malloc(sizeof(Node *));

    if (!newNode)
    {
        printf("ERROR: Couldn't allocate memory for node.");
        return false;
    }

    newNode->iNodeId = iNodeId;
    newNode->entryName = entryName;
    newNode->nextNode = NULL;

    if (!linkedList.head)
    {
        linkedList.head = linkedList.tail = newNode;
    }
    else
    {
        linkedList.tail->nextNode = newNode;
        linkedList.tail = newNode;
    }

    linkedList.nodeCount++;

    return true;
}

long getINodeNumber(LinkedList linkedList, char *entryName)
{
    Node *currNode = linkedList.head;

    while (currNode)
    {
        if (strcmp(currNode->entryName, entryName) == 0)
        {
            return currNode->iNodeId;
        }

        currNode = currNode->nextNode;
    }

    return -1;
}

bool removeNode(LinkedList linkedList, char *entryName)
{
    Node *currNode = linkedList.head;
    Node *prevNode = NULL;

    if (!currNode)
    {
        return false;
    }

    while (currNode)
    {
        if (strcmp(currNode->entryName, entryName) == 0)
        {
            if (!prevNode)
            {
                linkedList.head = linkedList.head->nextNode;
            }
            else
            {
                prevNode->nextNode = currNode->nextNode;
            }

            free(currNode);
            linkedList.nodeCount--;

            return true;
        }

        prevNode = currNode;
        currNode = currNode->nextNode;
    }

    return false;
}