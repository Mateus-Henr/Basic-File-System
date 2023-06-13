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
    printf("\nCreation: %sLast Modification: %sLast Access: %s",
           ctime(&(timestamps->creation)),
           ctime(&(timestamps->lastModification)),
           ctime(&(timestamps->lastAccess)));
}