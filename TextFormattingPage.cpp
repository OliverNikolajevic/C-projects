#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Set the page width and height
static unsigned int width = 40; // Page width in characters
static unsigned int height = 50; // Page height in lines

// Page buffer for text formatting
static char *page = NULL; // Pointer to the page buffer in memory
static unsigned int cursor_line = 0; // Current line on the page
static unsigned int cursor_pos = 0; // Current position in the line

// Function to set the page width
void page_set_width(unsigned int w) {
    width = w;
}

// Function to set the page height
void page_set_height(unsigned int h) {
    height = h;
}

// Function to clear the page
void page_clear() {
    if (page) {
        free(page);
        page = NULL;
    }
    cursor_line = 0;
    cursor_pos = 0;
}

// Function to initialize the page
int page_initialize() {
    page_clear();
    page = (char *)malloc(width * height);

    if (!page) {
        return 0; // Failed, return 0
    }
    return 1; // Success, return 1
}

// Function to print the page
void page_print() {
    for (unsigned int i = 0; i < cursor_line; ++i) {
        printf("%s\n", page + i * width);
    }
    cursor_line = 0;
    cursor_pos = 0;
}

// Function for a line break
static void line_break() {
    page[cursor_line * width + cursor_pos] = 0;
    cursor_pos = 0;
    cursor_line++;

    if (cursor_line >= height) {
        page_print();
    }
}

// Function to add a word to the page
static void add_word(const char *word) {
    if (cursor_pos > 0) {
        page[cursor_line * width + cursor_pos] = ' ';
        cursor_pos++;
    }

    while (*word) {
        page[cursor_line * width + cursor_pos] = *word;
        word++;
        cursor_pos++;
    }
}

// Function to add a word to the page with word wrapping
void page_add_word(const char *word) {
    unsigned int len = strlen(word);
    if (cursor_pos > 0)
        len++;

    if (cursor_pos + len >= width) {
        line_break();
    }

    add_word(word);
}

// Function for paragraph break
void page_paragraph_break() {
    if (cursor_line > 0)
        line_break();

    page[cursor_line * width + cursor_pos] = 0;
    cursor_pos = 0;
    cursor_line++;

    if (cursor_line >= height) {
        page_print();
    }
}

int main(int argc, char *argv[]) {
    FILE *output_file = fopen("formatted_output.txt", "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error: Failed to open the output file.\n");
        return 1;
    }

    if (!page_initialize()) {
        fprintf(stderr, "Error: Failed to initialize the page formatting library.\n");
        fclose(output_file);
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "W=text-width") == 0 && i + 1 < argc) {
            page_set_width(atoi(argv[i + 1));
            i++;
        } else if (strcmp(argv[i], "H=text-height") == 0 && i + 1 < argc) {
            page_set_height(atoi(argv[i + 1]));
            i++;
        }
    }

    char line[1000];
    while (1) {
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break;
        }

        fprintf(output_file, "%s", line);

        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        char *word = strtok(line, " \t\r\n");
        while (word != NULL) {
            page_add_word(word);
            word = strtok(NULL, " \t\r\n");
        }

        if (strlen(line) == 0) {
            page_paragraph_break();
        }
    }

    page_print();
    page_clear();
    fclose(output_file);

    return 0;
}

