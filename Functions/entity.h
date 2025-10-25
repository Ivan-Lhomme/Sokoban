#ifndef __ENTITY_H__
#define __ENTITY_H__

typedef struct s_entity entity;

struct s_entity
{
    int last_pos_x;
    int last_pos_z;
    int pos_x;
    int pos_z;
    char symbole;
};

int move(char ** level, entity * e, char direction, entity * boxes[]);
entity * create_entity(int x, int z, char symbole);
void * find_entity(entity * entity[], int x, int z);
void count_entity_wall(entity * entity[], int count[]);

#endif