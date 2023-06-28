/*
 * This header contains implementation of BST Tree.
 *
 *** A BST class includes:
 * A field for storing data: data
 * A field for storing left child pointer: left
 * A field for storing right child pointer: right
*/

#pragma once
#ifndef _BST_TREE_H
#define _BST_TREE_H

#include <iostream>

class BST {
private:
    struct node {
        int data;
        node *left;
        node *right;
    };
    /* Root of BST Tree */
    node *root;

    /* Initialize a new node */
    node* initializeNode(int);

    /* Make an allocated node to be nullptr*/
    node* makeEmpty(node*);

    /* Insert a new node into BST Tree */
    node* insert(node*, int);

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
public:
    /* Default constructor for BST class */
    BST() {this->root = nullptr; };

    /* Defaul destructor for BST class */
    ~BST() {makeEmpty(this->root); };

    void insert(int x) {this->root = insert(this->root, x); };

    void remove(int x) {this->root = remove(this->root, x); };

    /* 
     * Display BST Tree:
     * Case 1: In-order.
     * Case 2: Pre-order.
     * Case 3: Post-order.
    */
    void display();

    node* search(int x) {return find(this->root, x); };
};




BST::node* BST::initializeNode(int in_data) {
    node *p = new node;
    if (p != nullptr) {
        p->data = in_data;
        p->left = nullptr;
        p->right = nullptr;
    }
    return p;
}

BST::node* BST::makeEmpty(node* p) {
    if (p != nullptr) {
        BST::makeEmpty(p->left);
        BST::makeEmpty(p->right);
        delete p; 
    }
    return nullptr;
}


BST::node* BST::insert(node* p, int in_data) {
    if (p == nullptr)
        p = initializeNode(in_data);
    else {
        if (in_data <= p->data)
            p->left = insert(p->left, in_data);
        else
            p->right = insert(p->right, in_data);
    }
    return p;
}

BST::node* BST::findMin(node* p) {
    if (p != nullptr) {
        if (p->left != nullptr)
            findMin(p->left);
        else
            return p;
    }
    else
        return nullptr;
}

BST::node* BST::findMax(node* p) {
    if (p != nullptr) {
        if (p->right != nullptr)
            findMax(p->right);
        else
            return p;
    }
    else
        return nullptr;
}


/* 
 * Remove a node in BST/BST has three scenarios:
 * Case 1: Remove a leaf node (a node has no child).
 * Case 2: Remove a node that has only one child (left or right).
 * Case 3: Remove a node that has two children (both left and right).
 * 
*/
BST::node* BST::remove(node* p, int target) {
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
        return p;
    }
    return nullptr;
}

BST::node* BST::find(node* p, int target) {
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

void BST::inorder(node* p) {
    if (p != nullptr) {
        inorder(p->left);
        std::cout << p->data << " ";
        inorder(p->right);
    }
    return;
}

void BST::preorder(node* p) {
    if (p != nullptr) {
        std::cout << p->data << " ";
        preorder(p->left);
        preorder(p->right);
    }
    return;
}

void BST::postorder(node* p) {
    if (p != nullptr) {
        postorder(p->left);
        postorder(p->right);
        std::cout << p->data << " ";
    }
    return;
}

void BST::display() {
    int choice;


    do {
        std::system("cls");

        std::cout << "1. Pre-order\n2. Post-order\n3. In-order\nYour choice: ";
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
