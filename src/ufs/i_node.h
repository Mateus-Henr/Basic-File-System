#ifndef BASIC_FILE_SYSTEM_I_NODE_H
#define BASIC_FILE_SYSTEM_I_NODE_H

#include "../entry/entry_metadata.h"
#include "../entry/entry_content.h"

typedef struct INode
{
    EntryHeader *header;
    EntryMetadata metadata;
    EntryContent content;
} INode;

INode *initializeINode();

void initializeINodeWithContent(INode *iNode, long id, char *entryName, enum EntryType entryType);

bool changeINodeEntryName(INode *iNode, char *newEntryName);

void displayINode(INode *iNode);

void freeINode(INode *iNode);

#endif //BASIC_FILE_SYSTEM_I_NODE_H
