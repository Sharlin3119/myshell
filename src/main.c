#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse.h"
#include "execute.h"
#include "builtin.h"
#include "signals.h"
#include "logger.h"

#define MAX_INPUT_SIZE 1024

int main(void) {
    char input_buffer[MAX_INPUT_SIZE];
    
    setup_signals();
    init_logger();

    while (1) {
        printf("myshell> ");
        if (fgets(input_buffer, MAX_INPUT_SIZE, stdin) == NULL) {
            printf("\n");
            break;
        }

        size_t len = strlen(input_buffer);
        if (len > 0 && input_buffer[len - 1] == '\n') {
            input_buffer[len - 1] = '\0';
        }

        if (input_buffer[0] == '\0') continue;
        
        char raw_input_copy[MAX_INPUT_SIZE];
        strcpy(raw_input_copy, input_buffer);

        char **argv = parse_input(input_buffer);

        if (argv[0] != NULL) {
            if (!handle_builtin(argv)) {
                int background = 0;
                int i = 0;
                while (argv[i] != NULL) i++;
                if (i > 0 && strcmp(argv[i-1], "&") == 0) {
                    background = 1;
                    free(argv[i-1]);
                    argv[i-1] = NULL;
                }
                execute_command(argv, background, raw_input_copy);
            }
        }
        free_argv(argv);
    }
    
    close_logger();
    return 0;
}
