#include <stdio.h>
#include <sys/stat.h>

#include "entry_metadata.h"


void initializeEntryMetadata(EntryMetadata *entryMetadata,
                             size_t sizeInBytes,
                             long ownership)
{
    entryMetadata->sizeInBytes = sizeInBytes;
    entryMetadata->permissions = S_IRUSR;
    entryMetadata->ownership = ownership;
    initializeTimestamps(&entryMetadata->timestamps);
}

void displayEntryMetadata(EntryMetadata *entryMetadata)
{
    printf("\nMetadata: Size=%zu bytes, Permissions=%o, Ownership=%lu",
           entryMetadata->sizeInBytes,
           entryMetadata->permissions,
           entryMetadata->ownership);
    displayTimestamps(&entryMetadata->timestamps);
}