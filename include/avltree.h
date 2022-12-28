#ifndef __DSA_AVLTREE_H
#define __DSA_AVLTREE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;

AVLNode* avl_newNode(int key);

int avl_height(AVLNode *node);

int avl_getBalance(AVLNode *node);

/**
 * Performs a left rotation on a node in an AVL tree.
 *
 * @param x A pointer to the node to be rotated.
 * @return A pointer to the root node of the subtree after the rotation.
 *
 *          x                 y
 *         / \               / \
 *        T1  y     =>      x   T3
 *           / \           / \
 *          T2 T3         T1 T2
 */

AVLNode* avl_leftRotate(AVLNode *x);


/**
 * Performs a right rotation on a node in an AVL tree.
 *
 * @param y A pointer to the node to be rotated.
 * @return A pointer to the root node of the subtree after the rotation.
 *
 *        y                   x
 *       / \                 / \
 *      x   T3      =>      T1  y
 *     / \                     / \
 *    T1 T2                   T2 T3
 */
AVLNode* avl_rightRotate(AVLNode *y);

/**
 * Inserts a key into an AVL tree.
 *
 * @param node A pointer to the root node of the AVL tree.
 * @param key The key to be inserted.
 * @return A pointer to the root node of the AVL tree after the insertion.
 */
AVLNode* avl_insert(AVLNode *node, int key);

AVLNode* avl_search(AVLNode *node, int key);

void avl_printInOrder(AVLNode *node);

/**
 * Finds the node with the minimum key in a given subtree.
 *
 * @param node A pointer to the root node of the subtree.
 * @return A pointer to the node with the minimum key.
 */
AVLNode* avl_minValueNode(AVLNode *node);

/**
 * Deletes a node from an AVL tree.
 *
 * @param root A pointer to the root node of the tree.
 * @param key The key of the node to be deleted.
 * @return A pointer to the root node of the tree after the deletion.
 */
AVLNode* avl_deleteNode(AVLNode *root, int key);

/**     
 * Prints an AVL tree in a diagram format.
 *
 * @param root A pointer to the root node of the tree.
 * @param space The amount of space to print before the current node.
 */
void avl_printAVLTree(AVLNode *root, int space);

#endif
