#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path.h"
#include "../miscelaneous/error.h"

#define DELIMITER "/"

long getEntryPathSize(char *entryPath)
{
    long size = 1;
    long pathSize = (long) strlen(entryPath);

    for (long i = 1; i < pathSize; i++)
    {
        if (entryPath[i] == DELIMITER[0] && (i + 1) != pathSize)
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
