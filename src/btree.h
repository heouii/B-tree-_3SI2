#ifndef BTREE_H
#define BTREE_H

typedef struct Column {
    char name[32];
    char value[64];
    struct Column* next;
} Column;

typedef struct TreeNode {
    int id; //identifier for a node
    Column* columns;
    struct TreeNode* left; //pointer for left child
    struct TreeNode* right; //pointer for right child
} TreeNode;

// Prototypes for every functions for work with tree and columns

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
