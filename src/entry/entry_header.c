#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../miscelaneous/error.h"

#include "entry_header.h"

EntryHeader *initializeEntryHeader(long id, char *name)
{
    EntryHeader *entryHeader = (EntryHeader *) malloc(sizeof(EntryHeader));

    if (!entryHeader)
    {
        printf(ALLOCATION_ERROR, "Entry Header");
        exit(EXIT_FAILURE);
    }

    entryHeader->id = id;
    entryHeader->name = strdup(name);

    if (!entryHeader->name)
    {
        printf(ALLOCATION_ERROR, "Entry Header's entry name");
        free(entryHeader);
        exit(EXIT_FAILURE);
    }

    return entryHeader;
}

void freeEntryHeader(EntryHeader *entryHeader)
{
    if (entryHeader)
    {
        if (entryHeader->name)
        {
            free(entryHeader->name);
        }

        free(entryHeader);
    }
}