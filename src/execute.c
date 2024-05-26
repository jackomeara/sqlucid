#include "types.h"
#include <stdlib.h>
#include "table.h"
#include "cursor.h"

void print_row(Row *row) { printf("(%d, %s)\n", row->id, row->username); }

ExecuteResult execute_add(Statement *statement, Table *table)
{
    if (table->num_rows >= TABLE_MAX_ROWS)
    {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_add = &(statement->row_to_add);
    Cursor *cursor = table_end(table);

    serialize_row(row_to_add, cursor_value(cursor));
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_get(Statement *statement, Table *table)
{
    Cursor *cursor = table_start(table);
    Row row;
    while (!cursor->end_of_table)
    {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }

    free(cursor);

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