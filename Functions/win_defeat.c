#include <stdlib.h>
#include <stdio.h>
#include "entity.h"

int is_winning(entity * boxes[], entity * targets[], int nbr_entity) {
    int a = 0;
    int b;
    int on_target = 0;

    while ((boxes[a] != NULL)) {
        b = 0;
        while ((targets[b] != NULL)) {
            if ((boxes[a]->pos_x == targets[b]->pos_x) && (boxes[a]->pos_z == targets[b]->pos_z)) {
                on_target++;
            }
            b++;
        }

        a++;
    }

    if (on_target == nbr_entity) {
        return 1;
    } else {
        return -1;
    }
}

int is_loosing_corner(char ** level, entity * boxes[], entity * targets[]) {
    int x;
    int z;

    int a = 0;
    int b = 0;

    int win = -1;

    while ((win == -1) && (boxes[a] != NULL)) {
        x = boxes[a]->pos_x;
        z = boxes[a]->pos_z;
        if (((level[x-1][z] == '#') || (level[x+1][z] == '#')) && ((level[x][z-1] == '#') || (level[x][z+1] == '#'))) {
            if (find_entity(targets, x, z) == 0) {
                win = 0;
            }
        }

        a++;
    }

    return win;
}

int is_loosing_wall(entity * boxes[], int count_t[]) {
    int count_b[4] = {0, 0, 0, 0};
    count_entity_wall(boxes, count_b);
    int x = 0;
    int win = -1;

    while ((x < 4) && (win == -1)) {
        if ((count_b[x] > 0) && (count_b[x] > count_t[x])) {
            win = 0;
        }

        x++;
    }

    return win;
}

int is_loosing(char ** level, entity * boxes[], int count_t[], entity * targets[]) {
    int win = is_loosing_corner(level, boxes, targets);

    if (win == -1) {
        win = is_loosing_wall(boxes, count_t);
    }

    return win;
}