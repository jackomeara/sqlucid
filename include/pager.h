#include "types.h"
#include <stdint.h>

#ifndef PAGER_H
#define PAGER_H

Pager *pager_open(const char *);
void *get_page(Pager *pager, uint32_t pager_open);
void pager_flush(Pager *pager, uint32_t page_num, uint32_t size);
#endif