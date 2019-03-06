#ifndef SET_H
#define SET_H
#include "operations.h"

struct Set : public Operation {
    template <typename ...Cs>
    Set(bool addTable, Operation* parent = nullptr, Cs... columns) : Operation(addTable, parent, columns...) {
        PartQuery_ = " (" + Names_ + ") VALUES (" + Values_ + ") ";
    }
};

#endif // SET_H
