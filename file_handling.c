#include "cipher.h"

void readFromFile(char filename[], char content[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s for reading.\n", filename);
        content[0] = '\0';
        return;
    }
    fgets(content, 1000, file);
    fclose(file);
}

void writeToFile(char filename[], char content[]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Could not open file %s for writing.\n", filename);
        return;
    }
    fprintf(file, "%s", content);
    fclose(file);
}
