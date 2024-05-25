#include "types.h"
#include <stdlib.h>
#include "table.h"

void print_row(Row *row) { printf("(%d, %s)\n", row->id, row->username); }

ExecuteResult execute_add(Statement *statement, Table *table)
{
    if (table->num_rows >= TABLE_MAX_ROWS)
    {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_add = &(statement->row_to_add);

    serialize_row(row_to_add, row_slot(table, table->num_rows));
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_get(Statement *statement, Table *table)
{
    Row row;

    for (uint32_t i = 0; i < table->num_rows; i++)
    {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_delete(Statement *statement)
{
    printf("Delete will be done here.\n");

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_statement(Statement *statement, Table *table)
{
    switch (statement->type)
    {
    case (STATEMENT_ADD):
        return execute_add(statement, table);
    case (STATEMENT_GET):
        return execute_get(statement, table);
    case (STATEMENT_DELETE):
        return execute_delete(statement);
    }
    return EXECUTE_SUCCESS;
}