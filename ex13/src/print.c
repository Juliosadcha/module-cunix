#include <stdio.h>
#include <stdlib.h>
#include "../include/filler.h"

void 		print_pos(pos_t pos)
{
	FILE 	*logg;

	dprintf(1, "%d %d", pos.x, pos.y);

	logg = fopen("filler.log" , "a");
	fprintf(logg, "Found pos: %d %d\n", pos.x, pos.y);
	fclose(logg);
}
