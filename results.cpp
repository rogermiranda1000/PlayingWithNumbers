#include "results.h"

Results::Results(uint8_t size) {
    this->_size = size;
    this->_list = (Node**)malloc(sizeof(Node*)*size);
    for (uint8_t n = 0; n < size; n++) this->_list[n] = nullptr;
}

Results::~Results() {
    for (uint8_t n = 0; n < this->_size; n++) {
        for (Result *aux : getInorder(this->_list[n])) delete aux;
    }

    delete this->_list;
}

bool Results::add(Result* result) {
    uint8_t uses = result->getUses()-1; // si tiene 'n' numeros, se almacena en 'n-1' (ya que es imposible que tenga 0 números)
    if (uses >= this->_size) return false;
    this->_list[uses] = insert(this->_list[uses], result);
    return true;
}