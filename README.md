# Mono File System

The Mono File System (MFS) is a simple, hierarchical file system implemented in C. It supports basic operations such as creating directories and files, navigating directories, listing directory contents, deleting files and directories, and searching for files and directories. MFS is designed to be lightweight and educational, providing a clear example of file system principles.

## Developer

Vivek Vijayan © 2024

## Features

- **Create Directories**: Create new directories within the current directory.
- **Create Files**: Create new files within the current directory.
- **Change Directory**: Navigate to different directories.
- **List Contents**: List all files and directories in the current directory.
- **Delete Files/Directories**: Delete specified files or directories.
- **Search**: Search for files or directories starting from the current directory.
- **Print Path**: Print the full path from the root to the current directory.

## Getting Started

### Prerequisites

- A C compiler (e.g., GCC)
- Make (optional, for using the provided Makefile)

### Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/vivek-vijayan/mono-filesystem.git
    cd mono-filesystem
    ```

2. **Build the project:**
    You can use the provided Makefile to build the project.
    ```bash
    make
    ```

## Usage

### Running the File System

To start the Mono File System, run the compiled executable:
```bash
./mono_filesystem