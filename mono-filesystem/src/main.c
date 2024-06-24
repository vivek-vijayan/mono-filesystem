/*
MONO file system - it is a virtual file system created to handle the files in a virtually in
the physical disk without modifying the existing file system
*/

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include <stdbool.h>
#include "stringset.c"

typedef long long int llt_exe;
typedef char chr;
typedef double d_exe;

#define MAX 200000

void clrscr();
void __intro();

bool _handle_mono_basic_command(const char *command_id)
{
    if (strcmp(command_id, "exit") == 0)
    {
        exit(0);
    }
    else if (strcmp(command_id, "clear") == 0)
    {
        clrscr();
    }
    else
    {
        printf("No such command named : \"%s\". \n Try following commands: \n 1. HELP - Get your help on the commands\n", command_id);
        return false;
    }

    return true;
}
int main()
{
    // Print ASCII art for "MONO"
    clrscr();
    __intro();
    bool exit = false;

    while (exit == false)
    {
        char input[MAX];
        
        printf("anonymus-user @ monofs (primary) > ");
        scanf("%s", input);
        _handle_mono_basic_command(input);
    }
    return 0;
}
