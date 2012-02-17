/* 
 * File:   treetype.h
 * Author: bains
 *
 * Created on December 5, 2010, 10:05 AM
 */

#ifndef TREETYPE_H
#define	TREETYPE_H


#include <iostream>
#include <string.h>

enum OrderType {
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
};


class TreeType
{
public:
    TreeType();
    ~TreeType();

    //copy constructor
    TreeType(const TreeType & originalTree);
    void operator=(TreeType & originalTree);
    int numberOfNodes();
    void insertItem(int item);
//    void MakeEmpty();
//    bool isEmpty() const;
//    bool isFull() const;
private:

    struct TreeNode {
        int info;
        TreeNode* left;
        TreeNode* right;
    };
    TreeNode * root;

    int countNodes(TreeNode * node);
    void insertItem(TreeNode *& node, int item);
};


#endif	/* TREETYPE_H */

