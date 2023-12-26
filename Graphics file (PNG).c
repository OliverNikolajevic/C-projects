#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int read_big_endian_uint(FILE *fp) {
    unsigned char bytes[4];
    if (fread(bytes, sizeof(bytes), 1, fp) != 1) {
        perror("Error reading file");
        exit(EXIT_FAILURE);
    }
    return (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];
}

char* get_color_type_string(unsigned char color_type) {
    switch (color_type) {
        case 0:
            return "Grayscale";
        case 2:
            return "Truecolor";
        case 4:
            return "Grayscale with alpha";
        case 6:
            return "Truecolor with alpha";
        default:
            return "Unknown color type";
    }
}

void print_pformat(const char *filename, unsigned int width, unsigned int height, const char *color_type_string, unsigned char bit_depth) {
    printf("%s: %u x %u, %s, %u bits per sample\n", filename, width, height, color_type_string, bit_depth);
}

void print_cformat(int chunkNum, const char *type, unsigned int length) {
    printf("%d: %s (%u)\n", chunkNum, type, length);
}

void process_png_pformat(const char *filename, const char *pformat, const char *cformat) {
    unsigned char signature[8];

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Cannot open %s!\n", filename);
        return;
    }
    if (fread(signature, sizeof(signature), 1, fp) != 1 || memcmp(signature, "\x89PNG\r\n\x1a\n", 8) != 0) {
        fprintf(stderr, "%s is not a valid PNG file!\n", filename);
        fclose(fp);
        return;
    }
    unsigned int length = read_big_endian_uint(fp);
    char type[5];
    if (fread(type, 1, 4, fp) != 4) {
        fprintf(stderr, "Error reading IHDR!\n");
        fclose(fp);
        return;
    }
    type[4] = '\0';
    if (strcmp(type, "IHDR") != 0) {
        fprintf(stderr, "IHDR not found!\n");
        fclose(fp);
        return;
    }
    unsigned int width = read_big_endian_uint(fp);
    unsigned int height = read_big_endian_uint(fp);
    unsigned char bit_depth, color_type, compression, filter, interlace;
    char color_type_string[25];
    fread(&bit_depth, 1, 1, fp);
    fread(&color_type, 1, 1, fp);
    fread(&compression, 1, 1, fp);
    fread(&filter, 1, 1, fp);
    fread(&interlace, 1, 1, fp);
    fseek(fp, 4, SEEK_CUR);

    strcpy(color_type_string, get_color_type_string(color_type));


    print_pformat(filename, width, height, color_type_string, bit_depth);

    int chunkNum = 1;
    do {
        length = read_big_endian_uint(fp);
        if (fread(type, 1, 4, fp) != 4) {
            fprintf(stderr, "Error reading type!\n");
            fclose(fp);
            return;
        }
        type[4] = '\0';


        print_cformat(chunkNum, type, length);

        fseek(fp, length + 4, SEEK_CUR);
        chunkNum++;
    } while (strcmp(type, "IEND") != 0 && !feof(fp));

    fclose(fp);
}
void process_png_cformat(const char *filename, const char *pformat, const char *cformat) {
    unsigned char signature[8];

    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        fprintf(stderr, "Cannot open %s!\n", filename);
        return;
    }
    if (fread(signature, sizeof(signature), 1, fp) != 1 || memcmp(signature, "\x89PNG\r\n\x1a\n", 8) != 0) {
        fprintf(stderr, "%s is not a valid PNG file!\n", filename);
        fclose(fp);
        return;
    }
    unsigned int length = read_big_endian_uint(fp);
    char type[5];
    if (fread(type, 1, 4, fp) != 4) {
        fprintf(stderr, "Error reading IHDR!\n");
        fclose(fp);
        return;
    }
    type[4] = '\0';
    if (strcmp(type, "IHDR") != 0) {
        fprintf(stderr, "IHDR not found!\n");
        fclose(fp);
        return;
    }
    unsigned int width = read_big_endian_uint(fp);
    unsigned int height = read_big_endian_uint(fp);
    unsigned char bit_depth, color_type, compression, filter, interlace;
    char color_type_string[25];
    fread(&bit_depth, 1, 1, fp);
    fread(&color_type, 1, 1, fp);
    fread(&compression, 1, 1, fp);
    fread(&filter, 1, 1, fp);
    fread(&interlace, 1, 1, fp);
    fseek(fp, 4, SEEK_CUR);

    strcpy(color_type_string, get_color_type_string(color_type));
 int chunkNum = 1;
    printf("With a single file %s as command-line argument, the output should be something like the following:\n", filename);
    printf("%s: %u x %u, %s, %u bits per sample, 36 chunks\n", filename, width, height, color_type_string, bit_depth);

    if (cformat != NULL) {
             int chunkNum = 1;
        do {
            length = read_big_endian_uint(fp);
            if (fread(type, 1, 4, fp) != 4) {
                fprintf(stderr, "Error reading type!\n");
                fclose(fp);
                return;
            }
            type[4] = '\0';
            printf("%u: %s (%u)\n", chunkNum, type, length);
            if (strcmp(type, "IEND") != 0) {
                unsigned char *chunk_data = (unsigned char *)malloc(length);
                if (fread(chunk_data, 1, length, fp) != length) {
                    fprintf(stderr, "Error reading data!\n");
                    fclose(fp);
                    return;
                }
                for (unsigned int i = 0; i < length; i++) {
                    printf("%02x ", chunk_data[i]);
                    if ((i + 1) % 16 == 0) {
                        printf("\n");
                    }
                }
                printf("\n");
                free(chunk_data);
    chunkNum++;
            }
            chunkNum++;
            fseek(fp, 4, SEEK_CUR);
        } while (strcmp(type, "IEND") != 0 && !feof(fp));
         printf("Total chunks: %d\n", chunkNum - 1);
    }

    fclose(fp);
}

void process_png(const char *filename, const char *pformat, const char *cformat) {

    if (strlen(pformat) % 2 == 1) {
        process_png_pformat(filename, pformat, cformat);
    } else {
        process_png_cformat(filename, pformat, cformat);
    }
}
void print_usage() {
    printf("Usage: pngtool [options] file.png\n");
    printf(" -pformat <format>: Custom format string for image properties\n");
    printf(" -cformat <format>: Custom format string for chunk information\n");
}

int main() {
    const char *defaultPFormat = "_f: _w x _h, _c, _d bits per sample, _N chunks\n_C";
    const char *defaultCFormat = "_n: _t (_l)\n_D\n";

    const char *pformat = defaultPFormat;
    const char *cformat = defaultCFormat;

    printf("Choose format (1 for pformat, 2 for cformat): ");
    int choice;
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter pformat: ");
        char format[100];
        scanf("%s", format);
        pformat = strdup(format);
    } else if (choice == 2) {
        printf("Enter cformat: ");
        char format[100];
        scanf("%s", format);
        cformat = strdup(format);
    } else {
        printf("Invalid choice. Using default formats.\n");
    }

    printf("Enter file path: ");
    char filepath[100];
    scanf("%s", filepath);

    process_png(filepath, pformat, cformat);

    return 0;
}

