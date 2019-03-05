#include "innerjoin.h"
#include "on.h"

InnerJoin::InnerJoin(const Table& table, Operation* parent)
    : Operation(parent) {
    PartQuery_ = " INNER JOIN " + table.Name_;
}

InnerJoin::~InnerJoin() = default;

On& InnerJoin::ON(const Filter& filter) {
    On_.reset(new On(filter, this));
    return *On_;
}
