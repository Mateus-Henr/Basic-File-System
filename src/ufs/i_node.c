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

    iNode->id = id;
    iNode->entryName = strdup(entryName);
    initializeEntryMetadata(&iNode->entryMetadata, 10, 1);
    initializeEntryContent(&iNode->entryContent, entryType);

    if (!iNode->entryName)
    {
        printf(ALLOCATION_ERROR, "INode Entry Name");
        free(iNode);
        exit(EXIT_FAILURE);
    }

    return iNode;
}

bool changeINodeEntryName(INode *iNode, char *newName)
{
    newName = strdup(newName);

    if (!newName)
    {
        printf(ERROR_RENAME);
        return false;
    }

    bool status = changeEntryNameInDirectory(&iNode->entryContent.directory,
                                             iNode->entryName,
                                             newName);

    if (iNode->entryName)
    {
        free(iNode->entryName);
    }

    iNode->entryName = newName;

    return status;
}

void displayINode(INode *iNode)
{
    displayEntryMetadata(&iNode->entryMetadata);
}

void freeINode(INode *iNode)
{
    if (iNode)
    {
        if (iNode->entryName)
        {
            free(iNode->entryName);
        }

        free(iNode);
    }
}