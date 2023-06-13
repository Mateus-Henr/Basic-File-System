#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "path.h"

#define DELIMITER "/"

long getEntryPathSize(char *entryPath)
{
    long size = 0;

    for (long i = 0; i < strlen(entryPath); i++)
    {
        if (entryPath[i] == DELIMITER[0])
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
        printf("ERROR: Couldn't allocate memory for Path.");
        exit(EXIT_FAILURE);
    }

    path->size = getEntryPathSize(entryPath);

    if (path->size == 0)
    {
        printf("ERROR: Entry path invalid.");
        free(path);
        exit(EXIT_FAILURE);
    }

    path->entryNames = (char **) malloc(path->size * sizeof(char *));

    if (!path->entryNames)
    {
        printf("ERROR: Couldn't allocate memory for Path's entry names.");
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
