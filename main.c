#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Functions/level.h"
#include "Functions/entity.h"

int main()
{
	system("clear");
	printf("Bienvenue dans mon Sokoban fait maison !\n");

	int win = 0;

	char direction;

	char ** level = import_level(1);

	entity * player = create_entity(2, 2, 'O');
	entity * box1 = create_entity(3, 3, 'X');
	entity * target1 = create_entity(8, 5, '.');
	entity * boxes[] = {box1, NULL};
	entity * targets[] = {target1, NULL};

	while (win == 0) {
		draw_entity(level, player, boxes, targets);
		display_level(level);

		printf("Entrer une direction (zqsd) :\n");
		scanf("%c", &direction);
		move(level, player, direction, boxes);

		system("clear");
	}

	int i = 0;
	while (boxes[i] != NULL) {
		free(boxes[i]);
		free(targets[i]);
	}
	free(level);

	exit(0);
}