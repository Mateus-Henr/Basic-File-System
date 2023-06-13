#include <stdio.h>
#include <limits.h>
#include "path/path.h"
#include "ufs/ufs.h"

#define MAX_INODES 1000

int main()
{
    while (true)
    {
        char entryPath[CHAR_MAX];

        if (!scanf("%s", entryPath))
        {
            printf("ERROR: Path invalid.");
        }

        Path *path = initializePath(entryPath);

        if (!path)
        {
            continue;
        }

        UFS ufs;
        initializeUFS(&ufs, MAX_INODES);

        createEntry(&ufs, path, DIRECTORY);
        freePath(path);

        printf("HEY");

        return false;
    }

    return 0;
}