/*
 * DEVELOPER : VIVEK VIJAYAN (c) 2024
 * _MONO_UI_TERMINAL Handler Structure
 * This header defines structures and enums for handling _MONO_UI_TERMINAL commands
 * and their execution history in the Mono File System.
 */

#ifndef MONO__MONO_UI_TERMINAL
#define MONO__MONO_UI_TERMINAL

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Type alias for a long long int
typedef long long int llt;

/*
 * Enum for different parser commands in the Mono File System
 */
enum parser_command
{
    MKFD, // Make Directory
    MKFL, // Make File
    OPEN, // Open File/Directory
    GO,   // Change Directory
    BACK  // Move to Parent Directory
};

// Forward declarations of structures
struct _MONO_UI_TERMINAL_HISTORY;
struct _MONO_UI_TERMINAL_EXECUTION;
struct _MONO_UI_TERMINAL_EXCEPTION;
struct _MONO_UI_TERMINAL_PARSER;

/*
 * Structure for storing the history of _MONO_UI_TERMINAL commands
 */
struct _MONO_UI_TERMINAL_HISTORY
{
    struct _MONO_UI_TERMINAL_HISTORY *prior;
    struct _MONO_UI_TERMINAL_HISTORY *next;
    llt session_id;     // Unique identifier for the session
    char command[2000]; // Command executed
    char user[200];     // User who executed the command
    char result[2000];  // Result of the command execution
};

typedef struct _MONO_UI_TERMINAL_HISTORY _mt_history; // Alias for terminal history structure

// Function prototypes for handling execution history
void _view_master_mt_history(_mt_history *src);
bool _erase_master_mt_history(_mt_history *src);
_mt_history _get_mt_history(_mt_history *src);

/*
 * Structure for storing the execution details of _MONO_UI_TERMINAL commands
 */
struct _MONO_UI_TERMINAL_EXECUTION
{
    llt session_id;     // Unique identifier for the session
    char command[2000]; // Command to be executed
    char user[200];     // User executing the command
    char result[2000];  // Result of the command execution
};

typedef struct _MONO_UI_TERMINAL_EXECUTION _mt_execution;

// Function prototype for executing commands
bool _exec_mt_commands(enum parser_command, char *parameters);

/*
 * Structure for parsing _MONO_UI_TERMINAL commands
 */
struct _MONO_UI_TERMINAL_PARSER
{
    char mono_sys_command[2000]; // Parsed system command
    char parameter[10];          // Additional parameters for the command
};

#endif // MONO__MONO_UI_TERMINAL
