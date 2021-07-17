#include "bst.h"

// A utility function to get the
// height of the tree
int height(Node *N) {
    if (N == nullptr) return 0;
    return N->height;
}

/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */
Node* newNode(Result *result) {
    Node* node = new Node();
    node->result = result;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 1; // new node is initially
    // added at leaf
    return(node);
}

// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(Node *N) {
    if (N == nullptr) return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
Node* insert(Node* node, Result *result, bool *error) {
    *error = false;
    /* 1. Perform the normal BST insertion */
    if (node == nullptr) return(newNode(result));

    if (result->getResult() < node->result->getResult())
        node->left = insert(node->left, result, error);
    else if (result->getResult() > node->result->getResult())
        node->right = insert(node->right, result, error);
    else {
        // Equal keys are not allowed in BST
        *error = true;
        return node;
    }

    /* 2. Update height of this ancestor node */
    node->height = 1 + std::max(height(node->left), height(node->right));

    /* 3. Get the balance factor of this ancestor
        node to check whether this node became
        unbalanced */
    int balance = getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && result->getResult() < node->left->result->getResult())
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && result->getResult() > node->right->result->getResult())
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && result->getResult() > node->left->result->getResult())
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && result->getResult() < node->right->result->getResult())
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    /* return the (unchanged) node pointer */
    return node;
}


std::vector<Node*> searchAll(Node *root, float value, float range = 0.0000001) {
    std::vector<Node*> results;
    return searchAll(&results, root, value, range);
}

// TODO more accurate range
std::vector<Node*> searchAll(std::vector<Node*> *results, Node *root, float value, float range = 0.0000001) {
    /* base case */
    if (root == nullptr) return *results;

    float k1 = value-range, k2 = value+range;

    /* inorder type */

    /*  If root->data is greater than k1,
        then only we can get o/p keys
        in left subtree */
    if (k1 < root->result->getResult()) searchAll(results, root->left, value, range);

    /* if root's data lies in range,
    then prints root's data */
    if (k1 <= root->result->getResult() && k2 >= root->result->getResult()) results->push_back(root);

    /*  If root->data is smaller than k2,
        then only we can get o/p keys
        in right subtree */
    if (k2 > root->result->getResult()) searchAll(results, root->right, value, range);

    return *results;
}

Node *search(Node *root, float value, float range = 0.0000001) {
    std::vector<Node*> r = searchAll(root, value, range);
    for (Node *element : r) {
        if (nearlyEqual(value, element->result->getResult())) return element;
    }
    return nullptr;
}

std::vector<Result*> getInorder(std::vector<Result*> *list, Node *root) {
    if (root != nullptr) {
        getInorder(list, root->left);
        list->push_back(root->result);
        getInorder(list, root->right);
    }
    return *list;
}

std::vector<Result*> getInorder(Node *root) {
    std::vector<Result*> list;
    return getInorder(&list, root);
}