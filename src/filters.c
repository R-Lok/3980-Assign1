#include "../include/filters.h"

char upper_filter(char c)
{
    if(c >= 97 && c <= 122)
    {
        return c - 32;
    }
    return c;
}

char lower_filter(char c)
{
    if(c >= 65 && c <= 90)
    {
        return c + 32;
    }
    return c;
}

char null_filter(char c)
{
    return c;
}
