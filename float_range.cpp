#include "float_range.h"

bool nearlyEqual(float a, float b, float epsilon, float abs_th) {
    assert(std::numeric_limits<float>::epsilon() <= epsilon);
    assert(epsilon < 1.f);

    if (a == b) return true;

    float diff = std::abs(a-b);
    return diff < std::fmax(abs_th, epsilon * (std::abs(a) + std::abs(b)));
}