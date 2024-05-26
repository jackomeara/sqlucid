#include <stdio.h>
#include <stdbool.h>
#include "input.h"
#include "parser.h"
#include "table.h"
#include <stdlib.h>
#include "execute.h"

void print_prompt() { printf("db > "); }

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Must supply a db filename.\n");
        exit(EXIT_SUCCESS);
    }

    char *filename = argv[1];
    Table *table = db_open(filename);

    InputBuffer *input_buffer = new_input_buffer();

    // enter REPL
    while (true)
    {
        print_prompt();
        read_input(input_buffer);

        // handle meta command
        if (input_buffer->buffer[0] == '.')
        {
            switch (do_meta_command(input_buffer, table))
            {
            case (META_COMMAND_SUCCESS):
                continue;
            case (META_COMMAND_UNRECOGNIZED_COMMAND):
                printf("Unrecognized command '%s'", input_buffer->buffer);
            }
        }

        // prepare sql statement
        Statement statement;
        switch (prepare_statement(input_buffer, &statement))
        {
        case (PREPARE_SUCCESS):
            break;
        case (PREPARE_SYNTAX_ERROR):
            printf("Syntax error. Could not parse statement.\n");
            continue;
        case (PREPARE_UNRECOGNIZED_STATEMENT):
            printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
        }

        // execute sql statement
        execute_statement(&statement, table);
    }
}