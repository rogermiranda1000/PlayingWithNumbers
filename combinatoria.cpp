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

uint8_t Result::getUses() {
    return this->_uses;
}

void Result::addIfNotNull(std::vector<Result*> *list, Result *element) {
    if (element == nullptr) return;
    list->push_back(element);
}

std::vector<Result*> Result::combine(Result *a) {
    std::vector<Result*> combinations;
    Result::addIfNotNull(&combinations, this->add(a));
    Result::addIfNotNull(&combinations, this->subtract(a));
    Result::addIfNotNull(&combinations, this->divide(a));
    Result::addIfNotNull(&combinations, this->inverseDivide(a));
    Result::addIfNotNull(&combinations, this->multiply(a));
    Result::addIfNotNull(&combinations, this->pow(a));
    Result::addIfNotNull(&combinations, this->inversePow(a));
    /*Result::addIfNotNull(&combinations, this->module(a));
    Result::addIfNotNull(&combinations, this->inverseModule(a));*/
#ifdef SQRT_OPERATIONS
    Result::addIfNotNull(&combinations, this->root(a));
    Result::addIfNotNull(&combinations, this->inverseRoot(a));
#endif
#ifdef LOG_OPERATIONS
    Result::addIfNotNull(&combinations, this->logN(a));
    Result::addIfNotNull(&combinations, this->inverseLogN(a));
#endif
    return combinations;
}

std::vector<Result*> Result::combineSelf() {
    std::vector<Result*> combinations;
    Result::addIfNotNull(&combinations, this->negate());
    Result::addIfNotNull(&combinations, this->factorial());
    Result::addIfNotNull(&combinations, this->doubleFactorial());
#ifdef SQRT_OPERATIONS
    Result::addIfNotNull(&combinations, this->sqrt());
#endif
#ifdef LOG_OPERATIONS
    Result::addIfNotNull(&combinations, this->naturalLog());
    Result::addIfNotNull(&combinations, this->log());
#endif
#ifdef GAMMA_OPERATION
    Result::addIfNotNull(&combinations, this->gamma());
#endif
    return combinations;
}

std::vector<Result*> Result::predict(Node *elements, float expected) {
    std::vector<Result*> combinations;

    Result *tmp;
    bool error;
    float need = secureSubtract(&error, expected, this->_result); // x+? = expected
    if (!error) Result::addIfNotNull(&combinations, this->add(search(elements, need, 0.0000001f)));

    need = secureSubtract(&error, this->_result, expected); // x-? = expected
    if (!error) Result::addIfNotNull(&combinations, this->subtract(search(elements, need, 0.0000001f)));

    need = secureDivide(&error, this->_result, expected); // x/? = expected
    if (!error) Result::addIfNotNull(&combinations, this->divide(search(elements, need, 0.0000001f)));

    need = secureMultiply(&error, this->_result, expected); // ?/x = expected
    if (!error) {
        tmp = search(elements, need, 0.0000001f);
        if (tmp != nullptr) Result::addIfNotNull(&combinations, tmp->divide(this));
    }

    need = secureDivide(&error, expected, this->_result); // x*? = expected
    if (!error) Result::addIfNotNull(&combinations, this->multiply(search(elements, need, 0.0000001f)));

    need = secureLogN(&error, this->_result, expected); // x^? = expected -> log[x](expected)
    if (!error) Result::addIfNotNull(&combinations, this->pow(search(elements, need, 0.0000001f)));

    need = secureRoot(&error, expected, this->_result); // ?^x = expected -> expected^(1/x)
    if (!error) {
        tmp = search(elements, need, 0.0000001f);
        if (tmp != nullptr) Result::addIfNotNull(&combinations, tmp->pow(this));
    }

    // TODO implement other predictions
    /*Result::addIfNotNull(&combinations, this->module(a));
    Result::addIfNotNull(&combinations, this->inverseModule(a));*/
#ifdef SQRT_OPERATIONS
    need = secureLogN(&error, expected, this->_result); // x^(1/?) = expected -> x = expected^? -> log[expected](x)
    if (!error) Result::addIfNotNull(&combinations, this->root(search(elements, need, 0.0000001f)));

    need = securePow(&error, expected, this->_result); // ?^(1/x) = expected -> expected^x
    if (!error) {
        tmp = search(elements, need, 0.0000001f);
        if (tmp != nullptr) Result::addIfNotNull(&combinations, tmp->root(this));
    }
#endif
#ifdef LOG_OPERATIONS
    need = secureRoot(&error, this->_result, expected); // log[?](x) = expected -> ?^expected = x -> x^(1/expected)
    if (!error) Result::addIfNotNull(&combinations, this->logN(search(elements, need, 0.0000001f)));

    need = securePow(&error, this->_result, expected); // log[x](?) = expected -> x^expected = ?
    if (!error) {
        tmp = search(elements, need, 0.0000001f);
        if (tmp != nullptr) Result::addIfNotNull(&combinations, tmp->logN(this));
    }
#endif

    return combinations;
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
        case ROOT:
            return strm << "(" << *a._origen.a << ")^(1/(" << *a._origen.b << "))";
        case LOG_N:
            return strm << "log[" << *a._origen.b << "](" << *a._origen.a << ")";
        case MODULE:
            return strm << "(" << *a._origen.a << ")%(" << *a._origen.b << ")";

        case NEGATE:
            return strm << "-(" << *a._origen.a << ")";
        case FACTORIAL:
            return strm << "(" << *a._origen.a << ")!";
        case DOUBLE_FACTORIAL:
            return strm << "(" << *a._origen.a << ")!!";
        case SQRT:
            return strm << "(" << *a._origen.a << ")^(1/2)";
        case LN:
            return strm << "ln(" << *a._origen.a << ")";
        case LOG:
            return strm << "log(" << *a._origen.a << ")";
        case GAMMA:
            return strm << "Γ(" << *a._origen.a << ")";

        default:
            return strm << "?";
    }
}

Result *Result::add(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureAdd(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, ADD);
}

Result *Result::subtract(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureSubtract(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, SUBTRACT);
}

Result *Result::divide(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureDivide(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, DIVIDE);
}

Result *Result::inverseDivide(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureDivide(&error, r->_result, this->_result);
    if (error) return nullptr;
    return new Result(result, r, this, DIVIDE);
}

Result *Result::multiply(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureMultiply(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, MULTIPLY);
}

Result *Result::pow(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = securePow(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, this, r, POW);
}

Result *Result::inversePow(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = securePow(&error, r->_result, this->_result);
    if (error) return nullptr;
    return new Result(result, r, this, POW);
}
Result *Result::root(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureRoot(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, r, this, ROOT);
}

Result *Result::inverseRoot(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureRoot(&error, r->_result, this->_result);
    if (error) return nullptr;
    return new Result(result, r, this, ROOT);
}

Result *Result::logN(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureLogN(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, r, this, LOG_N);
}

Result *Result::inverseLogN(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureLogN(&error, r->_result, this->_result);
    if (error) return nullptr;
    return new Result(result, r, this, LOG_N);
}

Result *Result::module(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureModule(&error, this->_result, r->_result);
    if (error) return nullptr;
    return new Result(result, r, this, MODULE);
}

Result *Result::inverseModule(Result *r) {
    bool error;
    if (r == nullptr) return nullptr;
    float result = secureModule(&error, r->_result, this->_result);
    if (error) return nullptr;
    return new Result(result, r, this, MODULE);
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

Result *Result::doubleFactorial() {
    bool error;
    float result = secureDoubleFactorial(&error, this->_result);
    if (error) return nullptr;
    return new Result(result, this, DOUBLE_FACTORIAL);
}

Result *Result::sqrt() {
    bool error;
    float result = secureSqrt(&error, this->_result);
    if (error) return nullptr;
    return new Result(result, this, SQRT);
}

Result *Result::naturalLog() {
    bool error;
    float result = secureLn(&error, this->_result);
    if (error) return nullptr;
    return new Result(result, this, LN);
}

Result *Result::log() {
    bool error;
    float result = secureLog(&error, this->_result);
    if (error) return nullptr;
    return new Result(result, this, LOG);
}

Result *Result::gamma() {
    bool error;
    float result = secureGamma(&error, this->_result);
    if (error) return nullptr;
    return new Result(result, this, GAMMA);
}