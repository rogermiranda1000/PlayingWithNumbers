#include "results.h"

Results::Results(uint8_t size) {
    this->_size = size;
    this->_list = (Node**) malloc(sizeof(Node*)*size);
    for (uint8_t n = 0; n < size; n++) this->_list[n] = nullptr;
}

Results::~Results() {
    for (Result *aux : this->getAll()) delete aux;

    free(this->_list);
}

bool Results::add(Result* result) {
    uint8_t uses = result->getUses()-1; // si tiene 'n' numeros, se almacena en 'n-1' (ya que es imposible que tenga 0 números)
    if (uses >= this->_size) return false;
    bool error;
    this->_list[uses] = insert(this->_list[uses], result, &error);
    if (error) return false;
    this->_unchecked.push_back(result);
    return true;
}

std::vector<Result*> Results::getUnchecked() {
    std::vector<Result*> copy = this->_unchecked;
    this->_unchecked.clear();
    return copy;
}

std::vector<Result*> Results::getAll() {
    std::vector<Result*> copy = getInorder(this->_list[0]);
    for (uint8_t n = 1; n < this->_size; n++) {
        getInorder(&copy, this->_list[n]);
    }
    return copy;
}

Node* Results::get(uint8_t used) {
    if (used == 0 || used > this->_size) return nullptr;
    return this->_list[used-1];
}