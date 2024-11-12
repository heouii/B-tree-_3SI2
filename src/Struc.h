#ifndef STRUCT_H
#define STRUCT_H

#include <stddef.h> //pour size_t

typedef enum 
{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
} MetaCommandResult;



 typedef enum 
 {

     PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
} PrepareResult;



typedef enum 
{
    STATEMENT_INSERT,
    STATEMENT_SELECT
} StatementType;




typedef struct 
{
    StatementType type;
    int id;
    char name[32];
    char breed[32];
} Statement;




typedef struct {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

#endif 



    