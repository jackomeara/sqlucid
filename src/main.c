#include <stdio.h>
#include <stdbool.h>
#include "input.h"

void print_prompt() { printf("db > "); }

int main()
{
    InputBuffer *input_buffer = new_input_buffer();

    // enter REPL
    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        // handle meta command

        // prepare sql statement

        // execute sql statement
    }
}