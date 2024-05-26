#include "types.h"

#ifndef TABLE_H
#define TABLE_H

void serialize_row(Row *, void *);
void deserialize_row(void *, Row *);

void *row_slot(Table *, uint32_t);
Table *db_open(char *);
void db_close(Table *table);

uint32_t TABLE_MAX_ROWS;
uint32_t PAGE_SIZE;

#endif
