#ifndef BASIC_FILE_SYSTEM_COMMAND_H
#define BASIC_FILE_SYSTEM_COMMAND_H

#include "../ufs/ufs.h"

typedef struct Command
{
    char *command;
    char *options;
    Path *path;
    Path *secondPath;
} Command;

Command *initializeCommand(char *commandLine);

void commandSwitch(UFS *ufs, Command *command);

void freeCommand(Command *command);

#endif //BASIC_FILE_SYSTEM_COMMAND_H
