#ifndef BASIC_FILE_SYSTEM_UFS_H
#define BASIC_FILE_SYSTEM_UFS_H

#include <stdbool.h>
#include "i_node.h"
#include "../path/path.h"

typedef struct UFS
{
    INode **iNodes;
    INode **freeINodes;
    long maxINodes;
    long freeINodeCount;
    long iNodeCount;
} UFS;

void initializeUFS(UFS *ufs, long maxINodes);

bool createEntry(UFS *ufs, Path *entryPath, enum EntryType entryType);

bool renameEntry(UFS *ufs, Path *entryPath, char *newEntryName);

bool moveEntry(UFS *ufs, Path *entryPath, Path *newEntryPath);

int directoryRemovalAUX(UFS *ufs, Path *entryPath);

bool deleteEntry(UFS *ufs, Path *entryPath);

void displayEntry(UFS *ufs, Path *entryPath);

void displayEntryHierarchy(UFS *ufs, Path *entryPath);

void displayFile(UFS *ufs, Path *entryPath);

void displayMetadata(UFS *ufs, Path *entryPath);

#endif //BASIC_FILE_SYSTEM_UFS_H
