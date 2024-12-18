#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "btree.h"
#include "struc.h"
#include "repl.h"
#include "table.h"

// Initialize new buffer for user input
InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = (InputBuffer*)malloc(sizeof(InputBuffer));
    // buffer to hold the command line entered by user
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

// Display the prompt
void print_prompt() {
    printf("db > ");
}

// Read the user input and store in buffer
void read_input(InputBuffer* input_buffer) {
    size_t buffer_size = 1024;
    input_buffer->buffer = malloc(buffer_size);

    // Read line from stdin and check if success
    if (!fgets(input_buffer->buffer, buffer_size, stdin)) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    // We remove the newline from the end and add '\0'
    input_buffer->input_length = strlen(input_buffer->buffer) - 1;
    input_buffer->buffer[input_buffer->input_length] = '\0';
}

// Close and clean up the buffer
void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}

// Handle special commands starting with a dot (meta command)
MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
    if (strcmp(input_buffer->buffer, ".exit") == 0) {
        close_input_buffer(input_buffer);
        exit(EXIT_SUCCESS);
    } else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

// Prepare the statement for execution
PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
    char* keyword = strtok(input_buffer->buffer, " ");

    if (strcasecmp(keyword, "insert") == 0) {
        char* into = strtok(NULL, " ");
        char* table_name = strtok(NULL, " ");
        // Simple syntax checking
        if (!into || strcmp(into, "into") != 0 || !table_name) {
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        strcpy(statement->table_name, table_name);
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }

    if (strcasecmp(keyword, "select") == 0) {
        char* from = strtok(NULL, " ");
        char* table_name = strtok(NULL, " ");
        if (!from || strcmp(from, "from") != 0 || !table_name) {
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        strcpy(statement->table_name, table_name);
        statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }

    if (strcasecmp(keyword, "create") == 0) {
        char* table_keyword = strtok(NULL, " ");
        char* table_name = strtok(NULL, " ");
        if (!table_keyword || strcmp(table_keyword, "table") != 0 || !table_name) {
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        strcpy(statement->table_name, table_name);
        statement->type = STATEMENT_CREATE_TABLE;
        return PREPARE_SUCCESS;
    }

    if (strcasecmp(keyword, "delete") == 0) {
        char* from = strtok(NULL, " ");
        char* table_name = strtok(NULL, " ");
        char* id_str = strtok(NULL, " ");
        if (!from || strcmp(from, "from") != 0 || !table_name || !id_str) {
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        int id = atoi(id_str);
        strcpy(statement->table_name, table_name);
        statement->id = id;
        statement->type = STATEMENT_DELETE;
        return PREPARE_SUCCESS;
    }

    if (strcasecmp(keyword, "update") == 0) {
        char* table_name = strtok(NULL, " ");
        char* id_str = strtok(NULL, " ");
        char* column_name = strtok(NULL, " ");
        char* column_value = strtok(NULL, " ");
        if (!table_name || !id_str || !column_name || !column_value) {
            return PREPARE_UNRECOGNIZED_STATEMENT;
        }
        int id = atoi(id_str);
        strcpy(statement->table_name, table_name);
        statement->id = id;
        strcpy(statement->column_name, column_name);
        strcpy(statement->column_value, column_value);
        statement->type = STATEMENT_UPDATE;
        return PREPARE_SUCCESS;
    }

    return PREPARE_UNRECOGNIZED_STATEMENT;
}

// Execute the prepared statement depending on type
void execute_statement(Statement* statement, Database* db);

// Insert data into the table
void execute_insert(Statement* statement, Table* table) {
    Column* columns = NULL;
    printf("Add columns in 'column=value' format. Type 'end' to finish.\n");
    while (true) {
        char col_input[96];
        printf("db > ");
        fgets(col_input, sizeof(col_input), stdin);
        col_input[strcspn(col_input, "\n")] = 0;

        if (strcmp(col_input, "end") == 0) {
            break;
        }

        // We expect the user to enter column correctly
        char* name = strtok(col_input, "=");
        char* value = strtok(NULL, "=");
        if (name && value) {
            add_column(&columns, name, value);
        } else {
            printf("Format error. Use 'column=value'.\n");
        }
    }

    // Insert the columns to B-Tree
    table->root = insert(table->root, columns);
    printf("Insert completed for table=%s\n", table->name);
}

// Select (read) all data in the table
void execute_select(Table* table) {
    printf("Selecting from table: %s\n", table->name);
    print_separator();
    printf("| ID | Column:Value                        |\n");
    print_separator();
    inorder(table->root);
    print_separator();
}

// Update specific entries in the table
void execute_update(Statement* statement, Table* table) {
    Column* new_columns = NULL;
    add_column(&new_columns, statement->column_name, statement->column_value);
    update_node(table->root, statement->id, new_columns);
    printf("Update executed for ID=%d in table %s\n", statement->id, table->name);
}


// Save the table to a file
void save_table(Table* table) {
    char filename[64];
    snprintf(filename, sizeof(filename), "%s.txt", table->name);
    FILE* file = fopen(filename, "w"); //w for write in the file
    if (file) {
        save_tree(table->root, file);
        fclose(file);
        printf("Table saved to %s\n", filename);
    } else {
        perror("Error: Unable to open file for saving");
    }
}


// Load the table from a file
void load_table(Table* table) {
    char filename[64];
    snprintf(filename, sizeof(filename), "%s.txt", table->name);
    FILE* file = fopen(filename, "r");
    if (file) {
        table->root = load_tree(file);
        fclose(file);
        printf("Table loaded from %s\n", filename);
    } else {
        printf("No existing data found for %s, starting fresh.\n", filename);
    }
}


// Handle execution of different types of statements based on their type
void execute_statement(Statement* statement, Database* db) {
    if (statement->type == STATEMENT_CREATE_TABLE) {
        if (db->table_count < MAX_TABLES) {
            
            for (int i = 0; i < db->table_count; i++) {
                if (strcmp(db->tables[i].name, statement->table_name) == 0) {
                    printf("ERROR: Table '%s' already exists.\n", statement->table_name);
                    return;
                }
            }
            strncpy(db->tables[db->table_count].name, statement->table_name, 31);
            db->tables[db->table_count].name[31] = '\0';
            db->tables[db->table_count].root = NULL;
            db->table_count++;
            printf("Table '%s' created.\n", statement->table_name);
            save_table(&db->tables[db->table_count - 1]);  
            return;
        } else {
            printf("ERROR: Maximum number of tables reached.\n");
            return;
        }
    }

    Table* table = NULL;
    for (int i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].name, statement->table_name) == 0) {
            table = &db->tables[i];
            break;
        }
    }

    if (!table) {
        printf("ERROR: Table %s not found.\n", statement->table_name);
        return;
    }

    // Execute appropriate operation based on what we need here
    switch (statement->type) {
        case STATEMENT_INSERT:
            execute_insert(statement, table);
            break;

        case STATEMENT_SELECT:
            execute_select(table);
            break;

        case STATEMENT_DELETE:
            table->root = delete_node(table->root, statement->id);
            printf("Executed delete for ID=%d in table %s\n", statement->id, table->name);
            break;

        case STATEMENT_UPDATE:
            execute_update(statement, table);
            break;
    }
    save_table(table);  
}

///////////////////////////////////////////////////////////////////////////// REPL////////////////////////////////////////////////////////////////////////////////////// 
void repl(void) {
    Database* db = create_database();
    InputBuffer* input_buffer = new_input_buffer();

    // Start by telling the user what we gonna do
    printf("Starting database with an empty dataset.\n");

    // Load tables if that already exist here
    for (int i = 0; i < MAX_TABLES; i++) {
        char filename[64];
        snprintf(filename, sizeof(filename), "table_%d.txt", i);

        struct stat buffer;
        if (stat(filename, &buffer) == 0) {
            snprintf(db->tables[db->table_count].name, sizeof(db->tables[db->table_count].name), "table_%d", i);
            load_table(&db->tables[db->table_count]);
            db->table_count++;
        }
    }
    //If bool is true continue
    bool running = true; 
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
                    execute_statement(&statement, db);
                    printf("Executed.\n");
                    break;
                case PREPARE_UNRECOGNIZED_STATEMENT:
                    printf("Unknown keyword '%s'.\n", input_buffer->buffer);
                    continue;
            }
        }
    }

    close_input_buffer(input_buffer);
}
