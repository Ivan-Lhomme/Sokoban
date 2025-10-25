#ifndef __WIN_DEFEAT_H__
#define __WIN_DEFEAT_H__
#include "entity.h"

int is_winning(entity * boxes[], entity * targets[]);
int is_loosing(char ** level, entity * boxes[], int count_t[]);

#endif