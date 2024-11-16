#ifndef BTREE_H
#define BTREE_H

typedef struct TreeNode 

{
    int id;
    char name[32];
     char breed[32];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


TreeNode* insert(TreeNode* root,  const char* name, const char* breed);
TreeNode* search(TreeNode* root, int id);

//TreeNode* delete


TreeNode* load_tree(const char* filename);



void inorder(TreeNode* root);

#endif  
