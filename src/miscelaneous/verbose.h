/**
 * @file verbose.h
 * @brief Defines verbose messages as preprocessor macros.
 *
 * This header file defines several preprocessor macros to be used as verbose messages
 * when a command is written.
 */

#ifndef BASIC_FILE_SYSTEM_VERBOSE_H
#define BASIC_FILE_SYSTEM_VERBOSE_H

#include "colour.h"

#define VERBOSE_MKDIR "%s\nDirectory '%s' created under directory '%s'.\033[0m\n", YELLOW
#define VERBOSE_TOUCH "%s\nFile '%s' created under directory '%s'.\033[0m\n", YELLOW
#define VERBOSE_MV_FILE "%s\nFile '%s' moved from directory '%s' to directory '%s'.\033[0m\n", YELLOW
#define VERBOSE_MV_DIRECTORY "%s\nDirectory '%s' moved from directory '%s' to directory '%s'.\033[0m\n", YELLOW
#define VERBOSE_RENAME_FILE "%s\nFile '%s' renamed to '%s'.\033[0m\n", YELLOW
#define VERBOSE_RENAME_DIRECTORY "%s\nDirectory '%s' renamed to '%s'.\033[0m\n", YELLOW
#define VERBOSE_MV_RENAME_FILE "%s\nFile '%s' renamed to '%s' and moved from directory '%s' to directory '%s'.\033[0m\n", YELLOW
#define VERBOSE_MV_RENAME_DIRECTORY "%s\nDirectory '%s' renamed to '%s' and moved from directory '%s' to directory '%s'.\033[0m\n", YELLOW
#define VERBOSE_RM "%s\nFile '%s' removed from directory '%s'.\033[0m\n", YELLOW
#define VERBOSE_RM_R "%s\nDirectory '%s' removed from directory '%s'.\033[0m\n", YELLOW

#endif //BASIC_FILE_SYSTEM_VERBOSE_H