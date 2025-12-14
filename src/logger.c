#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include "logger.h"

static int log_fd = -1;

void init_logger() {
    log_fd = open("myshell.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd < 0) {
        perror("Logger failed");
    }
}

void log_command(char *raw_cmd, pid_t pid, int status) {
    if (log_fd < 0) return;
    char buffer[256];
    int len = snprintf(buffer, sizeof(buffer), "[pid=%d] cmd=\"%s\" status=%d\n", pid, raw_cmd, status);
    write(log_fd, buffer, len);
}

void close_logger() {
    if (log_fd >= 0) close(log_fd);
}
