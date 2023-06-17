#ifndef BASIC_FILE_SYSTEM_DIRECTORY_H
#define BASIC_FILE_SYSTEM_DIRECTORY_H

#include <stdbool.h>
#include "linkedlist/linked_list.h"
#include "../entry_header.h"

typedef struct Directory
{
    LinkedList entries;
} Directory;

void initializeDirectory(Directory *directory);

bool addEntry(Directory *directory, EntryHeader *entryHeader);

bool transferEntry(Directory *newDirectory, Directory *oldDirectory, EntryHeader *entryHeader);

long findINodeIdInDirectory(Directory *directory, char *entryName);

bool removeEntry(Directory *directory, char *entryName);

void displayDirectory(Directory *directory);

#endif //BASIC_FILE_SYSTEM_DIRECTORY_H
