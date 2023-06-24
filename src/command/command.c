#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "command.h"
#include "../miscelaneous/error.h"

#define MKDIR "mkdir"
#define TOUCH "touch"
#define RM "rm"
#define MV "mv"
#define TREE "tree"
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

    command->command = strdup(strtok(strdup(commandLine), " "));

    if (!command->command)
    {
        printf(ALLOCATION_ERROR, "Command's string");
        exit(EXIT_FAILURE);
    }

    if (isThereAnyOptions(commandLine))
    {
        char *option = strtok(NULL, " ");

        if (strcmp(command->command, LS) == 0 && strcmp(option, "-l") == 0 ||
            strcmp(command->command, RM) == 0 && strcmp(option, "-r") == 0)
        {
            command->hasOption = true;
        }
        else
        {
            printf(INVALID_OPTION);
            return NULL;
        }
    }
    else
    {
        command->hasOption = false;
    }

    char *pathString = strtok(NULL, " ");

    // Commands that can have no path.
    if (strcmp(command->command, LS) == 0 || strcmp(command->command, TREE) == 0)
    {
        if (!pathString)
        {
            pathString = strdup(".");
        }
        else
        {
            pathString = strdup(pathString);
        }
    }
    else
    {
        if (!pathString)
        {
            printf(INVALID_COMMAND, commandLine);
            return NULL;
        }
        else
        {
            pathString = strdup(pathString);
        }
    }

    char *secondPathString = strtok(NULL, " ");

    if (secondPathString)
    {
        secondPathString = strdup(secondPathString);
    }

    command->path = initializePath(pathString);

    if (!command->path)
    {
        return NULL;
    }

    if (strcmp(command->command, MV) == 0)
    {
        if (!secondPathString)
        {
            printf(INVALID_COMMAND, commandLine);
            return NULL;
        }

        command->secondPath = initializePath(secondPathString);

        if (!command->secondPath)
        {
            return NULL;
        }
    }
    else
    {
        command->secondPath = NULL;
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
    else if (strcmp(command->command, MV) == 0)
    {
        moveEntry(ufs, command->path, command->secondPath);
    }
    else if (strcmp(command->command, RM) == 0)
    {
        if(command->hasOption){
            printf("ola");
            //RM-R = deletarDiretorio
            deleteDirectory(ufs, command->path);
            return;
        }
        //deletarArquivo
        deleteFiles(ufs, command->path);
    }
    else if (strcmp(command->command, CAT) == 0)
    {
        displayFile(ufs, command->path);
    }
    else if (strcmp(command->command, LS) == 0)
    {
        if (command->hasOption)
        {
            displayMetadata(ufs, command->path);
            return;
        }

        displayEntry(ufs, command->path);
    }
    else if (strcmp(command->command, TREE) == 0)
    {
        displayEntryHierarchy(ufs, command->path);
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

        freePath(command->path);
        freePath(command->secondPath);
        free(command);
    }
}