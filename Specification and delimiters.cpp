/*
Enter input line: This is an example sentence for testing.
Enter output specification 2-3:  // You enter "2-3" to select the 2nd and 3rd words.
Enter delimiters: space  // You enter "space" as the delimiter.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

// Structure to represent the specification for selecting parts of a line
struct part_spec {
    int begin; // Starting position
    int end;   // Ending position
};

// Function to get input for the line, output specification, and delimiters
void get_input(char *line, char *spec_string, char *delimiters) {
    printf("Enter input line: ");
    fgets(line, MAX_LINE_LEN, stdin);
    line[strcspn(line, "\n")] = '\0';

    printf("Enter output specification 2-3: ");
    fgets(spec_string, sizeof(spec_string), stdin);
    spec_string[strcspn(spec_string, "\n")] = '\0';

    printf("Enter delimiters: ");
    fgets(delimiters, sizeof(delimiters), stdin);
    delimiters[strcspn(delimiters, "\n")] = '\0';
}

// Function to check if a character is a separator
int is_separator(const char *separators, char c) {
    return strchr(separators, c) != NULL;
}

// Function to read the output specification for selecting parts
int read_part_spec(const char *spec_string, struct part_spec *s) {
    if (sscanf(spec_string, "%d-%d", &(s->begin), &(s->end)) == 2) {
        return 1; // Successfully read the output specification
    }
    return 0; // Invalid output specification
}

// Function to print the selected parts of the input line based on the specification
void print_parts(const char *line, const char *separators, struct part_spec *parts) {
    int count = 0;
    char *input = strdup(line);

    char *token = strtok(input, separators);
    while (token != NULL) {
        count++;
        if (count >= parts->begin && count <= parts->end) {
            printf("%s ", token); // Print the selected part of the line
        }
        token = strtok(NULL, separators);
    }

    printf("\n"); // Print a new line after the selected parts

    free(input); // Free the dynamically allocated memory for input
}

int main() {
    char line[MAX_LINE_LEN];
    char spec_string[32];
    char delimiters[32];

    get_input(line, spec_string, delimiters);

    struct part_spec parts;
    if (!read_part_spec(spec_string, &parts)) {
        fprintf(stderr, "Invalid output specification.\n");
        return 1;
    }

    print_parts(line, delimiters, &parts);

    return 0;
}

