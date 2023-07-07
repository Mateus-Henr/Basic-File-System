#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
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

void updateEntryMetadata(EntryMetadata *entryMetadata)
{
    updateLastAccess(&entryMetadata->timestamps);
    updateLastModification(&entryMetadata->timestamps);
}

void displayEntryMetadata(EntryMetadata *entryMetadata)
{
    struct stat st;
    memset(&st, 0, sizeof(struct stat));
    st.st_mode = entryMetadata->permissions;

    // Get file permissions in string format
    char permissions[11];
    permissions[0] = (S_ISDIR(st.st_mode)) ? 'd' : '-';
    permissions[1] = (st.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (st.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (st.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (st.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (st.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (st.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (st.st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (st.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (st.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    // Display metadata
    printf("%s  %3hd %-8lu %-8zu %8lu %s\n",
           permissions, st.st_mode,
           entryMetadata->ownership,
           entryMetadata->sizeInBytes,
           entryMetadata->ownership,
           ctime(&entryMetadata->timestamps.lastModification));
}