#ifndef INNERJOIN_H
#define INNERJOIN_H
#include "operations.h"
#include "on.h"
#include "filter.h"

struct InnerJoin : public Operation {
    InnerJoin(Operation* parent = nullptr)
        : Operation(parent)
        , On_(this) {
        PartQuery_ = " INNER JOIN ";
    }

    On& ON(const Filter& filer) {
        On_.PartQuery_ += filer.Filter_;
        return On_;
    }
private:
    On On_;
};

#endif // INNERJOIN_H
