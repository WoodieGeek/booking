#ifndef SELECT_H
#define SELECT_H
#include "operations.h"
#include "from.h"

struct Select : public Operation {
    template <typename ...Cs>
    Select (Operation* parent = nullptr, Cs... columns)
        : Operation (true, parent, columns...) {
        PartQuery_ = "SELECT " + Names_;
    }

    template <typename ...Cs>
    Select& operator() (Cs... columns) {
        Names_.clear();
        Parse(true, columns...);
        PartQuery_ = "SELECT " + Names_;
        return *this;
    }

    From& FROM(const Table& table) {
        From_.reset(new From(table, this));
        return *From_;
    }

private:
    std::unique_ptr<From> From_;
};

static Select SELECT;

#endif // SELECT_H
