#include "disk.h"

#define BLOCK_SIZE 512

void write_to_disk(const char *device, const char *data, size_t data_size) {
    int fd = open(device, O_WRONLY);
    if (fd < 0) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    // Writing data to the beginning of the disk (you can adjust the offset)
    off_t offset = 0;
    if (lseek(fd, offset, SEEK_SET) < 0) {
        perror("Error seeking to position");
        close(fd);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_written = write(fd, data, data_size);
    if (bytes_written < 0) {
        perror("Error writing to device");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Successfully wrote %zd bytes to %s\n", bytes_written, device);

    close(fd);
}

void read_from_disk(const char *device, char *buffer, size_t data_size) {
    int fd = open(device, O_RDONLY);
    if (fd < 0) {
        perror("Error opening device");
        exit(EXIT_FAILURE);
    }

    // Reading data from the beginning of the disk (you can adjust the offset)
    off_t offset = 0;
    if (lseek(fd, offset, SEEK_SET) < 0) {
        perror("Error seeking to position");
        close(fd);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = read(fd, buffer, data_size);
    if (bytes_read < 0) {
        perror("Error reading from device");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("Successfully read %zd bytes from %s\n", bytes_read, device);
    buffer[bytes_read] = '\0';  // Null-terminate the buffer

    close(fd);
}

int main() {
    const char *device = "/dev/disk4";  // Adjust as needed
    const char *data = "This is a test data to write directly to disk.";
    size_t data_size = strlen(data);

    //write_to_disk(device, data, data_size);

    char buffer[data_size + 1];  // +1 for null-terminator

    // Read data from disk
    read_from_disk(device, buffer, data_size);

    // Print the read data
    printf("Data read from disk: %s\n", buffer);

    return 0;
}
