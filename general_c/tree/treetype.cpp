
#include "treetype.h"

int TreeType::numberOfNodes()
{
    return countNodes(root);
}

int TreeType::countNodes(TreeNode * node)
{
    if(node == NULL)
        return 0;
    else
        return countNodes(node->left) + countNodes(node->right) + 1;
}


TreeType::TreeType(){
    root = NULL;
}

TreeType::~TreeType(){

}

void TreeType::insertItem(int item)
{
    std::cout << "insertItem: " << item << std::endl;
    return insertItem(root, item);
}

void TreeType::insertItem(TreeNode* & node, int item)
{
    if(node == NULL)
    {
        node = new TreeNode;
        node->right = NULL;
        node->left = NULL;
        node->info = item;
    }
    else if(item < node->info)
    {
        insertItem(node->left, item);
    }
    else if(item > node->info)
    {
        insertItem(node->right, item);
    }
}

