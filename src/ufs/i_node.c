#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "i_node.h"
#include "../miscelaneous/error.h"

INode *initializeINode()
{
    INode *iNode = (INode *) malloc(sizeof(INode));

    if (!iNode)
    {
        printf(ALLOCATION_ERROR, "INode");
        exit(EXIT_FAILURE);
    }

    return iNode;
}

void initializeINodeWithContent(INode *iNode, long id, char *entryName, enum EntryType entryType, Memory *memory)
{
    iNode->header = initializeEntryHeader(id, entryName);
    initializeEntryMetadata(&iNode->metadata, 10, 1);
    initializeEntryContent(&iNode->content, entryType, memory);
}

bool changeINodeEntryName(INode *iNode, char *newEntryName)
{
    char *newName = strdup(newEntryName);

    if (!newName)
    {
        printf(ERROR_RENAME);
        return false;
    }

    if (iNode->header->name)
    {
        free(iNode->header->name);
    }

    return iNode->header->name = newName;
}

void displayINode(INode *iNode)
{
    displayEntryMetadata(&iNode->metadata);
}

void freeINode(INode *iNode)
{
    if (iNode)
    {
        freeEntryHeader(iNode->header);
        free(iNode);
    }
}