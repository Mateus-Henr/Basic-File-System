#include <sys/stat.h>

#include "entry_metadata.h"


void initializeEntryMetadata(EntryMetadata *entryMetadata,
                             size_t sizeInBytes,
                             unsigned long ownership)
{
    entryMetadata->sizeInBytes = sizeInBytes;
    entryMetadata->permissions = S_IRUSR;
    entryMetadata->ownership = ownership;
    initializeTimestamps(&entryMetadata->timestamps);
}