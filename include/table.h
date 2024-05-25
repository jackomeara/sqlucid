#include "types.h"

#ifndef TABLE_H
#define TABLE_H

void serialize_row(Row *, void *);
void deserialize_row(void *, Row *);

void *row_slot(Table *, uint32_t);
Table *new_table();

void free_table(Table *);

uint32_t TABLE_MAX_ROWS;

#endif
