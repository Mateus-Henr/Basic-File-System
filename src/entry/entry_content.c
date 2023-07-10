#include "entry_content.h"


void initializeEntryContent(EntryContent *entryContent, enum EntryType entryType, Memory *memory)
{
    if (entryType == DIRECTORY)
    {
        entryContent->entryType = DIRECTORY;
        initializeDirectory(&entryContent->directory);
    }
    else
    {
        entryContent->entryType = ARCHIVE;
        initializeFile(&entryContent->file, memory);
    }
}
