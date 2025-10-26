#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "entity.h"
#include "level.h"

void * find_entity(entity * entity[], int x, int z) {
    int i = 0;

    while ((entity[i] != NULL) && ((entity[i]->pos_x != x) || (entity[i]->pos_z != z))) {
        i++;
    }

    if (entity[i] != NULL) {
        return entity[i];
    } else {
        return 0;
    }
}

int collision_bis(char ** level, int X, int Z, char direction, entity * boxes[]) {
    if ((level[X][Z] == ' ') || (level[X][Z] == '.')) {
        return 1;
    } else if (level[X][Z] == 'X') {
        entity * box = find_entity(boxes, X, Z);
        if (move(level, box, direction, boxes) == 1) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int move(char ** level, entity * e, char direction, entity * boxes[]) {

    if (direction == 'z') {
        if (collision_bis(level, e->pos_x-1, e->pos_z, direction, boxes) == 1) {
            e->pos_x--;
        } else {
            return 0;
        }
    } else if (direction == 'q') {
        if (collision_bis(level, e->pos_x, e->pos_z-1, direction, boxes) == 1) {
            e->pos_z--;
        } else {
            return 0;
        }
    } else if (direction == 's') {
        if (collision_bis(level, e->pos_x+1, e->pos_z, direction, boxes) == 1) {
            e->pos_x++;
        } else {
            return 0;
        }
    } else if (direction == 'd') {
        if (collision_bis(level, e->pos_x, e->pos_z+1, direction, boxes) == 1) {
            e->pos_z++;
        } else {
            return 0;
        }
    }

    return 1;
}

entity ** create_entities(char symbole, entity * entities[], int nbr_entities, int ** coordinates, int indice) {
    srand(time(NULL));

    entities = realloc(entities, (nbr_entities + 1) * sizeof(*entities));

    int x;
    int z;


    int i = 0;

    while (i < nbr_entities) {
        if (symbole == 'X') {
            x = (rand() % (LENGTH - 4)) + 2;
            z = (rand() % (WIDTH - 4)) + 2;
        } else {
            x = (rand() % (LENGTH - 2)) + 1;
            z = (rand() % (WIDTH - 2)) + 1;
        }

        if (in_matrix(coordinates, x, z) == 0) {
            entities[i] = create_entity(symbole, x, z, coordinates, indice + i);

            i++;
        }
    }

    entities[i] = NULL;

    return entities;
}

int in_matrix(int ** coordone, int x, int z) {
    int find = 0;
    int i = 0;

    while ((find == 0) && (coordone[i] != NULL)) {
        if ((coordone[i][0] == x) && (coordone[i][1] == z)) {
            find = 1;
        }

        i++;
    }

    return find;
}

entity * create_entity(char symbole, int x, int z, int ** coordinates, int indice) {
    coordinates[indice] = malloc(2 * sizeof(int));
    if (x == -1) {
        srand(time(NULL));
        x = (rand() % (LENGTH - 2)) + 1;
        z = (rand() % (WIDTH - 2)) + 1;
    }

    entity * entity = malloc(sizeof(*entity));

    entity->last_pos_x = x;
    entity->last_pos_z = z;

    entity->pos_x = x;
    entity->pos_z = z;
    
    entity->symbole = symbole;

    coordinates[indice][0] = x;
    coordinates[indice][1] = z;

    return entity;
}

void count_entity_wall(entity * entity[], int count[]) {
    int i = 0;

    while (entity[i] != NULL) {
        if (entity[i]->pos_x == 1) {
            count[0]++;
        } else if (entity[i]->pos_x == 8) {
            count[1]++;
        }
        
        if (entity[i]->pos_z == 1) {
            count[2]++;
        } else if (entity[i]->pos_z == 8) {
            count[3]++;
        }

        i++;
    }
}