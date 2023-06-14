#include <stdio.h>
#include <stdlib.h>
#include "string.h"

#include "ufs.h"
#include "../miscelaneous/error.h"

#define DELIMITER "/"

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

INode *findParentINode(UFS *ufs, Path *entryPath)
{
    INode *parentINode = findINode(ufs, entryPath->entryNames[0]);

    for (long i = 1; i < entryPath->size - 1; i++)
    {
        if (!parentINode)
        {
            printf(INODE_NOT_FOUND, entryPath->entryNames[i]);
            return NULL;
        }

        if (parentINode->entryContent.entryType == DIRECTORY)
        {
            long iNodeId = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                                  entryPath->entryNames[i]);

            if (iNodeId == -1)
            {
                printf(INODE_NOT_FOUND, entryPath->entryNames[i]);
                return NULL;
            }

            parentINode = ufs->iNodes[iNodeId];
        }
        else // FILE
        {
            printf(FILE_IS_NOT_DIRECTORY, entryPath->entryNames[i]);
            return NULL;
        }
    }

    return parentINode;
}

bool createEntry(UFS *ufs, Path *entryPath, enum EntryType entryType)
{
    if (ufs->iNodeCount + 1 == ufs->maxINodes)
    {
        printf(MAX_NUMBER_OF_INODES);
        return false;
    }

    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        // Check if it is root entry that is going to be created.
        if (entryPath->size == 1)
        {
            return createSingleNode(ufs, entryPath->entryNames[0], entryType);
        }

        return false;
    }

    if (entryPath->size == 1 && parentINode->entryContent.entryType == DIRECTORY)
    {
        printf(DIRECTORY_EXISTS);
        return false;
    }

    if (parentINode->entryContent.entryType == ARCHIVE)
    {
        printf(FILE_IS_NOT_DIRECTORY, parentINode->entryName);
        return false;
    }

    int idFound = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                         entryPath->entryNames[entryPath->size - 1]);

    // Check if entry already exists.
    if (idFound != -1)
    {
        INode *existingINode = ufs->iNodes[idFound];

        if (entryType == DIRECTORY)
        {
            if (existingINode->entryContent.entryType == ARCHIVE)
            {
                printf(FILE_EXISTS);
                return false;
            }

            printf(DIRECTORY_EXISTS);
            return false;
        }
        else if (existingINode->entryContent.entryType == DIRECTORY)
        {
            printf(FILE_EXISTS);
            return false;
        }

        updateEntryMetadata(&existingINode->entryMetadata);
        return true;
    }

    INode *createdINode = createSingleNode(ufs, entryPath->entryNames[entryPath->size - 1], entryType);
    return addEntry(&parentINode->entryContent.directory, createdINode->id, createdINode->entryName);
}

bool renameEntry(UFS *ufs, Path *entryPath, char *newEntryName)
{
    INode *parentINode = findParentINode(ufs, entryPath);

    if (!parentINode)
    {
        return false;
    }

    int idFound = findINodeIdInDirectory(&parentINode->entryContent.directory,
                                         entryPath->entryNames[entryPath->size - 1]);

    if (idFound == -1)
    {
        printf(INODE_NOT_FOUND, entryPath->entryNames[entryPath->size - 1]);
        return false;
    }

    changeEntryName(ufs->iNodes[idFound], entryPath->entryNames[entryPath->size - 1]);
    changeEntryNameInDirectory(&parentINode->entryContent.directory,
                               entryPath->entryNames[entryPath->size - 1],
                               newEntryName);
    return true;
}

bool moveEntry(UFS *ufs, Path *entryPath, Path *newEntryPath, enum EntryType entryType)
{
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