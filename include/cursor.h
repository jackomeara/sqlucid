#include "types.h"

#ifndef CURSOR_H
#define CURSOR_H

Cursor *table_start(Table *table);
Cursor *table_end(Table *table);
void cursor_advance(Cursor *cursor);

#endif