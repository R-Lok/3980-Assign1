#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int checkValidArgs(const char *filter, const char *input, const char *output);

int main(int argc, char **argv)
{
    int opt;

    const char *filterMode = NULL;
    const char *inputFile  = NULL;
    const char *outputFile = NULL;

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
                filterMode = optarg;
                printf("Filter option: %s\n", filterMode);
                break;
            case ':':
                printf("Required argument missing for option %c \n", optopt);
                exit(1);
            default:
                printf("This should not print - please check the code");
                break;
        }
    }

    if(checkValidArgs(filterMode, inputFile, outputFile))
    {
        perror("Please run the program through: ./build/assign1 -i <inputFileName> -o <outputFileName> -f <upper/lower/null>");
        exit(1);
    }

    return EXIT_SUCCESS;
}

int checkValidArgs(const char *filter, const char *input, const char *output)
{
    if(!filter || !input || !output)
    {
        return 1;
    }
    return 0;
}
