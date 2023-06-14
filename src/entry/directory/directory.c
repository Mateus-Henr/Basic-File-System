#include "directory.h"

void initializeDirectory(Directory *directory)
{
    initializeLinkedList(&directory->entries);
}

bool addEntry(Directory *directory, long iNodeId, char *entryName)
{
    return insertNode(&directory->entries, iNodeId, entryName);
}

long findINodeIdInDirectory(Directory *directory, char *entryName)
{
    return getINodeNumber(&directory->entries, entryName);
}

bool changeEntryNameInDirectory(Directory *directory, char *entryName, char *newEntryName)
{
    return changeNodeName(&directory->entries, entryName, newEntryName);
}

bool removeEntry(Directory *directory, char *entryName)
{
    return removeNode(&directory->entries, entryName);
}

void displayDirectory(Directory *directory)
{
    displayLinkedList(&directory->entries);
}