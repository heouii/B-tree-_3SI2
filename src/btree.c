#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

static int current_id = 0;

TreeNode* create_node(Column* columns) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->id = current_id++;
    node->columns = columns;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void add_column(Column** head, const char* name, const char* value) {
    Column* new_col = (Column*)malloc(sizeof(Column));
    if (new_col == NULL) {
        perror("Failed to allocate memory for column");
        return;
    }
    strncpy(new_col->name, name, 31);
    new_col->name[31] = '\0';
    strncpy(new_col->value, value, 63);
    new_col->value[63] = '\0';
    new_col->next = *head;
    *head = new_col;
}

TreeNode* insert(TreeNode* root, Column* columns) {
    if (root == NULL) {
        return create_node(columns);
    }

    if (current_id < root->id) {
        root->left = insert(root->left, columns);
    } else {
        root->right = insert(root->right, columns);
    }

    return root;
}

TreeNode* search(TreeNode* root, int id) {
    if (root == NULL || root->id == id) {
        return root;
    }
    if (id < root->id) {
        return search(root->left, id);
    } else {
        return search(root->right, id);
    }
}

TreeNode* find_min(TreeNode* node) {
    while (node->left != NULL) {
        node = node->left;
    }
    return node;
}

TreeNode* delete_node(TreeNode* root, int id) {
    if (root == NULL) return root;

    if (id < root->id) {
        root->left = delete_node(root->left, id);
    } else if (id > root->id) {
        root->right = delete_node(root->right, id);
    } else {
        if (root->left == NULL) {
            TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        TreeNode* temp = find_min(root->right);
        root->id = temp->id;
        root->columns = temp->columns;
        root->right = delete_node(root->right, temp->id);
    }
    return root;
}

void update_node(TreeNode* root, int id, Column* new_columns) {
    TreeNode* target = search(root, id);
    if (target != NULL) {
        Column* col = target->columns;
        while (col != NULL) {
            Column* next = col->next;
            free(col);
            col = next;
        }
        target->columns = new_columns;
    }
}

void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        print_row(root);
        inorder(root->right);
    }
}

void print_separator() {
    printf("+----+----------------+----------------------+\n");
}

void print_row(TreeNode* node) {
    printf("| %2d ", node->id);
    Column* col = node->columns;
    while (col != NULL) {
        printf("| %s: %s ", col->name, col->value);
        col = col->next;
    }
    printf("|\n");
}

void save_tree(TreeNode* root, FILE* file) {
    if (root != NULL) {
        fprintf(file, "%d", root->id);
        Column* col = root->columns;
        while (col) {
            fprintf(file, ",%s,%s", col->name, col->value);
            col = col->next;
        }
        fprintf(file, "\n");
        save_tree(root->left, file);
        save_tree(root->right, file);
    }
}

TreeNode* load_tree(FILE* file) {
    TreeNode* root = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        int id;
        char* token = strtok(line, ",");
        
        sscanf(token, "%d", &id);

        Column* columns = NULL;

        while ((token = strtok(NULL, ","))) {
            char* name = token;
            char* value = strtok(NULL, ",");
            if (name && value) {
                add_column(&columns, name, value);
            }
        }

        root = insert(root, columns);
    }
    return root;
}
