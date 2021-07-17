#include <iostream>
#include "combinatoria.h"
#include "bst.h"

int main() {
    Result *a = new Result(3.f), *b = new Result(-3.f);
    Result *c = a->add(b);
    std::cout << *c << " [" << c->getResult() << "]" << std::endl;
    Result *d = a->factorial();
    std::cout << *d << " [" << d->getResult() << "]" << std::endl;

    Node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    delete a;
    delete b;
    delete c;
    delete d;

    return 0;
}
