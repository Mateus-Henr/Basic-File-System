#include <stdio.h>

#include "timestamps.h"

int main()
{
    Timestamps timestamps;

    initializeTimestamps(&timestamps);

    displayTimestamps(&timestamps);

    return 0;
}