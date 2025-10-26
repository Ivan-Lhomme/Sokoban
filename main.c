#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Functions/level.h"
#include "Functions/entity.h"
#include "Functions/win_defeat.h"

int main()
{
	system("clear");
	printf("Bienvenue dans mon Sokoban fait maison !\n");

	int win;
	int verif;
	int nbr_entities;

	int ** coordinates;

	char direction;
	char restart;

	char ** level;

	entity * player;
	entity ** boxes = malloc(sizeof(*boxes));
	entity ** targets = malloc(sizeof(*targets));

	int count_t[4];

	do {
		srand(time(NULL));

		win = -1;
		level = import_level(1);
		nbr_entities = (rand() % 5) + 1;
		for (int i = 0; i < 4; i++) {
			count_t[i] = 0;
		}

		coordinates = malloc((nbr_entities * 2 + 2) * sizeof(int *));
		for (int i = 0; i < nbr_entities * 2 + 2; i++) {
			coordinates[i] = NULL;
		}

		player = create_entity('o', -1, -1, coordinates, 0);

		boxes = create_entities('X', boxes, nbr_entities, coordinates, 1);
		targets = create_entities('.', targets, nbr_entities, coordinates, nbr_entities + 1);

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

			win = is_winning(boxes, targets, nbr_entities);

			if (win == -1) {
				win = is_loosing(level, boxes, count_t, targets);
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
	free(boxes);
	free(targets);

	for (int i = 0; i < (nbr_entities * 2 + 1); i++) {
        free(coordinates[i]);
    }
    free(coordinates);

	free(level);

	exit(0);
}