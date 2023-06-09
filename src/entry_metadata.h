#ifndef BASIC_FILE_SYSTEM_ENTRY_METADATA_H
#define BASIC_FILE_SYSTEM_ENTRY_METADATA_H

#include <crtdefs.h>
#include <sys/types.h>
#include "timestamps.h"


enum EntryType
{
    DIRECTORY, FILE
};


typedef struct EntryMetadata
{
    size_t sizeInBytes;
    mode_t permissions;
    unsigned long ownership;
    enum EntryType entryType;
    Timestamps timestamps;
} EntryMetadata;


void initializeEntryMetadata(EntryMetadata *entryMetadata,
                             size_t sizeInBytes,
                             unsigned long ownership,
                             enum EntryType entryType);


#endif //BASIC_FILE_SYSTEM_ENTRY_METADATA_H
