#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#define SIZE_LIMIT (30LL * 1024 * 1024 * 1024) // 30GB in bytes

// Function to calculate the size of a folder recursively
long long get_folder_size(const char *path) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dir = opendir(path);
    long long total_size = 0;

    if (dir == NULL) {
        perror("opendir");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == 0) {
            if (S_ISDIR(file_stat.st_mode)) {
                // Recursively get the size of subdirectories
                total_size += get_folder_size(full_path);
            } else if (S_ISREG(file_stat.st_mode)) {
                // Add file size to total size
                total_size += file_stat.st_size;
            }
        }
    }

    closedir(dir);
    return total_size;
}

// Function to scan a directory for large files and large folders
void scan_directory(const char *path) {
    struct dirent *entry;
    struct stat file_stat;
    DIR *dir = opendir(path);

    if (dir == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char full_path[1024];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == 0) {
            if (S_ISREG(file_stat.st_mode)) {
                // If it's a regular file and larger than SIZE_LIMIT, print it
                if (file_stat.st_size > SIZE_LIMIT) {
                    printf("Large file: %s (%lld GB)\n", full_path, file_stat.st_size / (1024 * 1024 * 1024));
                }
            } else if (S_ISDIR(file_stat.st_mode)) {
                // If it's a directory, calculate its size
                long long folder_size = get_folder_size(full_path);
                if (folder_size > SIZE_LIMIT) {
                    printf("Large folder: %s (%lld GB)\n", full_path, folder_size / (1024 * 1024 * 1024));
                }
                // Recurse into the subdirectory
                scan_directory(full_path);
            }
        }
    }

    closedir(dir);
}

int main() {
    const char *start_path = "/";  // Change this to your starting directory
    struct stat root_stat;

    if (stat(start_path, &root_stat) == 0 && S_ISDIR(root_stat.st_mode)) {
        scan_directory(start_path);
    } else {
        printf("Invalid directory: %s\n", start_path);
    }

    return 0;
}
