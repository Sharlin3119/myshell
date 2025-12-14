#ifndef PARSE_H
#define PARSE_H

#define MAX_ARGS 64

char **parse_input(char *input);
void free_argv(char **argv);

#endif
