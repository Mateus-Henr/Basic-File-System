#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "command/command.h"
#include "ufs/ufs.h"
#include "miscelaneous/print.h"
#include "miscelaneous/error.h"

#define MAX_INODES 1000

int main()
{
    bool verbose = false;

    while(true)
    {
        char input[UCHAR_MAX];

        printf("Would you like to use verbose mode? (Y/n)?\n");

        if(fgets(input, sizeof(input), stdin) != NULL)
        {
            if(input[0] == '\n')
            {
                continue;
            }

            if((input[0] == 'Y' || input[0] == 'y') && input[1] == '\n')
            {
                verbose = true;
            }

            break;
        }
    }

    UFS ufs;
    initializeUFS(&ufs, MAX_INODES, verbose);

    while(true)
    {
        char inputType[UCHAR_MAX];

        printf("Would you like to enter a command file? (Y/n)?\n");

        if(fgets(inputType, sizeof(inputType), stdin) != NULL)
        {
            if(inputType[0] == '\n')
            {
                continue;
            }

            if((inputType[0] == 'Y' || inputType[0] == 'y') && inputType[1] == '\n')
            {
                char fileName[UCHAR_MAX - 6];

                while(true)
                {
                    printf("Enter the file name: ");

                    if(fgets(fileName, sizeof(fileName), stdin) != NULL)
                    {
                        fileName[strcspn(fileName, "\n")] = '\0';

                        char filePath[UCHAR_MAX];
                        snprintf(filePath, sizeof(filePath), "files/%s", fileName);

                        FILE* file = fopen(filePath, "r");
            
                        if(file != NULL)
                        {    
                            char commandString[UCHAR_MAX];

                            while (fgets(commandString, sizeof(commandString), file))
                            {
                                commandString[strcspn(commandString, "\n")] = '\0';
                                commandString[strcspn(commandString, "\r")] = '\0';

                                Command* command = initializeCommand(commandString);

                                if (!command)
                                {
                                    continue;
                                }

                                commandSwitch(&ufs, command);
                                freeCommand(command);
                            }

                            fclose(file);

                            return 0;
                        }
                        else
                        {
                            printf(FILE_ERROR, fileName);
                        }
                    }
                    else
                    {            
                        printf(INPUT_ERROR);
                    }
                }
            }
            else break;
        }
        else
        {
            printf(INPUT_ERROR);
        }
    }
    printf(VALID_COMMANDS);

    while (true)
    {
        printf(USER);

        char commandString[UCHAR_MAX];

        if (fgets(commandString, sizeof(commandString), stdin) != NULL)
        {
            if (commandString[0] == '\n')
            {
                continue;
            }

            // Remove the trailing newline character, if present
            commandString[strcspn(commandString, "\n")] = '\0';
            commandString[strcspn(commandString, "\r")] = '\0';

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
            printf(INPUT_ERROR);
        }
    }
}
