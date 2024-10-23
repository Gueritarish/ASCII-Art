#include "utils.h"

#include <stdio.h>
#include <string.h>

int end_with(char *string, char* end)
{
    size_t str_size = strlen(string);
    size_t end_size = strlen(end);
    if (end_size > str_size)
        return 0;

    for (size_t i = str_size - end_size, j = 0; i < str_size; i++, j++)
    {
        if (string[i] != end[j])
            return 0;
    }
    return 1;
}