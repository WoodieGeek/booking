#ifndef SELECT_H
#define SELECT_H
#include "operations.h"
#include "from.h"

struct Select : public Operation {
    template <typename ...Cs>
    Select (Operation* parent = nullptr, Cs... columns)
        : Operation (parent, columns...)
        , From_(this) {
        PartQuery_ = "SELECT " + Names_;
    }

    template <typename ...Cs>
    Select& operator() (Cs... columns) {
        Names_.clear();
        From_.PartQuery_ = " FROM ";
        Parse(columns...);
        PartQuery_ = "SELECT " + Names_;
        return *this;
    }

    From& FROM(const Table& table) {
        From_.PartQuery_ += table.Name_;
        return From_;
    }

private:
    From From_;
};

static Select SELECT;

#endif // SELECT_H
