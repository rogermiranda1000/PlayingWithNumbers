#include <iostream>
#include "secure_math.h"

int main() {
    bool error;
    std::cout << secureFactorial(&error, 34.0) << " (" << error << ")" << std::endl;
    return 0;
}
