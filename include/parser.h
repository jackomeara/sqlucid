#include "types.h"

#ifndef PARSER_H
#define PARSER_H

MetaCommandResult do_meta_command(InputBuffer *);
PrepareResult prepare_statement(InputBuffer *, Statement *);

#endif