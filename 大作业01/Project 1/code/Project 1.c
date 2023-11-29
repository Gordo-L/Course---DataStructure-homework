#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

typedef struct TreeNode* Tree;
struct TreeNode {
    int Element;
    Tree  Left;
    Tree  Right;
};

/*
 * Insert an element into the tree.
 * ------------------------------------------------
 *
 *   X: an integer element to insert
 *   T: pointer to the binary search tree to be inserted
 *
 *   returns: the binary search tree that has been inserted
 */
Tree Insert(int X, Tree T) {
    //If the tree is empty, return a tree of one node.
    if (!T) {
        T = (Tree)malloc(sizeof(struct TreeNode));
        T->Element = X;
        T->Left = T->Right = NULL;
    }
    //Start looking for the location of the element to insert
    else {
        //Because we use negative signs to represent red nodes,
        //we compare the absolute values.
        if (abs(X) < abs(T->Element))
            T->Left = Insert(X, T->Left);    //Recursively insert the left subtree
        else if (abs(X) > abs(T->Element))
            T->Right = Insert(X, T->Right);  //Recursively insert the right subtree
        //else: X already exists and does nothing
    }
    return T;
}

/*
 * Read in the preorder traversal sequence of the tree,
 * and build a binary search tree according to it.
 * ------------------------------------------------
 *
 *   N: the total number of nodes in the binary tree
 *
 *   returns: pointer to the tree that has been built
 */
Tree BuildTree(int N) {
    int temp;
    Tree T = NULL;
    for (int i = 0; i < N; i++) {
        scanf("%d", &temp);
        T = Insert(temp, T);
    }
    return T;
}

/*
 * Judge whether red nodes' children are both black.
 * ------------------------------------------------
 *
 *   T: pointer to the tree to be judged
 *
 *   returns: 1 or 0; 1 represents yes, 0 represents no.
 */
bool RCareB(Tree T) {
    //If T is leaf(NULL), T is black. So don't need to judge.
    if (T) {
        //If T is red, then judge whether its children are both black.
        if (T->Element < 0) {
            if (T->Left) {
                if (T->Left->Element < 0)return 0;
            }
            if (T->Right) {
                if (T->Right->Element < 0)return 0;
            }
        }
        //Traverse T recursively.
        if (!RCareB(T->Left))return 0;
        if (!RCareB(T->Right))return 0;
    }
    return 1;
}

/*
 * Get the height of the node.
 * The hight means the maximum value of black nodes that
 * all simple paths from the node to descendant leaves contains.
 * ------------------------------------------------
 *
 *   T: pointer to the treenode
 *
 *   returns: the height of the node
 */
int GetNum(Tree T) {
    if (!T)return 1;
    int leftNum = GetNum(T->Left);
    int rightNum = GetNum(T->Right);
    if (leftNum > rightNum)
        return T->Element > 0 ? leftNum + 1 : leftNum;
    else
        return T->Element > 0 ? rightNum + 1 : rightNum;
}

/*
 * Judge whether all simple paths from the node to descendant leaves
 * contain the same number of black nodes for each node.
 * ------------------------------------------------
 *
 *   T: pointer to the treenode
 *
 *   returns: 1 or 0; 1 represents yes, 0 represents no.
 */
bool SameNum(Tree T) {
    //If it is null, it is black node, count + 1.
    if (!T)return 1;
    int leftNum = GetNum(T->Left);
    int rightNum = GetNum(T->Right);
    //Check if the height of the left and right subtrees is equal.
    if (leftNum != rightNum)return 0;
    //Traverse T recursively.
    return SameNum(T->Left) && SameNum(T->Right);
}

/*
 * Judge whether the tree is red-black tree.
 * ------------------------------------------------
 *
 *   T: pointer to the treenode
 *
 *   returns: 1 or 0; 1 represents yes, 0 represents no.
 */
bool IsRBTree(Tree T) {
    //Because N is a positive integer, the tree has one node at least.
    //requirement:(2)The root is black.
    if (T->Element < 0)return 0;
    //requirement:(4) If a node is red, then both its children are black.
    if (!(RCareB(T)))return 0;
    //requirement:(5)  For each node, all simple paths from the node 
    //to descendant leaves contain the same number of black nodes.
    if (!(SameNum(T)))return 0;
    return 1;
}

int main()
{
    int K;
    //enter the total number of cases K(<=30)
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        int N;
        //enter the total number of nodes in the binary tree N(<=30)
        scanf("%d", &N);
        Tree T;
        T = BuildTree(N);
        if (IsRBTree(T)) printf("Yes\n");
        else printf("No\n");
    }
    getchar();
    getchar();
}



