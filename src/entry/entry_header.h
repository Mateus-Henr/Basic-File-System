#ifndef BASIC_FILE_SYSTEM_ENTRY_HEADER_H
#define BASIC_FILE_SYSTEM_ENTRY_HEADER_H

typedef struct EntryHeader
{
    long id;
    char *name;
} EntryHeader;

EntryHeader *initializeEntryHeader(long id, char *name);

void freeEntryHeader(EntryHeader *entryHeader);

#endif //BASIC_FILE_SYSTEM_ENTRY_HEADER_H
