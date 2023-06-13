#ifndef BASIC_FILE_SYSTEM_ENTRY_CONTENT_H
#define BASIC_FILE_SYSTEM_ENTRY_CONTENT_H

#include "directory.h"
#include "file.h"

enum EntryType
{
    DIRECTORY, FILE
};

typedef struct EntryContent
{
    enum EntryType entryType;

    union
    {
        Directory directory;
        File file;
    };
} EntryContent;

void initializeEntryContent(EntryContent *entryContent, enum EntryType entryType);

#endif //BASIC_FILE_SYSTEM_ENTRY_CONTENT_H
