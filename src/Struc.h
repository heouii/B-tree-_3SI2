#ifndef STRUCT_H
#define STRUCT_H

#include <stddef.h>

typedef enum {
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;

typedef enum {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;

typedef enum {
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_DELETE,
    STATEMENT_CREATE_TABLE,
    STATEMENT_UPDATE
} StatementType;

typedef struct {
    char table_name[32];
    int id;
    char column_name[32];
    char column_value[64];
    StatementType type;
} Statement;

typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

#endif
