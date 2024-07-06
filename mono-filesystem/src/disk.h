#include "stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#ifndef _MONO_DISK_MANAGER
#define _MONO_DISK_MANAGER
typedef long long int llt;

typedef struct DiskProperty {
    char path[2000];        // Path to the disk or device
    llt disk_size;          // Disk size in bytes
    char fs_type[256];      // File system type
    char mount_point[2000]; // Mount point of the disk
    llt used_space;         // Used space in bytes
    llt available_space;    // Available space in bytes
    char label[256];        // Disk label
    char disk_type[50];     // Disk type (e.g., HDD, SSD)
} diskprops;

void _mono_disk_load();
void _mono_disk_error_check();
void _mono_disk_analyser();
void _mono_disk_health_check();
void _mono_disk_storage_analyser();

#endif // !1