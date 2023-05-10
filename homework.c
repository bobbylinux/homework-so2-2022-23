#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Params {
    char filename[100];
    long columnsForPage;
    long lineForColumn;
    long columnWidth;
    long distanceBetweenColumns;
};

/**
 * this function is used to parse arguments
 * @param arg
 * @param index
 * @param argc
 * @return
 */
long getArgsValue(char *arg[], int index, int argc) {
    long err = 0;
    char *ptr;
    if (index + 1 < argc) {
        err = strtol(arg[index + 1], &ptr, 10);
        if (err == 0) {
            goto error;
        }
    }
    return err;
    error:
    printf("Error parsing arguments.");
    exit(1);
}

struct Params parseParameters(int argc, char **argv) {
    struct Params params;
    int i = 1;
    long err = 0;
    while (argv[i] != NULL) {
        if (!strcmp(argv[i], "-f")) {
            if (i + 1 < argc) {
                printf("filename = %s\n", argv[i + 1]);
                strcpy(params.filename, argv[i + 1]);
            }
        }
        if (!strcmp(argv[i], "-w")) {
            params.columnWidth = getArgsValue(argv, i, argc);
        }
        if (!strcmp(argv[i], "-d")) {
            params.distanceBetweenColumns = getArgsValue(argv, i, argc);
        }
        if (!strcmp(argv[i], "-c")) {
            params.columnsForPage = getArgsValue(argv, i, argc);
        }
        if (!strcmp(argv[i], "-l")) {
            params.lineForColumn = getArgsValue(argv, i, argc);
        }
        i++;
    }
    return params;
}


int main(int argc, char **argv) {
    struct Params params = parseParameters(argc, argv);
    FILE *filePointer;
    if ((filePointer = fopen(params.filename, "r")) == NULL) {
        goto errorOpeningFile;
    }
    char buffer[100];
    while (fgets(buffer, 100, filePointer)) {
        printf("%s", buffer);
    }
    errorOpeningFile:
    printf("Error opening file.");
    exit(1);

    return 0;
}





