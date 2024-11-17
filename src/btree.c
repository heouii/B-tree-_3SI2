#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "btree.h"

static int Curent_id =0;

TreeNode* create_node(const char* name, const char* breed) {


    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->id = Curent_id++;
    
     strcpy(node->name, name);
    strcpy(node->breed, breed);
    
    node->left = NULL;
    node->right = NULL;
    
    
    return node;
}



void update_node(TreeNode* root, int id, const char* name, const char* breed) {


    if (root == NULL) return;

    if (root->id == id) {


        strncpy(root->name, name, 31);
        root->name[31] = '\0'; 
        strncpy(root->breed, breed, 31);
        root->breed[31] = '\0';
    } else if (id < root->id) {

        
        update_node(root->left, id, name, breed);
    } else {
        update_node(root->right, id, name, breed);
    }
}

TreeNode* insert(TreeNode* root, const char* name, const char* breed) {


    if (root == NULL) {
        return create_node(name, breed);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insert(root->left, name, breed);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insert(root->right, name, breed); 
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



TreeNode* find_min(TreeNode* node){


    while (node->left != NULL){

        node = node->left;
    }
    return node;
}




TreeNode* delete_node(TreeNode* root, int id){

    if(root == NULL) return root;

    if (id < root->id){

        root -> left = delete_node (root ->left, id);


    }else if (id > root->id){

        root ->right = delete_node(root -> right, id);


    }else{

        if (root->left == NULL){

            TreeNode* temp = root->right;
            free(root);
            return temp;
        }else if (root ->right == NULL ){

            TreeNode* temp = root-> left; 
            free(root);
            return temp;
        }


        TreeNode* temp = find_min(root->right);
        root->id = temp->id;
        strcpy(root->name, temp->name);
        strcpy(root->breed, temp->breed);

        root -> right = delete_node(root ->right, temp->id);
    }
    return root;
}




TreeNode* load_tree(const char* filename) {


    FILE* file = fopen(filename, "r");
    if (!file) {

        
        printf("No existing database found.\n");
        return NULL;
    }

    TreeNode* root = NULL;
    char line[256];

    while (fgets(line, sizeof(line), file)) {


        int id;
        char name[32], breed[32];

        if (sscanf(line, "%d,%31[^,],%31s", &id, name, breed) != 3) {
            continue;
        }

        root = insert(root, name, breed);
    }


    

    fclose(file);
    return root;
}

