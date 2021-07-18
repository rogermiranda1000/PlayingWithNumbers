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

float secureRoot(bool *error, float a, float b) {
    return securePow(error, a, 1.f/b);
}

float secureLogN(bool *error, float a, float b) {
    std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    float r = log10f(a);
    *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    if (!(*error)) {
        float tmp = log10f(b);
        *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
        if (!(*error)) r /= tmp;
    }
    return r;
}

// TODO negative module? decimal module?
float secureModule(bool *error, float a, float b) {
    std::feclearexcept(FE_INVALID);
    float  r = fmodf(a, b);
    *error = (bool)std::fetestexcept(FE_INVALID);
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

float secureSqrt(bool *error, float a) {
    return securePow(error, a, 1.f/2.f);
}

float secureLn(bool *error, float a) {
    std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    float r = logf(a);
    *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    return r;
}

float secureLog(bool *error, float a) {
    std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    float r = log10f(a);
    *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
    return r;
}

float secureGamma(bool *error, float z) {
    // https://stackoverflow.com/a/15454784/9178470
    static int g = 7;
    static float C[] = {0.99999999999980993, 676.5203681218851, -1259.1392167224028,771.32342877765313, -176.61502916214059, 12.507343278686905, -0.13857109526572012, 9.9843695780195716e-6, 1.5056327351493116e-7};
    float tmp;

    if (z < 0.5) {
        tmp = secureGamma(error, 1 - z);
        if (*error) return -1;
        std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
        tmp = M_PI / (sinf(M_PI * z) * tmp);
        *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
        return tmp;
    }
    else {
        z -= 1;

        std::feclearexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
        float x = C[0];
        for (int i = 1; i < g + 2; i++) x += C[i] / (z + (float)i);

        float t = z + (float)g + 0.5f;
        *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
        if (*error) return -1;
        tmp = sqrtf(2 *M_PI) * powf(t, (z + 0.5f)) * expf(-t) * x;
        *error = (bool)std::fetestexcept(FE_OVERFLOW | FE_UNDERFLOW | FE_INVALID | FE_DIVBYZERO);
        return tmp;
    }
}