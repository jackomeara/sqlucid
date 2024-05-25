#include "constants.h"
#include "types.h"
#include <stdint.h>
#include <stdlib.h>
#include "string.h"

const uint32_t ID_OFFSET = 0;
const uint32_t PAGE_SIZE = 4096;

uint32_t ID_SIZE;
uint32_t USERNAME_SIZE;
uint32_t USERNAME_OFFSET;
uint32_t ROW_SIZE;
uint32_t ROWS_PER_PAGE;
uint32_t TABLE_MAX_ROWS;

Table *new_table()
{
    // initialise constants
    ID_SIZE = size_of_attribute(Row, id);
    USERNAME_SIZE = size_of_attribute(Row, username);
    USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
    ROW_SIZE = ID_SIZE + USERNAME_SIZE;
    ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
    TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

    Table *table = (Table *)malloc(sizeof(Table));
    table->num_rows = 0;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        table->pages[i] = NULL;
    }
    return table;
}

// move row object into memory
void serialize_row(Row *source, void *destination)
{
    memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
    memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
}

// retrieve row object from memory
void deserialize_row(void *source, Row *destination)
{
    memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
    memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
}

// access the slot for a specific row in a table
void *row_slot(Table *table, uint32_t row_num)
{
    uint32_t page_num = row_num / ROWS_PER_PAGE;
    void *page = table->pages[page_num];
    if (page == NULL)
    {
        // allocate mem when trying to access page
        page = table->pages[page_num] = malloc(PAGE_SIZE);
    }
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}

// free table in memory
void free_table(Table *table)
{
    for (int i = 0; table->pages[i]; i++)
    {
        free(table->pages[i]);
    }
    free(table);
}