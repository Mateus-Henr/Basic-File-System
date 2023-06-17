#ifndef BASIC_FILE_SYSTEM_PRINT_H
#define BASIC_FILE_SYSTEM_PRINT_H

#include "colour.h"

#define USER "\n%ssomeone@PC\033[0m ", GREEN
#define VALID_COMMANDS "\n%sValid commands:\033[0m %s(mkdir) (touch) (mv) (rm) (rm -r) (ls) (ls -l) (tree) (cat)\033[0m\n", YELLOW, MAGENTA
#define FORCE_or_STOP "\n%sDo you want to force this command\033[0m %s[1] %sor stop here \033[0m%s[2]\033[0m%s?\033[0m\n", YELLOW, MAGENTA, YELLOW, RED, YELLOW

#endif //BASIC_FILE_SYSTEM_PRINT_H
