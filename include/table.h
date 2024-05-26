#include "types.h"

#ifndef TABLE_H
#define TABLE_H

void serialize_row(Row *, void *);
void deserialize_row(void *, Row *);

void *cursor_value(Cursor *);
Table *db_open(char *);
void db_close(Table *table);

uint32_t TABLE_MAX_ROWS;
uint32_t PAGE_SIZE;

#endif
