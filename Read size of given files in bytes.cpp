#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

// Function to calculate the total size of files with a specific extension in a directory
long long calculateTotalSize(const char *directoryPath, const char *extension) {
    long long totalSize = 0;

    // Open the directory
    DIR *dir = opendir(directoryPath);
    if (dir == NULL) {
        perror("Error opening directory");
        return -1;
    }

    // Iterate over entries in the directory
    // 'struct dirent' represents an entry in the directory and contains information
    // such as the name of the entry (file or directory) and the inode number
    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        // Create the path to the entry
        char entryPath[1024];
        snprintf(entryPath, sizeof(entryPath), "%s/%s", directoryPath, entry->d_name);

        // Get information about the entry
        struct stat fileInfo;
        if (stat(entryPath, &fileInfo) == -1) {
            perror("Error getting file info");
            continue;
        }

        // Check if the entry is a regular file and has the specified extension
        if (S_ISREG(fileInfo.st_mode) && strstr(entry->d_name, extension) != NULL) {
            totalSize += fileInfo.st_size;
        }
    }

    // Close the directory
    closedir(dir);

    return totalSize;
}

int main() {
    char directoryPath[1024];
    char extension[128];
    char outputFile[128];

    // Prompt for the directory path
    printf("Enter the directory path: ");
    scanf("%s", directoryPath);

    // Prompt for the file extension (e.g., .txt)
    printf("Enter the file extension (e.g., .txt): ");
    scanf("%s", extension);

    // Prompt for the output file name
    printf("Enter the output file name: ");
    scanf("%s", outputFile);

    // Calculate the total size of files with the specified extension in the directory
    long long totalSize = calculateTotalSize(directoryPath, extension);
    if (totalSize == -1) {
        return 1;
    }

    // Print the total size to the console
    printf("Total size of %s files in directory %s: %lld bytes\n", extension, directoryPath, totalSize);

    // Write the result to the output file
    FILE *output = fopen(outputFile, "w");
    if (output == NULL) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(output, "Total size of %s files in directory %s: %lld bytes\n", extension, directoryPath, totalSize);

    fclose(output);
    printf("Result written to %s\n", outputFile);

    return 0;
}

