#ifndef WHERE_H
#define WHERE_H
#include "operations.h"
#include "filter.h"
struct Where : public Operation {
    template <typename ...Cs>
    Where (const Filter& filter, Operation* parent = nullptr) : Operation (parent) {
        PartQuery_ = " WHERE " + filter.Filter_;
    }
};

#endif // WHERE_H
