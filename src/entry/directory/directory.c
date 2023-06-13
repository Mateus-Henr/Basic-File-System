#include "directory.h"

void initializeDirectory(Directory *directory)
{
    initializeLinkedList(&directory->entries);
}

bool addEntry(Directory *directory, long iNodeId, char *entryName)
{
    return insertNode(directory->entries, iNodeId, entryName);
}

long findINodeId(Directory *directory, char *entryName)
{
    return getINodeNumber(directory->entries, entryName);
}

bool removeEntry(Directory *directory, char *entryName)
{
    return removeNode(directory->entries, entryName);
}