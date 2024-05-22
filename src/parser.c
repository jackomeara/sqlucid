#include <stdlib.h>
#include <string.h>
#include "input.h"

// execute meta command such as exit program, list tables
MetaCommandResult do_meta_command(InputBuffer *input_buffer)
{
    if (strcmp(input_buffer->buffer, ".exit") == 0)
    {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    }
    else
    {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement)
{
    if (strncmp(input_buffer->buffer, "add", 3) == 0)
    {
        statement->type = STATEMENT_ADD;
        int args_assigned = sscanf(
            input_buffer->buffer, "add %d %s", &(statement->row_to_add.id),
            statement->row_to_add.username);

        if (args_assigned < 2)
        {
            return PREPARE_SYNTAX_ERROR;
        }

        return PREPARE_SUCCESS;
    }

    if (strncmp(input_buffer->buffer, "delete", 6) == 0)
    {
        statement->type = STATEMENT_DELETE;
        return PREPARE_SUCCESS;
    }

    if (strcmp(input_buffer->buffer, "get") == 0)
    {
        statement->type = STATEMENT_GET;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}