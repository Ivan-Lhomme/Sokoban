#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** import_level(int lvl_number) {
    char file_path[19];
    sprintf(file_path, "Levels/%d_level.txt", lvl_number);

    FILE * fp = fopen(file_path, "r");

    char * file_content;
    char buffer[10];

    file_content = malloc(sizeof(char));
    file_content[0] = '\0';


    while (fgets(buffer, 10, fp) != NULL) {
        file_content = realloc(file_content, (strlen(buffer) * sizeof(char)) + (strlen(file_content) * sizeof(char)) + 1);
        file_content = strcat(file_content, buffer);
    }

    fclose(fp);

    char ** level = malloc(sizeof(*level));
    char * line;
    int i = 0;

    line = strtok(file_content, "\n");


    while (line != NULL) {
        level[i] = malloc(strlen(line) * sizeof(char));
        level[i] = line;

        line = strtok(NULL, "\n");
        i++;
    }

    level[i] = NULL;

    return level;
}

void display_level(char ** level) {
    int i = 0;

    while (level[i] != NULL) {
        printf("%s\n", level[i]);
        i++;
    }
}