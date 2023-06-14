#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "../miscelaneous/error.h"

#define MKDIR "mkdir"
#define TOUCH "touch"
#define RM "rm"
#define CAT "cat"
#define LS "ls"


bool isThereAnyOptions(char *commandLine)
{
    for (long i = 0; i < strlen(commandLine); i++)
    {
        if (commandLine[i] == '-')
        {
            return true;
        }
    }

    return false;
}

Command *initializeCommand(char *commandLine)
{
    Command *command = (Command *) malloc(sizeof(Command));

    if (!command)
    {
        printf(ALLOCATION_ERROR, "Command");
        exit(EXIT_FAILURE);
    }

    command->command = strdup(strtok(commandLine, " "));

    if (!command->command)
    {
        printf(ALLOCATION_ERROR, "Command's string");
        exit(EXIT_FAILURE);
    }

    if (isThereAnyOptions(commandLine))
    {
        command->options = strdup(strtok(NULL, " -"));

        if (!command->options)
        {
            printf(ALLOCATION_ERROR, "Command's options");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        command->options = NULL;
    }

    char *pathString = strdup(strtok(NULL, " "));

    if (!pathString)
    {
        printf(INVALID_COMMAND, commandLine);
        return NULL;
    }

    command->path = initializePath(pathString);

    if (!command->path)
    {
        return NULL;
    }

    return command;
}

void commandSwitch(UFS *ufs, Command *command)
{
    if (strcmp(command->command, MKDIR) == 0)
    {
        createEntry(ufs, command->path, DIRECTORY);
    }
    else if (strcmp(command->command, TOUCH) == 0)
    {
        createEntry(ufs, command->path, ARCHIVE);
    }
    else if (strcmp(command->command, RM) == 0)
    {
        deleteEntry(ufs, command->path);
    }
    else if (strcmp(command->command, CAT) == 0)
    {
        displayEntry(ufs, command->path);
    }
    else if (strcmp(command->command, LS) == 0)
    {
        displayEntry(ufs, command->path);
    }
    else
    {
        printf(INVALID_COMMAND, command->command);
    }
}

void freeCommand(Command *command)
{
    if (command)
    {
        if (command->command)
        {
            free(command->command);
        }

        if (command->options)
        {
            free(command->options);
        }

        freePath(command->path);
        free(command);
    }
}