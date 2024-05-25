#include "types.h"

#ifndef PARSER_H
#define PARSER_H

MetaCommandResult do_meta_command(InputBuffer *, Table *table);
PrepareResult prepare_statement(InputBuffer *, Statement *);

#endif