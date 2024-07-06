#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> // Include errno for error handling

#ifdef __linux__
#include <fcntl.h> // Required for open() on Linux
#endif

typedef long long int llt;

typedef struct DiskProperty
{
    char path[2000];
    llt disk_size;
    char fs_type[256];      // Filesystem type (not used in current implementation)
    char mount_point[2000]; // Mount point path (not used in current implementation)
    llt used_space;         // Used space (not used in current implementation)
    llt available_space;    // Available space (not used in current implementation)
    char label[256];        // Disk label
    char disk_type[50];     // Disk type (SSD or HDD)
} diskprops;

#ifdef __linux__
void get_disk_size(diskprops *disk)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "lsblk -no SIZE %s", disk->path);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        perror("popen");
        return;
    }
    if (fscanf(fp, "%lld", &disk->disk_size) != 1)
    {
        fprintf(stderr, "Failed to get disk size\n");
    }
    pclose(fp);
}

void get_disk_label(diskprops *disk)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "lsblk -no LABEL %s", disk->path);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        perror("popen");
        return;
    }
    if (fgets(disk->label, sizeof(disk->label), fp) != NULL)
    {
        disk->label[strcspn(disk->label, "\n")] = 0; // Remove newline character
    }
    pclose(fp);
}

void get_disk_type(diskprops *disk)
{
    char rotational_path[256];
    snprintf(rotational_path, sizeof(rotational_path), "/sys/block/%s/queue/rotational", disk->path + 5); // +5 to skip /dev/
    int fd = open(rotational_path, O_RDONLY);
    if (fd == -1)
    {
        perror("open");
        return;
    }
    char buf[2];
    if (read(fd, buf, sizeof(buf)) != -1)
    {
        if (buf[0] == '0')
        {
            strncpy(disk->disk_type, "SSD", sizeof(disk->disk_type) - 1);
        }
        else if (buf[0] == '1')
        {
            strncpy(disk->disk_type, "HDD", sizeof(disk->disk_type) - 1);
        }
    }
    close(fd);
}
#elif __APPLE__
void get_disk_size(diskprops *disk)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "diskutil info %s | grep 'Disk Size' | awk '{print $3 $4}'", disk->path);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        perror("popen");
        return;
    }
    if (fscanf(fp, "%lld", &disk->disk_size) != 1)
    {
        fprintf(stderr, "Failed to get disk size\n");
    }
    pclose(fp);
}

void get_disk_label(diskprops *disk)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "diskutil info %s | grep 'Volume Name' | awk '{print $3}'", disk->path);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        perror("popen");
        return;
    }
    if (fgets(disk->label, sizeof(disk->label), fp) != NULL)
    {
        disk->label[strcspn(disk->label, "\n")] = 0; // Remove newline character
    }
    pclose(fp);
}

void get_disk_type(diskprops *disk)
{
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "diskutil info %s | grep 'Solid State' | awk '{print $3}'", disk->path);
    FILE *fp = popen(cmd, "r");
    if (fp == NULL)
    {
        perror("popen");
        return;
    }
    char type[10];
    if (fscanf(fp, "%s", type) == 1)
    {
        if (strcmp(type, "Yes") == 0)
        {
            strncpy(disk->disk_type, "SSD", sizeof(disk->disk_type) - 1);
        }
        else
        {
            strncpy(disk->disk_type, "HDD", sizeof(disk->disk_type) - 1);
        }
    }
    pclose(fp);
}
#endif

// Function to retrieve disk information without mounting
diskprops _mono_mount_disk(char *diskpath)
{
    diskprops _mono_disk;
    strncpy(_mono_disk.path, diskpath, sizeof(_mono_disk.path) - 1);
    _mono_disk.path[sizeof(_mono_disk.path) - 1] = '\0'; // Ensure null termination

    char _mount_status[20];

    // Retrieve disk size, label, and type
    get_disk_size(&_mono_disk);
    get_disk_label(&_mono_disk);
    get_disk_type(&_mono_disk);

    // Print disk information
    printf("Disk Path: %s\n", _mono_disk.path);
    printf("Disk Size: %lld GB\n", _mono_disk.disk_size);
    printf("Disk Label: %s\n", _mono_disk.label);
    printf("Disk Type: %s\n\n", _mono_disk.disk_type);

    // Check errno for any errors related to disk loading to MONO file system and ignorning the mount issue
    // as this file system can be used also in the unmounted drives
    strcpy(_mount_status, errno == 29 ? "UNMOUNTED" : "MOUNTED");
    if (errno < 0 || errno == 29)
        printf("Disk : %s (%s) loaded to MONO File system \n", _mono_disk.path, _mount_status);

    return _mono_disk;
}