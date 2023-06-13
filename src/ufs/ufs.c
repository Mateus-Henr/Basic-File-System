#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "ufs.h"

#define DELIMITER "/"

bool checkINodeCount(UFS *ufs)
{
    if (ufs->iNodeCount + 1 == ufs->maxINodes)
    {
        printf("ERROR: Max number of Inodes has been reached.");
        return false;
    }

    return true;
}

void initializeUFS(UFS *ufs, long maxINodes)
{
    ufs->maxINodes = maxINodes;
    ufs->freeINodeCount = 0;
    ufs->iNodeCount = 0;

    ufs->iNodes = (INode **) malloc(maxINodes * sizeof(INode *));

    if (!ufs->iNodes)
    {
        printf("ERROR: Couldn't allocate memory for Inodes.");
        return;
    }

    for (long i = 0; i < maxINodes; i++)
    {
        ufs->iNodes[i] = NULL;
    }

    ufs->freeINodes = (INode **) malloc(maxINodes * sizeof(INode *));

    if (!ufs->freeINodes)
    {
        printf("ERROR: Couldn't allocate memory for free Inodes.");
        return;
    }
}

INode *findINode(UFS *ufs, char *entryName)
{
    for (long i = 0; i < ufs->iNodeCount; i++)
    {
        if (strcmp(ufs->iNodes[i]->entryName, entryName) == 0)
        {
            return ufs->iNodes[i];
        }
    }

    return NULL;
}

bool createEntry(UFS *ufs, Path *entryPath, enum EntryType entryType)
{
    if (!checkINodeCount(ufs))
    {
        return false;
    }

    // Root INode
    INode *foundINode = findINode(ufs, entryPath->entryNames[0]);

    if (!foundINode && entryPath->size == 1)
    {
        ufs->iNodes[ufs->iNodeCount] = initializeINode(ufs->iNodeCount, entryPath->entryNames[0], entryType);
        ufs->iNodeCount++;
        return true;
    }

    for (long i = 1; i < entryPath->size; i++)
    {
        if (!foundINode)
        {
            if (i == entryPath->size - 1)
            {
                ufs->iNodes[ufs->iNodeCount] = initializeINode(ufs->iNodeCount, entryPath->entryNames[i], entryType);
                ufs->iNodeCount++;
                return true;
            }

            printf("ERROR: Couldn't find INode for '%s'.", entryPath->entryNames[i]);
            return false;
        }

        if (foundINode->entryContent.entryType == DIRECTORY)
        {
            long iNodeId = findINodeId(&foundINode->entryContent.directory, entryPath->entryNames[i]);

            if (iNodeId == -1)
            {
                printf("ERROR: Couldn't find INode for '%s'.", entryPath->entryNames[i]);
                return false;
            }

            foundINode = ufs->iNodes[iNodeId];
        }
        else
        {
            foundINode = NULL;
        }
    }

    return false;
}

bool renameEntry(UFS *ufs, Path *entryPath, char *newEntryName, enum EntryType entryType)
{

}

bool moveEntry(UFS *ufs, Path *entryPath, Path *newEntryPath, enum EntryType entryType)
{
    if (!checkINodeCount(ufs))
    {
        return false;
    }


    return true;
}

bool deleteEntry(UFS *ufs, Path *entryPath)
{

}

void displayEntryContent(UFS *ufs, Path *entryPath)
{

}