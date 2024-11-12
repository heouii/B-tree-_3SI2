#ifndef BTREE_H
#define BTREE_H

typedef struct TreeNode 
//implementer auto incrementation de l'id et le rajout de colunm pas de statique
{
    int id;
    char name[32];
     char breed[32];
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;


TreeNode* insert(TreeNode* root, int id, const char* name, const char* breed);
TreeNode* search(TreeNode* root, int id);

//TreeNode* delete




void inorder(TreeNode* root);

#endif  
