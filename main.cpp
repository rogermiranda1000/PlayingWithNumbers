#include <iostream>
#include "combinatoria.h"

int main() {
    Result *a = new Result(3.f), *b = new Result(-3.f);
    Result *c = a->add(b);
    std::cout << *c << " [" << c->getResult() << "]" << std::endl;
    Result *d = a->factorial();
    std::cout << *d << " [" << d->getResult() << "]" << std::endl;

    delete a;
    delete b;
    delete c;
    delete d;

    return 0;
}
