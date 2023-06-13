#ifndef BASIC_FILE_SYSTEM_DIRECTORY_H
#define BASIC_FILE_SYSTEM_DIRECTORY_H

#include <stdbool.h>
#include "../../linkedlist/linked_list.h"

typedef struct Directory
{
    LinkedList entries;
} Directory;

void initializeDirectory(Directory *directory);

bool addEntry(Directory *directory, long iNodeId, char *entryName);

long findINodeId(Directory *directory, char *entryName);

bool removeEntry(Directory *directory, char *entryName);

#endif //BASIC_FILE_SYSTEM_DIRECTORY_H
