#pragma once

#include <iostream>
#include <cstdint>
#include <vector>
#include "secure_math.h"
#include "bst.h"

/**
 * Enable operations like root, sqrt
 * /!\ Those are slow operations /!\
 */
#define SQRT_OPERATIONS

/**
 * Enable operations like logN, ln and log10
 * /!\ Those are imprecise operations /!\
 */
//#define LOG_OPERATIONS

/**
 * Enable the gamma operation
 * /!\ Imprecise operation /!\
 */
//#define GAMMA_OPERATION

typedef enum {
    NONE,

    ADD,            // a+b
    SUBTRACT,       // a-b
    DIVIDE,         // a/b
    MULTIPLY,       // a*b
    POW,            // a^b
    ROOT,           // a^(1/b)
    LOG_N,          // log[b](a)
    MODULE,         // a%b

    NEGATE,         // -a
    FACTORIAL,      // a!
    SQRT,           // a^(1/2)
    LN,             // ln(a)
    LOG,            // log(a)
    GAMMA           // Γ(x)
} Operation;

class Result;
class Node;

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
    std::vector<Result*> predict(Node *elements, float expected); // recuerda eliminar los resultados al terminar!

    /* OPERATOR OVERLOADING */
    friend std::ostream& operator<<(std::ostream &strm, const Result &a); // toString()
    Result *add(Result *r);
    Result *subtract(Result *r);
    Result *divide(Result *r);
    Result *inverseDivide(Result *r);
    Result *multiply(Result *r);
    Result *pow(Result *r);
    Result *inversePow(Result *r);
    Result *root(Result *r);
    Result *inverseRoot(Result *r);
    Result *logN(Result *r);
    Result *inverseLogN(Result *r);
    Result *module(Result *r);
    Result *inverseModule(Result *r);
    Result *negate();
    Result *factorial();
    Result *sqrt();
    Result *naturalLog();
    Result *log();
    Result *gamma();
private:
    Combination _origen;
    float _result;
    uint8_t _uses; // número de veces que se ha usado el número

    static void addIfNotNull(std::vector<Result*> *list, Result *element);
};