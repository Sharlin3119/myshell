#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include "signals.h"

void handle_sigchld(int sig) {
    (void)sig;
    int status;
    while (waitpid(-1, &status, WNOHANG) > 0) {
    }
}

void setup_signals() {
    signal(SIGINT, SIG_IGN);

    struct sigaction sa;
    sa.sa_handler = &handle_sigchld;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    sigaction(SIGCHLD, &sa, 0);
}
