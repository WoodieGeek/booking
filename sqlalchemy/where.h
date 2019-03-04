#ifndef WHERE_H
#define WHERE_H
#include "operations.h"

struct Where : public Operation {
    template <typename ...Cs>
    Where (Operation* parent = nullptr, Cs... columns) : Operation (parent, columns...) {
        PartQuery_ = " WHERE ";
    }

};

#endif // WHERE_H
