#pragma once

#include <limits>
#include <cassert>
#include <cfloat>
#include <cmath>

bool nearlyEqual(float a, float b, float epsilon = 128 * FLT_EPSILON, float abs_th = FLT_MIN);