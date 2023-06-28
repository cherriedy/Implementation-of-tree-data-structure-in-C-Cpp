/*
 * This header contains implementation of AVL Tree
 *
 *** An AVL class includes:
 ** A struct: node
 * A field for storing data: data
 * A field for storing left child pointer: left
 * A field for storing right child pointer: right
 * A field for storing height of each node: hight
 * 
 ** A field for storing root of AVL tree: root
 * 
*/

#pragma once
#ifndef _AVL_TREE_H
#define _AVL_TREE_H

#include <iostream>
#include <algorithm>

class AVL {
private:
    struct node {
        int data;
        node *left;
        node *right;
        int height;
    };
    /* Root fo AVL Tree */
    node *root;
    
    /* Initialize a new node */
    node* initializedNode(int);

    /* Make an allocated node to be null */
    node* makeEmpty(node*);

    /* Insert a new node into AVL Tree */
    node* insert(node*, int);

    /* Get balance factor*/
    int balanceFactor(node*);

    /* Find minimum node */
    node* findMin(node*);

    /* Find maximum node */
    node* findMax(node*);

    /* Remove an allocated node*/
    node* remove(node*, int);

    /* Find an allocated node */
    node* find(node*, int);

    /* In-order traversal */
    void inorder(node*);

    /* Pre-order traversal */
    void preorder(node*);

    /* Post-order traversal */
    void postorder(node*);

    /* Right (Left - Left) rotation */
    node* LL_rotation(node*);

    /* Left (Right - Right) rotation */
    node* RR_rotation(node*);

    /* Left - Right rotation */
    node* LR_rotation(node*);

    /* Right - Left rotation */
    node* RL_rotation(node*);

    /* Get new balance_height of node after rotation / deletion */
    int balance_height(node*);

    /* Get height of node */
    int height(node* p);

    int AVL_Height(node* p, int AVL_height = 0) {
        if (height(p) == 0)
            return AVL_height;
        else {
            if (height(p->left) > height(p->right))
                return AVL_Height(p->left, AVL_height + 1);
            else
                return AVL_Height(p->right, AVL_height + 1);
        }
    }
public:
    /* Default constructor for AVL class */
    AVL() {this->root = nullptr; };

    /* Default destructor for AVL class*/
    ~AVL() {makeEmpty(this->root); };

    void insert(int x) {this->root = insert(this->root, x); };

    void remove(int x) {this->root = remove(this->root, x); };

    /* 
     * Display BST Tree:
     * Case 1: In-order.
     * Case 2: Pre-order.
     * Case 3: Post-order.
    */
    void display();

    int AVLH() { return AVL_Height(this->root); };
};

/*      Implementation      */

AVL::node* AVL::initializedNode(int in_data) {
    node *p = new node;
    if (p != nullptr) {
        p->data = in_data;
        p->left = nullptr;
        p->right = nullptr;
        p->height = 0;
    }
    return p;
}

AVL::node* AVL::makeEmpty(node* p) {
    if (p != nullptr) {
        makeEmpty(p->left);
        makeEmpty(p->right);
        delete p;
    }
    return nullptr;
}

int AVL::height(AVL::node* p) {
    if (p == nullptr)
        return 0;
    return p->height;
}
int AVL::balance_height(node* p) {
    int l_height = 0, r_height = 0;

    if (p == nullptr) return 0;
    
    l_height = (p->left == nullptr) ? 0 : (1 + p->left->height);

    r_height = (p->right == nullptr) ? 0 : (1 + p->right->height);

    return std::max(l_height, r_height);
}


int AVL::balanceFactor(AVL::node* p) {
    int l_height = 0, r_height = 0;

    if (p == nullptr) return 0;

    l_height = (p->left == nullptr) ? 0 : (1 + p->left->height);

    r_height = (p->right == nullptr) ? 0 : (1 + p->right->height);

    return l_height - r_height;
}

AVL::node* AVL::insert(node* p, int in_data) {
    if (p == nullptr)
        return initializedNode(in_data);
    if (in_data < p->data)
        p->left = insert(p->left, in_data);
    else
        p->right = insert(p->right, in_data);

    /* Update balance_height */
    p->height = balance_height(p);

    /* Left heavy */
    if (balanceFactor(p) == 2) {
        if (in_data < p->left->data)   
            return LL_rotation(p);
        else
            return LR_rotation(p);
    }        
    /* Right heavy */
    else if (balanceFactor(p) == -2) {
        if (in_data >= p->right->data)
            return RR_rotation(p);
        else
            return RL_rotation(p);
    }
    return p;
}


AVL::node* AVL::LL_rotation(node* root) {
    node *pivot = root->left;
    root->left = pivot->right;
    
    /* root now is right child of pivot */
    pivot->right = root;

    /* Update new balance_height for both root and pivot */
    root->height = balance_height(root);
    pivot->height = balance_height(pivot);
    return pivot;
}

AVL::node* AVL::RR_rotation(node* root) {
    node *pivot = root->right;
    root->right = pivot->left;

    /* root now is left child of pivot */
    pivot->left = root;

    /* Update new balance_height for both root and pivot */
    root->height = balance_height(root);
    pivot->height = balance_height(pivot);
    return pivot;
}

/* Left Rotation -> Right Rotation */
AVL::node* AVL::LR_rotation(node* root) {
    root->left = RR_rotation(root->left);
    return LL_rotation(root);
}

/* Right Rotation -> Left Rotation */
AVL::node* AVL::RL_rotation(node* root) {
    root->right = LL_rotation(root->right);
    return RR_rotation(root);
}

AVL::node* AVL::findMin(node* p) {
    if (p != nullptr) {
        if (p->left != nullptr)
            findMin(p->left);
        else
            return p;
    }
    return nullptr;
}

AVL::node* AVL::findMax(node* p) {
    if (p != nullptr) {
        if (p->right != nullptr)
            findMax(p->right);
        else
            return p;
    }
    return nullptr;
}

/* 
 * Remove a node in AVL has three scenarios:
 * Case 1: Remove a leaf node (a node has no child).
 * Case 2: Remove a node that has only one child (left or right).
 * Case 3: Remove a node that has two children (both left and right).
 * 
*/

AVL::node* AVL::remove(node* p, int target) {
    node *temporary = nullptr;
    if (p != nullptr) {
        if (target < p->data)
            p->left = remove(p->left, target);
        else if (target > p->data)
            p->right = remove(p->right, target);
        /* Case 3 */
        else if (p->left && p->right) {
            // Case 1: Replace node with minimum in right.
            //temporary = findMin(p->right);
            //p->data = temporary->data;
            //p->right = remove(p->right, p->data);

            // Case 2: Replace node with maximum in left.
            temporary = findMax(p->left);
            p->data = temporary->data;
            p->left = remove(p->left, p->data);
        }
        /* Case 1, Case 2 */
        else {
            /* If both left and right are null that means this node is a leaf node */
            temporary = p;
            if (p->left == nullptr)
                p = p->right;
            else if (p->right == nullptr)
                p = p->left;
            delete temporary;
        }

        /* If AVL has no node or no child, return null */
        if (p == nullptr)
            return nullptr;
        
        /* Update new balance_height*/
        p->height = balance_height(p);
       
        /* Rotation after removing, if unbalance */
        /* Left heavy */
        if (balanceFactor(p) == 2) {
            if (balanceFactor(p->left) == 1)
                return LL_rotation(p);
            else
                return LR_rotation(p);
        }
        /* Right heavy */
        else if (balanceFactor(p) == -2) {
            if (balanceFactor(p->right) == -1)
                return RR_rotation(p);
            else
                return RL_rotation(p);
        }
        return p;
    }
    return nullptr;
}

AVL::node* AVL::find(node* p, int target) {
    if (p != nullptr) {
        if (target < p->data)
            find(p->left, target);
        else if (target > p->data)
            find(p->right, target);
        else
            return p;
    }   
    return nullptr; 
}

void AVL::inorder(node* p) {
    if (p != nullptr) {
        inorder(p->left);
        std::cout << p->data << " ";
        inorder(p->right);
    }
    return;
}

void AVL::preorder(node* p) {
    if (p != nullptr) {
        std::cout << p->data << " ";
        preorder(p->left);
        preorder(p->right);
    }
    return;
}

void AVL::postorder(node* p) {
    if (p != nullptr) {
        postorder(p->left);
        postorder(p->right);
        std::cout << p->data << " ";
    }
    return;
}

void AVL::display() {
    int choice;
    do {
        std::system("cls");
        std::cout << "1. Pre-order\n2. Post-order\n3. In-order\n0. Exit\nYour choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 0: break;
            case 1: {
                preorder(this->root);
                break;
            }
            case 2: {
                postorder(this->root);
                break;
            }
            case 3: {
                inorder(this->root);
                break;
            }
            default:
                std::cout << "Invalid choice !";
        }
        std::cout << std::endl;
        std::system("pause");
    } while (choice != 0);
}

#endif
