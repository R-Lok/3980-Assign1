#ifndef IO_H
#define IO_H
#include "filters.h"

int processText(int inputFd, int outputFd, filter_func func);
#endif
