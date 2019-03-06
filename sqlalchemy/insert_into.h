#ifndef INSERT_INTO_H
#define INSERT_INTO_H
#include "operations.h"
#include "set.h"

struct InsertInto : public Operation {
    InsertInto(Operation* parent = nullptr) : Operation(parent) {
    }

    InsertInto& operator () (const Table& table) {
        PartQuery_ = "INSERT INTO " + table.Name_;
        return *this;
    }

    template <typename ...Cs>
    Set& SET(Cs... columns) {
        Set_.reset(new Set(false, this, columns...));
        return *Set_;
    }
private:
    std::unique_ptr<Set> Set_;

};

static InsertInto INSERT_INTO;

#endif // INSERT_INTO_H
