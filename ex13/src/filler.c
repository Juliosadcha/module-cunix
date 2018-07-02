#include <stdlib.h>
#include <stdio.h>
#include "../include/filler.h"

int           main()
{
  filler_t    new_filler;
  create_filler(&new_filler);
  start_game(&new_filler);
  destroy_filler(&new_filler);

  return 0;
}

