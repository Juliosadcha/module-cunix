#ifndef _FILLER_H_
#define _FILLER_H_
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>
#include <stdbool.h>

typedef struct  map_s
{
  int           h;
  int           w;
  char          **array;
}               map_t;

typedef struct  elem_s
{
  int           h;
  int           w;
  char          **array;
}               elem_t;

typedef struct  pos_s
{
  int           x;
  int           y;
}               pos_t;

typedef struct  req_s
{
  char          symbol;
  map_t         map;
  elem_t        elem;
}               req_t;

typedef struct  stream_s
{
  char          *str;
  unsigned int  size;
  unsigned int  limit;
}               stream_t;

typedef struct  filler_s
{
  stream_t      *current_stream;
  int           status;
  int           find_enemy;
}               filler_t;

/*Functions for reading*/
req_t*          read_request(filler_t *filler);
void            read_input(filler_t* filler);
int             find_size(char res[32], char *buf, int start_pos);

/*Functions for parsing*/
req_t*          parse_all(char *all);
pos_t           parse_size(char *answer);

/*Functions for game logic*/
void            start_game(filler_t *filler);
pos_t           play(req_t *core, filler_t *filler);

/*Functions for printing*/
void            print_pos(pos_t p);

/*Tools*/
int             set_nonblocking(int fd);
void            fatal(char *msg);
void            create_filler(filler_t *filler);
void            destroy_filler(filler_t *filler);
void            create_req(req_t *req);
void            destroy_req(req_t *req);

/*Check*/
int             check_connection(map_t * map, elem_t *new_elem, pos_t p, char symbol);
int             check_free_space(map_t *map, elem_t *new_elem, pos_t p);

void            read_matrix(char **matrix, char *array, int pos, int w, int h);

#endif // _FILLER_H_
