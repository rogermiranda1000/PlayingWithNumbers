#include "secure_math.h"

static float _cache_factorial[FACTORIAL_OVERFLOW] = {1};

float secureAdd(bool *error, float a, float b) {
    std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);
    float r = a+b;
    *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW);
    return r;
}

float secureSubtract(bool *error, float a, float b) {
    std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW);
    float r = a-b;
    *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW);
    return r;
}

float secureMultiply(bool *error, float a, float b) {
    std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    float r = a*b;
    *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    return r;
}

float secureDivide(bool *error, float a, float b) {
    std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    float r = a/b;
    *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    return r;
}

float securePow(bool *error, float a, float b) {
    std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    float r = powf(a, b);
    *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    return r;
}

float secureNegate(bool *error, float a) {
    // TODO hay algo malo con negar?
    *error = false;
    return -a;
}

float secureFactorial(bool *error, float a) {
    int value = (int)roundf(a);
    if (!nearlyEqual(a, (float)value)) {
        // es decimal
        *error = true;
        return -1;
    }
    // TODO factorial decimal
    return secureFactorial(error, value);
}

float secureFactorial(bool *error, int a) {
    if (a < 0 || a >= FACTORIAL_OVERFLOW) {
        // no es positivo, o es decimal
        // >34 daria overflow en float
        *error = true;
        return -1;
    }

    *error = false;
    if (_cache_factorial[a] == 0) {
        // no está en la cache; hay que calcularlo
        _cache_factorial[a] = (float)a*secureFactorial(error, a-1);
    }
    return _cache_factorial[a];
}