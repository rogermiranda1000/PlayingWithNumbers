#pragma once


// C++ program to insert a node in AVL tree
#include<bits/stdc++.h>
#include <vector>
#include <cmath> // max
#include "float_range.h"

// An AVL tree node
class Node {
public:
    friend Node* insert(Node* node, float key);
    friend std::vector<Node*> searchAll(std::vector<Node*> *results, Node *root, float value, float range);
    friend std::vector<Node*> searchAll(Node *root, float value, float range);
    friend Node *search(Node *root, float value, float range);

private:
    float key;
    Node *left;
    Node *right;
    int height;

    friend Node *rightRotate(Node *y);
    friend Node* newNode(float key);
    friend int height(Node *N);
    friend Node *leftRotate(Node *x);
    friend int getBalance(Node *N);
};

// This code is contributed by
// rathbhupendra
// https://www.geeksforgeeks.org/avl-tree-set-1-insertion/