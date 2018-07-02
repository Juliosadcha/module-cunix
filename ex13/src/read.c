#include "../include/filler.h"
#include "../include/my_string.h"

int           find_size(char res[32], char *buf, int start)
{
  int i;

  i = 0;
  do {
    res[i] = buf[start];
    start++;
    i++;
  } while (buf[start - 1] != '\n');

  res[i] = '\0';
  start++;

  return i-1;
}

int         	read_is_finished(stream_t* buf)
{
  int 	pos;
 	bool 	first_size;
 	int 	elem_pos;
 	char 	arr_elem_size[32];
 	pos_t 	el_size;

	pos = 0;
	first_size = true;
	elem_pos = 0;

 	while(pos <= buf->size)
 	{
 		if(buf->str[pos] > '9' || buf->str[pos] < '0')
      pos++;
 		else if (first_size)
 		{
 		  while(pos <= buf->size && buf->str[pos] != '\n')
        pos++;
     	pos++;
     	first_size = false;
    }
    else
    {
      elem_pos = pos;
      while(pos <= buf->size && buf->str[pos] != '\n')
        pos++;
      	if(buf->str[pos] != '\n')
        	return -1;
      	else
      	{
        	find_size(arr_elem_size, buf->str, elem_pos);
        	el_size = parse_size(arr_elem_size);
        	if (buf->size <= pos + el_size.x*(el_size.y + 1))
        		return -1;
        	else return 0;
      	}
    }
  }

  return -1;
}


void            read_input(filler_t* filler)
{
  char *buf;
  int bytesRead;
  FILE *logg;

  do {
    memset(buf, '\0', BUF_SIZE);
    bytesRead = read(0, buf, BUF_SIZE - 1);

    if (!strlen(buf)){
      logg = fopen("my_filler.log", "a");
      fprintf(logg, "buf: empty", buf);
      fclose(logg);
      break;
    }

    if (!filler->current_stream)
      filler->current_stream = string_create(buf);
    else
      string_append(filler->current_stream, buf);
  } while(bytesRead != 0);

  logg = fopen("my_filler.log", "a");
  fprintf(logg, "all buf: , %s\n", filler->current_stream->str);
  fclose(logg);
}

req_t*          read_request(filler_t *filler)
{
  req_t *r;
  r = NULL;

  read_input(filler);

  if(read_is_finished(filler->current_stream) == 0)
		r = parse_all(filler->current_stream->str);

  return r;
}

