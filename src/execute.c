#include "types.h"
#include <stdlib.h>

void print_row(Row *row) { printf("(%d, %s)", row->id, row->username); }

ExecuteResult execute_insert(Statement *statement)
{
    printf("Insert will be done here.\n");

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(Statement *statement)
{
    printf("Select will be done here.\n");

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_delete(Statement *statement)
{
    printf("Delete will be done here.\n");

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *statement)
{
    switch (statement->type)
    {
    case (STATEMENT_INSERT):
        return execute_insert(statement);
    case (STATEMENT_SELECT):
        return execute_select(statement);
    case (STATEMENT_DELETE):
        return execute_delete(statement);
    }
    return EXECUTE_SUCCESS;
}