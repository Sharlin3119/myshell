#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include "execute.h"
#include "logger.h"

void run_single_command(char **argv) {
    char *input_file = NULL;
    char *output_file = NULL;
    int append_mode = 0;

    int i = 0;
    while (argv[i] != NULL) {
        if (strcmp(argv[i], "<") == 0) {
            input_file = argv[i+1];
            argv[i] = NULL;
        } else if (strcmp(argv[i], ">") == 0) {
            output_file = argv[i+1];
            append_mode = 0;
            argv[i] = NULL;
        } else if (strcmp(argv[i], ">>") == 0) {
            output_file = argv[i+1];
            append_mode = 1;
            argv[i] = NULL;
        }
        i++;
    }

    if (input_file != NULL) {
        int fd = open(input_file, O_RDONLY);
        if (fd < 0) { perror("open input"); exit(1); }
        dup2(fd, STDIN_FILENO);
        close(fd);
    }

    if (output_file != NULL) {
        int fd;
        if (append_mode) 
            fd = open(output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
        else 
            fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        
        if (fd < 0) { perror("open output"); exit(1); }
        dup2(fd, STDOUT_FILENO);
        close(fd);
    }

    signal(SIGINT, SIG_DFL);

    if (execvp(argv[0], argv) < 0) {
        perror("myshell");
        exit(1);
    }
}

void execute_command(char **argv, int background, char *raw_input) {
    int pipe_index = -1;
    for (int i = 0; argv[i] != NULL; i++) {
        if (strcmp(argv[i], "|") == 0) {
            pipe_index = i;
            break;
        }
    }

    if (pipe_index != -1) {
        argv[pipe_index] = NULL;
        char **argv_left = argv;
        char **argv_right = &argv[pipe_index + 1];

        int fd[2];
        if (pipe(fd) == -1) { perror("pipe"); return; }

        pid_t pid1 = fork();
        if (pid1 == 0) {
            dup2(fd[1], STDOUT_FILENO);
            close(fd[0]); close(fd[1]);
            run_single_command(argv_left);
        }

        pid_t pid2 = fork();
        if (pid2 == 0) {
            dup2(fd[0], STDIN_FILENO);
            close(fd[1]); close(fd[0]);
            run_single_command(argv_right);
        }

        close(fd[0]); close(fd[1]);
        
        log_command(raw_input, pid1, 0); 
        waitpid(pid1, NULL, 0);
        waitpid(pid2, NULL, 0);
        return;
    }

    pid_t pid = fork();
    if (pid == 0) {
        run_single_command(argv);
    } else {
        if (background) {
            printf("[bg] started pid %d\n", pid);
            log_command(raw_input, pid, 0); 
        } else {
            int status;
            waitpid(pid, &status, 0);
            log_command(raw_input, pid, status); 
        }
    }
}
