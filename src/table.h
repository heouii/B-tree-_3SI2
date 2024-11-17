#ifndef TABLE_H
#define TABLE_H

#define MAX_TABLES 10

#include "btree.h"

typedef struct {
    char name[32];
    TreeNode* root;
} Table;

typedef struct {
    Table tables[MAX_TABLES];
    int table_count;
} Database;

Database* create_database();
void add_table(Database* db, const char* table_name);


#endif
