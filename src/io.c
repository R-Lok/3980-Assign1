#include "../include/io.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

ssize_t readFully(int fd, char *buffer, size_t count, int *err);
ssize_t writeFully(int fd, const char *buffer, size_t count, int *err);

int processText(int inputFd, int outputFd, filter_func func)
{
    char    buffer;
    int     err = 0;
    char    transformedChar;
    ssize_t readRes;

    while((readRes = readFully(inputFd, &buffer, 1, &err)) != 0)
    {
        ssize_t writeRes;
        if(readRes == -1)
        {
            perror("Read error");
            return (EXIT_FAILURE);
        }
        transformedChar = func(buffer);
        writeRes        = writeFully(outputFd, &transformedChar, 1, &err);
        if(writeRes == -1)
        {
            perror("Write error");
            return (EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
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

ssize_t writeFully(int fd, const char *buffer, size_t count, int *err)
{
    size_t bytes_written = 0;

    while(bytes_written < count)
    {
        ssize_t result = write(fd, buffer + bytes_written, count - bytes_written);
        if(result == -1)
        {
            if(errno == EINTR)
            {
                continue;
            }
            *err = errno;
            return -1;
        }
        bytes_written += (size_t)result;
    }
    return (ssize_t)bytes_written;
}
