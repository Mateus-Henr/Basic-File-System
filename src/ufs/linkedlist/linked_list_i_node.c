#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list_i_node.h"
#include "../../miscelaneous/error.h"

void initializeLinkedListINode(LinkedListINode *linkedList)
{
    linkedList->head = NULL;
    linkedList->tail = NULL;
    linkedList->nodeCount = 0;
}

bool insertNodeINode(LinkedListINode *linkedList, long id)
{
    NodeINode *newNode = (NodeINode *) malloc(sizeof(NodeINode));

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

bool removeNodeINode(LinkedListINode *linkedList, long id)
{
    NodeINode *currNode = linkedList->head;
    NodeINode *prevNode = NULL;

    if (!currNode)
    {
        return false;
    }

    while (currNode)
    {
        if (currNode->id == id)
        {
            if (linkedList->nodeCount == 1)
            {
                linkedList->head = NULL;
                linkedList->tail = NULL;
            }

            if (!currNode->nextNode)
            {
                linkedList->tail = prevNode;
            }

            if (!prevNode)
            {
                linkedList->head = currNode->nextNode;
            }
            else
            {
                prevNode->nextNode = currNode->nextNode;
            }

            linkedList->nodeCount--;

            free(currNode);
            return true;
        }

        prevNode = currNode;
        currNode = currNode->nextNode;
    }

    return false;
}