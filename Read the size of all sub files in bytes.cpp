#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to calculate the total size of files with a specific extension in a directory and its subdirectories
long long calculateTotalSize(const char *directoryPath, const char *extension) {
    long long totalSize = 0;

    // Open the directory
    DIR *dir = opendir(directoryPath);
    if (dir == NULL) {
        perror("Error opening directory"); // Print an error message if the directory cannot be opened
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        char entryPath[1024];
        snprintf(entryPath, sizeof(entryPath), "%s/%s", directoryPath, entry->d_name);

        struct stat fileInfo;
        if (stat(entryPath, &fileInfo) == -1) {
            perror("Error getting file info"); // Print an error message if file information cannot be obtained
            continue;
        }

        if (S_ISDIR(fileInfo.st_mode)) {
            // Skip "." and ".." directories
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }

            // Recursively calculate the total size for subdirectories
            char subDirPath[1024];
            snprintf(subDirPath, sizeof(subDirPath), "%s/%s", directoryPath, entry->d_name);
            totalSize += calculateTotalSize(subDirPath, extension);
        } else if (S_ISREG(fileInfo.st_mode) && strstr(entry->d_name, extension) != NULL) {
            // Add the size of regular files with the specified extension to the total size
            totalSize += fileInfo.st_size;
        }
    }

    closedir(dir); // Close the directory
    return totalSize;
}


int main() {
    char directoryPath[1024];
    char extension[128];

    printf("Enter the directory path: ");
    scanf("%s", directoryPath);

    printf("Enter the file extension (e.g., .txt): ");
    scanf("%s", extension);

    long long totalSize = calculateTotalSize(directoryPath, extension);

    if (totalSize == -1) {
        return 1;
    }

    printf("Total size of %s files in directory %s and its subdirectories: %lld bytes\n", extension, directoryPath, totalSize);

    return 0;
}

