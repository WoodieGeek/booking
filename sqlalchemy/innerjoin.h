#ifndef INNERJOIN_H
#define INNERJOIN_H
#include "operations.h"
#include "filter.h"

struct On;

struct InnerJoin : public Operation {
    InnerJoin(const Table& table, Operation* parent = nullptr);
    On& ON(const Filter& filer);
    ~InnerJoin();
private:
    std::unique_ptr<On> On_;
};

#endif // INNERJOIN_H
