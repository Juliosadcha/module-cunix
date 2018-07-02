#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>

#include "../include/filler.h"
#include "../include/my_string.h"

req_t*          parse_all(char *all);
pos_t           parse_size(char *answer);
