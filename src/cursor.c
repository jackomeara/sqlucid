#include "types.h"
#include <stdlib.h>
#include <stdbool.h>

// create cursor at start of table
Cursor *table_start(Table *table)
{
    Cursor *cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->row_num = 0;
    cursor->end_of_table = (table->num_rows == 0);

    return cursor;
}

// create cursor at end of table
Cursor *table_end(Table *table)
{
    Cursor *cursor = malloc(sizeof(Cursor));
    cursor->table = table;
    cursor->row_num = table->num_rows;
    cursor->end_of_table = true;

    return cursor;
}

// move cursor down the table
void cursor_advance(Cursor *cursor)
{
    cursor->row_num += 1;
    if (cursor->row_num >= cursor->table->num_rows)
    {
        cursor->end_of_table = true;
    }
}