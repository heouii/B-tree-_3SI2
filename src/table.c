#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

Database* create_database() {
    Database* db = (Database*)malloc(sizeof(Database));
    db->table_count = 0;
    return db;
}

void add_table(Database* db, const char* table_name) {
    if (db->table_count < MAX_TABLES) {
        strncpy(db->tables[db->table_count].name, table_name, 31);
        db->tables[db->table_count].name[31] = '\0';
        db->tables[db->table_count].root = NULL;
        db->table_count++;
        printf("Table '%s' created.\n", table_name);
    } else {
        printf("ERROR: Maximum number of tables reached.\n");
    }
}
