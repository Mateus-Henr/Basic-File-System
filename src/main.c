#include <stdio.h>

#include "entry/timestamps.h"

int main()
{
    Timestamps timestamps;

    initializeTimestamps(&timestamps);

    displayTimestamps(&timestamps);

    return 0;
}