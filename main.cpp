#include <iostream>
#include "combinatoria.h"

int main() {
    Result *a = new Result(3.f), *b = new Result(-3.f);
    std::cout << *a << std::endl;
    //std::cout << Result(0, a, b, ADD) << std::endl;
    Result *c = (*a)+b;
    std::cout << *c << std::endl;

    delete a;
    delete b;
    delete c;

    return 0;
}
