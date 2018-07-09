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
#define BUF_SIZE 64

req_t 		*parse_all(char *all)
{
	int 	i;
	map_t 	map;
	elem_t 	elem;
	req_t 	*request;
	pos_t 	position;
	int 	flag;
	int 	n;
	int 	m;
	char 	*pos1;
	char 	*pos2;
	FILE 	*logger;

	i = 0;
	flag = 0;
	n = 0;
	m = 0;
	request = (req_t *) malloc(sizeof(req_t));
	pos1 = (char *) malloc(BUF_SIZE * sizeof(char));
	pos2 = (char *) malloc(BUF_SIZE * sizeof(char));

	memset(pos1, '\0', BUF_SIZE);
	memset(pos1, '\0', BUF_SIZE);

	logger = fopen("filler.log", "a");
	fprintf(logger, "parse\n");
	fclose(logger);

	request->symbol = *all;
	m += 2;

	do
	{
		*(pos1 + n) = *(all + m);
		m++;
		n++;
	}while(*(all + m - 1) != '\n');

	position = parse_size(pos1);
	request->map.h = position.x;
	request->map.w = position.y;

	request->map.array = (char **) malloc(request->map.h * sizeof(char*));

	logger=fopen("filler.log", "a");
	fprintf(logger, "first size: %d %d\n", request->map.h, request->map.w);
	fclose(logger);

	for(int i = 0; i < request->map.h; i++)
		request->map.array[i] = (char *) malloc((request->map.w + 1) * sizeof(char));

	for(int i = 0; i < request->map.h; i++)
		for(int j = 0; j < request->map.w + 1; j++)
		{
			*(*(request->map.array + i) + j) = *(all + m);
			logger = fopen("filler.log", "a");
			fprintf(logger, "%c", *(*(request->map.array + i)+j));
			fclose(logger);
			m++;
		}

	n = 0;

	do
	{
		*(pos2 + n) = *(all + m);
		m++;
		n++;
	}while(*(all + m - 1) != '\n');

	position = parse_size(pos2);
	request->elem.h = position.x;
	request->elem.w = position.y;

	request->elem.array = (char **) malloc(request->elem.h * sizeof(char*));

	logger = fopen("filler.log", "a");
	fprintf(logger, "second size: %d %d\n", request->elem.h, request->elem.w);
	fclose(logger);

	for(int i = 0; i < request->elem.h; i++)
		request->elem.array[i] = (char *)malloc((request->elem.w+1) * sizeof(char));

	for(int i = 0; i < request->elem.h; i++)
		for(int j = 0; j < request->elem.w +1; j++)
		{
			*(*(request->elem.array + i) + j) = *(all + m);
			logger = fopen("filler.log", "a");
			fprintf(logger, "%c", *(*(request->elem.array + i) + j));
			fclose(logger);
			m++;
		}

	logger = fopen("filler.log", "a");
	fprintf(logger, "end of parsing");
	fclose(logger);
	free(pos1);
	free(pos2);
	return request;
}

pos_t 		parse_size(char *answer)
{
	pos_t 	cur;
	int 	flag;
	char 	*c1 = NULL;
	char 	*c2 = NULL;
	int 	t1;
	int 	t2;
	FILE 	*logger;

	flag = 0;
	t1 = 0;
	t2 = 0;
	c1 = (char*) malloc(strlen(answer) * sizeof(char));
	c2 = (char*) malloc(strlen(answer) * sizeof(char));

	memset(c1, '\0', strlen(answer));
	memset(c2, '\0', strlen(answer));

	for(int i = 0; *(answer+i) != '\n'; i++)
	{
		if(*(answer+i) == ' ')
		{
			flag = 1;
			continue;
		}

		if(flag == 0)
		{
			*(c1 + t1) = *(answer+i);
			t1++;
		}

		if(flag == 1)
		{
			*(c2 + t2) = *(answer+i);
			t2++;
		}

	}

	cur.x = atoi(c1);
	cur.y = atoi(c2);

	logger = fopen("filler.log", "a");
	fprintf(logger, "c1 = %s, c2 = %s\n", c1, c2);
	fclose(logger);

	free(c1);
	free(c2);

	return cur;
}

int		find_size(char res[32], char *buf, int start_pos)
{
	int 	i;

	i = 0;

	do
	{
    		res[i] = buf[start_pos];
    		start_pos++;
    		i++;
  	}
  	while (buf[start_pos-1] != '\n');

	res[i] = '\0';
  	start_pos++;

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
        			if(buf->size <= pos + el_size.x*(el_size.y + 1))
          				return -1;
        			else return 0;
      			}
    		}
  	}

  	return -1;
}

void            read_input(filler_t* filler)
{
  	char    buffer[BUF_SIZE];
  	int     res;
	FILE 	*logger;

  	while(42)
  	{
      		memset(buffer, '\0', BUF_SIZE);
      		res = read(0, buffer, BUF_SIZE - 1);

      		if(!strlen(buffer))
		{
			logger = fopen("filler_new.log", "a");
      			fprintf(logger,"buffer: empty", buffer);
      			fclose(logger);
			break;
		}

		if(filler->current_stream == NULL)
       			filler->current_stream = string_create(buffer);
      		else
	      		string_append(filler->current_stream, buffer);
	}

	logger = fopen("filler_new.log", "a");
	fprintf(logger,"all buffer: %s\n", filler->current_stream->str);
	fclose(logger);
}

req_t       	*read_request(filler_t *filler)
{
	req_t   *req = NULL;

	read_input(filler);

	if(read_is_finished(filler->current_stream) == 0)
		req = parse_all(filler->current_stream->str);

	return req;
}
