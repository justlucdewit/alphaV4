#include "fileReader.h"

char* ReadFile(char* fileName) {
    FILE* fp = fopen(fileName, "r");

    if (fp == NULL) {
        perror("[ERROR 000] failed to open file");
        exit(1);
    }

    int capacity = 100;
    char ch;
    int i = 0;
    char* fileContent = malloc(capacity);
    while((ch = fgetc(fp)) != EOF) {
        fileContent[i++] = ch;

        if (i >= capacity) {
            capacity *= 1.5;
            fileContent = realloc(fileContent, capacity);
        }
    }

    fileContent[i++] = '\0';


    fclose(fp);
    return fileContent;
}