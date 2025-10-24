#include <stdio.h>
#include <stdlib.h>
#include "entity.h"

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

entity * create_entity(int x, int z, char symbole) {
    entity * entity = malloc(sizeof(*entity));

    entity->last_pos_x = x;
    entity->last_pos_z = z;

    entity->pos_x = x;
    entity->pos_z = z;
    
    entity->symbole = symbole;

    return entity;
}