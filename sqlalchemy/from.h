#ifndef FROM_H
#define FROM_H
#include "operations.h"
#include "where.h"
#include "filter.h"
#include "innerjoin.h"

struct From : public Operation {
    From (const Table& table, Operation* parent = nullptr)
        : Operation (parent) {
        PartQuery_ = " FROM " + table.Name_;
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
    std::unique_ptr<Where> Where_;
    std::unique_ptr<InnerJoin> InnerJoin_;
};

#endif // FROM_H
