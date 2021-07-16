#include <cfloat>
#include <limits>
#include <cassert>
#include "secure_math.h"

float _cache_factorial[FACTORIAL_OVERFLOW] = {1};

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

float securePower(bool *error, float a, float b) {
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

bool nearlyEqual(float a, float b, float epsilon = 128 * FLT_EPSILON, float abs_th = FLT_MIN) {
    assert(std::numeric_limits<float>::epsilon() <= epsilon);
    assert(epsilon < 1.f);

    if (a == b) return true;

    float diff = std::abs(a-b);
    float norm = std::fmin((std::abs(a) + std::abs(b)), std::numeric_limits<float>::max());
    return diff < std::fmax(abs_th, epsilon * norm);
}

float secureFactorial(bool *error, float a) {
    int value = (int)roundf(a);
    if (!nearlyEqual(a, (float)value)) {
        // es decimal
        *error = true;
        return -1;
    }
    // TODO factorial decimal
    return secureFactorialI(error, value);
}

float secureFactorialI(bool *error, int a) {
    if (a < 0 || a >= FACTORIAL_OVERFLOW) {
        // no es positivo, o es decimal
        // >34 daria overflow en float
        *error = true;
        return -1;
    }

    *error = false;
    if (_cache_factorial[a] == 0) {
        // no está en la cache; hay que calcularlo
        _cache_factorial[a] = (float)a*secureFactorialI(error, a-1);
    }
    return _cache_factorial[a];
}