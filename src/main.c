#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "command/command.h"
#include "ufs/ufs.h"
#include "miscelaneous/print.h"

#define MAX_INODES 1000

int main()
{
    UFS ufs;
    initializeUFS(&ufs, MAX_INODES);

    printf(VALID_COMMANDS);

    while (true)
    {
        printf(USER);

        char commandString[UCHAR_MAX];

        /// TODO: Issue - Press Enter without typing anything.
        ///       Fix - Create a pre-checking for the command string.
        if (fgets(commandString, sizeof(commandString), stdin) != NULL)
        {
            // Remove the trailing newline character, if present
            commandString[strcspn(commandString, "\n")] = '\0';

            Command *command = initializeCommand(commandString);

            if (!command)
            {
                continue;
            }

            commandSwitch(&ufs, command);
            freeCommand(command);
        }
        else
        {
            printf("ERROR: Failed to read input.");
        }
    }
}