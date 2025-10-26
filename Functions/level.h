#ifndef __LEVEL_H__
#define __LEVEL_H__
#include "entity.h"

#define LENGTH 10
#define WIDTH 10

char ** import_level(int lvl_number);
char ** draw_entity(char ** level, entity * player, entity * boxes[], entity * targets[]);
void display_level(char ** level);
void save_level (char ** level);

#endif