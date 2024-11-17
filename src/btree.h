#ifndef BTREE_H
#define BTREE_H

typedef struct Column {
    char name[32];
    char value[64];
    struct Column* next;
} Column;

typedef struct TreeNode {
    int id;
    Column* columns;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void add_column(Column** head, const char* name, const char* value);
TreeNode* insert(TreeNode* root, Column* columns);
TreeNode* search(TreeNode* root, int id);
TreeNode* delete_node(TreeNode* root, int id);
void update_node(TreeNode* root, int id, Column* new_columns);
void inorder(TreeNode* root);
void save_tree(TreeNode* root, FILE* file);
TreeNode* load_tree(FILE* file);
TreeNode* find_min(TreeNode* node);
void print_separator();
void print_row(TreeNode* node);

#endif
