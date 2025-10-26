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
entity * create_entity(char symbole, int x, int z, int ** coordinates, int indice);
entity ** create_entities(char symbole, entity * entities[], int nbr_entities, int ** coordinates, int indice);
void * find_entity(entity * entity[], int x, int z);
void count_entity_wall(entity * entity[], int count[]);
int in_matrix(int ** coordone, int x, int z);

#endif