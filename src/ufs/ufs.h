#ifndef BASIC_FILE_SYSTEM_UFS_H
#define BASIC_FILE_SYSTEM_UFS_H

#include <stdbool.h>
#include "i_node.h"
#include "linkedlist/linked_list_i_node.h"
#include "../path/path.h"

typedef struct UFS
{
    INode **iNodes;
    LinkedListINode freeINodes;
    long maxINodes;
    long iNodeCount;
    bool verbose;
    Memory memory;
} UFS;

void initializeUFS(UFS *ufs, long maxINodes, bool mode, int blockSize);

void getPath(char *pathString, Path *path, bool last);

bool createEntry(UFS *ufs, Path *entryPath, enum EntryType entryType);

bool checkPathInAnother(Path *entryPath, Path *newEntryPath);

bool moveEntry(UFS *ufs, Path *entryPath, Path *newEntryPath);

bool deleteEntry(UFS *ufs, Path *entryPath, bool isTraversalDeletion);

void displayEntry(UFS *ufs, Path *entryPath);

void displayEntryHierarchy(UFS *ufs, Path *entryPath);

void displayFile(UFS *ufs, Path *entryPath);

void displayMetadata(UFS *ufs, Path *entryPath);

#endif //BASIC_FILE_SYSTEM_UFS_H
