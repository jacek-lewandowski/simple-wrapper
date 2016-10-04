#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedImportStatement"

#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <err.h>
#include <wait.h>
#include <stdarg.h>
#include "utils.h"

int read_status(int *pipe)
{
    char buf[1];
    buf[0] = (char) 0;
    int ret = (int) read(pipe[0], buf, 1);
    if (ret <= 0)
        log_error("Error while reading from a pipe");
    else if (buf[0] != (char) 1)
        log_error("Read invalid status");
    else
        return 0;

    return -1;
}

int write_status(int *pipe)
{
    char buf[1];
    buf[0] = (char) 1;
    int ret = (int) write(pipe[1], buf, 1);
    if (ret <= 0)
        log_error("Error while writing to a pipe");
    else
        return 0;

    return -1;
}

void close_input(int *pipe)
{
    close(pipe[0]);
}

void close_output(int *pipe)
{
    close(pipe[1]);
}

int wait_for_child(int pid, int &status)
{
    int ret = waitpid(pid, &status, __WALL);
    if (ret < 0)
        log_error("Failed waiting for child process to terminate %d", ret);
    else
        return 0;

    return -1;
}

void log_error(const char *fmt, ...)
{
    // similar to perror but it doesn't print success if errno does not
    // indicate an error; additionally allows to provide a formatted string
    // as opposed to perror.
    va_list args;
    va_start(args, fmt);
    if (errno) vwarn(fmt, args); else vwarnx(fmt, args);
    va_end(args);
}

#pragma clang diagnostic pop
