#include "types.h"
#include <stdlib.h>

void print_row(Row *row) { printf("(%d, %s)", row->id, row->username); }

ExecuteResult execute_add(Statement *statement)
{
    printf("Add will be done here.\n");

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_get(Statement *statement)
{
    printf("Get will be done here.\n");

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
    case (STATEMENT_ADD):
        return execute_add(statement);
    case (STATEMENT_GET):
        return execute_get(statement);
    case (STATEMENT_DELETE):
        return execute_delete(statement);
    }
    return EXECUTE_SUCCESS;
}