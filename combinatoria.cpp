#include "combinatoria.h"

Result::Result(float result, Result *a, Result *b, Operation type) {
    this->_origen = (Combination){a, b, type};
    this->_result = result;
    if (a == nullptr) this->_uses = 1; // primer elemento
    else {
        if (b == nullptr) this->_uses = a->_uses; // elemento único
        else this->_uses = a->_uses + b->_uses; // elemento compuesto
    }
}

float Result::getResult() {
    return this->_result;
}

/* OPERATOR OVERLOADING */

/**
 * toString()
 */
std::ostream& operator<<(std::ostream &strm, const Result &a) {
    switch (a._origen.type) {
        case NONE:
            return strm << a._result;
        case ADD:
            return strm << "(" << *a._origen.a << ")+(" << *a._origen.b << ")";
        case SUBTRACT:
            return strm << "(" << *a._origen.a << ")-(" << *a._origen.b << ")";
        case DIVIDE:
            return strm << "(" << *a._origen.a << ")/(" << *a._origen.b << ")";
        case MULTIPLY:
            return strm << "(" << *a._origen.a << ")*(" << *a._origen.b << ")";
        case POW:
            return strm << "(" << *a._origen.a << ")^(" << *a._origen.b << ")";
        case NEGATE:
            return strm << "-(" << *a._origen.a << ")";
        case FACTORIAL:
            return strm << "(" << *a._origen.a << ")!";
        default:
            return strm << "?";
    }
}

Result *Result::add(Result *r) {
    bool error;
    float result = secureAdd(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, ADD);
}

Result *Result::subtract(Result *r) {
    bool error;
    float result = secureSubtract(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, SUBTRACT);
}

Result *Result::divide(Result *r) {
    bool error;
    float result = secureDivide(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, DIVIDE);
}

Result *Result::inverseDivide(Result *r) {
    bool error;
    float result = secureDivide(&error, r->_result, this->_result);
    if (error) return nullptr;
    return new Result(result, r, this, DIVIDE);
}

Result *Result::multiply(Result *r) {
    bool error;
    float result = secureMultiply(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, MULTIPLY);
}

Result *Result::pow(Result *r) {
    bool error;
    float result = securePow(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, POW);
}

Result *Result::inversePow(Result *r) {
    bool error;
    float result = securePow(&error, r->_result, this->_result);
    if (error) return nullptr;
    return new Result(result, r, this, POW);
}

Result *Result::negate() {
    bool error;
    float result = secureNegate(&error, this->_result);
    if (error) return nullptr;
    return new Result(result, this, NEGATE);
}

Result *Result::factorial() {
    bool error;
    float result = secureFactorial(&error, this->_result);
    if (error) return nullptr;
    return new Result(result, this, FACTORIAL);
}