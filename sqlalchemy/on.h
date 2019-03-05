#ifndef ON_H
#define ON_H
#include "operations.h"
#include "innerjoin.h"
#include "filter.h"
#include "where.h"

struct On : public Operation {
    On(const Filter& filter, Operation* parent)
        : Operation(parent) {
        PartQuery_ = " ON " + filter.Filter_;
    }

    Where& WHERE(const Filter& filter) {
        Where_.reset(new Where(filter, this));
        return *Where_;
    }

    InnerJoin& INNER_JOIN(const Table& table) {
        InnerJoin_.reset(new InnerJoin(table, this));
        return *InnerJoin_;
    }
private:
    std::unique_ptr<InnerJoin> InnerJoin_;
    std::unique_ptr<Where> Where_;
};

#endif // ON_H
