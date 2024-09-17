#include "../include/io.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ssize_t readFully(int fd, char *buffer, size_t count, int *err);
ssize_t writeFully(int fd, char *buffer, size_t count, int *err);

int processText(int inputFd, int outputFd, filter_func func)
{
    char buffer;
    int  err = 0;
    char filteredChar;

    ssize_t result = readFully(inputFd, &buffer, 1, &err);
    if(result == -1)
    {
        fprintf(stderr, "Read error: %s (error num: %d)", strerror(err), err);
        return (EXIT_FAILURE);
    }
    filteredChar = func(buffer);
}

ssize_t readFully(int fd, char *buffer, size_t count, int *err)
{
    size_t bytes_read = 0;

    while(bytes_read < count)
    {
        ssize_t result = read(fd, buffer + bytes_read, count - bytes_read);
        if(result == 0)
        {
            break;
        }
        if(result == -1)
        {
            if(errno == EINTR)
            {
                continue;
            }
            *err = errno;
            return -1;
        }
        bytes_read += (size_t)result;
    }
    return (ssize_t)bytes_read;
}
