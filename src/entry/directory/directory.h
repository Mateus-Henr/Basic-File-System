#ifndef BASIC_FILE_SYSTEM_DIRECTORY_H
#define BASIC_FILE_SYSTEM_DIRECTORY_H

#include <stdbool.h>
#include "linkedlist/linked_list.h"

typedef struct Directory
{
    LinkedList entries;
} Directory;

void initializeDirectory(Directory *directory);

bool addEntry(Directory *directory, long iNodeId, char *entryName);

long findINodeIdInDirectory(Directory *directory, char *entryName);

bool changeEntryNameInDirectory(Directory *directory, char *entryName, char *newEntryName);

bool removeEntry(Directory *directory, char *entryName);

void displayDirectory(Directory *directory);

#endif //BASIC_FILE_SYSTEM_DIRECTORY_H
