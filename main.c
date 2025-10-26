#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "Functions/level.h"
#include "Functions/entity.h"
#include "Functions/win_defeat.h"
#include "Functions/language.h"

int main()
{
	system("clear");

	int win;									// use to check if the player win
	int check;									// use to check if a plyer enter only a character
	int nbr_entities;							// stores the amount of boxes and targets

	int language;
	printf("Which language do you want to use ? (FR : 0, EN : 1)\n");
    scanf("%d", &language);

	system("clear");

	if (language == FRENCH) {
		printf("Bienvenue dans mon Sokoban fait maison !\n");
	} else {
		printf("Welcome to my homemade Sokoban !\n");
	}


	int ** coordinates;							// stores all coodinates of all entities (player, boxes, targets)

	char direction;								// store the direction of player
	char restart;								// use to ask to the user if he want to restart

	char ** level;								// stores the whole level

	entity * player;
	entity ** boxes = malloc(sizeof(*boxes));
	entity ** targets = malloc(sizeof(*targets));

	int count_t[4];								// stores the amount of targets near walls {top, bottom, left, right}

	while (getchar() != '\n') {}


	// loop of the whole game
	do {
		srand(time(NULL));

		win = -1;								// -1 meens the user don t win and don t loose
		level = import_level(1); 				// import the level from a file
		nbr_entities = (rand() % 6) + 1;		// min : 1 | max : 5
		for (int i = 0; i < 4; i++) {			// reset count_t every restart
			count_t[i] = 0;
		}

		coordinates = malloc((nbr_entities * 2 + 2) * sizeof(int *));
		for (int i = 0; i < nbr_entities * 2 + 2; i++) {
			coordinates[i] = NULL;
		}

		player = create_entity('o', -1, -1, coordinates, 0);

		boxes = create_entities('X', boxes, nbr_entities, coordinates, 1);
		targets = create_entities('.', targets, nbr_entities, coordinates, nbr_entities + 1);

		count_entity_wall(targets, count_t);	// count number of targets near walls

		// loop of the game
		while (win == -1) {
			draw_entity(level, player, boxes, targets);
			display_level(level);

			do {
				if (language == FRENCH) {
					printf("Entrer une direction (zqsd) :\n");
				} else {
					printf("Enter a direction (zqsd) :\n");
				}
				check = scanf("%c", &direction);

				while (getchar() != '\n') {}	// delete all input in stdint
			} while (check == 0);

			move(level, player, direction, boxes);

			win = is_winning(boxes, targets, nbr_entities);

			if (win == -1) {
				win = is_loosing(level, boxes, count_t, targets);
			}

			system("clear");
		}

		draw_entity(level, player, boxes, targets);
		display_level(level);
		save_level(level);						// save the end of game in a file 

		if (win == 1) {
			if (language == FRENCH) {
				printf("Bien joue, vous avez gagne !\n");
			} else {
				printf("Good game, you win !\n");
			}
		} else if (win == 0) {
			if (language == FRENCH) {
				printf("Dommage, vous avez bloque la caisse.\n");
			} else {
				printf("Bad game, you stuck a box.\n");
			}
		} else {
			printf("ERROR !\n");
		}

		if (language == FRENCH) {
			printf("Si tu veux recommence entre 'y' sinon n'importe quoi d'autre.\n");
		} else {
			printf("If you want to restart enter 'y' otherwise anything else.\n");
		}
		check = scanf("%c", &restart);

		while (getchar() != '\n') {}
		system("clear");
	} while (restart == 'y');

	// free all dynamically allocated variables
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