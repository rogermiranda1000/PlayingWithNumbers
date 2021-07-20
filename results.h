#pragma once

#include <vector>
#include "bst.h"
#include "combinatoria.h"

class Results {
public:
    Results(uint8_t size);
    ~Results();

    bool add(Result* result);
    std::vector<Result*> getUnchecked();
    std::vector<Result*> getAll();
    Node* get(uint8_t used);

private:
    uint8_t _size;
    Node **_list;
    std::vector<Result*> _unchecked;
};