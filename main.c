#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Functions/level.h"
#include "Functions/entity.h"
#include "Functions/win_defeat.h"

int main()
{
	system("clear");
	printf("Bienvenue dans mon Sokoban fait maison !\n");

	int win = -1;

	char direction;

	char ** level = import_level(1);

	entity * player = create_entity(2, 2, 'O');
	entity * box1 = create_entity(3, 3, 'X');
	entity * target1 = create_entity(8, 8, '.');
	entity * boxes[] = {box1, NULL};
	entity * targets[] = {target1, NULL};

	int count_t[] = {0, 0, 0, 0};
	count_entity_wall(targets, count_t);

	while (win == -1) {
		draw_entity(level, player, boxes, targets);
		display_level(level);

		printf("Entrer une direction (zqsd) :\n");
		scanf("%c", &direction);
		move(level, player, direction, boxes);

		win = is_winning(boxes, targets);

		if (win == -1) {
			win = is_loosing(level, boxes, count_t);
		}

		system("clear");
	}

	draw_entity(level, player, boxes, targets);
	display_level(level);

	if (win == 1) {
		printf("Bien joue, vous avez gagne !\n");
	} else if (win == 0) {
		printf("Dommage, vous avez bloque la caisse.\n");
	} else {
		printf("Petit probleme technique !\n");
	}

	int i = 0;
	while (boxes[i] != NULL) {
		free(boxes[i]);
		free(targets[i]);

		i++;
	}

	free(level);

	exit(0);
}