#include "stdio.h"
#include "time.h"

extern void clrscr()
{
    printf("\033[H\033[J");
}

extern void __intro()
{
    printf(" __  __  ___  _   _  ____  \n");
    printf("|  \\/  |/ _ \\| \\ | |/ __ \\ \n");
    printf("| \\  / | | | |  \\| | |  | |\n");
    printf("| |\\/| | | | | . ` | |  | |\n");
    printf("| |  | | |_| | |\\  | |__| |\n");
    printf("|_|  |_|\\___/|_| \\_|\\____/   FILE SYSTEM\n");

    // Print separator and additional information
    printf("----------------------------------------------\n");
    printf(" Version  1.0 \n");
    printf(" This program is a client of a mono file system.\n");
    printf(" It showcases basic file operations in a simulated environment.\n\n");

    // Print developer information
    printf(" Developer : Vivek Vijayan\n");
    printf(" Contact   : vijayanv31@gmail.com\n");
    printf(" Website   : www.github.com/vivek-vijayan\n");

    time_t t;
    time(&t);
    printf("\n Logged in  : %s\n\n", ctime(&t));
}