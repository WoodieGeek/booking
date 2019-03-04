#ifndef FROM_H
#define FROM_H
#include "operations.h"
#include "where.h"
#include "filter.h"
#include "innerjoin.h"

struct From : public Operation {
    From (Operation* parent = nullptr)
        : Operation (parent)
        , Where_(this)
        , InnerJoin_(this) {
        PartQuery_ = " FROM ";
    }

    Where& WHERE(const Filter& filter) {
        Where_.PartQuery_ += filter.Filter_;
        return Where_;
    }

    InnerJoin& INNER_JOIN(const Table& table) {
        InnerJoin_.PartQuery_ += table.Name_;
        return InnerJoin_;
    }

private:
    Where Where_;
    InnerJoin InnerJoin_;
};

#endif // FROM_H
