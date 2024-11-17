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
        
        int assigned = sscanf(input_buffer->buffer, "insert  %s %s", statement->name, statement->breed);
        if (assigned < 2) {
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

void execute_statement(Statement* statement, TreeNode** root);

void execute_insert(Statement* statement, TreeNode** root) {

    

    *root = insert(*root,  statement->name, statement->breed);

    printf("Executed insert:Name=%s Breed=%s\n", statement->name, statement->breed);
}

void execute_select(TreeNode* root) {


    printf("Executing select:\n");
    inorder(root);
}
 
 
 void save_tree( TreeNode* root, FILE* file) {
    if ( root != NULL) {


        fprintf(file, "%d,%s,%s\n", root->id, root->name, root->breed);
        
        save_tree ( root->left, file);
        save_tree( root->right, file);
    }
}

void execute_statement(Statement* statement, TreeNode** root) {
    switch (statement->type) {


        case (STATEMENT_INSERT):
            execute_insert(statement, root);
            break;
        case (STATEMENT_SELECT):
            execute_select(*root);
            break;
    }


   
/////////////////////////////////////////////////////////////////////////////////// Fonction REPL //////////////////////////////////////////////////////////////////////

}
//Affichage minimum
bool running = true; 

void repl(void) {


    InputBuffer* input_buffer = new_input_buffer();
    TreeNode* root = load_tree("database.txt"); 

    printf(root != NULL ? "Database loaded successfully.\n"
                        : "Starting with an empty database.\n");

    while (running) {


        print_prompt();
        read_input(input_buffer);

        if (strcmp(input_buffer->buffer, "exit") == 0) {
            close_input_buffer(input_buffer);
            running = false;  
        } else if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        } else {
            Statement statement;
            switch (prepare_statement(input_buffer, &statement)) {


                case PREPARE_SUCCESS:

                    break;
                case PREPARE_UNRECOGNIZED_STATEMENT:

                    printf("Unknown keyword '%s'.\n", input_buffer->buffer);
                    continue;
            }
            execute_statement(&statement, &root);
            printf("Executed.\n");
        }
    }

    FILE* file = fopen("database.txt", "w");
    if (file) {


        save_tree(root, file);
        fclose(file);
        printf("Database saved to file\n");
    } else {


        perror("Error: Couldn't open file to save");
    }
}
