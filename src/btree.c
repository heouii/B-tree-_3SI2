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


TreeNode* load_tree( const char* filename){

FILE* file = fopen (filename, "r");// r pour ecriture
if(!file){

    return NULL;
}


TreeNode* root = NULL;

char line [256];

while (fgets(line, sizeof(line),file)){

    int id;

    char name[32], breed[32];

    if(sscanf(line, "%d,%31[^,],%31s", &id, name, breed)){

        continue;


    }

    root = insert (root, name, breed);

}

fclose(file);

return root;

}