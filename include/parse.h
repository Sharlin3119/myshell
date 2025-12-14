#ifndef PARSE_H
#define PARSE_H

#define MAX_ARGS 64

// Parses a raw input string into an array of tokens (argv)
// Returns a dynamically allocated array of strings
char **parse_input(char *input);

// Frees the memory allocated by parse_input
void free_argv(char **argv);

#endif
