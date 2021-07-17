#pragma once

#include <vector>
#include "bst.h"
#include "combinatoria.h"

class Results {
public:
    Results(uint8_t size);
    ~Results();

    bool add(Result* result);

private:
    uint8_t _size;
    Node **_list;
};