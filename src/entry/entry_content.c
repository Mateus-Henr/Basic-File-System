#include "entry_content.h"

void initializeEntryContent(EntryContent *entryContent, enum EntryType entryType)
{
    if (entryType == DIRECTORY)
    {
        entryContent->entryType = DIRECTORY;
        initializeDirectory(&entryContent->directory);
    }
    else
    {
        entryContent->entryType = ARCHIVE;
    }
}