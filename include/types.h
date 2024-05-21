#include <stdio.h>

#ifndef TYPES_H
#define TYPES_H

// InputBuffer handles user query / command input
typedef struct
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

#endif