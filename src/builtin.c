#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

int handle_builtin(char **argv) {
    if (strcmp(argv[0], "exit") == 0 || strcmp(argv[0], "quit") == 0) {
        exit(0);
    }
    if (strcmp(argv[0], "cd") == 0) {
        if (argv[1] == NULL) {
            chdir(getenv("HOME")); 
        } else {
            if (chdir(argv[1]) != 0) {
                perror("myshell");
            }
        }
        return 1;
    }
    return 0;
}
