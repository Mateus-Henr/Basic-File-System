#ifndef BASIC_FILE_SYSTEM_PATH_H
#define BASIC_FILE_SYSTEM_PATH_H

typedef struct Path
{
    char **entryNames;
    long size;
} Path;

Path *initializePath(char *entryPath);

void freePath(Path *path);

#endif //BASIC_FILE_SYSTEM_PATH_H
