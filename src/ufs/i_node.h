#ifndef BASIC_FILE_SYSTEM_I_NODE_H
#define BASIC_FILE_SYSTEM_I_NODE_H

#include "../entry/entry_metadata.h"
#include "../entry/entry_content.h"

typedef struct INode
{
    long id;
    char *entryName;
    EntryMetadata entryMetadata;
    EntryContent entryContent;
} INode;

INode *initializeINode(long id, char *entryName, enum EntryType entryType);

bool changeINodeEntryName(INode *iNode, char *newName);

void displayINode(INode *iNode);

void freeINode(INode *iNode);

#endif //BASIC_FILE_SYSTEM_I_NODE_H
