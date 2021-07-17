#include <iostream>
#include "combinatoria.h"

int main() {
    Result *a = new Result(3.f), *b = new Result(-3.f);
    std::cout << *a << std::endl;
    //std::cout << Result(0, a, b, ADD) << std::endl;
    Result *c = a->add(b);
    std::cout << *c << std::endl;
    Result *d = (new Result(2.4e38))->add(new Result(2e38));
    if (d != nullptr) std::cout << *d << std::endl;
    else std::cout << "Error" << std::endl;

    delete a;
    delete b;
    delete c;
    delete d;

    return 0;
}
