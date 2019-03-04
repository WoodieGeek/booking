#ifndef ON_H
#define ON_H
#include "operations.h"

struct On : public Operation {
    On(Operation* parent)
        : Operation(parent) {
        PartQuery_ = " ON ";
    }
};

#endif // ON_H
