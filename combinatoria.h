#pragma once

#include <iostream>
#include <cstdint>
#include "secure_math.h"

typedef enum {
    NONE,

    ADD,            // a+b
    SUBTRACT,       // a-b
    DIVIDE,         // a/b
    INSERVE_DIVIDE, // b/a
    MULTIPLY,       // a*b
    POW,            // a^b
    INSERVE_POW,    // b^a

    NEGATE,         // -a
    FACTORIAL       // a!
} Operation;

class Result;

typedef struct {
    Result *a;
    Result *b;
    Operation type;
} Combination;

class Result {
public:
    Result(float result, Result *a, Result *b, Operation type);
    Result(float result, Result *a, Operation type) : Result(result, a, nullptr, type) {}
    Result(float result) : Result(result, nullptr, nullptr, NONE) {}
    //~Result(void);

    friend std::ostream& operator<<(std::ostream &strm, const Result &a); // toString()
private:
    Combination _origen;
    float _result;
    uint8_t _uses; // número de veces que se ha usado el número
};