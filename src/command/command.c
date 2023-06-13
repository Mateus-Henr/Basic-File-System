#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"

#define MKDIR "mkdir"
#define TOUCH "touch"
#define RM "rm"
#define R_OPTION "-r"
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
        printf("ERROR: Couldn't allocate memory for Command.");
        exit(EXIT_FAILURE);
    }

    if (isThereAnyOptions(commandLine))
    {
        command->command = strdup(strtok(commandLine, " "));

        if (!command->command)
        {
            printf("ERROR: Couldn't allocate memory for Command.");
            return NULL;
        }

        command->options = strdup(strtok(NULL, "-"));

        if (!command->options)
        {
            printf("ERROR: Couldn't allocate memory for Command's options.");
            return NULL;
        }

        command->path = initializePath(strdup(strtok(NULL, " ")));
    }
    else
    {
        char *token = strtok(commandLine, " ");

        command->command = strdup(token);
        command->path = initializePath(strtok(NULL, " "));
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
        displayEntryContent(ufs, command->path);
    }
    else if (strcmp(command->command, LS) == 0)
    {
        displayEntryContent(ufs, command->path);
    }
    else
    {
        printf("Invalid command");
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