#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "entity.h"

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

    char ** level = NULL;
    char * line;
    int i = 0;

    line = strtok(file_content, "\n");


    while (line != NULL) {
        level = realloc(level, (i+2) * sizeof(line));
        level[i] = malloc((strlen(line) + 1) * sizeof(char));
        strcpy(level[i], line);

        line = strtok(NULL, "\n");
        i++;
    }

    level[i] = NULL;

    return level;
}

char ** draw_entity(char ** level, entity * player, entity * boxes[], entity * targets[]) {
    int x = 0;
    int z = 0;
    entity * box;

    while (level[x] != NULL) {
        z = 0;
        while (level[x][z] != '\0') {
            
            if ((player->pos_x == x) && (player->pos_z == z)) {

                if (level[player->last_pos_x][player->last_pos_z] == player->symbole) {
                    level[player->last_pos_x][player->last_pos_z] = ' ';
                }

                player->last_pos_x = player->pos_x;
                player->last_pos_z = player->pos_z;

                level[x][z] = player->symbole;
            } else {
                box = find_entity(boxes, x, z);

                if (box != 0) {
                    level[x][z] = box->symbole;
                }
            }

            z++;
        }

        x++;
    }

    int i = 0;

    while (targets[i] != NULL) {
        if ((level[targets[i]->pos_x][targets[i]->pos_z] != 'X') && (level[targets[i]->pos_x][targets[i]->pos_z] != player->symbole)) {
            level[targets[i]->pos_x][targets[i]->pos_z] = targets[i]->symbole;
        }

        i++;
    }

    return level;
}

void display_level(char ** level) {
    int i = 0;

    while (level[i] != NULL) {
        printf("%s\n", level[i]);
        i++;
    }
}

void save_level (char ** level) {
    FILE * save_file = fopen("Levels/end.txt", "w");
    int i = 0;

    while (level[i] != NULL) {
        fprintf(save_file, "%s\n", level[i]);

        i++;
    }

    fclose(save_file);
}