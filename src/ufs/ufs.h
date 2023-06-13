#ifndef BASIC_FILE_SYSTEM_UFS_H
#define BASIC_FILE_SYSTEM_UFS_H

#include <stdbool.h>
#include "i_node.h"

typedef struct UFS
{
    INode **iNodes;
    INode **freeINodes;
    unsigned long maxINodes;
    unsigned long freeINodeCount;
    unsigned long iNodeCount;
} UFS;

void initializeUFS(UFS *ufs, unsigned long maxINodes);

bool createEntry(UFS *ufs, char *entryPath, enum EntryType entryType);

bool renameEntry(UFS *ufs, char *entryPath, char *newEntryName, enum EntryType entryType);

bool moveEntry(UFS *ufs, char *entryPath, char *newEntryPath, enum EntryType entryType);

bool deleteEntry(UFS *ufs, char *entryPath);

void displayEntryContent(UFS *ufs, char *entryPath);

#endif //BASIC_FILE_SYSTEM_UFS_H
