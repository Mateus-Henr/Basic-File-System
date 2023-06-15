#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path.h"
#include "../miscelaneous/error.h"

#define DELIMITER "/"

long getEntryPathSize(char *entryPath)
{
    long size = 1;
    long entryPathLength = (long) strlen(entryPath);

    if (entryPathLength == 1 && entryPath[0] == DELIMITER[0])
    {
        return 0;
    }

    for (long i = 1; i < entryPathLength; i++)
    {
        if (entryPath[i] == DELIMITER[0] && entryPath[entryPathLength - 1] != DELIMITER[0])
        {
            size++;
        }
    }

    return size;
}

Path *initializePath(char *entryPath)
{
    Path *path = (Path *) malloc(sizeof(Path));

    if (!path)
    {
        printf(ALLOCATION_ERROR, "Path");
        exit(EXIT_FAILURE);
    }

    path->size = getEntryPathSize(entryPath);

    if (path->size == 0)
    {
        printf(INVALID_ENTRY_PATH, entryPath);
        return NULL;
    }

    path->entryNames = (char **) malloc(path->size * sizeof(char *));

    if (!path->entryNames)
    {
        printf(ALLOCATION_ERROR, "Path's Entry Names");
        free(path);
        exit(EXIT_FAILURE);
    }

    path->entryNames[0] = strdup(strtok(entryPath, DELIMITER));

    for (long i = 1; i < path->size; i++)
    {
        path->entryNames[i] = strdup(strtok(NULL, DELIMITER));
    }

    return path;
}

void freePath(Path *path)
{
    if (path)
    {
        for (long i = 0; i < path->size; i++)
        {
            if (path->entryNames[i])
            {
                free(path->entryNames[i]);
            }
        }

        free(path);
    }
}
