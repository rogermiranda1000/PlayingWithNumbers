#include "bst.h"

/* A utility function to right
   rotate subtree rooted with y
   See the diagram given above. */
NODE_TEMPLATE
Node *Node::rightRotate() {
    Node *x = this->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(y->left.height, y->right.height) + 1;
    x->height = std::max(x->left.height, x->right.height) + 1;

    // Return new root
    return x;
}

/* A utility function to left
   rotate subtree rooted with x
   See the diagram given above. */
NODE_TEMPLATE
Node *Node::leftRotate() {
    Node *y = this->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(x->left.height, x->right.height) + 1;
    y->height = std::max(y->left.height, y->right.height) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
NODE_TEMPLATE
int Node::getBalance() {
    return height(this->left) - height(this->right);
}

// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.
NODE_TEMPLATE
Node* Node::insert(T *result, bool *error) {
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
    int balance = Node::getBalance(node);

    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && result->getResult() < node->left->result->getResult())
        return node->rightRotate();

    // Right Right Case
    if (balance < -1 && result->getResult() > node->right->result->getResult())
        return node->leftRotate();

    // Left Right Case
    if (balance > 1 && result->getResult() > node->left->result->getResult())
    {
        node->left = node->left->leftRotate();
        return node->rightRotate();
    }

    // Right Left Case
    if (balance < -1 && result->getResult() < node->right->result->getResult())
    {
        node->right = node->right->rightRotate();
        return node->leftRotate();
    }

    /* return the (unchanged) node pointer */
    return node;
}

NODE_TEMPLATE
std::vector<Node*> Node::searchAll(E value) {
    std::vector<Node*> results;
    return this->searchAll(results, value);
}

NODE_TEMPLATE
std::vector<Node*> Node::searchAll(std::vector<Node*> &results, E value) {
    float k1 = value-range, k2 = value+range;

    /* inorder type */

    /*  If root->data is greater than k1,
        then only we can get o/p keys
        in left subtree */
    if (k1 < root->result->getResult() && root->left != nullptr) searchAll(results, value);

    /* if root's data lies in range,
    then prints root's data */
    if (k1 <= root->result->getResult() && k2 >= root->result->getResult()) results.push_back(root);

    /*  If root->data is smaller than k2,
        then only we can get o/p keys
        in right subtree */
    if (k2 > root->result->getResult() && root->right != nullptr) searchAll(results, value);

    return results;
}

NODE_TEMPLATE
T *Node::search(NodeElementComparator<E> value) {
    std::vector<Node*> r = searchAll(root, value, range);
    for (Node *element : r) {
        if (value.equals(element->result)) return element->result;
    }
    return nullptr;
}

NODE_TEMPLATE
std::vector<T*> Node::getInorder(std::vector<T*> *list, Node *root) {
    if (root != nullptr) {
        getInorder(list, root->left);
        list->push_back(root->result);
        getInorder(list, root->right);
    }
    return *list;
}

NODE_TEMPLATE
std::vector<T*> Node::getInorder(Node *root) {
    std::vector<T*> list;
    return getInorder(&list, root);
}