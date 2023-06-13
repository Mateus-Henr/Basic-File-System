#ifndef BASIC_FILE_SYSTEM_COLOUR_H
#define BASIC_FILE_SYSTEM_COLOUR_H

#include <stdio.h>
#include <stdlib.h>

// Reset
#define RESET   "\033[0m"       // Reset to default colors

// Text color
#define BLACK   "\033[30m"      // Black text color
#define RED     "\033[31m"      // Red text color
#define GREEN   "\033[32m"      // Green text color
#define YELLOW  "\033[33m"      // Yellow text color
#define BLUE    "\033[34m"      // Blue text color
#define MAGENTA "\033[35m"      // Magenta text color
#define CYAN    "\033[36m"      // Cyan text color
#define WHITE   "\033[37m"      // White text color

// Background color
#define B_BLACK   "\033[40m"    // Black background color
#define B_RED     "\033[41m"    // Red background color
#define B_GREEN   "\033[42m"    // Green background color
#define B_YELLOW  "\033[43m"    // Yellow background color
#define B_BLUE    "\033[44m"    // Blue background color
#define B_MAGENTA "\033[45m"    // Magenta background color
#define B_CYAN    "\033[46m"    // Cyan background color
#define B_WHITE   "\033[47m"    // White background color

// Style
#define BOLD      "\033[1m"     // Bold style
#define UNDERLINE "\033[4m"     // Underline style
#define BLINK     "\033[5m"     // Blinking style

#endif //BASIC_FILE_SYSTEM_COLOUR_H
