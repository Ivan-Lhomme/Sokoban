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

	int win;
	int verif;

	char direction;
	char restart;

	char ** level;

	entity * player;
	entity * box1;
	entity * target1;
	entity * boxes[2];
	entity * targets[2];

	int count_t[] = {0, 0, 0, 0};

	do {
		win = -1;
		level = import_level(1);

		player = create_entity(2, 2, 'o');
		box1 = create_entity(3, 3, 'X');
		target1 = create_entity(8, 8, '.');

		boxes[0] = box1; boxes[1] = NULL;
		targets[0] = target1; targets[1] = NULL;

		count_entity_wall(targets, count_t);

		while (win == -1) {
			draw_entity(level, player, boxes, targets);
			display_level(level);

			do {
				printf("Entrer une direction (zqsd) :\n");
				verif = scanf("%c", &direction);

				while (getchar() != '\n') {}
			} while (verif == 0);

			move(level, player, direction, boxes);

			win = is_winning(boxes, targets);

			if (win == -1) {
				win = is_loosing(level, boxes, count_t);
			}

			system("clear");
		}

		draw_entity(level, player, boxes, targets);
		display_level(level);
		save_level(level);

		if (win == 1) {
			printf("Bien joue, vous avez gagne !\n");
		} else if (win == 0) {
			printf("Dommage, vous avez bloque la caisse.\n");
		} else {
			printf("Petit probleme technique !\n");
		}

		printf("Si tu veux recommence entre 'y' sinon n'importe quel lettre.\n");
		verif = scanf("%c", &restart);

		while (getchar() != '\n') {}
		system("clear");
	} while (restart == 'y');

	int i = 0;
	while (boxes[i] != NULL) {
		free(boxes[i]);
		free(targets[i]);

		i++;
	}

	free(level);

	exit(0);
}