#include <stdio.h>

#include "timestamps.h"


void initializeTimestamps(Timestamps *timestamps)
{
    time_t currentTime;

    time(&currentTime);

    timestamps->creation = currentTime;
    timestamps->lastModification = currentTime;
    timestamps->lastAccess = currentTime;
}


void updateLastModification(Timestamps *timestamps)
{
    time(&timestamps->lastModification);
}


void updateLastAccess(Timestamps *timestamps)
{
    time(&timestamps->lastAccess);
}


void displayTimestamps(Timestamps *timestamps)
{
    printf("Creation: %s", ctime(&(timestamps->creation)));
    printf("Last Modification: %s", ctime(&(timestamps->lastModification)));
    printf("Last Access: %s", ctime(&(timestamps->lastAccess)));
}