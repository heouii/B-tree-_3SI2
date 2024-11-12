#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

TreeNode* create_node(int id, const char* name, const char* breed) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->id = id;
    
    strcpy(node->name, name);
    strcpy(node->breed, breed);
    
    node->left = NULL;
    node->right = NULL;
    
    
    return node;
}

TreeNode* insert(TreeNode* root, int id, const char* name, const char* breed) {
    if (root == NULL) {
        return create_node(id, name, breed);
    }

    if (id < root->id) {
        root->left = insert(root->left, id, name, breed);
    } else if (id > root->id) {
        root->right = insert(root->right, id, name, breed);
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

void inorder(TreeNode* root) 
{
    if (root != NULL) {
        
        inorder(root->left);
        printf("ID: %d, Name: %s, Breeds: %s\n", root->id, root->name, root->breed);


        inorder(root->right);
    }
}
