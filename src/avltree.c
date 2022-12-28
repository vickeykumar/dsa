#include <stdio.h>
#include <stdlib.h>
#include "avltree.h"

#define COUNT 4
static int max(int i, int j) { return (i>j)?i:j; }

AVLNode* avl_newNode(int key) {
    AVLNode *node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->height = 1;   /* height of avl tree leaf node is 1, 
                        for the convenience of calculating balance factor */
    node->left = NULL;
    node->right = NULL;
    return node;
}


int avl_height(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int avl_getBalance(AVLNode *node) {
    if (node == NULL) {
        return 0;
    }
    return avl_height(node->left) - avl_height(node->right);
}

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

AVLNode* avl_leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    // Perform the rotation
    y->left = x;
    x->right = T2;

    // Update the heights of the nodes
    x->height = 1 + max(avl_height(x->left), avl_height(x->right));
    y->height = 1 + max(avl_height(y->left), avl_height(y->right));

    // Return the new root node
    return y;
}


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
AVLNode* avl_rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    // Perform the rotation
    x->right = y;
    y->left = T2;

    // Update the heights of the nodes
    y->height = 1 + max(avl_height(y->left), avl_height(y->right));
    x->height = 1 + max(avl_height(x->left), avl_height(x->right));

    // Return the new root node
    return x;
}

/**
 * Inserts a key into an AVL tree.
 *
 * @param node A pointer to the root node of the AVL tree.
 * @param key The key to be inserted.
 * @return A pointer to the root node of the AVL tree after the insertion.
 */
AVLNode* avl_insert(AVLNode *node, int key) {
    // performs normal BST insert 
    if (node == NULL) {
        return avl_newNode(key);
    }

    if (key < node->key) {
        node->left = avl_insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = avl_insert(node->right, key);
    } else {
        return node; // key should be unique, so that unique search can be availed
    }

    node->height = 1 + max(avl_height(node->left), avl_height(node->right));

    // Calculate the balance factor of the root node
    int balance = avl_getBalance(node);

    // If the balance factor is greater than 1 and the key to be inserted is less than the key in the left child,
    // perform a right rotation on the root node
    /*
        LL rotation: tree becomes unbalance after insertion in left subtree of left child of root node.
    */
    if (balance > 1 && key < node->left->key) {
        return avl_rightRotate(node);
    }

    // If the balance factor is less than -1 and the key to be inserted is greater than the key in the right child,
    // perform a left rotation on the root node
    /*
        RR rotation: tree becomes unbalanced by insertion in to right subtree of right child of the root node.
    */
    if (balance < -1 && key > node->right->key) {
        return avl_leftRotate(node);
    }

    // If the balance factor is greater than 1 and the key to be inserted is greater than the key in the left child,
    // perform a left rotation on the left child first and then a right rotation on the root node
    /*
        LR Rotation : insertion in direction root->left->right
        steps first make LL-> by doing left rotation at child, then right rotation at root
        leftrotate(child) -> right rotate(root of subtree)
    */
    if (balance > 1 && key > node->left->key) {
        node->left = avl_leftRotate(node->left);
        return avl_rightRotate(node);
    }

    // If the balance factor is less than -1 and the key to be inserted is less than the key in the right child,
    // perform a right rotation on the right child first and then a left rotation on the root node
    /*
        RL rotation: sequence insertion in R(root) and left(child)
        right roatation(child) -> left rotation(root)
        i.e. first make RR and then do left rotation.
    */
    if (balance < -1 && key < node->right->key) {
        node->right = avl_rightRotate(node->right);
        return avl_leftRotate(node);
    }

    // Return the root node
    return node;
}


AVLNode* avl_search(AVLNode *node, int key) {
    // If the tree is empty or the key is not found, return NULL
    if (node == NULL || node->key == key) {
        return node;
    }

    // If the key is less than the key in the root node, search the left subtree
    if (key < node->key) {
        return avl_search(node->left, key);
    }
    // If the key is greater than the key in the root node, search the right subtree
    else {
        return avl_search(node->right, key);
    }
}

void avl_printInOrder(AVLNode *node) {
    if (node == NULL) {
        return;
    }

    avl_printInOrder(node->left);
    printf("%d ", node->key);
    avl_printInOrder(node->right);
}

/**
 * Finds the node with the minimum key in a given subtree.
 *
 * @param node A pointer to the root node of the subtree.
 * @return A pointer to the node with the minimum key.
 */
AVLNode* avl_minValueNode(AVLNode *node) {
    AVLNode *current = node;
    while (current->left != NULL) {
        current = current->left;
    }
    return current;
}

/**
 * Deletes a node from an AVL tree.
 *
 * @param root A pointer to the root node of the tree.
 * @param key The key of the node to be deleted.
 * @return A pointer to the root node of the tree after the deletion.
 */
AVLNode* avl_deleteNode(AVLNode *root, int key) {
    // perform bst deletion
    if (root == NULL) {
        return root;
    }

    // Recursively search for the node to be deleted
    if (key < root->key) {
        root->left = avl_deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = avl_deleteNode(root->right, key);
    } else {
        // Case 1: the node has no children
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }
        // Case 2: the node has one child
        if (root->left == NULL) {
            AVLNode *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            AVLNode *temp = root->left;
            free(root);
            return temp;
        }
        // Case 3: the node has two children
        AVLNode *successor = avl_minValueNode(root->right);
        root->key = successor->key;
        root->right = avl_deleteNode(root->right, successor->key);
    }

    // Update the height of the current node
    root->height = 1 + max(avl_height(root->left), avl_height(root->right));

    // Check if the tree is unbalanced and perform the necessary rotations
    int balance = avl_getBalance(root);
    if (balance > 1 && avl_getBalance(root->left) >= 0) {
        return avl_rightRotate(root);
    }
    if (balance > 1 && avl_getBalance(root->left) < 0) {
        root->left = avl_leftRotate(root->left);
        return avl_rightRotate(root);    
    }
    if (balance < -1 && avl_getBalance(root->right) <= 0) {
        return avl_leftRotate(root);
    }
    if (balance < -1 && avl_getBalance(root->right) > 0) {
        root->right = avl_rightRotate(root->left);
        return avl_leftRotate(root);
    }

    // Return the root node of the tree
    return root;
}

/**
 * Prints an AVL tree in a diagram format.
 *
 * @param root A pointer to the root node of the tree.
 * @param space The amount of space to print before the current node.
 */
void avl_printAVLTree(AVLNode *root, int space) {
    // Base case: the tree is empty
    if (root == NULL) {
        return;
    }

    // Increase the amount of space for the next level
    space += COUNT;

    // Recursively print the right subtree
    avl_printAVLTree(root->right, space);

    // Print the current node
    printf("\n");
    for (int i = COUNT; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->key);

    // Recursively print the left subtree
    avl_printAVLTree(root->left, space);
}

