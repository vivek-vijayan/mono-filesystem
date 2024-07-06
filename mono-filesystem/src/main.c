/*
 * MONO File System - A virtual file system created to handle files virtually
 * on the physical disk without modifying the existing file system.
 */

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include <stdbool.h>
#include "stringset.c"
#include <fcntl.h>
#include <unistd.h>
#include "mount.c"

typedef long long int llt_exe; // Custom type definition for long long int
typedef char chr;              // Custom type definition for char
typedef double d_exe;          // Custom type definition for double

#define MAX 200000 // Maximum size for input buffer

// Function prototypes
void clrscr();  // Clears the screen
void __intro(); // Displays the introduction ASCII art

/*
 * Handles basic MONO file system commands such as "exit" and "clear".
 *
 * @param command_id - Command entered by the user.
 * @return - Returns true if the command is successfully handled, false otherwise.
 */
bool _handle_mono_basic_command(const char *command_id)
{
    if (strcmp(command_id, "exit") == 0) // Exit the program
    {
        exit(0);
    }
    else if (strcmp(command_id, "clear") == 0) // Clear the screen
    {
        clrscr();
    }
    else // Unknown command
    {
        printf("No such command named : \"%s\". \nTry following commands: \n1. HELP - Get help on the commands\n", command_id);
        return false;
    }

    return true;
}

int main()
{
    clrscr();  // Clear the screen at the start
    __intro(); // Display the introduction ASCII art

    // Load the disk
    char diskpath[2000];
    printf("Enter the disk path to load the Mono File System : ");
    scanf("%s", diskpath);
    diskprops disk = _mono_mount_disk(diskpath);

    bool exit = false; // Control variable for the main loop

    while (!exit)
    {
        char input[MAX];

        printf("anonymous-user @ monofs (primary) > ");
        fgets(input, sizeof(input), stdin); // Read user input safely

        // Remove trailing newline character from fgets
        input[strcspn(input, "\n")] = '\0';

        exit = _handle_mono_basic_command(input);
    }
    return 0;
}
