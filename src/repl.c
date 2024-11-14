#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "btree.h"
#include "struc.h" 
#include "repl.h"


InputBuffer* new_input_buffer() 
{
 
     InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
  
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
  
  
    return input_buffer;
}

void print_prompt() {
    printf("db > ");
}

void read_input(InputBuffer* input_buffer) {
    size_t buffer_size = 1024;
    input_buffer->buffer = malloc(buffer_size);

    if (!fgets(input_buffer->buffer, buffer_size, stdin)) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = strlen(input_buffer->buffer) - 1;
    input_buffer->buffer[input_buffer->input_length] = '\0';
}

void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}


MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}


PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
        statement->type = STATEMENT_INSERT;
        
        int assigned = sscanf(input_buffer->buffer, "insert %d %s %s", &(statement->id), statement->name, statement->breed);
        if (assigned < 3) {
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        return PREPARE_SUCCESS;
    }
    if (strcmp(input_buffer->buffer, "select") == 0) {
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}


void execute_insert(Statement* statement, TreeNode** root) {

    *root = insert(*root,  statement->name, statement->breed);

    printf("Executed insert:Name=%s Breed=%s\n", statement->name, statement->breed);
}

void execute_select(TreeNode* root) {
    printf("Executing select:\n");
    inorder(root);
}



// Fonction REPL

//Implementer le prepare statement
//Affichage minimum
void repl(void) {
    InputBuffer* input_buffer = new_input_buffer();
    TreeNode* root = NULL;
    while (true) {
        print_prompt();


        read_input(input_buffer);

        if (input_buffer->buffer[0] == '.') {

            switch (do_meta_command(input_buffer)) {

                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:


                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }
         Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENT:
                printf("Unknow keyword '%s'.\n", input_buffer->buffer);
                continue;
        }

        execute_statement(&statement);

       
        printf("Executed.\n");
    }
}
