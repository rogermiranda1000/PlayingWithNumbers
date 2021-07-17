#pragma once

#include <cfenv>
#include <cmath>

#define FACTORIAL_OVERFLOW 35 // 35! excede el límite del float

float secureAdd(bool *error, float a, float b);
float secureSubtract(bool *error, float a, float b);
float secureMultiply(bool *error, float a, float b);
float secureDivide(bool *error, float a, float b);
float securePow(bool *error, float a, float b);

float secureNegate(bool *error, float a);
float secureFactorial(bool *error, float a);
float secureFactorial(bool *error, int a);