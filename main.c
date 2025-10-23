#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Functions/level.h"


int main()
{
	system("clear");

	char ** level = import_level(1);
	display_level(level);

	free(level);

	exit(0);
}