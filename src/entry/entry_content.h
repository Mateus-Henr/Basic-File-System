#ifndef BASIC_FILE_SYSTEM_ENTRY_CONTENT_H
#define BASIC_FILE_SYSTEM_ENTRY_CONTENT_H

#include "directory/directory.h"
#include "file/file.h"

enum EntryType
{
    DIRECTORY, ARCHIVE
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

void displayEntryContent(EntryContent *entryContent);

#endif //BASIC_FILE_SYSTEM_ENTRY_CONTENT_H
