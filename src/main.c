#include "../include/io.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int checkValidArgs(filter_func filter, const char *input, const char *output);

int main(int argc, char **argv)
{
    int         opt;
    filter_func filter     = NULL;
    const char *inputFile  = NULL;
    const char *outputFile = NULL;
    int         inputFd;
    int         outputFd;
    const int   filePerms = 0644;

    while((opt = getopt(argc, argv, ":i:o:f:")) != -1)
    {
        switch(opt)
        {
            case 'i':
                inputFile = optarg;
                printf("Input file: %s\n", inputFile);
                break;
            case 'o':
                outputFile = optarg;
                printf("Output file: %s\n", outputFile);
                break;
            case 'f':
                filter = selectFilter(optarg);
                printf("Filter option: %s\n", optarg);
                break;
            case ':':
                perror("Required argument missing for an option");
                exit(1);
            default:
                printf("Useless flag entered: %c\n", optopt);
                break;
        }
    }

    if(checkValidArgs(filter, inputFile, outputFile))
    {
        errno = EINVAL;
        perror("Please run the program through: ./build/assign1 -i <inputFileName> -o <outputFileName> -f <upper/lower/null>");
        exit(1);
    }
    inputFd = open(inputFile, O_RDONLY | O_CLOEXEC);
    if(inputFd == -1)
    {
        perror("Error opening input file.");
        return EXIT_FAILURE;
    }

    outputFd = open(outputFile, O_CREAT | O_WRONLY | O_TRUNC | O_CLOEXEC, filePerms);
    if(outputFd == -1)
    {
        perror("Error opening output file.");
        close(inputFd);
        return EXIT_FAILURE;
    }

    if(processText(inputFd, outputFd, filter) == EXIT_FAILURE)
    {
        perror("Write/Read error in processText()");
        goto failure;
    }

    if(close(inputFd) == -1 || close(outputFd) == -1)
    {
        perror("error during closing of files");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

failure:
    if(close(inputFd) == -1 || close(outputFd) == -1)
    {
        perror("error during closing of files");
        return EXIT_FAILURE;
    }
    return EXIT_FAILURE;
}

int checkValidArgs(filter_func filter, const char *input, const char *output)
{
    if(!filter || !input || !output)
    {
        return 1;
    }
    return 0;
}
