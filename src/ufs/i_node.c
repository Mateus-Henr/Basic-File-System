#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "i_node.h"
#include "../miscelaneous/error.h"


INode *initializeINode(long id, char *entryName, enum EntryType entryType)
{
    INode *iNode = (INode *) malloc(sizeof(INode));

    if (!iNode)
    {
        printf(ALLOCATION_ERROR, "INode");
        exit(EXIT_FAILURE);
    }

    iNode->header = initializeEntryHeader(id, entryName);
    initializeEntryMetadata(&iNode->metadata, 10, 1);
    initializeEntryContent(&iNode->content, entryType);

    return iNode;
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