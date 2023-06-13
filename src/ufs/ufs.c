#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "ufs.h"
#include "../miscelaneous/error.h"

#define DELIMITER "/"


bool checkINodeCount(UFS *ufs)
{
    if (ufs->iNodeCount + 1 == ufs->maxINodes)
    {
        printf(MAX_NUMBER_OF_INODES);
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
        printf(ALLOCATION_ERROR, "UFS INodes");
        exit(EXIT_FAILURE);
    }

    for (long i = 0; i < maxINodes; i++)
    {
        ufs->iNodes[i] = NULL;
    }

    ufs->freeINodes = (INode **) malloc(maxINodes * sizeof(INode *));

    if (!ufs->freeINodes)
    {
        printf(ALLOCATION_ERROR, "UFS Free INodes.");
        free(ufs->iNodes);
        exit(EXIT_FAILURE);
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

INode *createSingleNode(UFS *ufs, char *entryName, enum EntryType entryType)
{
    return ufs->iNodes[ufs->iNodeCount++] = initializeINode(ufs->iNodeCount, entryName, entryType);
}

bool createEntryHierarchy(UFS *ufs, INode *parentINode, Path *entryPath, enum EntryType entryType)
{
    for (long i = 1; i < entryPath->size - 1; i++)
    {
        if (!parentINode)
        {
            printf(INODE_NOT_FOUND, entryPath->entryNames[i]);
            return false;
        }

        if (parentINode->entryContent.entryType == DIRECTORY)
        {
            long iNodeId = findINodeId(&parentINode->entryContent.directory, entryPath->entryNames[i]);

            if (iNodeId == -1)
            {
                printf(INODE_NOT_FOUND, entryPath->entryNames[i]);
                return false;
            }

            parentINode = ufs->iNodes[iNodeId];
        }
        else // FILE
        {
            printf(FILE_IS_NOT_DIRECTORY, entryPath->entryNames[i]);
            return false;
        }
    }

    INode *createdINode = createSingleNode(ufs, entryPath->entryNames[entryPath->size - 1], entryType);

    if (entryType == DIRECTORY)
    {
        return addEntry(&parentINode->entryContent.directory, createdINode->id, createdINode->entryName);
    }

    return true;
}

bool createEntry(UFS *ufs, Path *entryPath, enum EntryType entryType)
{
    if (!checkINodeCount(ufs))
    {
        return false;
    }

    // Root node
    INode *foundINode = findINode(ufs, entryPath->entryNames[0]);

    if (!foundINode)
    {
        // If only the root path is specified, such as "mkdir /root".
        if (entryPath->size == 1)
        {
            createSingleNode(ufs, entryPath->entryNames[0], entryType);
            return true;
        }

        printf(INODE_NOT_FOUND, entryPath->entryNames[0]);
        return false;
    }

    if (foundINode->entryContent.entryType == ARCHIVE)
    {
        printf(FILE_IS_NOT_DIRECTORY, entryPath->entryNames[0]);
        return false;
    }

    return createEntryHierarchy(ufs, foundINode, entryPath, entryType);
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

void displayEntry(UFS *ufs, Path *entryPath)
{
    for (long i = 0; i < ufs->iNodeCount; i++)
    {
        displayINode(ufs->iNodes[i]);
    }
}