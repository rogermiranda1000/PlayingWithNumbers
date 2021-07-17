#include <iostream>
#include "combinatoria.h"
#include "bst.h"

int main() {
    Result *a = new Result(3e38), *b = new Result(3.f);
    Result *c = a->add(b);
    std::cout << *c << " [" << c->getResult() << "]" << std::endl;

    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);
    //std::vector<Node*> r = searchAll(root, 20, 11);
    Node* r = search(root, 20, 11);

    std::vector<Result*> aux = a->combine(b);

    delete a;
    delete b;
    delete c;

    return 0;
}
