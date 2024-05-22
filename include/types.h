#include <stdio.h>
#include <stdint.h>

#ifndef TYPES_H
#define TYPES_H

// InputBuffer handles user query / command input
typedef struct
{
    char *buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

// prepare statement result status
typedef enum
{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT,
    PREPARE_SYNTAX_ERROR
} PrepareResult;

// meta command status
typedef enum
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

// command execution result status
typedef enum
{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL
} ExecuteResult;

// sql statement mode types
typedef enum
{
    STATEMENT_ADD,
    STATEMENT_GET,
    STATEMENT_DELETE
} StatementType;

// table row object
typedef struct
{
    uint32_t id;
    char username[32];
} Row;

// sql statement object
typedef struct
{
    StatementType type;
    Row row_to_add;
} Statement;

#endif