#include "constants.h"
#include "types.h"
#include <stdint.h>
#include <stdlib.h>
#include "string.h"
#include "pager.h"
#include <fcntl.h>

const uint32_t ID_OFFSET = 0;
const uint32_t PAGE_SIZE = 4096;

uint32_t ID_SIZE;
uint32_t USERNAME_SIZE;
uint32_t USERNAME_OFFSET;
uint32_t ROW_SIZE;
uint32_t ROWS_PER_PAGE;
uint32_t TABLE_MAX_ROWS;

Table *db_open(const char *filename)
{
    // initialise constants
    ID_SIZE = size_of_attribute(Row, id);
    USERNAME_SIZE = size_of_attribute(Row, username);
    USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
    ROW_SIZE = ID_SIZE + USERNAME_SIZE;
    ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
    TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;

    // init pager
    Pager *pager = pager_open(filename);
    uint32_t num_rows = pager->file_length / ROW_SIZE;

    Table *table = (Table *)malloc(sizeof(Table));
    table->pager = pager;
    table->num_rows = num_rows;
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        pager->pages[i] = NULL;
    }
    return table;
}

void db_close(Table *table)
{
    Pager *pager = table->pager;
    uint32_t num_full_pages = table->num_rows / ROWS_PER_PAGE;

    for (uint32_t i = 0; i < num_full_pages; i++)
    {
        if (pager->pages[i] == NULL)
        {
            continue;
        }
        pager_flush(pager, i, PAGE_SIZE);
        free(pager->pages[i]);
        pager->pages[i] = NULL;
    }

    // partial page to write to end of file
    uint32_t num_additional_rows = table->num_rows % ROWS_PER_PAGE;
    if (num_additional_rows > 0)
    {
        uint32_t page_num = num_full_pages;
        if (pager->pages[page_num] != NULL)
        {
            pager_flush(pager, page_num, num_additional_rows * ROW_SIZE);
            free(pager->pages[page_num]);
            pager->pages[page_num] = NULL;
        }
    }
    int result = _close(pager->file_descriptor);
    if (result == -1)
    {
        printf("Error closing db file.\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < TABLE_MAX_PAGES; i++)
    {
        void *page = pager->pages[i];
        if (page)
        {
            free(page);
            pager->pages[i] = NULL;
        }
    }
    free(pager);
    free(table);
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
    void *page = get_page(table->pager, page_num);
    uint32_t row_offset = row_num % ROWS_PER_PAGE;
    uint32_t byte_offset = row_offset * ROW_SIZE;
    return page + byte_offset;
}