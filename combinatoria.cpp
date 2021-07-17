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
        case INSERVE_DIVIDE:
            return strm << "(" << *a._origen.b << ")/(" << *a._origen.a << ")";
        case MULTIPLY:
            return strm << "(" << *a._origen.a << ")*(" << *a._origen.b << ")";
        case POW:
            return strm << "(" << *a._origen.a << ")^(" << *a._origen.b << ")";
        case INSERVE_POW:
            return strm << "(" << *a._origen.b << ")^(" << *a._origen.a << ")";
        case NEGATE:
            return strm << "-(" << *a._origen.a << ")";
        case FACTORIAL:
            return strm << "!(" << *a._origen.a << ")";
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