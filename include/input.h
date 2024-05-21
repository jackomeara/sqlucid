#ifndef INPUT_H
#define INPUT_H

#include "types.h"

InputBuffer *new_input_buffer();
void read_input(InputBuffer *);
void close_input_buffer(InputBuffer *);

#endif