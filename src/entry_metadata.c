#include <sys/stat.h>

#include "entry_metadata.h"


void initializeEntryMetadata(EntryMetadata *entryMetadata,
                             size_t sizeInBytes,
                             unsigned long ownership,
                             enum EntryType entryType)
{
    entryMetadata->sizeInBytes = sizeInBytes;
    entryMetadata->permissions = S_IRUSR;
    entryMetadata->ownership = ownership;
    entryMetadata->entryType = entryType;
    initializeTimestamps(&entryMetadata->timestamps);
}