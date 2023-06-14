#ifndef BASIC_FILE_SYSTEM_ENTRY_METADATA_H
#define BASIC_FILE_SYSTEM_ENTRY_METADATA_H

#include <crtdefs.h>
#include <sys/types.h>
#include "timestamps.h"


typedef struct EntryMetadata
{
    size_t sizeInBytes;
    mode_t permissions;
    long ownership;
    Timestamps timestamps;
} EntryMetadata;


void initializeEntryMetadata(EntryMetadata *entryMetadata,
                             size_t sizeInBytes,
                             long ownership);

void updateEntryMetadata(EntryMetadata *entryMetadata);

void displayEntryMetadata(EntryMetadata *entryMetadata);

#endif //BASIC_FILE_SYSTEM_ENTRY_METADATA_H
