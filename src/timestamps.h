#ifndef BASIC_FILE_SYSTEM_TIMESTAMPS_H
#define BASIC_FILE_SYSTEM_TIMESTAMPS_H

#include <time.h>

typedef struct Timestamps
{
    time_t creation;
    time_t lastModification;
    time_t lastAccess;
} Timestamps;

void initializeTimestamps(Timestamps *timestamps);

void updateLastModification(Timestamps *timestamps);

void updateLastAccess(Timestamps *timestamps);

void displayTimestamps(Timestamps *timestamps);

#endif //BASIC_FILE_SYSTEM_TIMESTAMPS_H
