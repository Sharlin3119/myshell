#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"

char **parse_input(char *input) {
    // Allocate memory for the array of pointers (max 64 args)
    // We use calloc to ensure everything is initialized to NULL
    char **argv = calloc(MAX_ARGS, sizeof(char *));
    if (!argv) {
        perror("malloc failed");
        exit(1);
    }

    int i = 0;
    // strtok chops the string by " " (space), "\t" (tab), or "\n" (newline)
    char *token = strtok(input, " \t\n");

    while (token != NULL && i < MAX_ARGS - 1) {
        // Duplicate the string so we own the memory (deep copy)
        argv[i] = strdup(token); 
        i++;
        token = strtok(NULL, " \t\n"); // Get next token
    }

    argv[i] = NULL; // The list must end with NULL for execvp
    return argv;
}

void free_argv(char **argv) {
    if (!argv) return;

    // Loop through the array and free every string we strdup'ed
    for (int i = 0; argv[i] != NULL; i++) {
        free(argv[i]);
    }
    
    // Finally, free the array itself
    free(argv);
}
