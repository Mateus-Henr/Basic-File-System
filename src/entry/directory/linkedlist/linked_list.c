#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "../../../miscelaneous/error.h"

void initializeLinkedList(LinkedList *linkedList)
{
    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->nodeCount = 0;
}

bool insertNode(LinkedList *linkedList, long iNodeId, char *entryName)
{
    Node *newNode = (Node *) malloc(sizeof(Node *));

    if (!newNode)
    {
        printf(ALLOCATION_ERROR, "Linked List's Node");
        exit(EXIT_FAILURE);
    }

    newNode->iNodeId = iNodeId;
    newNode->entryName = entryName;
    newNode->nextNode = NULL;

    if (!linkedList->head)
    {
        linkedList->head = linkedList->tail = newNode;
    }
    else
    {
        linkedList->tail->nextNode = newNode;
        linkedList->tail = newNode;
    }

    linkedList->nodeCount++;

    return true;
}

long getINodeNumber(LinkedList *linkedList, char *entryName)
{
    Node *currNode = linkedList->head;

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

bool changeNodeName(LinkedList *linkedList, char *entryName, char *newEntryName)
{
    Node *currNode = linkedList->head;

    while (currNode)
    {
        if (strcmp(currNode->entryName, entryName) == 0)
        {
            if (currNode->entryName)
            {
                free(currNode->entryName);
            }

            return currNode->entryName = newEntryName;
        }

        currNode = currNode->nextNode;
    }

    return false;
}

bool removeNode(LinkedList *linkedList, char *entryName)
{
    Node *currNode = linkedList->head;
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
                linkedList->head = linkedList->head->nextNode;
            }
            else
            {
                prevNode->nextNode = currNode->nextNode;
            }

            free(currNode);
            linkedList->nodeCount--;

            return true;
        }

        prevNode = currNode;
        currNode = currNode->nextNode;
    }

    return false;
}

void displayLinkedList(LinkedList *linkedList)
{
    Node *currNode = linkedList->head;

    printf("\n");

    while (currNode)
    {
        printf("%s|%s %ld %s%s - %s |",
               CYAN,
               ORANGE,
               currNode->iNodeId,
               RESET,
               CYAN,
               currNode->entryName);

        currNode = currNode->nextNode;

        if (currNode)
        {
            printf(" => ");
        }
    }

    printf("%s\n", RESET);
}