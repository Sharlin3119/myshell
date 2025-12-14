#ifndef LOGGER_H
#define LOGGER_H

#include <sys/types.h>

void init_logger();

void log_command(char *raw_cmd, pid_t pid, int status);

void close_logger();

#endif
