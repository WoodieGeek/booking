#ifndef FILTER_H
#define FILTER_H
#include <QString>

struct Filter {
    Filter() = default;
    Filter(const QString& filter) : Filter_(filter) {}
    const Filter& operator & (const Filter& rhs) {
        Filter result(Filter_ + " and " + rhs.Filter_);
        return result;
    }
    const Filter& operator | (const Filter& rhs) {
        Filter result(Filter_ + " or " + rhs.Filter_);
        return result;
    }
    QString Filter_;

};

#endif // FILTER_H
