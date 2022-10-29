#pragma once


// C++ program to insert a node in AVL tree
#include <bits/stdc++.h>
#include <vector>
#include <cmath> // max

#define NODE_TEMPLATE template <class T, typename E, typename std::enable_if<std::is_base_of<NodeElementComparator<E>, T>::value>::type*>

template <typename E>
class NodeElementComparator {
public:
    virtual bool equals(NodeElementComparator<E> &e) = 0;
    virtual E value() = 0;
};

template <class T, typename E, typename std::enable_if<std::is_base_of<NodeElementComparator<E>, T>::value>::type* = nullptr>
class Node;

// An AVL tree node
NODE_TEMPLATE
class Node {
public:
    Node* insert(T *result, bool *error);
    std::vector<Node*> searchAll(E value);
    std::vector<Node*> searchAll(std::vector<Node*> *results, E value);
    T *search(NodeElementComparator<E> value);
    std::vector<T*> getInorder(Node *root);
    std::vector<T*> getInorder(std::vector<T*> *list, Node *root);

private:
    T *result;
    Node *left;
    Node *right;
    int height;

    Node *rightRotate();
    Node *leftRotate();
    int getBalance();


    /* Helper function that allocates a
       new node with the given key and
       NULL left and right pointers. */
    static Node* newNode(T *result) {
        Node* node = new Node();
        node->result = result;
        node->left = nullptr;
        node->right = nullptr;
        node->height = 1;

        return node;
    }

    static int getBalance(Node *n) {
        if (n == nullptr) return 0;
        return n->getBalance();
    }
};

// This code is contributed by
// rathbhupendra
// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/