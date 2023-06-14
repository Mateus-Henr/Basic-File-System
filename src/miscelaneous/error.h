/**
 * @file error.h
 * @brief Defines error messages as preprocessor macros.
 *
 * This header file defines several preprocessor macros to be used as error messages
 * in different parts of the program. These macros are used to display specific
 * error messages when the program encounters certain errors, such as invalid input
 * or memory allocation failure.
 */

#ifndef BASIC_FILE_SYSTEM_ERROR_H
#define BASIC_FILE_SYSTEM_ERROR_H

#include "colour.h"

#define INVALID_COMMAND "%s\nERROR: Invalid command '%s'.\033[0m\n", RED
#define ALLOCATION_ERROR "%s\nERROR: Couldn't allocate memory correctly for '%s'.\033[0m\n", RED
#define INVALID_ENTRY_PATH "%s\nERROR: Invalid entry path '%s'.\033[0m\n", RED
#define INODE_NOT_FOUND "%s\nERROR: Couldn't find INode for '%s'.\033[0m\n", RED
#define MAX_NUMBER_OF_INODES "%s\nERROR: Max number of Inodes has been reached.\033[0m\n", RED
#define DIRECTORY_EXISTS "%s\nERROR: Directory already exists.\033[0m\n", RED
#define FILE_IS_NOT_DIRECTORY "%s\nERROR: Couldn't create entry, '%s' is not a directory.\033[0m\n", RED

#endif //BASIC_FILE_SYSTEM_ERROR_H