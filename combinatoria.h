#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include "secure_math.h"

typedef enum {
    NONE,

    ADD,            // a+b
    SUBTRACT,       // a-b
    DIVIDE,         // a/b
    MULTIPLY,       // a*b
    POW,            // a^b

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
    /* CONSTRUCTOR/DESTRUCTOR */
    Result(float result, Result *a, Result *b, Operation type);
    Result(float result, Result *a, Operation type) : Result(result, a, nullptr, type) {}
    Result(float result) : Result(result, nullptr, nullptr, NONE) {}
    //~Result(void);

    /* METHODS */
    float getResult();
    uint8_t getUses();
    std::vector<Result*> combine(Result *a);    // recuerda eliminar los resultados al terminar!
    std::vector<Result*> combineSelf();         // recuerda eliminar los resultados al terminar!

    /* OPERATOR OVERLOADING */
    friend std::ostream& operator<<(std::ostream &strm, const Result &a); // toString()
    Result *add(Result *r);
    Result *subtract(Result *r);
    Result *divide(Result *r);
    Result *inverseDivide(Result *r);
    Result *multiply(Result *r);
    Result *pow(Result *r);
    Result *inversePow(Result *r);
    Result *negate();
    Result *factorial();
private:
    Combination _origen;
    float _result;
    uint8_t _uses; // número de veces que se ha usado el número

    static void addIfNotNull(std::vector<Result*> *list, Result *element);
};