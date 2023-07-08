#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../miscelaneous/error.h"

#include "linked_list_block.h"


void initializeLinkedListBlock(LinkedListBlock *linkedList)
{
    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->nodeCount = 0;
}

bool insertNodeBlock(LinkedListBlock *linkedList, long id)
{
    NodeBlock *newNode = (NodeBlock *) malloc(sizeof(NodeBlock));

    if (!newNode)
    {
        printf(ALLOCATION_ERROR, "Linked List's Free INode");
        exit(EXIT_FAILURE);
    }

    newNode->id = id;
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

long popNodeBlock(LinkedListBlock *linkedList)
{
    if (!linkedList->head)
    {
        return -1;
    }

    NodeBlock *firstNode = linkedList->head;
    long deletedId = firstNode->id;

    linkedList->head = firstNode->nextNode;
    linkedList->nodeCount--;

    if (!linkedList->head)
    {
        linkedList->tail = NULL;
    }

    free(firstNode);

    return deletedId;
}