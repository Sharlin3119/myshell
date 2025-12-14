#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

char **parse_input(char *input) {
    char **argv = calloc(MAX_ARGS, sizeof(char *));
    if (!argv) {
        perror("malloc failed");
        exit(1);
    }

    int i = 0;
    char *token = strtok(input, " \t\n");

    while (token != NULL && i < MAX_ARGS - 1) {
        argv[i] = strdup(token); 
        i++;
        token = strtok(NULL, " \t\n");
    }

    argv[i] = NULL;
    return argv;
}

void free_argv(char **argv) {
    if (!argv) return;
    for (int i = 0; i < MAX_ARGS; i++) {
        if (argv[i] != NULL) {
            free(argv[i]);
        }
    }
    free(argv);
}
