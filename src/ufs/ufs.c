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

unsigned long getFormattedEntryPathSize(char *entryPath)
{
    unsigned long size = 0;

    if (entryPath[0] != DELIMITER)
    {
        size++;
    }

    for (unsigned long i = 1; i < strlen(entryPath); i++)
    {
        if (entryPath[i] == DELIMITER)
        {
            size++;
        }
    }

    return size;
}

char *getFormattedEntryPath(char *entryPath, int size)
{

}

void initializeUFS(UFS *ufs, unsigned long maxINodes)
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

bool createEntry(UFS *ufs, char *entryPath, enum EntryType entryType)
{
    if (!checkINodeCount(ufs))
    {
        return false;
    }

    char *entryName = strtok(entryPath, DELIMITER);

    while (entryName)
    {
        INode *node = findINode(ufs, entryName);
        char *nextEntryName = strtok(NULL, DELIMITER);

        if (!node)
        {

        }
    }
}

bool renameEntry(UFS *ufs, char *entryPath, char *newEntryName, enum EntryType entryType)
{

}

bool moveEntry(UFS *ufs, char *entryPath, char *newEntryPath, enum EntryType entryType)
{
    if (!checkINodeCount(ufs))
    {
        return false;
    }


    return true;
}

bool deleteEntry(UFS *ufs, char *entryPath)
{

}

void displayEntryContent(UFS *ufs, char *entryPath)
{

}