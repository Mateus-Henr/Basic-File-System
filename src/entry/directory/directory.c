#include "directory.h"

void initializeDirectory(Directory *directory)
{
    initializeLinkedList(&directory->entries);
}

bool addEntry(Directory *directory, EntryHeader *entryHeader)
{
    return insertNode(&directory->entries, entryHeader);
}

bool transferEntry(Directory *newDirectory, Directory *oldDirectory, EntryHeader *entryHeader)
{
//    return transferNode(&newDirectory->entries, &oldDirectory->entries, entryHeader);
return true;
}

long findINodeIdInDirectory(Directory *directory, char *entryName)
{
    return getINodeNumber(&directory->entries, entryName);
}

bool removeEntry(Directory *directory, char *entryName)
{
    return removeNode(&directory->entries, entryName);
}

void displayDirectory(Directory *directory)
{
    displayLinkedList(&directory->entries);
}