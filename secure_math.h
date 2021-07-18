#pragma once

#include <cfenv>
#include "float_range.h"

#define FACTORIAL_OVERFLOW 35 // 35! excede el límite del float

float secureAdd(bool *error, float a, float b);
float secureSubtract(bool *error, float a, float b);
float secureMultiply(bool *error, float a, float b);
float secureDivide(bool *error, float a, float b);
float securePow(bool *error, float a, float b);
float secureRoot(bool *error, float a, float b);
float secureLogN(bool *error, float a, float b);

float secureNegate(bool *error, float a);
float secureFactorial(bool *error, float a);
float secureFactorial(bool *error, int a);
float secureSqrt(bool *error, float a);
float secureLn(bool *error, float a);
float secureLog(bool *error, float a);