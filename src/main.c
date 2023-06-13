#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "commands/command.h"
#include "ufs/ufs.h"

#define MAX_INODES 1000

int main()
{
    UFS ufs;
    initializeUFS(&ufs, MAX_INODES);

    while (true)
    {
        printf("\nsomeone@PC ");

        char commandString[UCHAR_MAX];

        if (fgets(commandString, sizeof(commandString), stdin) != NULL)
        {
            // Remove the trailing newline character, if present
            commandString[strcspn(commandString, "\n")] = '\0';

            // Rest of the code
            commandSwitch(&ufs, initializeCommand(commandString));
        }
        else
        {
            printf("ERROR: Failed to read input.");
        }
    }

    return 0;
}