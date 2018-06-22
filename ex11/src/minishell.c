#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include "../include/minishell.h"
#define BUF 1024
#define TOK " \t\r\n\a"

int export(char **args, hashtable_t *ht);
int sh_exit(char **args, hashtable_t *ht);
int env(char **args, hashtable_t *ht);
int ls(char ** args, hashtable_t *ht);
int echo(char **args,  hashtable_t *ht);
int launch(char **args);
int execute(char **args, hashtable_t *ht);

char *commands[] = {
  "export",
  "env",
  "ls",
  "echo",
  "exit"
};

int (*com_func[]) (char **, hashtable_t *) = {
  &export,
  &env,
  &ls,
  &echo,
  &sh_exit
};

int num_com() {
  return sizeof(commands) / sizeof(char *);
}

int export(char **args, hashtable_t *ht)
{
  int i;
  char *p, *key, *data, *word;

  if (!args[1])
    return 1;

  word = args[1];
  p = strtok(word, "=");
  key = malloc((strlen(p) + 1)  * sizeof(char));
  strcpy(key, p);

  while (p){
    data = malloc((strlen(p) + 1)  * sizeof(char));
    strcpy(data, p);
    p = strtok(NULL, "=");
  }
  if (!strcmp(key, data)){
    return 1;
  }
  hash_set(ht, key, (void *)data);
  write(1,"\n",1);
  return 1;
}

int env(char **args, hashtable_t *ht)
{
  write(1, "\n", 1);
  hash_print(ht);

  return 1;
}

int ls(char **args, hashtable_t *ht)
{
  struct dirent **name;
  int n;

  if(args[1] == NULL) {
    n = scandir(".", &name, NULL, alphasort);
  }
  else
    n = scandir(args[1], &name, NULL, alphasort);

  if(n < 0){
    write(1, "scandir", 7);
  }
  else {
    int i = 0;

    while (i < n) {
      if(strcmp(name[i]->d_name,".") && strcmp(name[i]->d_name,"..")){
        write(1, name[i]->d_name, strlen(name[i]->d_name));
        if (i != n - 1)
          write(1, " ", 1);
      }

      free(name[i]);
      ++i;
    }
  }

  free(name);
  write(1, "\n", 1);

  return 1;
}

static void echo_out(char **str, int pos, hashtable_t *ht)
{
	int	str_len;
  char *dest;

  str_len = strlen(str[pos]);
  dest = malloc((str_len + 1) * (sizeof(char)));

  if (str[pos][0] == '$'){
    strcpy(dest, hash_get(ht, str[pos] + 1));
    write(1, dest, str_len + 1);
  }
  else {
    write(1, str[pos], str_len);
  }

	if (str[pos + 1])
    write(1, " ", 1);

  free(dest);
}

int echo(char **args, hashtable_t *ht)
{
	int i;

	if (!args[0]) {
		write(1, "\n", 1);
		return 1;
	}

	i = 0;

	while (args[++i]) {
    echo_out(args, i, ht);
		if (!args[i + 1] )
      write(1, "\n", 1);
	}

	return 1;
}

int sh_exit(char **args, hashtable_t *ht)
{
  write(1, "\n", 1);
  return 0;
}

char *read_line()
{
  int buf, pos, c;
  char *bufr;

  buf = BUF;
  pos = 0;

  bufr = malloc(sizeof(char) * buf);

  if (!bufr) {
    write(1, "allocation error\n", 16);
    write(1, "\n", 1);
    exit(EXIT_FAILURE);
  }

  while (1) {
    c = getchar();

    if (c == EOF || c == '\n') {
      bufr[pos] = '\0';
      return bufr;
    } else {
      bufr[pos] = c;
    }

    pos++;

    if (pos >= buf) {
      buf += BUF;
      bufr = realloc(bufr, buf);
      if (!bufr) {
        write(1, "allocation error\n", 16);
        write(1, "\n", 1);
        exit(EXIT_FAILURE);
      }
    }
  }
  free(bufr);
}

char **split_line(char *ln)
{
  int pos, bufsize;
  char **args;
  char *arg;

  pos = 0;
  bufsize = 64;
  args = malloc(bufsize * sizeof(char *));

  if (!args) {
    write(1, "allocation error\n", 16);
    write(1, "\n", 1);
    exit(EXIT_FAILURE);
  }

  arg = strtok(ln, TOK);

  while (arg != NULL) {
    args[pos] = arg;
    pos++;

    if (pos >= bufsize) {
      bufsize += 64;
      args = realloc(args, bufsize * sizeof(char*));

      if (!args) {
        write(1, "allocation error\n", 16);
        write(1, "\n", 1);
        exit(EXIT_FAILURE);
      }
    }

    arg = strtok(NULL, TOK);
  }

  args[pos] = NULL;

  return args;
}

int execute(char **args, hashtable_t *ht)
{
  int i;

  if (args[0] == NULL) {
    return 1;
  }

  for (i = 0; i < num_com(); i++) {
    if (strcmp(args[0], commands[i]) == 0) {
      return (*com_func[i])(args, ht);
    }
  }

  return launch(args);
}

int launch(char **args)
{
  pid_t pid, wpid;
  int status;

  pid = fork();
  if (pid == 0) {
    if (execvp(args[0], args) == -1) {
      write(1, "minishell", 9);
      write(1, "\n", 1);
    }

    exit(EXIT_FAILURE);
  } else if (pid < 0) {
    write(1, "minishell", 9);
    write(1, "\n", 1);
  } else {
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }

  return 1;
}

void signal_handler(int sign) {
	if (sign == SIGINT) {
		puts("");
    write(1,"$_>",3);
		signal(SIGINT, signal_handler);
	}
}

void _loop(void)
{
  char *line;
  char **args;
  int status;
  hashtable_t *ht;

  ht = hash_create(64);
  do {
    write(1, "$_>", 3);
    signal(SIGINT, signal_handler);
    line = read_line();
    args = split_line(line);
    status = execute(args, ht);
    free(line);
    free(args);
  } while (status);

  write(1, "\n", 1);
  hash_destroy(ht);
}

int  main(int argc, char **argv)
{
     _loop();
     return EXIT_SUCCESS;
}

