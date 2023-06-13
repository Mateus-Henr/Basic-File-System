#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "i_node.h"


INode *initializeINode(long id, char *entryName, enum EntryType entryType)
{
    INode *iNode = (INode *) malloc(sizeof(INode));

    if (!iNode)
    {
        printf("ERROR: Couldn't allocate INode in memory.");
        exit(EXIT_FAILURE);
    }

    iNode->id = id;
    iNode->entryName = (char *) malloc(strlen(entryName) + 1);
    initializeEntryMetadata(&iNode->entryMetadata, 10, 1);
    initializeEntryContent(&iNode->entryContent, entryType);

    if (!iNode->entryName)
    {
        printf("ERROR: Couldn't allocate string for INode in memory.");
        free(iNode);
        exit(EXIT_FAILURE);
    }

    return iNode;
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